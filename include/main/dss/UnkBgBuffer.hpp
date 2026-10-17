#pragma once
#include <globaldefs.h>

struct UnkPaletteBuffer;

// BG character buffer of the dss engine (tiles of 0x20 bytes)
struct UnkCharBuffer {
    void* buf_;                                 // 0x00
    int width_;                                 // 0x04
    int height_;                                // 0x08
    int pitch_;                                 // 0x0C
};

// BG screen buffer of the dss engine (one entry per cell)
struct UnkScreenBuffer {
    unsigned short* buf_;                       // 0x00
    unsigned short* base_;                      // 0x04
    int width_;                                 // 0x08
    int height_;                                // 0x0C
    int pitch_;                                 // 0x10
};

void unkfunc_0204e558(UnkCharBuffer* buffer, void* buf, int width, int height);
void* unkfunc_0204e564(UnkCharBuffer* buffer, int x, int y);            // tile address
void unkfunc_0204e574(UnkCharBuffer* buffer, unsigned int pattern);     // fill
void unkfunc_0204e58c(UnkCharBuffer* buffer, int x, int y, int w, int h, unsigned int pattern);  // fill tiles
void unkfunc_0204e5ec(UnkCharBuffer* buffer, int x, int y, int color);  // set a pixel
void unkfunc_0204e60c(UnkCharBuffer* buffer, int x, int y, int flip, int bank, unsigned short chr);   // copy a system tile
void unkfunc_0204e83c(UnkScreenBuffer* buffer, void* buf, int width, int height);
void unkfunc_0204e848(UnkScreenBuffer* buffer, void* buf, int width, int height, int pitch);
unsigned short* unkfunc_0204e858(UnkScreenBuffer* buffer, int x, int y);    // cell address
void unkfunc_0204e868(UnkScreenBuffer* buffer, unsigned short value);   // fill
void unkfunc_0204e8b0(UnkScreenBuffer* buffer, int x, int y, int w, int h, unsigned short value);   // fill a rect
void unkfunc_0204e90c(UnkScreenBuffer* buffer, int x, int y, int w, int h, int palette, unsigned short chr);
void unkfunc_0204e92c(UnkScreenBuffer* buffer, int x, int y, int w, int h, int palette, int vflip, int hflip, unsigned short chr);
void unkfunc_0204e958(UnkScreenBuffer* buffer, int x, int y, unsigned short value);
void unkfunc_0204e964(UnkScreenBuffer* buffer, int x, int y, int w, int h, int palette);   // map the character buffer to a rect
void unkfunc_0204ea5c(UnkScreenBuffer* buffer, int x, int y, const char* text);     // ascii text (palette 15)
void unkfunc_0204ea94(UnkScreenBuffer* buffer, int palette);            // clear (-1: palette 15)
void unkfunc_0204eaac(UnkScreenBuffer* buffer, int x, int y, int w, int h, int palette);   // clear a rect
void unkfunc_0208066c(UnkScreenBuffer* buffer, int x, int y, int palette);
void unkfunc_0204ead4(UnkScreenBuffer* buffer, int x, int y, int w, int h, int palette);
void unkfunc_0204eb00(UnkScreenBuffer* buffer, int x, int y, int w, int h, int palette);   // window frame
void unkfunc_0204ec48(UnkScreenBuffer* buffer, int x, int y, int w, int h, int palette);   // window frame
void unkfunc_0204ed5c(UnkScreenBuffer* buffer, int x, int y, int w, int palette, int type);    // horizontal line
void unkfunc_0204ee0c(void* tile, int x, int y, int color);             // set a pixel
void unkfunc_0204ee28(void* tile, const void* src);                     // flip horizontally (NULL: in place)
void unkfunc_0204ee90(void* dst, const void* src);                      // draw a tile (color 0 is transparent)
void unkfunc_0204eed8(void* dst, const void* src);                      // draw a tile flipped vertically



