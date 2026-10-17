#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/UnkDiaryInfo.hpp"
#include "main/profile/SaveLoad.hpp"

// adventure log (save file) selection menu of the title screen
struct MaterielMenu_LOAD : menu::MenuBase {
    enum LOAD_STATUS {
        LOAD_MODESELECT = 0,
        LOAD_IS_RESUME = 1,
        LOAD_RESUME = 2,
        LOAD_DATACHECK = 3,
        LOAD_DATASELECT = 4,
        LOAD_ISOVERLOAD = 5,
        LOAD_NAMEEDIT = 6,
        LOAD_WRITECHECK = 7,
        LOAD_DELETECHECK = 8,
        LOAD_DELETEWAIT = 9,
        LOAD_LOADCHECK = 10,
        LOAD_ERROR = 11,
        LOAD_END = 12,
    };

    static const int ROOT_RESUME_COUNT;
    static const int ROOT_COUNT;
    static int activeDiaryNo_;

    menu::MenuItem rootItem_;                   // 0x1C
    menu::MenuItem dataItem_;                   // 0x80
    menu::MenuItem resumeItem_;                 // 0xE4
    UnkCursorMoveGridLoop navigator_;           // 0x148
    LOAD_STATUS status_;                        // 0x154
    int menuMode_;                              // 0x158
    int messageCounter_;                        // 0x15C
    int firstDiary_;                            // 0x160
    int freeDiary_;                             // 0x164
    int country_;                               // 0x168
    UnkDiaryInfo diary_[4];                     // 0x16C  [3] = resume data
    profile::CatalogView* catalogview_;         // 0x1CC
    int killResult_;                            // 0x1D0
    int makeResult_;                            // 0x1D4
    int wait_;                                  // 0x1D8
    int resumeExist_;                           // 0x1DC
    int frame_;                                 // 0x1E0
    int deleteWaitFlag_;                        // 0x1E4
    int deleteWaitCounter_;                     // 0x1E8
    int deleteResult_;                          // 0x1EC

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool messageUpdate();
    void rootUpdate();
    void resumeUpdate();
    void dataSelectUpdate();
    bool getSaveData();
    bool deleteDiary();
    bool makeDiary();
    void changeStatus(LOAD_STATUS status);
    void closeMessage();
};

extern MaterielMenu_LOAD gMaterielMenu_LOAD;
