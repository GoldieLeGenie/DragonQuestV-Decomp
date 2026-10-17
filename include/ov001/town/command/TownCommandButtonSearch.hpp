#pragma once
#include <globaldefs.h>
#include "main/dss/CommandObject.hpp"

namespace twn {
    struct TownCommandButtonSearch : args::CommandObject {
        int search_;                                // 0x04
        int script_;                                // 0x08
        int ido_;                                   // 0x0C

        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };
}
