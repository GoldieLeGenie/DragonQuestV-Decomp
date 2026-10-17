#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"
#include "main/leveldata/PlayerData1.hpp"

namespace dq5 {
namespace level {
    // level tables of the characters (one file per character)
    struct CharacterData {
        static const char* filename_;
        static ExcelBinaryData binary_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[36];

        static PlayerData1* getRecord(int index, int level);
    };
}
}
