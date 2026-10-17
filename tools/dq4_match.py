#!/usr/bin/env python3
"""Finds the functions this game shares with the Dragon Quest IV decomp.

Dragon Quest IV and V on DS share their engine (dss, menus, text, the Nitro SDK
and NitroSystem, MSL), built by the same team with the same tools. A function
whose bytes are identical once addresses are masked out (calls, pointers and
literal words, from dsd's relocations) is the same function: it takes the name
the DQ IV decomp gives it, and the DQ IV source file it comes from can be reused.
Its relocations then line up one to one, which names the functions and data it
refers to as well, even where their own code differs.

Outputs (in the output directory):
  dq4_functions.txt  DQ V function -> DQ IV name, DQ IV source file, how found
  dq4_data.txt       DQ V data symbol -> DQ IV name (through matched relocations)
  dq4_units.txt      DQ IV source files with how many of their functions match

usage: dq4_match.py PATH_TO_DQIVDECOMP [--version eur] [-o mobile]
"""

import argparse
import bisect
import hashlib
from collections import defaultdict
from pathlib import Path

from dq4_match_lib import Project, module_of

parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("dq4", type=Path, help="DQ IV decomp checkout (with extract/<version>)")
parser.add_argument("--version", default="eur")
parser.add_argument("-o", "--output", type=Path, default=Path("mobile"))
args = parser.parse_args()


dq5 = Project(Path("."), args.version)
dq4 = Project(args.dq4, args.version)
dq4_starts = defaultdict(list)
for module, address in sorted(dq4.symbols):
    dq4_starts[module].append(address)


def digest(project, key):
    raw, relocs = project.body(key)
    _, size, thumb = project.functions[key]
    kinds = tuple(kind for kind, _, _ in relocs)
    return hashlib.sha1(raw + repr((size, thumb, kinds)).encode()).hexdigest()


# Small functions have generic shapes (a getter returning some global), so a
# body only identifies its function when it is long enough and unique on both
# sides; smaller ones are found through their callers.
MINIMUM_SIZE = 0x18
dq4_by_hash = defaultdict(list)
for key, (_, size, _) in dq4.functions.items():
    if size >= MINIMUM_SIZE:
        dq4_by_hash[digest(dq4, key)].append(key)
dq5_by_hash = defaultdict(list)
for key, (_, size, _) in dq5.functions.items():
    if size >= MINIMUM_SIZE:
        dq5_by_hash[digest(dq5, key)].append(key)

names = {}          # DQ5 key -> (DQ4 name, DQ4 unit, how)
used = {}           # DQ4 key -> DQ5 key: one function each way
data_names = {}
data_source = {}    # DQ5 data key -> DQ4 data key
pending = []
for digest_value, keys5 in dq5_by_hash.items():
    keys4 = dq4_by_hash.get(digest_value, [])
    if len(keys5) == 1 and len(keys4) == 1:
        key, source = keys5[0], keys4[0]
        names[key] = (dq4.functions[source][0], dq4.unit_of(source), "same bytes")
        used[source] = key
        pending.append((key, source))


def target_key(project, target, target_module):
    module = module_of(target_module)
    if module is None:
        return None
    return (module, target)


# Matched functions: their relocations line up and name their targets.
while pending:
    key5, key4 = pending.pop()
    _, relocs5 = dq5.body(key5)
    _, relocs4 = dq4.body(key4)
    for (kind5, target5, module5), (kind4, target4, module4) in zip(relocs5, relocs4):
        t5 = target_key(dq5, target5, module5)
        t4 = target_key(dq4, target4, module4)
        if t5 is None or t4 is None:
            continue
        callee5 = (t5[0], t5[1] & ~1)
        callee4 = (t4[0], t4[1] & ~1)
        if kind5.endswith("call") or "_call_" in kind5:
            if callee5 in dq5.functions and callee4 in dq4.functions and callee5 not in names and callee4 not in used:
                names[callee5] = (dq4.functions[callee4][0], dq4.unit_of(callee4), f"called by {dq4.functions[key4][0]}")
                used[callee4] = callee5
                pending.append((callee5, callee4))
        else:
            # Full addresses (symbol plus addend, e.g. a vtable pointer is
            # &vtable + 8): the DQ IV symbol holding the target, and the
            # address its start has here.
            starts = dq4_starts[t4[0]]
            index = bisect.bisect_right(starts, t4[1]) - 1
            if index < 0:
                continue
            start4 = (t4[0], starts[index])
            start5 = (t5[0], t5[1] - (t4[1] - starts[index]))
            if start5 not in data_names and start5 not in dq5.functions and start4 not in dq4.functions:
                data_names[start5] = dq4.symbols[start4]
                data_source[start5] = start4

args.output.mkdir(exist_ok=True)
with (args.output / "dq4_functions.txt").open("w", encoding="utf-8") as out:
    for key in sorted(names, key=lambda k: (k[0] != "main", k[0], k[1])):
        name, unit, how = names[key]
        out.write(f"{key[0]} 0x{key[1]:08x} {dq5.functions[key][0]} -> {name}  [{unit}]  ({how})\n")
with (args.output / "dq4_data.txt").open("w", encoding="utf-8") as out:
    for key in sorted(data_names, key=lambda k: (k[0] != "main", k[0], k[1])):
        out.write(f"{key[0]} 0x{key[1]:08x} {dq5.symbols.get(key, '?')} -> {data_names[key]}\n")
# Machine-readable pairs (kind, DQ V module and address, DQ IV module and address)
# for tools that bring DQ IV source files over.
with (args.output / "dq4_pairs.txt").open("w", encoding="utf-8") as out:
    for key4, key5 in sorted(used.items(), key=lambda item: (item[1][0], item[1][1])):
        out.write(f"F {key5[0]} 0x{key5[1]:08x} {key4[0]} 0x{key4[1]:08x}\n")
    for key5, key4 in sorted(data_source.items()):
        out.write(f"D {key5[0]} 0x{key5[1]:08x} {key4[0]} 0x{key4[1]:08x}\n")

# DQ IV source files: how many of their functions are found in DQ V.
unit_total = defaultdict(int)
for key in dq4.functions:
    unit_total[dq4.unit_of(key)] += 1
unit_found = defaultdict(int)
for name, unit, _ in names.values():
    unit_found[unit] += 1
with (args.output / "dq4_units.txt").open("w", encoding="utf-8") as out:
    for unit in sorted(unit_found, key=lambda u: (-unit_found[u] / max(unit_total[u], 1), str(u))):
        out.write(f"{unit_found[unit]:4d}/{unit_total[unit]:<4d} {unit}\n")
exact = sum(1 for n in names.values() if n[2] == "same bytes")
print(f"DQ V functions {len(dq5.functions)}: {exact} identical to DQ IV, {len(names) - exact} more through their callers; data {len(data_names)}")
