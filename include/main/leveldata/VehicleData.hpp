#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct VehicleData {
        int shipX;                                  // 0x00
        int shipY;                                  // 0x04
        unsigned short placeNum;                    // 0x08
        unsigned short floor;                       // 0x0A
        unsigned char id;                           // 0x0C
        char byte_1;                                // 0x0D
        unsigned char dummy0;                       // 0x0E
        unsigned char dummy1;                       // 0x0F

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[496];

        int getShipX();
        int getShipY();
        unsigned char getId();
        unsigned short getPlaceNum();
        unsigned short getFloor();
        char getYounenki();
        char getSeinenki();
        char getSounenki();
        static void setup();
        static void cleanup();
        static VehicleData* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
