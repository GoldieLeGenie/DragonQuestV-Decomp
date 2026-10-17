#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/window/NormalControl.hpp"

#pragma thumb on

inline void BillboardCharacter::setAllAnimLock(bool flag)
{
    allAnimLock = flag;
}

twn::TownSystemPlayer::TownSystemPlayer()
{
}

twn::TownSystemPlayer::~TownSystemPlayer()
{
}

void twn::TownSystemPlayer::initialize()
{
    TownPlayerManager::getSingleton().initialize();
    TownPlayerManager::getSingleton().setup();
}

void twn::TownSystemPlayer::terminate()
{
    TownPlayerManager::getSingleton().cleanup();
    BillboardCharacter::setAllAnimLock(false);
    TownPlayerManager::getSingleton().terminate();
}

void twn::TownSystemPlayer::execute()
{
    window::gNormalControl.execute();
    TownPlayerManager::getSingleton().execute();
}

void twn::TownSystemPlayer::draw()
{
    TownPlayerManager::getSingleton().draw();
}
