#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"
#include "nitro/fx.hpp"

namespace dq5 {
namespace level {
    struct MonsterAnim {
        fx32 scale;                                 // 0x00
        unsigned short index;                       // 0x04
        unsigned short action;                      // 0x06
        unsigned short sound;                       // 0x08
        unsigned short hitframe;                    // 0x0A
        unsigned short wait;                        // 0x0C
        unsigned short effect;                      // 0x0E
        unsigned short camera;                      // 0x10
        unsigned short camera2;                     // 0x12
        unsigned char anim;                         // 0x14
        unsigned char animfile;                     // 0x15
        unsigned char startframe;                   // 0x16
        char byte_1;                                // 0x17

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[240];

        static void setup();
        static void cleanup();
        static MonsterAnim* getRecord(int index);
        static unsigned int getArraySize();
        unsigned short getIndex();
        unsigned short getAction();
        unsigned short getSound();
        unsigned char getAnim();
        fx32 getScale();
        unsigned short getHitframe();
        unsigned short getEffect();
        unsigned char getAnimfile();
        unsigned char getStartframe();
        char getDisplay();
    };
}
}
