#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct FieldSymbol {
        unsigned long message;                      // 0x00
        unsigned short uid;                         // 0x04
        unsigned short item;                        // 0x06
        unsigned char posY;                         // 0x08
        unsigned char posX;                         // 0x09
        unsigned char type;                         // 0x0A
        char byte_1;                                // 0x0B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[1140];

        unsigned short getUid();
        unsigned char getPosY();
        unsigned char getPosX();
        char getWorld();
        char getSymbol();
        static unsigned int getArraySize();
        static void setup();
        static void cleanup();
        static FieldSymbol* getRecord(int index);
    };
}
}
