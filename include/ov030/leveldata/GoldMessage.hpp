#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct GoldMessage {
        enum BANK {
            BANK_MES0 = 0,
            BANK_MES1 = 1,
            BANK_MES2 = 2,
            BANK_MES3 = 3,
            BANK_MES4 = 4,
            BANK_MES5 = 5,
            BANK_MES6 = 6,
            BANK_MES7 = 7,
            BANK_MES8 = 8,
            BANK_MES9 = 9,
            BANK_MES10 = 10,
            BANK_MES11 = 11,
            BANK_MES12 = 12,
            BANK_MES13 = 13,
            BANK_MES14 = 14,
            BANK_MES15 = 15,
            BANK_MES16 = 16,
            BANK_MES17 = 17,
            BANK_MES18 = 18,
            BANK_MES19 = 19,
            BANK_MES20 = 20,
            BANK_MES21 = 21,
            BANK_MES22 = 22,
            BANK_MAX = 23,
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
        static char dataRegion[184];

        unsigned long getMessage1();
        static void setup();
        static void cleanup();
        static GoldMessage* getRecord(int index);
    };
}
}
