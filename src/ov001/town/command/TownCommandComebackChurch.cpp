#pragma ipa file
#include "ov001/town/command/TownCommandComebackChurch.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "ov019/leveldata/ChurchMessage.hpp"
#include "main/town/TownCommandEncount.hpp"
#include "main/leveldata/MapChurch.hpp"
#include "main/leveldata/VehicleData.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"

#pragma thumb on

inline dq5::level::VehicleData* dq5::level::VehicleData::getRecord(int index)
{
    return (VehicleData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::MapChurch* dq5::level::MapChurch::getRecord(int index)
{
    return (MapChurch*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatusInfo::getPlayerIndex() const
{
    return haveStatus_.getPlayerIndex();
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline int status::BattleResult::isDisableChurchMessage()
{
    return playerDemolitionMessage_;
}

inline void status::BattleResult::setDisableChurchMessage(int flag)
{
    playerDemolitionMessage_ = flag;
}

inline void status::StageInfo::setReliveCheckFlag(bool flag)
{
    reliveCheckFlag_ = flag;
}

inline int status::StageInfo::getReturnChurch()
{
    return returnChurchData_;
}

inline int status::StageInfo::getLoadChurch()
{
    return loadChurchData_;
}

inline dss::Fix32Vector3& status::StageInfo::getOverviewPosition()
{
    return overviewPosition_;
}

inline void status::StageInfo::setOverviewTempPosition(dss::Fix32Vector3& pos)
{
    overviewTempPosition_ = pos;
}

inline void status::StageInfo::setShipPosition(int index, dss::Fix32Vector3& pos)
{
    shipPosition_[index] = pos;
}

inline void status::StageInfo::setRanaMapSurfaceId(int id)
{
    lastFldSurface_ = id;
}

inline char dq5::level::MapChurch::getChurchman()
{
    return byte_1 & 1;
}

inline unsigned short dq5::level::MapChurch::getRanafloor()
{
    return ranafloor;
}

inline unsigned char dq5::level::MapChurch::getLocationSounen()
{
    return locationSounen;
}

inline unsigned char dq5::level::MapChurch::getLocationSeinen()
{
    return locationSeinen;
}

inline int dq5::level::VehicleData::getShipX()
{
    return shipX;
}

inline int dq5::level::VehicleData::getShipY()
{
    return shipY;
}

inline unsigned long dq5::level::ChurchMessage::getMessage1()
{
    return message1;
}

inline unsigned long dq5::level::ChurchMessage::getMessage2()
{
    return message2;
}

inline char dq5::level::ChurchMessage::getVocalSound()
{
    return byte_1 & 1;
}

inline dq5::level::ChurchMessage* dq5::level::ChurchMessage::getRecord(int index)
{
    return (ChurchMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

twn::TownCommandComebackChurch::TownCommandComebackChurch()
{
    wait_ = defaultWait;
}

twn::TownCommandComebackChurch::~TownCommandComebackChurch()
{
}

int twn::TownCommandComebackChurch::isExec()
{
    if (status::g_BattleResult.isDisableChurchMessage() != 2) {
    if (wait_ == defaultWait) {
        status::g_Party.setAllPlayerMode();
        int pusan = status::g_Party.getSortIndex(15);
        if (pusan != -1) {
            status::g_Party.del(pusan);
        }
        int hero = status::g_Party.getSortIndex(1);
        if (status::g_Party.getPlayerStatus(hero).getHaveStatusInfo().isDeath()) {
            status::g_Party.getPlayerStatus(hero).getHaveStatusInfo().revival();
        }
        status::g_Party.setAllPlayerMode();
        int reorderPlayer[4] = { -1 };
        for (int i = 0; i < 4; i++) {
            reorderPlayer[i] = -1;
        }
        int human[10] = { -1 };
        for (int i = 0; i < 10; i++) {
            human[i] = -1;
        }
        int monster[10] = { -1 };
        for (int i = 0; i < 10; i++) {
            monster[i] = -1;
        }
        int npcIndex[2] = { -1 };
        for (int i = 0; i < 2; i++) {
            npcIndex[i] = -1;
        }
        int humanCount = 0, monsterCount = 0, npcCount = 0, npcCgIndex = 0;
        int partyCount = status::g_Party.getCount();
        int carriageOutCount = status::g_Party.getCarriageOutCount();
        for (int i = 0; i < partyCount; i++) {
            status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
            int type = statusInfo.getHaveStatus().playerType_;
            if (type == status::HaveStatus::TYPE_FRIENDMONSTER) {
                monster[monsterCount] = statusInfo.getPlayerIndex();
                monsterCount++;
            } else {
                int index = statusInfo.getPlayerIndex();
                if (type == status::HaveStatus::TYPE_NOBATTLENPC) {
                    if (npcCount == 0) {
                        npcCgIndex = statusInfo.getHaveStatus().getCharaIndex();
                    }
                    npcIndex[npcCount] = index;
                    npcCount++;
                } else {
                    human[humanCount] = index;
                    humanCount++;
                }
            }
        }
        for (int i = 0; i < humanCount; i++) {
            if (human[i] == 1) {
                for (int j = i; j > 0; j--) {
                    human[j] = human[j - 1];
                }
                human[0] = 1;
                break;
            }
        }
        for (int i = 0; i < monsterCount; i++) {
            human[humanCount + i] = monster[i];
        }
        for (int i = 0; i < npcCount; i++) {
            human[monsterCount + humanCount + i] = npcIndex[i];
        }
        status::g_Party.clear();
        for (int i = 0; i < partyCount; i++) {
            status::g_Party.add(human[i], true);
        }
        status::g_Party.setBattleModeAndCarriage();
        for (int i = 0; i < carriageOutCount - npcCount; i++) {
            reorderPlayer[i] = i;
        }
        status::g_Party.reorder(reorderPlayer[0], reorderPlayer[1], reorderPlayer[2], reorderPlayer[3]);
        if (npcCgIndex != 0) {
            status::g_Party.setAllPlayerMode();
            status::g_Party.getPlayerStatus(partyCount - 1).getHaveStatusInfo().getHaveStatus().setCharaIndex(npcCgIndex);
        }
        TownPlayerManager::getSingleton().resetParty();
        status::g_StageInfo.setReliveCheckFlag(false);
        status::PartyStatusUtility::resetForceReorderMember();
        dss::Fix32Vector3 pos = status::g_StageInfo.getOverviewPosition();
        status::g_StageInfo.setOverviewTempPosition(pos);
        TownPlayerManager::getSingleton().setLock(true);
        status::g_StageInfo.setReliveCheckFlag(true);
    }
    if (wait_ <= 0) {
        dq5::level::MapChurch::setup();
        dq5::level::ChurchMessage::setup();
        if (dq5::level::MapChurch::getRecord(status::g_StageInfo.getReturnChurch())->getChurchman() == 0) {
            if (dq5::level::ChurchMessage::getRecord(dq5::level::ChurchMessage::CHURCH_MES43)->getVocalSound()) {
                ui_MsgSndSet(0x32);
            } else {
                status::g_BattleResult.setDisableChurchMessage(2);
            }
            TownWindowSystem::getSingleton().openMessage(dq5::level::ChurchMessage::getRecord(dq5::level::ChurchMessage::CHURCH_MES43)->getMessage1(), 1);
        } else {
            if (dq5::level::ChurchMessage::getRecord(dq5::level::ChurchMessage::CHURCH_MES43)->getVocalSound()) {
                if (status::g_StageInfo.getLoadChurch() == 0x20) {
                    ui_MsgSndSet(0x31);
                } else {
                    ui_MsgSndSet(0x32);
                }
            } else {
                status::g_BattleResult.setDisableChurchMessage(2);
            }
            TownWindowSystem::getSingleton().openMessage(dq5::level::ChurchMessage::getRecord(dq5::level::ChurchMessage::CHURCH_MES43)->getMessage2(), 1);
        }
        TownPlayerManager::getSingleton().setLock(false);
        status::g_BattleResult.setDisableChurchMessage(2);
        wait_ = defaultWait;
        int index;
        if (status::g_Story.getChapter() == dq5::CHAPTER_SEINENKI) {
            index = dq5::level::MapChurch::getRecord(status::g_StageInfo.getReturnChurch())->getLocationSeinen();
        } else {
            index = dq5::level::MapChurch::getRecord(status::g_StageInfo.getReturnChurch())->getLocationSounen();
        }
        dss::Fix32Vector3 pos;
        pos.vx.value = dq5::level::VehicleData::getRecord(index)->getShipX();
        pos.vy.value = dq5::level::VehicleData::getRecord(index)->getShipY();
        status::g_StageInfo.setShipPosition(1, pos);
        if (index != 0x1c) {
            pos.vx = 578.5f;
            pos.vy = 2397.0f;
        }
        status::g_StageInfo.setShipPosition(0, pos);
        int mapId = dq5::level::MapChurch::getRecord(status::g_StageInfo.getReturnChurch())->getRanafloor();
        status::g_StageInfo.setRanaMapNameId(mapId);
        status::g_StageInfo.setRanaMapSurfaceId(0x70001);
        dq5::level::ChurchMessage::cleanup();
        dq5::level::MapChurch::cleanup();
    } else {
        wait_--;
    }
    return true;
    }
    return false;
}

int twn::TownCommandComebackChurch::isEnd()
{
    return true;
}

void twn::TownCommandComebackChurch::exec()
{
    CommandObjectDefineTownSystem::setLoadReturn();
}
