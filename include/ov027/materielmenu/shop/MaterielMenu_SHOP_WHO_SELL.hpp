#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// shop: choose whose items (or the sack) to sell
struct MaterielMenu_SHOP_WHO_SELL : menu::MenuBase {
    int endMessage_;                             // 0x1C
    char charaCount_;                            // 0x20
    menu::MenuItem menuItem_;               // 0x24
    CursorMoveGridLoop navigator_;       // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void selectSeller();
};

extern MaterielMenu_SHOP_WHO_SELL gMaterielMenu_SHOP_WHO_SELL;
