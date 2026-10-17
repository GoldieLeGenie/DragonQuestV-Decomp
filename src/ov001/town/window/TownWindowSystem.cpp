#include "ov001/town/TownWindowSystem.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/window/MessageControl.hpp"

THUMB twn::TownWindowSystem::TownWindowSystem()
{
    unk_00 = 0;
}

THUMB twn::TownWindowSystem& twn::TownWindowSystem::getSingleton()
{
    static TownWindowSystem m_singleton;
    return m_singleton;
}

THUMB void twn::TownWindowSystem::initialize()
{
    town_message_ = false;
}

THUMB void twn::TownWindowSystem::terminate()
{
}

THUMB void twn::TownWindowSystem::openMessage(int message, int count)
{
    town_message_ = true;
    MenuAPI::openMessage(message, count);
}

THUMB void twn::TownWindowSystem::openCommonMessage()
{
    window::gMessageControl.MESSAGECOMMONWINDOW();
    town_message_ = true;
}

THUMB void twn::TownWindowSystem::openSystemMessage(int message, int count)
{
    town_message_ = true;
    MenuAPI::openMenu(&gTownMenu_MESSAGE);
    MenuAPI::openMessageWindowMenu();
    for (int i = 0; i < count; i++) {
        addCommonMessage(message + i);
    }
}

THUMB void twn::TownWindowSystem::openTalkMessage(int message, int count)
{
    town_message_ = true;
    MenuAPI::openMessage(message, count);
}

THUMB void twn::TownWindowSystem::openSystemMessage()
{
    MenuAPI::openMenu(&gTownMenu_MESSAGE);
    MenuAPI::openMessageWindowMenu();
    town_message_ = true;
}

THUMB void twn::TownWindowSystem::openTalkMessage()
{
    window::gMessageControl.MESSAGECOMMONWINDOW();
    town_message_ = true;
}

THUMB void twn::TownWindowSystem::addCommonMessage(int message)
{
    window::gMessageControl.ADDCOMMONWINDOW(message);
}

THUMB void twn::TownWindowSystem::serialCommonMessage(int message)
{
    window::gMessageControl.SERIALCOMMONWINDOW(message);
    town_message_ = true;
}

THUMB void twn::TownWindowSystem::waitCommonMessage()
{
    window::gMessageControl.WAITCOMMONWINDOW();
}

THUMB void twn::TownWindowSystem::clearCommonMessage()
{
    window::gMessageControl.CLEARCOMMONWINDOW();
}

THUMB int twn::TownWindowSystem::isMessageStart()
{
    return town_message_;
}

THUMB bool twn::TownWindowSystem::isMessageOpen()
{
    return window::gMessageControl.state_ != window::MessageControl::END_MESSAGE;
}

THUMB void twn::TownWindowSystem::setMessageFlag(int flag)
{
    town_message_ = flag;
}

THUMB bool twn::TownWindowSystem::isWait()
{
    return MenuAPI::isWaitMessage();
}
