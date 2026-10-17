#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"

namespace twn {
    struct TownActionTabi : cmn::ActionBase {
        int counter;                                // 0x04
        int exitIndex_;                             // 0x08
        int start_;                                 // 0x0C

        virtual int setup();
        virtual void execute();
        virtual int update();
        void start(int exitIndex, bool start);
        int isEffectEnd();
    };
}
