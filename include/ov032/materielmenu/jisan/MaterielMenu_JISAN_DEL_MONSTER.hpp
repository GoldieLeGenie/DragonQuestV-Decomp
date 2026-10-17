#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// monster keeper: part with a monster for good
struct MaterielMenu_JISAN_DEL_MONSTER : menu::MenuBase {
    enum {
        MODE_SELECT = 0,
        MODE_DEATH = 1,
        MODE_ALIVE = 2,
        MODE_SYSTEM = 3,
        MODE_END = 4,
    };

    int systemMessage_[2];                  // 0x1C
    short activeChara_;                     // 0x24
    char mode_;                             // 0x26
    menu::MenuItem menuItem_;               // 0x28
    UnkCursorMoveGridLoop navigator_;       // 0x8C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void selectYes();
    void selectNo();
    void returnRoot();
    int getMessageNo(int index);
};

extern MaterielMenu_JISAN_DEL_MONSTER gMaterielMenu_JISAN_DEL_MONSTER;
