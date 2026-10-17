#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// lottery (fukubiki): tickets check, draw and prize message
struct MaterielMenu_HUKUBIKI_ROOT : menu::MenuBase {
    enum {
        HUKUBIKI_FIRST = 0,
        HUKUBIKI_START = 1,
        HUKUBIKI_DRAW = 2,
        HUKUBIKI_GET = 3,
        HUKUBIKI_NEXT = 4,
        HUKUBIKI_END = 5,
    };

    int retryHukubiki_;                         // 0x1C
    short ticketCount_;                         // 0x20
    short getPrize_;                            // 0x22
    char mode_;                                 // 0x24

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    short getTicket(bool sub);
    void setRetryHukubiki();
    void selectYes();
    void selectNo();
    void hukubikiUpdate();
    void setHukubikiPrize();
    void showMessage(int mes1, int mes2, int mes3);
};

extern MaterielMenu_HUKUBIKI_ROOT gMaterielMenu_HUKUBIKI_ROOT;
