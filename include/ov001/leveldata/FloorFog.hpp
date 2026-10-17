#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct FloorFog {
        int rate01;                         // 0x00
        int rate00;                         // 0x04
        unsigned short offset00;            // 0x08
        unsigned short offset01;            // 0x0A
        unsigned char colorR00;             // 0x0C
        unsigned char colorR01;             // 0x0D
        unsigned char colorG00;             // 0x0E
        unsigned char colorG01;             // 0x0F
        unsigned char colorB00;             // 0x10
        unsigned char colorB01;             // 0x11
        unsigned char dummy0;               // 0x12
        unsigned char dummy1;               // 0x13

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[60];

        static void setup();
        static void cleanup();
        static FloorFog* getRecord(int index);
    };
}
}
