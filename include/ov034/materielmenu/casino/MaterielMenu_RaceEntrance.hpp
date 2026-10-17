#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// slime race: entrance counter (bet, own slime, explanation)
struct MaterielMenu_RaceEntrance : menu::MenuBase {
    enum RACE_MENU_MODE {
        MODE_START_MSG = 0,
        MODE_RESTART = 1,
        MODE_SELECT = 2,
        MODE_NOT_HAVECOIN = 3,
        MODE_NOT_HAVEGOLD = 4,
        MODE_CHOICE_SLIME = 5,
        MODE_NOT_SLIME = 6,
        MODE_IN_RACE = 7,
        MODE_RACE = 8,
        MODE_RESULT = 9,
        MODE_TUTORIAL = 10,
        MODE_CANCEL = 11,
        MODE_END = 12,
    };

    RACE_MENU_MODE mode_;                       // 0x1C
    menu::MenuItem menuItem_;                   // 0x20

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool messageUpdate();
    void commandUpdate();
    void selectUpdate();
    void raceStart();
    bool isEnableSlime();
};

extern MaterielMenu_RaceEntrance gMaterielMenu_RaceEntrance;
