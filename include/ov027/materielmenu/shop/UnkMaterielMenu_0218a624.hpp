#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// shop: choose the item of a party member to sell
struct UnkMaterielMenu_0218a624 : menu::MenuBase {
    menu::MenuItem menuItem_;               // 0x1C
    UnkCursorMoveGridLoop navigator_;       // 0x80

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

extern UnkMaterielMenu_0218a624 data_ov019_0218421c;
