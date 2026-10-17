#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/status/MenuStatus.hpp"

THUMB int fld::FieldCommandNormal::isExec()
{
    status::g_Menu.resetMenuEventNo();
    return true;
}

THUMB void fld::FieldCommandNormal::exec()
{
    CommandObjectDefineFieldSystem::setNormal();
}

THUMB int fld::FieldCommandNormal::isEnd()
{
    return true;
}
