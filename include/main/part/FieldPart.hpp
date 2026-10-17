#pragma once
#include <globaldefs.h>
#include "main/global/GlobalGamePart.hpp"

namespace fld
{
    struct FieldPart : args::GamePart {
        virtual void initialize();
        virtual void terminate();
        virtual void onExecutePart();
        virtual void onDrawPart();
        virtual void onWindowPart();
        virtual void onDebugPart();
        virtual void onSwapBuffersPart();
    };
} // namespace fld

extern fld::FieldPart g_FieldPart;
