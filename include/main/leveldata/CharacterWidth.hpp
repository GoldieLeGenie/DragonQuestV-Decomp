#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"
#include "nitro/fx.hpp"

namespace dq5 {
namespace level {
    struct CharacterWidth {
        fx32 fieldRight;                            // 0x00
        fx32 townFront;                             // 0x04
        fx32 townBack;                              // 0x08
        fx32 fieldBack;                             // 0x0C
        fx32 fieldFront;                            // 0x10
        fx32 fieldLeft;                             // 0x14
        unsigned short index;                       // 0x18
        unsigned char dummy0;                       // 0x1A
        unsigned char dummy1;                       // 0x1B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        unsigned short getIndex();
        fx32 getFieldFront();
        fx32 getFieldBack();
        fx32 getFieldRight();
        fx32 getFieldLeft();
        static void setup();
        static CharacterWidth* getRecord(int index);
        static void cleanup();
        static unsigned int getArraySize();
    };
}
}
