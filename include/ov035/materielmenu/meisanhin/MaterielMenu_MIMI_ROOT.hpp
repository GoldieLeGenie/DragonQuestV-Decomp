#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// museum memo/hints: list of the specialties
struct MaterielMenu_MIMI_ROOT : menu::MenuBase {
    enum MIMI_MODE {
        MODE_MEMO = 0,
        MODE_HINT = 1,
    };

    menu::MenuItem menuItem_;                   // 0x1C
    CursorMoveGridLoop navigator_;           // 0x80
    MIMI_MODE mode_;                            // 0x8C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setMimiMode(MIMI_MODE mode);
    bool checkHaveMeisan(int active);
    void openMimiMessage();
};

extern MaterielMenu_MIMI_ROOT gMaterielMenu_MIMI_ROOT;
