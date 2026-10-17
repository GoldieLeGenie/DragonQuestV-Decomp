#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/status/HaveBattleStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/HaveItemSack.hpp"
#include "main/status/UseActionParam.hpp"

namespace menu {
    struct MenuStatusInfo {
        enum ACCESS_MODE {
            NORMAL_MODE = 0,
            PLAYER_MODE = 1,
            BATTLE_MODE = 2,
            BATTLE_CARRIAGE_MODE = 3,
            BATTLE_AND_CARRIAGE_MODE = 4,
            DISPLAY_MODE = 5,
            SHIFT_MEMBER_MODE = 6,
            ALL_PLAYER_MODE = 7,
        };
        enum PARTY_COUNT {
            COUNT_ALL = 0,
            COUNT_CARRIAGE_IN = 1,
            COUNT_CARRIAGE_OUT = 2,
        };
        enum PLAYER_POSITION {
            POSITION_CARRIAGE_IN = 0,
            POSITION_CARRIAGE_OUT = 1,
        };
        enum PLAYER_TYPE {
            TYPE_PLAYER = 0,
            TYPE_FRIEND_MONSTER = 1,
            TYPE_BATTLE_NPC = 2,
            TYPE_NORMAL_NPC = 3,
        };
        enum PLAYER_CONDITION {
            CONDITION_ALIVE = 0,
            CONDITION_DEATH = 1,
            CONDITION_NEARDEATH = 2,
            CONDITION_POISON = 3,
            CONDITION_VENOM = 4,
            CONDITION_SPELL = 5,
            CONDITION_ITEM_SPELL = 6,
        };
        enum USE_MAGIC_TYPE {
            USE_ALL = 0,
            USE_TOWN = 1,
            USE_BATTLE = 2,
        };
        enum EQUIP_RESULT {
            EQUIP_SUCCESS = 0,
            EQUIP_FAILED = 1,
            EQUIP_ALREADY = 2,
        };

        static void setMode(ACCESS_MODE mode);
        static void setMode(unsigned int mode);
        static unsigned int getMode();
        static unsigned int getGold();
        static void setGold(unsigned int gold);
        static unsigned int getCoin();
        static void setCoin(unsigned int coin);
        static unsigned int getBank();
        static void setBank(unsigned int bank);
        static unsigned int getMedal();
        static void setMedal(unsigned int medal);
        static int getPartyCount(PARTY_COUNT mode);
        static bool isCarriageEnable();
        static bool isCarriagePosition(int playerIndex, PLAYER_POSITION position);
        static bool ableToShow();
        static void reorder(int index0, int index1, int index2, int index3);
        static void addPlayer(int activeChara);
        static void delPlayer(int activeChara);
        static int getPlayerIndex(int activeChara);
        static int getPlayerKindIndex(int activeChara);
        static int getPlayerIconIndex(int activeChara);
        static int getPlayerCharaIndex(int activeChara);
        static int getPlayerJob(int activeChara);
        static int getPlayerSex(int activeChara);
        static int getPlayerSortIndex(int activeChara);
        static int getPlayerItemID(int activeChara, int activeItem);
        static bool isPlayerType(int activeChara, PLAYER_TYPE type);
        static int getPlayerItemCount(int activeChara);
        static bool isPlayerHaveItem(int activeChara, int itemID);
        static bool isPlayerEquipItem(int activeChara, int itemID);
        static bool isPlayerEquipItemIndex(int activeChara, int activeItem);
        static bool isPlayerEquipEnable(int activeChara, int itemID);
        static int getPlayerEquipItemID(int activeChara, ItemType type, int index);
        static bool isAbleToEqip(int activeChara, int activeItem);
        static void throwPlayerItem(int activeChara, int activeItem);
        static void addPlayerItem(int activeChara, int itemID);
        static int getPlayerItemCommandFlag(int activeChara, int activeItem);
        static EQUIP_RESULT setEquipItem(int activeChara, int activeItem, ItemType type);
        static void resetEquipItemForIndex(int activeChara, int activeItem);
        static bool isPlayerCondition(int activeChara, PLAYER_CONDITION condition);
        static void setPlayerCondition(int activeChara, PLAYER_CONDITION condition);
        static void resetPlayerCondition(int activeChara, PLAYER_CONDITION condition);
        static bool isPlayerItemSort(int activeChara);
        static bool isPlayerClever(int activeChara);
        static bool isPlayerActionEnable(int activeChara);
        static int getPlayerActionCount(int activeChara, USE_MAGIC_TYPE type);
        static int getPlayerActionID(int activeChara, int activeAction);
        static int getPlayerActionID(int activeChara, int activeAction, USE_MAGIC_TYPE type);
        static bool isPlayerActionUseType(int magicID, USE_MAGIC_TYPE type);
        static int getPlayerTactics(int activeChara);
        static void setPlayerTactics(int activeChara, CommandType command);
        static status::HaveStatusInfo& getHaveStatusInfo(int activeChara);
        static status::HaveBattleStatus& getHaveBattleStatus(int activeChara);
        static status::PlayerData& getPlayerData(int activeChara);
        static int getFukuroItemCount();
        static int getFukuroItemCount(int activeItem);
        static int getFukuroMaxPage();
        static int getFukuroItemID(int activeItem, int page);
        static int getFukuroItemIndexToAll(int activeItem, int page);
        static int getFukuroItemCountInPage(int page);
        static int getFukuroItemCommandFlag();
        static void throwFukuroItem(int activeItem, int page);
        static void throwFukuroItemForID(int itemID);
        static void addFukuroItem(int itemID, int count);
        static int isFukuroHaveItem(int itemID);
        static void setFukuroName(char* name);
        static char* getFukuroName();
        static status::HaveItemSack& getHaveItemSack();
        static void changeItemPlayertoPlayer(int activeChara0, int activeItem0, int activeChara1, int activeItem1);
        static void changeItemPlayertoSack(int activeChara, int activeItem);
        static void changeItemSacktoPlayer(int activeItem, int activeChara, int activeItem1);
        static int usePlayerItem(status::UseActionParam& param, int activeChara, int activeItem, int target);
        static int useFukuroItem(status::UseActionParam& param, int activeItem, int target);
        static int usePlayerMagic(status::UseActionParam& param, int activeChara, int target, int magicID);
        static bool isCheckRecoveryPlayer();
        static bool isRecoveryPlayer(status::UseActionParam& param);
        static bool isCheckPosonPlayer();
        static bool isPoisonPlayer(status::UseActionParam& param);
        static void sortPlayerItem(int activeChara);
        static void sortFukuroItem();
        static int getWordDBIndex(int magicID);
        static status::PlayerStatus& getPlayerStatus(int activeChara);
        static status::HaveAction& getHaveAction(int activeChara);
    };
}
