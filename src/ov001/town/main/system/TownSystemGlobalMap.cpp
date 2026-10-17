#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownGlobalMap.hpp"

#pragma thumb on

twn::TownSystemGlobalMap::TownSystemGlobalMap()
{
}

twn::TownSystemGlobalMap::~TownSystemGlobalMap()
{
}

void twn::TownSystemGlobalMap::initialize()
{
}

void twn::TownSystemGlobalMap::terminate()
{
}

void twn::TownSystemGlobalMap::execute()
{
    TownGlobalMap::getSingleton().execute();
}

void twn::TownSystemGlobalMap::draw()
{
    TownGlobalMap::getSingleton().draw();
}
