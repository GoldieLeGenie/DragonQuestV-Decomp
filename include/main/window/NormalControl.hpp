#pragma once
#include <globaldefs.h>
#include "main/window/InputControl.hpp"

namespace window {
    /* vtable 0x020942b0 */
    class NormalControl : public InputControl {
    public:
        enum {
            CONTROL_NORMAL = 0,
            CONTROL_NPC_MESSAGE = 1,
            CONTROL_PARTY_TALK = 2,
        };

        int state_;                                 // 0x08

        ~NormalControl();
        virtual void execute();
        virtual int getPhase();
        virtual void setup();
        void executePlayer();
        void checkCamera();
    };

    extern NormalControl gNormalControl;
}
