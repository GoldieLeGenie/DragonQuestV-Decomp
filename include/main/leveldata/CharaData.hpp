#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct CharaData {
        unsigned short index;                       // 0x00
        unsigned char height;                       // 0x02
        unsigned char width;                        // 0x03
        char byte_1;                                // 0x04
        unsigned char dummy0;                       // 0x05
        unsigned char dummy1;                       // 0x06
        unsigned char dummy2;                       // 0x07

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[2048];

        unsigned short getIndex();
        unsigned char getHeight();
        unsigned char getWidth();
        void setWidth(unsigned char width);
        char getVoice();
        char getType();
        char getAnim();
        void setType(char type);
        static void setup();
        static void cleanup();
        static CharaData* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
