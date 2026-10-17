#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/status/BasePartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"

namespace status {
    struct PartyStatusData {
        static const int CARRIAGE_OUTSIDE_MAX = 4;
        static const int CARRIAGE_INSIDE_MAX = 7;
        static const int CARRIAGE_BACKSIDE_MAX = 2;

        PlayerStatus playerStatus_[10];                     // 0x0000
        dss::Flag playerStatusFlag_[10];                    // 0x3318
        int orderOutside_[CARRIAGE_OUTSIDE_MAX];            // 0x3340
        int orderInside_[CARRIAGE_INSIDE_MAX];              // 0x3350
        int orderBackside_[CARRIAGE_BACKSIDE_MAX];          // 0x336C

        PartyStatusData();
        ~PartyStatusData();
        void clear();
        bool add(int index, bool flag);
        void del(int ctrl);
        void store(int index);
        int getOrder(int index);
        int getOutsideOrder(int index);
        int getInsideOrder(int index);
        int getBacksideOrder(int index);
        void reorder(int a, int b, int c, int d);
        int getCount();
        int getOutsideCount();
        int getInsideCount();
        int getBackCount();
        bool isCarriageOut(int ctrl);
        bool isCarriageIn(int ctrl);
        bool isCarriageBack(int ctrl);
        bool isPlayer(int ctrl);
        bool isBattleNpc(int ctrl);
        bool isNormalNpc(int ctrl);
        PlayerStatus& getPlayerStatusForCtrl(int ctrl);
        unsigned int getPlayerStatusFlagValue(int idx);
        void setPlayerStatusFlagValue(int idx, unsigned int val);
        void setPlayerStatus(int index, int playerIndex);
        void addOrder(int ctrlIndex);
        void delOrder(int index);
        int getCountForReorder();
        void setOutsideOrder(int index, int val);
        void setInsideOrder(int index, int val);
        void setBacksideOrder(int index, int val);
    };

    struct PartyStatus : BasePartyStatus {
        static const unsigned int FLAG_DISPLAY = 0x1;
        static const unsigned int FLAG_MEMBER_SHIFT = 0x2;
        static const unsigned int FLAG_BATTLE_NPC_CARRIAGE = 0x4;
        static const unsigned int FLAG_BATTLE_NPC_IN_CARRIAGE = 0x8;
        static const unsigned int FLAG_ALL_PLAYER = 0x10;
        static const unsigned int FLAG_PLAYER = 0x200;
        static const unsigned int FLAG_BATTLE_NPC = 0x400;
        static const unsigned int FLAG_NORMAL_NPC = 0x800;

        dss::Flag accessFlag_;                              // 0x478
        int party_[10];                                     // 0x47C
        int partyCount_;                                    // 0x4A4
        int sugorokuMode_;                                  // 0x4A8
        PartyStatusData partyStatusData_;                   // 0x4AC

        PartyStatus();
        ~PartyStatus();
        void initialize();
        void add(int index, bool flag);
        void addNpc(int charaIndex);
        void del(int ctrlIndex);
        void clear();
        void store();
        void reorder(int a, int b, int c, int d);
        int getPlayerIndex(int index);
        int getNpcPlayerIndex();
        PlayerStatus& getPlayerStatus(int index);
        PlayerStatus& getPlayerStatusForPlayerIndex(int playerIndex);
        bool isInsideCarriage(int index);
        bool isOutsideCarriage(int index);
        static bool isInsideCarriageForPlayerIndex(int playerIndex);
        int getSortIndex(int playerIndex);
        void setNormalMode();
        bool isNormalMode();
        void setPlayerMode();
        bool isPlayerMode();
        void setBattleMode();
        bool isBattleMode();
        void setBattleModeWithCarriage();
        bool isBattleModeWithCarriage();
        void setBattleModeAndCarriage();
        bool isBattleModeAndCarriage();
        void setDisplayMode();
        bool isDisplayMode();
        void setMemberShiftMode();
        bool isMemberShiftMode();
        void setAllPlayerMode();
        bool isAllPlayerMode();
        int isSugorokuMode();
        void setAccessMode(unsigned int mode);
        unsigned int getAccessMode();
        void setParty();
        void setPartyPlayerMode();
        void setPartyBattleMode();
        void setPartyBattleModeWithCarriage();
        void setPartyBattleModeAndCarriage();
        void setPartyMemberShiftMode();
        void setPartyNormalMode();
        void setPartyDisplayMode();
        void setPartyAllPlayerMode();
        void setPartySugorokuMode();
        int getCount();
        int getCarriageCount();
        int getCarriageOutCount();
        int getCarriageOutAliveCount();
        int getCarriageAliveCount();
        int isCarriage();
    };

    struct UseActionParam;

    struct PartyStatusUtility {
        static int noDamage_;
        static int noDamageForMonster_;
        static int formerParty_[4];
        static int separatePlayer_[10];
        static int separateCarriageOutPlayer_[5];
        static int separateFlag_;

        static int isSeparate();
        static int getCarriageOutPlayer(int no);
        static int getSeparatePlayer(int no);

        static void setNoDamageEnable(int flag);
        static void setNoDamageEnableForMonster(bool flag);
        static bool isExecMinadein();
        static bool isMinadeinEnable(PlayerStatus* player);
        static int getMaxLevel();
        static int getPlayerMaxLevel();
        static bool isPartyActionEnable();
        static bool isPoisonForMantan();
        static bool destroyPoisonForMantan(UseActionParam& useActionParam);
        static bool isRecoveryForMantan();
        static bool recoveryForMantan(UseActionParam& useActionParam);
        static int calcRecoveryValue(int actionIndex, int* valueBMax, int* valueCMax);
        static void calcRecoveryLocal(int actionIndex, int* valueA, int* valueB, int* valueC);
        static int calcRecoveryLocalMax(int count, int* valueA, int* valueB, int* valueC, int* valueBMax, int* valueCMax);
        static void getBehomalaTargetIndex(int* target);
        static bool isDemolition();
        static bool isPapasBattle();
        static bool isPapasBattle2();
        static bool isAlivePapasOnly();
        static void recoveryBattleEnd();
        static PlayerStatus& getStoryPlayerStatus();
        static int getLevelupPlayer();
        static void recovery();
        static void kaifukuyuka();
        static void startBattle();
        static void execOfRoundInCarriage();
        static int giveItem(int itemIndex);
        static int getLeaderIndex();
        static void reflectBattleExp();
        static int getAlivePlayerCountOutsideCarriage();
        static int getAliveCountOutsideCarriagePlayerOnly();
        static int getAliveWithoutSpazzCountOutsideCarriagePlayerOnly();
        static void forceReorderBattle();
        static void forceReorderTown(bool notCheck);
        static void resetForceReorderMember();
        static void reorderFormerMember();
        static void recoveryDisableDemolition();
        static void separateParty(bool resetFlag);
        static void resetSeparateParty(bool resetFlag);
        static void clearWalkDamage();
    };

    extern PartyStatus g_Party;
}
