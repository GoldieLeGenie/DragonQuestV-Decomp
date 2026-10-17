#pragma ipa file
#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "main/object/DisplayCharacter.hpp"

#pragma thumb on

twn::TownSystemCharacter::TownSystemCharacter()
{
}

twn::TownSystemCharacter::~TownSystemCharacter()
{
}

void twn::TownSystemCharacter::initialize()
{
    TownCharacterManager::getSingleton()->initialize();
}

void twn::TownSystemCharacter::terminate()
{
    DisplayCharacter::sleepBodyOffset_ = dss::Fix32(0.27f);
    DisplayCharacter::sleepHeadOffset_ = dss::Fix32(0.173f);
    DisplayCharacter::sleepHeight_ = dss::Fix32(0.194f);
    TownCharacterManager::getSingleton()->terminate();
}

void twn::TownSystemCharacter::execute()
{
    TownCharacterManager::getSingleton()->execute();
}

void twn::TownSystemCharacter::draw()
{
    TownCharacterManager::getSingleton()->draw();
}
