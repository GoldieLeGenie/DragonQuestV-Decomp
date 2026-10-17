#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct ShopMessage {
        unsigned long message1;                     // 0x00
        unsigned long message2;                     // 0x04
        unsigned long message3;                     // 0x08
        unsigned long message4;                     // 0x0C
        char byte_1;                                // 0x10
        unsigned char dummy0;                       // 0x11
        unsigned char dummy1;                       // 0x12
        unsigned char dummy2;                       // 0x13

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[780];

        unsigned long getMessage1();
        unsigned long getMessage2();
        unsigned long getMessage3();
        unsigned long getMessage4();
        static void setup();
        static void cleanup();
        static ShopMessage* getRecord(int index);
    };
}
}
