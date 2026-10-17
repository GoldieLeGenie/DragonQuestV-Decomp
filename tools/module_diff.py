#!/usr/bin/env python3
"""Lists where a built module differs from the original, by source file.

usage: module_diff.py MODULE [--version eur]     (MODULE: main, itcm, dtcm, ov000...)
"""

import argparse
import re
from pathlib import Path

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("module")
parser.add_argument("--version", default="eur")
args = parser.parse_args()

extract = Path("extract") / args.version
build = Path("build") / args.version / "build"
config = Path("config") / args.version / "arm9"
if args.module == "main":
    original, built, base, delinks = extract / "arm9" / "arm9.bin", build / "arm9.bin", 0x02000000, config / "delinks.txt"
else:
    number = int(args.module[2:])
    original = extract / "arm9_overlays" / f"{args.module}.bin"
    built = build / f"arm9_{args.module}.bin"
    delinks = config / "overlays" / args.module / "delinks.txt"
    text = (extract / "arm9_overlays" / "overlays.yaml").read_text()
    base = int(re.search(rf"- id: {number}\n\s+base_address: (\d+)", text).group(1))

units = []
source = None
for line in delinks.read_text().splitlines():
    if line and not line[0].isspace() and line.rstrip().endswith(":"):
        source = line.rstrip()[:-1]
    match = re.match(r"\s+(\.\w+)\s+start:0x([0-9a-f]+) end:0x([0-9a-f]+)", line)
    if match and source:
        units.append((int(match.group(2), 16), int(match.group(3), 16), source, match.group(1)))

a, b = original.read_bytes(), built.read_bytes()
print(f"sizes: original {len(a):#x}, built {len(b):#x}")
ranges = []
index = 0
while index < min(len(a), len(b)):
    if a[index] != b[index]:
        start = index
        while index < min(len(a), len(b)) and (a[index] != b[index] or a[index:index + 8] != b[index:index + 8]):
            index += 1
        ranges.append((start, index))
    index += 1
for start, end in ranges[:30]:
    address = base + start
    owner = next((f"{s} {sec}" for lo, hi, s, sec in units if lo <= address < hi), "(not decompiled)")
    print(f"0x{address:08x}..0x{base + end:08x} {owner}: {a[start:end].hex()[:32]} -> {b[start:end].hex()[:32]}")
print(f"{len(ranges)} differing ranges")
