#pragma once
#include <globaldefs.h>
#include "main/dss/Sprite2D.hpp"
#include "ov012/casino/CasinoMiniGameBase.hpp"

namespace casino {
    struct CasinoPoker : CasinoMiniGameBase {
        static const char* stagePoker;

        UnkMenuSprite sprite_;                  // 0x008 upper screen background

        CasinoPoker();
        ~CasinoPoker();
        static CasinoPoker* getSingleton();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
        virtual char* getStageName();
    };
}
