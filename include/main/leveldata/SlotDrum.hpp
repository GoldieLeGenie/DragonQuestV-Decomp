#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct SlotDrum {
        unsigned char drum5;                        // 0x00
        unsigned char name;                         // 0x01
        unsigned char drum1;                        // 0x02
        unsigned char drum2;                        // 0x03
        unsigned char drum3;                        // 0x04
        unsigned char drum4;                        // 0x05
        unsigned char dummy0;                       // 0x06
        unsigned char dummy1;                       // 0x07

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[640];

        static void setup();
        static void cleanup();
        static SlotDrum* getRecord(int index);
        static unsigned int getArraySize();
        int getName();
    };
}
}
