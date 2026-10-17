#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct EncountSpecial {
        unsigned char monsterID1;                   // 0x00
        unsigned char monsterID2;                   // 0x01
        unsigned char monsterID3;                   // 0x02
        unsigned char monsterID4;                   // 0x03
        char byte_1;                                // 0x04
        char byte_2;                                // 0x05
        unsigned char dummy0;                       // 0x06
        unsigned char dummy1;                       // 0x07

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[80];

        unsigned char getMonsterID1();
        unsigned char getMonsterID2();
        unsigned char getMonsterID3();
        unsigned char getMonsterID4();
        char getGroup_count1();
        char getGroup_count2();
        char getGroup_count3();
        char getGroup_count4();
        static void setup();
        static void cleanup();
        static EncountSpecial* getRecord(int index);
    };
}
}
