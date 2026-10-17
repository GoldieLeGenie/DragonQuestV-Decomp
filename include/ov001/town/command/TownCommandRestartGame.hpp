#pragma once
#include <globaldefs.h>
#include "main/dss/CommandObject.hpp"

namespace twn {
    struct TownCommandRestartGame : args::CommandObject {
        static const int defaultWait = 30;

        int wait_;                                  // 0x04

        TownCommandRestartGame();
        ~TownCommandRestartGame();
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };
}
