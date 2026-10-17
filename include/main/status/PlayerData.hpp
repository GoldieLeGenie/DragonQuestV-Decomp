#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/status/BaseStatus.hpp"
#include "main/status/HaveItem.hpp"
#include "main/status/HaveAction.hpp"
#include "main/status/HaveEquipment.hpp"

namespace status {
    struct PlayerData {
        static const unsigned int FLAG_STATUS_CHANGE_CURSE4 = 0x1;
        static const unsigned int FLAG_STATUS_CHANGE_CURSE5 = 0x2;
        static const unsigned int FLAG_STATUS_CHANGE_POISON = 0x4;
        static const unsigned int FLAG_STATUS_CHANGE_VENOM = 0x8;
        static const unsigned int FLAG_NAME_INDEX_001 = 0x10;
        static const unsigned int FLAG_NAME_INDEX_002 = 0x20;
        static const unsigned int FLAG_NAME_INDEX_003 = 0x40;
        static const unsigned int FLAG_NAME_INDEX_004 = 0x80;

        unsigned char index_;
        unsigned char kindIndex_;
        unsigned short nameId_;
        char name_[25];
        Sex nameBasedSex_;
        unsigned char command_;
        unsigned char actionCursorIndex_;
        dss::BitFlag<unsigned char> flag_;
        BaseStatus baseStatus_;
        HaveItem haveItem_;
        HaveAction haveAction_;
        unsigned int nextLevelExp_;
        HaveEquipment haveEquipment_;
        int cursedName_;

        PlayerData();
        ~PlayerData();
        void setup(bool flag, int kind, int index, int offset);
        void setupNameId(int kindIndex, int offset);
        void setNameString(char* name);
        char* getNameString();
        Sex getNameBasedSex();
        void setCursedName(int val);
        void setFlagValue(unsigned char val);
        int getAttack();
        int getDefence();
        int getEquipStrength();
        int getEquipAgility();
        int getEquipProtection();
        int getEquipWisdom();
        int getEquipLuck();
        void setFriendMonsterNameIndex(int index, bool flag);
        int getFriendMonsterNameIndex();
        int getKindIndex();
        unsigned short getStrength();
        void setStrength(unsigned short strength);
        unsigned char getAgility();
        void setAgility(unsigned short agility);
        unsigned short getProtection();
        void setProtection(unsigned short protection);
        unsigned char getWisdom();
        void setWisdom(unsigned char wisdom);
        unsigned char getLuck();
        void setLuck(unsigned char luck);
        unsigned short getHp();
        void setHp(unsigned short hp);
        unsigned short getHpMax();
        void setHpMax(unsigned short hpMax);
        unsigned short getMp();
        void setMp(unsigned short mp);
        unsigned short getMpMax();
        void setMpMax(unsigned short mpMax);
        int getExp();
        void setExp(int exp);
        unsigned char getLevel();
        void setLevel(unsigned char lvl);
        unsigned char getCommand();
        void setCommand(unsigned char val);
        unsigned char getActionCursorIndex();
        void setActionCursorIndex(unsigned char idx);
        HaveItem& getHaveItem();
        void setHaveItem(HaveItem& item);
        int getCgIndex();
        int getIconIndex();
        int getEquipAttrIndex();
        int getCharacterKind();
        unsigned char getLevelMax();
        unsigned short getActionMonsterIndex();
        unsigned short getJob();
        unsigned short getMonsterIndex();
        unsigned short getSexId();
        bool isCurse4();
        bool isCurse5();
        bool isPoison();
        bool isVenom();
        void setCurse4(bool flag);
        void setCurse5(bool flag);
        void setPoison(bool flag);
        void setVenom(bool flag);
        HaveAction& getHaveAction();
        void setHaveAction(HaveAction& action);
    };

    struct PlayerDataAll {
        static const int PLAYER_ALL_MAX = 232;
        static const unsigned int FLAG_FRIEND_MONSTER = 0x1;
        static const unsigned int FLAG_RUIDA = 0x2;
        static const unsigned int FLAG_MONSTER_OLDMAN = 0x4;

        static PlayerData playerData_[PLAYER_ALL_MAX];
        static dss::BitFlag<unsigned char> playerFlag_[PLAYER_ALL_MAX];
        static unsigned char nameIndex_[PLAYER_ALL_MAX];

        static void initialize(bool flag);
        static int getCtrlFromFriendMonsterIndex(int playerIndex);
        static PlayerData& getPlayerData(int index);
        static unsigned char getPlayerNameIndex(int index);
        static void setPlayerNameIndex(int index, unsigned char val);
        static void setPlayerFlagValue(int index, unsigned char val);
        static unsigned int getStartIndexForName(int index);
        static unsigned int getUseFlagForName(int index);
        static void setStartIndexUseFlagForName(int index, unsigned int startIndex, unsigned int useFlag);
        static int getNextAddFriendMonster(int playerKindIndex);
        static int addFriendMonster(int playerKindIndex);
        static void delFriendMonster(int index);
        static int getFriendMonsterCount();
        static int getFriendMonsterCountWithoutEventMonster();
        static int getFriendMonsterCtrl(int index);
        static int getFriendMonsterCountInMonster(int playerKindIndex);
        static void setupFriendMonster(int index);
        static int getMonsterCountInOldMan();
        static int getMonsterCtrlInOldMan(int index);
        static int getPlayerCountInRuida();
        static int getPlayerCtrlInRuida(int index);
        static void setFriendMonsterFlag(int index, bool flag);
        static bool isFriendMonsterFlag(int index);
        static void setRuidaFlag(int index, bool flag);
        static bool isRuidaFlag(int index);
        static void setMonsterOldManFlag(int index, bool flag);
        static bool isMonsterOldManFlag(int index);
    };
}
