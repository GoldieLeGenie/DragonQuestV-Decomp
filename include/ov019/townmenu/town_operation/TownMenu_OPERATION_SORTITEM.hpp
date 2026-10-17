#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/UnkCursorMoveGridLoop.hpp"

// town misc menu: item sorting
struct TownMenu_OPERATION_SORTITEM : menu::MenuBase {
    enum SORT_MODE {
        SORT_SACK = 0,
        SORT_ITEM = 1,
        SORT_END = 2,
    };

    short m_selectPlayer[9];                    // 0x1C
    char m_selectPlayerCount;                   // 0x2E
    char m_mode;                                // 0x2F
    menu::MenuItem menuItem_;                   // 0x30
    UnkCursorMoveGridLoop navigator_;           // 0x94

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setSortMode(SORT_MODE mode);
    void boxUpSack();
    void boxUpItem();
};

extern TownMenu_OPERATION_SORTITEM gTownMenu_OPERATION_SORTITEM;
