#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/menu/UiMsg.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldSystem.hpp"
#include "ov005/fld/FieldWindowSystem.hpp"

inline bool fld::FieldPlayer::search()
{
    return fieldAction_[actionIndex_]->search();
}

inline bool fld::FieldPlayerManager::search()
{
    return player_.search();
}

THUMB int fld::FieldCommandMenuSearch::isExec()
{
    if (cmn::g_cmnPartyInfo.menuAction_ == cmn::MENU_SEARCH) {
        script_ = 0;
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        if (FieldPlayerManager::getSingleton().checkScriptSearch() == true) {
            script_ = 1;
            FieldSystem::getSingleton()->fieldSystemScript_.search_ = 1;
            return true;
        }
        if (FieldPlayerManager::getSingleton().search() != true) {
            ui_MsgSndSet(0x30);
            if (FieldPlayerManager::getSingleton().player_.getMoveType() == 1) {
                FieldWindowSystem::getSingleton()->openCommonMessage();
                FieldWindowSystem::getSingleton()->addCommonMessage(0xc44ab);
                FieldWindowSystem::getSingleton()->addCommonMessage(0xc44b3);
            } else {
                FieldWindowSystem::getSingleton()->openCommonMessage();
                FieldWindowSystem::getSingleton()->addCommonMessage(0xc44a2);
                FieldWindowSystem::getSingleton()->addCommonMessage(0xc44b1);
            }
        }
        return true;
    }
    return false;
}

THUMB int fld::FieldCommandMenuSearch::isEnd()
{
    return true;
}

THUMB void fld::FieldCommandMenuSearch::exec()
{
    if (script_ == 1) {
        CommandObjectDefineFieldSystem::setMenuSearchScript();
    } else {
        CommandObjectDefineFieldSystem::setMenuSearchNone();
    }
}
