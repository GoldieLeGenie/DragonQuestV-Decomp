#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/global/Global.hpp"

THUMB int fld::FieldCommandPartChange::isExec()
{
    return g_Global.partChangeFlag_;
}

THUMB void fld::FieldCommandPartChange::exec()
{
    CommandObjectDefineFieldSystem::setPartChange();
}

THUMB int fld::FieldCommandPartChange::isEnd()
{
    return true;
}
