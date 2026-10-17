#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/BattleResult.hpp"
#include "main/global/Global.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/leveldata/VehicleData.hpp"
#include "main/leveldata/MapChurch.hpp"
#include "main/leveldata/PlayerCarriage.hpp"
#include "main/leveldata/LevelDataUtility.hpp"
#include "main/cmn/CommonRuraData.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/town/TownSugorokuInfo.hpp"
#include "main/town/TownTruckData.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::level::MapChurch* dq5::level::MapChurch::getRecord(int index)
{
    return (MapChurch*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::VehicleData* dq5::level::VehicleData::getRecord(int index)
{
    return (VehicleData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline int Global::getMapNameId() { return nextMapNameId; }

inline status::StageInfo::StageInfo()
{
}

inline int dq5::level::VehicleData::getShipX() { return shipX; }
inline int dq5::level::VehicleData::getShipY() { return shipY; }
inline fx32 dq5::level::MapChurch::getPlayerX() { return playerX; }
inline fx32 dq5::level::MapChurch::getPlayerY() { return playerY; }
inline fx32 dq5::level::MapChurch::getPlayerZ() { return playerZ; }
inline unsigned short dq5::level::MapChurch::getDirection() { return direction; }
inline unsigned short dq5::level::MapChurch::getSettingflag() { return settingflag; }
inline unsigned short dq5::level::MapChurch::getCheckflag() { return checkflag; }
inline unsigned short dq5::level::MapChurch::getFloor() { return floor; }
inline char dq5::level::MapChurch::getLoadOnly() { return (byte_1 & 2) >> 1; }
inline char dq5::level::MapChurch::getMapTime() { return (byte_1 & 0x1c) >> 2; }
inline char dq5::level::MapChurch::getChapter() { return (byte_1 & 0xe0) >> 5; }
inline unsigned int dq5::level::MapChurch::getArraySize() { return binary_.getRecordCount(); }
inline unsigned char dq5::level::PlayerCarriage::getArea() { return area; }
inline char dq5::level::PlayerCarriage::getRelive() { return (byte_1 & 4) >> 2; }
inline dq5::level::PlayerCarriage* dq5::level::PlayerCarriage::getRecord(int index) { return (PlayerCarriage*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned int dq5::level::PlayerCarriage::getArraySize() { return binary_.getRecordCount(); }
inline bool status::PlayerStatus::isAlive() const { return !haveStatusInfo_.isDeath(); }
inline void status::BattleResult::setDisableChurchMessage(int flag) { playerDemolitionMessage_ = flag; }

status::StageInfo status::g_StageInfo;

THUMB void status::StageInfo::initialize()
{
    cmn::CommonRuraData::getSingleton().initialize();
    worldTime_ = 0;
    chapterLoad_ = 0;
    for (int i = 0; i < 9; i++) {
        lastParty_[i] = 0;
    }
    lastParty_[0] = 1;
    shipPosition_[1].vx.value = dq5::level::VehicleData::getRecord(10)->getShipX();
    shipPosition_[1].vy.value = dq5::level::VehicleData::getRecord(10)->getShipY();
    shipPosition_[1].vz.value = 0;
    shipPosition_[0].vx.value = dq5::level::VehicleData::getRecord(10)->getShipX();
    shipPosition_[0].vy.value = dq5::level::VehicleData::getRecord(10)->getShipY();
    shipPosition_[0].vz.value = 0;
    firmamentPosition_.vx.value = 0xdea000;
    firmamentPosition_.vy.value = 0x73a000;
    firmamentPosition_.vz.value = 0;
    for (int i = 0; i < 10; i++) {
        rockFlag_[i] = 1;
    }
    setRuraFlag(0);
    ropeLink_ = 0;
    idoLinkInFlag_ = 0;
    idoLinkOutFlag_ = 0;
    shipEncount_ = 0;
    encountMapUid_ = 0;
    encount_ = 0;
    riremitMap_ = 0x2d3;
    symbolID_ = 0x10001;
    kimeraSymbol_ = 0;
    setRanaMapNameId(0);
    lastFldSurface_ = -1;
    sepiaFlag_ = 0;
    cmn::g_cmnPartyInfo.rideOnType_ = cmn::RIDE_ON_NONE;
    cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
    twn::g_SugorokuInfo.continueState_ = 0;
    cmn::g_cmnPartyInfo.prevLocation_ = 0;
    returnGame_ = dq5::RETURN_GAME_NONE;
    setTimeZone(TIME_ZONE_DAYTIME);
    initSymbolFlag();
    initFurnFlag();
    initDoorOpenFlag();
    resetVeil(true);
    initPuzzle();
}

THUMB void status::StageInfo::collectMapFlag(profile::SAVETYPE savetype, profile::PROFILE_PARTY* pparty)
{
    for (int i = 0; i < 16; i++) {
        pparty->MAPSYMBOL_FLAG[i] = symbolFlag_[i].flag_;
    }
    for (int i = 0; i < 16; i++) {
        pparty->MAPVEIL_FLAG[i] = mapVeil_[i].flag_;
    }
    for (int i = 0; i < 128; i++) {
        pparty->FURN_FLAG[i] = furnFlag_[i].flag_;
    }
    for (int i = 0; i < 32; i++) {
        if (savetype == profile::SAVETYPE_RESUME) {
            pparty->BREAK_FLAG[i] = breakFlag_[i].flag_;
        } else {
            pparty->BREAK_FLAG[i] = 0;
        }
    }
    for (int i = 0; i < 32; i++) {
        pparty->DOOR_FLAG[i] = doorFlag_[i].flag_;
    }
    for (int i = 0; i < 10; i++) {
        pparty->ROCK_VX[i] = rock_[i].vx.value;
        pparty->ROCK_VY[i] = rock_[i].vy.value;
        pparty->ROCK_VZ[i] = rock_[i].vz.value;
    }
}

THUMB void status::StageInfo::deliverMapFlag(profile::SAVETYPE savetype, profile::PROFILE_PARTY* pparty)
{
    for (int i = 0; i < 16; i++) {
        symbolFlag_[i].flag_ = pparty->MAPSYMBOL_FLAG[i];
    }
    for (int i = 0; i < 16; i++) {
        mapVeil_[i].flag_ = pparty->MAPVEIL_FLAG[i];
    }
    for (int i = 0; i < 128; i++) {
        furnFlag_[i].flag_ = pparty->FURN_FLAG[i];
    }
    for (int i = 0; i < 32; i++) {
        if (savetype == profile::SAVETYPE_RESUME) {
            breakFlag_[i].flag_ = pparty->BREAK_FLAG[i];
        } else {
            breakFlag_[i].flag_ = 0;
        }
    }
    for (int i = 0; i < 32; i++) {
        pparty->DOOR_FLAG[i] = doorFlag_[i].flag_;
    }
    for (int i = 0; i < 10; i++) {
        rock_[i].vx.value = pparty->ROCK_VX[i];
        rock_[i].vy.value = pparty->ROCK_VY[i];
        rock_[i].vz.value = pparty->ROCK_VZ[i];
    }
}

THUMB void status::StageInfo::resetVeil(bool flag)
{
    if (flag) {
        for (int i = 0; i < 16; i++) {
            mapVeil_[i].set(0xffff);
        }
    } else {
        for (int i = 0; i < 16; i++) {
            mapVeil_[i].clear();
        }
    }
}

THUMB void status::StageInfo::setMapVeil(int x, int y, int flag)
{
    if (g_Story.getChapter() == dq5::CHAPTER_ENDING) {
        return;
    }
    int mx = x * 16 / 256;
    int my = y * 16 / 256;
    mapVeil_[my].flag_ &= ~(1 << mx);
}

THUMB bool status::StageInfo::getMapVeil(int x, int y)
{
    dss::BitFlag<unsigned short>& flag = mapVeil_[y];
    return (flag.flag_ & (1 << x)) ? true : false;
}

THUMB void status::StageInfo::setSymbolFlag(int index)
{
    symbolFlag_[index / 8].flag_ |= 1 << (index % 8);
}

THUMB bool status::StageInfo::getSymbolFlag(int index)
{
    dss::BitFlag<unsigned char>& flag = symbolFlag_[index / 8];
    return (flag.flag_ & (1 << (index % 8))) ? true : false;
}

THUMB void status::StageInfo::initSymbolFlag()
{
    for (int i = 0; i < 16; i++) {
        symbolFlag_[i].clear();
    }
}

THUMB void status::StageInfo::setFurnFlag(int index)
{
    furnFlag_[index / 8].flag_ |= 1 << (index % 8);
}

THUMB bool status::StageInfo::getFurnFlag(int index)
{
    dss::BitFlag<unsigned char>& flag = furnFlag_[index / 8];
    return (flag.flag_ & (1 << (index % 8))) ? true : false;
}

THUMB void status::StageInfo::removeFurnFlag(int index)
{
    furnFlag_[index / 8].flag_ &= ~(1 << (index % 8));
}

THUMB void status::StageInfo::initFurnFlag()
{
    for (int i = 0; i < 128; i++) {
        furnFlag_[i].clear();
    }
}

THUMB void status::StageInfo::setDoorOpenFlag(int index)
{
    doorFlag_[index / 8].flag_ |= 1 << (index % 8);
}

THUMB void status::StageInfo::removeDoorOpenFlag(int index)
{
    doorFlag_[index / 8].flag_ &= ~(1 << (index % 8));
}

THUMB bool status::StageInfo::getDoorOpenFlag(int index)
{
    dss::BitFlag<unsigned char>& flag = doorFlag_[index / 8];
    return (flag.flag_ & (1 << (index % 8))) ? true : false;
}

THUMB void status::StageInfo::initDoorOpenFlag()
{
    for (int i = 0; i < 32; i++) {
        doorFlag_[i].clear();
    }
}

THUMB void status::StageInfo::setFurnBreakFlag(int index)
{
    breakFlag_[index / 8].flag_ |= 1 << (index % 8);
}

THUMB bool status::StageInfo::getFurnBreakFlag(int index)
{
    dss::BitFlag<unsigned char>& flag = breakFlag_[index / 8];
    return (flag.flag_ & (1 << (index % 8))) ? true : false;
}

THUMB void status::StageInfo::initFurnBreakFlag()
{
    for (int i = 0; i < 32; i++) {
        breakFlag_[i].clear();
    }
}

THUMB void status::StageInfo::setTimeZone(TIME_ZONE time)
{
    timeZone_ = time;
    switch (time) {
    case TIME_ZONE_MORNING:
        worldTime_ = cmn::WorldLocation::getMorning();
        break;
    case TIME_ZONE_DAYTIME:
        worldTime_ = cmn::WorldLocation::getDaytime();
        break;
    case TIME_ZONE_EVENING:
        worldTime_ = cmn::WorldLocation::getEvening();
        break;
    case TIME_ZONE_NIGHT:
        worldTime_ = cmn::WorldLocation::getNight();
        break;
    }
}

THUMB dq5::DAY_NIGHT status::StageInfo::getDayNight()
{
    return cmn::WorldLocation::getCurrentDayNight();
}

THUMB TIME_ZONE status::StageInfo::getTimeZone()
{
    return timeZone_;
}

THUMB void status::StageInfo::setWorldTime(unsigned short wt)
{
    worldTime_ = wt;
    timeZone_ = cmn::WorldLocation::getCurrentTimeZone();
}

THUMB int status::StageInfo::getWorldTime() const
{
    return worldTime_;
}

THUMB void status::StageInfo::setChurchMapNameId(unsigned short nameId)
{
    int index = -1;
    int timezone = -1;
    overviewPosition_ = overviewTempPosition_;
    dq5::level::MapChurch::setup();
    for (unsigned int i = 0; i < dq5::level::MapChurch::getArraySize(); i++) {
        if (nameId == dq5::level::MapChurch::getRecord(i)->getFloor()) {
            dq5::level::MapChurch* church = dq5::level::MapChurch::getRecord(i);
            int chapter = church->getChapter();
            if (chapter == g_Story.getChapter() || chapter == 0) {
                index = i;
                timezone = church->getMapTime();
                break;
            }
        }
    }
    if (dq5::level::MapChurch::getRecord(index)->getLoadOnly()) {
        loadChurchData_ = index;
    } else {
        returnChurchData_ = index;
        loadChurchData_ = index;
        if (timezone != 0) {
            switch (getTimeZone()) {
            case TIME_ZONE_MORNING:
            case TIME_ZONE_DAYTIME:
            case TIME_ZONE_EVENING:
                break;
            case TIME_ZONE_NIGHT:
                loadChurchData_++;
                break;
            }
        }
    }
    dq5::level::MapChurch::cleanup();
}

THUMB void status::StageInfo::returnChurch()
{
    dss::Fix32Vector3 pos;
    int floorIndex;
    unsigned short dir;
    int dataIndex = returnChurchData_;
    initDoorOpenFlag();
    initFurnBreakFlag();
    dq5::level::MapChurch::setup();
    for (unsigned int i = 0; i < dq5::level::MapChurch::getArraySize(); i++) {
        if (dq5::level::MapChurch::getRecord(i)->getCheckflag() != 0 && g_AreaFlag.check(dq5::level::MapChurch::getRecord(i)->getCheckflag())) {
            if (i == 30) {
                g_Party.setBattleMode();
                for (int j = 0; j < g_Party.getCount(); j++) {
                    if (g_Party.getPlayerStatus(j).isAlive()) {
                        dataIndex = i;
                        g_AreaFlag.set(dq5::level::MapChurch::getRecord(i)->getSettingflag());
                        g_BattleResult.setDisableChurchMessage(2);
                        break;
                    }
                }
            } else {
                dataIndex = i;
                g_AreaFlag.set(dq5::level::MapChurch::getRecord(i)->getSettingflag());
                g_BattleResult.setDisableChurchMessage(2);
            }
            break;
        }
    }
    pos.vx = dq5::level::MapChurch::getRecord(dataIndex)->getPlayerX();
    pos.vy = dq5::level::MapChurch::getRecord(dataIndex)->getPlayerY();
    pos.vz = dq5::level::MapChurch::getRecord(dataIndex)->getPlayerZ();
    dir = dq5::level::MapChurch::getRecord(dataIndex)->getDirection();
    floorIndex = dq5::level::MapChurch::getRecord(dataIndex)->getFloor();
    int area = dq5::level::g_LevelDataUtility.getAreaNoByMapId(floorIndex);
    unsigned int max = dq5::level::PlayerCarriage::getArraySize();
    returnChurchReOrder_ = 0;
    dq5::level::PlayerCarriage::setup();
    for (unsigned int i = 0; i < max; i++) {
        dq5::level::PlayerCarriage* data = dq5::level::PlayerCarriage::getRecord(i);
        if (area == data->getArea()) {
            if (data->getRelive() == 1 || area == 6) {
                returnChurchReOrder_ = 1;
                break;
            }
        }
    }
    dq5::level::PlayerCarriage::cleanup();
    cmn::g_extraMapLink.setExtraLinkTown(floorIndex, pos, dir);
    if (g_Story.getChapter() != dq5::CHAPTER_YOUNENKI) {
        g_StageInfo.setTimeZone(TIME_ZONE_DAYTIME);
    }
    dq5::level::MapChurch::cleanup();
}

THUMB void status::StageInfo::loadChurch()
{
    dss::Fix32Vector3 pos;
    dq5::level::MapChurch::setup();
    pos.vx = dq5::level::MapChurch::getRecord(loadChurchData_)->getPlayerX();
    pos.vy = dq5::level::MapChurch::getRecord(loadChurchData_)->getPlayerY();
    pos.vz = dq5::level::MapChurch::getRecord(loadChurchData_)->getPlayerZ();
    unsigned short dir = dq5::level::MapChurch::getRecord(loadChurchData_)->getDirection();
    int floorIndex = dq5::level::MapChurch::getRecord(loadChurchData_)->getFloor();
    cmn::g_extraMapLink.setExtraLinkTown(floorIndex, pos, dir);
    dq5::level::MapChurch::cleanup();
}

THUMB void status::StageInfo::initPuzzle()
{
    section_[0][0] = 1;
    section_[1][0] = 2;
    section_[2][0] = 3;
    section_[0][1] = 4;
    section_[1][1] = 5;
    section_[2][1] = 6;
    section_[0][2] = 7;
    section_[1][2] = 0;
    section_[2][2] = 8;
}

THUMB int status::StageInfo::getPuzzleSection(int x, int y)
{
    return section_[x][y];
}

THUMB void status::StageInfo::setPuzzleSection(int num, int x, int y)
{
    section_[x][y] = num;
}

THUMB void status::StageInfo::setRanaMap(int id)
{
    lastRanaStageNameId_ = g_Global.getMapNameId();
    lastFldSurface_ = id;
}

THUMB void status::StageInfo::setRanaMapNameId(int nameId)
{
    lastRanaStageNameId_ = nameId;
}

THUMB void status::StageInfo::setRuraFlag(int rura)
{
    ruraFlag_ = rura;
    if (rura == 1) {
        if (data_02101c88.unkfunc_02051818(dq5::FIELD_PART)) {
            fld::FieldPlayerManager::getSingleton().setLock(true);
        } else {
            twn::TownPlayerManager::getSingleton().setLock(true);
        }
    }
}

THUMB void status::StageInfo::setRuraTownID(int id)
{
    ruraSymbol_ = id;
}

THUMB int status::StageInfo::getRuraTownID()
{
    return ruraSymbol_;
}

THUMB void status::StageInfo::setFallFlag(bool flag)
{
    fallFlag_ = flag;
}

THUMB int status::StageInfo::getFallFlag()
{
    return fallFlag_;
}

THUMB void status::StageInfo::pushCameraAngle(dss::Vector3<short> pos)
{
    backupCameraAngle_ = pos;
}

THUMB dss::Vector3<short>& status::StageInfo::popCameraAngle()
{
    return backupCameraAngle_;
}

THUMB void status::StageInfo::playerFlagClear()
{
    shipEncount_ = 0;
    idoLinkOutFlag_ = 0;
    idoLinkInFlag_ = 0;
    encount_ = 0;
    initDoorOpenFlag();
    cmn::g_cmnPartyInfo.rideOnType_ = cmn::RIDE_ON_NONE;
    cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
    twn::g_SugorokuInfo.continueState_ = 0;
    cmn::g_cmnPartyInfo.prevLocation_ = 0;
}

THUMB void status::StageInfo::saveBeforTruckDataSetup()
{
    if (data_02101c88.unkfunc_02051818(dq5::TOWN_PART)) {
        twn::TownPlayerManager::getSingleton().player_.townActionTruck_.system_.saveBeforSetup();
    } else {
        switchDataFlag_ = 0;
        switchInitFlag_ = 0;
        wagonData1Flag_ = 0;
        wagonData2Flag_ = 0;
    }
}

THUMB void status::StageInfo::loadAfterTruckDataSetup()
{
    twn::loadAfterSetup();
}

ARM status::StageInfo::~StageInfo()
{
}

THUMB
