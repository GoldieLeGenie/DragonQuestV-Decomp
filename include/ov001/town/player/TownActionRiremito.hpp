#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"

namespace twn {
    struct TownActionRiremito : cmn::ActionBase {
        int counter_;                               // 0x04

        virtual int setup();
        virtual void execute();
        virtual int update();
        int isEffectEnd();
        void start();
    };
}
