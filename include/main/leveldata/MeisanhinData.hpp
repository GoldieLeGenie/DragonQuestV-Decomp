#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct MeisanhinData {
        unsigned long message1;                     // 0x00
        unsigned long message2;                     // 0x04
        unsigned long message3;                     // 0x08
        unsigned long message4;                     // 0x0C
        unsigned long mizusashiMsg;                 // 0x10
        unsigned long housekiMsg;                   // 0x14
        unsigned long migakiMsg;                    // 0x18
        unsigned short itemid;                      // 0x1C
        unsigned char index;                        // 0x1E
        unsigned char point3;                       // 0x1F
        unsigned char point4;                       // 0x20
        unsigned char point5;                       // 0x21
        unsigned char point6;                       // 0x22
        char byte_1;                                // 0x23
        char byte_2;                                // 0x24
        unsigned char dummy0;                       // 0x25
        unsigned char dummy1;                       // 0x26
        unsigned char dummy2;                       // 0x27

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[1400];

        static void setup();
        static void cleanup();
        static unsigned int getArraySize();
        unsigned short getItemid();
        unsigned long getMizusashiMsg();
        unsigned long getHousekiMsg();
        unsigned long getMigakiMsg();
        char getPoint1();
        char getPoint2();
        unsigned char getPoint3();
        unsigned char getPoint4();
        unsigned char getPoint5();
        unsigned char getPoint6();
        char getLevel();
        static MeisanhinData* getRecord(int index);
    };
}
}
