#pragma once
#include <globaldefs.h>
#include "main/window/InputControl.hpp"
#include "main/window/ImageMap.hpp"

namespace window {
    class ShoplistControl : public InputControl {
    public:
        enum {
            TOWNMAP_WAIT_OPEN = 0,
            TOWNMAP_VIEWING = 1,
            TOWMMAP_WAIT_CLOSE = 2,
            TOWMMAP_CLOSE = 3,
            TOWNMAP_MESSAGE = 4,
            RELEASE_WAIT = 5,
            TOWNMAP_END = 6,
        };

        int open_;                                  // 0x08
        ImageMap* imageMap_;                        // 0x0C

        ShoplistControl();
        ~ShoplistControl();
        virtual void execute();
        virtual int getPhase();
        virtual void setup();
        void registShopList(ImageMap* imageMap);
        void openList();
        void closeList();
        bool nextList();
        void closeListMessage();
        void setOpen(bool flag);
        int isOpen();
        bool isEnd();
    };

    extern ShoplistControl gShoplistControl;
}
