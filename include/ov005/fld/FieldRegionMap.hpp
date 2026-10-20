#pragma once
#include <globaldefs.h>
#include "main/window/WorldMap.hpp"

namespace fld
{
    // map of the regions outside the overworld (fairy world, dark world)
    struct FieldRegionMap : window::WorldMap {
        UnkMenuSprite playerMarker_;                   // 0xA8 player marker
        int world_;                             // 0xF8 world passed to symbolDraw

        FieldRegionMap();
        ~FieldRegionMap();
        virtual void setup() = 0;
        virtual void cleanup();
        virtual void draw();
        virtual void load();
        virtual void clear();
        virtual void playerMapPosition();
        virtual void setAlpha(unsigned char alpha);
        static dss::Vector2<int> convertMapPos(int x, int y);
    };
} // namespace fld
