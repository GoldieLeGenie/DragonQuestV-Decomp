#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// bank: withdraw money
struct MaterielMenu_BANK_DRAW : menu::MenuBase {
    enum DRAW_MODE {
        DRAW_START = 0,
        DRAW_SELECT = 1,
        DRAW_END = 2,
    };

    menu::MenuItem menuItem_;                   // 0x1C
    CursorMoveGridLoop navigator_;           // 0x80
    int bankMoney_;                             // 0x8C
    int drawMoney_;                             // 0x90
    char mode_;                                 // 0x94

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool messageUpdate();
    void bankUpdate();
    void bankDraw();
    void cancelDrawfrom();
    void showMessage(int index1, int index2);
};

extern MaterielMenu_BANK_DRAW gMaterielMenu_BANK_DRAW;
