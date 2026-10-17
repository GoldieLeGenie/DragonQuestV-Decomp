#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct MedalPrize {
        unsigned short item;                        // 0x00
        unsigned char medal;                        // 0x02
        char byte_1;                                // 0x03

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[28];

        unsigned short getItem();
        unsigned char getMedal();
        static void setup();
        static void cleanup();
        static MedalPrize* getRecord(int index);
    };
}
}
