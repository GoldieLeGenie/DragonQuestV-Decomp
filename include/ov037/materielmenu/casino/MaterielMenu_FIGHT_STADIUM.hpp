#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// monster arena counter: monster choice, bet, battle and result
struct MaterielMenu_FIGHT_STADIUM : menu::MenuBase {
    enum FIGHT_STADIUM_STATUS {
        FIGHT_STADIUM_START = 0,
        FIGHT_STADIUM_CHOICE = 1,
        FIGHT_STADIUM_CHECK = 2,
        FIGHT_STADIUM_BET = 3,
        FIGHT_STADIUM_BATTLE = 4,
        FIGHT_STADIUM_RESULT = 5,
        FIGHT_STADIUM_RETRY = 6,
        FIGHT_STADIUM_END = 7,
    };
    enum {
        RESULT_NONE = 0,
        RESULT_WIN = 1,
        RESULT_LOSE = 2,
        RESULT_DRAW = 3,
        RESULT_RETIRE = 4,
    };

    menu::MenuItem menuItem_;                   // 0x1C  bet digits
    menu::MenuItem monsterItem_;                // 0x80  monster list
    int status_;                                // 0xE4
    int messageCount_;                          // 0xE8
    int haveCoin_;                              // 0xEC
    int result_;                                // 0xF0
    unsigned char unk_f4;                       // 0xF4
    unsigned char blinkCount_;                       // 0xF5  blink frame counter
    int blink_;                                 // 0xF8  blinks the bet cursor
    int waitProg_;                                 // 0xFC  message waiting for the menu (last frame)
    int m_bDispCoin;                            // 0x100
    int unk_104;                                // 0x104 monster list shown

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void playBackMenu(int result);
    bool messageUpdate();
    void statusUpdate();
    void coinUpdate();
    void monsterListUpdate();
    void resultUpdate();
    void battleStart();
    void showMessage(int mes);
    void playFanfare();
    void setMenuStatus(int status);
    void closeMessage();
};

extern MaterielMenu_FIGHT_STADIUM gMaterielMenu_FIGHT_STADIUM;
