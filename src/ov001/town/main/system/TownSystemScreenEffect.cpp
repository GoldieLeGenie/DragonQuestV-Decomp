#include "ov001/town/TownSystem.hpp"
#include "main/dss/GameSystemManager.hpp"
#include "main/window/ScreenEffectManager.hpp"

#pragma thumb on

twn::TownSystemScreenEffect::TownSystemScreenEffect()
{
}

twn::TownSystemScreenEffect::~TownSystemScreenEffect()
{
}

void twn::TownSystemScreenEffect::initialize()
{
    window::gScreenEffect.initialize();
}

void twn::TownSystemScreenEffect::terminate()
{
    window::gScreenEffect.terminate();
}

void twn::TownSystemScreenEffect::execute()
{
    if (window::gScreenEffect.isActiveSetup()) {
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::RenderPriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::ScreenEffectPriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::MessagePriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::MaterielMenuPriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::MenuPriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::DrawTownShopListPriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::StagePriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::StageEffectPriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::CharacterPriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::FurniturePriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::RiseupPriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::PlayerPriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::EncountPriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::SugorokuPriority, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(TownSystem::CameraPriority, false);
    }
    window::gScreenEffect.execute();
}

void twn::TownSystemScreenEffect::draw()
{
    window::gScreenEffect.draw();
}
