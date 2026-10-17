#!/usr/bin/env python3
"""Compares a DQ IV decomp source file's functions with this game's, one by one.

The unit's place here comes from its matched functions (the most common shift,
mobile/dq4_pairs.txt). Each DQ IV function is compared with the bytes at the
same offset here, relocated words masked: the ones that differ are those to
decompile again (or to adapt) for this game.

usage: dq4_unit_diff.py PATH_TO_DQIVDECOMP SOURCE [--version eur]
"""

import argparse
import bisect
import sys
from collections import Counter
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
    pairs[(module4, int(address4, 16))] = (module5, int(address5, 16))


def masked(project, module, start, end):
    base, image, _ = project.modules[module]
    raw = bytearray(image[start - base:end - base])
    relocs = project.relocs[module]
    index = bisect.bisect_left(relocs, (start,))
    while index < len(relocs) and relocs[index][0] < end:
        offset = relocs[index][0] - start
        raw[offset:offset + 4] = b"\0\0\0\0"
        index += 1
    return bytes(raw)


for module4, units in dq4.units.items():
    for start4, end4, source in units:
        if source != args.source:
            continue
        functions = sorted(k for k in dq4.functions if k[0] == module4 and start4 <= k[1] < end4)
        shifts = Counter((pairs[k][0], pairs[k][1] - k[1]) for k in functions if k in pairs)
        if not shifts:
            print(f"{source}: no matched function")
            continue
        (module5, shift), _ = shifts.most_common(1)[0]
        print(f"{source} .text 0x{start4:08x}..0x{end4:08x} -> {module5} 0x{start4 + shift:08x} (shift {shift:+#x})")
        same = 0
        for key in functions:
            name, size, _ = dq4.functions[key]
            a = masked(dq4, module4, key[1] & ~1, (key[1] & ~1) + size)
            b = masked(dq5, module5, (key[1] & ~1) + shift, (key[1] & ~1) + shift + size)
            if a == b:
                same += 1
                continue
            first = next(i for i in range(min(len(a), len(b))) if a[i] != b[i]) if a[:len(b)] != b[:len(a)] else min(len(a), len(b))
            print(f"  DIFFERS 0x{key[1]:08x} -> 0x{key[1] + shift:08x} {name} (size {size:#x}, first difference at +{first:#x})")
            print(f"     DQ IV: {a[first:first + 16].hex()}")
            print(f"     here : {b[first:first + 16].hex()}")
        print(f"  {same}/{len(functions)} functions identical")
