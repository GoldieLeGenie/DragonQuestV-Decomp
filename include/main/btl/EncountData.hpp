#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/btl/EncountSpecial.hpp"

namespace btl {
    struct EncountData {
        struct MonsterInfo {
            unsigned int rate_;                 // 0x0
            unsigned int monsterIndex_;         // 0x4
            unsigned int countMax_;             // 0x8
        };

        short tileId_;                          // 0x00
        short tileLevel_;                       // 0x02
        short stdTileRate_;                     // 0x04
        short formationId_;                     // 0x06
        short teamAddEnable_;                   // 0x08
        short escapeDisable_;                   // 0x0A
        short eventEncount_;                    // 0x0C
        FirstAttack firstAttack_;               // 0x10
        short sound_;                           // 0x14
        int selectGroup_;                       // 0x18
        MonsterInfo monsterInfo_[14];           // 0x1C
        unsigned int specialRate_;              // 0xC4
        unsigned int specialGroupIndex_;        // 0xC8
        unsigned int specialNightOnly_;         // 0xCC
        TIME_ZONE timeZone_;                    // 0xD0
        EncountSpecial encountSpecial_;         // 0xD4
        unsigned short monsterIndex_[4];        // 0xE4
        unsigned short monsterCount_[4];        // 0xEC
        unsigned short monsterGroup_[4];        // 0xF4

        EncountData();
        ~EncountData();
        void setup(int tileId, bool flag);
        void setup(int tileId, TIME_ZONE timeZone, bool flag);
        void clear();
        void setupData(int flag);
        void setTileId(int tileId);
        void setTileLevel(int lv);
        int getStdRate();
        FirstAttack getFirstAttack();
        unsigned short getMonsterIndex(int group);
        int getTileLevel();
        bool isTeamAddEnable();
        unsigned short getMonsterCount(int group);
        void setupFirstAttack();
        void selectGroup();
        void selectSpecialParty();
        void selectOneGroup();
        void selectMultiGroup();
        int selectAE_GroupCount();
        int selectA_E();
        bool selectAE_Add(int group, int groupMax);
        int getEncountTileIdForPlayerLevel(int level);
        int getRandomTileID(int min, int max);
        void setTeamAddEnable(bool flag);
        void setEventEncount(bool flag);
    };

    unsigned char getRandArrayIndex(unsigned char* ary, unsigned char count);
}
