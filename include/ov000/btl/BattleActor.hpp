#pragma once
#include <globaldefs.h>
#include "ov000/btl/BattleActorExec2.hpp"
#include "ov000/btl/BattleSelectTargetParam.hpp"
#include "main/status/UseActionParam.hpp"

namespace status {
    struct CharacterStatus;
    struct HaveBattleStatus;
}

namespace btl {
    struct BattleActor {
        enum ActorMode {
            ActorExecute = 0,
            ActorFinish = 1,
            ActorEnd = 2,
        };

        status::CharacterStatus* characterStatus_;      // 0x0000
        status::HaveBattleStatus* haveBattleStatus_;    // 0x0004
        status::UseActionParam useActionParam_;         // 0x0008
        BattleActorExec2 battleActorExec2_;             // 0x043C
        BattleActorFinish battleActorFinish_;           // 0x148C
        int agility_;                                   // 0x1524
        ActorMode actorMode_;                           // 0x1528
        int end_;                                       // 0x152C

        BattleActor();
        ~BattleActor();
        void setup(status::CharacterStatus* characterStatus);
        void setup();
        void execute();
        int isEnd();
        void reattack();
        void meganteRing();
        void rebirthStone();
        status::CharacterStatus* getCharacterStatus();
        void setActionTargetOnRound();
        static void setActionTargetOnTurn(status::UseActionParam* useActionParam, bool action);
        static void selectAI(status::UseActionParam* useActionParam, bool roundCheck);
        static void selectFriendMonster(status::UseActionParam* useActionParam);
        static void selectMosyasTarget(status::UseActionParam* useActionParam);
        static void setTargetMyself(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetFriend(int actionIndex, BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetEnemy(int actionIndex, BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetBoth(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetOneFriend(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetOneEnemy(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetGroupFriend(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetGroupEnemy(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetAllFriend(BattleSelectTargetParam* battleSelectTargetParam);
        static void setTargetAllEnemy(BattleSelectTargetParam* battleSelectTargetParam);
        bool isActionEnable();
        int getAgility();
        void setAgility(int ag);
    };
}
