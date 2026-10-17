#pragma once
#include <globaldefs.h>
#include "main/global/GlobalGamePart.hpp"

// Debug battle launcher
struct UnkBattleMenuPart : args::GamePart {
    int mode_;                                  // 0x04  0: encount, 1: select
    int x_;                                     // 0x08
    int y_;                                     // 0x0C
    int cursor_;                                // 0x10
    int tileId_;                                // 0x14
    int timeZone_;                              // 0x18
    int group_;                                 // 0x1C
    int monster_[4];                            // 0x20
    int count_[4];                              // 0x30
    int isStart_;                               // 0x40

    UnkBattleMenuPart();
    virtual void initialize();
    virtual void terminate();
    virtual void onExecutePart();
    virtual void onDrawPart();
    virtual void onWindowPart();
    virtual void onDebugPart();
    void unkfunc_0200928c();                    // encount mode input
    void unkfunc_02009378();                    // select mode input
    void unkfunc_02009504();                    // encount mode draw
    void unkfunc_0200959c();                    // select mode draw
};

extern UnkBattleMenuPart data_0209cf54;
