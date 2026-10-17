#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct FurnitureList {
        unsigned long floor;                        // 0x00

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        unsigned long getFloor();
        static void setup();
        static void cleanup();
        static FurnitureList* getRecord(int index);
        static unsigned int getArraySize();
    };
}
}
