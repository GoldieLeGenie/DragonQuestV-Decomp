#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/status/ShopList.hpp"

// church: save, omen, revival, antidote, curse removal
struct MaterielMenu_CHURCH_ROOT : menu::MenuBase {
    enum MIRACLE_ORDER {
        MIRACLE_ORDER_REVIVAL = 0,
        MIRACLE_ORDER_ANTIDOTE = 1,
        MIRACLE_ORDER_ANTICURSE = 2,
    };

    static int sexType_;
    static int voiceType_;

    unsigned char unk_1c[0x64];                 // 0x1C
    menu::MenuItem menuItem_;                   // 0x80
    int activeCommand_;                         // 0xE4
    int unk_e8;                                 // 0xE8
    int timeType_;                              // 0xEC
    status::ShopList::ChurchType churchType_;   // 0xF0
    int commandNum_;                            // 0xF4
    int firstFlag_;                             // 0xF8
    int m_bOpen;                                // 0xFC
    CursorMoveGridLoop navigator_;           // 0x100

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    static void setupSexType();
    bool rootUpdate();
    bool commandUpdate();
    void selectEnd();
    void firstMessage();
    void oneMessage(int mes);
    static int getMessageNo(int index);
    static bool getSexType();
    static void setTalkSound();
};

extern MaterielMenu_CHURCH_ROOT gMaterielMenu_CHURCH_ROOT;
