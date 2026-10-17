#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace twn {
    // Map object pushed on a grid (puzzle gimmick)
    struct MapObjGridMove {
        int uid_;                               // 0x00
        dss::Fix32Vector3 basePosition_;        // 0x04
        int countMoveX_;                        // 0x10
        int countMoveZ_;                        // 0x14
        dss::Fix32 moveLength_;                 // 0x18
        dss::Fix32Vector3 start_;               // 0x1C
        dss::Fix32Vector3 end_;                 // 0x28
        int endCount_;                          // 0x34
        int counter_;                           // 0x38

        static const dss::Fix32 baseSpeed;

        void initialize();
        void setup(int uid, int flag, dss::Fix32 length);
        void execute();
        void setMove(int direction, dss::Fix32 speed);
        int getUid();
        bool isExecEnd();
    };

    extern MapObjGridMove g_GridMove[2];
}
