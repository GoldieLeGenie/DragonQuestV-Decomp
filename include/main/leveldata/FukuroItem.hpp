#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct FukuroItem {
        unsigned short fukuroNum;                   // 0x00
        unsigned char itemID1;                      // 0x02
        unsigned char itemID2;                      // 0x03
        unsigned char itemID3;                      // 0x04
        unsigned char itemID4;                      // 0x05
        unsigned char itemID5;                      // 0x06
        unsigned char itemID6;                      // 0x07
        unsigned char itemID7;                      // 0x08
        unsigned char itemID8;                      // 0x09
        unsigned char itemID9;                      // 0x0A
        unsigned char itemID10;                     // 0x0B
        unsigned char itemID11;                     // 0x0C
        unsigned char itemID12;                     // 0x0D
        unsigned char itemID13;                     // 0x0E
        unsigned char itemID14;                     // 0x0F
        unsigned char itemID15;                     // 0x10
        unsigned char itemID16;                     // 0x11
        unsigned char itemID17;                     // 0x12
        unsigned char dummy0;                       // 0x13

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static void setup();
        static void cleanup();
        unsigned char getItemID1();
        unsigned char getItemID2();
        unsigned char getItemID3();
        unsigned char getItemID4();
        unsigned char getItemID5();
        unsigned char getItemID6();
        unsigned char getItemID7();
        unsigned char getItemID8();
        unsigned char getItemID9();
        unsigned char getItemID10();
        unsigned char getItemID11();
        unsigned char getItemID12();
        unsigned char getItemID13();
        unsigned char getItemID14();
        unsigned char getItemID15();
        unsigned char getItemID16();
        unsigned char getItemID17();
        static FukuroItem* getRecord(int index);
    };
}
}
