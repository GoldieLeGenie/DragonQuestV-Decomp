#pragma once
#include <globaldefs.h>
#include "main/global/GlobalGamePart.hpp"
#include "main/global/UnkBuildDate.hpp"

// Part select screen (all its functions are empty)
struct UnkTitlePart : args::GamePart {
    int unk_04;                                 // 0x04
    int unk_08;                                 // 0x08
    UnkBuildDate buildDate_;                    // 0x0C

    virtual void initialize();
    virtual void terminate();
    virtual void onExecutePart();
    virtual void onDrawPart();
    virtual void onWindowPart();
    virtual void onDebugPart();
};

extern UnkTitlePart data_0209cf9c;
