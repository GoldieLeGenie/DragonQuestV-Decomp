#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"

namespace twn {
    struct TownActionKaifuku : cmn::ActionBase {
        int state_;                                 // 0x04

        virtual int setup();
        virtual void execute();
        virtual int update();
        void start();
    };
}
