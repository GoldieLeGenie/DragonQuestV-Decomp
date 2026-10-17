#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct ItemData {
        unsigned long casino;                       // 0x00
        unsigned long menuMes;                      // 0x04
        unsigned long MeisanhinMsg;                 // 0x08
        unsigned long CommentMsg;                   // 0x0C
        unsigned short BuyPrice;                    // 0x10
        unsigned short SellPrice;                   // 0x12
        unsigned short samall;                      // 0x14
        unsigned short effect;                      // 0x16
        unsigned short action;                      // 0x18
        unsigned short battleAction;                // 0x1A
        unsigned short typeSort;                    // 0x1C
        unsigned short nameSort;                    // 0x1E
        unsigned char equipType;                    // 0x20
        unsigned char CommentID;                    // 0x21
        unsigned char CommentType;                  // 0x22
        unsigned char type;                         // 0x23
        char byte_1;                                // 0x24
        char byte_2;                                // 0x25
        char byte_3;                                // 0x26
        char byte_4;                                // 0x27
        char byte_5;                                // 0x28
        unsigned char dummy0;                       // 0x29
        unsigned char dummy1;                       // 0x2A
        unsigned char dummy2;                       // 0x2B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static ItemData* getRecord(int index);
        unsigned long getCasino();
        unsigned long getMenuMes();
        unsigned long getMeisanhinMsg();
        unsigned long getCommentMsg();
        unsigned short getBuyPrice();
        unsigned short getSellPrice();
        unsigned short getEffect();
        unsigned short getAction();
        unsigned short getBattleAction();
        unsigned short getTypeSort();
        unsigned char getEquipType();
        unsigned char getCommentID();
        unsigned char getCommentType();
        unsigned char getType();
        char getProtagonist();
        char getBianca();
        char getHenry();
        char getFlora();
        char getDevora();
        char getSancho();
        char getPipin();
        char getSon();
        char getDaughter();
        char getMonster1();
        char getMonster2();
        char getMonster3();
        char getMonster4();
        char getMonster5();
        char getMonster6();
        char getMonster7();
        char getMonster8();
        char getMonster9();
        char getMonster10();
        char getMonster11();
        char getMonster12();
        char getMonster13();
        char getMonster14();
        char getMonster15();
        char getMonster16();
        char getLost();
        char getCurse();
        char getImportant();
        char getSell();
        char getThrow();
        char getOrderby();
        char getChange();
        static char dataRegion[11616];
        static void setup();
        static void cleanup();
    };
}
}
