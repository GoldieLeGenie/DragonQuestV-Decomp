#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// casino prize exchange: give the prize and offer to equip it
struct MaterielMenu_CHANGEGIFT_EQUIPCHECK : menu::MenuBase {
    enum EQUIPCHECK_MODE {
        ITEM_NORMAL = 0,
        ITEM_HAVEMAX = 1,
        ITEM_EQUIP = 2,
        ITEM_NOEQUIP = 3,
        ITEM_SORT = 4,
        ITEM_RETURN_CHARA = 5,
        ITEM_RETURN_ITEM = 6,
        ITEM_COIN_CHECK = 7,
        ITEM_END = 8,
    };

    int fukuro_;                            // 0x1C
    char activeChara_;                      // 0x20
    short itemID_;                          // 0x22
    char mode_;                             // 0x24

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void checkTarget();
    void selectYes();
    void selectNo();
    void aliveCheck();
    void getGift();
    void checkEquipItem();
    void openMessage(int mes1, int mes2);
};

extern MaterielMenu_CHANGEGIFT_EQUIPCHECK gMaterielMenu_CHANGEGIFT_EQUIPCHECK;
