#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct TruckRail {
        unsigned short moveFloor;           // 0x00
        unsigned short floor;               // 0x02
        unsigned short link1;               // 0x04
        unsigned short link2;               // 0x06
        unsigned short ID;                  // 0x08
        unsigned short branch;              // 0x0A
        unsigned short moveID;              // 0x0C
        unsigned char special;              // 0x0E
        unsigned char dummy0;               // 0x0F

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static void setup();
        static void cleanup();
        static TruckRail* getRecord(int index);
    };
}
}
