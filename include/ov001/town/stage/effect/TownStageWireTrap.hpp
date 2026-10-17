#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace twn {
    struct TownStageWireTrap {
        static const int MAX_FIRE_DRAW = 8;
        static const int FIRE_EFFECT_INDEX = 0x38a;

        int counter_;                               // 0x00
        int damage_;                                // 0x04
        int phase_;                                 // 0x08
        int prevIndex;                              // 0x0C
        int lastFire_;                              // 0x10
        int enable_;                                // 0x14

        static dss::Fix32 distance_;
        static dss::Fix32 distanceSq_;
        static int distanceSq2_;

        TownStageWireTrap();
        ~TownStageWireTrap();
        void cleanup();
        bool isTrap();
        void execute();
        int checkTrap();
        void setTrapSide(int index);
        int setDrawFire(dss::Fix32Vector3& pos, int side);
        void calcPlayerDamage();
        bool checkPlayerDemolition();
    };
}
