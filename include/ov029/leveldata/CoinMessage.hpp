#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct CoinMessage {
        enum COIN {
            COIN_MES0 = 0,
            COIN_MES1 = 1,
            COIN_MES2 = 2,
            COIN_MES3 = 3,
            COIN_MES4 = 4,
            COIN_MES5 = 5,
            COIN_MES6 = 6,
            COIN_MES7 = 7,
            COIN_MES8 = 8,
            COIN_MES9 = 9,
            COIN_MES10 = 10,
            COIN_MES11 = 11,
            COIN_MES12 = 12,
            COIN_MAX = 13,
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
        static char dataRegion[104];

        unsigned long getMessage1();
        static void setup();
        static void cleanup();
        static CoinMessage* getRecord(int index);
    };
}
}
