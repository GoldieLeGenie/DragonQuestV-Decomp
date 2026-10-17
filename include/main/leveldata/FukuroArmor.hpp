#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct FukuroArmor {
        unsigned short fukuroNum;                   // 0x00
        unsigned char itemID1;                      // 0x02
        unsigned char itemID3;                      // 0x03
        unsigned char itemID2;                      // 0x04
        unsigned char dummy0;                       // 0x05
        unsigned char dummy1;                       // 0x06
        unsigned char dummy2;                       // 0x07

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static void setup();
        static void cleanup();
        unsigned char getItemID1();
        unsigned char getItemID2();
        unsigned char getItemID3();
        static FukuroArmor* getRecord(int index);
    };
}
}
