#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct FukuroWeapon {
        unsigned short fukuroNum;                   // 0x00
        unsigned char itemID;                       // 0x02
        unsigned char dummy0;                       // 0x03

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static void setup();
        static void cleanup();
        unsigned char getItemID();
        static FukuroWeapon* getRecord(int index);
    };
}
}
