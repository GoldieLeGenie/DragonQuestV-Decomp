#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"

namespace twn {
    struct TownActionSube : cmn::ActionBase {
        static const dss::Fix32 subeR;
        static const dss::Fix32 subeSpeed;
        static const int maxCount = 3;

        int subeDir4_;                              // 0x04
        int prev_subeDir4_;                         // 0x08
        int count_;                                 // 0x0C
        dss::Fix32Vector3 vec[4];                   // 0x10

        virtual int setup();
        virtual void execute();
        virtual int update();
        int startCheck();
    };
}
