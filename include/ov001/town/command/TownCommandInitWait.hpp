#pragma once
#include <globaldefs.h>
#include "main/dss/CommandObject.hpp"

namespace twn {
    struct TownCommandInitWait : args::CommandObject {
        int flag_;                                  // 0x04
        int count_;                                 // 0x08

        TownCommandInitWait();
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
        void setWait(bool flag);
    };
}
