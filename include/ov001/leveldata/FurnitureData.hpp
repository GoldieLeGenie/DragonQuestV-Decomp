#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct FurnitureData {
        unsigned long message;              // 0x00
        unsigned short uid;                 // 0x04
        unsigned short item;                // 0x06
        unsigned short gold;                // 0x08
        unsigned short encount;             // 0x0A
        unsigned short openIndex;           // 0x0C
        unsigned short flagIndex;           // 0x0E
        unsigned char type;                 // 0x10
        unsigned char furnIndex;            // 0x11
        unsigned char ListSize;             // 0x12
        char byte_1;                        // 0x13

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[200];

        static void setup();
        static void cleanup();
        static FurnitureData* getRecord(int index);

        char getScript();
        char getSlot();
    };
}
}
