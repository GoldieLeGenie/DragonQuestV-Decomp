#include "main/town/TownCommandEncount.hpp"
#include "main/dss/GameSystemManager.hpp"

THUMB void twn::CommandObjectDefineTownSystem::setPartChangeNormal()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(3, true);
    manager.setExclusion(17, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setPartChangeFall()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(3, true);
    manager.setExclusion(17, true);
    manager.setExclusion(14, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setScreenEffect()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(3, true);
    manager.setExclusion(14, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setScope()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(14, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setMessage()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(4, true);
    manager.setExclusion(17, true);
    manager.setExclusion(11, true);
    manager.setExclusion(19, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setLoadReturn()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(11, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setLoseReturn()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(11, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setShopList()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(7, true);
    manager.setExclusion(17, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setMateriel()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(5, true);
    manager.setExclusion(17, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setXmenu()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(6, true);
    manager.setExclusion(17, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setTownMap()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(21, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setSugoroku()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(8, true);
    manager.setExclusion(11, true);
    manager.setExclusion(12, true);
    manager.setExclusion(14, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setPlayer()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(8, true);
    manager.setExclusion(10, true);
    manager.setExclusion(11, true);
    manager.setExclusion(14, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setNormal()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(8, true);
    manager.setExclusion(10, true);
    manager.setExclusion(11, true);
    manager.setExclusion(13, true);
    manager.setExclusion(14, true);
    manager.setExclusion(16, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setEncount()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setButtonTalk()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(16, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setAfterPartChange()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(8, true);
    manager.setExclusion(10, true);
    manager.setExclusion(11, true);
    manager.setExclusion(13, true);
    manager.setExclusion(16, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setMenuTalk()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(16, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setMenuSearchNone()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setMenuSearchProgram()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(4, true);
    manager.setExclusion(17, true);
    manager.setExclusion(8, true);
    manager.setExclusion(10, true);
    manager.setExclusion(11, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setMenuSearchScript()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(4, true);
    manager.setExclusion(17, true);
    manager.setExclusion(8, true);
    manager.setExclusion(10, true);
    manager.setExclusion(11, true);
    manager.setExclusion(16, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setScriptEvent()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(8, true);
    manager.setExclusion(10, true);
    manager.setExclusion(11, true);
    manager.setExclusion(13, true);
    manager.setExclusion(14, true);
    manager.setExclusion(16, true);
    manager.setExclusion(19, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setPartyTalk()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setWalkCount()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setMapLink()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setReturnMaterielMenu()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(5, true);
    manager.setExclusion(17, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setReturnNormalMenu()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(6, true);
    manager.setExclusion(17, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setFukubiki()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(8, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setTreasuerRoom()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(8, true);
    manager.setExclusion(10, true);
    manager.setExclusion(11, true);
    manager.setExclusion(12, true);
    manager.setExclusion(13, true);
    manager.setExclusion(14, true);
    manager.setExclusion(16, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setplayerLock()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
    manager.setExclusion(8, true);
    manager.setExclusion(10, true);
    manager.setExclusion(11, true);
    manager.setExclusion(13, true);
    manager.setExclusion(14, true);
    manager.setExclusion(16, true);
}

THUMB void twn::CommandObjectDefineTownSystem::setPlaySound()
{
    allFalse();
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(17, true);
}

THUMB void twn::CommandObjectDefineTownSystem::allFalse()
{
    args::GameSystemManager& manager = args::GameSystemManager::getSingleton();
    manager.setExclusion(3, false);
    manager.setExclusion(4, false);
    manager.setExclusion(5, false);
    manager.setExclusion(6, false);
    manager.setExclusion(7, false);
    manager.setExclusion(17, false);
    manager.setExclusion(8, false);
    manager.setExclusion(10, false);
    manager.setExclusion(11, false);
    manager.setExclusion(12, false);
    manager.setExclusion(13, false);
    manager.setExclusion(14, false);
    manager.setExclusion(16, false);
    manager.setExclusion(19, false);
    manager.setExclusion(20, false);
    manager.setExclusion(21, false);
}
