#pragma once
#include <globaldefs.h>

namespace btl {
    struct EncountSpecial {
        unsigned short monsterIndex_[4];        // 0x0
        unsigned short monsterCount_[4];        // 0x8

        EncountSpecial();
        ~EncountSpecial();
        void setup(int index);
        int getMonsterIndex(int group);
        int getMonsterCount(int group);
    };

    int getAppearCount(int index);
}
