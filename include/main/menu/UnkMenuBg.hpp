#pragma once
#include <globaldefs.h>
#include "main/dss/UnkBgBuffer.hpp"

// Sub screen window BG: characters + screen (data_020fb8f4)
struct UnkMenuWindowBg {
    UnkCharBuffer char_;                        // 0x0000
    UnkScreenBuffer screen_;                    // 0x0010
    char charData_[0xc000];                     // 0x0024  32x48 tiles
    unsigned short screenData_[0x600];          // 0xC024  32x48 cells

    void unkfunc_020636e0();
    UnkCharBuffer* unkfunc_02063708();
    UnkScreenBuffer* unkfunc_0206370c();
};

// VRAM slot of 32 icon characters
struct UnkMenuIconSlot {
    unsigned int key_;                          // 0x00  icon type | index, -1: none
    int offset_;                                // 0x04  first character
    int state_;                                 // 0x08  0: free, 1: used this frame, 2: cached
    int unk_0c;                                 // 0x0C

    void unkfunc_02063710(int offset);
    void unkfunc_02063720(unsigned int key);
    unsigned int unkfunc_02063724();
    void unkfunc_02063728(int state);
    int unkfunc_0206372c();
    int unkfunc_02063730();
};

// Queued icon draw
struct MenuIconRequest {
    int enable_;                                // 0x00
    int x_;                                     // 0x04
    int y_;                                     // 0x08
    int w_;                                     // 0x0C
    int h_;                                     // 0x10
    int type_;                                  // 0x14
    int index_;                                 // 0x18

    int set(int x, int y, int w, int h, int type, int index);
};

// Sub screen icon BG with its VRAM character cache (data_02108518)
struct UnkMenuIconBg {
    int enable_;                                // 0x0000
    UnkScreenBuffer screen_;                    // 0x0004
    unsigned short screenData_[0x600];          // 0x0018
    UnkMenuIconSlot slots_[28];                 // 0x0C18
    MenuIconRequest requests_[56];           // 0x0D68
    int requestCount_;                          // 0x1388

    UnkMenuIconBg();
    void unkfunc_0206375c(int enable);
    void unkfunc_020637ac();                    // load the icon palettes
    void unkfunc_020637f8();                    // clear the screen
    int unkfunc_02063804(unsigned int key, void* src, int size);
    int unkfunc_020638ac(unsigned int key);
    int unkfunc_020638e8(unsigned int key);
    int unkfunc_02063960();
    int unkfunc_02063988(unsigned int key);
    int unkfunc_020639bc();
    void unkfunc_020639f8(int x, int y, int w, int h, int type, int index);
    void unkfunc_02063aac(int x, int y, int w, int h, int type, int index);
    void unkfunc_02063ae4();
    void unkfunc_02063b50(int type);
    void unkfunc_02063ba4(int frame);
};

// Sub screen back BG with a color fade (data_020facbc)
struct MenuBackBg {
    UnkScreenBuffer screen_;                    // 0x000
    unsigned short screenData_[0x600];          // 0x014
    int enable_;                                // 0xC14
    int r_;                                     // 0xC18
    int g_;                                     // 0xC1C
    int b_;                                     // 0xC20
    int targetR_;                               // 0xC24
    int targetG_;                               // 0xC28
    int targetB_;                               // 0xC2C
    int frame_;                                 // 0xC30
    int unk_c34;                                // 0xC34

    void unkfunc_02063574();
    UnkScreenBuffer* getScreenBuffer();
    void startFade(int r, int g, int b, int frame);
    void unkfunc_020635d4();
};

// Sub screen menu BGs (data_02106178)
struct UnkMenuBg {
    int transferCount_;                         // 0x0000  frames left to transfer the BGs
    MenuBackBg back_;                        // 0x0004
    UnkMenuWindowBg window_;                    // 0x0C3C
    UnkMenuIconBg icon_;                        // 0xD860
};

extern UnkMenuBg data_02106178;

void unkfunc_02063568();                        // transfer the sub screen BGs on the next two frames
