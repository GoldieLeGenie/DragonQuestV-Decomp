#!/usr/bin/env python3
"""Names this game's symbols after a decompiled (or adapted) source file.

Builds the source's object and the delinked original (its delinks.txt entry
must exist), then:
- with --own, renames the unit's functions in symbols.txt after the source's,
  in address order (both must have the same number of functions);
- pairs each function's relocations with the original's (same name, same
  relocation offsets, or else same count and kinds) and names the targets:
  a placeholder name of the source (unkfunc_XXXXXXXX, func_..., data_... with
  another address, e.g. DQ IV's) is moved to the target's address here, in
  symbols.txt and in the sources and headers; a real name is given to the
  target's symbol when it has dsd's automatic name.

Run `dsd format`-free: only names change. Then build again (ninja check).

usage: sync_names.py SOURCE [--own [--skip NAME]] [--dry] [--version eur]
"""

import argparse
import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("source")
parser.add_argument("--own", action="store_true", help="name the unit's functions after the source's, in order")
parser.add_argument("--dry", action="store_true")
parser.add_argument("--skip", action="append", default=[], help="with --own: a source function the linker drops (e.g. an unused C2 constructor)")
parser.add_argument("--version", default="eur")
args = parser.parse_args()

stem = Path(args.source).with_suffix(".o")
built = Path("build") / args.version / stem
original = Path("build") / args.version / "delinks" / stem


def ninja(*targets):
    result = subprocess.run(["ninja", *[str(t).replace("\\", "/") for t in targets]], capture_output=True, text=True)
    if result.returncode != 0:
        sys.exit(result.stdout + result.stderr)


ninja(built, Path("build") / args.version / "delinks" / "delink.yaml")

config = Path("config") / args.version / "arm9"
symbol_files = {"main": config / "symbols.txt", "itcm": config / "itcm" / "symbols.txt", "dtcm": config / "dtcm" / "symbols.txt"}
for folder in sorted((config / "overlays").glob("ov*")):
    symbol_files[folder.name] = folder / "symbols.txt"
symbol_re = re.compile(r"^(\S+) kind:(\S+) addr:0x([0-9a-f]+)")
auto_re = re.compile(r"^(?:func|data|__sinit|\.p__sinit)_(?:ov\d{3}_)?[0-9a-f]{8}$")
placeholder_re = re.compile(r"(unkfunc|func|data|unk|s)_(ov\d{3}_)?([0-9a-f]{8})")
by_name = {}
for module, path in symbol_files.items():
    for line in path.read_bytes().decode().splitlines():
        match = symbol_re.match(line)
        if match:
            by_name.setdefault(match.group(1), (module, int(match.group(3), 16), match.group(2)))


def module_prefix(module):
    return f"{module}_" if module.startswith("ov") else ""


local_functions = set()   # static functions of the source


def load(path):
    elf = ELFFile(open(path, "rb"))
    sections = list(elf.iter_sections())
    symtab = elf.get_section_by_name(".symtab")
    symbols = list(symtab.iter_symbols())
    functions = {}
    for symbol in symbols:
        if symbol["st_info"]["type"] == "STT_FUNC" and symbol["st_shndx"] != "SHN_UNDEF" and not symbol.name.startswith("$"):
            functions[symbol.name] = (symbol["st_shndx"], symbol["st_value"] & ~1, symbol["st_size"])
            if symbol["st_info"]["bind"] == "STB_LOCAL":
                local_functions.add(symbol.name)
    relocs = defaultdict(list)
    for section in sections:
        if not isinstance(section, RelocationSection):
            continue
        target = sections[section["sh_info"]]
        data = target.data()
        for reloc in section.iter_relocations():
            symbol = symbols[reloc["r_info_sym"]]
            if reloc.is_RELA():
                addend = reloc["r_addend"]
            elif reloc["r_info_type"] == 2:      # R_ARM_ABS32: addend in the word
                addend = int.from_bytes(data[reloc["r_offset"]:reloc["r_offset"] + 4], "little", signed=True)
            else:
                addend = 0
            name = symbol.name
            if symbol["st_info"]["type"] == "STT_SECTION":
                name = None
            relocs[section["sh_info"]].append((reloc["r_offset"], reloc["r_info_type"], name, addend,
                                               symbol["st_shndx"] == "SHN_UNDEF", symbol["st_info"]["bind"]))
    for values in relocs.values():
        values.sort()
    return functions, relocs


ours_functions, ours_relocs = load(built)
theirs_functions, theirs_relocs = load(original)

symbol_renames = {}    # (module, address) -> new symbol name
source_renames = {}    # identifier -> identifier
problems = []


def want(module, address, name):
    old = symbol_renames.setdefault((module, address), name)
    if old != name:
        problems.append(f"{module} 0x{address:08x}: {old} / {name}")


def moved_name(our_name, module, address):
    """The source's name with its placeholder moved to this game's address
    (and the source rename recorded)."""
    placeholder = list(placeholder_re.finditer(our_name))
    if len(placeholder) != 1:
        return our_name
    match = placeholder[0]
    moved = f"{match.group(1)}_{module_prefix(module)}{address:08x}"
    if len(moved) != len(match.group(0)) and our_name.startswith("_Z"):
        problems.append(f"{our_name}: placeholder length changes in a mangled name, rename by hand")
        return our_name
    new = our_name[:match.start()] + moved + our_name[match.end():]
    # The old placeholder's address can also be one of this game's (a name
    # already here): renaming it everywhere would be wrong.
    if new != our_name and our_name in by_name and by_name[our_name][:2] != (module, address):
        problems.append(f"{our_name} also names this game's 0x{by_name[our_name][1]:08x}, rename by hand")
        return our_name
    if new != our_name:
        source_renames[match.group(0)] = moved
    return new


local_symbols = set()
if args.own:
    mine = sorted((item for item in ours_functions.items() if item[0] not in args.skip), key=lambda item: (item[1][0], item[1][1]))
    theirs = sorted((by_name[name][1], name) for name in theirs_functions if name in by_name)
    if len(mine) > len(theirs):
        # Base-object constructors/destructors (C2/D2) next to complete-object
        # ones (C1/D1) are usually unreferenced: the linker drops them.
        mine = [item for item in mine if not re.search(r"[CD]2E", item[0])]
    if len(mine) != len(theirs):
        sys.exit(f"--own: {len(mine)} functions in the source, {len(theirs)} in the original")
    for (name, _), (address, their_name) in zip(mine, theirs):
        module = by_name[their_name][0]
        name = moved_name(name, module, address & ~1)
        if name != their_name:
            want(module, address, name)
        if name.startswith("__sinit_") or name in local_functions:   # static functions
            local_symbols.add((module, address))

for name, (section, start, size) in ours_functions.items():
    if name not in theirs_functions:
        continue
    their_section, their_start, their_size = theirs_functions[name]
    mine = [(o - start, *rest) for o, *rest in ours_relocs[section] if start <= o < start + size]
    theirs = [(o - their_start, *rest) for o, *rest in theirs_relocs[their_section] if their_start <= o < their_start + their_size]
    if [r[:2] for r in mine] != [r[:2] for r in theirs]:
        if [r[1] for r in mine] != [r[1] for r in theirs]:
            problems.append(f"{name}: relocations differ, not paired")
            continue
    for (_, _, our_name, our_addend, undefined, bind), (_, _, their_name, their_addend, _, _) in zip(mine, theirs):
        if our_name is None or their_name is None or their_name not in by_name:
            continue
        module, address, kind = by_name[their_name]
        address = address + their_addend - our_addend
        if kind.startswith("function"):
            address &= ~1
        if not undefined and bind == "STB_LOCAL":
            continue
        new = moved_name(our_name, module, address)
        if their_name == new:
            continue
        if (module, address) in symbol_renames or auto_re.match(their_name) or placeholder_re.search(their_name):
            want(module, address, new)
        else:
            problems.append(f"{module} 0x{address:08x} is {their_name}, the source calls it {our_name}")

# The unit's own data: sections of the same name and size pair up, their
# symbols by offset (string literals @N, statics, globals).


def data_symbols(path):
    """Per section name, the symbols at their offsets in the sections laid
    out one after the other (mwcc emits a section per string literal)."""
    elf = ELFFile(open(path, "rb"))
    sections = list(elf.iter_sections())
    starts, sizes = {}, defaultdict(int)
    for index, section in enumerate(sections):
        if section.name in (".data", ".rodata", ".bss", ".sbss", ".sdata", ".ctor"):
            align = max(section["sh_addralign"], 4)     # the linker script aligns all to 4
            start = (sizes[section.name] + align - 1) // align * align
            starts[index] = (section.name, start)
            sizes[section.name] = start + section["sh_size"]
    found = defaultdict(list)
    for symbol in elf.get_section_by_name(".symtab").iter_symbols():
        place = starts.get(symbol["st_shndx"])
        if place is None or not symbol.name or symbol.name.startswith("$") or symbol["st_info"]["type"] == "STT_SECTION":
            continue
        found[place[0]].append((place[1] + symbol["st_value"], symbol.name, symbol["st_info"]["bind"], symbol["st_size"]))
    return found, sizes


inside = {}   # (module, address of a dsd symbol inside an object) -> the object's address
additions = []  # (module, address, name, kind, local) for symbols to add

# Where the unit's sections are here (its delinks.txt entry): the original's
# symbols are placed from them, local names (@N) repeating across units.
section_starts = {}
for module, path in symbol_files.items():
    delinks = path.with_name("delinks.txt")
    if not delinks.is_file():
        continue
    current = None
    for line in delinks.read_bytes().decode().splitlines():
        header = re.match(r"^(\S.*):\s*$", line)
        if header:
            current = header.group(1).replace("\\", "/")
            continue
        entry = re.match(r"^\s+(\.\w+)\s+start:0x([0-9a-f]+)", line)
        if entry and current == Path(args.source).as_posix():
            section_starts[entry.group(1)] = (module, int(entry.group(2), 16))
ours_data, our_sizes = data_symbols(built)
theirs_data, their_sizes = data_symbols(original)
for name, mine in ours_data.items():
    if (our_sizes[name] + 3) & ~3 != (their_sizes.get(name, 0) + 3) & ~3:
        problems.append(f"{name}: {our_sizes[name]:#x} bytes in the source, {their_sizes.get(name, 0):#x} in the original, not paired")
        continue
    at = {offset: their_name for offset, their_name, _, _ in theirs_data.get(name, [])}
    for offset, our_name, bind, size in mine:
        # dsd symbols inside one of the source's objects (references to its
        # members) go: the references become the object plus an addend.
        for inner, inner_name, _, _ in theirs_data.get(name, []):
            if offset < inner < offset + size and name in section_starts and auto_re.match(inner_name):
                inner_module, base = section_starts[name]
                inside[(inner_module, base + inner)] = base + offset
        their_name = at.get(offset)
        if their_name == our_name or name not in section_starts:
            continue
        module, base = section_starts[name]
        address = base + offset
        if their_name is None:
            # No symbol there yet (e.g. a vtable dsd only knows by its +8):
            # one is added.
            additions.append((module, address, our_name, "bss" if name == ".bss" else "data(any)", bind == "STB_LOCAL"))
            continue
        if auto_re.match(their_name) or placeholder_re.search(their_name) or their_name.startswith("@"):
            want(module, address, our_name)
            if bind == "STB_LOCAL":
                local_symbols.add((module, address))
        else:
            problems.append(f"{module} 0x{address:08x} is {their_name}, the source calls it {our_name}")

for (module, address), name in sorted(symbol_renames.items()):
    print(f"{module} 0x{address:08x} -> {name}")
for old, new in sorted(source_renames.items()):
    print(f"  source: {old} -> {new}")
for (module, address), base in sorted(inside.items()):
    print(f"{module} 0x{address:08x}: inside the object at 0x{base:08x}, removed")
for module, address, name, _, _ in additions:
    print(f"{module} 0x{address:08x}: {name} added")
for problem in problems:
    print(f"PROBLEM {problem}")
if args.dry:
    sys.exit()

taken = {name for name in by_name}
for module, path in symbol_files.items():
    lines = path.read_bytes().decode().splitlines()
    changed = False
    removed = [line for line in lines if (m := symbol_re.match(line)) and (module, int(m.group(3), 16)) in inside]
    if removed:
        lines = [line for line in lines if line not in removed]
        changed = True
    for added_module, address, name, kind, local in additions:
        if added_module == module:
            lines.append(f"{name} kind:{kind} addr:0x{address:08x}" + (" local" if local else ""))
            changed = True
    for index, line in enumerate(lines):
        match = symbol_re.match(line)
        if not match:
            continue
        address = int(match.group(3), 16)
        name = symbol_renames.get((module, address)) or symbol_renames.get((module, address & ~1))
        if name and name != match.group(1):
            # Local names (string literals @N, statics) may repeat across units.
            if name in taken and by_name[name][:2] != (module, address) and (module, address) not in local_symbols:
                print(f"PROBLEM {name} already names another symbol, left {match.group(1)}")
                continue
            lines[index] = name + line[len(match.group(1)):]
            changed = True
        if (module, address) in local_symbols and not lines[index].endswith(" local"):
            lines[index] += " local"
            changed = True
    if changed:
        path.write_bytes(("\n".join(lines) + "\n").encode())

if source_renames:
    word = re.compile(r"\b(" + "|".join(map(re.escape, sorted(source_renames, key=len, reverse=True))) + r")\b")
    for root in ("src", "include", "libs"):
        for path in Path(root).rglob("*"):
            if path.suffix not in (".c", ".cpp", ".h", ".hpp", ".s", ".inc"):
                continue
            text = path.read_bytes().decode("utf-8", errors="surrogateescape")
            new = word.sub(lambda m: source_renames[m.group(1)], text)
            if new != text:
                path.write_bytes(new.encode("utf-8", errors="surrogateescape"))

# References to the removed symbols: the object's address plus an addend.
reloc_re = re.compile(r"^(\s*from:0x[0-9a-f]+ kind:\w+ )to:0x([0-9a-f]+)(?: add:(-?0x[0-9a-f]+))?( module:(\S+).*)$")


def target_module(text):
    match = re.match(r"overlay\((\d+)\)$", text)
    return f"ov{int(match.group(1)):03d}" if match else text


if inside:
    for path in {path.with_name("relocs.txt") for path in symbol_files.values()}:
        if not path.is_file():
            continue
        lines = path.read_bytes().decode().splitlines()
        changed = False
        for index, line in enumerate(lines):
            match = reloc_re.match(line)
            if not match:
                continue
            key = (target_module(match.group(5)), int(match.group(2), 16))
            if key in inside:
                base = inside[key]
                addend = key[1] - base + (int(match.group(3), 16) if match.group(3) else 0)
                lines[index] = f"{match.group(1)}to:0x{base:08x} add:{addend:#x}{match.group(4)}"
                changed = True
        if changed:
            path.write_bytes(("\n".join(lines) + "\n").encode())
