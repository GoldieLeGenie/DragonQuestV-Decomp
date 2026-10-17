#pragma once
#include <globaldefs.h>

namespace fld
{
    struct FieldSymbolManager {
        struct SmallMapSymbol {
            unsigned char type;                 // 0x0
            unsigned char x;                    // 0x1
            unsigned char y;                    // 0x2
        };

        int index_;                             // 0x000
        SmallMapSymbol small_[128];             // 0x004
        int walkX_;                             // 0x184
        int walkY_;                             // 0x188
        int resetFlag_;                         // 0x18C

        FieldSymbolManager();
        ~FieldSymbolManager();
        static FieldSymbolManager& getSingleton();
        void initialize();
        void terminate();
        bool checkSymbol(int index, int flag);
        void setResetFlag(bool flag);
    };
} // namespace fld
