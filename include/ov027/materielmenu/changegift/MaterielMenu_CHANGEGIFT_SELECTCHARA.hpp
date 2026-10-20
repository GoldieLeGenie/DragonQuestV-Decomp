#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// casino prize exchange: choose who gets the prize
struct MaterielMenu_CHANGEGIFT_SELECTCHARA : menu::MenuBase {
    menu::MenuItem menuItem_;               // 0x1C
    CursorMoveGridLoop navigator_;       // 0x80
    char maxCharaCount_;                    // 0x8C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void cancelChange();
};

extern MaterielMenu_CHANGEGIFT_SELECTCHARA gMaterielMenu_CHANGEGIFT_SELECTCHARA;
