#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/CursorMoveGridLoop.hpp"

// town spell menu: selection of the caster
struct UnkTownMenuMagicChara : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    CursorMoveGridLoop navigator_;           // 0x80

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

extern UnkTownMenuMagicChara data_ov019_021830a8;
