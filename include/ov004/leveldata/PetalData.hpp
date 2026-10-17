#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    // ending petal (hanabira) animation table
    struct PetalData {
        unsigned char position;                     // 0x00
        unsigned char index;                        // 0x01
        char byte_1;                                // 0x02
        unsigned char dummy0;                       // 0x03

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[248];

        static void setup();
        static PetalData* getRecord(int index);
    };
}
}
