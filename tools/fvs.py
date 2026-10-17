#!/usr/bin/env python3
"""Compares a function of a source file with the original code at an address.

Builds the source's object, takes the function NAME (or the functions in
order, with --all and a START address) and shows its disassembly next to the
original's at ADDR (relocated words masked on both sides). Useful before the
unit has a delinks.txt entry or names.

usage: fvs.py SOURCE NAME ADDR [--module main] [--version eur]
       fvs.py SOURCE --all START [--module main]      (summary of every function)
       fvs.py SOURCE --match START END                 (pair functions by identical bytes)
"""

import argparse
import bisect
import re
import subprocess
import sys
from pathlib import Path

import capstone
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("source")
parser.add_argument("name", nargs="?")
parser.add_argument("addr", nargs="?", type=lambda v: int(v, 16))
parser.add_argument("--all", type=lambda v: int(v, 16))
parser.add_argument("--match", nargs=2, type=lambda v: int(v, 16))
parser.add_argument("--module", default="main")
parser.add_argument("--skip", action="append", default=[])
parser.add_argument("--version", default="eur")
args = parser.parse_args()

built = Path("build") / args.version / Path(args.source).with_suffix(".o")
result = subprocess.run(["ninja", str(built).replace("\\", "/")], capture_output=True, text=True)
if result.returncode != 0:
    sys.exit(result.stdout + result.stderr)

extract = Path("extract") / args.version
config = Path("config") / args.version / "arm9"
if args.module == "main":
    image, base = (extract / "arm9" / "arm9.bin").read_bytes(), 0x02000000
    relocs_path = config / "relocs.txt"
else:
    image = (extract / "arm9_overlays" / f"{args.module}.bin").read_bytes()
    text = (extract / "arm9_overlays" / "overlays.yaml").read_text()
    base = int(re.search(rf"- id: {int(args.module[2:])}\n\s+base_address: (\d+)", text).group(1))
    relocs_path = config / "overlays" / args.module / "relocs.txt"
relocs = sorted(int(m.group(1), 16) for m in re.finditer(r"from:0x([0-9a-f]+)", relocs_path.read_text()))

elf = ELFFile(open(built, "rb"))
sections = list(elf.iter_sections())
symtab = elf.get_section_by_name(".symtab")
masks = {}
for section in sections:
    if isinstance(section, RelocationSection):
        masks.setdefault(section["sh_info"], set()).update(r["r_offset"] & ~1 for r in section.iter_relocations())
mapping = {}
for symbol in symtab.iter_symbols():
    if symbol.name in ("$a", "$t") and isinstance(symbol["st_shndx"], int):
        mapping.setdefault(symbol["st_shndx"], []).append((symbol["st_value"], symbol.name == "$t"))
functions = []
for symbol in symtab.iter_symbols():
    if symbol["st_info"]["type"] == "STT_FUNC" and isinstance(symbol["st_shndx"], int) and not symbol.name.startswith("$"):
        index = symbol["st_shndx"]
        start = symbol["st_value"] & ~1
        raw = bytearray(sections[index].data()[start:start + symbol["st_size"]])
        for offset in masks.get(index, ()):
            if start <= offset < start + len(raw):
                raw[offset - start:offset - start + 4] = b"\0\0\0\0"
        modes = [t for o, t in sorted(mapping.get(index, [])) if o <= start]
        functions.append((index, start, symbol.name, bytes(raw), bool(modes and modes[-1])))
functions.sort()


def original(address, size):
    raw = bytearray(image[address - base:address - base + size])
    index = bisect.bisect_left(relocs, address)
    while index < len(relocs) and relocs[index] < address + size:
        offset = relocs[index] - address
        raw[offset:offset + 4] = b"\0\0\0\0"
        index += 1
    return bytes(raw)


def disassemble(raw, thumb):
    md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB if thumb else capstone.CS_MODE_ARM)
    lines, address = [], 0
    while address < len(raw):
        for insn in md.disasm(raw[address:], address):
            lines.append(f"{insn.address:4x}  {insn.mnemonic} {insn.op_str}")
            address = insn.address + insn.size
        if address < len(raw):
            lines.append(f"{address:4x}  .word {raw[address:address + 4].hex()}")
            address += 4
    return lines


def rom_functions():
    sizes = {}
    for line in (config / "symbols.txt" if args.module == "main" else config / "overlays" / args.module / "symbols.txt").read_text().splitlines():
        m = re.match(r"^(\S+) kind:function\(\w+,size=0x([0-9a-f]+)\) addr:0x([0-9a-f]+)", line)
        if m:
            sizes[int(m.group(3), 16) & ~1] = (int(m.group(2), 16), m.group(1))
    return sizes


if args.match is not None:
    # Pair our functions with this game's functions of the range by identical masked bytes.
    lo, hi = args.match
    rom = {a: v for a, v in rom_functions().items() if lo <= a < hi}
    used = set()
    for _, _, name, raw, thumb in functions:
        hit = None
        for a in sorted(rom):
            size, their = rom[a]
            if a not in used and size == len(raw) and original(a, size) == raw:
                hit = a
                break
        if hit is not None:
            used.add(hit)
            print(f"  {hit:08x} {len(raw):5x} same {name}")
        else:
            print(f"  -------- {len(raw):5x} ---- {name}")
    for a in sorted(rom):
        if a not in used:
            print(f"  {a:08x} {rom[a][0]:5x} UNMATCHED ROM {rom[a][1]}")
    sys.exit()

if args.all is not None:
    # Walk this game's functions (symbols.txt sizes) next to the source's.
    sizes = {}
    for line in (config / "symbols.txt" if args.module == "main" else config / "overlays" / args.module / "symbols.txt").read_text().splitlines():
        m = re.match(r"^(\S+) kind:function\(\w+,size=0x([0-9a-f]+)\) addr:0x([0-9a-f]+)", line)
        if m:
            sizes[int(m.group(3), 16) & ~1] = (int(m.group(2), 16), m.group(1))
    address = args.all
    for _, _, name, raw, thumb in functions:
        if name in args.skip:
            continue
        size, their_name = sizes.get(address, (len(raw), "?"))
        theirs = original(address, len(raw))
        verdict = "same" if theirs == raw and size == len(raw) else "DIFF"
        print(f"{address:08x} {size:5x} {len(raw):5x} {verdict} {name}  ({their_name})")
        address += size
        while address not in sizes and address < args.all + 0x100000 and any(a > address for a in sizes):
            address += 2
    sys.exit()

for _, _, name, raw, thumb in functions:
    if name == args.name:
        theirs = original(args.addr, len(raw) + 0x40)
        a, b = disassemble(theirs, thumb), disassemble(raw, thumb)
        for i in range(max(len(a), len(b))):
            left = a[i] if i < len(a) else ""
            right = b[i] if i < len(b) else ""
            print(f"  {'  ' if left == right else '! '}{left:45s} | {right}")
        break
else:
    sys.exit(f"{args.name} not in the object; functions: " + " ".join(f[2] for f in functions))
