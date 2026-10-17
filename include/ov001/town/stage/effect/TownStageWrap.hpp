#pragma once
#include <globaldefs.h>
#include "main/dss/UnkSprite2D.hpp"

namespace twn {
    struct TownStageWrap {
        enum EFFECT_TYPE {
            EFFECT_TYPE_DREAM1 = 0,
            EFFECT_TYPE_DREAM2 = 1,
            EFFECT_TYPE_DEATHPISARO = 2,
            EFFECT_TYPE_EVILPRIEST = 3,
        };

        UnkMenuSprite sprite_;                      // 0x00
        UnkMenuSprite unk_50;                       // 0x50
        int isData_;                                // 0xA0
        EFFECT_TYPE effectType_;                    // 0xA4
        int isDisplay_;                             // 0xA8
        short centerX_;                             // 0xAC
        short centerY_;                             // 0xAE
        short sizeX_;                               // 0xB0
        short sizeY_;                               // 0xB2
        fx32 scaleX_;                               // 0xB4
        fx32 scaleY_;                               // 0xB8
        int isSetup_;                               // 0xBC
        short colorR_;                              // 0xC0
        short colorG_;                              // 0xC2
        short colorB_;                              // 0xC4
        short counter_;                             // 0xC6
        short baseCounter_;                         // 0xC8

        TownStageWrap();
        ~TownStageWrap();
        void setup(EFFECT_TYPE type);
        void cleanup();
        void checkData();
        void setScalingX(fx32 scale);
        void setScalingY(fx32 scale);
        fx32 getScalingX();
        fx32 getScalingY();
        void setDisplay(int flag);
    };
}
