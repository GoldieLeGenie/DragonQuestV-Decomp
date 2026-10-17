#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

THUMB int fld::FieldCommandPlayer::isExec()
{
    cmn::MENU_ACTION menuAction = cmn::g_cmnPartyInfo.menuAction_;
    if (menuAction != cmn::MENU_ACTION_NONE) {
        FieldPlayerManager::getSingleton().checkMenuAction(menuAction);
        return true;
    }
    FieldPlayerManager::getSingleton().player_.update();
    FieldPlayerManager::getSingleton().execMapLink();
    return FieldPlayerManager::getSingleton().remote_;
}

THUMB void fld::FieldCommandPlayer::exec()
{
    CommandObjectDefineFieldSystem::setPlayer();
}

THUMB int fld::FieldCommandPlayer::isEnd()
{
    return true;
}
