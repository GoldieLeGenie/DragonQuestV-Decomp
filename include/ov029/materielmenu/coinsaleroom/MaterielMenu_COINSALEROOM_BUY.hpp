#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// casino coin counter: price check and purchase of the chosen amount
struct MaterielMenu_COINSALEROOM_BUY : menu::MenuBase {
    enum BUY_MODE {
        MODE_LACKING = 0,
        MODE_OVER = 1,
        MODE_BUY = 2,
        MODE_END = 3,
    };

    int coin_;                                  // 0x1C
    unsigned char mode_;                        // 0x20  BUY_MODE

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setCoin(int coin);
    bool messageUpdata();
    void buyCoinMessage();
    void selectYes();
    void getCasinoCoin();
    void showMessage(int index1, int index2);
};

extern MaterielMenu_COINSALEROOM_BUY gMaterielMenu_COINSALEROOM_BUY;
