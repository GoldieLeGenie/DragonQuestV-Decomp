#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// town item menu: gives an item to another character (or the bag) and shows the result
struct TownMenu_ITEM_CHECKTARGET : menu::MenuBase {
    int isSpace_;                               // 0x1C  the target has a free item slot
    int activeFukuro_;                          // 0x20
    int targetFukuro_;                          // 0x24
    short targetItem_;                          // 0x28
    short changeItemID_;                        // 0x2A
    short activeItem_;                          // 0x2C
    unsigned char toActiveChara_;               // 0x2E
    unsigned char fromActiveChara_;             // 0x2F

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    unsigned int checkGiveFlag();
    void changeItem(unsigned int flag);
    void setTargetItem();
    void closeMenuCheck();
};

extern TownMenu_ITEM_CHECKTARGET gTownMenu_ITEM_CHECKTARGET;
