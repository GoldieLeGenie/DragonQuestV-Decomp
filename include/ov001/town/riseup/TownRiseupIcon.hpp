#pragma once
#include <globaldefs.h>
#include "ov001/town/riseup/TownRiseupBase.hpp"
#include "ov001/town/riseup/BillboardItem.hpp"

namespace twn {
    struct TownRiseupIcon : TownRiseupBase {
        enum {
            PHASE_NONE = 0,
            PHASE_START_WAIT = 1,
            PHASE_RISE = 2,
            PHASE_END_WAIT = 3,
            PHASE_FADE_OUT = 4,
        };

        BillboardItem* item_;                       // 0x18
        int phase_;                                 // 0x1C
        char alpha_;                                // 0x20
        int height_;                                // 0x24
        int endCounter_;                            // 0x28
        int startCounter_;                          // 0x2C
        const RiseupParam* param;                   // 0x30

        TownRiseupIcon();
        ~TownRiseupIcon();
        virtual void setup(int index);
        virtual void setType(int type);
        virtual void setResource(void* data);
        virtual void setPosition(dss::Fix32Vector3 pos);
        virtual void execute();
        virtual void draw();
        virtual bool isFinish();
        virtual void setEndFrame(int frame);
        virtual void setStartFrame(int frame);
        virtual int getResorceType();
        virtual int getType();
    };
}
