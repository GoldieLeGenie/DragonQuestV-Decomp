#pragma once
#include <globaldefs.h>
#include "main/dss/Render.hpp"

namespace casino {
    // base of the casino minigames (poker, slot)
    struct CasinoMiniGameBase {
        // vtable                               // 0x000
        Render* render_;                        // 0x004

        ~CasinoMiniGameBase();
        virtual void initialize() = 0;
        virtual void terminate() = 0;
        virtual void execute() = 0;
        virtual void draw() = 0;
        virtual char* getStageName() = 0;
        void setRender(Render* render);
    };
}
