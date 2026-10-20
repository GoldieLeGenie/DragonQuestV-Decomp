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
void drawDebugBox(int x, int y, int w, int h);         // sub screen back BG box
void drawDebugWindow(int x, int y, int w, int h);         // sub screen window frame
void initDebugDisplay();                                   // end of the part initialize
void updateDebugDisplay();                                   // part onDebugPart
int getDebugDisplaySlot();                                    // part slot of the current task
