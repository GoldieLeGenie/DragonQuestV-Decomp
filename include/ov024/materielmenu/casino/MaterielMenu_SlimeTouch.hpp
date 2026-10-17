#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// slime touch game counter: start, ranking, tutorial
struct MaterielMenu_SlimeTouch : menu::MenuBase {
    enum TOUCH_MENU_MODE {
        MODE_START = 0,
        MODE_RESTART = 1,
        MODE_SELECT = 2,
        MODE_TUTORIAL = 3,
        MODE_NOTRANKIN = 4,
        MODE_RANKING = 5,
        MODE_END = 6,
    };
    enum {
        SELECT_START = 0,
        SELECT_RANKING = 1,
        SELECT_TUTORIAL = 2,
        SELECT_END = 3,
    };

    menu::MenuItem menuItem_;                   // 0x1C
    TOUCH_MENU_MODE mode_;                      // 0x80

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool messageUpdate();
    void commandUpdate();
    void selectUpdate();
    void okUpdate();
};

extern MaterielMenu_SlimeTouch gMaterielMenu_SlimeTouch;
