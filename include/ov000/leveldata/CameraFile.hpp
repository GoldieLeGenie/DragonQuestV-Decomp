#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct CameraFile {
        char file[16];                              // 0x00

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[1024];

        static void setup();
        static unsigned int getArraySize();
        static CameraFile* getRecord(int index);
        char* getFile();
    };
}
}
