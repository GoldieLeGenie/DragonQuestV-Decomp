#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace btl {
    struct BattleCameraHoming {
        enum {
            STEP_NONE = 0,
            STEP_START = 1,
            STEP_WAIT = 2,
            STEP_RESTORE = 3,
        };

        int enable_;                                // 0x00
        int step_;                                  // 0x04
        unsigned char startTime_;                   // 0x08
        unsigned char waitTime_;                    // 0x09
        unsigned char restoreTime_;                 // 0x0A
        unsigned char count_;                       // 0x0B
        short rotAngle_;                            // 0x0C

        BattleCameraHoming();
        ~BattleCameraHoming();
        void setup(dss::Fix32Vector3 target, int drawCtrlId);
        void calcHomingTarget(dss::Vector3<short>& angle);
        void waitHomingTarget(dss::Vector3<short>& angle);
        void restoreHomingTarget(dss::Vector3<short>& angle);
        void calculation(dss::Vector3<short>& angle);
        void setRotateTime(int time);
        void setWaitTime(int time);
        void start();
    };
}
