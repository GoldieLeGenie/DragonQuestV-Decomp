#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct ShopIndexSugoroku {
        unsigned short area;                        // 0x00
        unsigned char dummy0;                       // 0x02
        unsigned char dummy1;                       // 0x03

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[40];

        unsigned short getArea();
        static void setup();
        static void cleanup();
        static ShopIndexSugoroku* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
