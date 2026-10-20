#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/CursorMoveGridLoop.hpp"

// town item menu: command selection for an item (use, give, throw, equip, show)
struct TownMenuItemSelectCommand : menu::MenuBase {
    short itemID_;                              // 0x1C
    short activeChara_;                         // 0x1E
    char commandFlag_;                          // 0x20
    char throwType_;                            // 0x21  step of the throw away messages
    menu::MenuItem menuItem_;                   // 0x24
    CursorMoveGridLoop navigator_;           // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void judgeUseItem();
    void judgeEquipItem();
    void setItemShowAction();
    void judgeThrowItem();
    int unkfunc_0216fb40();
    void closeMenuCheck();
    bool checkSeinenStart();
};

extern TownMenuItemSelectCommand gTownMenuItemSelectCommand;
