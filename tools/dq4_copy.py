#!/usr/bin/env python3
"""Copies a DQ IV decomp source file here, with the names this game already uses.

The DQ IV placeholders (unkfunc_XXXXXXXX, data_..., func_... with DQ IV's
addresses) that this game's copies of the DQ IV headers already renamed (to
this game's addresses) are renamed in the copy the same way: the renames come
from comparing each DQ IV header with its copy here, token by token. The
#include paths and the destination follow this game's overlay numbers. The
placeholders left with DQ IV names are listed (sync_names.py moves them once
the unit has its delinks.txt entry).

usage: dq4_copy.py PATH_TO_DQIVDECOMP SOURCE [--force]
"""

import argparse
import difflib
import re
import sys
from collections import defaultdict
from pathlib import Path

parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("dq4", type=Path)
parser.add_argument("source")
parser.add_argument("--pairs", type=Path, default=Path("mobile/dq4_pairs.txt"))
parser.add_argument("--force", action="store_true", help="overwrite an existing file")
args = parser.parse_args()

# DQ IV overlay numbers -> this game's (majority of the matched functions).
votes = defaultdict(lambda: defaultdict(int))
for line in args.pairs.read_text().splitlines():
    kind, module5, _, module4, _ = line.split()
    votes[module4][module5] += 1
overlay_map = {module4: max(v, key=v.get) for module4, v in votes.items()}
overlay_dir_re = re.compile(r"^(src/|include/)?(ov\d{3})(/.*)$")


def translate(path: str) -> str:
    match = overlay_dir_re.match(path)
    if not match or match.group(2) not in overlay_map:
        return path
    return f"{match.group(1) or ''}{overlay_map[match.group(2)]}{match.group(3)}"


placeholder_re = re.compile(r"^(?:unkfunc|func|data|unk)_(?:ov\d{3}_)?[0-9a-f]{8}$")
token_re = re.compile(r"\w+|[^\w\s]")

renames = defaultdict(set)
roots = [("include", "include")] + [(f"libs/{lib.name}/include", f"libs/{lib.name}/include")
                                    for lib in (args.dq4 / "libs").iterdir() if lib.is_dir()]
for root4, root5 in roots:
    for header4 in (args.dq4 / root4).rglob("*"):
        if header4.suffix not in (".h", ".hpp"):
            continue
        relative = header4.relative_to(args.dq4).as_posix()
        header5 = Path(translate(relative))
        if not header5.is_file():
            continue
        tokens4 = token_re.findall(header4.read_bytes().decode("utf-8", errors="replace"))
        tokens5 = token_re.findall(header5.read_bytes().decode("utf-8", errors="replace"))
        matcher = difflib.SequenceMatcher(None, tokens4, tokens5, autojunk=False)
        for tag, a0, a1, b0, b1 in matcher.get_opcodes():
            if tag == "replace" and a1 - a0 == b1 - b0:
                for old, new in zip(tokens4[a0:a1], tokens5[b0:b1]):
                    if placeholder_re.match(old) and placeholder_re.match(new) and old != new:
                        renames[old].add(new)

table = {old: next(iter(new)) for old, new in renames.items() if len(new) == 1}
for old, new in renames.items():
    if len(new) > 1:
        print(f"ambiguous: {old} -> {sorted(new)}")

word = re.compile(r"\b(" + "|".join(map(re.escape, sorted(table, key=len, reverse=True))) + r")\b") if table else None
include_re = re.compile(r'(#\s*include\s+")([^"]+)(")')
left = set()


def copy(source4: Path, target: Path):
    """Copies a file, and the DQ IV headers it includes that are not here yet."""
    text = source4.read_bytes().decode("utf-8", errors="surrogateescape")

    def include(match):
        name = match.group(2)
        header4 = args.dq4 / "include" / name
        header5 = Path("include") / translate(name)
        if not (source4.parent / name).is_file() and header4.is_file() and not header5.exists():
            copy(header4, header5)
        return match.group(1) + translate(name) + match.group(3)

    text = include_re.sub(include, text)
    if word:
        text = word.sub(lambda m: table[m.group(1)], text)
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(text.encode("utf-8", errors="surrogateescape"))
    print(f"wrote {target}")
    left.update(re.findall(r"\b(?:unkfunc|func|data)_(?:ov\d{3}_)?[0-9a-f]{8}\b", text))


target = Path(translate(args.source))
if target.exists() and not args.force:
    sys.exit(f"{target} exists (--force to overwrite)")
copy(args.dq4 / args.source, target)
if left:
    print("placeholders as in DQ IV (or already this game's): " + " ".join(sorted(left)))
