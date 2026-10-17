#include "ov001/town/TownFurniture.hpp"

THUMB twn::TownFurnitureNothing::TownFurnitureNothing()
{
}

THUMB twn::TownFurnitureNothing::~TownFurnitureNothing()
{
}

THUMB void twn::TownFurnitureNothing::setSecondMessage()
{
    if (data_ != 0 && (furniture_.flag_ & CHECK_MESSAGE_FLAG)) {
        addMessage(data_, true);
    }
}
