#pragma once
#include <globaldefs.h>
#include "main/window/InputControl.hpp"

namespace window {
    /* vtable 0x02094288 */
    class MenuControl : public InputControl {
    public:
        enum {
            OPEN_SETUP = 0,
            OPEN_SETUP1 = 1,
            OPEN_SETUP2 = 2,
            OPEN_WAIT = 3,
            OPEN = 4,
            CLOSE_WAIT = 5,
            RELEASE_WAIT = 6,
            MENU_END = 7,
        };

        int regist_;                                // 0x08

        static int menu_;

        MenuControl();
        ~MenuControl();
        virtual void execute();
        virtual int getPhase();
        virtual void setup();
        static void setMenu(int menu);
        void openSetup();
        bool isMenuEnd();
        void openMenu();
    };

    extern MenuControl gMenuControl;
}
