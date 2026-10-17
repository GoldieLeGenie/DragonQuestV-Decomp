#pragma once
#include <globaldefs.h>
#include "main/dss/CommandObject.hpp"
#include "main/dss/DssUtils.hpp"

namespace twn {
    struct TownCommandScope : args::CommandObject {
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };

    extern const dss::Fix32 farLen;
    extern const dss::Fix32 defaultLen;
}
