#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"
#include "ov001/town/player/gimmick/MapGimmickBase.hpp"

namespace twn {
    struct TownActionGimmick : cmn::ActionBase {
        static const int MAP_GIMMICK_COUNT = 5;

        MapGimmickBase* mapGimmick_[MAP_GIMMICK_COUNT];     // 0x004
        int gimmickIndex_;                                  // 0x018
        int prevAction_;                                    // 0x01C
        TownGimmickTrap townGimmickTrap_;                   // 0x020
        TownGimmickYari townGimmickYari_;                   // 0x0B4
        TownGimmickKanbotsuUpper townGimmickKanbotsuUpper_; // 0x148
        TownGimmickKanbotsuLower townGimmickKanbotsuLower_; // 0x1E0

        virtual int setup();
        virtual void execute();
        virtual int update();
        int startCheck(int action);
        void registGimmick(MapGimmickBase& gimmick);
    };
}
