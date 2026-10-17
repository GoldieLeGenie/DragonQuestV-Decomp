#pragma once
#include <globaldefs.h>
#include "main/dss/Render.hpp"
#include "ov012/casino/CasinoMiniGameBase.hpp"

namespace casino {
    struct CasinoSystem {
        CasinoMiniGameBase* minigame;           // 0x000
        Render render_;                         // 0x004

        CasinoSystem();
        ~CasinoSystem();
        static CasinoSystem* getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
    };
}
