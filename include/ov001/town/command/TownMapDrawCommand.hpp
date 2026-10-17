#pragma once
#include <globaldefs.h>
#include "main/dss/CommandObject.hpp"

namespace twn {
    struct TownMapDrawCommand : args::CommandObject {
        int push_;                                  // 0x04
        int counter_;                               // 0x08

        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };
}
