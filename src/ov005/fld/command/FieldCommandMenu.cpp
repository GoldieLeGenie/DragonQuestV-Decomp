#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "main/window/MenuControl.hpp"
#include <nitro/pad.h>

THUMB int fld::FieldCommandMenu::isExec()
{
    if (dss::g_Pad.edge() & PAD_BUTTON_X) {
        if (!fadeEffector.isFadeEnd()) {
            return false;
        }
        window::gMenuControl.openSetup();
        return true;
    }
    return false;
}

THUMB void fld::FieldCommandMenu::exec()
{
    CommandObjectDefineFieldSystem::setXmenu();
}

THUMB int fld::FieldCommandMenu::isEnd()
{
    return window::gMenuControl.state_ == window::MenuControl::MENU_END;
}
