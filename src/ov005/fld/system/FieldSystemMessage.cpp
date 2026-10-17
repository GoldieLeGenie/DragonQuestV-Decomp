#include "ov005/fld/FieldSystem.hpp"
#include "main/window/MessageControl.hpp"

THUMB fld::FieldSystemMessage::FieldSystemMessage()
{
}

THUMB fld::FieldSystemMessage::~FieldSystemMessage()
{
}

THUMB void fld::FieldSystemMessage::initialize()
{
}

THUMB void fld::FieldSystemMessage::terminate()
{
}

THUMB void fld::FieldSystemMessage::execute()
{
    window::gMessageControl.execute();
}

THUMB void fld::FieldSystemMessage::draw()
{
}
