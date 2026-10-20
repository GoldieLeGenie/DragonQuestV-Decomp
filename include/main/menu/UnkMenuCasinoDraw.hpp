#pragma once
#include <globaldefs.h>

// window parts of the casino and adventure log menus drawn from menu parts lists
void unkfunc_02029fa4(int flag);                            // monster list title
void unkfunc_02029fc8(int flag);                            // bet window title
void unkfunc_02029fec(int* message, int count, int x, int y);   // command list
void unkfunc_0202a034(int monster, int diameter, int index, int order);    // monster list line
void drawFightStadiumCursor(int index);                           // monster list cursor
void unkfunc_0202a0d0(int coin, int x, int y, int flag);    // coins window
void drawCenteredMessage(int* message, int x, int y, int w, int h);    // window title
void unkfunc_0202a164(int index, const char* name, int clear, int level, int town, int time, int x, int flag);  // adventure log line
void unkfunc_0202a274(const char* name, int clear, int level, int time);    // resume data
void drawNameEditCharTable(int* text, int flag);                 // name entry keyboard lines
void unkfunc_0202a374(int language, unsigned int* text, int count, int max, int blink, int type);  // name entry chars
void unkfunc_0202a428(unsigned int* text, int count);      // name entry message chars
