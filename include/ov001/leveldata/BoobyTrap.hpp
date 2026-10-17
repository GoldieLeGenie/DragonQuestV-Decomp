#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct BoobyTrap {
        unsigned short index;               // 0x00
        unsigned short placeRight;          // 0x02
        unsigned short placeLeft;           // 0x04
        unsigned short floor;               // 0x06

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[240];

        static void setup();
        static void cleanup();
        static BoobyTrap* getRecord(int index);
        static unsigned int getArraySize();
        int getIndex();
        int getPlaceRight();
        int getPlaceLeft();
    };
}
}
