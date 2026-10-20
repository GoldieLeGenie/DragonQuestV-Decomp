#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// sugoroku: an item is found (the bag may be full)
struct MaterielMenu_SUGOROKU_GETITEM : menu::MenuBase {
    short itemID_;                          // 0x1C
    short meCount_;                         // 0x1E
    char mode_;                             // 0x20
    menu::MenuItem menuItem_;               // 0x24
    CursorMoveGridLoop navigator_;       // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void selectYes();
    void selectNo();
};

extern MaterielMenu_SUGOROKU_GETITEM gMaterielMenu_SUGOROKU_GETITEM;
