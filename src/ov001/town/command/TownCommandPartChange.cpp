#include "ov001/town/command/TownCommandPartChange.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownSystem.hpp"
#include "main/dss/GameSystemManager.hpp"
#include "main/global/Global.hpp"
#include "main/town/TownCommandEncount.hpp"

#pragma thumb on

inline int Global::isPartChangeFlag()
{
    return partChangeFlag_;
}

inline twn::TOWN_PLAYER_ACTION_TYPE twn::TownPlayerManager::getActionType()
{
    return player_.actionType_;
}

int twn::TownCommandPartChange::isExec()
{
    return g_Global.isPartChangeFlag();
}

void twn::TownCommandPartChange::exec()
{
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::CommandPriority, true);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::MenuPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::MessagePriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::MaterielMenuPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::DrawTownShopListPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::DrawTownMapPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::SugorokuPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::CameraPriority, true);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::StagePriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::FurniturePriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::RiseupPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::PlayerPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::CharacterPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::ScriptPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::GlobalMapPriority, false);
    args::GameSystemManager::getSingleton().setExclusion(TownSystem::ScreenEffectPriority, true);
    if (TownPlayerManager::getSingleton().getActionType() == ACTION_TYPE_FALL) {
        CommandObjectDefineTownSystem::setPartChangeFall();
    } else {
        CommandObjectDefineTownSystem::setPartChangeNormal();
    }
}

int twn::TownCommandPartChange::isEnd()
{
    return true;
}
