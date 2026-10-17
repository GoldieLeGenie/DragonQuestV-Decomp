#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// medal king: equip the prize right away
struct MaterielMenu_MEDALKING_EQUIP : menu::MenuBase {
    enum MENU_MODE {
        MODE_CHECK = 0,
        MODE_EQUIP = 1,
        MODE_NOEQUIP = 2,
        MODE_EQUIPEND = 3,
        MODE_CANCEL = 4,
        MODE_END = 5,
    };

    char m_mode;                            // 0x1C
    short m_equipItem;                      // 0x1E

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void selectYes();
    void selectNo();
    void selectReturnMessage();
};

extern MaterielMenu_MEDALKING_EQUIP gMaterielMenu_MEDALKING_EQUIP;
