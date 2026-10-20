#pragma once
#include <globaldefs.h>
#include "main/debug/UnkDebugTask.hpp"
#include "main/debug/UnkDebugTurnTask.hpp"
#include "main/debug/UnkMapPerfCheck.hpp"
#include "main/debug/UnkShopMapCheck.hpp"

// Base of the debug info pages drawn on the debug console (one page per part slot)
struct UnkDebugDisplay {
    virtual void initialize() = 0;
    virtual void draw() = 0;
};

void debugConsolePrintf(int x, int y, const char* fmt, ...);  // console printf
void debugPrint(int x, int y, const char* str);      // console print (not while a menu is requested)
void unkfunc_02027058(int x, int y, int w, int h);         // sub screen back BG box
void drawDebugWindow(int x, int y, int w, int h);         // sub screen window frame
void unkfunc_020270dc();                                   // end of the part initialize
void unkfunc_0202711c();                                   // part onDebugPart
int unkfunc_020271b4();                                    // part slot of the current task
