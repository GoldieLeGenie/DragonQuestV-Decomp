#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// medal king: choose who gets the prize
struct MaterielMenu_MEDALKING_SELECTCHARA : menu::MenuBase {
    enum MENU_MODE {
        MODE_SELECT_CHARA = 0,
        MODE_NEXT = 1,
        MODE_SORT = 2,
        MODE_RETURN = 3,
        MODE_CANCEL = 4,
        MODE_END = 5,
    };

    char m_mode;                            // 0x1C
    menu::MenuItem menuItem_;               // 0x20
    UnkCursorMoveGridLoop navigator_;       // 0x84

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void selectYes();
    void selectNo();
    void selectReturnMessage();
};

extern MaterielMenu_MEDALKING_SELECTCHARA gMaterielMenu_MEDALKING_SELECTCHARA;
