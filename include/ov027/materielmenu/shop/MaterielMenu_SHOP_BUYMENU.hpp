#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// shop: choose the item (and quantity) to buy
struct MaterielMenu_SHOP_BUYMENU : menu::MenuBase {
    enum BUYMENU_MODE {
        MODE_SELECT = 0,
        MODE_NEXT = 1,
        MODE_RETURN = 2,
    };

    menu::MenuItem menuItem_;                   // 0x1C
    int unk_80;                                 // 0x80
    char mode_;                                 // 0x84
    UnkCursorMoveGridLoop navigator_;           // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void checkBuy();
    void unkfunc_02186c58(bool add);
};

extern MaterielMenu_SHOP_BUYMENU gMaterielMenu_SHOP_BUYMENU;
