#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "ov005/fld/FieldSystem.hpp"

THUMB int fld::FieldCommandEvent::isExec()
{
    return FieldSystem::getSingleton()->fieldSystemScript_.isEventLock();
}

THUMB void fld::FieldCommandEvent::exec()
{
    CommandObjectDefineFieldSystem::setScriptEvent();
}

THUMB int fld::FieldCommandEvent::isEnd()
{
    return true;
}
