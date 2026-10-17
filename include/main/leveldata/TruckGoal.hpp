#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct TruckGoal {
        int X;                                      // 0x00
        int Y;                                      // 0x04
        int Z;                                      // 0x08
        unsigned short floor;                       // 0x0C
        unsigned short uid;                         // 0x0E
        short dir;                                  // 0x10
        unsigned char dummy0;                       // 0x12
        unsigned char dummy1;                       // 0x13

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        int getX();
        int getY();
        int getZ();
        unsigned short getFloor();
        unsigned short getUid();
        short getDir();
        static void setup();
        static void cleanup();
        static TruckGoal* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
