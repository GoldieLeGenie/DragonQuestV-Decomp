#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// shop: choose whose items (or the sack) to sell
struct MaterielMenu_SHOP_WHO_SELL : menu::MenuBase {
    int unk_1c;                             // 0x1C
    char unk_20;                            // 0x20
    menu::MenuItem menuItem_;               // 0x24
    UnkCursorMoveGridLoop navigator_;       // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_0218910c();
};

extern MaterielMenu_SHOP_WHO_SELL gMaterielMenu_SHOP_WHO_SELL;
