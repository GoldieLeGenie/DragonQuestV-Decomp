#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// museum stand: set, change or take back the specialty shown on a pedestal
struct MaterielMenu_MEISANHIN_ROOT : menu::MenuBase {
    enum {
        MODE_SET_ITEM = 0,
        MODE_CHANGE_ITEM = 1,
        MODE_CLEARANCE = 2,
        MODE_NEXT_MENU = 3,
        MODE_DAY_TIME = 4,
        MODE_NIGHT_TIME = 5,
        MODE_END = 6,
    };

    menu::MenuItem menuItem_;                   // 0x1C
    CursorMoveGridLoop navigator_;           // 0x80
    short meisanItem_;                          // 0x8C
    char mode_;                                 // 0x8E
    char daizaNo_;                              // 0x8F
    char waitCount_;                            // 0x90

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void selectYes();
    void selectNo();
};

extern MaterielMenu_MEISANHIN_ROOT gMaterielMenu_MEISANHIN_ROOT;
