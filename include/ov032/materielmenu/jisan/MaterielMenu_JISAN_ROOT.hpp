#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// monster keeper (jisan): leave / take back / status / part / rename / quit
struct MaterielMenu_JISAN_ROOT : menu::MenuBase {
    enum {
        MODE_START = 0,
        MODE_SELECT = 1,
        MODE_RETRY = 2,
        MODE_END = 3,
    };

    int changeMenu_;                        // 0x1C
    char mode_;                             // 0x20
    char active_;                           // 0x21
    menu::MenuItem menuItem_;               // 0x24
    UnkCursorMoveGridLoop navigator_;       // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setActiveMenu(char select);
    int getMes(int index);
    void openWaitMessage(int count, int mes1, int mes2, int mes3);
    void selectAzuke();
    void selectMukae();
    void selectYousu();
    void selectWakare();
    void selectNextMenu(bool next);
};

extern MaterielMenu_JISAN_ROOT gMaterielMenu_JISAN_ROOT;
