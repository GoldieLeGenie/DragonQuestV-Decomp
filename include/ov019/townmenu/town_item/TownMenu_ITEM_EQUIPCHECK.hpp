#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// town item menu: proposes to equip an item that was just given
struct TownMenu_ITEM_EQUIPCHECK : menu::MenuBase {
    short itemID_;                              // 0x1C
    short targetItem_;                          // 0x1E
    unsigned char mode_;                        // 0x20
    unsigned char target_;                      // 0x21

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void equipItem();
    void openItemRoot();
};

extern TownMenu_ITEM_EQUIPCHECK gTownMenu_ITEM_EQUIPCHECK;
