#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct AppriseItem {
        unsigned long message9;                     // 0x00
        unsigned long message1;                     // 0x04
        unsigned long message2;                     // 0x08
        unsigned long message3;                     // 0x0C
        unsigned long message4;                     // 0x10
        unsigned long message5;                     // 0x14
        unsigned long message6;                     // 0x18
        unsigned long message7;                     // 0x1C
        unsigned long message8;                     // 0x20
        unsigned short ID;                          // 0x24
        unsigned char dummy0;                       // 0x26
        unsigned char dummy1;                       // 0x27

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static AppriseItem* getRecord(int index);
        unsigned long getMessage9();
        unsigned long getMessage1();
        unsigned long getMessage2();
        unsigned long getMessage3();
        unsigned long getMessage4();
        unsigned long getMessage5();
        unsigned long getMessage6();
        unsigned long getMessage7();
        unsigned long getMessage8();
        static char dataRegion[400];
        static void setup();
        static void cleanup();
    };
}
}
