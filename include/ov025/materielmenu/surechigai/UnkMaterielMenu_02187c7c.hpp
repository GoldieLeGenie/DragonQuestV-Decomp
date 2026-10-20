#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// passing communication: envoy production and price
struct UnkMaterielMenu_02187c7c : menu::MenuBase {
    short unk_1c;                               // 0x1C  envoy icon
    signed char mode_;                          // 0x1E
    int unk_20;                                 // 0x20  price
    int unk_24;                                 // 0x24
    int unk_28;                                 // 0x28  screen offset set
    menu::MenuItem menuItem_;                   // 0x2C
    CursorMoveGridLoop navigator_;           // 0x90

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_021870ac();
};

extern UnkMaterielMenu_02187c7c data_ov019_02185900;
