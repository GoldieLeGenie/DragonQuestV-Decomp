#pragma once
#include <globaldefs.h>
#include "main/status/CharacterStatus.hpp"
#include "main/leveldata/MonsterData.hpp"

namespace status {
    struct MonsterStatus : CharacterStatus {
        static const unsigned int FLAG_TAKE_UP_MONSTER_DROP = 0x1;

        int ctrlId_;                                    // 0x508
        int sortIndex_;                                 // 0x50C
        dss::Flag eventFlag_;                           // 0x510
        int mosyasIndex_;                               // 0x514
        int mosyasMonsterIndex_;                        // 0x518
        CharacterStatus* mosyasTarget_;                 // 0x51C
        dss::Flag flag_;                                // 0x520

        MonsterStatus();
        ~MonsterStatus();
        void setup(int monsterGroup, int monsterIndex, int sortIndex);
        void cleanup();
        bool isEnable();
        bool isBattleEnable();
        bool isBeingEnable();
        int getMonsterIndex();
        void setMonsterIndex(int index);
        int getMonsterGroup();
        int getSortIndexInGroup();
        int getMosyasIndex();
        int getMosyasMonsterIndex();
        void setCtrlId(int ctrlId);
        int getCtrlId();
        int getDrawCtrlId();
        int getDropItem();
        int getHaveDropItem();
        void naturalRecovery();
        void setStartStatus();
        void execStartOfRound();
        static bool isAddParty(int monsterIndex, int count);
        static bool isAddPartyFirst(int ratio);
        static bool isAddPartySecond(int ratio);
        static bool isAddPartyTherd(int ratio);
        void setTakeUpMonsterDrop(bool flag);
        bool isTakeUpMonsterDrop();
        void changeMonsterWithHPMP(int monsterIndex);

        virtual void setMosyasChange(int monsterIndex);
        virtual void setMosyasChange(CharacterStatus* target);
        virtual void setMosyasRelease();
        virtual bool isDeathDisable();
        virtual void print();
        virtual void printAction();
    };

}
