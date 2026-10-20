#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/CursorMoveGridLoop.hpp"

// town misc menu: tactics of the party members
struct TownMenu_OPERATION_TACTICS : menu::MenuBase {
    char playerList_[10];                       // 0x1C  -1 terminated
    unsigned char mode_;                        // 0x26  0: character selection, 1: tactics selection
    unsigned char prevMode_;                    // 0x27
    unsigned char charaCount_;                  // 0x28
    menu::MenuItem tacticsItem_;                // 0x2C
    menu::MenuItem charaItem_;                  // 0x90
    CursorMoveGridLoop navigator_;           // 0xF4

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void loadActiveTactics();
    void applyTactics();
};

extern TownMenu_OPERATION_TACTICS gTownMenu_OPERATION_TACTICS;
