#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// Luida's bar: status of the party members
struct MaterielMenu_LUIDA_STATUS : menu::MenuBase {
    char mode_;                                 // 0x1C
    menu::MenuItem menuItem_;                   // 0x20
    CursorMoveGridLoop navigator_;           // 0x84

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    int getMessageNo(int index);
    void unkfunc_02186b1c();
    void returnRoot();
};

extern MaterielMenu_LUIDA_STATUS gMaterielMenu_LUIDA_STATUS;
