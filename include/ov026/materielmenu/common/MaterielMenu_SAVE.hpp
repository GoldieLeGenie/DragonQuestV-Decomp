#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/UnkDiaryInfo.hpp"
#include "main/profile/SaveLoad.hpp"

// adventure log writing (church, chapter end, last dungeon, game clear, passing communication)
struct MaterielMenu_SAVE : menu::MenuBase {
    enum SAVE_TYPE {
        TYPE_CHURCH = 0,
        TYPE_CHAPTER = 1,
        TYPE_LASTDUNGEON = 2,
        TYPE_CLEAR = 3,
        TYPE_SURECHIGAI = 4,
    };
    enum SAVEMENU_MODE {
        MENU_IS_SAVE = 0,
        MENU_READING = 1,
        MENU_SELECT = 2,
        MENU_IS_OVERWRITE = 3,
        MENU_WRITING = 4,
        MENU_WRITINGEXEC = 5,
        MENU_WRITINGWAIT = 6,
        MENU_SOUNDWAIT = 7,
        MENU_FAILED = 8,
        MENU_SUCCESS = 9,
        MENU_IS_END = 10,
        MENU_GAME_END = 11,
        MENU_END = 12,
        MENU_BLANK = 13,
        MENU_SURECHIGAI_START = 14,
    };

    UnkDiaryInfo diary_[3];                     // 0x1C
    int saveType_;                              // 0x64
    SAVEMENU_MODE status_;                      // 0x68
    short selectList_;                          // 0x6C
    int isSave_;                                // 0x70
    int mother_;                                // 0x74
    int startSurechigai_;                       // 0x78
    int saveWaitFlag_;                          // 0x7C
    int saveWaitCounter_;                       // 0x80
    int sexType_;                               // 0x84
    menu::MenuItem menuItem_;                   // 0x88
    int messageCounter_;                        // 0xEC
    int saveResult_;                            // 0xF0
    int saveSoundCounter_;                      // 0xF4
    profile::CatalogView* catalogview_;         // 0xF8

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool messageUpdate();
    void commandUpdate();
    bool getSaveData();
    void setMode(SAVEMENU_MODE mode);
    void selectDiary();
    void setMessage(int mes);
    void setWaitMessage(int mes);
    void setYesNoMessage(int mes, bool yes);
    void setTalkMessage(int mes);
    void setTalkWaitMessage(int mes);
    void setTalkYesNoMessage(int mes, bool yes);
    void setTalkYesNoMessage2(int mes1, int mes2, bool yes);
    void firstCancelMessage();
};

extern MaterielMenu_SAVE gMaterielMenu_SAVE;
