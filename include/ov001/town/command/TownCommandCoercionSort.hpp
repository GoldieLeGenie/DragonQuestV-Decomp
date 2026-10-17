#pragma once
#include <globaldefs.h>
#include "main/dss/CommandObject.hpp"

namespace twn {
    struct TownCommandCoercionSort : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };
}
