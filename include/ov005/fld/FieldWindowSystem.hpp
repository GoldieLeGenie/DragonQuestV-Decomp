#pragma once
#include <globaldefs.h>

namespace fld
{
    // Field window system
    struct FieldWindowSystem {
        int message_open_;                      // 0x00

        FieldWindowSystem();
        static FieldWindowSystem* getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
        void openMessage(int index, int count);
        void addCommonMessage(int index);
        void openCommonMessage();
        bool isMessageOpen();
    };
} // namespace fld
