"""Reads a dsd project: module images, symbols, relocations and source files."""

import bisect
import re
from collections import defaultdict
from pathlib import Path


symbol_re = re.compile(r"^(\S+) kind:(\w+)(?:\(([^)]*)\))? addr:0x([0-9a-f]+)")
reloc_re = re.compile(r"from:0x([0-9a-f]+) kind:(\w+) to:0x([0-9a-f]+)(?: add:(-?0x[0-9a-f]+|-?\d+))? module:(\S+)")
delink_re = re.compile(r"^\s+(\.\w+)\s+start:0x([0-9a-f]+) end:0x([0-9a-f]+)")


class Project:
    """One dsd project: module images, symbols, relocations, source files."""

    def __init__(self, root: Path, version: str):
        config = root / "config" / version / "arm9"
        extract = root / "extract" / version
        self.modules = {"main": (0x02000000, (extract / "arm9" / "arm9.bin").read_bytes(), config)}
        current = None
        for line in (extract / "arm9_overlays" / "overlays.yaml").read_text().splitlines():
            line = line.strip()
            if line.startswith("- id:"):
                current = int(line.split(":")[1])
            elif line.startswith("base_address:") and current is not None:
                name = f"ov{current:03d}"
                self.modules[name] = (int(line.split(":")[1]), (extract / "arm9_overlays" / f"{name}.bin").read_bytes(), config / "overlays" / name)
                current = None
        self.functions = {}        # (module, address) -> (name, size, thumb)
        self.symbols = {}          # (module, address) -> name (any kind)
        self.relocs = defaultdict(list)   # module -> sorted [(from, kind, to, target module)]
        self.addends = {}          # (module, from) -> addend added to the target symbol
        self.units = {}            # module -> [(start, end, source file)]
        for module, (_, _, folder) in self.modules.items():
            for line in (folder / "symbols.txt").read_text().splitlines():
                match = symbol_re.match(line)
                if not match:
                    continue
                name, kind, extra, address = match.groups()
                address = int(address, 16)
                self.symbols[(module, address)] = name
                if kind == "function":
                    size = re.search(r"size=0x([0-9a-f]+)", extra or "")
                    self.functions[(module, address)] = (name, int(size.group(1), 16) if size else 0, (extra or "").startswith("thumb"))
            relocs = folder / "relocs.txt"
            if relocs.is_file():
                for line in relocs.read_text().splitlines():
                    match = reloc_re.match(line.strip())
                    if match:
                        source, kind, target, addend, target_module = match.groups()
                        self.relocs[module].append((int(source, 16), kind, int(target, 16), target_module))
                        if addend:
                            self.addends[(module, int(source, 16))] = int(addend, 0)
            self.relocs[module].sort()
            ranges = []
            delinks = folder / "delinks.txt"
            if delinks.is_file():
                source = None
                for line in delinks.read_text().splitlines():
                    if line and not line[0].isspace() and line.rstrip().endswith(":"):
                        source = line.rstrip()[:-1]
                    else:
                        match = delink_re.match(line)
                        if match and source and match.group(1) == ".text":
                            ranges.append((int(match.group(2), 16), int(match.group(3), 16), source))
            self.units[module] = sorted(ranges)

    def body(self, key):
        """The function's bytes with relocated words masked, and its relocations."""
        module, address = key
        base, image, _ = self.modules[module]
        name, size, thumb = self.functions[key]
        start = address & ~1
        raw = bytearray(image[start - base: start - base + size])
        relocs = self.relocs[module]
        index = bisect.bisect_left(relocs, (start,))
        found = []
        while index < len(relocs) and relocs[index][0] < start + size:
            source, kind, target, target_module = relocs[index]
            offset = source - start
            raw[offset:offset + 4] = b"\0\0\0\0"
            found.append((kind, target + self.addends.get((module, source), 0), target_module))  # full address
            index += 1
        return bytes(raw), found

    def unit_of(self, key):
        module, address = key
        ranges = self.units.get(module, [])
        index = bisect.bisect_right(ranges, (address & ~1, 1 << 40)) - 1
        if index >= 0 and ranges[index][0] <= (address & ~1) < ranges[index][1]:
            return ranges[index][2]
        return None


def module_of(text):
    if text == "main":
        return "main"
    match = re.match(r"overlay\((\d+)\)", text)
    if match:
        return f"ov{int(match.group(1)):03d}"
    if text in ("itcm", "dtcm"):
        return text
    return None
