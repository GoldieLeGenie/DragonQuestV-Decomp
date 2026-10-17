#pragma once
#include <globaldefs.h>
#include "main/global/GlobalGamePart.hpp"

namespace btl
{
    struct BattlePart : args::GamePart {
        virtual void initialize();
        virtual void terminate();
        virtual void onExecutePart();
        virtual void onDrawPart();
        virtual void onWindowPart();
        virtual void onDebugPart();
    };
} // namespace btl

extern btl::BattlePart g_BattlePart;
