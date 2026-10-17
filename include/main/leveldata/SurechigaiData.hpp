#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct SurechigaiData {
        unsigned short cgicon;                      // 0x00
        unsigned short itemid;                      // 0x02
        unsigned char index;                        // 0x04
        char byte_1;                                // 0x05
        unsigned char dummy0;                       // 0x06
        unsigned char dummy1;                       // 0x07

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[512];

        static void setup();
        static void cleanup();
        static SurechigaiData* getRecord(int index);
        unsigned short getCgicon();
        char getLevel();
        char getType();
    };
}
}
