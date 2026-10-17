#include "main/cmn/CommandObjectField.hpp"
#include "main/dss/GameSystemManager.hpp"

THUMB void fld::CommandObjectDefineFieldSystem::setPartChange()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(2, true);
}

THUMB void fld::CommandObjectDefineFieldSystem::setScreenEffect()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(2, true);
    manager.setExclusion(7, true);
}

THUMB void fld::CommandObjectDefineFieldSystem::setMessage()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(3, true);
}

THUMB void fld::CommandObjectDefineFieldSystem::setReturnNormalMenu()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(5, true);
}

THUMB void fld::CommandObjectDefineFieldSystem::setReturnMaterielMenu()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(4, true);
}

THUMB void fld::CommandObjectDefineFieldSystem::setMenuSearchNone()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
}

THUMB void fld::CommandObjectDefineFieldSystem::setMenuSearchScript()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(9, true);
}

THUMB void fld::CommandObjectDefineFieldSystem::setMateriel()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(4, true);
}

THUMB void fld::CommandObjectDefineFieldSystem::setPlayer()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(6, true);
    manager.setExclusion(7, true);
}

THUMB void fld::CommandObjectDefineFieldSystem::setScriptEvent()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(6, true);
    manager.setExclusion(7, true);
    manager.setExclusion(9, true);
}

THUMB void fld::CommandObjectDefineFieldSystem::setAreaMap()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
}

THUMB void fld::CommandObjectDefineFieldSystem::setfieldVehicle()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(6, true);
    manager.setExclusion(7, true);
}

THUMB void fld::CommandObjectDefineFieldSystem::setWalkCount()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
}

THUMB void fld::CommandObjectDefineFieldSystem::setEncount()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
}

THUMB void fld::CommandObjectDefineFieldSystem::setXmenu()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(5, true);
}

THUMB void fld::CommandObjectDefineFieldSystem::setButtonSearch()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
}

THUMB void fld::CommandObjectDefineFieldSystem::setPartyTalk()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
}

THUMB void fld::CommandObjectDefineFieldSystem::setNormal()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(6, true);
    manager.setExclusion(7, true);
    manager.setExclusion(9, true);
}

THUMB void fld::CommandObjectDefineFieldSystem::setButtonSearchScript()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(9, true);
}

THUMB void fld::CommandObjectDefineFieldSystem::allFalse()
{
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(2, false);
    manager.setExclusion(3, false);
    manager.setExclusion(4, false);
    manager.setExclusion(5, false);
    manager.setExclusion(6, false);
    manager.setExclusion(7, false);
    manager.setExclusion(9, false);
}
