#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// bank: deposit money
struct MaterielMenu_BANK_PUTIN : menu::MenuBase {
    enum PUTIN_MODE {
        PUTIN_START = 0,
        PUTIN_SELECT = 1,
        PUTIN_MAX = 2,
        PUTIN_END = 3,
    };

    menu::MenuItem menuItem_;                   // 0x1C
    UnkCursorMoveGridLoop navigator_;           // 0x80
    int bankMoney_;                             // 0x8C
    int putinMoney_;                            // 0x90
    char mode_;                                 // 0x94

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool messageUpdate();
    void bankUpdate();
    void bankPutin();
    void cancelPutin();
    void showMessage(int index1, int index2);
};

extern MaterielMenu_BANK_PUTIN gMaterielMenu_BANK_PUTIN;
