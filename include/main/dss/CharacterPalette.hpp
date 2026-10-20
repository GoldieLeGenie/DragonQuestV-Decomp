#pragma once
#include <globaldefs.h>
#include "main/dss/TextureObject.hpp"

// copy of the palette of a texture, loaded in its own palette VRAM block
struct CharacterPalette {
    unsigned char palette_[0x400];               // 0x000 palette
    int texFormat_;                                // 0x400 texture format
    int size_;                                // 0x404 palette size
    int address_;                                // 0x408 palette VRAM address
    int handle_;                                // 0x40C palette VRAM handle
    int enable_;                                // 0x410

    CharacterPalette();
    ~CharacterPalette();
    void unkfunc_0204a3f4(TextureObject* texture, int flag);    // copy the palette of a texture
    void unkfunc_0204a474();                    // free the VRAM
    void unkfunc_02086d78(int flag);            // transfer to the VRAM
    void unkfunc_0204a4d4();                    // G3 palette base
};
