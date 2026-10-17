#pragma once
#include <globaldefs.h>
#include "main/status/HaveItemSack.hpp"

namespace status {
    struct BasePartyStatus {
        int bashaEnter_;                    // 0x00
        int bashaEnable_;                   // 0x04
        int fukuro_;                        // 0x08
        int battleMonsterCount_;            // 0x0C
        int battleExp_;                     // 0x10
        int battleGold_;                    // 0x14
        int carriage_;                      // 0x18
        unsigned int gold_;                 // 0x1C
        unsigned int bankMoney_;            // 0x20
        unsigned int casinoCoin_;           // 0x24
        unsigned int medalCoin_;            // 0x28
        HaveItemSack haveItemSack_;         // 0x2C

        BasePartyStatus();
        bool isCarriageEnter();
        bool isCarriageEnableOnGame();
        void setCarriage(int flag);
        void setFukuro(bool flag);
        int isFukuro();
        HaveItemSack& getFukuro();
        unsigned int getGold();
        void setGold(unsigned int gold);
        void addGold(int gold);
        void setBankMoney(unsigned int money);
        unsigned int getCasinoCoin();
        void setCasinoCoin(unsigned int coin);
        void setMedalCoin(unsigned int coin);
        unsigned int getMedalCoin();
        void addMedalCoin(int coin);
        void addBattleMonsterCount(int num);
        void addBattleExp(int exp);
        void addBattleGold(int gold);
        int getBattleExp();
        int getBattleGold();
        void reflectBattleGold();
        void clearBattleMonsterCount();
        void clearBattleExp();
        void clearBattleGold();
    };
}
