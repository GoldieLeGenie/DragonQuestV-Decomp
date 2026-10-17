#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct SugorokuPanelList {
        unsigned long execMsg;                      // 0x00
        unsigned long divergentMsg;                 // 0x04
        unsigned short panelNo;                     // 0x08
        unsigned char dummy0;                       // 0x0A
        unsigned char dummy1;                       // 0x0B

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[120];

        static void setup();
        static void cleanup();
        static SugorokuPanelList* getRecord(int index);
    };
}
}
