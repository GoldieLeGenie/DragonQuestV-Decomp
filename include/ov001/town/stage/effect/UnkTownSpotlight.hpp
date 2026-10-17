#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkSprite2D.hpp"
#include "main/window/UnkMapPoint.hpp"

namespace twn {
    // one light circle drawn over a map point on both screens
    struct UnkTownSpotlightLight {
        int size_;                                  // 0x00
        int index_;                                 // 0x04 map point
        int enable_;                                // 0x08
        dss::Fix32 unk_0c;                          // 0x0C
        int x_;                                     // 0x10
        int y_;                                     // 0x14
        dss::Fix32Vector3* pos_;                    // 0x18
        unsigned short color_;                      // 0x1C
        unsigned char alpha_;                       // 0x1E

        static UnkMenuSprite sprite_[2];

        UnkTownSpotlightLight();
        ~UnkTownSpotlightLight();
        void unkfunc_0212e6b0(int index, dss::Fix32Vector3* pos);
        void unkfunc_0212e6c0();
        static void unkfunc_0212e6c8();
        static void unkfunc_0212e73c();
        void unkfunc_0212e758(int screen);
        void unkfunc_0212e7c0();
    };

    // darkness over the screens with light circles around the map points
    struct UnkTownSpotlight {
        static const int LIGHT_MAX = 8;

        int enable_;                                // 0x000
        int setup_;                                 // 0x004
        UnkSprite2D blind_;                         // 0x008
        UnkTownSpotlightLight light_[LIGHT_MAX];    // 0x040
        dss::Fix32 unk_140;                         // 0x140

        UnkTownSpotlight();
        ~UnkTownSpotlight();
        void unkfunc_0212e850();
        void unkfunc_0212e8b4(int index, dss::Fix32Vector3* pos);
        void unkfunc_0212e8c4(int index);
        void unkfunc_0212e8d4();
        void unkfunc_0212e900();
        void unkfunc_0212e920();
        void unkfunc_0212e95c(int enable);
        void setBlindAlpha(unsigned char alpha);
        void unkfunc_0212e974(int r, int g, int b);
    };
}
