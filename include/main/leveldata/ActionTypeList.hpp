#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct ActionTypeList {
        unsigned char turn;                         // 0x00
        unsigned char typeID;                       // 0x01
        unsigned char pattern;                      // 0x02
        char byte_1;                                // 0x03
        char byte_2;                                // 0x04
        unsigned char dummy0;                       // 0x05
        unsigned char dummy1;                       // 0x06
        unsigned char dummy2;                       // 0x07

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[408];

        unsigned char getTurn();
        unsigned char getTypeID();
        unsigned char getPattern();
        static unsigned int getArraySize();
        static void setup();
        static void cleanup();
        static ActionTypeList* getRecord(int index);
    };
}
}
