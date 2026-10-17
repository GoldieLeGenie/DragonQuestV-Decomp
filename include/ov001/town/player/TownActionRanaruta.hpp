#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"

namespace twn {
    struct TownActionRanaruta : cmn::ActionBase {
        int counter_;                               // 0x04
        int change_;                                // 0x08

        virtual int setup();
        virtual void execute();
        virtual int update();
        void start();
        int isEffectEnd();
    };
}
