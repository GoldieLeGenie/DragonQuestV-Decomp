#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct LuidaMessage {
        enum LUIDA {
            LUIDA_MES0 = 0,
            LUIDA_MES1 = 1,
            LUIDA_MES2 = 2,
            LUIDA_MES3 = 3,
            LUIDA_MES4 = 4,
            LUIDA_MES5 = 5,
            LUIDA_MES6 = 6,
            LUIDA_MES7 = 7,
            LUIDA_MES8 = 8,
            LUIDA_MES9 = 9,
            LUIDA_MES10 = 10,
            LUIDA_MES11 = 11,
            LUIDA_MES12 = 12,
            LUIDA_MES13 = 13,
            LUIDA_MES14 = 14,
            LUIDA_MES15 = 15,
            LUIDA_MES16 = 16,
            LUIDA_MES17 = 17,
            LUIDA_MES18 = 18,
            LUIDA_MES19 = 19,
            LUIDA_MES20 = 20,
            LUIDA_MES21 = 21,
            LUIDA_MES22 = 22,
            LUIDA_MES23 = 23,
            LUIDA_MES24 = 24,
            LUIDA_MES25 = 25,
            LUIDA_MES26 = 26,
            LUIDA_MES27 = 27,
            LUIDA_MES28 = 28,
            LUIDA_MES29 = 29,
            LUIDA_MAX = 30,
        };

        unsigned long message1;                     // 0x00
        char byte_1;                                // 0x04
        unsigned char dummy0;                       // 0x05
        unsigned char dummy1;                       // 0x06
        unsigned char dummy2;                       // 0x07

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[240];

        unsigned long getMessage1();
        static void setup();
        static void cleanup();
        static LuidaMessage* getRecord(int index);
    };
}
}
