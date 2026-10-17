#pragma once
#include <globaldefs.h>
#include "main/global/GlobalGamePart.hpp"

namespace twn
{
    struct TownPart : args::GamePart {
        virtual void initialize();
        virtual void terminate();
        virtual void onExecutePart();
        virtual void onDrawPart();
        virtual void onWindowPart();
        virtual void onDebugPart();
    };
} // namespace twn

extern twn::TownPart g_TownPart;
