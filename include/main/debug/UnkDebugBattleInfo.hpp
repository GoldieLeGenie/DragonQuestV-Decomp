#pragma once
#include <globaldefs.h>
#include "main/debug/UnkDebugDisplay.hpp"
#include "main/status/HaveStatusInfo.hpp"

// Debug battle page: status of one player or monster
struct UnkDebugBattleInfo : UnkDebugDisplay {
    // vtable                                   // 0x00
    int type_;                                  // 0x04  1: player, 2: monster
    int index_;                                 // 0x08
    int blink_;                                 // 0x0C  frames the target arrow blinks
    int unk_10;                                 // 0x10
    int showHeap_;                              // 0x14
    int showLog_;                               // 0x18

    UnkDebugBattleInfo();
    virtual void initialize();
    virtual void draw();
    void unkfunc_020273fc(int x, int y);        // free heap / VRAM
    void unkfunc_02027460(int x, int y, status::HaveStatusInfo* info);  // status of a player or monster
    void unkfunc_020278ac(int x, int y);        // message IDs of the debug info page
};

extern UnkDebugBattleInfo data_020c2ce4;
