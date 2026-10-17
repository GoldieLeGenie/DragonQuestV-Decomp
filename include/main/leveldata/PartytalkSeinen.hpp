#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct PartytalkSeinen {
        unsigned long preMessage;                   // 0x00
        unsigned long message;                      // 0x04
        unsigned long no;                           // 0x08
        unsigned long value1;                       // 0x0C
        unsigned long value2;                       // 0x10
        unsigned long value4;                       // 0x14
        unsigned long format;                       // 0x18
        unsigned short start;                       // 0x1C
        unsigned short end;                         // 0x1E
        unsigned short floor;                       // 0x20
        char timezone;                              // 0x22
        char priority;                              // 0x23
        char condition1;                            // 0x24
        char condition2;                            // 0x25
        char alivePC;                               // 0x26
        char conduct;                               // 0x27
        char byte_1;                                // 0x28
        unsigned char dummy0;                       // 0x29
        unsigned char dummy1;                       // 0x2A
        unsigned char dummy2;                       // 0x2B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static void setup();
        static void cleanup();
        static PartytalkSeinen* getRecord(int index);
    };
}
}
