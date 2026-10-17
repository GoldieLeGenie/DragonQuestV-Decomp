#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/status/BaseStatus.hpp"
#include "main/leveldata/PlayerData1.hpp"

namespace status {
    struct HaveStatus {
        static const int TYPE_HERO = 1;
        static const int TYPE_FRIEND = 2;
        static const int TYPE_BATTLENPC = 3;
        static const int TYPE_NOBATTLENPC = 4;
        static const int TYPE_FRIENDMONSTER = 5;
        static const int TYPE_MONSTER = 6;

        unsigned short playerIndex_;
        unsigned short playerKindIndex_;
        unsigned short charaIndex_;
        unsigned short monsterIndex_;
        int exp_;
        unsigned short gold_;
        unsigned short jobId_;
        unsigned short sexId_;
        unsigned char iconIndex_;
        unsigned char level_;
        unsigned char levelMax_;
        char playerType_;
        char isPlayer_;
        char isBattleNpc_;
        char isNoBattleNpc_;
        char isSpecialNpc_;
        char isMonster_;
        unsigned char monsterId_;
        int equipAttrIndex_;
        unsigned char command_;
        unsigned char actionCursorIndex_;
        BaseStatus baseStatus_;

        static int seinenki_;           // data_020a1000
        static BaseStatus diffStatus_;  // data_020a1010
        static BaseStatus& getDiffStatus();

        HaveStatus();
        ~HaveStatus();
        void setup(unsigned short index, int flag);
        void setupPlayer(unsigned short index);
        void setupMonster(unsigned short index, bool flag);
        void cleanup();
        void cleanupPlayer();
        void resetExpGold();
        bool isLevelup();
        void levelup(bool flag);
        void debugLevelup(int level);
        unsigned short levelupAdd(unsigned short value);
        unsigned short levelupAjust(unsigned short value, unsigned short diff, unsigned short normal);
        unsigned short levelupAjustSpecial(unsigned short value, unsigned short diff, unsigned short normal);
        static dq5::level::PlayerData1* getLevelupData(int playerIndex, int level);
        int getPlayerIndex() const;
        int getPlayerKindIndex() const;
        unsigned short getMonsterIndex() const;
        int getMonsterKind() const;
        bool isBattleNpc() const;
        bool isFriendMonster() const;
        bool isMonster() const;
        int getEquipAttrIndex() const;
        int getExp() const;
        int getGold() const;
        int getLevel() const;
        int getLevelMax() const;
        int getCommand() const;
        void setCommand(CommandType type);
        unsigned short getStrength() const;
        unsigned short getProtection() const;
        void setCharaIndex(int index);
        int getCharaIndex() const;
        int getIconIndex() const;
        void setExp(int exp);
        void addExp(int exp);
        int getLevelupExp() const;
        void setLevelupExp(int exp);
        Sex getSex() const;
        void setLevel(unsigned char level);
        void addStrength(char value);
        unsigned char getAgility() const;
        void addAgility(char value);
        void addProtection(char value);
        unsigned char getWisdom() const;
        void addWisdom(char value);
        void addLuck(char value);
        unsigned char getLuck() const;
        void setHp(unsigned short hp);
        unsigned short getHp() const;
        void setHpMax(unsigned short hpMax);
        unsigned short getHpMax() const;
        void addHpMax(char value);
        void setMp(unsigned short mp);
        unsigned short getMp() const;
        void setMpMax(unsigned short mpMax);
        unsigned short getMpMax() const;
        void addMpMax(char value);
        unsigned short getAttack() const;
        unsigned short getDefence() const;
        void addBaseHp(int value);
        void addBaseMp(int value);
        static void setSeinenki(bool flag);

        bool isPlayer() const;
        bool isNoBattleNpc() const;
    };
}
