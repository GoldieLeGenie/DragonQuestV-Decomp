#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct FurnitureParam {
        unsigned long normalMsg;                    // 0x00
        unsigned long nothingMsg;                   // 0x04
        unsigned long monsterMsg;                   // 0x08
        unsigned long backMsg;                      // 0x0C
        unsigned long checkMsg;                     // 0x10
        unsigned short sound;                       // 0x14
        unsigned char type;                         // 0x16
        char byte_1;                                // 0x17

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[1800];

        static void setup();
        static void cleanup();
        static FurnitureParam* getRecord(int index);

        unsigned long getNormalMsg();
        unsigned long getMonsterMsg();
        unsigned long getCheckMsg();
        unsigned short getSound();
        unsigned char getType();
        char getBroken();
        char getAnimation();
    };
}
}
