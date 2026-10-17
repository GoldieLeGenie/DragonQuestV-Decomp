#!/usr/bin/env python3
"""Brings over DQ IV decomp source files whose whole content is in this game.

For each source file (translation unit) of the DQ IV decomp, its sections are
placed in this game from the functions and data matched by dq4_match.py
(mobile/dq4_pairs.txt): every matched symbol of a section must give the same
address shift, the code sections must have all their functions matched, and the
section bytes must be identical once relocated words are masked. A unit passing
all checks gets its delinks.txt entry here and its source file copied.

usage: port_dq4_units.py PATH_TO_DQIVDECOMP [--filter REGEX] [--dry] [--version eur]
"""

import argparse
import bisect
import re
import shutil
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from dq4_match_lib import Project, module_of  # noqa: E402

parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("dq4", type=Path)
parser.add_argument("--filter", default=r"^libs/", help="Regex on DQ IV source paths to consider")
parser.add_argument("--exclude", help="Regex on DQ IV source paths to leave out (e.g. a unit emitting its own copy "
                    "of an inline function this game still has in undecompiled code)")
parser.add_argument("--pairs", type=Path, default=Path("mobile/dq4_pairs.txt"))
parser.add_argument("--version", default="eur")
parser.add_argument("--dry", action="store_true")
args = parser.parse_args()

dq5 = Project(Path("."), args.version)
dq4 = Project(args.dq4, args.version)

shift_of = {}       # DQ4 key -> DQ5 key
for line in args.pairs.read_text().splitlines():
    kind, module5, address5, module4, address4 = line.split()
    shift_of[(module4, int(address4, 16))] = (module5, int(address5, 16))

# DQ IV overlays and this game's are numbered differently (DQ IV's town is
# ov000, here ov001): the matched functions tell which is which, and files go
# under this game's numbers (src/ov001/town/..., include/ov001/town/...).
overlay_votes = defaultdict(lambda: defaultdict(int))
for (module4, _), (module5, _) in shift_of.items():
    overlay_votes[module4][module5] += 1
overlay_map = {module4: max(votes, key=votes.get) for module4, votes in overlay_votes.items()}
overlay_dir_re = re.compile(r"^(src/|include/)?(ov\d{3})(/.*)$")


def translate(path: str) -> str:
    match = overlay_dir_re.match(path)
    if not match or match.group(2) not in overlay_map:
        return path
    return f"{match.group(1) or ''}{overlay_map[match.group(2)]}{match.group(3)}"


unit_re = re.compile(r"^(\S.*):\s*$")
section_re = re.compile(r"^\s+(\.\w+)\s+start:0x([0-9a-f]+) end:0x([0-9a-f]+)")


def units_of(project):
    """source -> (module, [(section, start, end)]) from every delinks.txt."""
    result = {}
    for module, (_, _, folder) in project.modules.items():
        source = None
        for line in (folder / "delinks.txt").read_text().splitlines():
            match = unit_re.match(line)
            if match:
                source = match.group(1)
                result[source] = (module, [])
                continue
            match = section_re.match(line)
            if match and source:
                result[source][1].append((match.group(1), int(match.group(2), 16), int(match.group(3), 16)))
    return result


dq4_units = units_of(dq4)
dq5_units = units_of(dq5)
claimed = defaultdict(list)          # DQ5 module -> [(start, end)]
for module, sections in dq5_units.values():
    for _, start, end in sections:
        claimed[module].append((start, end))

module_sections5 = {}
for module, (_, _, folder) in dq5.modules.items():
    module_sections5[module] = []
    for line in (folder / "delinks.txt").read_text().splitlines():
        if unit_re.match(line):
            break
        match = section_re.match(line)
        if match:
            module_sections5[module].append((match.group(1), int(match.group(2), 16), int(match.group(3), 16)))


def masked(project, module, start, end):
    base, image, _ = project.modules[module]
    if not (base <= start <= end <= base + len(image)):
        return None
    raw = bytearray(image[start - base:end - base])
    relocs = project.relocs[module]
    index = bisect.bisect_left(relocs, (start,))
    while index < len(relocs) and relocs[index][0] < end:
        offset = relocs[index][0] - start
        raw[offset:offset + 4] = b"\0\0\0\0"
        index += 1
    return bytes(raw)


def reloc_at(project, module, source):
    relocs = project.relocs[module]
    index = bisect.bisect_left(relocs, (source,))
    if index < len(relocs) and relocs[index][0] == source:
        return relocs[index]
    return None


def place(module4, section, start4, end4, placed):
    """The DQ5 (module, start, end) of a DQ4 section, or a reason it cannot be placed.

    Candidate shifts come from the matched symbols in the section, and from the
    unit's sections already placed: their relocations into this section line up
    with this game's. The most supported candidate whose whole section has
    identical bytes (relocated words masked) is taken: a wrong match elsewhere
    cannot pass, and the bytes vouch for functions too small to match alone.
    """
    if start4 == end4:
        return "empty"
    support = defaultdict(int)
    for (m, address), target in shift_of.items():
        if m == module4 and start4 <= (address & ~1) < end4:
            support[(target[0], (target[1] & ~1) - (address & ~1))] += 1
    for _, (start, end), (module5, start5, _) in placed:
        relocs = dq4.relocs[module4]
        index = bisect.bisect_left(relocs, (start,))
        while index < len(relocs) and relocs[index][0] < end:
            source4, _, target4, target_module4 = relocs[index]
            index += 1
            # Full addresses: symbol plus addend (a vtable pointer is &vtable + 8).
            full4 = target4 + dq4.addends.get((module4, source4), 0)
            if module_of(target_module4) != module4 or not (start4 <= full4 < end4):
                continue
            source5 = start5 + (source4 - start)
            mirror = reloc_at(dq5, module5, source5)
            if mirror and module_of(mirror[3]) is not None:
                full5 = mirror[2] + dq5.addends.get((module5, source5), 0)
                support[(module_of(mirror[3]), full5 - full4)] += 1
    # Static initializers are referenced only by the .ctor table: the .init
    # code is looked for by its bytes, the .ctor entry by its pointer to it.
    if not support and section == ".init":
        wanted = masked(dq4, module4, start4, end4)
        found = []
        for module5, sections5 in module_sections5.items():
            for name5, low, high in sections5:
                if name5 != ".init":
                    continue
                for start5 in range(low, high - len(wanted) + 1, 2):
                    if masked(dq5, module5, start5, start5 + len(wanted)) == wanted:
                        found.append((module5, start5 - start4))
        # Initializers look alike (constructor call, destructor registered):
        # the one calling into the unit's placed code is the unit's.

        def calls_into_unit(candidate):
            module5, shift = candidate
            count = 0
            relocs = dq4.relocs[module4]
            index = bisect.bisect_left(relocs, (start4,))
            while index < len(relocs) and relocs[index][0] < end4:
                source4, _, target4, target_module4 = relocs[index]
                index += 1
                for _, (low, high), (placed_module, placed_start, _) in placed:
                    if module_of(target_module4) == module4 and low <= (target4 & ~1) < high:
                        mirror = reloc_at(dq5, module5, source4 + shift)
                        if mirror and (mirror[2] & ~1) == placed_start + ((target4 & ~1) - low):
                            count += 1
            return count

        if len(found) > 1:
            scored = sorted(((calls_into_unit(c), c) for c in found), reverse=True)
            if scored[0][0] > 0 and (len(scored) == 1 or scored[1][0] < scored[0][0]):
                found = [scored[0][1]]
        if len(found) == 1:
            support[found[0]] += 1
    if not support and section == ".ctor":
        for name, _, (module5, init5, _) in placed:
            if name != ".init":
                continue
            for source5, _, target5, target_module5 in dq5.relocs[module5]:
                if (target5 & ~1) == init5 and module_of(target_module5) == module5 and any(
                        s[0] == ".ctor" and s[1] <= source5 < s[2] for s in module_sections5.get(module5, [])):
                    support[(module5, source5 - start4)] += 1
    if not support:
        return "nothing matched"
    reasons = []
    for (module5, shift), _ in sorted(support.items(), key=lambda item: -item[1]):
        start5, end5 = start4 + shift, end4 + shift
        if not any(s[0] == section and s[1] <= start5 and end5 <= s[2] for s in module_sections5.get(module5, [])):
            reasons.append(f"outside {module5} {section}")
            continue
        if section != ".bss" and masked(dq4, module4, start4, end4) != masked(dq5, module5, start5, end5):
            reasons.append("different bytes")
            continue
        if any(start < end5 and start5 < end for start, end in claimed[module5]):
            reasons.append("overlaps a unit")
            continue
        return (module5, start5, end5)
    return reasons[0]


# Masked bytes cannot tell a call or pointer to another function: the targets
# must line up too. Each DQ IV symbol a unit refers to stands for one address
# here, and two DQ IV symbols never for the same one (here, a class whose
# virtual functions were reordered would point a vtable at other methods).
target_4to5 = {}
target_5to4 = {}


def check_targets(module4, placed):
    found_4to5, found_5to4 = {}, {}
    for section, (start4, end4), (module5, start5, _) in placed:
        relocs = dq4.relocs[module4]
        index = bisect.bisect_left(relocs, (start4,))
        while index < len(relocs) and relocs[index][0] < end4:
            source4, _, target4, target_module4 = relocs[index]
            index += 1
            mirror = reloc_at(dq5, module5, start5 + (source4 - start4))
            if not mirror:
                return f"{section}: relocation 0x{source4:08x} has no counterpart"
            base4 = (module_of(target_module4) or target_module4, target4 & ~1)
            base5 = (module_of(mirror[3]) or mirror[3],
                     (mirror[2] + dq5.addends.get((module5, mirror[0]), 0) - dq4.addends.get((module4, source4), 0)) & ~1)
            for table, key, value in ((found_4to5, base4, base5), (found_5to4, base5, base4),
                                      (target_4to5, base4, base5), (target_5to4, base5, base4)):
                if table.get(key, value) != value:
                    name = dq4.symbols.get(base4, f"0x{base4[1]:08x}")
                    return f"{section}: targets differ ({name})"
            found_4to5[base4] = base5
            found_5to4[base5] = base4
    target_4to5.update(found_4to5)
    target_5to4.update(found_5to4)
    return None


ported = defaultdict(list)
report = []
pattern = re.compile(args.filter)
for source, (module4, sections) in sorted(dq4_units.items()):
    if not pattern.search(source) or translate(source) in dq5_units or (args.exclude and re.search(args.exclude, source)):
        continue
    placed = []         # (section, DQ4 range, DQ5 place)
    reason = None
    # Code first: its relocations then place the unit's data.
    for section, start4, end4 in sorted(sections, key=lambda s: s[0] not in (".text", ".init")):
        result = place(module4, section, start4, end4, placed)
        if result == "empty":
            continue
        if isinstance(result, str):
            reason = f"{section}: {result}"
            break
        placed.append((section, (start4, end4), result))
    modules5 = {p[2][0] for p in placed}
    if reason is None and len(modules5) != 1:
        reason = "no section placed" if not modules5 else f"spread over {modules5}"
    if reason is None:
        reason = check_targets(module4, placed)
    if reason:
        report.append(f"skip {source}: {reason}")
        continue
    module5 = modules5.pop()
    ported[module5].append((source, module4, placed))
    for _, _, (_, start5, end5) in placed:
        claimed[module5].append((start5, end5))
    report.append(f"port {source} -> {module5}")

print("\n".join(report))
print(f"{sum(len(v) for v in ported.values())} units ported, {sum(1 for r in report if r.startswith('skip'))} skipped")
if args.dry:
    sys.exit(0)

# Symbols: inside each placed range, this game's symbols give way to the DQ IV
# unit's, at their new addresses. Address-based placeholder names (func_xxx,
# data_xxx, unk_xxx...) are renamed after the new address, in the copied
# sources and headers too; real names stay.
placeholder_re = re.compile(r"^(func|data|unk|unkfunc|_?unk_data)_(ov\d{3}_)?([0-9a-f]{8})(.*)$")
address_re = re.compile(r"addr:0x([0-9a-f]+)")


def module_prefix(module):
    return "" if module == "main" else f"{module}_"


def symbol_lines(project, module):
    return (project.modules[module][2] / "symbols.txt").read_bytes().decode().splitlines()


renames = {}
symbol_edits = defaultdict(lambda: {"remove": [], "add": [], "added": set(), "local": set(), "ends": []})
for module5, units in ported.items():
    for source, module4, placed in units:
        for section, (start4, end4), (_, start5, end5) in placed:
            shift = start5 - start4
            symbol_edits[module5]["remove"].append((start5, end5))
            for line in symbol_lines(dq4, module4):
                match = address_re.search(line)
                if not match or not (start4 <= int(match.group(1), 16) < end4):
                    continue
                # Zero-size symbols are labels the DQ IV linker script defines
                # (addresses the SDK's BuildInfo points to), not unit symbols.
                if "(size=0x0)" in line:
                    continue
                address4 = int(match.group(1), 16)
                address5 = address4 + shift
                name, rest = line.split(" ", 1)
                placeholder = placeholder_re.match(name)
                if placeholder and int(placeholder.group(3), 16) == address4 & ~1:
                    new = f"{placeholder.group(1)}_{module_prefix(module5)}{address5 & ~1:08x}{placeholder.group(4)}"
                    if new != name:
                        renames[name] = new
                    name = new
                symbol_edits[module5]["add"].append(f"{name} {address_re.sub(f'addr:0x{address5:08x}', rest)}")
                symbol_edits[module5]["added"].add(address5 & ~1)
                if " local" in rest:
                    symbol_edits[module5]["local"].add(address5 & ~1)
            # A data symbol without a size runs to the next symbol: one starts
            # where the section ends, so the unit's last one stops there.
            if section not in (".text", ".init"):
                kind = "bss" if section == ".bss" else "data(any)"
                symbol_edits[module5]["ends"].append((end5, kind))

# Symbols outside the ported units that their code refers to: the ported
# sources use DQ IV's names. The relocations line up (identical bytes), so each
# DQ IV target has its counterpart here: a real name is given to it, a DQ IV
# placeholder becomes this game's placeholder (in the sources too).
external = {}       # (module5, address5) -> name it must have here
external_kind = {}  # (module5, address5) -> dsd kind, should a symbol be added
dq4_kinds = {}
for module4 in dq4.modules:
    for line in symbol_lines(dq4, module4):
        match = address_re.search(line)
        if match and " kind:" in line:
            dq4_kinds[(module4, int(match.group(1), 16) & ~1)] = line.split(" kind:", 1)[1].split(" ", 1)[0]


def dq4_kind(key):
    return dq4_kinds.get(key, "data(any)")
merged = defaultdict(list)   # module5 -> [(start, end)]: one DQ IV symbol, split here
conflicts = []
# Where each DQ IV symbol ends (the next symbol), for symbols referred to with
# an addend: DQ IV knows one variable where dsd split this game's into pieces.
dq4_starts = defaultdict(list)
for (module, address) in dq4.symbols:
    dq4_starts[module].append(address)
for module in dq4_starts:
    dq4_starts[module].sort()


def dq4_extent(module, address):
    starts = dq4_starts[module]
    index = bisect.bisect_right(starts, address)
    return starts[index] - address if index < len(starts) else 4
ported_ranges4 = defaultdict(list)
for module5, units in ported.items():
    for source, module4, placed in units:
        for section, (start4, end4), _ in placed:
            ported_ranges4[module4].append((start4, end4))
for module5, units in ported.items():
    for source, module4, placed in units:
        for section, (start4, end4), (_, start5, end5) in placed:
            relocs = dq4.relocs[module4]
            index = bisect.bisect_left(relocs, (start4,))
            while index < len(relocs) and relocs[index][0] < end4:
                source4, _, target4, target_module4 = relocs[index]
                index += 1
                t4 = (module_of(target_module4), target4 & ~1)
                if t4[0] is None or any(s <= t4[1] < e for s, e in ported_ranges4.get(t4[0], [])):
                    continue
                source5 = start5 + (source4 - start4)
                mirror = reloc_at(dq5, module5, source5)
                if not mirror or module_of(mirror[3]) is None:
                    continue
                # The DQ IV symbol's start here: this game's target and addend,
                # less the DQ IV addend.
                base5 = mirror[2] + dq5.addends.get((module5, source5), 0) - dq4.addends.get((module4, source4), 0)
                t5 = (module_of(mirror[3]), base5 & ~1)
                name4 = dq4.symbols.get(t4) or dq4.symbols.get((t4[0], t4[1] | 1))
                if not name4:
                    continue
                if dq4.addends.get((module4, source4)) and t4 not in dq4.functions:
                    merged[t5[0]].append((t5[1], t5[1] + dq4_extent(t4[0], t4[1])))
                placeholder = placeholder_re.match(name4)
                if placeholder:
                    wanted = f"{placeholder.group(1)}_{module_prefix(t5[0])}{t5[1]:08x}{placeholder.group(4)}"
                    if wanted != name4:
                        renames[name4] = wanted
                else:
                    wanted = name4
                external_kind[t5] = "bss" if dq4_kind(t4).startswith("bss") else "data(any)"
                if external.setdefault(t5, wanted) != wanted:
                    conflicts.append(f"{t5[0]} 0x{t5[1]:08x}: {external[t5]} / {wanted}")

for module, (_, _, folder) in dq5.modules.items():
    path = folder / "symbols.txt"
    lines = path.read_bytes().decode().splitlines()
    changed = False
    # The pieces of a merged variable go: references to them become the
    # variable's symbol plus an addend (relocations, below).
    pieces = [line for line in lines if (m := address_re.search(line)) and
              any(start < int(m.group(1), 16) < end for start, end in merged.get(module, []))]
    if pieces:
        lines = [line for line in lines if line not in pieces]
        changed = True
    for index, line in enumerate(lines):
        match = address_re.search(line)
        if not match:
            continue
        wanted = external.get((module, int(match.group(1), 16) & ~1))
        name = line.split(" ", 1)[0]
        if wanted and wanted != name:
            if placeholder_re.match(name):
                lines[index] = wanted + " " + line.split(" ", 1)[1]
                changed = True
            else:
                conflicts.append(f"{module} {name} already named, sources want {wanted}")
    # A referenced variable dsd never started a symbol at (it split it at
    # other offsets) gets one, with the DQ IV symbol's kind.
    present = {int(m.group(1), 16) & ~1 for m in map(address_re.search, lines) if m}
    for (target_module, address), wanted in external.items():
        if target_module == module and address not in present:
            kind = external_kind.get((module, address), "data(any)")
            lines.append(f"{wanted} kind:{kind} addr:0x{address:08x}")
            changed = True
    if changed:
        path.write_bytes(("\n".join(lines) + "\n").encode())

# This game's own symbols inside a placed range normally give way. One that
# code outside the unit points to, with no DQ IV symbol at its address, stays
# as a zero-size label: the linker script has to define it (reported below).
outside_targets = set()
for module, (_, _, folder) in dq5.modules.items():
    for source, kind, target, target_module in dq5.relocs[module]:
        inside = any(start <= source < end for start, end in symbol_edits.get(module, {}).get("remove", []))
        if not inside and module_of(target_module):
            outside_targets.add((module_of(target_module), target & ~1))
labels = []
for module5, edits in symbol_edits.items():
    path = dq5.modules[module5][2] / "symbols.txt"
    kept = []
    for line in path.read_bytes().decode().splitlines():
        match = address_re.search(line)
        if match and any(start <= int(match.group(1), 16) < end for start, end in edits["remove"]):
            address = int(match.group(1), 16) & ~1
            # Pointing inside a global symbol of the unit, the reference becomes
            # that symbol plus an addend (relocations, below); inside a local
            # one it cannot, so a label stays.
            covering = max((a for a in edits["added"] if a <= address), default=None)
            if ((module5, address) in outside_targets and address not in edits["added"]
                    and covering is not None and covering in edits["local"]):
                name, rest = line.split(" ", 1)
                kind = rest.split(" ", 1)[0].split("(", 1)[0]
                if kind == "kind:bss":
                    kept.append(f"{name} {kind}(size=0x0) addr:0x{address:08x}")
                    labels.append(f"{module5} {name}")
                else:
                    conflicts.append(f"{module5} {name}: points inside local data, cannot be kept")
            continue
        kept.append(line)
    starts = edits["added"] | {int(m.group(1), 16) & ~1 for m in map(address_re.search, kept) if m}
    for end, kind in edits["ends"]:
        if end not in starts:
            kept.append(f"data_{module_prefix(module5)}{end:08x} kind:{kind} addr:0x{end:08x}")
            starts.add(end)
    # Bytes out: text mode would change the file's line endings on Windows.
    path.write_bytes(("\n".join(kept + edits["add"]) + "\n").encode())

# Relocations into the placed ranges that pointed at this game's own symbols
# now refer to the DQ IV unit's: those landing inside a symbol become that
# symbol plus an addend.
symbol_starts = defaultdict(set)
for module5 in dq5.modules:
    for line in symbol_lines(dq5, module5):
        match = address_re.search(line)
        if match:
            symbol_starts[module5].add(int(match.group(1), 16) & ~1)
reloc_line_re = re.compile(r"^(\s*from:0x[0-9a-f]+ kind:\w+ )to:0x([0-9a-f]+)(?: add:(-?0x[0-9a-f]+))?( module:(\S+).*)$")
for module, (_, _, folder) in dq5.modules.items():
    path = folder / "relocs.txt"
    if not path.is_file():
        continue
    lines = path.read_bytes().decode().splitlines()
    changed = False
    for index, line in enumerate(lines):
        match = reloc_line_re.match(line)
        if not match:
            continue
        head, target, addend, tail, target_module = match.groups()
        target = int(target, 16)

        def lost(module5):
            """A symbol at the target went with a placed range."""
            ranges = symbol_edits.get(module5, {}).get("remove", []) + merged.get(module5, [])
            return any(start <= target < end for start, end in ranges) and (target & ~1) not in symbol_starts[module5]

        # Ambiguous target (overlays sharing the address): the candidates that
        # lost their symbol there drop out; the address is the same either way.
        candidates = re.match(r"overlays\(([\d,]+)\)", target_module)
        if candidates:
            numbers = [int(n) for n in candidates.group(1).split(",")]
            keep = [n for n in numbers if not lost(f"ov{n:03d}")]
            if keep and len(keep) < len(numbers):
                module_text = f"overlay({keep[0]})" if len(keep) == 1 else f"overlays({','.join(map(str, keep))})"
                lines[index] = line.replace(f"module:{target_module}", f"module:{module_text}")
                changed = True
            continue
        module5 = module_of(target_module)
        ranges = symbol_edits.get(module5, {}).get("remove", []) + merged.get(module5, [])
        if not any(start <= target < end for start, end in ranges) or (target & ~1) in symbol_starts[module5]:  # Thumb code addresses are odd
            continue
        below = max((s for s in symbol_starts[module5] if s <= target), default=None)
        if below is None:
            continue
        total = target - below + (int(addend, 16) if addend else 0)
        lines[index] = f"{head}to:0x{below:08x} add:{total:#x}{tail}"
        changed = True
    if changed:
        path.write_bytes(("\n".join(lines) + "\n").encode())

include_re = re.compile(r'^(\s*#\s*include\s+")([^"]+)(")', re.M)
lib_includes = [p for p in (args.dq4 / "libs").glob("*/include")]


def copy_source(source4: Path, target: Path):
    """Copies a DQ IV file, its #include paths translated, with the DQ IV game
    headers it needs (recursively, under their translated paths)."""
    text = source4.read_bytes().decode("utf-8", errors="surrogateescape")

    def include(match):
        name = match.group(2)
        local = source4.parent / name
        header = args.dq4 / "include" / name
        if not local.is_file() and header.is_file():
            destination = Path("include") / translate(name)
            if not destination.exists() and destination not in started:
                started.add(destination)     # headers including each other
                copy_source(header, destination)
            return f"{match.group(1)}{translate(name)}{match.group(3)}"
        return match.group(0)

    text = include_re.sub(include, text)
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(text.encode("utf-8", errors="surrogateescape"))
    copied.append(target)


copied = []
started = set()
for module5, units in ported.items():
    folder = dq5.modules[module5][2]
    with (folder / "delinks.txt").open("a", encoding="utf-8", newline="\n") as out:
        for source, _, placed in units:
            out.write(f"\n{translate(source)}:\n    complete\n")
            for section, _, (_, start5, end5) in sorted(placed, key=lambda p: p[2][1]):
                out.write(f"    {section} start:0x{start5:08x} end:0x{end5:08x}\n")
            target = Path(translate(source))
            copy_source(args.dq4 / source, target)
            # Private headers of the library (libs/<library>/src/..., e.g.
            # sdk_internal.h, msl_fp_internal.h), or of the source's folder.
            parts = Path(source).parts
            private = Path(*parts[:3]) if parts[0] == "libs" and len(parts) > 3 else Path(source).parent
            for header in (args.dq4 / private).rglob("*"):
                if header.suffix in (".h", ".hpp"):
                    destination = header.relative_to(args.dq4)
                    if not destination.exists():
                        destination.parent.mkdir(parents=True, exist_ok=True)
                        shutil.copyfile(header, destination)
                        copied.append(destination)

# Placeholders of every matched DQ IV symbol: files copied now may use names
# that earlier runs already moved in this game's sources (VEC_Subtract's
# declaration, renamed when the libraries came over).
known_renames = {}
for (module4, address4), (module5, address5) in shift_of.items():
    name4 = dq4.symbols.get((module4, address4)) or dq4.symbols.get((module4, address4 & ~1))
    placeholder = placeholder_re.match(name4 or "")
    if placeholder and int(placeholder.group(3), 16) == address4 & ~1:
        known_renames[name4] = f"{placeholder.group(1)}_{module_prefix(module5)}{address5 & ~1:08x}{placeholder.group(4)}"
known_renames.update(renames)


def rename_in(paths, table):
    if not table:
        return
    word = re.compile(r"\b(" + "|".join(map(re.escape, sorted(table, key=len, reverse=True))) + r")\b")
    for path in paths:
        text = path.read_bytes().decode("utf-8", errors="surrogateescape")
        new = word.sub(lambda m: table[m.group(1)], text)
        if new != text:
            path.write_bytes(new.encode("utf-8", errors="surrogateescape"))


rename_in(set(copied), known_renames)
rename_in({p for root in (Path("include"), Path("libs"), Path("src")) if root.is_dir()
           for p in root.rglob("*") if p.suffix in (".h", ".hpp", ".c", ".cpp", ".s", ".inc")} - set(copied), renames)
print(f"{len(renames)} placeholder names moved to this game's addresses")
for label in labels:
    print(f"define in the linker script (tools/configure.py, generate_lcf): {label}")
for conflict in conflicts:
    print(f"name conflict: {conflict}")
