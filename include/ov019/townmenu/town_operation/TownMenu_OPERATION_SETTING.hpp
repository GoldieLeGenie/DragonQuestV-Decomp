#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/UnkCursorMoveGridLoop.hpp"

// town misc menu: settings (music volume, sound effect volume, battle speed)
struct TownMenu_OPERATION_SETTING : menu::MenuBase {
    unsigned char prevMode_;                    // 0x1C
    unsigned char mode_;                        // 0x1D  0: battle speed, 1: music volume, 2: sound effect volume
    menu::MenuItem bgmItem_;                    // 0x20
    menu::MenuItem seItem_;                     // 0x84
    menu::MenuItem battleItem_;                 // 0xE8
    UnkCursorMoveGridLoop navigator_;           // 0x14C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_02176750();
    bool unkfunc_0217677c(menu::MenuItem* menuItem, int mode);
    void unkfunc_02176840();
};

extern TownMenu_OPERATION_SETTING gTownMenu_OPERATION_SETTING;
