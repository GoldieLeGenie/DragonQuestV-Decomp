#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/dss/Pad.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldSystem.hpp"
#include <nitro/pad.h>

inline bool fld::FieldPlayer::search()
{
    return fieldAction_[actionIndex_]->search();
}

inline bool fld::FieldPlayerManager::search()
{
    return player_.search();
}

THUMB int fld::FieldCommandButtonSearch::isExec()
{
    if (dss::g_Pad.edge() & PAD_BUTTON_A) {
        script_ = 0;
        if (FieldPlayerManager::getSingleton().checkScriptSearch() == true) {
            script_ = 1;
            FieldSystem::getSingleton()->fieldSystemScript_.search_ = 1;
            return true;
        }
        if (FieldPlayerManager::getSingleton().search() == true) {
            return true;
        }
        return false;
    }
    return false;
}

THUMB int fld::FieldCommandButtonSearch::isEnd()
{
    return true;
}

THUMB void fld::FieldCommandButtonSearch::exec()
{
    if (script_ == 1) {
        CommandObjectDefineFieldSystem::setButtonSearchScript();
    } else {
        CommandObjectDefineFieldSystem::setButtonSearch();
    }
}
