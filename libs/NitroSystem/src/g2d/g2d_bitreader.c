#include "g2d_charcanvas.h"

#pragma thumb on

/* Bit stream reader used to unpack glyph images. */

/* Reads the next nBits (<= 8) bits, most significant first. */
u32 func_0207f904(UnkBitReader* reader, int nBits) {
    int avail = reader->unk_04;
    u32 bits = reader->unk_05;
    u32 val;

    if (avail < nBits) {
        int rest = nBits - avail;

        val = bits << rest;
        reader->unk_05 = *reader->unk_00++;
        reader->unk_04 = 8;
        val |= func_0207f904(reader, rest);
    } else {
        int rest = avail - nBits;

        val = bits >> rest;
        reader->unk_04 = rest;
    }
    return val & (0xff >> (8 - nBits));
}
