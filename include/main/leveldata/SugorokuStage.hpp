#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct SugorokuStage {
        unsigned short mapNo;                       // 0x00
        unsigned short placeNo;                     // 0x02
        unsigned short panelNo;                     // 0x04
        unsigned short link1;                       // 0x06
        unsigned short link2;                       // 0x08
        unsigned short link3;                       // 0x0A
        unsigned short reverse;                     // 0x0C
        unsigned short divergent;                   // 0x0E
        unsigned short warpMapNo;                   // 0x10
        unsigned short warpPlaceNo;                 // 0x12
        unsigned short index;                       // 0x14
        unsigned char dummy0;                       // 0x16
        unsigned char dummy1;                       // 0x17

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static void setup();
        static void cleanup();
        static SugorokuStage* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
