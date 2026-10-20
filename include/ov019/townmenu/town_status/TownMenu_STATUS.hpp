#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/CursorMoveGridLoop.hpp"

// town status menu
struct TownMenu_STATUS : menu::MenuBase {
    char mode_;                                 // 0x1C  displayed page
    CursorMoveGridLoop navigator_;           // 0x20
    menu::MenuItem menuItem_;                   // 0x2C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void updateSelectSound();
};

extern TownMenu_STATUS gTownMenu_STATUS;

int getRootMenuKind(int index);                // status icon of a tactics
int getRootMenuName(int index);                // name of a tactics
