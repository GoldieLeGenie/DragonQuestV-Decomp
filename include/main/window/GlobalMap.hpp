#pragma once
#include <globaldefs.h>
#include "main/window/WorldMap.hpp"

namespace window {
    /* vtable 0x020942c4 */
    class GlobalMap : public WorldMap {
    public:
        UnkMenuSprite unk_a8;                       // 0xA8 veil sprite

        GlobalMap();
        ~GlobalMap();
        virtual void setup();
        virtual void cleanup();
        virtual void draw();
        virtual void load();
        virtual void clear();
        virtual void playerMapPosition();
        virtual void setAlpha(unsigned char alpha);
        void unkfunc_020195f0();
        void unkfunc_02019704(int x, int y, bool veil);
        static dss::Vector2<int> convertMapPos(int x, int y);
    };
}
