#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// menu opened by scripts to show the gold window
struct MaterielMenu_SCRIPT : menu::MenuBase {
    enum DRAW_MENU {
        DRAW_GOLD = 0,
        DRAW_MAX = 1,
    };

    char drawMode_;                             // 0x1C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

extern MaterielMenu_SCRIPT data_ov019_02183ed4;
