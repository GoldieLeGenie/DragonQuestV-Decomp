#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// sugoroku: party status
struct MaterielMenu_SUGOROKU_STATUS : menu::MenuBase {
    menu::MenuItem menuItem_;               // 0x1C
    UnkCursorMoveGridLoop navigator_;       // 0x80
    char mode_;                             // 0x8C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

extern MaterielMenu_SUGOROKU_STATUS gMaterielMenu_SUGOROKU_STATUS;
