#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// Luida's bar: call a member waiting at the bar
struct MaterielMenu_LUIDA_ADD_PLAYER : menu::MenuBase {
    enum {
        MODE_OPEN = 0,
        MODE_SELECT = 1,
        MODE_SYSTEM = 2,
        MODE_RETURN = 3,
        MODE_BOOKING = 4,
        MODE_END = 5,
    };

    char mode_;                                 // 0x1C
    menu::MenuItem menuItem_;                   // 0x20
    UnkCursorMoveGridLoop navigator_;           // 0x84

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void messageUpdate();
    void returnRoot();
    int getMessageNo(int index);
    void setFlag(int index);
};

extern MaterielMenu_LUIDA_ADD_PLAYER gMaterielMenu_LUIDA_ADD_PLAYER;
