#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct ShopIndex3 {
        unsigned short area;                        // 0x00
        char byte_1;                                // 0x02
        unsigned char dummy0;                       // 0x03

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[40];

        unsigned short getArea();
        static void setup();
        static void cleanup();
        static ShopIndex3* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
