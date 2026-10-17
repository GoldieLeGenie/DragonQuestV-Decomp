#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct EncountData {
        unsigned short bgm;                         // 0x00
        unsigned char monsterA;                     // 0x02
        unsigned char monsterB;                     // 0x03
        unsigned char monsterC;                     // 0x04
        unsigned char monsterD;                     // 0x05
        unsigned char monsterE;                     // 0x06
        unsigned char monsterF;                     // 0x07
        unsigned char monsterG;                     // 0x08
        unsigned char monsterH;                     // 0x09
        unsigned char monsterI;                     // 0x0A
        unsigned char monsterJ;                     // 0x0B
        unsigned char particulParty;                // 0x0C
        unsigned char tileLevel;                    // 0x0D
        char byte_1;                                // 0x0E
        char byte_2;                                // 0x0F
        char byte_3;                                // 0x10
        char byte_4;                                // 0x11
        char byte_5;                                // 0x12
        char byte_6;                                // 0x13
        char byte_7;                                // 0x14
        char byte_8;                                // 0x15
        char byte_9;                                // 0x16
        char byte_10;                               // 0x17
        char byte_11;                               // 0x18
        char byte_12;                               // 0x19
        char byte_13;                               // 0x1A
        unsigned char dummy0;                       // 0x1B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[280];

        unsigned short getBgm();
        unsigned char getMonsterA();
        unsigned char getMonsterB();
        unsigned char getMonsterC();
        unsigned char getMonsterD();
        unsigned char getMonsterE();
        unsigned char getMonsterF();
        unsigned char getMonsterG();
        unsigned char getMonsterH();
        unsigned char getMonsterI();
        unsigned char getMonsterJ();
        unsigned char getParticulParty();
        unsigned char getTileLevel();
        char getEscape();
        char getParticulNight();
        char getInvite();
        char getEvent();
        char getFirstattack();
        char getGroup2();
        char getGroup3();
        char getGroup4();
        char getStandard();
        char getRatioA();
        char getRatioB();
        char getRatioC();
        char getRatioD();
        char getRatioE();
        char getRatioF();
        char getRatioG();
        char getRatioH();
        char getRatioI();
        char getRatioJ();
        char getRatioParticul();
        char getMaxA();
        char getMaxB();
        char getMaxC();
        char getMaxD();
        char getMaxE();
        char getMaxF();
        char getMaxG();
        char getMaxH();
        char getMaxI();
        char getMaxJ();
        static void setup();
        static void cleanup();
        static EncountData* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
