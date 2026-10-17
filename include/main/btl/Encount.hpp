#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/btl/EncountCountDown.hpp"
#include "main/btl/EncountData.hpp"
#include "main/btl/EncountTile.hpp"
#include "main/btl/EncountScreenOver.hpp"

namespace btl
{
    struct Encount {
        enum EncountNumber {
            EncountSingle = 0,
            EncountNumbers = 1,
            EncountMultiple = 2,
        };

        int chapter_;                           // 0x000
        int landType_;                          // 0x004
        int tileId_;                            // 0x008
        TIME_ZONE timeZone_;                    // 0x00C
        int enable_;                            // 0x010
        int brewCount_;                         // 0x014
        unsigned short walkCount_;              // 0x018
        unsigned short totalWalkCount_;         // 0x01A
        int monsterIndex_[4];                   // 0x01C
        int monsterCount_[4];                   // 0x02C
        int monsterGroupWidth_[4];              // 0x03C
        int encountNumberIndex_;                // 0x04C
        int encountCountType_[4];               // 0x050
        EncountCountDown encountCountDown_;     // 0x060
        EncountData encountData_;               // 0x078
        EncountTile encountTile_;               // 0x174
        EncountScreenOver encountScreenOver_;   // 0x17C

        Encount();
        static Encount* getSingleton();
        void setupDungeon(int chapter, TIME_ZONE timeZone, int floorIndex);
        void setupField(int chapter, TIME_ZONE timeZone);
        void execDungeon();
        void execField();
        void execWalk();
        void exec();
        FirstAttack getFirstAttack();
        int isEncounted();
        bool isEncountedNext();
        void setBlock(int type, int land, int x, int y);
        void setTimeZone(TIME_ZONE timeZone);
        bool brew();
        void forceBrew(int tile);
        void forceEventBrew(int tile);
        int getRandomTileID(int min, int max);
        int getEncountTileIdForPlayerLevel(int level);
        void setFriendMonster(bool flag);
        void setEventEncount(bool flag);
        void setLevel(int lvl);
        void forceEncount();
        EncountNumber getEncountNumberType();
        int getEncountNumberIndex();
        void setMonsterCountName();
        bool getMonsterCountName(int monsterIndex);
        int getLandType();
        bool isEnable();
        void setEnable(int flag);
        void setTileId(int id);
        void setMonsterIndex(int group, int index);
        void setMonsterCount(int group, int count);
        int getMonsterIndex(int group);
        int getMonsterCount(int group);
        int getLevel();
        bool isFriendMonster();
    };
} // namespace btl
