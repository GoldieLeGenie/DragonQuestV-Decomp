#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// Luida's bar: choose the member who leaves the party
struct MaterielMenu_LUIDA_LEAVE_PLAYER : menu::MenuBase {
    enum {
        MODE_SELECT = 0,
        MODE_END = 1,
    };

    char mode_;                                 // 0x1C
    menu::MenuItem menuItem_;                   // 0x20
    CursorMoveGridLoop navigator_;           // 0x84

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    int getMessageNo(int index);
};

extern MaterielMenu_LUIDA_LEAVE_PLAYER gMaterielMenu_LUIDA_LEAVE_PLAYER;
