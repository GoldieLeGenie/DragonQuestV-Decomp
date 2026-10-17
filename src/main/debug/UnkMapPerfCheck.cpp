#pragma ipa file
#include "main/debug/UnkMapPerfCheck.hpp"
#include "main/debug/UnkDebugTurnTask.hpp"
#include "main/cmn/PlayerManager.hpp"
#include "main/data/FileLoader.hpp"
#include "main/global/Global.hpp"
#include "main/global/StageLink.hpp"
#include "main/leveldata/FloorList.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"

#pragma thumb on

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::level::FloorList* dq5::level::FloorList::getRecord(int index)
{
    return (FloorList*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

UnkMapPerfCheck::UnkMapPerfCheck()
{
    waitFrame_ = 0x40;
    startFloor_ = 1;
    endFloor_ = 0;
    unk_1c = 0;
    chapterType_ = 0;
    timeZoneType_ = 0;
    perf_.initialize();
    requestState_ = 1;
    state_ = 0;
}

void UnkMapPerfCheck::vf0c()
{
    perf_.update();
    if (waitFrame_ == frame_) {
        perf_.stop();
        nextFloor();
        if (state_ == 2) {
            searchFloor();
            if (state_ == 2) {
                startFloor();
            }
        }
    }
}

void UnkMapPerfCheck::vf10()
{
    if (frame_ == 0) {
        gTownMenu_MESSAGE.openMessageForTALK();
        gTownMenu_MESSAGE.addMessage("FINISH");
    }
    if (gTownMenu_MESSAGE.isOpen() && gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_OK) {
        gTownMenu_MESSAGE.close();
    }
}

void UnkMapPerfCheck::vf04()
{
    floor_ = startFloor_;
    chapterMask_ = getChapterMask(chapterType_);
    timeZoneMask_ = getTimeZoneMask(timeZoneType_);
    searchFloor();
    startFloor();
    requestState_ = 2;
    state_ = 0;
}

void UnkMapPerfCheck::vf08()
{
    perf_.finish();
    requestState_ = 3;
    state_ = 0;
}

void UnkMapPerfCheck::startFloor()
{
    if (dq5::level::FloorList::binary_.getRecordCount() > floor_) {
        char* name = dq5::level::FloorList::getRecord(floor_)->floor;
        if (name == NULL) {
            vf08();
            return;
        }
        char path[0x80];
        dss::sprintf_s(path, 0x80, "data/map/%s.lz", name);
        if (dss::g_File.isExist(path, dss::File::None)) {
            status::g_Story.setChapter((dq5::CHAPTER_NO)chapter_);
            if (timeZone_ == 0) {
                status::g_StageInfo.timeZone_ = TIME_ZONE_DAYTIME;
            } else {
                status::g_StageInfo.timeZone_ = TIME_ZONE_NIGHT;
            }
            status::g_Party.clear();
            status::g_Party.add(1, true);
            cmn::PlayerManager::setLock(true);
            util::StageLink::resetTownExitIndex();
            g_Global.startTown(name);
            status::g_StageInfo.flagMapChange_ = 1;
            perf_.start();
            if (turnCheck_ != 0) {
                data_020f3520.vf04();
            }
            requestState_ = 2;
            state_ = 0;
        } else {
            vf08();
        }
    }
}

void UnkMapPerfCheck::nextFloor()
{
    if (++timeZone_ == 2) {
        timeZone_ = 0;
        if (++chapter_ == 6) {
            chapter_ = 0;
            floor_++;
        }
    }
}

void UnkMapPerfCheck::searchFloor()
{
    for (;;) {
        if (floor_ > endFloor_) {
            vf08();
            return;
        }
        if (isCheckFloor()) {
            return;
        }
        nextFloor();
    }
}

bool UnkMapPerfCheck::isCheckFloor()
{
    if (dq5::level::FloorList::binary_.getRecordCount() <= floor_) {
        return false;
    }
    if (isSkipFloor(dq5::level::FloorList::getRecord(floor_)->floorIndex) == true) {
        return false;
    }
    char* name = dq5::level::FloorList::getRecord(floor_)->floor;
    if (name == NULL) {
        return true;
    }
    if (!(getChapterMask(chapter_) & chapterMask_)) {
        return false;
    }
    if (!(getTimeZoneMask(timeZone_) & timeZoneMask_)) {
        return false;
    }
    char path[0x80];
    dss::sprintf_s(path, 0x80, "data/map/%s.lz", name);
    if (dss::g_File.isExist(path, dss::File::None) != false) {
        return true;
    }
    return false;
}

int UnkMapPerfCheck::getChapterMask(int type)
{
    int mask = 0;
    switch (type) {
    case 0:
        mask = 0x1;
        break;
    case 1:
        mask = 0x2;
        break;
    case 2:
        mask = 0x4;
        break;
    case 3:
        mask = 0x8;
        break;
    case 4:
        mask = 0x10;
        break;
    case 5:
        mask = 0x20;
        break;
    case 6:
        mask = 0xf;
        break;
    case 7:
        mask = 0x3f;
        break;
    }
    return mask;
}

int UnkMapPerfCheck::getTimeZoneMask(int type)
{
    int mask = 0;
    switch (type) {
    case 0:
        mask = 0x40;
        break;
    case 1:
        mask = 0x80;
        break;
    case 2:
        mask = 0xc0;
        break;
    }
    return mask;
}

bool UnkMapPerfCheck::isSkipFloor(int floorIndex)
{
    if (floorIndex == 0 || floorIndex == 18 || floorIndex == 89 || floorIndex == 90) {
        return true;
    }
    if (floorIndex == 100 || floorIndex == 113 || floorIndex == 114 || floorIndex == 115 || floorIndex == 170) {
        return true;
    }
    if (floorIndex == 250 || floorIndex == 331 || floorIndex == 332) {
        return true;
    }
    if (floorIndex == 400 || (floorIndex >= 439 && floorIndex <= 442) || (floorIndex >= 451 && floorIndex <= 456)) {
        return true;
    }
    if (floorIndex == 470 || floorIndex == 514) {
        return true;
    }
    if (floorIndex == 600 || floorIndex == 638) {
        return true;
    }
    if (floorIndex >= 700 && floorIndex <= 721) {
        return true;
    }
    if (floorIndex >= 726) {
        return true;
    }
    return false;
}

UnkMapPerfCheck data_020d8800;
