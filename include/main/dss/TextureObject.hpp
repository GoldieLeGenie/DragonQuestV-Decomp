#pragma once
#include <globaldefs.h>
#include "main/dss/DssCore.hpp"
#include "nitro/gx.h"

// texture file of the dss engine: texture + palette (+ second palette for the types 1 and 2), loaded in VRAM
unsigned int unkfunc_02049f7c(unsigned int value, unsigned int align);  // round up

struct TextureObject {
    unsigned char unk_00[0x14];                 // 0x00
    volatile int flags_;                        // 0x14 bit 0: loaded in VRAM
    int type_;                                 // 0x18 type
    int unk_1c;                                 // 0x1C
    GXTexFmt unk_20;                            // 0x20 texture format
    GXTexSizeS unk_24;                          // 0x24 width (GX size S)
    GXTexSizeT unk_28;                          // 0x28 height (GX size T)
    int unk_2c;                                 // 0x2C
    unsigned int texSize_;                        // 0x30 texture size
    int texData_;                                 // 0x34 texture data (file offset, then address)
    unsigned int plttSize_;                        // 0x38 palette size
    int plttData_;                                 // 0x3C palette data (file offset, then address)
    int texVramKey_;                                 // 0x40 texture VRAM handle
    int plttVramKey_;                                 // 0x44 palette VRAM handle
    int texAddr_;                                 // 0x48 texture VRAM address
    int plttAddr_;                                 // 0x4C palette VRAM address
    unsigned int unk_50;                        // 0x50 second texture size
    int unk_54;                                 // 0x54 second texture data
    unsigned int subPlttSize_;                        // 0x58 second palette size
    int subPlttData_;                                 // 0x5C second palette data
    int unk_60;                                 // 0x60
    int subPlttVramKey_;                                 // 0x64 second palette VRAM handle
    int unk_68;                                 // 0x68
    int subPlttAddr_;                                 // 0x6C second palette VRAM address

    TextureObject();
    ~TextureObject();
    void unkfunc_02049e9c(int flag);            // relocate, allocate the VRAM and transfer
    void unkfunc_02049ef0();                    // relocate the texture and palette offsets
    void unkfunc_02049f90();                    // free the VRAM
    void unkfunc_0204a004();                    // allocate the VRAM
    void unkfunc_0204a090(int flag);            // transfer to the VRAM
    void unkfunc_0204a114(TextureObject* src, int flag);    // transfer the data of another texture
    int unkfunc_0204a1bc();                     // texture address
    int unkfunc_0204a1c4();                     // texture data
    int unkfunc_0204a1cc();                     // palette address
    int unkfunc_0204a1d4();                     // palette data
    int unkfunc_0204a1dc();                     // palette size
    void unkfunc_0204a1e4();                    // G3 texture parameters (repeat)
    void unkfunc_0204a21c();                    // G3 texture parameters
    void unkfunc_0204a264();                    // G3 palette base
    void unkfunc_0204a290();                    // G3 texture parameters of the second texture
    void unkfunc_0204a300();                    // G3 palette base of the second palette
    int unkfunc_0204a340();                     // width
    int unkfunc_0204a38c();                     // height
};

void disableTexture();                        // G3 no texture
