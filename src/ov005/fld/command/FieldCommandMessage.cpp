#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/window/MessageControl.hpp"
#include "ov005/fld/FieldWindowSystem.hpp"

THUMB int fld::FieldCommandMessage::isExec()
{
    if (FieldWindowSystem::getSingleton()->message_open_ != 0) {
        window::gMessageControl.startMessage();
        FieldWindowSystem::getSingleton()->message_open_ = 0;
        return true;
    }
    return false;
}

THUMB void fld::FieldCommandMessage::exec()
{
    CommandObjectDefineFieldSystem::setMessage();
}

THUMB int fld::FieldCommandMessage::isEnd()
{
    return window::gMessageControl.state_ == window::MessageControl::END_MESSAGE;
}
