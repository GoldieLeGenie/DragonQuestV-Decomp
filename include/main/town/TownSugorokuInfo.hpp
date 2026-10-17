#pragma once
#include <globaldefs.h>
#include "main/town/SugorokuPanelData.hpp"

namespace twn {
    struct TownSugorokuInfo {
        static const int SUGOROKU_PANEL_MAX_NUM = 160;
        static const int DICE_MOVE_MAX_NUM = 60;
        static const int MOVE_BACKUP_NUM = 60;
        static const int EXTRA_BACK_COUNT = 4;

        enum {
            NOT_SUGOROKU = 0,
            START_SUGOROKU = 1,
            CONTINUE_TABI = 2,
            CONTINUE_FALL = 3,
            CONTINUE_BATTLE = 4,
            CONTINUE_STRAT = 5,
            CONTINUE_TREASURE_PRE_ROOM = 6,
            CONTINUE_TREASURE_ROOM = 7,
            CONTINUE_MOVE = 8,
            CONTINUE_BATTLE_END = 9,
            CONTINUE_INN = 10,
        };

        int back_;                                  // 0x00
        int reverce_;                               // 0x04
        int nextMapSugoroku_;                       // 0x08
        int continueState_;                         // 0x0C
        unsigned short nextPanelUid_;               // 0x10
        PanelData panel_[SUGOROKU_PANEL_MAX_NUM];   // 0x14
        int panelNum_;                              // 0x2094
        PanelData* diceMovePanel_[DICE_MOVE_MAX_NUM]; // 0x2098
        PanelData* moveBackup_[MOVE_BACKUP_NUM];    // 0x2188
        int count_;                                 // 0x2278
        PanelData* nowPanel;                        // 0x227C
        PanelData* nextPanel;                       // 0x2280
        PanelData lastPanel_;                       // 0x2284
        int endMapId_;                              // 0x22B8
        dss::Fix32Vector3 endMapPos_;               // 0x22BC
        short endMapIdx_;                           // 0x22C8
        int randomEcountFlag_;                      // 0x22CC
        int diceLimit_;                             // 0x22D0
        char diceLimitCount_;                       // 0x22D4
        int diceControlFlag_;                       // 0x22D8
        int moveStart_;                             // 0x22DC
        int nextPayOff_;                            // 0x22E0
        int startPanelMapId_;                       // 0x22E4
        int startPanelUid_;                         // 0x22E8
        int fallMapId_;                             // 0x22EC
        dss::Fix32Vector3 fallPosition_;            // 0x22F0
        int sugorokuEndMode_;                       // 0x22FC
        int menuState_;                             // 0x2300
        int dngMap_;                                // 0x2304
        int dngUid_;                                // 0x2308
        int dngIn_;                                 // 0x230C
        int trgMap_;                                // 0x2310
        int trgUid_;                                // 0x2314
        int prevMapNameId_;                         // 0x2318
        int prevMapLastUid_;                        // 0x231C
        int timeCount_;                             // 0x2320
        int backReverce_;                           // 0x2324
        PanelData* extraBack_[EXTRA_BACK_COUNT];    // 0x2328
        unsigned short extraUid_[EXTRA_BACK_COUNT]; // 0x2338
        unsigned short chanceCardID_;               // 0x2340
        unsigned short diceCount_;                  // 0x2342
        unsigned char stageDataOffset_;             // 0x2344
        char nowMoveCount;                          // 0x2345
        char orgMoveCount_;                         // 0x2346
        char debugOrgMoveCount_;                    // 0x2347

        TownSugorokuInfo();

        void initialize();
        char getNowMoveCount();
        void setDiceCount(unsigned short count);
        int getDiceCount();
        void setNowMoveCount(char count);
        void setBack(bool flag);
        void setNextMapPanelUid(unsigned short uid);
        unsigned short getChanceCardID();
        void setChanceCardID(unsigned short id);
        void setRandomEncountFlag(bool flag);
        void setDiceControlFlag(bool flag);
        void setDiceLimit(bool flag);
        int getDiceLimit();
        char downDiceLimitCount();
        int getDiceControlFlag();
        void setOrgMoveCount(char count);
        char getDebugOrgMoveCount();
        void setDebugOrgMoveCount(char count);
        int getPanelUidByIndex(int index);
        void setNowPanel(int index);
        void setNowPanel(PanelData* data);
        void clearDiceMove();
        int getPushCount();
        void pushDiceMovePanel(PanelData* panel);
        void popDiceMovePanel();
        PanelData* getLastMovePanel();
        int isReverce();
        void setRevece(bool flag);
        int isBack();
        int getMenuState();
        void moveBackup();
        void setStartPanelMapId(int id);
        int getStartPanelMapId();
        void setStartPanelUid(int uid);
        int getStartPanelUid();
        dss::Fix32Vector3 getFallPosition();
        int getFallMapId();
        PanelData& getLastPanel();
        void setTrgMap(int map);
        int getTrgMap();
        void setTrgUid(int uid);
        int getTrgUid();
        int isMoveStart();
        void setPrevMapNameId(int id);
        void setPrevMapLastUid(int id);
        int getPrevMapNameId();
        int getPrevMapLastUid();
        void setTime(int time);
        int isGateNextPayOff();
        bool isExtraBackLink(unsigned short uid);
        PanelData* getExtraBackLink(unsigned short uid);
        int isBackReverce();
        void setBackReverce(bool flag);
        PanelData* getNowPane();
        int getPanelNum();
        void pushPanelData(unsigned short uid, unsigned short panelID, unsigned short attr, unsigned short warpMapNo, unsigned short warpUid, dss::Fix32Vector3& pos);
        void pushPanelLink(int index, int no, int link);
        void setLoopLink(int index, int link);
        int getPanelIDByIndex(int index);
        dss::Fix32Vector3& getPanelPosByIndex(int index);
        int getEndMapNameId();
        void setEndMapNameId(int id);
        dss::Fix32Vector3& getEndMapPosition();
        void setEndMapPosition(dss::Fix32Vector3& pos);
        short getEndMapDirIdx();
        void setEndMapDirIdx(short idx);
        bool isContinue();
        void setContinue(int state);
        int getContinueState();
        void setFallPosition(dss::Fix32Vector3& pos);
        void setFallMapId(int id);
        PanelData* getPanelDataByIndex(int index);
        void setLastPanel(PanelData* panel);
        void setSugorokuEndMode(int type);
        int getSugorokuEndMode();
        void setDngOutMap(int map);
        void setDngOutUid(int uid);
        int getDngOutMap();
        int getDngOutUid();
        void setDngIn(bool flag);
        int isDngIn();
        void setMoveStart(bool flag);
        int getTime();
        void decTimer();
        void setGateNextPayOff(bool flag);
        void pushBackup(PanelData* data);
        void popBackup();
    };

    extern TownSugorokuInfo g_SugorokuInfo;
}
