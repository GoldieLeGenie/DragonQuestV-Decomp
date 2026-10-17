#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// shop: equip the bought weapon / armour right away
struct MaterielMenu_SHOP_EQUIPCHECK : menu::MenuBase {
    int haveItemOver_;                          // 0x1C
    int getItemFlag_;                           // 0x20
    char mode_;                                 // 0x24
    char ctrlID_;                               // 0x25

    virtual void menuSetup();
    virtual void menuUpdate();
    void yesAdmin();
    void noAdmin();
    void giveItem();
    void messageSetup();
    void showMessage(int mes);
    void returnRoot();
    void checkMoneyMessage(int* mes, int mesCount, int haveNoMoney);
};

extern MaterielMenu_SHOP_EQUIPCHECK gMaterielMenu_SHOP_EQUIPCHECK;
