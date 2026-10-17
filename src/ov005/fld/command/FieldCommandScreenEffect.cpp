#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/window/ScreenEffectManager.hpp"

THUMB int fld::FieldCommandScreenEffect::isExec()
{
    if (window::gScreenEffect.setupFlag_ != 0) {
        return true;
    }
    return false;
}

THUMB int fld::FieldCommandScreenEffect::isEnd()
{
    if (window::gScreenEffect.isEnd()) {
        window::gScreenEffect.cleanUp();
        return true;
    }
    return false;
}

THUMB void fld::FieldCommandScreenEffect::exec()
{
    CommandObjectDefineFieldSystem::setScreenEffect();
}
