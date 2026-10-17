#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct FloorBackColor {
        unsigned char colorR1;              // 0x00
        unsigned char colorG1;              // 0x01
        unsigned char colorB1;              // 0x02
        unsigned char colorR2;              // 0x03
        unsigned char colorG2;              // 0x04
        unsigned char colorB2;              // 0x05
        unsigned char colorR3;              // 0x06
        unsigned char colorG3;              // 0x07
        unsigned char colorB3;              // 0x08
        unsigned char colorR4;              // 0x09
        unsigned char colorG4;              // 0x0A
        unsigned char colorB4;              // 0x0B
        unsigned char colorR5;              // 0x0C
        unsigned char colorG5;              // 0x0D
        unsigned char colorB5;              // 0x0E
        unsigned char colorR6;              // 0x0F
        unsigned char colorG6;              // 0x10
        unsigned char colorB6;              // 0x11
        unsigned char colorR7;              // 0x12
        unsigned char colorG7;              // 0x13
        unsigned char colorB7;              // 0x14
        unsigned char colorR8;              // 0x15
        unsigned char colorG8;              // 0x16
        unsigned char colorB8;              // 0x17

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[720];

        static void setup();
        static void cleanup();
        static FloorBackColor* getRecord(int index);
    };
}
}
