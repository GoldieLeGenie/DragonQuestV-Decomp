#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// shop: choose how many of a sack item to sell
struct UnkMaterielMenu_0218a5d0 : menu::MenuBase {
    int unk_1c;                             // 0x1C
    char quantity_;                         // 0x20
    menu::MenuItem menuItem_;               // 0x24
    UnkCursorMoveGridLoop navigator_;       // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_02188604(bool add);
};

extern UnkMaterielMenu_0218a5d0 data_ov019_021853a8;
