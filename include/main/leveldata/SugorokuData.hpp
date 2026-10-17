#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct SugorokuData {
        unsigned short moneyMin;                    // 0x00
        unsigned short moneyMax;                    // 0x02
        unsigned short item;                        // 0x04
        unsigned short ratio256;                    // 0x06
        unsigned char index;                        // 0x08
        unsigned char times;                        // 0x09
        unsigned char ratio32;                      // 0x0A
        unsigned char encount1;                     // 0x0B
        unsigned char encount2;                     // 0x0C
        unsigned char encount3;                     // 0x0D
        unsigned char encount4;                     // 0x0E
        unsigned char dummy0;                       // 0x0F

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[2688];

        static void setup();
        static void cleanup();
        static SugorokuData* getRecord(int index);
        static unsigned int getArraySize();
        unsigned short getMoneyMin();
        unsigned short getMoneyMax();
    };
}
}
