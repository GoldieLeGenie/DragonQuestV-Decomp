#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"

namespace twn {
    struct TownActionIce : cmn::ActionBase {
        int collActionFlag_;                        // 0x04
        int count_;                                 // 0x08
        dss::Fix32Vector3 target_;                  // 0x0C
        int end_;                                   // 0x18

        virtual int setup();
        virtual void execute();
        virtual int update();
        int startCheck();
    };
}
