#pragma once
#include <globaldefs.h>
#include "main/dss/Sprite2D.hpp"

namespace window {
    /* vtable 0x02094350 */
    class WorldMap {
    public:
        UnkMenuSprite mapSprite_;                       // 0x04
        UnkMenuSprite symbolSprite_;                       // 0x54 symbol sprite
        int blinkCount_;                                 // 0xA4 symbol blink counter

        WorldMap();
        ~WorldMap();
        virtual void setup() = 0;
        virtual void cleanup() = 0;
        virtual void draw() = 0;
        virtual void load() = 0;
        virtual void clear() = 0;
        virtual void playerMapPosition() = 0;
        virtual void setAlpha(unsigned char alpha) = 0;
        void symbolDraw(int world);
    };
}
