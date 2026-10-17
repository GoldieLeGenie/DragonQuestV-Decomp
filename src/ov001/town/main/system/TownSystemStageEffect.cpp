#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownStageEffectManager.hpp"

#pragma thumb on

twn::TownSystemStageEffect::TownSystemStageEffect()
{
}

twn::TownSystemStageEffect::~TownSystemStageEffect()
{
}

void twn::TownSystemStageEffect::initialize()
{
    TownStageEffectManager::getSingleton()->initialize();
}

void twn::TownSystemStageEffect::terminate()
{
    TownStageEffectManager::getSingleton()->terminate();
}

void twn::TownSystemStageEffect::execute()
{
    TownStageEffectManager::getSingleton()->execute();
}

void twn::TownSystemStageEffect::draw()
{
    TownStageEffectManager::getSingleton()->draw();
}
