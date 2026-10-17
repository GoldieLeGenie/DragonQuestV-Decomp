#include "ov001/town/command/TownCommandWalkCount.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/text/TextAPI.hpp"
#include "main/town/TownCommandEncount.hpp"

#pragma thumb on

inline status::StatusChange& status::HaveStatusInfo::getStatusChange()
{
    return statusChange_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

int twn::TownCommandWalkCount::isExec()
{
    status::g_Party.setBattleMode();
    status::StatusChange& statusChange = status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getStatusChange();
    if (statusChange.isRelease(dq5::level::ActionParam::ACTIONTYPE_TOHEROSU)) {
        int mess = 0;
        switch (statusChange.getActionIndex(dq5::level::ActionParam::ACTIONTYPE_TOHEROSU)) {
        case 0x13a:
            TextAPI::setMACRO0(10, 0x40000000, 0xa3);
            mess = statusChange.getReleaseMessage(dq5::level::ActionParam::ACTIONTYPE_TOHEROSU);
            break;
        case 0x83:
            mess = statusChange.getReleaseMessage(dq5::level::ActionParam::ACTIONTYPE_TOHEROSU);
            break;
        }
        ui_MsgSndSet(0x30);
        TownWindowSystem::getSingleton().openMessage(mess, 1);
        statusChange.cleanup(dq5::level::ActionParam::ACTIONTYPE_TOHEROSU);
    }
    if (statusChange.isRelease(dq5::level::ActionParam::ACTIONTYPE_SINOBIASI)) {
        int mess = statusChange.getReleaseMessage(dq5::level::ActionParam::ACTIONTYPE_SINOBIASI);
        ui_MsgSndSet(0x30);
        TownWindowSystem::getSingleton().openMessage(mess, 1);
        statusChange.cleanup(dq5::level::ActionParam::ACTIONTYPE_SINOBIASI);
    }
    if (statusChange.isRelease(dq5::level::ActionParam::ACTIONTYPE_NORMAL_MAMONONOESA)) {
        switch (statusChange.getActionIndex(dq5::level::ActionParam::ACTIONTYPE_NORMAL_MAMONONOESA)) {
        case 0x14c:
            TextAPI::setMACRO0(10, 0x40000000, 0xb5);
            statusChange.getReleaseMessage(dq5::level::ActionParam::ACTIONTYPE_NORMAL_MAMONONOESA);
            break;
        case 0x141:
            TextAPI::setMACRO0(10, 0x40000000, 0xaa);
            statusChange.getReleaseMessage(dq5::level::ActionParam::ACTIONTYPE_NORMAL_MAMONONOESA);
            break;
        }
        int mess = statusChange.getReleaseMessage(dq5::level::ActionParam::ACTIONTYPE_NORMAL_MAMONONOESA);
        ui_MsgSndSet(0x30);
        TownWindowSystem::getSingleton().openMessage(mess, 1);
        statusChange.cleanup(dq5::level::ActionParam::ACTIONTYPE_NORMAL_MAMONONOESA);
    }
    return false;
}

int twn::TownCommandWalkCount::isEnd()
{
    return true;
}

void twn::TownCommandWalkCount::exec()
{
    CommandObjectDefineTownSystem::setWalkCount();
}
