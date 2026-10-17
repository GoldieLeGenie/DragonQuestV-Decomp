#pragma once
#include <globaldefs.h>

namespace twn {
    struct TownCurseSpotLight {
        int isEnd_;                                 // 0x00
        int isContraction_;                         // 0x04
        int size_;                                  // 0x08
        unsigned char alpha_;                       // 0x0C

        TownCurseSpotLight();
        ~TownCurseSpotLight();
        static TownCurseSpotLight& getSingleton();
        void setup();
        void execute();
    };
}
