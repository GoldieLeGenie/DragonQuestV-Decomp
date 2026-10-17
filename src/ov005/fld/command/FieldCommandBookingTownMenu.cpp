#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/window/MenuControl.hpp"

THUMB int fld::FieldCommandBookingTownMenu::isExec()
{
    if (status::g_Menu.bookingFlag_ == 4) {
        status::g_Menu.bookingFlag_ = 0;
        window::gMenuControl.openSetup();
        return true;
    }
    return false;
}

THUMB void fld::FieldCommandBookingTownMenu::exec()
{
    CommandObjectDefineFieldSystem::setReturnNormalMenu();
}

THUMB int fld::FieldCommandBookingTownMenu::isEnd()
{
    return window::gMenuControl.state_ == window::MenuControl::MENU_END;
}
