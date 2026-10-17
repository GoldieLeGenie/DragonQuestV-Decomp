#pragma once
#include <globaldefs.h>
#include "main/dss/CommandObject.hpp"

namespace twn {
    struct TownCommandBookingMenu : args::CommandObject {
        int meisanInnFlag_;                         // 0x04
        int fadeEnd_;                               // 0x08
        int fadeCount_;                             // 0x0C

        TownCommandBookingMenu();
        virtual int isExec();
        virtual int isEnd();
        virtual void exec();
    };
}
