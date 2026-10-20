#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// casino coin counter: amount selection (one cursor per digit)
struct MaterielMenu_COINSALEROOM_ROOT : menu::MenuBase {
    enum BUY_COIN_MODE {
        MODE_FIRST = 0,
        MODE_BACK = 1,
        MODE_SELECT = 2,
        MODE_END = 3,
    };

    menu::MenuItem menuItem_;                   // 0x1C
    CursorMoveGridLoop navigator_;           // 0x80
    int blink_;                                 // 0x8C  blinks the cursor
    int coin_;                                  // 0x90
    unsigned char blinkCount_;                       // 0x94  blink frame counter
    unsigned char mode_;                        // 0x95  BUY_COIN_MODE

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setMode(char mode);
    bool messageUpdata();
    void buyCoinUpdata();
    void showMessage(int index1, int index2, int index3);
};

extern MaterielMenu_COINSALEROOM_ROOT gMaterielMenu_COINSALEROOM_ROOT;
