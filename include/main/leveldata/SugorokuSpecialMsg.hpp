#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct SugorokuSpecialMsg {
        unsigned long divergent;                    // 0x00
        unsigned long msg1;                         // 0x04
        unsigned long msg2;                         // 0x08
        unsigned long msg3;                         // 0x0C
        unsigned long msg4;                         // 0x10
        unsigned long msg5;                         // 0x14
        unsigned long msg6;                         // 0x18
        unsigned long msg7;                         // 0x1C

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[256];

        static void setup();
        static void cleanup();
        static SugorokuSpecialMsg* getRecord(int index);
    };
}
}
