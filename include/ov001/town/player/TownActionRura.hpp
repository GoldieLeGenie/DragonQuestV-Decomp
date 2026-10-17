#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"

namespace twn {
    struct TownActionRura : cmn::ActionBase {
        static const int RULA_EFFECT = 0x39e;

        dss::Fix32Vector3 tempPos_;                 // 0x04
        dss::Fix32Vector3 startPos_;                // 0x10
        int counter_;                               // 0x1C
        int sprite_;                                // 0x20

        virtual int setup();
        virtual void execute();
        virtual int update();
        int startCheck();
    };
}
