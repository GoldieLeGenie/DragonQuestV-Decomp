#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct StadiumCard {
        unsigned short monsterID1;                  // 0x00
        unsigned short monsterID2;                  // 0x02
        unsigned short monsterID3;                  // 0x04
        unsigned short monsterID4;                  // 0x06
        unsigned short encount;                     // 0x08
        unsigned char odds4;                        // 0x0A
        unsigned char odds1;                        // 0x0B
        unsigned char odds2;                        // 0x0C
        unsigned char odds3;                        // 0x0D
        unsigned char level;                        // 0x0E
        unsigned char dummy0;                       // 0x0F

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[816];

        static void setup();
        static void cleanup();
        static StadiumCard* getRecord(int index);
        unsigned char getOdds4();
        unsigned char getOdds1();
        unsigned char getOdds2();
        unsigned char getOdds3();
    };
}
}
