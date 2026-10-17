#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// slime touch result: ranking message and prize items
struct MaterielMenu_TouchResult : menu::MenuBase {
    enum TOUCH_RESULT_MODE {
        MODE_RESULT = 0,
        MODE_RANK_IN = 1,
        MODE_RANK_OUT = 2,
        MODE_GIFT = 3,
        MODE_GIFTCHECK = 4,
        MODE_END = 5,
    };

    TOUCH_RESULT_MODE mode_;                    // 0x1C
    int rankIn_;                                // 0x20
    int itemGet_;                               // 0x24
    int itemCount_;                             // 0x28

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void commandUpdate();
    bool messageUpdate();
};

extern MaterielMenu_TouchResult gMaterielMenu_TouchResult;
