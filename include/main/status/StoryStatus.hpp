#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace dq5 {
    enum CHAPTER_NO {
        CHAPTER_DEBUG = 0,
        CHAPTER_YOUNENKI = 1,
        CHAPTER_SEINENKI = 2,
        CHAPTER_SOUNENKI = 3,
        CHAPTER_OPENING = 4,
        CHAPTER_ENDING = 5,
        CHAPTER_DEMO = 6,
    };
}

namespace status {
    struct StoryStatus {
        static const int FLAG_JISAN = 0x1;
        static const int FLAG_USE_BANK = 0x2;
        static const int FLAG_JISAN_SACK = 0x4;
        static const int FLAG_HAVE_GOLD_CARD = 0x8;
        static const int FLAG_GET_MEDAL = 0x10;
        static const int FLAG_GET_INLAND_SHIP = 0x20;
        static const int FLAG_GET_OCEAN_SHIP = 0x40;
        static const int FLAG_GET_FIRMAMENT = 0x80;

        dss::Flag flag_;                        // 0x00
        dq5::CHAPTER_NO chapter_;               // 0x04
        short heroEquip_[9];                    // 0x08
        short clearFriendMonster_[3];           // 0x1A

        StoryStatus();
        ~StoryStatus();
        void initialize();
        void setJisan(bool flag);
        bool isJisan();
        void setUseBank(bool flag);
        bool isUseBank();
        void setJisanSack(bool flag);
        bool isJisanSack();
        void setGoldCard(bool flag);
        bool isGoldCard();
        void setMedalFlag(bool flag);
        bool isMedalFlag();
        void setVehicleEnable(int type, bool flag);
        bool isVehicleEnable(int type);
        void setChapter(dq5::CHAPTER_NO chapter);
        unsigned int getFlagValue();
        void setFlagValue(unsigned int val);
        short getHeroEquip(int index);
        void setHeroEquip(int index, short itemID);
        dq5::CHAPTER_NO getChapter();
        short getClearFriendMonster(int index);
        void setClearFriendMonster(int index, short ctrlID);
    };

    extern StoryStatus g_Story;
}
