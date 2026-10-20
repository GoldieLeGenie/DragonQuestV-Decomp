#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// sugoroku: dice / status / quit menu
struct MaterielMenu_SUGOROKU_ROOT : menu::MenuBase {
    menu::MenuItem menuItem_;               // 0x1C
    CursorMoveGridLoop navigator_;       // 0x80

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

extern MaterielMenu_SUGOROKU_ROOT gMaterielMenu_SUGOROKU_ROOT;
