#include "ov000/btl/BattleEffectStorage.hpp"

THUMB btl::BattleEffectStorage::BattleEffectStorage()
{
}

THUMB btl::BattleEffectStorage::~BattleEffectStorage()
{
}

THUMB void btl::BattleEffectStorage::initialize()
{
    effectCounter_ = 0;
}

THUMB void btl::BattleEffectStorage::terminate()
{
}

THUMB btl::BattleEffectGroup* btl::BattleEffectStorage::getContainer()
{
    effectCounter_++;
    for (unsigned int i = 0; i < BATTLE_EFFECT_MAX; i++) {
        if (!group[i].isEnable()) {
            return &group[i];
        }
    }
    return 0;
}

THUMB void btl::BattleEffectStorage::restoreContainer()
{
    effectCounter_--;
}

THUMB int btl::BattleEffectStorage::getContainerStock()
{
    return BATTLE_EFFECT_MAX - effectCounter_;
}
