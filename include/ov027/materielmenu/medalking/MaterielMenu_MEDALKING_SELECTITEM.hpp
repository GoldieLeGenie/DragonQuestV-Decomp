#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// medal king: choose the prize
struct MaterielMenu_MEDALKING_SELECTITEM : menu::MenuBase {
    enum MENU_MODE {
        MODE_ITEM_SELECT = 0,
        MODE_YESNO = 1,
        MODE_NEXT = 2,
        MODE_END = 3,
    };

    char m_mode;                            // 0x1C
    menu::MenuItem menuItem_;               // 0x20
    CursorMoveGridLoop navigator_;       // 0x84

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

extern MaterielMenu_MEDALKING_SELECTITEM gMaterielMenu_MEDALKING_SELECTITEM;
