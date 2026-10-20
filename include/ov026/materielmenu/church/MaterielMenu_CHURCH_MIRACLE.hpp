#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// church: revival, antidote and curse removal for gold
struct MaterielMenu_CHURCH_MIRACLE : menu::MenuBase {
    enum MIRACLE_STATUS {
        MIRACLE_FIRST = -2,
        MIRACLE_NONE = -1,
        MIRACLE_CHECK = 0,
        MIRACLE_CHECKOK = 1,
        MIRACLE_CHECKNG = 2,
        MIRACLE_NG = 3,
        MIRACLE_ISEND = 4,
        MIRACLE_SOUND = 5,
        MIRACLE_SOUNDEND = 6,
        MIRACLE_END = 7,
    };
    enum HEAL_RESULT {
        HEAL_ENABLE = 0,
        HEAL_DISABLE = 1,
        HEAL_NEEDLESS = 2,
    };

    menu::MenuItem menuItem_;                   // 0x1C
    unsigned char unk_80[0x64];                 // 0x80
    CursorMoveGridLoop navigator_;           // 0xE4
    int miracle_;                               // 0xF0
    int activeChara_;                           // 0xF4
    MIRACLE_STATUS miracleStatus_;              // 0xF8
    int unk_fc;                                 // 0xFC  list opens when the message is shown
    int miracleAmount_[3];                      // 0x100
    int soundType_;                             // 0x10C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void execMiracle();
    void makePayment();
    bool messageUpdate();
    void calcCost();
    void selectUpdate();
    bool listUpdate();
    void selectRevival();
    void unkfunc_02186ec8();
    void selectAntidote();
    void selectAntiCurse();
    void selectGoldCheck();
    void selectCheckNG();
    void selectNG();
    HEAL_RESULT isMiracle(int index, int miracle);
    void payOutMiracle();
    void openRootMenu();
    int getMiracleMessageNo(int index);
    int getMessageNo(int index);
};

extern MaterielMenu_CHURCH_MIRACLE gMaterielMenu_CHURCH_MIRACLE;
