#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/status/GameFlag.hpp"

namespace twn {
    struct MapGimmickBase {
        static const int USE_GLOBAL_FLAG_START = 900;
        static const int USE_GLOBAL_FLAG_END = 960;

        // vtable                                   // 0x00
        dss::Flag state_;                           // 0x04
        int startUid_;                              // 0x08
        int endUid_;                                // 0x0C
        int surfaceType_;                           // 0x10
        status::GameFlag flag_;                     // 0x14

        MapGimmickBase();
        void setData(int startUid, int endUid, int surfaceType, unsigned int state);
        int isStart();
        void setup();
        virtual void useGlobalSetup(int uid);
        virtual void execute();
        virtual bool isEnd();
        virtual void setAnimation(int uid) = 0;
        int set(int uid, int surface);
    };

    struct TownGimmickKanbotsuLower : MapGimmickBase {
        virtual void useGlobalSetup(int uid);
        virtual void setAnimation(int uid);
    };

    struct TownGimmickKanbotsuUpper : MapGimmickBase {
        int counter_;                               // 0x94

        virtual void useGlobalSetup(int uid);
        virtual void setAnimation(int uid);
        virtual bool isEnd();
    };

    struct TownGimmickTrap : MapGimmickBase {
        virtual void setAnimation(int uid);
    };

    struct TownGimmickYari : MapGimmickBase {
        virtual void setAnimation(int uid);
    };
}
