#pragma once
#include <globaldefs.h>

namespace window {
    /* vtable 0x02094274 */
    class InputControl {
    public:
        enum {
            PHASE_NORMAL = 1,
            PHASE_SHOPMENU = 2,
            PHASE_MENU = 4,
            PHASE_MESSAGE = 8,
            PHASE_MAP = 16,
            PHASE_SHOPLIST = 32,
            PHASE_EVENT = 64,
            PHASE_GLOBALMAP = 128,
            PHASE_PARTY_TALK = 256,
        };

        int state_;                                 // 0x04

        static int prev_;
        static int next_;

        InputControl();
        ~InputControl();
        virtual void execute() = 0;
        virtual int getPhase() = 0;
        virtual void setup() = 0;
        void playerLock(bool flag);
        bool isPlayerLock();
        void setupIcon();
    };
}
