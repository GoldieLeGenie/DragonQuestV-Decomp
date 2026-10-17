#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct FloorParam {
        unsigned char bgmDaytime;                   // 0x00
        unsigned char bgmNight;                     // 0x01
        char battlefloor;                           // 0x02
        char eventfloor;                            // 0x03
        char byte_1;                                // 0x04
        char byte_2;                                // 0x05
        char byte_3;                                // 0x06
        char byte_4;                                // 0x07
        char byte_5;                                // 0x08
        char byte_6;                                // 0x09
        char byte_7;                                // 0x0A
        unsigned char dummy0;                       // 0x0B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[120];

        char getBattlefloor();
        char getEventfloor();
        char getDaytime();
        char getIcon_map();
        char getIcon_shop();
        char getIcon_rotate();
        char getRula();
        char getRiremito();
        char getLanaruta();
        char getHorsepict();
        char getNohorse();
        char getNopict();
        char getSave();
        char getYami();
        char getEncount();
        static void setup();
        static void cleanup();
        static FloorParam* getRecord(int index);
    };
}
}
