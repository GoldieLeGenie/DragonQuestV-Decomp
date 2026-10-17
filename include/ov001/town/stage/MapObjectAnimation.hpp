#pragma once
#include <globaldefs.h>

namespace twn {
    struct MapObjectAnimation {
        static const int ANIM_COUNT = 4;

        int animNo_[ANIM_COUNT];                    // 0x00
        int mapUid_;                                // 0x10
        char playIndex_;                            // 0x14
        char count_;                                // 0x15

        MapObjectAnimation();
        void setMapUid(int uid);
        int getMapUid();
        void start();
        bool isStop();
        int getPlayNo();
        bool isNext();
        void clear();
        bool registAnimation(int anim);
        int getNextPlayNo();
    };
}
