#pragma once
#include <globaldefs.h>
#include "main/global/GlobalGamePart.hpp"
#include "main/menu/MenuBase.hpp"
#include "ov036/materielmenu/common/MaterielMenu_LOAD.hpp"

// Debug start: card check then the load menu
struct GameStartPart : args::GamePart {
    int cursorPos_;                             // 0x04
    int cardcheck_;                             // 0x08

    virtual void initialize();
    virtual void terminate();
    virtual void onExecutePart();
    virtual void onDrawPart();
    virtual void onWindowPart();
    virtual void onDebugPart();
};

extern GameStartPart g_GameStartPart;
