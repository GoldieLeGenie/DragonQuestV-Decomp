#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/dss/DssUtils.hpp"

namespace btl {
    struct BattleActor;

    struct BattleTurn {
        static const int FLAG_INITIALIZED = 1;
        static const int FLAG_TERMINATED = 2;

        CharacterType characterType_;               // 0x00
        int actorIndex_;                            // 0x04
        BattleActor* battleActor_;                  // 0x08
        dss::Flag flag_;                            // 0x0C

        BattleTurn();
        ~BattleTurn();
        void setBattleActor(BattleActor* actor);
        void execute();
        bool isEnd();
        bool checkEnd();
        bool isActionEnable();
        BattleActor* getBattleActor();
        void reattack();
        void setup();
        void cleanup();
        void exec();
        bool isBattleActorEnd();
    };
}
