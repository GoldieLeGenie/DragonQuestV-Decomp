#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "ov000/btl/BattleActor.hpp"

namespace status {
    struct CharacterStatus;
}

namespace btl
{
    struct BattleActorManager {
        static const int PLAYER_MAX = 8;
        static const int MONSTER_MAX = 12;
        static const int DEATH_NUMBERS = 0x10000;
        static const int DEATH_MULTIPLE = 0x20000;
        static const int DEATH_SINGLE = 0x40000;
        static const int INDEX_MASK = 0xFFFF;
        static const int FLAG_MASK = 0xFFFF0000;

        BattleActor actor_[PLAYER_MAX + MONSTER_MAX];   // 0x00000
        int actorCount_;                        // 0x1A7C0
        int turnCount_;                         // 0x1A7C4
        int escape_;                            // 0x1A7C8
        int escapeSuccess_;                     // 0x1A7CC
        int escapeCount_;                       // 0x1A7D0
        int eventFlag_;                         // 0x1A7D4
        int disableEscapeFlag_;                 // 0x1A7D8
        int eventType_;                         // 0x1A7DC
        int eventTile_;                         // 0x1A7E0
        int eventEnd_;                          // 0x1A7E4
        FirstAttack firstAttack_;               // 0x1A7E8
        int monsterDeathCount_;                 // 0x1A7EC
        int monsterEscapeCount_;                // 0x1A7F0
        int monsterDisappearCount_;             // 0x1A7F4
        int winningStatus_;                     // 0x1A7F8
        short deathLog_;                        // 0x1A7FC

        BattleActorManager();
        ~BattleActorManager();
        static BattleActorManager* getSingleton();
        void initialize();
        void selectActor();
        void selectActorPlayer();
        void selectActorMonster();
        BattleActor* add(status::CharacterStatus* character);
        void selectVenomActor();
        void setActorOrder(bool flag);
        void setActorAction();
        int getActorCount();
        BattleActor* getBattleActor(int index);
        void execStartOfRound();
        void execEndOfRound();
        void execEndOfTurn();
        void retireActor();
        void execStartOfBattle();
        void execEndOfBattle();
        bool isBattleEnd(int flag);
        void execMonsterDeath(int index);
        void execMonsterDeathForItem();
        bool isAddMonster();
        FirstAttack getFirstAttack();
        bool isSingleBeat();
        bool isNumbersBeat();
        bool isMultipleBeat();
        int getBeatIndex();
        void clearFirstAttack();
        void setEscape(bool flag);
        bool isEscape();
        bool isEscapeSuccess();
        void addMonsterDeathCount(int count);
        int getMonsterDeathCount();
        void addMonsterEscapeCount(int count);
        int getMonsterEscapeCount();
        void addMonsterDisappearCount(int count);
        int getMonsterDisappearCount();
        void setFirstAttack(FirstAttack firstAttack);
        void setDisableEscapeFlag(int flag);
        void setEventBattle(int flag, int tile);
        void checkDeathMonster();
        void setDeathLog(int deathLog);
        int getDeathLog();
        void clearDeadMonster(bool all);
    };
} // namespace btl
