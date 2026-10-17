#pragma once
#include <globaldefs.h>

namespace twn {
    struct TownMuseumManager {
        static const int MAX_EXHIBIT = 32;

        struct Pedestal {
            int drawID;                             // 0x00
            int uid;                                // 0x04
        };

        Pedestal pedestal_[MAX_EXHIBIT];            // 0x000
        int target_;                                // 0x100

        TownMuseumManager();
        ~TownMuseumManager();
        static TownMuseumManager& getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
        int getPedestal(int uid);
        void pushExhibit(int uid, int icon);
        void popExhibit(int uid);
    };
}
