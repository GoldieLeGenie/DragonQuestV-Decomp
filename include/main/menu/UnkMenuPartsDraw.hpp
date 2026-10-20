#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/dss/UnkBgBuffer.hpp"

extern int data_02105f2c;                       // origin of the parts
extern int data_02105f30;
extern int data_02105f34;                       // 1: sub screen BGs set up
extern UnkScreenBuffer* data_02105f38;          // back BG screen
extern UnkScreenBuffer* data_02105f3c;          // window BG screen
extern UnkCharBuffer* data_02105f40;            // window BG characters

// Menu parts drawn on the sub screen BGs (window frames, tiles, texts, numbers, gauges, icons, faces, arrows)
void unkfunc_02061c5c(int x, int y);            // origin of the parts
void unkfunc_02061bd8(int redraw);              // begin drawing the sub screen BGs
void drawMenuItemFrame(int x, int y, int w, int h, int priority, int flag);  // frame on data_02114dd4.frames_
int unkfunc_020623f8(int index, const char* text);  // name plate width
void unkfunc_0206241c(int index, int x, int y, int priority, int flag);  // show a name plate
void unkfunc_0206297c(UnkMenuParts* parts, int* param);
void unkfunc_02062990(UnkMenuParts* parts, int* param, int x, int y);
void unkfunc_020629a4(UnkMenuParts* parts, int* param, int color);
void unkfunc_020629b4(UnkMenuParts* parts, int* param, int x, int y, int color);
void unkfunc_020629f0(UnkMenuParts* part, int* param, int x, int y);
void unkfunc_02062a04(UnkMenuParts* part, int* param, int x, int y, int defaultColor);
extern "C" void func_02062480(int index, int r, int g, int b);  // set a color of the sub screen BG palette 15
void unkfunc_02061bd0();                        // ui_MsgSystemInit
void fillMenuBackRect(int x, int y, int w, int h, int palette);
void drawMenuWindowBack(int x, int y, int w, int h, int palette);
void drawMenuWindowBorder(int x, int y, int w, int h, int palette);
void drawMenuObjFrame(int x, int y, int w, int h, int xlu);
void drawMenuIcon(int x, int y, int w, int h, int type, int index);     // icon
void unkfunc_02061df8(int x, int y, int w, int h, int palette, int flip, int bank, int chr);
int unkfunc_02061e98(int x, int y, int w, int h, int palette, int color, int align, int font, int value, int wrap,
                     int autoReturn);
int unkfunc_02062244(int x, int y, int w, int h, int palette, int color, int align, int font, int value);
void unkfunc_020622d8(int x, int y, int percent);   // HP gauge
