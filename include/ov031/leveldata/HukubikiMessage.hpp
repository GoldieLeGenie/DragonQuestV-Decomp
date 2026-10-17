#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct HukubikiMessage {
        enum HUKUBIKI {
            HUKUBIKI_MES0 = 0,
            HUKUBIKI_MES1 = 1,
            HUKUBIKI_MES2 = 2,
            HUKUBIKI_MES3 = 3,
            HUKUBIKI_MES4 = 4,
            HUKUBIKI_MES5 = 5,
            HUKUBIKI_MES6 = 6,
            HUKUBIKI_MES7 = 7,
            HUKUBIKI_MES8 = 8,
            HUKUBIKI_MES9 = 9,
            HUKUBIKI_MES10 = 10,
            HUKUBIKI_MES11 = 11,
            HUKUBIKI_MES12 = 12,
            HUKUBIKI_MES13 = 13,
            HUKUBIKI_MES14 = 14,
            HUKUBIKI_MES15 = 15,
            HUKUBIKI_MES16 = 16,
            HUKUBIKI_MES17 = 17,
            HUKUBIKI_MES18 = 18,
            HUKUBIKI_MES19 = 19,
            HUKUBIKI_MES20 = 20,
            HUKUBIKI_MES21 = 21,
            HUKUBIKI_MES22 = 22,
            HUKUBIKI_MES23 = 23,
            HUKUBIKI_MES24 = 24,
            HUKUBIKI_MES25 = 25,
            HUKUBIKI_MES26 = 26,
            HUKUBIKI_MES27 = 27,
            HUKUBIKI_MES28 = 28,
            HUKUBIKI_MES29 = 29,
            HUKUBIKI_MAX = 30,
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
        static HukubikiMessage* getRecord(int index);
    };
}
}
