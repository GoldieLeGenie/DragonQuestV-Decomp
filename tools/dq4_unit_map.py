#!/usr/bin/env python3
"""Shows where a DQ IV decomp source file's functions are in this game.

For each function of the DQ IV unit (in its order): its counterpart here (from
mobile/dq4_pairs.txt), the shift, and how it was found; then the functions of
this game lying between the matched ones, which the unit here probably holds
too (new or changed functions to decompile).

usage: dq4_unit_map.py PATH_TO_DQIVDECOMP SOURCE [--version eur]
"""

import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from dq4_match_lib import Project  # noqa: E402

parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("dq4", type=Path)
parser.add_argument("source")
parser.add_argument("--pairs", type=Path, default=Path("mobile/dq4_pairs.txt"))
parser.add_argument("--version", default="eur")
args = parser.parse_args()

dq4 = Project(args.dq4, args.version)
dq5 = Project(Path("."), args.version)
pairs = {}
for line in args.pairs.read_text().splitlines():
    kind, module5, address5, module4, address4 = line.split()
    if kind == "F":
        pairs[(module4, int(address4, 16))] = (module5, int(address5, 16))

ranges = []
for module, units in dq4.units.items():
    for start, end, source in units:
        if source == args.source:
            ranges.append((module, start, end))
if not ranges:
    sys.exit(f"{args.source} has no .text in the DQ IV decomp")

matched5 = []
for module4, start4, end4 in ranges:
    print(f"DQ IV {module4} .text 0x{start4:08x}..0x{end4:08x}")
    for key in sorted(k for k in dq4.functions if k[0] == module4 and start4 <= k[1] < end4):
        name, size, thumb = dq4.functions[key]
        target = pairs.get(key)
        where = f"{target[0]} 0x{target[1]:08x} (shift {target[1] - key[1]:+#x})" if target else "-"
        print(f"  0x{key[1]:08x} {size:#6x} {'T' if thumb else 'A'} {name:60s} -> {where}")
        if target:
            matched5.append(target)

if matched5:
    module5 = max(set(m for m, _ in matched5), key=[m for m, _ in matched5].count)
    addresses = sorted(a for m, a in matched5 if m == module5)
    low, high = addresses[0], addresses[-1]
    print(f"\nThis game, {module5} 0x{low:08x}..: functions between the matched ones")
    matched = set(matched5)
    for key in sorted(k for k in dq5.functions if k[0] == module5 and low <= k[1] <= high):
        name, size, thumb = dq5.functions[key]
        print(f"  0x{key[1]:08x} {size:#6x} {'T' if thumb else 'A'} {name:60s} {'matched' if key in matched else 'NEW/CHANGED'}")
