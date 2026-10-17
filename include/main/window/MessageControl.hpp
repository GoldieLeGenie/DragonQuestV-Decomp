#pragma once
#include <globaldefs.h>
#include "main/window/InputControl.hpp"

namespace window {
    /* vtable 0x0209429c */
    class MessageControl : public InputControl {
    public:
        enum {
            MESSAGE = 0,
            CLOSE_WAIT = 1,
            END_MESSAGE = 2,
        };

        int back_;                                  // 0x08

        MessageControl();
        ~MessageControl();
        virtual void execute();
        virtual int getPhase();
        virtual void setup();
        void startMessage();
        bool isMessageEnd();
        void MESSAGEWINDOW(int message, int count);
        void MESSAGECOMMONWINDOW();
        void ADDCOMMONWINDOW(int message);
        void WAITCOMMONWINDOW();
        void CLEARCOMMONWINDOW();
        void SERIALCOMMONWINDOW(int message);
    };

    extern MessageControl gMessageControl;
}
