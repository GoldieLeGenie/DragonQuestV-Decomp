#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// monster keeper: choose the monster (or the sack) to rename
struct MaterielMenu_JISAN_CHANGE_NAME : menu::MenuBase {
    enum {
        MODE_SELECT = 0,
        MODE_NEXT = 1,
        MODE_CURSE = 2,
        MODE_CURSE_NEXT = 3,
        MODE_CANCEL = 4,
        MODE_END = 5,
    };

    short unk_1c;                           // 0x1C
    char mode_;                             // 0x1E
    menu::MenuItem menuItem_;               // 0x20
    UnkCursorMoveGridLoop navigator_;       // 0x84
    short unk_90[0x51];                     // 0x90

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void selectYes();
    void selectNo();
    int getMessageNo(int index);
};

extern MaterielMenu_JISAN_CHANGE_NAME gMaterielMenu_JISAN_CHANGE_NAME;
