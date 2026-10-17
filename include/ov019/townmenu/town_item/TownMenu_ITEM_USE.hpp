#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/UnkCursorMoveGridLoop.hpp"

namespace status {
    struct UseActionParam;
}

// town item menu: selection of the target of an item
struct TownMenu_ITEM_USE : menu::MenuBase {
    int activeFukuro_;                          // 0x1C
    int unk_20;                                 // 0x20  the item list became empty
    int isResult_;                              // 0x24
    int unk_28;                                 // 0x28  heal message pending
    int resultMes_[4];                          // 0x2C
    short itemID_;                              // 0x3C
    short activeItem_;                          // 0x3E
    short updateHP_;                            // 0x40
    short updateMP_;                            // 0x42
    char activeChara_;                          // 0x44
    menu::MenuItem menuItem_;                   // 0x48
    UnkCursorMoveGridLoop navigator_;           // 0xAC

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setActiveChara();
    void itemUse();
    bool checkUseCharaAlive(int target);
    bool useHealItem();
    void openHealMessage();
    void setUseItemMessage(status::UseActionParam& useActionParam, int* useMes, int* resultMes, short itemID);
};

extern TownMenu_ITEM_USE gTownMenu_ITEM_USE;
