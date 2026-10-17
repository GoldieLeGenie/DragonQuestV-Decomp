#pragma once
#include <globaldefs.h>
#include "main/global/GlobalGamePart.hpp"

// Shows a save/card error message then goes to the next part
struct GameEndPart : args::GamePart {
    int type_;                                  // 0x04
    int message_;                               // 0x08
    int nextPart_;                              // 0x0C

    GameEndPart();
    virtual void initialize();
    virtual void terminate();
    virtual void onExecutePart();
    virtual void onDrawPart();
    virtual void onWindowPart();
    virtual void onDebugPart();
    void unkfunc_02041a4c(int type);
    void unkfunc_02041a58(int type, int nextPart);
    void unkfunc_02041ab8(int type);
    void unkfunc_02041acc(int type, int nextPart);
};

extern GameEndPart g_GameEndPart;
