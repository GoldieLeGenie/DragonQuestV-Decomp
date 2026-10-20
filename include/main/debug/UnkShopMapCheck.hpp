#pragma once
#include <globaldefs.h>
#include "main/debug/UnkDebugTask.hpp"

// Starts the town map of every shop event in turn
struct UnkShopMapCheck : UnkDebugTask {
    int waitFrame_;                             // 0x10
    int startIndex_;                            // 0x14
    int endIndex_;                              // 0x18
    int maxIndex_;                                 // 0x1C
    int index_;                                 // 0x20

    UnkShopMapCheck();
    virtual void vf04();
    virtual void vf0c();
    void nextShop();
    void startShopMap();
};

extern UnkShopMapCheck data_020dc058;
