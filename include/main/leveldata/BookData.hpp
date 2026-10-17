#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct BookData {
        unsigned short index;                       // 0x00
        unsigned char friendly;                     // 0x02
        unsigned char dummy0;                       // 0x03

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[48];

        unsigned short getIndex();
        unsigned char getFriendly();
        static void setup();
        static void cleanup();
        static BookData* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
