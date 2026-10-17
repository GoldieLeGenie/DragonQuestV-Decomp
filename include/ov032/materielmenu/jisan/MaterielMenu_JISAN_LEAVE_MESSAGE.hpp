#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// monster keeper: the chosen monster is left with the keeper
struct MaterielMenu_JISAN_LEAVE_MESSAGE : menu::MenuBase {
    enum {
        MODE_START = 0,
        MODE_DEATH = 1,
        MODE_LEAVE = 2,
        MODE_RETURN = 3,
        MODE_END = 4,
    };

    short activeCharaIndex_;                // 0x1C
    char mode_;                             // 0x1E
    char activeChara_;                      // 0x1F

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void returnMenuMessage();
    int getMessageNo(int index);
    void selectYes();
    void selectNo();
    void leaveMonster();
    void returnRoot();
};

extern MaterielMenu_JISAN_LEAVE_MESSAGE gMaterielMenu_JISAN_LEAVE_MESSAGE;
