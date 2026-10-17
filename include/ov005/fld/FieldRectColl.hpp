#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace fld
{
    struct FieldRectColl {
        dss::Fix32Vector3 pos1;                 // 0x00
        dss::Fix32Vector3 pos2;                 // 0x0C
        int type;                               // 0x18
    };

    struct FieldRectCollManager {
        FieldRectColl rectColl_[5];             // 0x00
        int rectCollCount_;                     // 0x8C

        void setup();
        static FieldRectCollManager& getSingleton();
    };
} // namespace fld
