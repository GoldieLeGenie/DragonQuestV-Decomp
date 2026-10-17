#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// museum memo: details of one specialty
struct MaterielMenu_MIMI_DETAIL : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    UnkCursorMoveGridLoop navigator_;           // 0x80

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

extern MaterielMenu_MIMI_DETAIL gMaterielMenu_MIMI_DETAIL;
