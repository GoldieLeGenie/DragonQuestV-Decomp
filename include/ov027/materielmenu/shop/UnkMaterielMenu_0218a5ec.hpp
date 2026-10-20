#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// shop: choose the sack item to sell
struct UnkMaterielMenu_0218a5ec : menu::MenuBase {
    menu::MenuItem menuItem_;               // 0x1C
    CursorMoveGridLoop navigator_;       // 0x80

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void selectSellItem();
};

extern UnkMaterielMenu_0218a5ec data_ov019_021843c0;
