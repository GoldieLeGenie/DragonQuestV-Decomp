#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// bank: deposit / withdraw / quit
struct MaterielMenu_BANK_ROOT : menu::MenuBase {
    enum ROOT_MODE {
        ROOT_START = 0,
        ROOT_MESSAGE = 1,
        ROOT_SELECT = 2,
        ROOT_END = 3,
    };

    menu::MenuItem menuItem_;                   // 0x1C
    CursorMoveGridLoop navigator_;           // 0x80
    char m_state;                               // 0x8C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void closeBank();
    int getMessageNo(int index);
};

extern MaterielMenu_BANK_ROOT gMaterielMenu_BANK_ROOT;
