#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"
#include "main/dss/UnkTextureObject.hpp"

namespace fld
{
    struct FieldSymbolAnimation {
        int animId_;                            // 0x00
        int enable_;                            // 0x04
        DataObject data_;                       // 0x08

        FieldSymbolAnimation();
        ~FieldSymbolAnimation();
        void setup(const char* filename);
        void calcAnim(UnkTextureObject* texture);
        void cleanup();
    };
} // namespace fld
