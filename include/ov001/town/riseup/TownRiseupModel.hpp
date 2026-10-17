#pragma once
#include <globaldefs.h>
#include "ov001/town/riseup/TownRiseupBase.hpp"
#include "main/cmn/CommonEffect.hpp"

namespace twn {
    struct TownRiseupModel : TownRiseupBase {
        cmn::CommonEffectCubic model_;              // 0x018
        int unk_32c;                                // 0x32C
        dss::Fix32Vector3 unk_330;                  // 0x330
        dss::Fix32Vector3 unk_33c;                  // 0x33C
        dss::Fix32Vector3 unk_348;                  // 0x348
        unsigned char unk_354[0xc];                 // 0x354

        TownRiseupModel();
        ~TownRiseupModel();
        virtual void setup(int index);
        virtual void setResource(void* data);
        virtual void execute();
        virtual void draw();
        virtual void cleanup();
        virtual void setPosition(dss::Fix32Vector3 pos);
        virtual bool isFinish();
        virtual int getType();
        virtual int getResorceType();
    };
}
