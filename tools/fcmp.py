#!/usr/bin/env python3
"""Compares a source file's compiled functions with the original ones, one by one.

Builds the source's object, then compares each function of its .text with the
delinked original's function of the same name (relocated words masked on both
sides). Functions only in one of them are listed too.

usage: fcmp.py SOURCE [--version eur] [-v NAME]   (-v: disassembly of both)
"""

import argparse
import re
import subprocess
import sys
from pathlib import Path

import capstone
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("source")
parser.add_argument("--version", default="eur")
parser.add_argument("-v", "--verbose", action="append", default=[])
args = parser.parse_args()

stem = Path(args.source).with_suffix(".o")
built = Path("build") / args.version / stem
original = Path("build") / args.version / "delinks" / stem
targets = [built, Path("build") / args.version / "delinks" / "delink.yaml"]
result = subprocess.run(["ninja", *[str(t).replace("\\", "/") for t in targets]], capture_output=True, text=True)
if result.returncode != 0:
    sys.exit(result.stdout + result.stderr)


def functions(path):
    elf = ELFFile(open(path, "rb"))
    sections = {}
    for index, section in enumerate(elf.iter_sections()):
        if section.name.startswith(".text") or section.name == ".init":
            sections[index] = (section.data(), {}, section.name)
    symtab = elf.get_section_by_name(".symtab")
    for section in elf.iter_sections():
        if isinstance(section, RelocationSection) and section["sh_info"] in sections:
            for reloc in section.iter_relocations():
                target = symtab.get_symbol(reloc["r_info_sym"])
                name = target.name if target["st_info"]["type"] != "STT_SECTION" else ""
                sections[section["sh_info"]][1][reloc["r_offset"] & ~1] = name
    found = {}
    mapping = {}     # $a/$t mapping symbols: the instruction set of each place
    for symbol in symtab.iter_symbols():
        if symbol.name in ("$a", "$t") and symbol["st_shndx"] in sections:
            mapping.setdefault(symbol["st_shndx"], []).append((symbol["st_value"], symbol.name == "$t"))
    for symbol in symtab.iter_symbols():
        if symbol["st_info"]["type"] != "STT_FUNC" or symbol["st_shndx"] not in sections or symbol.name.startswith("$"):
            continue
        data, relocs, _ = sections[symbol["st_shndx"]]
        start = symbol["st_value"] & ~1
        size = symbol["st_size"]
        raw = bytearray(data[start:start + size])
        for offset in relocs:
            if start <= offset < start + size:
                raw[offset - start:offset - start + 4] = b"\0\0\0\0"
        modes = [thumb for offset, thumb in sorted(mapping.get(symbol["st_shndx"], [])) if offset <= start]
        targets = {offset - start: name for offset, name in relocs.items() if start <= offset < start + size}
        found[symbol.name] = (bytes(raw), (symbol["st_value"] & 1) or (modes[-1] if modes else 0), start, targets)
    return found


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


ours = functions(built)
theirs = functions(original)
same = 0
auto_re = re.compile(r"^(?:func|data|@|\.L|__sinit)")
for name, (raw, thumb, start, targets) in sorted(theirs.items(), key=lambda item: item[1][2]):
    if name not in ours:
        print(f"  MISSING  {name}")
        continue
    mine = ours[name][0]
    # Masked bytes hide the targets: the named ones must agree too.
    wrong = [(offset, their, ours[name][3].get(offset)) for offset, their in sorted(targets.items())
             if their and not auto_re.match(their) and ours[name][3].get(offset) not in (their, None, "")]
    for offset, their, our in wrong:
        print(f"  TARGET   {name} +{offset:#x}: original calls {their}, the source {our}")
    if mine == raw and not wrong:
        same += 1
        if name not in args.verbose:
            continue
    else:
        first = next((i for i in range(min(len(mine), len(raw))) if mine[i] != raw[i]), min(len(mine), len(raw)))
        print(f"  DIFFERS  {name} (size {len(raw):#x}, ours {len(mine):#x}, first difference at +{first:#x})")
    if name in args.verbose or len(args.verbose) == 1 and args.verbose[0] == "all":
        a, b = disassemble(raw, thumb), disassemble(mine, thumb)
        for i in range(max(len(a), len(b))):
            left = a[i] if i < len(a) else ""
            right = b[i] if i < len(b) else ""
            print(f"    {'  ' if left == right else '! '}{left:45s} | {right}")
for name in ours:
    if name not in theirs:
        print(f"  EXTRA    {name}")
print(f"{same}/{len(theirs)} functions identical")
