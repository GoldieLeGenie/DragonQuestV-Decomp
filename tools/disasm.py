#!/usr/bin/env python3
"""Disassembles a range of a module of this game (or of the DQ IV decomp).

usage: disasm.py MODULE START END [--thumb] [--project PATH] [--version eur]
"""

import argparse
import re
from pathlib import Path

import capstone

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("module")
parser.add_argument("start", type=lambda v: int(v, 16))
parser.add_argument("end", type=lambda v: int(v, 16))
parser.add_argument("--thumb", action="store_true")
parser.add_argument("--project", type=Path, default=Path("."))
parser.add_argument("--version", default="eur")
args = parser.parse_args()

extract = args.project / "extract" / args.version
if args.module == "main":
    image, base = (extract / "arm9" / "arm9.bin").read_bytes(), 0x02000000
else:
    image = (extract / "arm9_overlays" / f"{args.module}.bin").read_bytes()
    text = (extract / "arm9_overlays" / "overlays.yaml").read_text()
    base = int(re.search(rf"- id: {int(args.module[2:])}\n\s+base_address: (\d+)", text).group(1))
md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB if args.thumb else capstone.CS_MODE_ARM)
address = args.start
while address < args.end:
    # Data that is no instruction (literal pools) is printed as words.
    for insn in md.disasm(image[address - base:args.end - base], address):
        print(f"  {insn.address:08x}  {insn.bytes.hex():12s} {insn.mnemonic} {insn.op_str}")
        address = insn.address + insn.size
    if address < args.end:
        word = image[address - base:address - base + 4]
        print(f"  {address:08x}  {word.hex():12s} .word 0x{int.from_bytes(word, 'little'):08x}")
        address += 4
