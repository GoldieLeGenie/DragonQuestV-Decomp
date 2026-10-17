#include "ov001/town/command/TownCommandBookingTownMenu.hpp"
#include "main/town/TownCommandEncount.hpp"
#include "main/window/MenuControl.hpp"
#include "main/status/MenuStatus.hpp"

#pragma thumb on

inline int status::MenuStatus::getBooking()
{
    return bookingFlag_;
}

inline void status::MenuStatus::clearBooking()
{
    bookingFlag_ = 0;
}

inline bool window::MenuControl::isMenuEnd()
{
    return state_ == MENU_END;
}

int twn::TownCommandBookingTownMenu::isExec()
{
    if (status::g_Menu.getBooking() == 4) {
        status::g_Menu.clearBooking();
        window::gMenuControl.openSetup();
        return true;
    }
    return false;
}

void twn::TownCommandBookingTownMenu::exec()
{
    CommandObjectDefineTownSystem::setReturnNormalMenu();
}

int twn::TownCommandBookingTownMenu::isEnd()
{
    return window::gMenuControl.isMenuEnd();
}
