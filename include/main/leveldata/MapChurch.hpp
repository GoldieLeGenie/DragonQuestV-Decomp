#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"
#include "nitro/fx.hpp"

namespace dq5 {
namespace level {
    struct MapChurch {
        fx32 playerX;                               // 0x00
        fx32 playerY;                               // 0x04
        fx32 playerZ;                               // 0x08
        unsigned short direction;                   // 0x0C
        unsigned short ranafloor;                   // 0x0E
        unsigned short settingflag;                 // 0x10
        unsigned short checkflag;                   // 0x12
        unsigned short floor;                       // 0x14
        unsigned char locationSounen;               // 0x16
        unsigned char locationSeinen;               // 0x17
        char byte_1;                                // 0x18
        unsigned char dummy0;                       // 0x19
        unsigned char dummy1;                       // 0x1A
        unsigned char dummy2;                       // 0x1B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[980];

        fx32 getPlayerX();
        fx32 getPlayerY();
        fx32 getPlayerZ();
        unsigned short getDirection();
        unsigned short getSettingflag();
        unsigned short getCheckflag();
        unsigned short getFloor();
        char getChurchman();
        unsigned short getRanafloor();
        unsigned char getLocationSounen();
        unsigned char getLocationSeinen();
        char getLoadOnly();
        char getMapTime();
        char getChapter();
        static void setup();
        static void cleanup();
        static MapChurch* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
