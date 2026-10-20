#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/CursorMoveGridLoop.hpp"

// town spell menu: selection of the target of a spell
struct TownMenu_MAGIC_CHARSELECT : menu::MenuBase {
    int isResult_;                              // 0x1C
    int isHealMessage_;                                 // 0x20  heal message pending
    int resultMes_[4];                          // 0x24
    short magicID_;                             // 0x34
    short updateHP_;                            // 0x36
    menu::MenuItem menuItem_;                   // 0x38
    CursorMoveGridLoop navigator_;           // 0x9C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void useMagic();
    int resultRebirth();
};

extern TownMenu_MAGIC_CHARSELECT gTownMenu_MAGIC_CHARSELECT;
