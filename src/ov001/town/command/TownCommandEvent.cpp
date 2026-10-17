#include "ov001/town/command/TownCommandEvent.hpp"
#include "ov001/town/TownSystem.hpp"
#include "main/town/TownCommandEncount.hpp"

#pragma thumb on

inline twn::TownSystemScript& twn::TownSystem::getScriptSystem()
{
    return townSystemScript_;
}

int twn::TownCommandEvent::isExec()
{
    return TownSystem::getSingleton().getScriptSystem().isEventLock();
}

void twn::TownCommandEvent::exec()
{
    CommandObjectDefineTownSystem::setScriptEvent();
}

int twn::TownCommandEvent::isEnd()
{
    return true;
}
