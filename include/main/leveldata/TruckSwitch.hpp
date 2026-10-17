#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct TruckSwitch {
        unsigned short railUid;                     // 0x00
        unsigned short floor;                       // 0x02
        unsigned short split;                       // 0x04
        unsigned short next;                        // 0x06
        unsigned short switchUid;                   // 0x08
        char byte_1;                                // 0x0A
        unsigned char dummy0;                       // 0x0B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        unsigned short getRailUid();
        unsigned short getSplit();
        unsigned short getSwitchUid();
        char getSwitchAnim();
        char getRailAnim();
        static void setup();
        static void cleanup();
        static TruckSwitch* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
