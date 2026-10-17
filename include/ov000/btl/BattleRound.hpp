#pragma once
#include <globaldefs.h>
#include "ov000/btl/BattleRoundEnd.hpp"
#include "ov000/btl/BattleTurn.hpp"

namespace status {
    struct CharacterStatus;
}

namespace btl {
    struct BattleRound {
        enum RoundMode {
            RoundStart = 0,
            RoundExecute = 1,
            RoundEnd = 2,
            RoundAllEnd = 3,
        };

        static const int TURN_MAX = 32;

        BattleTurn battleTurn_[TURN_MAX];           // 0x000
        int currentBattleTurn_;                     // 0x200
        int currentBattleTurnID_;                   // 0x204
        int countBattleTurn_;                       // 0x208
        int turnEndFlag_;                           // 0x20C
        int venomActionFlag_;                       // 0x210
        RoundMode roundMode_;                       // 0x214
        BattleRoundEnd roundEnd_;                   // 0x218

        BattleRound();
        ~BattleRound();
        void initialize();
        void terminate();
        bool execute();
        bool isEnd();
        int isTurnEnd();
        BattleActor* add(status::CharacterStatus* character);
        bool execMeganteRing();
        bool execRebirthStone();
        bool setupVenomActor();
    };
}
