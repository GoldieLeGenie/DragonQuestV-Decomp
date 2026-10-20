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
void setMenuDrawOffset(int x, int y);            // origin of the parts
void setupMenuBgDraw(int redraw);              // begin drawing the sub screen BGs
void drawMenuItemFrame(int x, int y, int w, int h, int priority, int flag);  // frame on data_02114dd4.frames_
int setNamePlateText(int index, const char* text);  // name plate width
void showNamePlate(int index, int x, int y, int priority, int flag);  // show a name plate
void drawMenuPartsPlain(UnkMenuParts* parts, int* param);
void drawMenuPartsAt(UnkMenuParts* parts, int* param, int x, int y);
void drawMenuPartsColored(UnkMenuParts* parts, int* param, int color);
void drawMenuParts(UnkMenuParts* parts, int* param, int x, int y, int color);
void drawMenuPartAt(UnkMenuParts* part, int* param, int x, int y);
void drawMenuPart(UnkMenuParts* part, int* param, int x, int y, int defaultColor);
extern "C" void func_02062480(int index, int r, int g, int b);  // set a color of the sub screen BG palette 15
void initMenuMsgSystem();                        // ui_MsgSystemInit
void fillMenuBackRect(int x, int y, int w, int h, int palette);
void drawMenuWindowBack(int x, int y, int w, int h, int palette);
void drawMenuWindowBorder(int x, int y, int w, int h, int palette);
void drawMenuObjFrame(int x, int y, int w, int h, int xlu);
void drawMenuIcon(int x, int y, int w, int h, int type, int index);     // icon
void drawMenuSystemTiles(int x, int y, int w, int h, int palette, int flip, int bank, int chr);
int drawMenuText(int x, int y, int w, int h, int palette, int color, int align, int font, int value, int wrap,
                     int autoReturn);
int drawMenuNumber(int x, int y, int w, int h, int palette, int color, int align, int font, int value);
void drawMenuHpGauge(int x, int y, int percent);   // HP gauge
