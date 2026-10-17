#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct ShopData1 {
        unsigned long price;                        // 0x00
        unsigned short item;                        // 0x04
        unsigned char dummy0;                       // 0x06
        unsigned char dummy1;                       // 0x07

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[80];

        unsigned long getPrice();
        unsigned short getItem();
        static void setup();
        static void cleanup();
        static ShopData1* getRecord(int index);
    };
}
}
