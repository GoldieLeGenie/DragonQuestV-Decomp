# Links the ARM9 ELF with one copy of each weak function/vtable per overlay.
#
# mwcc emits the out-of-line copies of inline functions and the weak vtables
# as STB_LOPROC symbols. mwldarm keeps only ONE such copy for the whole link
# (the first object in link order), even across overlays that share the same
# memory, while the ROM has one copy per overlay (DSSAObject2D C1 in ov001 and
# ov004, the cmn::PartyMoveAction vtable in ov001 and ov005).
#
# Before linking, a weak symbol defined in several overlays but not in the
# static modules (main/ITCM/DTCM, whose copy the overlays do use) is made
# local in each overlay where a single object defines and uses it. The patched
# objects are written to a separate folder (same file names, so the LCF still
# finds them) and the linker gets a new objects list.
#
# usage: overlay_weak_copies.py OBJECTS LCF OUTDIR -- LINKER ARGS...
#        (the "@OBJECTS" argument of the linker is replaced by the new list)
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

STB_LOCAL, STB_WEAK, STB_LOPROC = 0, 2, 13
STATIC_REGIONS = {"ARM9", "ITCM", "DTCM"}


def read_symbols(data: bytearray):
    # yields (offset of the symbol entry, name, binding, defined)
    table = struct.unpack_from("<I", data, 32)[0]
    entry_size, count = struct.unpack_from("<HH", data, 46)
    headers = [struct.unpack_from("<IIIIIIIIII", data, table + entry_size * i) for i in range(count)]
    for header in headers:
        if header[1] != 2:  # SHT_SYMTAB
            continue
        strings = headers[header[6]][4]
        for offset in range(header[4] + 16, header[4] + header[5], 16):
            name_offset, _, _, info, _, index = struct.unpack_from("<IIIBBH", data, offset)
            start = strings + name_offset
            name = data[start:data.index(0, start)].decode("ascii", "replace")
            yield offset, name, info >> 4, index != 0


def object_regions(lcf: str) -> dict[str, str]:
    regions = {}
    for block in re.finditer(r"\n    \.\w+ : \{(.*?)\n    \} > (\w+)", lcf, re.S):
        for name in re.findall(r"([^\s(]+\.o)\(", block.group(1)):
            regions.setdefault(name, block.group(2))
    return regions


def main():
    split = sys.argv.index("--")
    objects_file, lcf_file, out_dir = sys.argv[1:split]
    command = sys.argv[split + 1:]
    regions = object_regions(Path(lcf_file).read_text())
    objects = [line.strip().strip('"') for line in Path(objects_file).read_text().splitlines() if line.strip()]

    data = {}
    weak_defs: dict[str, set[str]] = {}         # symbol -> regions defining it
    users: dict[tuple[str, str], set[str]] = {}  # (symbol, region) -> objects defining or using it
    for path in objects:
        region = regions.get(os.path.basename(path), "ARM9")
        data[path] = bytearray(Path(path).read_bytes())
        for _, name, bind, defined in read_symbols(data[path]):
            if not name or name.startswith("."):
                continue
            if defined and bind in (STB_WEAK, STB_LOPROC):
                weak_defs.setdefault(name, set()).add(region)
            if bind != STB_LOCAL:
                users.setdefault((name, region), set()).add(path)

    local: dict[str, set[str]] = {}  # object -> symbols to make local
    for name, defined_in in weak_defs.items():
        overlays = defined_in - STATIC_REGIONS
        if len(overlays) < 2 or defined_in & STATIC_REGIONS:
            continue
        for region in overlays:
            paths = users[(name, region)]
            if len(paths) == 1:
                local.setdefault(next(iter(paths)), set()).add(name)

    listed = []
    for path in objects:
        if path in local:
            buffer = data[path]
            for offset, name, bind, defined in read_symbols(buffer):
                if defined and name in local[path] and bind in (STB_WEAK, STB_LOPROC):
                    buffer[offset + 12] = (STB_LOCAL << 4) | (buffer[offset + 12] & 0xf)
            target = Path(out_dir) / Path(path).relative_to(Path(path).anchor) if Path(path).is_absolute() else Path(out_dir) / path
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(buffer)
            path = str(target)
        listed.append(f'"{path}"')
    new_list = Path(out_dir) / "objects.txt"
    new_list.parent.mkdir(parents=True, exist_ok=True)
    new_list.write_text("\n".join(listed) + "\n")

    command = [f"@{new_list}" if arg == f"@{objects_file}" else arg for arg in command]
    sys.exit(subprocess.run(command).returncode)


if __name__ == "__main__":
    main()
