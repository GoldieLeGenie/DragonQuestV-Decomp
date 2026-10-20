#pragma once
#include <globaldefs.h>

// Debug state machines updated every frame by the debug display
struct UnkDebugTask {
    // vtable                                   // 0x00
    int requestState_;                          // 0x04
    int state_;                                 // 0x08 2: running, 3: finished
    int frame_;                                 // 0x0C frames spent in the current state

    virtual void update();            // update: vf0c while running, vf10 once finished
    virtual void vf04() = 0;                    // start
    virtual void vf08();                        // finish
    virtual void vf0c() = 0;
    virtual void vf10();
};
