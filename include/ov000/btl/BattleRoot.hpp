#pragma once
#include <globaldefs.h>
#include "ov000/btl/BattleTask.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/GameFlag.hpp"

namespace status {
    struct PartyStatus;
}

namespace btl {
    struct BattleRound;

    struct BattleRoot {
        EncountTask encountTask_;                   // 0x000
        StatusTask statusTask_;                     // 0x008
        FirstAttackTask firstAttackTask_;           // 0x010
        FirstReorderTask firstReorderTask_;         // 0x018
        CommandTask commandTask_;                   // 0x020
        RoundTask roundTask_;                       // 0x028
        RoundEndTask roundEndTask_;                 // 0x034
        BattleEndTask battleEndTask_;               // 0x03C
        ExitTask exitTask_;                         // 0x044
        ExitWaitTask exitWaitTask_;                 // 0x04C
        PartyReorderTask partyReorderTask_;         // 0x054
        DemolitionTask demolitionTask_;             // 0x05C
        TimeReverseTask timeReverseTask_;           // 0x064
        TimeReverseEndTask timeReverseEndTask_;     // 0x070
        EscapeTask escapeTask_;                     // 0x078
        StadiumEndTask stadiumEndTask_;             // 0x080
        StadiumDrawTask stadiumDrawTask_;           // 0x08C
        StadiumResultTask stadiumResultTask_;       // 0x098
        int eventEncount_;                          // 0x0A4
        status::PartyStatus* backupPartyStatus_;    // 0x0A8
        status::GameFlag backupGlobalFlag_;         // 0x0AC
        status::GameFlag backupAreaFlag_;           // 0x12C
        status::GameFlag backupLocalFlag_;          // 0x1AC
        status::BattleResult backupBattleResult_;   // 0x22C
        int backupMonsterIndex_[4];                 // 0x728
        int backupMonsterCount_[4];                 // 0x738
        int executeFlag_;                           // 0x748

        BattleRoot();
        ~BattleRoot();
        static BattleRoot* getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
        void setupBattle();
        void cleanupBattle();
        void setupMonster();
        void cleanupMonster();
        void store();
        void restore();
        bool isRoundEnd();
        bool isMenuEnd();
        bool isEncountMenuEnd();
        bool isBattleStart();
        void setBattleEnd();
        bool isUseItem(int itemIndex);
        void setExecuteEnable(int flag);
    };

    extern BattleRound battleRound_;
}
