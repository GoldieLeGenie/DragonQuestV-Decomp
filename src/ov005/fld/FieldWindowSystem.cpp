#include "ov005/fld/FieldWindowSystem.hpp"
#include "main/window/MessageControl.hpp"

THUMB fld::FieldWindowSystem::FieldWindowSystem()
{
}

THUMB fld::FieldWindowSystem* fld::FieldWindowSystem::getSingleton()
{
    static FieldWindowSystem townWindowSystem;
    return &townWindowSystem;
}

THUMB void fld::FieldWindowSystem::initialize()
{
    message_open_ = 0;
}

THUMB void fld::FieldWindowSystem::terminate()
{
}

THUMB void fld::FieldWindowSystem::execute()
{
}

THUMB void fld::FieldWindowSystem::draw()
{
}

THUMB void fld::FieldWindowSystem::openMessage(int index, int count)
{
    message_open_ = 1;
    window::gMessageControl.MESSAGEWINDOW(index, count);
}

THUMB void fld::FieldWindowSystem::addCommonMessage(int index)
{
    window::gMessageControl.ADDCOMMONWINDOW(index);
}

THUMB void fld::FieldWindowSystem::openCommonMessage()
{
    message_open_ = 1;
    window::gMessageControl.MESSAGECOMMONWINDOW();
}
