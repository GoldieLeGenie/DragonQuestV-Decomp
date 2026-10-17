#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// medal king: medal count and prize exchange
struct MaterielMenu_MEDALKING_ROOT : menu::MenuBase {
    enum MENU_MODE {
        MODE_START = 0,
        MODE_SELECT = 1,
        MODE_NEXT = 2,
        MODE_END = 3,
    };

    char m_mode;                            // 0x1C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

extern MaterielMenu_MEDALKING_ROOT gMaterielMenu_MEDALKING_ROOT;
