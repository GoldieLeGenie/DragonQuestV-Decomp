#pragma once
#include <globaldefs.h>
#include "ov001/town/riseup/TownRiseupBase.hpp"
#include "main/cmn/CommonEffect.hpp"

namespace twn {
    struct TownRiseupSprite : TownRiseupBase {
        enum {
            PHASE_WAIT = 0,
            PHASE_ANIM = 1,
            PHASE_MOVE = 2,
            PHASE_FADE_IN = 3,
            PHASE_FADE_OUT = 4,
        };

        cmn::CommonEffectFlat sprite_;              // 0x018
        int phase_;                                 // 0x0E8
        dss::Fix32Vector3 move_;                    // 0x0EC
        dss::Fix32Vector3 start_;                   // 0x0F8
        dss::Fix32Vector3 end_;                     // 0x104
        int frame_;                                 // 0x110
        int counter_;                               // 0x114
        dss::Fix32 alpha_;                          // 0x118
        int startCounter_;                          // 0x11C

        TownRiseupSprite();
        ~TownRiseupSprite();
        virtual void setup(int index);
        virtual void setupNear(int flag);
        virtual void setupNear2(int type);
        virtual void setResource(void* data);
        virtual void execute();
        virtual void draw();
        virtual void cleanup();
        virtual void setPosition(dss::Fix32Vector3 pos);
        virtual bool isFinish();
        virtual void setScriptData(dss::Fix32Vector3 start, dss::Fix32Vector3 end, int frame, int type);
        virtual void setScriptFade(dss::Fix32Vector3 pos, int frame, int flag);
        virtual void setStartFrame(int frame);
        virtual int getResorceType();
        virtual int getType();
    };
}
