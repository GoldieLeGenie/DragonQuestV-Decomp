#include "ov001/town/command/TownCommandLink.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "main/town/TownCommandEncount.hpp"

inline int twn::TownCommandLink::isEnd()
{
    return true;
}

#pragma thumb on

inline bool twn::TownPlayerManager::isLinked()
{
    return link_;
}

int twn::TownCommandLink::isExec()
{
    return TownPlayerManager::getSingleton().isLinked();
}

void twn::TownCommandLink::exec()
{
    CommandObjectDefineTownSystem::setMapLink();
}
