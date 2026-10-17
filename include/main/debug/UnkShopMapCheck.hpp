#pragma once
#include <globaldefs.h>
#include "main/debug/UnkDebugTask.hpp"

// Starts the town map of every shop event in turn
struct UnkShopMapCheck : UnkDebugTask {
    int waitFrame_;                             // 0x10
    int startIndex_;                            // 0x14
    int endIndex_;                              // 0x18
    int unk_1c;                                 // 0x1C
    int index_;                                 // 0x20

    UnkShopMapCheck();
    virtual void vf04();
    virtual void vf0c();
    void unkfunc_02038118();
    void unkfunc_02038148();
};

extern UnkShopMapCheck data_020dc058;
