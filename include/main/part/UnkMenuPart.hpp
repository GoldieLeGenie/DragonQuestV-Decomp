#pragma once
#include <globaldefs.h>
#include "main/global/GlobalGamePart.hpp"

// Boot logos (Square Enix, ArtePiazza), then the opening
struct UnkMenuPart : args::GamePart {
    virtual void initialize();
    virtual void terminate();
    virtual void onExecutePart();
    virtual void onDrawPart();
    virtual void onWindowPart();
    virtual void onDebugPart();
};

extern UnkMenuPart data_0209cfd0;
