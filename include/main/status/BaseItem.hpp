#pragma once
#include <globaldefs.h>

namespace status
{
    struct BaseItem {
        int itemIndex_;     // 0x00
        bool available_;    // 0x04
        int unk_08[5];      // 0x08

        BaseItem();
        static void initialize();
    };
} // namespace status
