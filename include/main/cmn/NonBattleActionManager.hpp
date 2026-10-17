#pragma once
#include <globaldefs.h>

namespace cmn
{
    struct NonBattleActionManager {
        enum ACTION_EFFECT {
            ACTION_NONE = 0,
            ACTION_TRAVELDOOR = 1,
            ACTION_RIREMITO = 2,
            ACTION_RANARUTA = 3,
        };

        ACTION_EFFECT status_;                  // 0x00
        int startFlag_;                         // 0x04
        int waitTurn_;                          // 0x08

        static NonBattleActionManager* getSingleton();
        void execute();
        void setAction(ACTION_EFFECT action);
    };
} // namespace cmn
