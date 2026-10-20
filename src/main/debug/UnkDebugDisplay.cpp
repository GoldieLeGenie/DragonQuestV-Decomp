#include "main/debug/UnkDebugDisplay.hpp"
#include "main/debug/UnkBattleTest.hpp"
#include "main/debug/DebugBattleInfo.hpp"
#include "main/debug/DebugInfo.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/UnkArrayWarning.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/MenuManager.hpp"
#include "main/menu/UnkMenuBg.hpp"
#include <stdio.h>

static int s_messageTime;
static int s_arrayWarningCount;
static UnkDebugDisplay* s_display[3];
static char s_message[0x24];

THUMB void debugConsolePrintf(int x, int y, const char* fmt, ...)
{
    char buf[0x80];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, 0x80, fmt, args);
    data_020f6f9c.print(x, y, buf);
}

THUMB void debugPrint(int x, int y, const char* str)
{
    if (!MenuManager::isRequesting()) {
        data_020f6f9c.print(x, y, str);
    }
}

THUMB void drawDebugBox(int x, int y, int w, int h)
{
    if (!MenuManager::isRequesting()) {
        fillWindowBackRect(data_02106178.back_.getScreenBuffer(), x, y, w, h, 0xf);
    }
}

THUMB void drawDebugWindow(int x, int y, int w, int h)
{
    if (!MenuManager::isRequesting()) {
        drawWindowBorder(data_02106178.window_.getScreenBuffer(), x - 1, y - 1, w + 2, h + 2, 0xf);
        drawWindowBack(data_02106178.back_.getScreenBuffer(), x - 1, y - 1, w + 2, h + 2, 0xf);
    }
}

THUMB void initDebugDisplay()
{
    s_display[0] = NULL;
    s_display[1] = &data_020c2ce4;
    s_display[2] = &data_020c2d10;
    UnkDebugDisplay* display = s_display[getDebugDisplaySlot()];
    if (display != NULL) {
        display->initialize();
    }
    data_020f6f9c.clear();
}

THUMB void updateDebugDisplay()
{
    UnkDebugDisplay* display = s_display[getDebugDisplaySlot()];
    if (display != NULL) {
        display->draw();
    }
    data_020c2c40.update();
    UnkDebugTask* task = &data_020d8800;
    task->update();
    task = &data_020dc058;
    task->update();
    task = &data_020f3520;
    task->update();
    if (s_arrayWarningCount != getArrayErrorCount()) {
        s_arrayWarningCount = getArrayErrorCount();
        data_020c2d10.setShowArrayWarning(1);
    }
    if (s_messageTime != 0) {
        if (s_messageTime & 1) {
            data_020f6f9c.print(0, 0x18, s_message);
        }
        s_messageTime--;
    }
}

THUMB int getDebugDisplaySlot()
{
    switch (data_02101c88.getCurrentPart()) {
    case 4:
        return 2;
    case 6:
        return 2;
    case 5:
        return 1;
    }
    return 0;
}
