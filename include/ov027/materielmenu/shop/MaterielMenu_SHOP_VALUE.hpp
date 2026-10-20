#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// shop: sale price of the chosen item and confirmation
struct MaterielMenu_SHOP_VALUE : menu::MenuBase {
    int fukuro_;                            // 0x1C
    int isEndMessage_;                             // 0x20
    int endMessage_;                             // 0x24
    short activeItem_;                      // 0x28
    char activeChara_;                      // 0x2A
    char sellType_;                         // 0x2B
    char page_;                             // 0x2C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void selectYes();
    void selectNo();
    void checkHaveMoney();
    void showMessage(int mes1, int mes2, int mes3);
};

extern MaterielMenu_SHOP_VALUE gMaterielMenu_SHOP_VALUE;
