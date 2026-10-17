#pragma once
#include <globaldefs.h>
#include "main/window/InputControl.hpp"

namespace window {
    class ShopMenuControl : public InputControl {
    public:
        enum {
            OPEN_SETUP = 0,
            OPEN_SETUP1 = 1,
            OPEN_SETUP2 = 2,
            OPEN_WAIT = 3,
            OPEN = 4,
            CLOSE_WAIT = 5,
            RELEASE_WAIT = 6,
            MENU_START = 7,
            MENU_END = 8,
        };

        int menuType_;                              // 0x08

        ~ShopMenuControl();
        virtual void execute();
        virtual int getPhase();
        virtual void setup();
        void startMenu(int type);
        bool isMenuStart();
        bool isMenuEnd();
    };

    extern ShopMenuControl gShopMenuControl;
}
