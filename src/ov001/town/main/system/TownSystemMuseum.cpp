#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownMuseumManager.hpp"

#pragma thumb on

twn::TownSystemMuseum::TownSystemMuseum()
{
}

twn::TownSystemMuseum::~TownSystemMuseum()
{
}

void twn::TownSystemMuseum::initialize()
{
    TownMuseumManager::getSingleton().initialize();
}

void twn::TownSystemMuseum::terminate()
{
    TownMuseumManager::getSingleton().terminate();
}

void twn::TownSystemMuseum::execute()
{
    TownMuseumManager::getSingleton().execute();
}

void twn::TownSystemMuseum::draw()
{
    TownMuseumManager::getSingleton().draw();
}
