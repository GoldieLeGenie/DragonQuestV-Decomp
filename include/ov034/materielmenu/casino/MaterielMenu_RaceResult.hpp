#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// slime race: payout of the bets and of the party slime prize
struct MaterielMenu_RaceResult : menu::MenuBase {
    enum RACE_MENU_MODE {
        MODE_RESULT = 0,
        MODE_LOSE = 1,
        MODE_BET_HIT = 2,
        MODE_SLIME_WIN = 3,
        MODE_SLIME_LOSE = 4,
        MODE_IS_LOOK = 5,
        MODE_IS_NEXT = 6,
        MODE_IS_NEXTSLIME = 7,
        MODE_TAKE_GOLD = 8,
        MODE_PAYOUT = 9,
        MODE_TAKE_COIN = 10,
        MODE_RACE = 11,
        MODE_CANCEL = 12,
        MODE_FANFARE = 13,
        MODE_END = 14,
    };

    RACE_MENU_MODE mode_;                       // 0x1C
    menu::MenuItem menuItem_;                   // 0x20
    int coin_;                                  // 0x84
    int gold_;                                  // 0x88
    int ranking_;                               // 0x8C
    int yesno_;                                 // 0x90
    int slime_;                                 // 0x94

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool messageUpdate();
    void commandUpdate();
    void checkResult();
    void checkSlimeResult();
    void checkNext();
    void setMessage(int mes1, int mes2);
    void setYesNoMessage(int mes1, int mes2);
    void execCoinAnim(unsigned int& coin, int& anim, bool plus);
};

extern MaterielMenu_RaceResult gMaterielMenu_RaceResult;
