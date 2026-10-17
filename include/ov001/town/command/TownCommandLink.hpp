#pragma once
#include <globaldefs.h>
#include "main/dss/CommandObject.hpp"

namespace twn {
    struct TownCommandLink : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };
}
