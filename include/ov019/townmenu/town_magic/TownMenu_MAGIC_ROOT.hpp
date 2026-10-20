#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/CursorMoveGridLoop.hpp"

// town spell menu: spell list of the caster
struct TownMenu_MAGIC_ROOT : menu::MenuBase {
    int isResult_;                              // 0x1C
    short magicID_;                             // 0x20
    char targetCount_;                          // 0x22
    char soundCount_;                           // 0x23
    menu::MenuItem menuItem_;                   // 0x24
    CursorMoveGridLoop navigator_;           // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void useMagic();
    void useMoveMagic();
    void useMagicNoTarget();
    bool resultMagic();
};

extern TownMenu_MAGIC_ROOT gTownMenu_MAGIC_ROOT;
