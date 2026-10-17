#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct TimeZone {
        unsigned short frame;                       // 0x00
        char byte_1;                                // 0x02
        char byte_2;                                // 0x03

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[32];

        unsigned short getFrame();
        char getScript();
        char getZone();
        char getPrevPalette();
        char getNextPalette();
        static unsigned int getArraySize();
        static void setup();
        static void cleanup();
        static TimeZone* getRecord(int index);
    };
}
}
