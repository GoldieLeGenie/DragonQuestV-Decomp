#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// passing communication: envoy object choice
struct UnkMaterielMenu_02187cb4 : menu::MenuBase {
    signed char mode_;                          // 0x1C
    int isFirstMessage_;                                 // 0x20  first message
    int isCancelEnable_;                                 // 0x24  cancel allowed
    menu::MenuItem menuItem_;                   // 0x28
    CursorMoveGridLoop navigator_;           // 0x8C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

extern UnkMaterielMenu_02187cb4 data_ov019_021854d4;
