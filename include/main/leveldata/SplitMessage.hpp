#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct SplitMessage {
        unsigned long branch;                       // 0x00
        unsigned long carriageTwo;                  // 0x04
        unsigned long aliveTwo;                     // 0x08
        unsigned long monsterOne;                   // 0x0C
        unsigned long monsterTwo;                   // 0x10
        unsigned long monsterOneGroup;              // 0x14
        unsigned long monsterTwoGroup;              // 0x18
        unsigned long monsterMore;                  // 0x1C
        unsigned long targetMonster;                // 0x20
        unsigned long venom;                        // 0x24
        unsigned long notmanusa;                    // 0x28
        unsigned long manusa;                       // 0x2C
        unsigned long notempty;                     // 0x30
        unsigned long empty;                        // 0x34
        unsigned long alive;                        // 0x38
        unsigned long dead;                         // 0x3C
        unsigned long astoron;                      // 0x40
        unsigned long mosyasu;                      // 0x44
        unsigned long splitAvoid;                   // 0x48
        unsigned long split;                        // 0x4C
        unsigned long avoid;                        // 0x50
        unsigned long equip;                        // 0x54
        unsigned long notEquit;                     // 0x58
        unsigned long male;                         // 0x5C
        unsigned long female;                       // 0x60
        unsigned long human;                        // 0x64
        unsigned long monster;                      // 0x68
        unsigned long jump;                         // 0x6C
        unsigned long strait;                       // 0x70
        unsigned long wastePlace;                   // 0x74
        unsigned long rura;                         // 0x78
        unsigned long riremito;                     // 0x7C
        unsigned long wasteTime;                    // 0x80
        unsigned long cofferItem;                   // 0x84
        unsigned long cofferMonster;                // 0x88
        unsigned long cofferGold;                   // 0x8C
        unsigned long cofferNothing;                // 0x90
        unsigned long tuboItem;                     // 0x94
        unsigned long tuboMonster;                  // 0x98
        unsigned long tuboGold;                     // 0x9C
        unsigned long tuboNothing;                  // 0xA0
        unsigned long noTarget;                     // 0xA4
        unsigned long random1;                      // 0xA8
        unsigned long random2;                      // 0xAC
        unsigned long random3;                      // 0xB0
        unsigned long random4;                      // 0xB4
        unsigned long random5;                      // 0xB8
        unsigned long random6;                      // 0xBC
        unsigned long random7;                      // 0xC0
        unsigned long random8;                      // 0xC4
        unsigned long random9;                      // 0xC8
        unsigned long random10;                     // 0xCC
        unsigned long random11;                     // 0xD0
        unsigned long nothing;                      // 0xD4
        unsigned long special;                      // 0xD8
        unsigned long aliveOne;                     // 0xDC
        unsigned long carriageOne;                  // 0xE0
        unsigned long notvenom;                     // 0xE4
        unsigned long targetMale;                   // 0xE8
        unsigned long targetFemale;                 // 0xEC
        unsigned long targetHuman;                  // 0xF0

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[2440];

        static void setup();
        static void cleanup();
        static SplitMessage* getRecord(int index);
        static unsigned int getArraySize();
        unsigned long getBranch();
        unsigned long getCarriageTwo();
        unsigned long getAliveTwo();
        unsigned long getMonsterOne();
        unsigned long getMonsterTwo();
        unsigned long getMonsterOneGroup();
        unsigned long getMonsterTwoGroup();
        unsigned long getMonsterMore();
        unsigned long getTargetMonster();
        unsigned long getVenom();
        unsigned long getNotmanusa();
        unsigned long getManusa();
        unsigned long getNotempty();
        unsigned long getEmpty();
        unsigned long getAlive();
        unsigned long getDead();
        unsigned long getAstoron();
        unsigned long getMosyasu();
        unsigned long getSplitAvoid();
        unsigned long getSplit();
        unsigned long getAvoid();
        unsigned long getEquip();
        unsigned long getNotEquit();
        unsigned long getMale();
        unsigned long getFemale();
        unsigned long getHuman();
        unsigned long getMonster();
        unsigned long getJump();
        unsigned long getStrait();
        unsigned long getWastePlace();
        unsigned long getRura();
        unsigned long getRiremito();
        unsigned long getWasteTime();
        unsigned long getCofferItem();
        unsigned long getCofferMonster();
        unsigned long getCofferGold();
        unsigned long getCofferNothing();
        unsigned long getTuboItem();
        unsigned long getTuboMonster();
        unsigned long getTuboGold();
        unsigned long getTuboNothing();
        unsigned long getNoTarget();
        unsigned long getRandom1();
        unsigned long getRandom2();
        unsigned long getRandom3();
        unsigned long getRandom4();
        unsigned long getRandom5();
        unsigned long getRandom6();
        unsigned long getRandom7();
        unsigned long getRandom8();
        unsigned long getRandom9();
        unsigned long getRandom10();
        unsigned long getRandom11();
        unsigned long getNothing();
        unsigned long getSpecial();
        unsigned long getAliveOne();
        unsigned long getCarriageOne();
        unsigned long getNotvenom();
        unsigned long getTargetMale();
        unsigned long getTargetFemale();
        unsigned long getTargetHuman();
    };
}
}
