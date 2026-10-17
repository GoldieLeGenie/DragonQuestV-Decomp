#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/UnkCursorMoveGridLoop.hpp"

// town misc menu: equipment, selection of the character
struct TownMenu_OPERATION_EQUIP : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    UnkCursorMoveGridLoop navigator_;           // 0x80

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

extern TownMenu_OPERATION_EQUIP gTownMenu_OPERATION_EQUIP;
