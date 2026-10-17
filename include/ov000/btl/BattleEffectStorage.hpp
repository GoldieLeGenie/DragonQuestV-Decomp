#pragma once
#include <globaldefs.h>
#include "ov000/btl/BattleEffectGroup.hpp"

namespace btl {
    struct BattleEffectStorage {
        static const unsigned int BATTLE_EFFECT_MAX = 12;

        BattleEffectGroup group[BATTLE_EFFECT_MAX]; // 0x0000
        int effectCounter_;                         // 0x2F70

        BattleEffectStorage();
        ~BattleEffectStorage();
        void initialize();
        void terminate();
        BattleEffectGroup* getContainer();
        void restoreContainer();
        int getContainerStock();
    };
}
