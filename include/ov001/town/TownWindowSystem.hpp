#pragma once
#include <globaldefs.h>

namespace twn
{
    struct TownWindowSystem {
        int unk_00;                             // 0x00
        int town_message_;                      // 0x04

        TownWindowSystem();
        static TownWindowSystem& getSingleton();
        void initialize();
        void terminate();
        void openMessage(int message, int count);
        void openCommonMessage();
        void openSystemMessage(int message, int count);
        void openTalkMessage(int message, int count);
        void openSystemMessage();
        void openTalkMessage();
        void addCommonMessage(int message);
        void serialCommonMessage(int message);
        void waitCommonMessage();
        void clearCommonMessage();
        int isMessageStart();
        bool isMessageOpen();
        void setMessageFlag(int flag);
        bool isWait();
    };
} // namespace twn
