#include "ov001/town/TownSystem.hpp"
#include "main/window/MessageControl.hpp"

#pragma thumb on

twn::TownSystemMessage::TownSystemMessage()
{
}

twn::TownSystemMessage::~TownSystemMessage()
{
}

void twn::TownSystemMessage::initialize()
{
}

void twn::TownSystemMessage::terminate()
{
}

void twn::TownSystemMessage::execute()
{
    window::gMessageControl.execute();
}

void twn::TownSystemMessage::draw()
{
}
