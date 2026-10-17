#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// casino prize exchange: choose the prize
struct MaterielMenu_CHANGEGIFT_SELECTGIFT : menu::MenuBase {
    enum SELECT_MODE {
        MODE_MESSAGE = 0,
        MODE_SELECT = 1,
        MODE_NONE = 2,
    };

    menu::MenuItem menuItem_;               // 0x1C
    UnkCursorMoveGridLoop navigator_;       // 0x80
    char itemCount_;                        // 0x8C
    char mode_;                             // 0x8D

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void checkAmount();
    void cancelChange();
};

extern MaterielMenu_CHANGEGIFT_SELECTGIFT gMaterielMenu_CHANGEGIFT_SELECTGIFT;
