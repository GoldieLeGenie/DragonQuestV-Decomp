#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

THUMB int fld::FieldCommandVehicle::isExec()
{
    if (FieldPlayerManager::getSingleton().player_.getMoveType() == 0 || FieldPlayerManager::getSingleton().player_.getMoveType() == 1) {
        return false;
    }
    return true;
}

THUMB int fld::FieldCommandVehicle::isEnd()
{
    return true;
}

THUMB void fld::FieldCommandVehicle::exec()
{
    CommandObjectDefineFieldSystem::setfieldVehicle();
}
