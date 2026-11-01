#!/usr/bin/env python3
"""Gives a built ROM the secure area checksum of the base ROM.

"""

import argparse
import struct
import subprocess
from pathlib import Path

SECURE_AREA_CRC = 0x6C
HEADER_CRC = 0x15E


def crc16(data: bytes, crc: int = 0xFFFF) -> int:
    for byte in data:
        crc ^= byte
        for _ in range(8):
            crc = (crc >> 1) ^ 0xA001 if crc & 1 else crc >> 1
    return crc


parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("rom", type=Path, help="Built ROM, changed in place")
parser.add_argument("baserom", type=Path, help="Original ROM")
parser.add_argument("build", nargs=argparse.REMAINDER,
                    help="Command building the ROM first (ninja runs no shell to chain them)")
args = parser.parse_args()

if args.build:
    subprocess.run(args.build, check=True)

with args.baserom.open("rb") as file:
    base = file.read(0x200)
rom = bytearray(args.rom.read_bytes())
rom[SECURE_AREA_CRC:SECURE_AREA_CRC + 2] = base[SECURE_AREA_CRC:SECURE_AREA_CRC + 2]
struct.pack_into("<H", rom, HEADER_CRC, crc16(rom[:HEADER_CRC]))
args.rom.write_bytes(rom)
