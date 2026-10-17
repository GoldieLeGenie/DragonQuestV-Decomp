#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// Luida's bar: the chosen member leaves the party
struct MaterielMenu_LUIDA_LEAVE_MESSAGE : menu::MenuBase {
    enum {
        MODE_START = 0,
        MODE_LEAVE = 1,
        MODE_RETURN = 2,
        MODE_END = 3,
    };

    int unk_1c;                                 // 0x1C
    char mode_;                                 // 0x20
    char activeChara_;                          // 0x21
    char activeCharaIndex_;                     // 0x22

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void returnMenuMessage();
    int getMessageNo(int index);
    void selectYes();
    void selectNo();
    void leavePlayer();
    void returnRoot();
};

extern MaterielMenu_LUIDA_LEAVE_MESSAGE gMaterielMenu_LUIDA_LEAVE_MESSAGE;
