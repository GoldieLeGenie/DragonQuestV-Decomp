#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownSugorokuManager.hpp"

#pragma thumb on

twn::TownSystemSugoroku::TownSystemSugoroku()
{
}

twn::TownSystemSugoroku::~TownSystemSugoroku()
{
}

void twn::TownSystemSugoroku::initialize()
{
    TownSugorokuManager::getSingleton().initialize();
}

void twn::TownSystemSugoroku::terminate()
{
    TownSugorokuManager::getSingleton().terminate();
}

void twn::TownSystemSugoroku::execute()
{
    TownSugorokuManager::getSingleton().execute();
}

void twn::TownSystemSugoroku::draw()
{
    TownSugorokuManager::getSingleton().draw();
}
