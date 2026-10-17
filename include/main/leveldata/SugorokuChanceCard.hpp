#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct SugorokuChanceCard {
        unsigned long exec;                         // 0x00
        unsigned long divergent;                    // 0x04
        unsigned char chance;                       // 0x08
        char byte_1;                                // 0x09
        char byte_2;                                // 0x0A
        unsigned char dummy0;                       // 0x0B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[468];

        static void setup();
        static void cleanup();
        static SugorokuChanceCard* getRecord(int index);

        char getFloor1();
        char getFloor2();
        char getFloor3();
        char getFloor4();
        char getFloor5();
        char getFloor6();
        char getFloor7();
        char getFloor8();
        char getFloor9();
        char getFloor10();
        char getFloor11();
        char getFloor12();
        char getFloor13();
        char getFloor14();
    };
}
}
