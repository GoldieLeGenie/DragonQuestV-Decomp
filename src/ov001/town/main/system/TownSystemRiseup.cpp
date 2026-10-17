#include "ov001/town/TownSystem.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"

#pragma thumb on

twn::TownSystemRiseup::TownSystemRiseup()
{
}

twn::TownSystemRiseup::~TownSystemRiseup()
{
}

void twn::TownSystemRiseup::initialize()
{
    TownRiseupManager::getSingleton().initialize();
}

void twn::TownSystemRiseup::terminate()
{
    TownRiseupManager::getSingleton().terminate();
}

void twn::TownSystemRiseup::execute()
{
    TownRiseupManager::getSingleton().execute();
}

void twn::TownSystemRiseup::draw()
{
    TownRiseupManager::getSingleton().draw();
}
