#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct MirrorMessage {
        unsigned long message;              // 0x00
        unsigned char leader;               // 0x04
        char byte_1;                        // 0x05
        char byte_2;                        // 0x06
        unsigned char dummy0;               // 0x07

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[80];

        static void setup();
        static void cleanup();
        static MirrorMessage* getRecord(int index);
        static unsigned int getArraySize();

        char getYounenki();
        char getSeinenki();
        char getSounenki();
        char getCount();
        char getVoice1();
        char getVoice2();
        char getVoice3();
    };
}
}
