#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct BattleMap {
        unsigned char R;                            // 0x00
        unsigned char G;                            // 0x01
        unsigned char B;                            // 0x02
        unsigned char mapIndex;                     // 0x03
        char map[12];                               // 0x04
        char byte_1;                                // 0x10
        unsigned char dummy0;                       // 0x11
        unsigned char dummy1;                       // 0x12
        unsigned char dummy2;                       // 0x13

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[1800];

        unsigned char getR();
        unsigned char getG();
        unsigned char getB();
        unsigned char getMapIndex();
        char* getMap();
        char getTime();
        static void setup();
        static void cleanup();
        static BattleMap* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
