#include "ov005/fld/FieldCommand.hpp"
#include "main/cmn/CommandObjectField.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/StatusChange.hpp"
#include "main/text/TextAPI.hpp"
#include "ov005/fld/FieldWindowSystem.hpp"

THUMB int fld::FieldCommandWalkCount::isExec()
{
    status::g_Party.setBattleMode();
    status::StatusChange& statusChange = status::g_Party.getPlayerStatus(0).haveStatusInfo_.statusChange_;
    if (statusChange.isRelease(dq5::level::ActionParam::ACTIONTYPE(0x2b))) {
        int mess = 0;
        switch (statusChange.getActionIndex(dq5::level::ActionParam::ACTIONTYPE(0x2b))) {
            case 0x13a:
                TextAPI::setMACRO0(10, 0x40000000, 0xa3);
                mess = statusChange.getReleaseMessage(dq5::level::ActionParam::ACTIONTYPE(0x2b));
                break;
            case 0x83:
                mess = statusChange.getReleaseMessage(dq5::level::ActionParam::ACTIONTYPE(0x2b));
                break;
        }
        ui_MsgSndSet(0x30);
        FieldWindowSystem::getSingleton()->openMessage(mess, 1);
        statusChange.cleanup(dq5::level::ActionParam::ACTIONTYPE(0x2b));
    }
    if (statusChange.isRelease(dq5::level::ActionParam::ACTIONTYPE(0x2c))) {
        int mess = statusChange.getReleaseMessage(dq5::level::ActionParam::ACTIONTYPE(0x2c));
        ui_MsgSndSet(0x30);
        FieldWindowSystem::getSingleton()->openMessage(mess, 1);
        statusChange.cleanup(dq5::level::ActionParam::ACTIONTYPE(0x2c));
    }
    if (statusChange.isRelease(dq5::level::ActionParam::ACTIONTYPE(0x2f))) {
        switch (statusChange.getActionIndex(dq5::level::ActionParam::ACTIONTYPE(0x2f))) {
            case 0x14c:
                TextAPI::setMACRO0(10, 0x40000000, 0xb5);
                statusChange.getReleaseMessage(dq5::level::ActionParam::ACTIONTYPE(0x2f));
                break;
            case 0x141:
                TextAPI::setMACRO0(10, 0x40000000, 0xaa);
                statusChange.getReleaseMessage(dq5::level::ActionParam::ACTIONTYPE(0x2f));
                break;
        }
        int mess = statusChange.getReleaseMessage(dq5::level::ActionParam::ACTIONTYPE(0x2f));
        ui_MsgSndSet(0x30);
        FieldWindowSystem::getSingleton()->openMessage(mess, 1);
        statusChange.cleanup(dq5::level::ActionParam::ACTIONTYPE(0x2f));
    }
    return false;
}

THUMB int fld::FieldCommandWalkCount::isEnd()
{
    return true;
}

THUMB void fld::FieldCommandWalkCount::exec()
{
    CommandObjectDefineFieldSystem::setWalkCount();
}
