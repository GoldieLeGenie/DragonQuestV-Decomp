#pragma once
#include <globaldefs.h>
#include "main/global/GlobalGamePart.hpp"

namespace race {
    struct SlimeRacePart : args::GamePart {
        virtual void initialize();
        virtual void terminate();
        virtual void onExecutePart();
        virtual void onDrawPart();
        virtual void onWindowPart();
        virtual void onDebugPart();
        virtual void onSwapBuffersPart();
    };
}

extern race::SlimeRacePart g_SlimeRacePart;
