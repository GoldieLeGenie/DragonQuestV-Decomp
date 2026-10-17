#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/UnkCursorMoveGridLoop.hpp"

// town item menu: selection of the character an item is given to
struct TownMenuItemSelectTargetChara : menu::MenuBase {
    unsigned char unk_1c;                       // 0x1C  number of selectable characters (bag included)
    menu::MenuItem menuItem_;                   // 0x20
    UnkCursorMoveGridLoop navigator_;           // 0x84

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

extern TownMenuItemSelectTargetChara gTownMenuItemSelectTargetChara;
