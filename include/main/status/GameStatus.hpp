#pragma once
#include <globaldefs.h>
#include "main/dss/UnkRandom.hpp"
#include "GameInfo.hpp"


namespace status{
    struct GameStatus {
        Language language_;                     // 0x0
        unsigned int playTime_;                 // 0x4
        unsigned int uniqueID_;                 // 0x8
        GameStatus();
        ~GameStatus();
        void initialize();
        void setLanguage(Language language);
        void setPlayTime(unsigned int time);
        void addPlayTime(unsigned int time);
        unsigned int getPlayTime();
        void resetUniqueID();
        unsigned int getUniqueID();
        void setUniqueID(unsigned int id);
    };

    extern GameStatus g_Game;
}

extern "C" void func_020887b4(unsigned char buffer[]);
