#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// party chat window (talk to the party members)
struct TownMenu_PARTY_TALK : menu::MenuBase {
    char mode_;                                 // 0x1C  1: yes/no question, 2: last messages

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setMacroTeaSet();
};

extern TownMenu_PARTY_TALK gTownMenu_PARTY_TALK;
