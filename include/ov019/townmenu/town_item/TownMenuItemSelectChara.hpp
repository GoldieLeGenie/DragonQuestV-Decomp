#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/CursorMoveGridLoop.hpp"

// town item menu: item list of the selected character (or of the bag), also used to place souvenirs in the museum
struct TownMenuItemSelectChara : menu::MenuBase {
    enum {
        MODE_SELECT_ITEM = 0,
        MODE_SET_ITEM = 1,
        MODE_END = 2,
    };

    int activeFukuro_;                          // 0x1C
    int meisanhinFlag_;                         // 0x20
    int curseMessage_;                          // 0x24
    short daizaItem_;                           // 0x28
    short setItem_;                             // 0x2A
    char mode_;                                 // 0x2C
    menu::MenuItem menuItem_;                   // 0x30
    CursorMoveGridLoop navigator_;           // 0x94

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setMeisanhin();
    void selectYes();
    void selectNo();
};

extern TownMenuItemSelectChara gTownMenuItemSelectChara;
