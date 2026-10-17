#pragma once
#include <globaldefs.h>
#include "main/global/GlobalGamePart.hpp"

namespace casino {
    struct CasinoPart : args::GamePart {
        virtual void initialize();
        virtual void terminate();
        virtual void onExecutePart();
        virtual void onDrawPart();
        virtual void onWindowPart();
        virtual void onDebugPart();
    };
}

extern casino::CasinoPart g_CasinoPart;
