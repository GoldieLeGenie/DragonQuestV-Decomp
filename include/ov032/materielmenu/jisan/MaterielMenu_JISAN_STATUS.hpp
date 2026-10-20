#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// monster keeper: status of the monsters left with the keeper
struct MaterielMenu_JISAN_STATUS : menu::MenuBase {
    enum {
        SELECT_MONSTER = 0,
        SELECT_MAGIC = 1,
        SELECT_END = 2,
    };

    char mode_;                             // 0x1C
    menu::MenuItem menuItem_;               // 0x20
    CursorMoveGridLoop navigator_;       // 0x84

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    int getMessageNo(int index);
    void unkfunc_021889c4();
};

extern MaterielMenu_JISAN_STATUS gMaterielMenu_JISAN_STATUS;
