#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"
#include "nitro/fx.hpp"

namespace dq5 {
namespace level {
    struct SugorokuDrop {
        fx32 x;                                     // 0x00
        fx32 y;                                     // 0x04
        fx32 z;                                     // 0x08
        unsigned short before;                      // 0x0C
        unsigned short after;                       // 0x0E

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[176];

        static void setup();
        static void cleanup();
        static SugorokuDrop* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
