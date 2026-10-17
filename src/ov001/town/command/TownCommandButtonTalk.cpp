#include "ov001/town/command/TownCommandButtonTalk.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "main/dss/Pad.hpp"
#include "main/town/TownCommandEncount.hpp"

inline int twn::TownCommandButtonTalk::isEnd()
{
    return true;
}

#pragma thumb on

int twn::TownCommandButtonTalk::isExec()
{
    if (dss::g_Pad.edge() & 1) {
        if (TownPlayerManager::getSingleton().checkTalkToCharacter() == true) {
            return true;
        }
    }
    return false;
}

void twn::TownCommandButtonTalk::exec()
{
    CommandObjectDefineTownSystem::setButtonTalk();
}
