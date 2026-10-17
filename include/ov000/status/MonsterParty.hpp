#pragma once
#include <globaldefs.h>
#include "ov000/status/MonsterStatus.hpp"

namespace status
{
    struct MonsterParty {
        static const int MONSTER_MAX = 12;

        // vtable                                       // 0x0000
        MonsterStatus monster_[MONSTER_MAX];            // 0x0004
        int monsterCount_;                              // 0x3DB4
        int dropItem_;                                  // 0x3DB8
        int dropItemMonster_;                           // 0x3DBC
        int dropFlag_;                                  // 0x3DC0
        int partyMonster_;                              // 0x3DC4

        static int sortIndex_[4];
        static int sortCount_[4];

        MonsterParty();
        ~MonsterParty();
        virtual int add(int monsterGroup, int monsterIndex, bool flag);
        virtual void del(int ctrl);
        virtual void clear();
        int getCount();
        int getBattleCount();
        int getAliveCount();
        int getMonsterCountDeadOrAlive(int monsterIndex);
        int getMonsterCountInGroup(int group);
        int getMonsterCountInGroupAlive(int group);
        MonsterStatus& getMonsterInGroup(int group, int index);
        int getMonsterIndexInGroup(int group);
        int getMonsterGroup(int index);
        int getMonsterIndex(int index);
        MonsterStatus& getMonsterStatus(int index);
        int getCtrlId(int index);
        int getGroupCount();
        int getMonsterGroupForMonsterIndex(int monsterIndex);
        int getMonsterCallType();
        int getMonsterCallIndex();
        static void initializeSortIndex();
        static int getSortIndex(int monsterIndex);
        static int getSortIndexInGroup(int group);
        static bool isSortIndex(int sortIndex, int monsterIndex);
        void checkDropItemMonster(int index);
        void checkDropItem(int ctrl);
        void setDropItem(int item);
        int getDropItem();
        void setDropItemMonster(int monster);
        int getDropItemMonster();
        int getPartyMonster();
        int isAddParty(int count);
        void setNoDamageEnable(int flag);
    };

    struct MonsterPartyWithDraw : MonsterParty {
        MonsterPartyWithDraw();
        virtual int add(int monsterGroup, int monsterIndex, bool flag);
        virtual void del(int ctrl);
    };

    extern MonsterPartyWithDraw g_Monster;
} // namespace status
