#pragma once
#include <globaldefs.h>

namespace btl
{
    struct EncountScreenOver {
        int* monsterIndex_;                     // 0x00
        int* monsterCount_;                     // 0x04
        int monsterGroupWidth_[4];              // 0x08
        int count_;                             // 0x18

        EncountScreenOver();
        ~EncountScreenOver();
        void setup(int* monsterIndex, int* monsterCount);
        void execThinning();
        bool checkScreenOver();
        void setThinning(int count);
    };
} // namespace btl
