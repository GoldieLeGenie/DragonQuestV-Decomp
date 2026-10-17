#pragma once
#include <globaldefs.h>

namespace btl {
    struct SetFlagInfo {
        short flagNo;                           // 0x0
        char flagType;                          // 0x2
        char victory;                           // 0x3
    };

    struct BattleScriptManager {
        static const int SET_BATTLE_END_FLAG_COUNT = 2;

        int checkBattle_;                       // 0x00
        int setDataInit_;                       // 0x04
        SetFlagInfo flagInfo_[SET_BATTLE_END_FLAG_COUNT]; // 0x08

        BattleScriptManager();
        void setScriptBattleResult(int flagType, int flagNo, int victory);
        void checkScriptBattleResult();
    };

    extern BattleScriptManager gBattleScriptManager;
}
