#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct EventList {
        unsigned short index;                       // 0x00
        unsigned short gold;                        // 0x02
        unsigned short weapon;                      // 0x04
        unsigned short armor;                       // 0x06
        unsigned short shield;                      // 0x08
        unsigned short helmet;                      // 0x0A
        unsigned short accessory;                   // 0x0C
        unsigned char level;                        // 0x0E
        unsigned char character;                    // 0x0F
        char caption[128];                          // 0x10
        char floor[8];                              // 0x90
        char byte_1;                                // 0x98
        unsigned char dummy0;                       // 0x99
        unsigned char dummy1;                       // 0x9A
        unsigned char dummy2;                       // 0x9B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static void setup();
        static void cleanup();
        static EventList* getRecord(int index);
        static unsigned int getArraySize();
        unsigned short getIndex();
        unsigned short getGold();
        unsigned short getWeapon();
        unsigned short getArmor();
        unsigned short getShield();
        unsigned short getHelmet();
        unsigned short getAccessory();
        unsigned char getLevel();
        unsigned char getCharacter();
        char* getFloor();
        char getChapter();
    };
}
}
