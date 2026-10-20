#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/CursorMoveGridLoop.hpp"

// town spell menu: destination of the return spell
struct TownMenu_MAGIC_MOVE : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    CursorMoveGridLoop navigator_;           // 0x80
    int isResult_;                              // 0x8C
    short moveTown_[20];                        // 0x90

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void moveTown();
};

extern TownMenu_MAGIC_MOVE gTownMenu_MAGIC_MOVE;
