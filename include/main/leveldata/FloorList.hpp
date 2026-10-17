#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct FloorList {
        unsigned short floorIndex;                  // 0x00
        unsigned short area;                        // 0x02
        char floor[10];                             // 0x04
        unsigned char dummy0;                       // 0x0E
        unsigned char dummy1;                       // 0x0F

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[10064];

        unsigned short getFloorIndex();
        unsigned short getArea();
        char* getFloor();
        static void setup();
        static void cleanup();
        static FloorList* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
