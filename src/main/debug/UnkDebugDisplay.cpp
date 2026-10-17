#include "main/debug/UnkDebugDisplay.hpp"
#include "main/debug/UnkBattleTest.hpp"
#include "main/debug/UnkDebugBattleInfo.hpp"
#include "main/debug/UnkDebugInfo.hpp"
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

THUMB void unkfunc_02026ffc(int x, int y, const char* fmt, ...)
{
    char buf[0x80];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, 0x80, fmt, args);
    data_020f6f9c.unkfunc_0204b034(x, y, buf);
}

THUMB void unkfunc_02027034(int x, int y, const char* str)
{
    if (!MenuManager::isRequesting()) {
        data_020f6f9c.unkfunc_0204b034(x, y, str);
    }
}

THUMB void unkfunc_02027058(int x, int y, int w, int h)
{
    if (!MenuManager::isRequesting()) {
        unkfunc_0204ead4(data_02106178.back_.unkfunc_020635a8(), x, y, w, h, 0xf);
    }
}

THUMB void unkfunc_0202708c(int x, int y, int w, int h)
{
    if (!MenuManager::isRequesting()) {
        unkfunc_0204ec48(data_02106178.window_.unkfunc_0206370c(), x - 1, y - 1, w + 2, h + 2, 0xf);
        unkfunc_0204eb00(data_02106178.back_.unkfunc_020635a8(), x - 1, y - 1, w + 2, h + 2, 0xf);
    }
}

THUMB void unkfunc_020270dc()
{
    s_display[0] = NULL;
    s_display[1] = &data_020c2ce4;
    s_display[2] = &data_020c2d10;
    UnkDebugDisplay* display = s_display[unkfunc_020271b4()];
    if (display != NULL) {
        display->initialize();
    }
    data_020f6f9c.unkfunc_0204affc();
}

THUMB void unkfunc_0202711c()
{
    UnkDebugDisplay* display = s_display[unkfunc_020271b4()];
    if (display != NULL) {
        display->draw();
    }
    data_020c2c40.unkfunc_02026b68();
    UnkDebugTask* task = &data_020d8800;
    task->unkfunc_02038248();
    task = &data_020dc058;
    task->unkfunc_02038248();
    task = &data_020f3520;
    task->unkfunc_02038248();
    if (s_arrayWarningCount != unkfunc_0204c130()) {
        s_arrayWarningCount = unkfunc_0204c130();
        data_020c2d10.unkfunc_02028258(1);
    }
    if (s_messageTime != 0) {
        if (s_messageTime & 1) {
            data_020f6f9c.unkfunc_0204b034(0, 0x18, s_message);
        }
        s_messageTime--;
    }
}

THUMB int unkfunc_020271b4()
{
    switch (data_02101c88.unkfunc_02051810()) {
    case 4:
        return 2;
    case 6:
        return 2;
    case 5:
        return 1;
    }
    return 0;
}
