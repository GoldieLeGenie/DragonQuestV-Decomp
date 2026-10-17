#pragma once
#include <globaldefs.h>
#include "ov001/town/riseup/TownRiseupBase.hpp"
#include "ov001/town/riseup/BillboardItem.hpp"

namespace twn {
    // billboard vertices given as four corners
    struct UnkBillboardCorners : UnkBillboardVertex {
        UnkBillboardCorners(const dss::Vector2<dss::Fix16>& v0, const dss::Vector2<dss::Fix16>& v1,
                            const dss::Vector2<dss::Fix16>& v2, const dss::Vector2<dss::Fix16>& v3);
    };

    struct TownRiseupExhibit : TownRiseupBase {
        enum {
            PHASE_NONE = 0,
            PHASE_FADE_IN = 1,
            PHASE_FADE_OUT = 2,
        };

        BillboardItem* item_;                       // 0x18
        int phase_;                                 // 0x1C
        int icon_;                                  // 0x20
        UnkBillboardTexCoord uv_;                   // 0x24
        unsigned char startFrame_;                  // 0x44
        unsigned char endFrame_;                    // 0x45
        unsigned char frame_;                       // 0x46
        unsigned char alpha_;                       // 0x47

        static UnkBillboardCorners xy_;

        TownRiseupExhibit();
        ~TownRiseupExhibit();
        virtual void setup(int index);
        virtual void setResource(void* data);
        virtual void setStartFrame(int frame);
        virtual void setEndFrame(int frame);
        virtual void execute();
        virtual void draw();
        virtual bool isFinish();
        virtual void setExhibitIcon(int number);
        virtual int getType();
        virtual int getResorceType();
    };
}
