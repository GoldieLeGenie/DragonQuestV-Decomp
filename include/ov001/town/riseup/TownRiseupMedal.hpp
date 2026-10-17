#pragma once
#include <globaldefs.h>
#include "ov001/town/riseup/TownRiseupBase.hpp"
#include "main/cmn/CommonEffect.hpp"

namespace twn {
    struct TownRiseupMedal : TownRiseupBase {
        enum {
            PHASE_NONE = 0,
            PHASE_START_WAIT = 1,
            PHASE_RISE = 2,
            PHASE_END_WAIT = 3,
            PHASE_FADE_OUT = 4,
        };

        cmn::CommonEffectFlat sprite_;              // 0x18
        int phase_;                                 // 0xE8
        unsigned char alpha_;                       // 0xEC
        int height_;                                // 0xF0
        int endCounter_;                            // 0xF4
        int startCounter_;                          // 0xF8
        const RiseupParam* param;                   // 0xFC

        TownRiseupMedal();
        ~TownRiseupMedal();
        virtual void setup(int index);
        virtual void setType(int type);
        virtual void setResource(void* data);
        virtual void setPosition(dss::Fix32Vector3 pos);
        virtual void execute();
        virtual void draw();
        virtual void cleanup();
        virtual bool isFinish();
        virtual void setEndFrame(int frame);
        virtual void setStartFrame(int frame);
        virtual int getResorceType();
        virtual int getType();
    };
}
