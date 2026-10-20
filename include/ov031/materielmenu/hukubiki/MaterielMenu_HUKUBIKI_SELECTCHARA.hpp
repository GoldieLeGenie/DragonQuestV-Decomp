#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// lottery (fukubiki): who receives the prize
struct MaterielMenu_HUKUBIKI_SELECTCHARA : menu::MenuBase {
    enum {
        MODE_NONE = 0,
        MODE_CHACK_1 = 1,
        MODE_CHACK_2 = 2,
        MODE_RETRY = 3,
        MODE_SORT = 4,
        MODE_SELECT_CHARA = 5,
        MODE_END = 6,
    };

    short prize_;                               // 0x1C
    short ticketCount_;                         // 0x1E
    char mode_;                                 // 0x20
    char partyCount_;                           // 0x21
    menu::MenuItem menuItem_;                   // 0x24
    CursorMoveGridLoop navigator_;           // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setPrize(short itemID);
    void selectYes();
    void selectNo();
    void selectChara();
    void haveMaxItem();
    void showGetPrizeMessage(int first);
    void showRetryMessage(int first, int second);
    void showMessage(int mes1, int mes2, int mes3, int mes4);
};

extern MaterielMenu_HUKUBIKI_SELECTCHARA gMaterielMenu_HUKUBIKI_SELECTCHARA;
