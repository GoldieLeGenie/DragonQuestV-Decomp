#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct ColorCorrect {
        unsigned short floor;                       // 0x00
        unsigned char backcolor;                    // 0x02
        char byte_1;                                // 0x03
        char byte_2;                                // 0x04
        unsigned char dummy0;                       // 0x05
        unsigned char dummy1;                       // 0x06
        unsigned char dummy2;                       // 0x07

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[1024];

        unsigned short getFloor();
        unsigned char getBackcolor();
        int getFog();
        char getClut();
        static void setup();
        static void cleanup();
        static ColorCorrect* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
