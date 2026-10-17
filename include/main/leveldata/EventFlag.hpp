#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct EventFlag {
        unsigned short flag1;                       // 0x00
        unsigned short flag2;                       // 0x02
        unsigned short flag3;                       // 0x04
        unsigned short flag4;                       // 0x06
        unsigned short flag5;                       // 0x08
        unsigned short flag6;                       // 0x0A
        unsigned short flag7;                       // 0x0C
        unsigned short flag8;                       // 0x0E
        unsigned short flag9;                       // 0x10
        unsigned short flag10;                      // 0x12
        unsigned short flag11;                      // 0x14
        unsigned short flag12;                      // 0x16
        unsigned short waitFlag1;                   // 0x18
        unsigned short waitFlag2;                   // 0x1A
        unsigned short waitFlag3;                   // 0x1C
        unsigned short waitFlag4;                   // 0x1E
        unsigned short waitFlag5;                   // 0x20
        unsigned short waitFlag6;                   // 0x22
        unsigned short index;                       // 0x24
        unsigned char NPC;                          // 0x26
        char byte_1;                                // 0x27
        char byte_2;                                // 0x28
        char byte_3;                                // 0x29
        unsigned char dummy0;                       // 0x2A
        unsigned char dummy1;                       // 0x2B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static void setup();
        static void cleanup();
        static EventFlag* getRecord(int index);
        unsigned short getFlag1();
        unsigned short getFlag2();
        unsigned short getFlag3();
        unsigned short getFlag4();
        unsigned short getFlag5();
        unsigned short getFlag6();
        unsigned short getFlag7();
        unsigned short getFlag8();
        unsigned short getFlag9();
        unsigned short getFlag10();
        unsigned short getFlag11();
        unsigned short getFlag12();
        unsigned short getWaitFlag1();
        unsigned short getWaitFlag2();
        unsigned short getWaitFlag3();
        unsigned short getWaitFlag4();
        unsigned short getWaitFlag5();
        unsigned short getWaitFlag6();
        unsigned char getNPC();
        char getTownFlag1();
        char getTownFlag2();
        char getTownFlag3();
        char getTownFlag4();
        char getTownFlag5();
        char getTownFlag6();
        char getTownFlag7();
        char getTownFlag8();
        char getTownFlag9();
        char getTownFlag10();
        char getTownFlag11();
        char getTownFlag12();
        char getTownFlag13();
        char getTownFlag14();
        char getTownFlag15();
        char getTownFlag16();
        char getTownFlag17();
        char getTownFlag18();
        char getTownFlag19();
        char getTownFlag20();
    };
}
}
