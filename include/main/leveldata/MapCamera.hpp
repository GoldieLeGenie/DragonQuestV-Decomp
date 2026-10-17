#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"
#include "nitro/fx.hpp"

namespace dq5 {
namespace level {
    struct MapCamera {
        fx32 distance;                              // 0x00
        fx32 angleX;                                // 0x04
        fx32 angleY;                                // 0x08
        fx32 angleZ;                                // 0x0C
        fx32 x;                                     // 0x10
        fx32 y;                                     // 0x14
        fx32 z;                                     // 0x18
        unsigned short areaNo;                      // 0x1C
        unsigned short flagNo;                      // 0x1E
        unsigned short floorNo;                     // 0x20
        char fileNo[16];                            // 0x22
        unsigned char dummy0;                       // 0x32
        unsigned char dummy1;                       // 0x33

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[1040];

        unsigned short getAreaNo();
        unsigned short getFlagNo();
        unsigned short getFloorNo();
        static void setup();
        static void cleanup();
        static MapCamera* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
