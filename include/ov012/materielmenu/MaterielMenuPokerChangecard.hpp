#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/dss/DssUtils.hpp"

// poker: card change menu (overlay 12)
struct MaterielMenuPokerChangecard : menu::MenuBase {
    int reverse_;                               // 0x1C
    int unk_20;                                 // 0x20 won: draw the won coins
    int change_[5];                             // 0x24 held cards
    int isPlaySound_;                           // 0x38
    int betCoin_;                               // 0x3C
    int getCoin_;                               // 0x40
    int haveCoin_;                              // 0x44
    char gameMode_;                             // 0x48
    char combination_;                          // 0x49
    char effectCount_;                          // 0x4A
    dss::Fix32 distance_;                       // 0x4C
    int animation_;                             // 0x50
    int gyre_;                                  // 0x54
    int index_;                                 // 0x58
    unsigned short ang_;                        // 0x5C
    menu::MenuItem menuItem_;                   // 0x60 cards
    menu::MenuItem dealItem_;                   // 0xC4 deal button
    CursorMoveGridLoop navigator_128;        // 0x128
    CursorMoveGridLoop navigator_134;        // 0x134

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool messageUpdata();
    void menuUpdata();
    void changeCard();
    void showMessage(int messageID, int messageID2);
    void pokerDealCard();
    void pokerChangeCard();
    void pokerReverseCard(bool flag);
    void pokerFadeAnimation();
    void setSoundNo();
    void unkfunc_0212bab0();
    void unkfunc_0212baf0();
    void unkfunc_0212bb74();
    void unkfunc_0212bc70();
};

extern MaterielMenuPokerChangecard gMaterielMenu_POKER_CHANGECARD;
