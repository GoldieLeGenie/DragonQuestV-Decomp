#pragma once
#include <globaldefs.h>
#include "ov001/town/riseup/TownRiseupBase.hpp"
#include "ov001/town/riseup/BillboardItem.hpp"

namespace twn {
    struct TownRiseupScriptMove : TownRiseupBase {
        BillboardItem* item_;                       // 0x18
        dss::Fix32Vector3 start_;                   // 0x1C
        dss::Fix32Vector3 end_;                     // 0x28
        int frame_;                                 // 0x34
        int counter_;                               // 0x38

        TownRiseupScriptMove();
        ~TownRiseupScriptMove();
        virtual void setup(int index);
        virtual void setResource(void* data);
        virtual void execute();
        virtual void draw();
        virtual bool isFinish();
        virtual void setScriptData(dss::Fix32Vector3 start, dss::Fix32Vector3 end, int frame, int type);
        virtual int getResorceType();
        virtual int getType();
    };
}
