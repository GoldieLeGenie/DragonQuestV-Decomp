#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct PartytalkSeinenIndex {
        unsigned long floor;                        // 0x00
        unsigned long offset;                       // 0x04
        unsigned short size;                        // 0x08
        unsigned char dummy0;                       // 0x0A
        unsigned char dummy1;                       // 0x0B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static void setup();
        static void cleanup();
        static unsigned int getArraySize();
        static PartytalkSeinenIndex* getRecord(int index);
    };
}
}
