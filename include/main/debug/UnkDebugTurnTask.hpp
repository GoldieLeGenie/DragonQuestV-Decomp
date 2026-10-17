#pragma once
#include <globaldefs.h>
#include "main/debug/UnkDebugTask.hpp"

// Walks the town player over a 5x5 grid of positions, one every ten frames
struct UnkDebugTurnTask : UnkDebugTask {
    int active_;                                // 0x10
    int wait_;                                  // 0x14
    int count_;                                 // 0x18

    UnkDebugTurnTask();
    virtual void vf04();
    virtual void vf0c();
};

extern UnkDebugTurnTask data_020f3520;
