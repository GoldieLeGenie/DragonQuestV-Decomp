#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// Luida's bar: add / leave / list / quit
struct MaterielMenu_LUIDA_ROOT : menu::MenuBase {
    enum {
        MODE_START = 0,
        MODE_OPEN_DRAW = 1,
        MODE_OPEN = 2,
        MODE_SELECT = 3,
        MODE_CHANGE_MENU = 4,
        MODE_RETURN = 5,
        MODE_END = 6,
    };

    int unk_1c;                                 // 0x1C  submenu opens when the message is closed
    char mode_;                                 // 0x20
    char active_;                           // 0x21
    menu::MenuItem menuItem_;                   // 0x24
    UnkCursorMoveGridLoop navigator_;           // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setActiveMenu(char active);
    void selectKuwaeru();
    void selectAzuke();
    void selectList();
    void selectYameru();
    int getMessageNo(int index);
    void openMessage(int mes1, int mes2);
};

extern MaterielMenu_LUIDA_ROOT gMaterielMenu_LUIDA_ROOT;
