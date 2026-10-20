#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// monster keeper: a monster must be left when a new one joins a full party (script)
struct MaterielMenu_JISAN_LEAVE_SCRIPT : menu::MenuBase {
    enum MENU_MODE {
        MODE_SELECT = 0,
        MODE_YESNO = 1,
        MODE_RETRY = 2,
        MODE_END = 3,
    };

    int party_[8];                          // 0x1C
    short addMonster_;                      // 0x3C
    char mode_;                             // 0x3E
    char monsterCount_;                     // 0x3F
    menu::MenuItem menuItem_;               // 0x40
    CursorMoveGridLoop navigator_;       // 0xA4

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    int getFriendMonsterName();
};

extern MaterielMenu_JISAN_LEAVE_SCRIPT gMaterielMenu_JISAN_LEAVE_SCRIPT;
