#pragma once
#include <globaldefs.h>
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/UnkBgBuffer.hpp"
#include "main/dss/UnkVramRequest.hpp"

// BG used for the system text on each screen
struct UnkDisplayText {
    int type_;                                  // 0x00 0: none, 1: main + sub, 2: sub + main, 3: alternated
    int screen1_;                               // 0x04 BG of the first screen
    int screen2_;                               // 0x08 BG of the second screen
    int unk_0c;                                 // 0x0C
    int unk_10;                                 // 0x10
    int unk_14;                                 // 0x14
};

// window of the main screen
struct UnkDisplayWindow {
    int plane_;                                 // 0x00
    int x_;                                     // 0x04
    int y_;                                     // 0x08
    int w_;                                     // 0x0C
    int h_;                                     // 0x10
};

// display manager: plugin, palettes and OAM shadow buffers, debug screen, windows, capture
struct UnkDisplay {
    dss::UnkDisplayPlugin* plugin_;                // 0x0000
    dss::UnkDisplayPlugin* nextPlugin_;            // 0x0004
    unsigned int frame_;                        // 0x0008
    unsigned short backColor_;                  // 0x000C
    unsigned short unk_0e;                      // 0x000E
    int blendMode_;                             // 0x0010
    UnkPaletteBuffer bgPalette_[2];             // 0x0014
    UnkPaletteBuffer objPalette_[2];            // 0x0414
    UnkOamBuffer oam_[2];                       // 0x0814
    UnkDisplayText text_;                       // 0x102C
    UnkScreenBuffer screen_;                    // 0x1044 debug screen
    unsigned short screenData_[2][0x300];       // 0x1058
    int windowEnable_[2];                       // 0x1C58
    UnkDisplayWindow window_[2];                // 0x1C60
    char unk_1c88[0x50];                        // 0x1C88
    int capture_;                               // 0x1CD8
    int captureStep_;                           // 0x1CDC
    int captureX_;                              // 0x1CE0
    int captureY_;                              // 0x1CE4
    int blendA_;                                // 0x1CE8
    int blendB_;                                // 0x1CEC

    UnkDisplay();
};

extern UnkDisplay data_020fe6b0;

void unkfunc_0204c9ac(int* x, int* y);          // capture position
void unkfunc_0204c9bc(int x, int y);
void unkfunc_0204c9c8();
void unkfunc_0204c9d8(dss::UnkDisplayPlugin* plugin);  // change the plugin now
void unkfunc_0204ca54();                        // clear the OAM buffers
void unkfunc_0204ca6c();                        // update
void unkfunc_0204cc9c(dss::UnkDisplayPlugin* plugin);  // change the plugin
int unkfunc_0204cca8();                         // plugin changed and text shown
int getDisplayFrame();                         // frame counter
void unkfunc_0204ccdc(unsigned short color);    // backdrop color
void unkfunc_0204cce8(unsigned short value);
void unkfunc_0204ccf4(int mode);                // blend mode
UnkPaletteBuffer* getBgPaletteBuffer(int bg);     // BG palette (0-3 main, 4-7 sub)
UnkPaletteBuffer* getObjPaletteBuffer(int screen); // OBJ palette
UnkOamBuffer* unkfunc_0204ce18(int screen);     // OAM buffer
UnkOamBuffer* unkfunc_0204ce40(int y);          // OAM buffer of a position (0: main screen, 192: sub screen)
int unkfunc_0204ced8(int y);                    // text BG of a position
int unkfunc_0204cf7c(int y);
void unkfunc_0204d020(int type, int screen1, int screen2, int unk_0c, int unk_10, int unk_14);
int unkfunc_0204d03c();
UnkScreenBuffer* getDebugScreenBuffer();            // debug screen
void setDisplayTextCounter(int counter);             // show the text
void unkfunc_0204d068(int enable);              // window 0
void unkfunc_0204d074(int enable);              // window 1
void unkfunc_0204d080(int plane, int x, int y, int w, int h);
void unkfunc_0204d098(int plane, int x, int y, int w, int h);
int unkfunc_0204d0b8();                         // plugin type
void unkfunc_0204d0cc();                        // request a screen capture
void unkfunc_0204d0f4();                        // capture step
int unkfunc_0204d1f4();                         // screen capture done

extern "C" {
    void func_02075aa0(unsigned int* reg, int plane, int brightness);   // brightness blend
    void _G2_SetBlend(unsigned int* reg, int srcPlane, int dstPlane, int eva, int evb);
}
