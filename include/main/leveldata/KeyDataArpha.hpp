#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct KeyDataArpha {
        unsigned long Data;                         // 0x00
        unsigned short No;                          // 0x04
        unsigned char dummy0;                       // 0x06
        unsigned char dummy1;                       // 0x07

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static void setup();
        static void cleanup();
        static KeyDataArpha* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
