#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/CursorMoveGridLoop.hpp"

// town item menu: selection of the item exchanged with the given one
struct TownMenuItemSelectTargetItem : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    CursorMoveGridLoop navigator_;           // 0x80

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool isEmptySlotSelected(int page);
};

extern TownMenuItemSelectTargetItem gTownMenuItemSelectTargetItem;
