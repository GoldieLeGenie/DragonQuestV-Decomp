#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct MonsterData {
        unsigned short index;                       // 0x00
        unsigned short HP;                          // 0x02
        unsigned short MP;                          // 0x04
        unsigned short attack;                      // 0x06
        unsigned short defence;                     // 0x08
        unsigned short money;                       // 0x0A
        unsigned short exp;                         // 0x0C
        unsigned short action1;                     // 0x0E
        unsigned short action2;                     // 0x10
        unsigned short action3;                     // 0x12
        unsigned short action4;                     // 0x14
        unsigned short action5;                     // 0x16
        unsigned short action6;                     // 0x18
        unsigned short item;                        // 0x1A
        unsigned short animIndex;                   // 0x1C
        unsigned char party;                        // 0x1E
        unsigned char agility;                      // 0x1F
        unsigned char ratio;                        // 0x20
        unsigned char animAll;                      // 0x21
        unsigned char anim1;                        // 0x22
        unsigned char anim2;                        // 0x23
        unsigned char anim3;                        // 0x24
        unsigned char anim4;                        // 0x25
        unsigned char anim5;                        // 0x26
        unsigned char anim6;                        // 0x27
        char byte_1;                                // 0x28
        char byte_2;                                // 0x29
        char byte_3;                                // 0x2A
        char byte_4;                                // 0x2B
        char byte_5;                                // 0x2C
        char byte_6;                                // 0x2D
        char byte_7;                                // 0x2E
        char byte_8;                                // 0x2F
        char byte_9;                                // 0x30
        char byte_10;                               // 0x31
        char byte_11;                               // 0x32
        unsigned char dummy0;                       // 0x33

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[12792];

        unsigned short getIndex();
        unsigned short getHP();
        unsigned short getMP();
        unsigned short getAttack();
        unsigned short getDefence();
        unsigned short getMoney();
        unsigned short getExp();
        unsigned short getAction1();
        unsigned short getAction2();
        unsigned short getAction3();
        unsigned short getAction4();
        unsigned short getAction5();
        unsigned short getAction6();
        unsigned short getItem();
        unsigned short getAnimIndex();
        unsigned char getParty();
        unsigned char getAgility();
        unsigned char getRatio();
        unsigned char getAnimAll();
        unsigned char getAnim1();
        unsigned char getAnim2();
        unsigned char getAnim3();
        unsigned char getAnim4();
        unsigned char getAnim5();
        unsigned char getAnim6();
        char getPosition();
        char getGroup1();
        char getGroup2();
        char getGroup3();
        char getGroup4();
        char getGroup5();
        char getGroup6();
        char getFocus();
        char getInteger();
        char getTimes();
        char getAvoid();
        char getMera();
        char getGira();
        char getIo();
        char getHyado();
        char getBagi();
        char getDein();
        char getManusa();
        char getRarihoma();
        char getZaki();
        char getNifram();
        char getMahotora();
        char getMahoton();
        char getMedapani();
        char getRukani();
        char getRukanan();
        char getMegante();
        char getEmbrace();
        char getPoison();
        char getVenom();
        char getParalysis();
        char getRest();
        char getDragon();
        char getMetal();
        char getRegistBlizzard();
        char getRegistFire();
        char getZombi();
        char getRariho();
        char getPattern();
        char getHeal();
        char getInit();
        char getInitRatio();
        char getItemRatio();
        static void setup();
        static void cleanup();
        static MonsterData* getRecord(int index);
    };
}
}
