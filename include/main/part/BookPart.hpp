#pragma once
#include <globaldefs.h>
#include "main/global/GlobalGamePart.hpp"

namespace book {
    struct BookPart : args::GamePart {
        virtual void initialize();
        virtual void terminate();
        virtual void onExecutePart();
        virtual void onDrawPart();
        virtual void onWindowPart();
        virtual void onDebugPart();
    };
}

extern book::BookPart g_BookPart;
