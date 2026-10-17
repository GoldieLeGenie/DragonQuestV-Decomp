#include "ov001/town/command/TownCommandPartyTalk.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/town/TownCommandEncount.hpp"
#include "main/window/MenuControl.hpp"

#pragma thumb on

inline void window::MenuControl::setMenu(int menu)
{
    menu_ = menu;
}

inline void status::MenuStatus::setBooking(menu::BOOKING_FLAG flag)
{
    bookingFlag_ = flag;
}

int twn::TownCommandPartyTalk::isExec()
{
    if (dss::g_Pad.edge() & 2) {
        if (!fadeEffector.isFadeEnd()) {
            return false;
        }
        window::MenuControl::setMenu(4);
        status::g_Menu.setBooking(menu::BOOKING_TOWN);
        return true;
    }
    return false;
}

void twn::TownCommandPartyTalk::exec()
{
    CommandObjectDefineTownSystem::setPartyTalk();
}

int twn::TownCommandPartyTalk::isEnd()
{
    return true;
}
