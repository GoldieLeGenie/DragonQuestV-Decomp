#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// poker: double-up (high and low) menu (overlay 12)
struct MaterielMenu_POKER_HIGHANDLOW : menu::MenuBase {
    int m_pos;                                  // 0x1C cards to animate
    int m_win;                                  // 0x20
    int m_isPlaySound;                          // 0x24
    int m_haveCoin;                             // 0x28
    int m_getCoin;                              // 0x2C
    short m_doubleupCount;                      // 0x30
    char m_mode;                                // 0x32
    menu::MenuItem menuItem_;                   // 0x34
    CursorMoveGridLoop navigator_;           // 0x98

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool messageUpdate();
    void statusUpdate();
    void selectYes();
    void selectNo();
    void judgementHiAndLow();
    void showMessage(int messageID, int messageID2);
    void getCoinAction();
    void actionFade();
    void actionSwing();
    void actionMove();
    void setCardTex(int card, bool base);
    void setSoundNo();
};

extern MaterielMenu_POKER_HIGHANDLOW gMaterielMenu_POKER_HIGHANDLOW;
