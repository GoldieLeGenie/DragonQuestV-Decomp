#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct ChurchMessage {
        enum CHURCH {
            CHURCH_MES42 = 42,
            CHURCH_MES43 = 43,
        };

        unsigned long message1;                     // 0x00
        unsigned long message2;                     // 0x04
        char byte_1;                                // 0x08
        unsigned char dummy0;                       // 0x09
        unsigned char dummy1;                       // 0x0A
        unsigned char dummy2;                       // 0x0B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[528];

        unsigned long getMessage1();
        unsigned long getMessage2();
        char getVocalSound();
        static void setup();
        static void cleanup();
        static ChurchMessage* getRecord(int index);
    };
}
}
