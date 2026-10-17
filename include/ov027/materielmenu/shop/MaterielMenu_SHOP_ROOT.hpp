#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// shop: buy / sell / quit
struct MaterielMenu_SHOP_ROOT : menu::MenuBase {
    enum SHOP_MODE {
        SHOP_START = 0,
        SHOP_MESWAIT = 1,
        SHOP_SELECT = 2,
        SHOP_NEXT = 3,
        SHOP_END = 4,
    };
    enum PLAYER_ACTION {
        BUY_ITEM = 0,
        SELL_ITEM = 1,
        CANCEL_ITEM = 2,
    };

    char mode_;                                 // 0x1C
    menu::MenuItem menuItem_;                   // 0x20
    UnkCursorMoveGridLoop navigator_;           // 0x84

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void execConduct();
    void showMessage(int mes);
};

extern MaterielMenu_SHOP_ROOT gMaterielMenu_SHOP_ROOT;
