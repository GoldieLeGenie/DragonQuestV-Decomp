#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// casino prize exchange counter
struct MaterielMenu_CHANGEGIFT_ROOT : menu::MenuBase {
    enum CHANGEGIFT {
        CHANGEGIFT_FIRST = 0,
        CHANGEGIFT_CHECK = 1,
        CHANGEGIFT_CHANGE = 2,
        CHANGEGIFT_BACK = 3,
        CHANGEGIFT_SELECT = 4,
        CHANGEGIFT_END = 5,
    };

    char mode_;                             // 0x1C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    int getMessageNo(int index);
    void selectYes();
    void checkCoin();
};

extern MaterielMenu_CHANGEGIFT_ROOT gMaterielMenu_CHANGEGIFT_ROOT;
