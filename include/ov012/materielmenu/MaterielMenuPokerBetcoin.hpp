#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// poker: coin bet menu (overlay 12)
struct MaterielMenuPokerBetcoin : menu::MenuBase {
    int blink_;                                 // 0x1C
    char messageMode_;                          // 0x20
    char blinkCount_;                           // 0x21
    menu::MenuItem menuItem_;                   // 0x24
    UnkCursorMoveGridLoop navigator_;           // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    int unkfunc_0212b1bc();
    void unkfunc_0212b33c();
    void unkfunc_0212b380();
};

extern MaterielMenuPokerBetcoin gMaterielMenu_POKER_BETCOIN;
