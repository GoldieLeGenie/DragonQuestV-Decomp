#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownFurniture.hpp"

#pragma thumb on

twn::TownSystemFurniture::TownSystemFurniture()
{
}

twn::TownSystemFurniture::~TownSystemFurniture()
{
}

void twn::TownSystemFurniture::initialize()
{
    TownFurnitureManager::getSingleton()->initialize();
}

void twn::TownSystemFurniture::terminate()
{
    TownFurnitureManager::getSingleton()->terminate();
}

void twn::TownSystemFurniture::execute()
{
    TownFurnitureManager::getSingleton()->execute();
}

void twn::TownSystemFurniture::draw()
{
    TownFurnitureManager::getSingleton()->draw();
}
