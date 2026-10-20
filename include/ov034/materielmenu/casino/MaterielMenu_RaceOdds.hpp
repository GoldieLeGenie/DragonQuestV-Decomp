#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// slime race: odds table and bets
struct MaterielMenu_RaceOdds : menu::MenuBase {
    enum RACE_ODDS_MODE {
        MODE_STANDBY = 0,
        MODE_READY = 1,
        MODE_START = 2,
        MODE_RESULT = 3,
        MODE_ESCAPE = 4,
        MODE_END = 5,
    };

    int maxToken_;                              // 0x1C
    int menuItemY_;                             // 0x20
    int uniqueItem_;                            // 0x24
    int unk_28;                                 // 0x28  held button: 1 bet, 2 back
    int unk_2c;                                 // 0x2C  held button frame counter
    menu::MenuItem menuItem_;                   // 0x30
    CursorMoveGridLoop navigator_;           // 0x94
    RACE_ODDS_MODE mode_;                       // 0xA0
    int unk_a4;                                 // 0xA4

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void commandUpdate();
    void unkfunc_02186cd8(int active, int result);
    bool unkfunc_02186d18();
    bool betCoin();
    bool backCoin();
    bool unkfunc_02186e28();
};

extern MaterielMenu_RaceOdds gMaterielMenu_RaceOdds;
