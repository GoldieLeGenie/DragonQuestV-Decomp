#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// shop: choose who gets the bought item
struct MaterielMenu_SHOP_WHOSE : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    int endMessage_;                                 // 0x80  message shown when returning to the shop menu
    char activeItem_;                           // 0x84
    char mode_;                                 // 0x85
    CursorMoveGridLoop navigator_;           // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void haveMaxCheck();
    void selectYes();
    void selectNo();
    void yesSort();
    void checkMoney();
    void giveBuyItem();
    void showMessage(int mes1, int mes2);
    int getPortSelmiMes();
};

extern MaterielMenu_SHOP_WHOSE gMaterielMenu_SHOP_WHOSE;
