#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/town/TownTruckSwitch.hpp"

namespace twn {
    // Wagon left on the rails
    struct TownTruckWagon {
        short uid_;                             // 0x00
        short map_;                             // 0x02
        dss::Fix32Vector3 pos_;                 // 0x04
        short idx_;                             // 0x10

        TownTruckWagon();
        void setMap(short map);
        void setUid(short uid);
        void setPos(dss::Fix32Vector3& pos);
        void setIdx(short idx);
        short getUid();
    };

    struct TownTruckSeesaw {
        int uid_;                               // 0x00
        int link_;                              // 0x04
        int switchAnim_;                        // 0x08
        int switchIndex_[2];                    // 0x0C

        void setup();
        bool setupAnim();
        bool isSeesawIndex(int index);
        void seesawSwitch(bool anim);
    };

    void loadAfterSetup();
    int getSetupData(int animNo);

    extern TownTruckWagon wagon_[20];
    extern int wagonCount_;
    extern TownTruckSwitch switch_[25];
    extern int switchCount_;
    extern TownTruckSeesaw seesaw_;
}
