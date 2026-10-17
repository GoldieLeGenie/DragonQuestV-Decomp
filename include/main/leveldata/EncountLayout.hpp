#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct EncountLayout {
        unsigned short floorNum;                    // 0x00
        unsigned char chapter;                      // 0x02
        unsigned char tileID;                       // 0x03

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[1120];

        static void setup();
        static void cleanup();
        unsigned short getFloorNum();
        unsigned char getChapter();
        unsigned char getTileID();
        static unsigned int getArraySize();
        static EncountLayout* getRecord(int index);
    };
}
}
