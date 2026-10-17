#pragma once
#include <globaldefs.h>
#include "main/window/InputControl.hpp"
#include "main/window/ImageMap.hpp"

namespace window {
    class MapControl : public InputControl {
    public:
        enum {
            TOWNMAP_WAIT_MOVE = 0,
            TOWNMAP_WAIT_OPEN = 1,
            TOWNMAP_VIEWING = 2,
            TOWMMAP_WAIT_CLOSE = 3,
            TOWNMAP_MESSAGE = 4,
            TOWNMAP_END = 5,
            TOWNMAP_NOT_DRAW = 6,
        };

        ImageMap* imageMap_;                        // 0x08
        int count_;                                 // 0x0C

        ~MapControl();
        virtual void execute();
        virtual int getPhase();
        virtual void setup();
        void registImageMap(ImageMap* imageMap);
        void openMap();
        void closeMap();
        void closeMapMessage();
        bool isEnd();
    };

    extern MapControl gMapControl;
}
