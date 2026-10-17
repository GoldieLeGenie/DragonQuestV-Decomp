#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct InnMessage {
        enum INN {
            INN_MES0 = 0,
            INN_MES1 = 1,
            INN_MES2 = 2,
            INN_MES3 = 3,
            INN_MES4 = 4,
            INN_MES5 = 5,
            INN_MES6 = 6,
            INN_MES7 = 7,
            INN_MAX = 8,
        };

        unsigned long message1;                     // 0x00
        unsigned long message2;                     // 0x04
        unsigned long message3;                     // 0x08
        char byte_1;                                // 0x0C
        unsigned char dummy0;                       // 0x0D
        unsigned char dummy1;                       // 0x0E
        unsigned char dummy2;                       // 0x0F

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[128];

        unsigned long getMessage1();
        unsigned long getMessage2();
        unsigned long getMessage3();
        static void setup();
        static void cleanup();
        static InnMessage* getRecord(int index);
    };
}
}
