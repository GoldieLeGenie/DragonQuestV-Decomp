#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/dss/DssUtils.hpp"

namespace status
{
    struct HaveStatusInfo;

    struct HaveBattleStatus
    {
        enum SelectCommand
        {
            Attack = 0,
            Defence = 1,
            UseAction = 2,
            UseItem = 3,
            NoSelect = 4,
            AISelect = 5
        };

        enum CallStart
        {
            StartRound = 0,
            StartTurn = 1
        };

        static const int MOSYAS_ACTION_COUNT = 17;

        int groupIndex_;                        // 0x00
        int index_;                             // 0x04
        int originalIndex_;                     // 0x08
        CharacterType originalType_;            // 0x0C
        CharacterType type_;                    // 0x10
        HaveStatusInfo* haveStatusInfo_;        // 0x14
        int exp_;                               // 0x18
        unsigned short hp_;                     // 0x1C
        unsigned short hpMax_;                  // 0x1E
        unsigned short mp_;                     // 0x20
        unsigned short mpMax_;                  // 0x22
        unsigned short strength_;               // 0x24
        unsigned short protection_;             // 0x26
        unsigned short agility_;                // 0x28
        unsigned short wisdom_;                 // 0x2A
        unsigned char luck_;                    // 0x2C
        int texp_;                              // 0x30
        int tlevel_;                            // 0x34
        int change_;                            // 0x38
        int actionIndex_;                       // 0x3C
        int actionCount_;                       // 0x40
        int patternIndex_;                      // 0x44
        dss::BitFlag<unsigned int> patternFailedFlag_;  // 0x48
        dss::BitFlag<unsigned int> disablePattern_;     // 0x4C
        dss::BitFlag<unsigned int> disablePattern2nd_;  // 0x50
        SelectCommand selectCommand_;           // 0x54
        int selectIndex_;                       // 0x58
        int selectedGroup_;                     // 0x5C
        int selectedTarget_;                    // 0x60
        int sortIndex_;                         // 0x64
        int selectItemIndex_;                   // 0x68
        int monsterCtrlId_;                     // 0x6C
        int escape_;                            // 0x70
        unsigned char brains_;                  // 0x74
        unsigned char group_[6];                // 0x75
        unsigned char crossFire_;               // 0x7B
        int crossFireTarget_;                   // 0x7C
        unsigned char multi_;                   // 0x80
        char multiCount_;                       // 0x81
        char multiCount2_;                      // 0x82
        char multiTurnCount_;                   // 0x83
        char multiGlobalCount_;                 // 0x84
        char multiExecCount_;                   // 0x85
        unsigned char level_;                   // 0x86
        unsigned char dragon_;                  // 0x87
        unsigned char metal_;                   // 0x88
        unsigned char zombi_;                   // 0x89
        unsigned char air_;                     // 0x8A
        unsigned char slime_;                   // 0x8B
        unsigned char jouk_;                    // 0x8C
        int monsterIndexForNpc_;                // 0x90
        int roundActionIndex_;                  // 0x94
        unsigned char mosyasAction_[MOSYAS_ACTION_COUNT];  // 0x98
        int mosyasActionCount_;                 // 0xAC

        static dss::BitFlag<unsigned int> groupControl_[4];
        static int groupRoopIndex_[4];
        static int parupunteDebugIndex_;
        static int confusionDebugIndex_;
        static int eventFlag_;

        HaveBattleStatus();
        ~HaveBattleStatus();
        static void initialize();
        void setup(CharacterType type, int group, int index);
        void newBaseChangeMonster(int index);
        void newBaseChangeMonsterFromPlayer(int index);
        void newBaseChangeMonsterReverse2();
        void changeMonsterFromPlayer(int index);
        void changeMonsterReverse();
        void setupPlayer();
        void setupMonster();
        bool isJouk();
        void setActionIndex(int actionIndex);
        void setActionSelect(CallStart callStart, bool secondCheck);
        void setActionSelectForPlayer();
        void setActionSelectForMonster(CallStart callStart, bool secondCheck);
        void setActionPatternForMonster(CallStart callStart);
        void setActionIndexForMonster();
        int getActionIndexForPattern();
        int getActionIndex(int index);
        int getActionAnimation();
        void setActionFailed(int actionIndex);
        bool isActionFailed();
        void setActionDisable(bool flag);
        bool isActionDisable();
        bool isActionAllDisable();
        void setActionDisable2nd();
        bool isActionDisable2nd();
        bool isActionDisable2nd(int pattern);
        bool isActionAllDisable2nd();
        void clearActionDisable2nd();
        bool isRestOneAction2nd();
        void setRestOne();
        int getRestNum();
        bool isUseMp();
        int isMahoton();
        int isFizzleZone();
        bool checkRestMP_Mahoton();
        void setLoopCount(bool secondCheck);
        static void clearGroupControl();
        void setGroupControl();
        bool checkGroupControl();
        void setSelectCommand(SelectCommand command, int index);
        void setSelectGroup(int group);
        void setSelectTarget(int playerIndex);
        int getSelectGroup();
        int getSelectTarget();
        bool isAutoSelect();
        int getIndex();
        void setIndex(int index);
        void clearMulti();
        SelectCommand getSelectCommand();
        int getSelectCommandIndex();
        int getSelectItemIndex();
        unsigned char getBrains();
        bool isZombi();
        bool isDragon();
        bool isMetal();
        int getActionIndex();
        int getItemSortIndex();
        void clearSelectCommand();
        void startBattle();
        void execStartOfRound();
        void setMultiAction();
        bool isMultiAction();
        int getCrossFire();
        void setCrossFireTarget(int index);
        int getCrossFireTarget();
        int getParupunteAction(int event);
        int getParupunteActionForMonster(int event);
        void setupParupunteAction();
        int getPlayerConfuseAction();
        int getMonsterConfuseAction();
        int getMonsterConfuseActionOnEvent();
        int getMonsterConfuseActionOnStadium();
        void setupConfuseAction();
        void setupSpecialAction(int actionIndex);
        void setupSleepAction();
        void setupRollOver();
        void setupTurnBeforeAction();
    };

    extern int actionPattern[5][6];
}
