#include "ov005/fld/FieldCommand.hpp"
#include "main/btl/Encount.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

THUMB int fld::FieldCommandEncount::isExec()
{
    if (!status::g_StageAttribute.isEncount()) {
        return false;
    }
    if (btl::Encount::getSingleton()->enable_ == 0) {
        return false;
    }
    if (btl::Encount::getSingleton()->isEncounted()) {
        return true;
    }
    return false;
}

THUMB int fld::FieldCommandEncount::isEnd()
{
    return true;
}

THUMB void fld::FieldCommandEncount::exec()
{
    if (btl::Encount::getSingleton()->isEncounted()) {
        btl::Encount::getSingleton()->execField();
        status::g_StageAttribute.setBtlMapNameOnField(FieldPlayerManager::getSingleton().getLandType());
        if (FieldPlayerManager::getSingleton().player_.getMoveType() == 1) {
            status::g_StageInfo.shipEncount_ = 1;
        }
        FieldPlayerManager::getSingleton().unkfunc_02131c70();
    }
    CommandObjectDefineFieldSystem::setEncount();
}
