#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// inn: price for the party, stay with fade out/in, revives the dead members
struct MaterielMenu_INN_ROOT : menu::MenuBase {
    enum INN_TYPE {
        TYPE_NORMAL = 0,
        TYPE_ARAKURE = 1,
        TYPE_SUGOROKU = 2,
    };
    enum INN_MODE {
        INN_BRACKOUT = 0,
        INN_CHECKMONEY = 1,
        INN_END_MAPCHANGE = 2,
        INN_END = 3,
    };
    enum FADE_MODE {
        FADE_OUT = 0,
        FADE_SOUND = 1,
        FADE_END = 2,
    };

    INN_TYPE innType_;                          // 0x1C  message column
    int isDrawMoney_;                                 // 0x20  draws the gold window
    short innCharge_;                           // 0x24
    char mode_;                                 // 0x26  INN_MODE
    char fadeMode_;                             // 0x27  FADE_MODE
    char extraInnType_;                         // 0x28

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void selectYes();
    void checkMoney();
    void fadeEffect();
    void showMessage(int mesIndex0, int mesIndex1);
    void revivalParty();
};

extern MaterielMenu_INN_ROOT gMaterielMenu_INN_ROOT;
