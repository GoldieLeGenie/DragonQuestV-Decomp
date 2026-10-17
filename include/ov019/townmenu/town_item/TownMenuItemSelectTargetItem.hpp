#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/UnkCursorMoveGridLoop.hpp"

// town item menu: selection of the item exchanged with the given one
struct TownMenuItemSelectTargetItem : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    UnkCursorMoveGridLoop navigator_;           // 0x80

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool unkfunc_02171304(int page);
};

extern TownMenuItemSelectTargetItem gTownMenuItemSelectTargetItem;
