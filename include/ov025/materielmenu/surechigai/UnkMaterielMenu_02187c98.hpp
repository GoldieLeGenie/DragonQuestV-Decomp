#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// passing communication: root menu
struct UnkMaterielMenu_02187c98 : menu::MenuBase {
    signed char mode_;                          // 0x1C
    int unk_20;                                 // 0x20  first message
    menu::MenuItem menuItem_;                   // 0x24
    CursorMoveGridLoop navigator_;           // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_02187278();
    void unkfunc_02187310();
    void selectCommand();
};

extern UnkMaterielMenu_02187c98 data_ov019_02184d4c;
