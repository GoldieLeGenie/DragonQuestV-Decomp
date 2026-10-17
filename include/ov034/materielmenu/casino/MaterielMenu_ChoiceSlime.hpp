#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// slime race: choice of the party slime
struct MaterielMenu_ChoiceSlime : menu::MenuBase {
    enum RACE_MENU_MODE {
        MODE_START_MSG = 0,
        MODE_RESTART = 1,
        MODE_SELECT = 2,
        MODE_NOT_SLIME = 3,
        MODE_CHILD_SLIME = 4,
        MODE_TIRED_SLIME = 5,
        MODE_IS_ACCEPT = 6,
        MODE_ACCEPT = 7,
        MODE_NOT_MONEY = 8,
        MODE_NOT_COIN = 9,
        MODE_LOOK_ONLY = 10,
        MODE_IN_RACE = 11,
        MODE_RACE = 12,
        MODE_CANCEL = 13,
        MODE_END = 14,
    };

    RACE_MENU_MODE mode_;                       // 0x1C
    menu::MenuItem menuItem_;                   // 0x20
    int yesno_;                                 // 0x84
    int charaNum_;                              // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool messageUpdate();
    void commandUpdate();
    void selectUpdate();
    void checkSlime();
    void raceStart();
    void setMessage(int mes1, int mes2);
    void setYesNoMessage(int mes1, int mes2);
};

extern MaterielMenu_ChoiceSlime gMaterielMenu_ChoiceSlime;
