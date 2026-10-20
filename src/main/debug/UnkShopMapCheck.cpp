#pragma ipa file
#include "main/debug/UnkShopMapCheck.hpp"
#include "nitro/os.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/cmn/PlayerManager.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/data/FileLoader.hpp"
#include "main/global/Global.hpp"
#include "main/global/StageLink.hpp"
#include "main/leveldata/EventList.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/Status.hpp"
#include "ov001/town/TownPlayerManager.hpp"

#pragma thumb on

inline twn::TOWN_PLAYER_ACTION_TYPE twn::TownPlayerManager::getActionType()
{
    return player_.actionType_;
}

inline dq5::level::EventList* dq5::level::EventList::getRecord(int index)
{
    return (EventList*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::EventList::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline unsigned short dq5::level::EventList::getIndex()
{
    return index;
}

inline char* dq5::level::EventList::getFloor()
{
    return floor;
}

UnkShopMapCheck::UnkShopMapCheck()
{
    waitFrame_ = 0x3c;
    startIndex_ = 0;
    endIndex_ = 0x15a;
    unk_1c = 0x15a;
    requestState_ = 1;
    state_ = 0;
}

void UnkShopMapCheck::vf0c()
{
    if (frame_ == 10) {
        unkfunc_02038148();
    }
    if (waitFrame_ == frame_) {
        if (twn::TownPlayerManager::getSingleton().getActionType() == twn::ACTION_TYPE_FALL) {
            waitFrame_ = frame_ + 10;
            return;
        }
        unkfunc_02038118();
    }
}

void UnkShopMapCheck::vf04()
{
    index_ = startIndex_;
    requestState_ = 2;
    state_ = 0;
}

void UnkShopMapCheck::unkfunc_02038118()
{
    int index = ++index_;
    if (index > endIndex_) {
        requestState_ = 1;
        state_ = 0;
    } else if (index > unk_1c) {
        requestState_ = 1;
        state_ = 0;
    } else {
        requestState_ = 2;
        state_ = 0;
    }
}

void UnkShopMapCheck::unkfunc_02038148()
{
    int index = index_ + 1;
    dq5::level::EventList* event = NULL;
    cmn::PartyTalk::getSingleton().initialize();
    dq5::level::EventList::setup();
    for (int i = 0; i < dq5::level::EventList::getArraySize(); i++) {
        if (index == dq5::level::EventList::getRecord(i)->getIndex()) {
            event = dq5::level::EventList::getRecord(i);
            break;
        }
    }
    char floor[0x20];
    dss::memset(floor, 0, 0x20);
    dss::strcpy_s(floor, 0x20, event->getFloor());
    char name[0x20];
    for (int i = 0; i < 0x20; i++) {
        name[i] = dss::toLower(floor[i]);
    }
    dq5::level::EventList::cleanup();
    char path[0x80];
    func_020873c0(path, 0x80, "data/map/%s.lz", name);
    if (dss::g_File.isExist(path, dss::File::None)) {
        status::Status::initialize();
        status::Status::setFlagShopIndex(index);
        status::Status::flagShopInit = 1;
        cmn::PlayerManager::setLock(true);
        util::StageLink::resetTownExitIndex();
        g_Global.startTown(name);
        status::g_StageInfo.flagMapChange_ = 1;
    }
}

void UnkDebugTask::unkfunc_02038248()
{
    if (requestState_ != state_) {
        state_ = requestState_;
        frame_ = 0;
    }
    if (state_ != 1) {
        if (state_ == 3) {
            vf10();
        }
        if (state_ == 2) {
            vf0c();
        }
        frame_++;
    }
}

void UnkDebugTask::vf08()
{
}

void UnkDebugTask::vf10()
{
}

UnkShopMapCheck data_020dc058;
