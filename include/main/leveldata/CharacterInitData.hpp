#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct CharacterInitData {
        unsigned long exp;                          // 0x00
        unsigned short friendID;                    // 0x04
        unsigned short index;                       // 0x06
        unsigned short strength;                    // 0x08
        unsigned short agility;                     // 0x0A
        unsigned short vitality;                    // 0x0C
        unsigned short intelligence;                // 0x0E
        unsigned short luck;                        // 0x10
        unsigned short HP;                          // 0x12
        unsigned short MP;                          // 0x14
        unsigned short gold;                        // 0x16
        unsigned short weapon;                      // 0x18
        unsigned short armor;                       // 0x1A
        unsigned short shield;                      // 0x1C
        unsigned short hat;                         // 0x1E
        unsigned short battle1;                     // 0x20
        unsigned short battle2;                     // 0x22
        unsigned short battle3;                     // 0x24
        unsigned short battle9;                     // 0x26
        unsigned short normal1;                     // 0x28
        unsigned short normal2;                     // 0x2A
        unsigned short normal3;                     // 0x2C
        unsigned short normal9;                     // 0x2E
        unsigned short CGNumber;                    // 0x30
        unsigned short job;                         // 0x32
        unsigned short sex;                         // 0x34
        unsigned short actionMonsterID;             // 0x36
        unsigned short monsterID;                   // 0x38
        unsigned short battle4;                     // 0x3A
        unsigned short battle5;                     // 0x3C
        unsigned short battle6;                     // 0x3E
        unsigned short battle7;                     // 0x40
        unsigned short battle8;                     // 0x42
        unsigned short normal4;                     // 0x44
        unsigned short normal5;                     // 0x46
        unsigned short normal6;                     // 0x48
        unsigned short normal7;                     // 0x4A
        unsigned short normal8;                     // 0x4C
        unsigned char equipment;                    // 0x4E
        unsigned char icon;                         // 0x4F
        unsigned char mostLv;                       // 0x50
        unsigned char level;                        // 0x51
        unsigned char talk1;                        // 0x52
        unsigned char talk2;                        // 0x53
        char byte_1;                                // 0x54
        unsigned char dummy0;                       // 0x55
        unsigned char dummy1;                       // 0x56
        unsigned char dummy2;                       // 0x57

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[8008];

        unsigned long getExp();
        unsigned short getFriendID();
        unsigned short getStrength();
        unsigned short getAgility();
        unsigned short getVitality();
        unsigned short getIntelligence();
        unsigned short getLuck();
        unsigned short getHP();
        unsigned short getMP();
        unsigned short getWeapon();
        unsigned short getArmor();
        unsigned short getShield();
        unsigned short getHat();
        unsigned short getBattle1();
        unsigned short getBattle2();
        unsigned short getBattle3();
        unsigned short getNormal1();
        unsigned short getNormal2();
        unsigned short getNormal3();
        unsigned short getCGNumber();
        unsigned short getJob();
        unsigned short getSex();
        unsigned short getActionMonsterID();
        unsigned short getMonsterID();
        unsigned short getBattle4();
        unsigned short getBattle5();
        unsigned short getBattle6();
        unsigned short getBattle7();
        unsigned short getBattle8();
        unsigned short getNormal4();
        unsigned short getNormal5();
        unsigned short getNormal6();
        unsigned short getNormal7();
        unsigned short getNormal8();
        unsigned char getEquipment();
        unsigned char getIcon();
        unsigned char getMostLv();
        unsigned char getLevel();
        char getDemolition();
        char getCharacter();
        static void setup();
        static void cleanup();
        static CharacterInitData* getRecord(int index);
    };
}
}
