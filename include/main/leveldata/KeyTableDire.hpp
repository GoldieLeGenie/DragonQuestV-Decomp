#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct KeyTableDire {
        unsigned char position;                     // 0x00
        unsigned char right;                        // 0x01
        unsigned char Up;                           // 0x02
        unsigned char down;                         // 0x03
        unsigned char left;                         // 0x04
        unsigned char No;                           // 0x05
        unsigned char command;                      // 0x06
        unsigned char dummy0;                       // 0x07

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static void setup();
        static void cleanup();
        static KeyTableDire* getRecord(int index);
    };
}
}
