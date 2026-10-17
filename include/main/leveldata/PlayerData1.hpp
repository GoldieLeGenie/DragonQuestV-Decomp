#pragma once
#include <globaldefs.h>

namespace dq5 {
    namespace level {
        struct PlayerData1 {
            unsigned long exp;
            unsigned short strength;
            unsigned short agility;
            unsigned short intelligence;
            unsigned short luck;
            unsigned short HP;
            unsigned short MP;
            unsigned short battleAction1;
            unsigned short battleAction2;
            unsigned short battleAction3;
            unsigned short battleAction4;
            unsigned short normalAction1;
            unsigned short normalAction2;
            unsigned short normalAction3;
            unsigned short normalAction4;
            unsigned short vitality;
            unsigned char level;
            unsigned char dummy0;

            unsigned long getExp();
            unsigned short getStrength();
            unsigned short getAgility();
            unsigned short getIntelligence();
            unsigned short getLuck();
            unsigned short getHP();
            unsigned short getMP();
            unsigned short getBattleAction1();
            unsigned short getBattleAction2();
            unsigned short getBattleAction3();
            unsigned short getBattleAction4();
            unsigned short getNormalAction1();
            unsigned short getNormalAction2();
            unsigned short getNormalAction3();
            unsigned short getNormalAction4();
            unsigned short getVitality();
        };
    }
}
