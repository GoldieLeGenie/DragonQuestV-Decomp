#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"
#include "nitro/fx.hpp"

namespace dq5 {
namespace level {
    struct EffectColorParam {
        fx32 rPoint;                                // 0x00
        fx32 gPoint;                                // 0x04
        fx32 bPoint;                                // 0x08
        unsigned short frame;                       // 0x0C
        unsigned char index;                        // 0x0E
        unsigned char dummy0;                       // 0x0F

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[3584];

        fx32 getRPoint();
        fx32 getGPoint();
        fx32 getBPoint();
        unsigned short getFrame();
        unsigned char getIndex();
        static unsigned int getArraySize();
        static void setup();
        static void cleanup();
        static EffectColorParam* getRecord(int index);
    };
}
}
