#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// monster keeper: take a monster back into the party
struct MaterielMenu_JISAN_ADD_MONSTER : menu::MenuBase {
    enum {
        MODE_INIT = 0,
        MODE_SELECT = 1,
        MODE_SYSTEM = 2,
        MODE_RETURN = 3,
        MODE_BOOKING = 4,
        MODE_END = 5,
    };

    char mode_;                             // 0x1C
    menu::MenuItem menuItem_;               // 0x20
    CursorMoveGridLoop navigator_;       // 0x84

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void messageUpdate();
    void returnRoot();
    int getMessageNo(int index);
};

extern MaterielMenu_JISAN_ADD_MONSTER gMaterielMenu_JISAN_ADD_MONSTER;
