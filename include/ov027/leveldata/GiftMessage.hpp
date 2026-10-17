#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct GiftMessage {
        unsigned long message1;                     // 0x00
        char byte_1;                                // 0x04
        unsigned char dummy0;                       // 0x05
        unsigned char dummy1;                       // 0x06
        unsigned char dummy2;                       // 0x07

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[184];

        unsigned long getMessage1();
        static void setup();
        static void cleanup();
        static GiftMessage* getRecord(int index);
    };
}
}
