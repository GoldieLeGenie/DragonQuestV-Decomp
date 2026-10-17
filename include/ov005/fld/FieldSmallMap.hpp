#pragma once
#include <globaldefs.h>
#include "main/window/GlobalMap.hpp"

namespace fld
{
    struct FieldSmallMap : window::GlobalMap {
        UnkMenuSprite unk_f8;                   // 0xF8 player marker

        FieldSmallMap();
        ~FieldSmallMap();
        virtual void setup();
        virtual void cleanup();
        virtual void draw();
        virtual void load();
        virtual void clear();
        virtual void playerMapPosition();
        virtual void setAlpha(unsigned char alpha);
    };
} // namespace fld
