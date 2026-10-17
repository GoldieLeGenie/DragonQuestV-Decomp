#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/UnkCursorMoveGridLoop.hpp"

// town misc menu: party order
struct TownMenu_OPERATION_SHIFT_PARTY : menu::MenuBase {
    int carriageEnable_;                        // 0x1C
    int enableEnter_;                           // 0x20
    char selectChara_[8];                       // 0x24  members that can be ordered
    char selectCharaAllocation_[4];             // 0x2C
    char npcPosition_;                          // 0x30
    unsigned char selectCharaMaxCount_;         // 0x31
    unsigned char shiftPartyCharaCount_;        // 0x32
    menu::MenuItem menuItem_;                   // 0x34
    UnkCursorMoveGridLoop navigator_;           // 0x98

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_02176b1c();
    void chengeChara();
};

extern TownMenu_OPERATION_SHIFT_PARTY gTownMenu_OPERATION_SHIFT_PARTY;
