#!/usr/bin/env python3

import os
from pathlib import Path
import argparse
import sys
import subprocess
import shutil
import tempfile
import struct
import re

import ninja_syntax
from get_platform import get_platform

DEFAULT_WIBO_PATH = "./wibo"

parser = argparse.ArgumentParser(description="Generates build.ninja")
parser.add_argument('-w', type=str, default=DEFAULT_WIBO_PATH, dest="wine", required=False, help="Path to Wine/Wibo (linux only)")
parser.add_argument("--compiler", type=Path, required=False, help="Path to compiler root directory")
parser.add_argument("--no-extract", action="store_true", help="Skip extract step")
parser.add_argument("--dsd", type=Path, required=False, help="Path to pre-installed dsd CLI")
parser.add_argument("--generate-delinks", action="store_true", help="Generate reference objects with compiler-specific ARM mappings")
parser.add_argument("--generate-lcf", action="store_true", help="Generate the linker command file only")
parser.add_argument('version', help='Game version')
args = parser.parse_args()

# MWCC_VERSION = "2.0/sp1p6" (DQ IV decomp compiler; DQ V needs sp2p2+, e.g. coll_GetNextMoveBox)
# DECOMP_ME_COMPILER = "mwcc_30_133"
# Config
GAME = "dqv"
# 0.12 handles the signed, compressed overlays of this game.
DSD_VERSION = 'v0.12.1'
WIBO_VERSION = '0.6.16'
OBJDIFF_VERSION = 'v3.8.2'
MWCC_VERSION = "2.0/sp2p2"
DECOMP_ME_COMPILER = "mwcc_30_131"
CC_FLAGS = " ".join([
    "-enum int",
    "-proc arm946e",
    "-gccext,on",
    "-fp soft",
    "-inline on,noauto",
    "-gccinc",
    "-interworking",
    "-gccdep",
    "-g",
    "-lang c++",
    "-O4,p",
    "-char signed",
    "-Cpp_exceptions off",
    "-RTTI off",
    "-nolink",
    "-msgstyle gcc",
    
])

# Libraries (NitroSDK, MSL, runtime) are prebuilt SDK code, compiled with another compiler and flags
LIBS_MWCC_VERSION = "2.0/sp1p5"  # NitroSDK units match sp1 to sp1p5, MSL printf needs sp1p5 or later
LIBS_CC_FLAGS = " ".join([
    "-O4,p",
    "-enum int",
    "-char signed",
    "-proc arm946e",
    "-gccext,on",
    "-fp soft",
    "-inline noauto",
    "-RTTI off",
    "-interworking",
    "-w off",
    "-sym on",
    "-gccinc",
    "-gccdep",
    "-nolink",
    "-msgstyle gcc",
    "-ipa file",
    "-str noreuse",
    "-Cpp_exceptions off",
])


LD_FLAGS = " ".join([
    "-proc arm946e",        # Target processor
    "-nostdlib",            # No C/C++ standard library
    "-Cpp_exceptions off",  # The original ROM has no exception tables
    "-interworking",        # Enable ARM/Thumb interworking
    "-m Entry",             # Set entry function
    "-map closure,unused",  # Generate map file
    "-msgstyle gcc",        # Use GCC-like messages (some IDEs will make file names clickable)
    "-dead",                # Strip unused code
])
DSD_OBJDIFF_ARGS = " ".join([
    "--scratch",                        # Metadata for creating decomp.me scratches
    f"--compiler {DECOMP_ME_COMPILER}", # decomp.me compiler name
    f'--c-flags "{CC_FLAGS}"',          # decomp.me compiler flags
    "--custom-make ninja",              # Command for rebuilding files
])


# Paths
current_path     = Path(__name__)
root_path        = current_path.parent
build_ninja_path = root_path / "build.ninja"
arm7_bios_path   = root_path / "arm7_bios.bin"
config_path      = root_path / "config"
build_path       = root_path / "build"
src_path         = root_path / "src"
libs_path        = root_path / "libs"
extract_path     = root_path / "extract"
tools_path       = root_path / "tools"
mwcc_root        = args.compiler or tools_path / "mwccarm"
mwcc_path        = mwcc_root / MWCC_VERSION


# Includes
includes = [
    str(root_path / "include")
]
for root, dirs, _ in os.walk(libs_path):
    for dir in dirs:
        if dir == "include":
            includes.append(Path(root) / dir)
CC_INCLUDES = " ".join(f"-i {include}" for include in includes)


# Platform info
platform = get_platform()
if platform is None:
    exit(1)

EXE = platform.exe
WINE = args.wine if platform.system != "windows" else ""
DSD = str(args.dsd or os.path.join('.', str(root_path / f"dsd{EXE}")))
# Path() drops the leading "./": run the given dsd by its full path, as Windows
# may not search the current directory for programs.
DSD_RUN = str(Path(DSD).resolve())
OBJDIFF = os.path.join('.', str(root_path / f"objdiff-cli{EXE}"))
CC = os.path.join('.', str(mwcc_path / "mwccarm.exe"))
CC_LIBS = os.path.join('.', str(mwcc_root / LIBS_MWCC_VERSION / "mwccarm.exe"))
MWASM_LIBS = os.path.join('.', str(mwcc_root / LIBS_MWCC_VERSION / "mwasmarm.exe"))
LD = os.path.join('.', str(mwcc_path / "mwldarm.exe"))
# Library sources built with another compiler version than LIBS_MWCC_VERSION
LIBS_CC_OVERRIDES = {
    # needs a newer compiler than sp1p2 (spill slots / register choice of three functions)
    "libs/NitroSystem/src/g3d/g3d_sbc.c": "2.0/sp2p2",
}
PYTHON = sys.executable


class Project:
    def __init__(self, game_version: str):
        self.game_version = game_version
        '''Version of the game'''
        self.game_config = config_path / game_version
        '''Root directory for dsd configs'''

        if not self.game_config.is_dir():
            print(f"Version '{game_version}' not recognized")
            exit(1)

        self.game_build = build_path / game_version
        '''Path to build directory'''
        self.game_extract = extract_path / game_version
        '''Path to extract directory'''

        self.delinks_files = get_config_files(self.game_config, "delinks.txt")
        '''Paths to every delinks.txt file'''
        self.relocs_files = get_config_files(self.game_config, "relocs.txt")
        '''Paths to every relocs.txt file'''
        self.symbols_files = get_config_files(self.game_config, "symbols.txt")
        '''Paths to every symbols.txt file'''

    def dsd_configs(self) -> list[str]:
        return self.delinks_files + self.relocs_files + self.symbols_files

    def arm9_config_yaml(self) -> Path:
        return self.game_config / "arm9" / "config.yaml"

    def baserom(self) -> Path:
        return extract_path / f'baserom_{GAME}_{self.game_version}.nds'

    def build_rom(self) -> str:
        return f"{GAME}_{self.game_version}.nds"

    def baserom_config(self) -> Path:
        return self.game_extract / 'config.yaml'

    def build_rom_config(self) -> Path:
        return self.game_build / "build" / "rom_config.yaml"

    def source_object_files(self) -> list[str]:
        return [
            str(self.game_build / source_file.with_suffix(".o"))
            for source_file in [*get_c_cpp_files([src_path, libs_path]), *get_asm_files([libs_path])]
        ]

    def arm9_lcf(self) -> Path:
        return self.game_build / "arm9.lcf"

    def arm9_objects_txt(self) -> Path:
        return self.game_build / "objects.txt"

    def arm9_delink_yaml(self) -> Path:
        return self.game_build / "delinks" / "delink.yaml"

    def arm9_o(self) -> Path:
        return self.game_build / "arm9.o"

    def arm9_delinks(self) -> Path:
        return self.game_build / "delinks"

    def objdiff_report(self) -> Path:
        return self.game_build / "report.json"


# Sections of dsd's gap objects (the ROM parts not decompiled yet) kept whole.
GAP_SECTIONS = (".text", ".rodata", ".data", ".bss")


def retained_input_sections() -> dict[Path, tuple[str, ...]]:
    # Whole input sections whose unreferenced contents are present in the ROM.
    # Module padding is ordinary source data, not a list of linker root symbols.
    result: dict[Path, tuple[str, ...]] = {
        # SDK and runtime storage nothing refers to (as in DQ IV).
        Path("libs/Runtime/src/MWException.cpp"): (".data",),
        Path("libs/NitroSDK/src/math/math_sha1_block.c"): (".text",),
        Path("libs/NitroSystem/src/g2d/g2d_softsprite.c"): (".bss",),
        Path("libs/NitroSystem/src/snd/snd_nns_main.c"): (".bss",),
        Path("libs/NitroSDK/src/os/os_exception.c"): (".bss",),
    }
    result.update((source, (".data", ".bss"))
                  for source in src_path.rglob("ModulePadding_*.cpp"))
    return result


def library_functions(project: "Project") -> list[str]:
    """Functions of the delinked library files (libs/...), from symbols.txt.

    A library file's functions are all in the ROM, called or not by this game
    (OS_DisableProtectionUnit is not): the linker keeps them (FORCE_ACTIVE).
    """
    ranges = []
    for delinks in project.delinks_files:
        source = None
        for line in Path(delinks).read_text().splitlines():
            if line and not line[0].isspace() and line.rstrip().endswith(":"):
                source = line.rstrip()[:-1]
            elif source and source.startswith("libs/") and ".text" in line:
                fields = dict(part.split(":", 1) for part in line.split() if ":" in part)
                ranges.append((int(fields["start"], 16), int(fields["end"], 16)))
    names = []
    for symbols in project.symbols_files:
        for line in Path(symbols).read_text().splitlines():
            if " kind:function" in line:
                name = line.split(" ", 1)[0]
                address = int(line.rsplit("addr:0x", 1)[1].split()[0], 16)
                if any(start <= address < end for start, end in ranges):
                    names.append(name)
    return names


def name_retained_reference_sections(path: Path, sections: tuple[str, ...]):
    # DSD extracts the original output-section names. Match the explicit input
    # section names used by the compiler for KEEP_SECTION. Only ELF section-name
    # metadata changes: code/data bytes, symbols and relocations are untouched.
    data = bytearray(path.read_bytes())
    if data[:6] != b"\x7fELF\x01\x01":
        raise ValueError(f"Expected little-endian ELF32: {path}")
    table = struct.unpack_from("<I", data, 32)[0]
    entry_size, count, names_index = struct.unpack_from("<HHH", data, 46)
    names_header = table + entry_size * names_index
    names_offset, names_size = struct.unpack_from("<II", data, names_header + 16)
    names = bytearray(data[names_offset:names_offset + names_size])
    changed = False
    for index in range(count):
        header = table + entry_size * index
        offset = struct.unpack_from("<I", data, header)[0]
        end = names.index(0, offset)
        name = names[offset:end].decode("ascii")
        if name in sections:
            struct.pack_into("<I", data, header, len(names))
            names.extend((name + ".keep").encode("ascii") + b"\0")
            changed = True
    if changed:
        struct.pack_into("<II", data, names_header + 16, len(data), len(names))
        data.extend(names)
        path.write_bytes(data)


# Out-of-line copies of inline functions that the ROM keeps in a part of main
# not decompiled yet. mwcc objects define such copies as STB_LOPROC, and mwld
# stops with "Multiply-defined" when the gap object defines them as globals:
# marked STB_LOPROC like a compiled object, the gap's copy is the one kept
# (first in link order) and the decompiled units' copies are dropped.
GAP_INLINE_COPIES = {
    "_ZN15UnkLZDataObjectC1Ev",  # 0x02057d70
    "_ZN15UnkLZDataObjectD1Ev",  # 0x020555c4
}


def mark_inline_copies(path: Path, symbols: set[str]):
    data = bytearray(path.read_bytes())
    table = struct.unpack_from("<I", data, 32)[0]
    entry_size, count = struct.unpack_from("<HH", data, 46)
    headers = [struct.unpack_from("<IIIIIIIIII", data, table + entry_size * i) for i in range(count)]
    changed = False
    for header in headers:
        if header[1] != 2:
            continue
        strings = headers[header[6]][4]
        for offset in range(header[4], header[4] + header[5], 16):
            name_offset = struct.unpack_from("<I", data, offset)[0]
            start = strings + name_offset
            name = data[start:data.index(0, start)].decode("ascii")
            if name in symbols:
                data[offset + 12] = (13 << 4) | (data[offset + 12] & 0xf)
                changed = True
    if changed:
        path.write_bytes(data)


def generate_delinks(project: Project):
    # MWCC leaves inline jump tables in code mode; mwasm emits data mappings.
    # Keep the ROM bytes/relocations unchanged and use the appropriate mapping
    # style for each producer so objdiff decodes both sides consistently.
    command = [DSD_RUN, "delink", "-c", str(project.arm9_config_yaml())]
    subprocess.run(command + ["--all-mapping-symbols"], check=True)
    with tempfile.TemporaryDirectory(dir=project.game_build) as directory:
        saved = []
        full_mapping_sources = list(get_asm_files([libs_path]))
        for source in full_mapping_sources:
            target = project.arm9_delinks() / source.with_suffix(".o")
            if target.is_file():
                copy = Path(directory) / f"{len(saved)}.o"
                shutil.copyfile(target, copy)
                saved.append((copy, target))
        subprocess.run(command, check=True)
        for copy, target in saved:
            shutil.copyfile(copy, target)
    for source, sections in retained_input_sections().items():
        target = project.arm9_delinks() / source.with_suffix(".o")
        if target.is_file():
            name_retained_reference_sections(target, sections)
    # The parts of the ROM not decompiled yet (dsd's gap objects) stay whole:
    # a function there nothing refers to by name (an overlay entered through
    # tables, a stub left alone between decompiled files) is still in the ROM.
    for gap in project.arm9_delinks().glob("_dsd_gap@*.o"):
        name_retained_reference_sections(gap, GAP_SECTIONS)
        mark_inline_copies(gap, GAP_INLINE_COPIES)


def generate_lcf(project: Project):
    subprocess.run([DSD_RUN, "lcf", "-c", str(project.arm9_config_yaml())], check=True)
    # Link-time constants of the SDK (arena starts, stack sizes) that the
    # delinked code refers to by absolute value, per game version.
    absolute_symbols: dict[str, dict[str, int]] = {
        "eur": {
            "unk_IrqStackSize": 0x1000,
            "unk_SysStackSize": 0,
            "unk_DtcmArenaStart": 0x027e0080,
            "unk_MainArenaStart": 0x0218c1c0,
            "unk_ItcmArenaStart": 0x01ff82a0,
            "unk_DtcmStackEnd": 0x027e3f80,
            # end of the (empty) overlay digest table, whose start is data_0209c8cc
            "data_0209c8cc_end": 0x0209c8cc,
        },
    }
    lcf = project.arm9_lcf()
    text = lcf.read_text()
    sections = "SECTIONS {\n"
    if sections not in text:
        raise ValueError(f"Missing SECTIONS block in {lcf}")
    definitions = "".join(
        f"    {name} = 0x{value:08x};\n"
        for name, value in absolute_symbols.get(project.game_version, {}).items()
    )
    text = text.replace(sections, sections + definitions, 1)
    # Preserve the original unreferenced SDK storage and linker padding by
    # input section, without maintaining a list of forced symbol names.
    text = text.replace("KEEP_SECTION {", "KEEP_SECTION {\n"
                        "    .text.keep,\n    .rodata.keep,\n"
                        "    .data.keep,\n    .bss.keep,", 1)
    for source, sections_to_keep in retained_input_sections().items():
        for section in sections_to_keep:
            text = text.replace(f"{source.stem}.o({section})",
                                f"{source.stem}.o({section}.keep)")
    gap_sections = "|".join(re.escape(section) for section in GAP_SECTIONS)
    text = re.sub(rf"(_dsd_gap@\w+\.o)\(({gap_sections})\)", r"\1(\2.keep)", text)
    # The SDK's BuildInfo points into the main BSS, past its start: these
    # labels (zero-size symbols in symbols.txt) are defined there, in the main
    # BSS section, as absolute assignments could attach to overlapping overlays.
    bss_labels: dict[str, dict[str, int]] = {
        "eur": {
            "data_0209cbe0": 0x300,
            "data_0209cbf8": 0x318,
        },
    }
    labels = "".join(f"\n        {name} = . + 0x{offset:x};"
                     for name, offset in bss_labels.get(project.game_version, {}).items())
    text = text.replace("        ARM9_BSS_START = .;", "        ARM9_BSS_START = .;" + labels, 1)
    # The ROM has no exception table index: the runtime's exception handling
    # files are compiled with exceptions on, but the original link left their
    # index out (dsd 0.12's EXCEPTION directive would generate one).
    text = text.replace("        EXCEPTION\n", "")
    functions = library_functions(project)
    if functions:
        force = "FORCE_ACTIVE {\n" + ",\n".join(f"    {name}" for name in functions) + "\n}\n\n"
        text = text.replace("KEEP_SECTION {", force + "KEEP_SECTION {", 1)
    lcf.write_text(text)


def main():
    project = Project(args.version)
    if args.generate_delinks:
        generate_delinks(project)
        return
    if args.generate_lcf:
        generate_lcf(project)
        return

    with build_ninja_path.open("w") as file:
        n = ninja_syntax.Writer(file)

        configure_script = Path(os.path.relpath(os.path.abspath(sys.argv[0])))
        python_lib_dir = configure_script.parent
        n.comment("The arguments passed to configure.py, for rerunning it.")
        n.variable("configure_args", sys.argv[1:])
        n.variable("python", f'"{PYTHON}"')

        n.rule(
            name="download_tool",
            command=f'{PYTHON} tools/download_tool.py $tool $tag --path $path'
        )
        n.newline()

        if arm7_bios_path.is_file():
            n.variable("arm7_bios_flag", f"--arm7-bios {arm7_bios_path.relative_to(root_path)}")
        else:
            n.variable("arm7_bios_flag", "")
        n.newline()

        n.rule(
            name="extract",
            command=f"{DSD} rom extract --rom $in --output-path $output_path $arm7_bios_flag"
        )
        n.newline()

        n.rule(
            name="delink",
            command=f'$python tools/configure.py $version --generate-delinks --dsd "{DSD}"'
        )
        n.newline()

        # -MMD excludes all includes instead of just system includes for some reason, so use -MD instead.
        mwcc_cmd = f'{WINE} "{CC}" {CC_FLAGS} {CC_INCLUDES} $cc_flags -d $game_version -MD -c $in -o $basedir'
        mwcc_implicit = [CC]
        if platform.system != "windows":
            transform_dep = "tools/transform_dep.py"
            mwcc_cmd += f" && $python {transform_dep} $basefile.d $basefile.d"
            mwcc_implicit.append(transform_dep)

        n.rule(
            name="mwcc",
            command=mwcc_cmd,
            depfile="$basefile.d",
        )
        n.newline()

        mwcc_libs_cmd = f'{WINE} "$cc_libs" {LIBS_CC_FLAGS} {CC_INCLUDES} $cc_flags -MD -c $in -o $basedir'
        if platform.system != "windows":
            mwcc_libs_cmd += f" && $python {transform_dep} $basefile.d $basefile.d"
        n.rule(
            name="mwcc_libs",
            command=mwcc_libs_cmd,
            depfile="$basefile.d",
        )
        n.newline()

        # hand-written assembly (lib sources that are not compiled code)
        n.rule(
            name="mwasm",
            command=f'{WINE} "$mwasm" -proc arm5TE $in -o $out',
        )
        n.newline()

        n.rule(
            name="lcf",
            command=f'$python tools/configure.py $version --generate-lcf --dsd "{DSD}"'
        )
        n.newline()

        n.rule(
            name="mwld",
            # overlay_weak_copies.py keeps one weak copy per overlay, as in the ROM
            command=f'$python tools/overlay_weak_copies.py $objects_file $lcf_file $target_dir/weak -- '
                    f'{WINE} "{LD}" {LD_FLAGS} @$objects_file $lcf_file -o $out'
        )
        n.newline()

        n.rule(
            name="rom_config",
            command=f"{DSD} rom config --elf $in --config $config_path"
        )
        n.newline()

        n.rule(
            name="rom_build",
            # dsd's re-encrypted secure area has another checksum than the
            # original header's: secure_area_crc.py restores it.
            command=f"$python tools/secure_area_crc.py $out $baserom "
                    f"{DSD_RUN} rom build --config $in --rom $out $arm7_bios_flag"
        )
        n.newline()
        
        n.rule(
            name="objdiff",
            command=f"{DSD} objdiff --config-path $config_path {DSD_OBJDIFF_ARGS}"
        )
        n.newline()

        n.rule(
            name="objdiff_report",
            # ARM mapping symbols must stay with their original code sections.
            command=f"{OBJDIFF} report generate -c combine_text_sections=false -o $out"
        )
        n.newline()

        n.rule(
            name="m2ctx",
            command=f"{PYTHON} tools/m2ctx.py -f $out $in"
        )
        n.newline()

        n.rule(
            name="check_modules",
            command=f"{DSD} check modules --config-path $config_path --fail"
        )
        n.newline()

        n.rule(
            name="check_symbols",
            command=f"{DSD} check symbols --config-path $config_path --elf-path $elf_path --fail"
        )
        n.newline()

        n.rule(
            name="sha1",
            command=f"{PYTHON} tools/sha1.py $in -c $sha1_file"
        )
        n.newline()

        add_download_tool_builds(n)
        add_extract_build(n, project)
        add_delink_and_lcf_builds(n, project)
        add_mwcc_builds(n, project, mwcc_implicit)
        add_mwld_and_rom_builds(n, project)
        add_check_builds(n, project)
        add_objdiff_builds(n, project)
        add_configure_build(n, project, configure_script, python_lib_dir)

        n.default("report")

def add_download_tool_builds(n: ninja_syntax.Writer):
    if args.dsd is None:
        n.build(
            rule="download_tool",
            outputs=DSD,
            variables={
                "tool": "dsd",
                "tag": DSD_VERSION,
                "path": DSD,
            },
        )
        n.newline()

    n.build(
        rule="download_tool",
        outputs=OBJDIFF,
        variables={
            "tool": "objdiff",
            "tag": OBJDIFF_VERSION,
            "path": OBJDIFF,
        }
    )
    n.newline()

    if args.compiler is None:
        n.build(
            rule="download_tool",
            outputs=[CC, LD, CC_LIBS, MWASM_LIBS],
            variables={
                "tool": "mwccarm",
                "tag": "latest",
                "path": tools_path,
            },
        )
        n.newline()

    if platform.system != "windows" and WINE == DEFAULT_WIBO_PATH:
        n.build(
            rule="download_tool",
            outputs=WINE,
            variables={
                "tool": "wibo",
                "tag": WIBO_VERSION,
                "path": WINE,
            },
        )
        n.newline()

def add_extract_build(n: ninja_syntax.Writer, project: Project):
    if not args.no_extract:
        n.build(
            inputs=str(project.baserom()),
            implicit=DSD,
            rule="extract",
            outputs=str(project.baserom_config()),
            variables={
                "output_path": str(project.game_extract)
            }
        )
        n.newline()


def add_mwld_and_rom_builds(n: ninja_syntax.Writer, project: Project):
    lcf_file = str(project.arm9_lcf())
    objects_file = str(project.arm9_objects_txt())
    delink_file = str(project.arm9_delink_yaml())
    elf_file = str(project.arm9_o())
    n.build(
        inputs=project.source_object_files() + [lcf_file, objects_file, delink_file],
        implicit=[LD, "tools/overlay_weak_copies.py"],
        rule="mwld",
        outputs=elf_file,
        variables={
            "target_dir": project.game_build,
            "objects_file": objects_file,
            "lcf_file": lcf_file,
        }
    )
    n.newline()

    n.build(
        inputs=elf_file,
        rule="phony",
        outputs="arm9",
    )
    n.newline()

    rom_config_file = str(project.build_rom_config())
    n.build(
        inputs=elf_file,
        implicit=DSD,
        rule="rom_config",
        outputs=rom_config_file,
        variables={
            "config_path": project.arm9_config_yaml(),
        }
    )
    n.newline()

    rom_file = project.build_rom()
    n.build(
        inputs=rom_config_file,
        implicit=[DSD, "tools/secure_area_crc.py"],
        rule="rom_build",
        outputs=rom_file,
        variables={
            "baserom": str(project.baserom()),
        },
    )
    n.newline()

    n.build(
        inputs=rom_file,
        rule="phony",
        outputs="rom",
    )
    n.newline()

    n.build(
        inputs=rom_file,
        rule="sha1",
        variables={
            "sha1_file": project.game_config / f"{GAME}_{project.game_version}.sha1"
        },
        outputs="sha1",
    )
    n.newline()

def add_mwcc_builds(n: ninja_syntax.Writer, project: Project, mwcc_implicit: list[Path]):
    for source_file in get_c_cpp_files([src_path, libs_path]):
        src_obj_path = project.game_build / source_file
        cc_flags = []
        if is_cpp(source_file): cc_flags.append("-lang=c++")
        elif is_c(source_file): cc_flags.append("-lang=c")
        is_lib = libs_path in source_file.parents
        cc_libs = CC_LIBS
        override = LIBS_CC_OVERRIDES.get(source_file.relative_to(root_path).as_posix()) if is_lib else None
        if override:
            cc_libs = os.path.join('.', str(mwcc_root / override / "mwccarm.exe"))
        n.build(
            inputs=str(source_file),
            implicit=mwcc_implicit + ([cc_libs] if is_lib else []),
            rule="mwcc_libs" if is_lib else "mwcc",
            outputs=str(src_obj_path.with_suffix(".o")),
            variables={
                "game_version": project.game_version,
                "cc_flags": " ".join(cc_flags),
                "basedir": os.path.dirname(src_obj_path),
                "basefile": str(src_obj_path.with_suffix("")),
                "cc_libs": cc_libs,
            },
        )
        n.newline()
        
        extension = source_file.suffix
        ctx_file = str(project.game_build / source_file.with_suffix(f".ctx{extension}"))
        n.build(
            inputs=str(source_file),
            rule="m2ctx",
            outputs=ctx_file,
        )
        n.newline()


    for source_file in get_asm_files([libs_path]):
        n.build(
            inputs=str(source_file),
            implicit=[MWASM_LIBS],
            rule="mwasm",
            outputs=str((project.game_build / source_file).with_suffix(".o")),
            variables={"mwasm": MWASM_LIBS},
        )
        n.newline()


def get_asm_files(dirs: list[Path]):
    for dir in dirs:
        for root, _, files in os.walk(dir):
            for file in files:
                if Path(file).suffix == ".s":
                    yield Path(root) / file


def get_c_cpp_files(dirs: list[Path]):
    for dir in dirs:
        for root, _, files in os.walk(dir):
            root = Path(root)
            for file in files:
                if is_cpp(file) or is_c(file):
                    yield root / file


def is_cpp(name: str):
    return Path(name).suffix in [".cpp"]


def is_c(name: str):
    return Path(name).suffix in [".c"]


def add_delink_and_lcf_builds(n: ninja_syntax.Writer, project: Project):
    n.comment("Delink ELF binaries when any delinks.txt file is modified")
    rom_config = str(project.baserom_config())
    delinks_path = project.arm9_delinks()
    n.build(
        inputs=project.dsd_configs() + [rom_config],
        implicit=[DSD, "tools/configure.py"],
        rule="delink",
        outputs=str(delinks_path / "delink.yaml"),
        variables={
            "config_path": project.arm9_config_yaml(),
            "version": project.game_version,
        }
    )
    n.newline()

    n.build(
        inputs=str(delinks_path / "delink.yaml"),
        rule="phony",
        outputs="delink"
    )
    n.newline()

    lcf_file = project.arm9_lcf()
    objects_file = project.arm9_objects_txt()
    n.build(
        inputs=project.delinks_files + [str(rom_config)],
        implicit=[DSD, "tools/configure.py"],
        rule="lcf",
        outputs=[str(lcf_file), str(objects_file)],
        variables={
            "config_path": project.arm9_config_yaml(),
            "lcf_file": lcf_file,
            "objects_file": objects_file,
            "version": project.game_version,
        }
    )
    n.newline()

def add_check_builds(n: ninja_syntax.Writer, project: Project):
    n.build(
        inputs=str(project.arm9_o()),
        rule="check_modules",
        outputs="check_modules",
        variables={
            "config_path": project.arm9_config_yaml(),
        },
    )
    n.newline()

    n.build(
        inputs=str(project.arm9_o()),
        rule="check_symbols",
        outputs="check_symbols",
        variables={
            "config_path": project.arm9_config_yaml(),
            "elf_path": project.arm9_o(),
        },
    )
    n.newline()

    n.build(
        inputs=["check_modules", "check_symbols", "sha1"],
        rule="phony",
        outputs="check",
    )
    n.newline()

def add_objdiff_builds(n: ninja_syntax.Writer, project: Project):
    n.build(
        inputs=project.dsd_configs(),
        implicit=DSD,
        rule="objdiff",
        outputs="objdiff.json",
        variables={
            "config_path": project.arm9_config_yaml(),
        }
    )
    n.newline()

    n.build(
        inputs="objdiff.json",
        rule="phony",
        outputs="objdiff",
    )
    n.newline()

    n.build(
        inputs=["objdiff.json"],
        implicit=[OBJDIFF, "arm9", "check"] + project.source_object_files(),
        rule="objdiff_report",
        outputs=str(project.objdiff_report()),
    )
    n.newline()

    n.build(
        inputs=str(project.objdiff_report()),
        rule="phony",
        outputs="report",
    )
    n.newline()

def add_configure_build(n: ninja_syntax.Writer, project: Project, configure_script: Path, python_lib_dir):
    ###
    # Regenerate on change
    ###
    n.comment("Reconfigure on change")
    n.rule(
        name="configure",
        command=f"$python {configure_script} $configure_args",
        generator=True,
        description=f"RUN {configure_script}",
    )

    n.build(
        outputs="build.ninja",
        rule="configure",
        implicit=[
            str(configure_script),
            str(python_lib_dir / "ninja_syntax.py"),
        ] + project.dsd_configs(),
    )
    n.newline()

def get_config_files(game_config: Path, name: str) -> list[str]:
    return [
        f"{root}/{file}"
        for root, _, files in os.walk(game_config)
        for file in files
        if file == name
    ]


if __name__ == "__main__":
    main()
