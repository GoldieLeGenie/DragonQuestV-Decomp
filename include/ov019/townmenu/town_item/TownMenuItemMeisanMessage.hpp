#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// town item menu: use of an item on a museum pedestal
struct TownMenuItemMeisanMessage : menu::MenuBase {
    int m_isPlaySound;                          // 0x1C
    int m_daizaUid;                             // 0x20
    int m_message;                              // 0x24
    short m_daizaItem;                          // 0x28
    short m_useItem;                            // 0x2A
    menu::MenuItem menuItem_;                   // 0x2C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setUseItem(short item);
    int getRecordNo();
};

extern TownMenuItemMeisanMessage gTownMenuItemMeisanMessage;
