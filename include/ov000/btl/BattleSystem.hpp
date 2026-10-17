#pragma once
#include <globaldefs.h>
#include "main/dss/Render.hpp"

namespace btl
{
    struct BattleSystem {
        Render render_;                             // 0x00

        BattleSystem();
        ~BattleSystem();
        static BattleSystem* getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
    };
} // namespace btl
