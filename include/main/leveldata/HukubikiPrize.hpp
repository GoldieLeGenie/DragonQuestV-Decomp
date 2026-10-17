#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct HukubikiPrize {
        short prize;                                // 0x00
        unsigned char dummy0;                       // 0x02
        unsigned char dummy1;                       // 0x03

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[32];

        static void setup();
        static void cleanup();
        static HukubikiPrize* getRecord(int index);
        short getPrize();
    };
}
}
