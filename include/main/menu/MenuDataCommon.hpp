#pragma once
#include <globaldefs.h>

namespace menu {
    struct MenuDataCommon {
        enum STATUS_INDEX {
            ATTACK = 0,
            DEFENCE = 1,
            STRENGTH = 2,
            AGILITY = 3,
            PROTECTION = 4,
            WISDOM = 5,
            LUCK = 6,
            NOWHP = 7,
            MAXHP = 8,
            NOWMP = 9,
            MAXMP = 10,
            LEVEL = 11,
            EXP = 12,
        };

        static int getEquipKind(int index);
        static int getAbilityKind(STATUS_INDEX index);
        static int getStatus(int activeChara, STATUS_INDEX index, int noEquip);
        static int getRuraName(int index);
        static int getItemTypeMessageNo(int itemID);
        static int getItemMessageNo(int itemID);
        static int getPlayerJob(int activeChara);
        static int getPlayerCondition(int activeChara);
    };
}
