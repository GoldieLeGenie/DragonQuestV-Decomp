#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace status {
    struct BattleResult {
        struct Result {
            unsigned short monsterCount_;       // 0x0
            unsigned short itemCount_;          // 0x2
            unsigned char level_;               // 0x4
        };
        Result result_[202];                    // 0x000
        dss::FlagArray<202> encountFlag_;       // 0x4BC
        int playerVictory_;                     // 0x4D8
        int playerDemolition_;                  // 0x4DC
        int playerDemolitionMessage_;           // 0x4E0
        int disablePlayerDemolition_;           // 0x4E4
        int battleTurnCount_;                   // 0x4E8
        int battleExecute_;                     // 0x4EC
        int demolitionPartyTalk_;               // 0x4F0
        int firstAttack_;                       // 0x4F4
        int debugFirstAttack_;                  // 0x4F8

        BattleResult();
        ~BattleResult();
        void initialize();
        void addMonsterCount(int index);
        unsigned short getMonsterCount(int index);
        void setMonsterCount(int index, unsigned short count);
        unsigned short getMonsterItemCount(int index);
        void setMonsterItemCount(int index, unsigned short count);
        unsigned char getMonsterLevel(int index);
        void setMonsterLevel(int index, unsigned char level);
        void addMonsterItemCount(int index);
        unsigned int getMonsterExp(int index);
        unsigned int getMonsterGold(int index);
        void regenesisMonsterLevel(int index, unsigned char level);
        void setMonsterEncount(unsigned int index, bool flag);
        bool isMonsterEncount(unsigned int index);
        int getMonsterEncountCount();
        unsigned int getMonsterTotalExp(int index);
        unsigned int getMonsterTotalGold(int index);
        short getMonsterItemIndex(int index);
        int getMonsterIndex(int index);
        int getMonsterFriendly(int index);
        int getMonsterBookIndex(int monsterIndex);
        void setPlayerDemolition(bool flag);
        int isPlayerDemolition();
        void setDisablePlayerDemolition(bool flag);
        int isDisablePlayerDemolition();
        void setDisableChurchMessage(int flag);
        int isDisableChurchMessage();
        void setDemolitionPartyTalk(bool flag);
        void setPlayerVictory(bool flag);
        int isPlayerVictory();
        int getDebugFirstAttack();
        void setBattleTurnCount(int count);
        int getBattleTurnCount();
        int isDemolitionPartyTalk();
    };

    extern BattleResult g_BattleResult;
}
