#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct SugorokuChangeMsg {
        unsigned long divergent;                    // 0x00
        unsigned long msg1;                         // 0x04
        unsigned long msg2;                         // 0x08

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[48];

        static void setup();
        static void cleanup();
        static SugorokuChangeMsg* getRecord(int index);
    };
}
}
