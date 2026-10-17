#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/window/MenuControl.hpp"
#include <nitro/pad.h>

THUMB int fld::FieldCommandPartyTalk::isExec()
{
    if (dss::g_Pad.edge() & PAD_BUTTON_B) {
        if (!fadeEffector.isFadeEnd()) {
            return false;
        }
        window::MenuControl::menu_ = 4;
        status::g_Menu.bookingFlag_ = 4;
        return true;
    }
    return false;
}

THUMB void fld::FieldCommandPartyTalk::exec()
{
    CommandObjectDefineFieldSystem::setPartyTalk();
}

THUMB int fld::FieldCommandPartyTalk::isEnd()
{
    return true;
}
