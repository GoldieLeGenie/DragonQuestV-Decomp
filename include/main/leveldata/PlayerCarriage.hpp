#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct PlayerCarriage {
        unsigned short floor;                       // 0x00
        unsigned char area;                         // 0x02
        char byte_1;                                // 0x03

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        unsigned short getFloor();
        unsigned char getArea();
        char getSorting();
        char getMostRelive();
        char getRelive();
        static void setup();
        static void cleanup();
        static PlayerCarriage* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
