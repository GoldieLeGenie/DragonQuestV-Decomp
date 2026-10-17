#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"
#include "nitro/fx.hpp"

namespace dq5 {
namespace level {
    struct CLUTCode {
        fx32 colorB;                                // 0x00
        fx32 colorR;                                // 0x04
        fx32 colorG;                                // 0x08

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[192];

        fx32 getColorB();
        fx32 getColorR();
        fx32 getColorG();
        static void setup();
        static void cleanup();
        static CLUTCode* getRecord(int index);
    };
}
}
