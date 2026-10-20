#include "main/window/InputControl.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

int window::InputControl::prev_ = PHASE_NORMAL;
int window::InputControl::next_ = PHASE_NORMAL;

THUMB window::InputControl::InputControl()
{
}

THUMB window::InputControl::~InputControl()
{
}

THUMB void window::InputControl::playerLock(bool flag)
{
    if (data_02101c88.isCurrentPart(4)) {
        twn::TownPlayerManager::getSingleton().setLock(flag);
    }
    if (data_02101c88.isCurrentPart(6)) {
        fld::FieldPlayerManager::getSingleton().setLock(flag);
    }
}

THUMB bool window::InputControl::isPlayerLock()
{
    if (data_02101c88.isCurrentPart(4)) {
        return twn::TownPlayerManager::getSingleton().isLock();
    }
    if (data_02101c88.isCurrentPart(6)) {
        return fld::FieldPlayerManager::getSingleton().isLock();
    }
    return true;
}

THUMB void window::InputControl::setupIcon()
{
}
