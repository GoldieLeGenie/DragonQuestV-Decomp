#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"

namespace twn {
    struct TownActionFall : cmn::ActionBase {
        static const dss::Fix32 fallStartFix;
        static const dss::Fix32 fallSpeed;

        int sePlay_;                                // 0x04
        int count_;                                 // 0x08
        int fallType_;                              // 0x0C
        int moveMode_;                              // 0x10
        int partyMove_;                             // 0x14
        dss::Fix32Vector3 cameraPos_;               // 0x18
        dss::Fix32Vector3 vecXZ_;                   // 0x24

        virtual int setup();
        virtual void execute();
        virtual int update();
        int startCheck();
        void setCollFall();
        void setFixXZ();
        void exitFall();
    };
}
