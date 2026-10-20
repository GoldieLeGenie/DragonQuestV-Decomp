#pragma ipa file
#include "main/cmn/PartyTalk.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/cmn/WorldLocation.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/dss/UnkTextConvert.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/PartytalkEnding.hpp"
#include "main/leveldata/PartytalkEndingIndex.hpp"
#include "main/leveldata/PartytalkMonster.hpp"
#include "main/leveldata/PartytalkSeinen.hpp"
#include "main/leveldata/PartytalkSeinenIndex.hpp"
#include "main/leveldata/PartytalkSounen.hpp"
#include "main/leveldata/PartytalkSounenIndex.hpp"
#include "main/leveldata/PartytalkYounen.hpp"
#include "main/leveldata/PartytalkYounenIndex.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatus::getPlayerKindIndex() const
{
    return playerKindIndex_;
}

inline bool status::HaveStatus::isFriendMonster() const
{
    return playerType_ == TYPE_FRIENDMONSTER;
}

inline int status::HaveStatusInfo::getPlayerIndex() const
{
    return haveStatus_.getPlayerIndex();
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline status::HaveItem& status::HaveStatusInfo::getHaveItem()
{
    return haveItem_;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::level::PartytalkEndingIndex* dq5::level::PartytalkEndingIndex::getRecord(int index)
{
    return (PartytalkEndingIndex*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::PartytalkSeinenIndex* dq5::level::PartytalkSeinenIndex::getRecord(int index)
{
    return (PartytalkSeinenIndex*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::PartytalkSounenIndex* dq5::level::PartytalkSounenIndex::getRecord(int index)
{
    return (PartytalkSounenIndex*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::PartytalkYounenIndex* dq5::level::PartytalkYounenIndex::getRecord(int index)
{
    return (PartytalkYounenIndex*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline cmn::PlayerManager* cmn::GameManager::getPlayerManager()
{
    return playerManager_;
}

inline void cmn::PlayerManager::resetTalkRefresh()
{
    talkRefresh_ = 0;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline bool status::HaveStatus::isNoBattleNpc() const
{
    return playerType_ == TYPE_NOBATTLENPC;
}

inline int status::PlayerData::getKindIndex()
{
    return kindIndex_;
}

inline int status::StageInfo::getReturnBookFlag()
{
    return returnBookFlag_;
}

inline void status::StageInfo::setReturnBookFlag(bool flag)
{
    returnBookFlag_ = flag;
}

inline void status::BattleResult::setDemolitionPartyTalk(bool flag)
{
    demolitionPartyTalk_ = flag;
}

inline int status::BattleResult::isDemolitionPartyTalk()
{
    return demolitionPartyTalk_;
}

inline dq5::level::PartytalkYounen* dq5::level::PartytalkYounen::getRecord(int index)
{
    return (PartytalkYounen*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::PartytalkSeinen* dq5::level::PartytalkSeinen::getRecord(int index)
{
    return (PartytalkSeinen*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::PartytalkSounen* dq5::level::PartytalkSounen::getRecord(int index)
{
    return (PartytalkSounen*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::PartytalkEnding* dq5::level::PartytalkEnding::getRecord(int index)
{
    return (PartytalkEnding*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::PartytalkMonster* dq5::level::PartytalkMonster::getRecord(int index)
{
    return (PartytalkMonster*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::PartytalkYounenIndex::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::PartytalkSeinenIndex::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::PartytalkSounenIndex::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned int dq5::level::PartytalkEndingIndex::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned long dq5::level::PartytalkYounenIndex::getFloor()
{
    return floor;
}

inline unsigned long dq5::level::PartytalkYounenIndex::getOffset()
{
    return offset;
}

inline unsigned short dq5::level::PartytalkYounenIndex::getSize()
{
    return size;
}

inline unsigned long dq5::level::PartytalkYounen::getPreMessage()
{
    return preMessage;
}

inline unsigned long dq5::level::PartytalkYounen::getMessage()
{
    return message;
}

inline unsigned long dq5::level::PartytalkYounen::getValue1()
{
    return value1;
}

inline unsigned long dq5::level::PartytalkYounen::getValue2()
{
    return value2;
}

inline unsigned long dq5::level::PartytalkYounen::getValue4()
{
    return value4;
}

inline unsigned long dq5::level::PartytalkYounen::getFormat()
{
    return format;
}

inline unsigned short dq5::level::PartytalkYounen::getStart()
{
    return start;
}

inline unsigned short dq5::level::PartytalkYounen::getEnd()
{
    return end;
}

inline char dq5::level::PartytalkYounen::getTimezone()
{
    return timezone;
}

inline char dq5::level::PartytalkYounen::getPriority()
{
    return priority;
}

inline char dq5::level::PartytalkYounen::getCondition1()
{
    return condition1;
}

inline char dq5::level::PartytalkYounen::getCondition2()
{
    return condition2;
}

inline char dq5::level::PartytalkYounen::getAlivePC()
{
    return alivePC;
}

inline char dq5::level::PartytalkYounen::getConduct()
{
    return conduct;
}

inline char dq5::level::PartytalkYounen::getDelete()
{
    return byte_1 & 1;
}

inline unsigned long dq5::level::PartytalkMonster::getMessage()
{
    return message;
}

inline char dq5::level::PartytalkMonster::getAlivePC()
{
    return alivePC;
}

inline char dq5::level::PartytalkMonster::getConduct()
{
    return conduct;
}

THUMB cmn::PartyTalk& cmn::PartyTalk::getSingleton()
{
    static PartyTalk singleton_;
    return singleton_;
}

THUMB void cmn::PartyTalk::initialize()
{
    for (int i = 0; i < PIC_MESSAGE_COUNT_MAX; i++) {
        for (int j = 0; j < MESSAGE_COUNT_MAX; j++) {
            partyTalk_[i].mesSoundIndex_[j] = 0x30;
        }
        for (int j = 0; j < MESSAGE_COUNT_MAX; j++) {
            partyTalk_[i].message_[j] = 0;
        }
        for (int j = 0; j < YES_NO_COUNT; j++) {
            partyTalk_[i].yesnoCount_[j] = 0;
        }
        partyTalk_[i].record_ = 0;
        partyTalk_[i].talkMonster_ = 0;
        partyTalk_[i].mesCount_ = 0;
        partyTalk_[i].messageType_ = TYPE_NORMAL;
    }
    for (int i = 0; i < SAVE_MESSAGE_COUNT_MAX; i++) {
        saveMessage_[i] = 0;
    }
    for (int i = 0; i < ADD_PLAYER_COUNT_MAX; i++) {
        player_[i] = 0;
    }
    partyTalkNo_ = 0;
    mesCount_ = 0;
    saveMessageCount_ = 0;
    floor_ = 0;
    noChangeObjectLimitCount_ = 0;
    prevItem_ = 0;
    saveMessageFlag_ = 0;
    findPriorityMessage_ = 0;
    size_ = 0;
    preMessage_ = 0;
    chapter_ = 0;
    useItem_ = 0;
    treasureUid_ = 0;
    addPlayerCount_ = 0;
}

THUMB void cmn::PartyTalk::setPartyTalkMessage()
{
    status::g_Party.setDisplayMode();
    for (int i = 0; i < PIC_MESSAGE_COUNT_MAX; i++) {
        for (int j = 0; j < MESSAGE_COUNT_MAX; j++) {
            partyTalk_[i].mesSoundIndex_[j] = 0x30;
        }
        for (int j = 0; j < MESSAGE_COUNT_MAX; j++) {
            partyTalk_[i].message_[j] = 0;
        }
        for (int j = 0; j < YES_NO_COUNT; j++) {
            partyTalk_[i].yesnoCount_[j] = 0;
        }
        partyTalk_[i].record_ = 0;
        partyTalk_[i].talkMonster_ = 0;
        partyTalk_[i].mesCount_ = 0;
        partyTalk_[i].messageType_ = TYPE_NORMAL;
    }
    partyTalkNo_ = 0;
    mesCount_ = 0;
    saveMessageFlag_ = 0;
    findPriorityMessage_ = 0;
    size_ = 0;
    chapter_ = status::g_Story.getChapter();
    carriageOutCount_ = status::g_Party.getCarriageOutCount();
    floor_ = g_Global.getMapNameId();
    if (floor_ == 999) {
        switch (g_Global.getFieldType()) {
            case 0:
                floor_ = 0x385;
                break;
            case 1:
                floor_ = 0x387;
                break;
            case 2:
                floor_ = 0x386;
                break;
            case 3:
                floor_ = 0x388;
                break;
        }
    }
    int heroIndex = status::g_Party.getSortIndex(1);
    if (heroIndex == -1) {
        partyTalk_[0].message_[0] = 0xc428a;
        partyTalk_[0].mesCount_ = 1;
        return;
    }
    if (status::g_Party.getPlayerStatus(heroIndex).getHaveStatusInfo().isDeath() == true) {
        partyTalk_[0].message_[0] = 0xc428a;
        partyTalk_[0].mesCount_ = 1;
        return;
    }
    int aliveCount = 0;
    for (int i = 0; i < carriageOutCount_; i++) {
        status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
        if (statusInfo.isDeath() == false || statusInfo.getHaveStatus().isNoBattleNpc()) {
            aliveCount++;
        }
    }
    if (aliveCount <= 1) {
        partyTalk_[0].message_[0] = 0xc4288;
        partyTalk_[0].mesCount_ = 1;
        return;
    }
    if (g_Global.getNowAreaNo() == 0x5d) {
        chapter_ = dq5::CHAPTER_SEINENKI;
    }
    switch (chapter_) {
        case dq5::CHAPTER_YOUNENKI:
            dq5::level::PartytalkYounen::setup();
            dq5::level::PartytalkYounenIndex::setup();
            size_ = dq5::level::PartytalkYounenIndex::getArraySize();
            break;
        case dq5::CHAPTER_SEINENKI:
            dq5::level::PartytalkSeinen::setup();
            dq5::level::PartytalkSeinenIndex::setup();
            size_ = dq5::level::PartytalkSeinenIndex::getArraySize();
            break;
        case dq5::CHAPTER_SOUNENKI:
            dq5::level::PartytalkSounen::setup();
            dq5::level::PartytalkSounenIndex::setup();
            size_ = dq5::level::PartytalkSounenIndex::getArraySize();
            break;
        case dq5::CHAPTER_ENDING:
            dq5::level::PartytalkEnding::setup();
            dq5::level::PartytalkEndingIndex::setup();
            size_ = dq5::level::PartytalkEndingIndex::getArraySize();
            break;
    }
    getPartyTalk();
    if (mesCount_ != 0) {
        partyTalkNo_ = UnkDssRand::rand(mesCount_);
        if (saveMessageFlag_ == 1) {
            saveMessageUpdate();
            noChangeObjectLimitCount_++;
            dq5::level::PartytalkYounen* talk = getPartytalkRecord(partyTalk_[partyTalkNo_].record_);
            setPartyTalkFlag(talk->getConduct(), talk->getValue4());
        }
    }
    switch (chapter_) {
        case dq5::CHAPTER_YOUNENKI:
            dq5::level::PartytalkYounen::cleanup();
            dq5::level::PartytalkYounenIndex::cleanup();
            break;
        case dq5::CHAPTER_SEINENKI:
            dq5::level::PartytalkSeinen::cleanup();
            dq5::level::PartytalkSeinenIndex::cleanup();
            break;
        case dq5::CHAPTER_SOUNENKI:
            dq5::level::PartytalkSounen::cleanup();
            dq5::level::PartytalkSounenIndex::cleanup();
            break;
        case dq5::CHAPTER_ENDING:
            dq5::level::PartytalkEnding::cleanup();
            dq5::level::PartytalkEndingIndex::cleanup();
            break;
    }
}

THUMB void cmn::PartyTalk::resetPartyTalk()
{
    preMessage_ = 0;
    noChangeObjectLimitCount_ = 0;
    prevItem_ = 0;
    useItem_ = 0;
    treasureUid_ = 0;
    intoFloor_ = 0;
    for (int i = 0; i < ADD_PLAYER_COUNT_MAX; i++) {
        player_[i] = 0;
    }
    addPlayerCount_ = 0;
    GameManager::getSingleton().getPlayerManager()->resetTalkRefresh();
}

THUMB void cmn::PartyTalk::resetWalkPartyTalk()
{
    preMessage_ = 0;
    noChangeObjectLimitCount_ = 0;
    intoFloor_ = 0;
    for (int i = 0; i < ADD_PLAYER_COUNT_MAX; i++) {
        player_[i] = 0;
    }
    addPlayerCount_ = 0;
}

THUMB void cmn::PartyTalk::setExitNo(int exitNo)
{
    if (status::g_StageInfo.getReturnBookFlag() == 1) {
        status::g_StageInfo.setReturnBookFlag(false);
        return;
    }
    lastExit_ = exitNo;
    prevItem_ = 0;
    useItem_ = 0;
    treasureUid_ = 0;
    noChangeObjectLimitCount_ = 0;
    intoFloor_ = 1;
    for (int i = 0; i < ADD_PLAYER_COUNT_MAX; i++) {
        player_[i] = 0;
    }
    addPlayerCount_ = 0;
    status::g_BattleResult.setDemolitionPartyTalk(false);
}

THUMB void cmn::PartyTalk::setPreItem(int itemID)
{
    prevItem_ = itemID;
}

THUMB void cmn::PartyTalk::setUseItem(int itemID)
{
    useItem_ = itemID;
}

THUMB void cmn::PartyTalk::setTreasureUid(int uid)
{
    treasureUid_ = uid;
}

THUMB void cmn::PartyTalk::setAddPlayer(int playerIndex)
{
    if (addPlayerCount_ != ADD_PLAYER_COUNT_MAX) {
        player_[addPlayerCount_] = playerIndex;
        addPlayerCount_++;
    }
}

THUMB void cmn::PartyTalk::getPartyTalk()
{
    TIME_ZONE timeZone = TIME_ZONE_DAYTIME;
    if (status::g_StageInfo.getDayNight() == dq5::DAY_NIGHT_NIGHT) {
        timeZone = TIME_ZONE_NIGHT;
    }
    int priority = 0;
    int start = 0;
    int end = 0;
    getFloorPartyTalkRecord(start, end);
    for (; priority < 10 && findPriorityMessage_ == 0; priority++) {
        for (int i = start; i < end; i++) {
            dq5::level::PartytalkYounen* partyTalk = getPartytalkRecord(i);
            if (partyTalk->getDelete() == 1) {
                continue;
            }
            if (priority != partyTalk->getPriority()) {
                continue;
            }
            if (partyTalk->getStart() != 0 && g_AreaFlag.check(partyTalk->getStart()) == false) {
                continue;
            }
            if (partyTalk->getEnd() != 0 && g_AreaFlag.check(partyTalk->getEnd()) == true) {
                continue;
            }
            if (partyTalk->getTimezone() != 0 && timeZone != partyTalk->getTimezone()) {
                continue;
            }
            if (partyTalk->getPreMessage() != 0 && preMessage_ != partyTalk->getPreMessage()) {
                continue;
            }
            if (partyTalk->getCondition1() != 0) {
                if (checkCondition(partyTalk->getCondition1(), partyTalk->getValue1()) == false) {
                    continue;
                }
                if (partyTalk->getCondition2() != 0) {
                    if (checkCondition(partyTalk->getCondition2(), partyTalk->getValue2()) == false) {
                        continue;
                    }
                }
            }
            if (partyTalk->getAlivePC() != 0) {
                int alivePC = getPlayerIndex(partyTalk->getAlivePC());
                int carriageOutChara = false;
                for (int j = 0; j < carriageOutCount_; j++) {
                    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(j).getHaveStatusInfo();
                    int index = statusInfo.getPlayerIndex();
                    if (statusInfo.getHaveStatus().isNoBattleNpc()) {
                        index = status::g_Party.getNpcPlayerIndex();
                    }
                    if (index == alivePC) {
                        if (statusInfo.isDeath() == false || statusInfo.getHaveStatus().isNoBattleNpc()) {
                            carriageOutChara = true;
                            break;
                        }
                    }
                }
                if (carriageOutChara == false) {
                    continue;
                }
            }
            if (partyTalk->getMessage() != 0) {
                setPickMessage(partyTalk->getMessage(), i);
                if (mesCount_ == PIC_MESSAGE_COUNT_MAX) {
                    priority = 10;
                    break;
                }
            }
        }
    }
    if (mesCount_ != 0) {
        return;
    }

    int count = 0;
    char partyMonster[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++) {
        partyMonster[i] = 0;
    }
    partyTalk_[0].mesCount_ = 1;
    for (int i = 0; i < carriageOutCount_; i++) {
        status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
        if (statusInfo.getHaveStatus().isFriendMonster() && statusInfo.isDeath() == false) {
            partyMonster[count] = statusInfo.getHaveStatus().getPlayerKindIndex();
            count++;
        }
    }
    if (status::g_Party.getNpcPlayerIndex() == 0x10 && g_AreaFlag.check(0x35f) == true) {
        partyMonster[count] = 0x10;
        count++;
    }
    if (count == 0) {
        if (status::g_Party.isCarriageEnableOnGame() == true) {
            partyTalk_[0].message_[0] = 0xc428d;
            partyTalk_[0].mesSoundIndex_[0] = 0x32;
            return;
        }
        partyTalk_[0].message_[0] = 0xc4292;
        return;
    }
    int talkActor = UnkDssRand::rand(count + 1);
    if (talkActor == count) {
        if (status::g_Party.isCarriageEnableOnGame() == true) {
            partyTalk_[0].message_[0] = 0xc428d;
            partyTalk_[0].mesSoundIndex_[0] = 0x32;
            return;
        }
        for (int i = 0; i < carriageOutCount_; i++) {
            status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
            if (statusInfo.getPlayerIndex() != 1 && !statusInfo.getHaveStatus().isFriendMonster() && statusInfo.isDeath() == false) {
                partyTalk_[0].message_[0] = 0xc4292;
                return;
            }
        }
    }
    int randActor = UnkDssRand::rand(count);
    dq5::level::PartytalkMonster::setup();
    int actor = partyMonster[randActor];
    int mesOffset = 0;
    if (status::g_StageAttribute.isEncount() == false) {
        mesOffset = 0x46;
    }
    int record = actor + mesOffset - 0x10;
    int monsterIndex;
    dq5::level::PartytalkMonster* data;
    if (actor == 0x56) {
        monsterIndex = 0x56;
        if (mesOffset == 0x46) {
            data = dq5::level::PartytalkMonster::getRecord(0x8e);
        } else {
            data = dq5::level::PartytalkMonster::getRecord(0x8c);
        }
    } else if (actor == 0x57) {
        monsterIndex = 0x57;
        if (mesOffset == 0x46) {
            data = dq5::level::PartytalkMonster::getRecord(0x8f);
        } else {
            data = dq5::level::PartytalkMonster::getRecord(0x8d);
        }
    } else {
        data = dq5::level::PartytalkMonster::getRecord(record);
        monsterIndex = data->getAlivePC();
    }
    partyTalk_[0].message_[0] = data->getMessage();
    int temp[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        temp[i] = 0;
    }
    int tempCount = 0;
    for (int i = 0; i < carriageOutCount_; i++) {
        status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
        if (statusInfo.getHaveStatus().isFriendMonster() && statusInfo.isDeath() == false) {
            int index = statusInfo.getPlayerIndex();
            if (monsterIndex == status::PlayerDataAll::playerData_[index].getKindIndex()) {
                temp[tempCount] = index;
                tempCount++;
            }
        }
    }
    if (tempCount <= 1) {
        partyTalk_[0].talkMonster_ = temp[0];
    } else {
        partyTalk_[0].talkMonster_ = temp[UnkDssRand::rand(tempCount)];
    }
    int sound = 0x30;
    switch (data->getConduct()) {
        case 19:
            sound = 0x33;
            break;
        case 20:
            sound = 0x32;
            break;
        case 21:
            sound = 0x31;
            break;
    }
    partyTalk_[0].mesSoundIndex_[0] = sound;
    dq5::level::PartytalkMonster::cleanup();
}

THUMB dq5::level::PartytalkYounen* cmn::PartyTalk::getPartytalkRecord(int index)
{
    dq5::level::PartytalkYounen* partyTalk = NULL;
    switch (chapter_) {
        case dq5::CHAPTER_YOUNENKI:
            partyTalk = dq5::level::PartytalkYounen::getRecord(index);
            break;
        case dq5::CHAPTER_SEINENKI:
            partyTalk = (dq5::level::PartytalkYounen*)dq5::level::PartytalkSeinen::getRecord(index);
            break;
        case dq5::CHAPTER_SOUNENKI:
            partyTalk = (dq5::level::PartytalkYounen*)dq5::level::PartytalkSounen::getRecord(index);
            break;
        case dq5::CHAPTER_ENDING:
            partyTalk = (dq5::level::PartytalkYounen*)dq5::level::PartytalkEnding::getRecord(index);
            break;
    }
    return partyTalk;
}

THUMB dq5::level::PartytalkYounenIndex* cmn::PartyTalk::getPartytalkRecordIndex(int index)
{
    dq5::level::PartytalkYounenIndex* partyTalk = NULL;
    switch (chapter_) {
        case dq5::CHAPTER_YOUNENKI:
            partyTalk = dq5::level::PartytalkYounenIndex::getRecord(index);
            break;
        case dq5::CHAPTER_SEINENKI:
            partyTalk = (dq5::level::PartytalkYounenIndex*)dq5::level::PartytalkSeinenIndex::getRecord(index);
            break;
        case dq5::CHAPTER_SOUNENKI:
            partyTalk = (dq5::level::PartytalkYounenIndex*)dq5::level::PartytalkSounenIndex::getRecord(index);
            break;
        case dq5::CHAPTER_ENDING:
            partyTalk = (dq5::level::PartytalkYounenIndex*)dq5::level::PartytalkEndingIndex::getRecord(index);
            break;
    }
    return partyTalk;
}

THUMB int cmn::PartyTalk::checkCondition(int condition, int value)
{
    int ret = false;
    switch (condition) {
        case 1:
            if (g_AreaFlag.check(value) == true) {
                ret = true;
            }
            break;
        case 2:
            if (g_AreaFlag.check(value) == false) {
                ret = true;
            }
            break;
        case 3:
            if (g_LocalFlag.check(value) == true) {
                ret = true;
            }
            break;
        case 4:
            if (g_LocalFlag.check(value) == false) {
                ret = true;
            }
            break;
        case 5:
            if (g_GlobalFlag.check(value) == true) {
                ret = true;
            }
            break;
        case 6:
            if (g_GlobalFlag.check(value) == false) {
                ret = true;
            }
            break;
        case 7:
            if (checkHaveItem(value) == false) {
                ret = true;
            }
            break;
        case 8:
            ret = checkHaveItem(value);
            break;
        case 9:
            if (prevItem_ == value) {
                ret = true;
            }
            break;
        case 10: {
            int index = status::g_Party.getSortIndex(getPlayerIndex(value));
            if (index != -1 && index < status::g_Party.getCarriageOutCount() && status::g_Party.getPlayerStatus(index).getHaveStatusInfo().isDeath() == false) {
                ret = true;
            }
            break;
        }
        case 11:
            if (status::g_Party.getSortIndex(getPlayerIndex(value)) == 0) {
                ret = true;
            }
            break;
        case 12:
            if (value == 0x10 && chapter_ > dq5::CHAPTER_YOUNENKI) {
                value = 0x11;
            }
            ret = false;
            for (int i = 0; i < ADD_PLAYER_COUNT_MAX; i++) {
                if (value == player_[i]) {
                    ret = true;
                }
            }
            break;
        case 14:
            if (intoFloor_ == 1) {
                ret = true;
            }
            break;
        case 15:
            if (treasureUid_ == value) {
                ret = true;
            }
            break;
        case 16:
            ret = status::g_BattleResult.isDemolitionPartyTalk();
            break;
        case 19: {
            char buf[25];
            char name[25] = "\x83\x70\x83\x93\x83\x63";
            convertSjisToUtf8(buf, 25, name);
            if (dss::strcmp(status::PlayerDataAll::playerData_[13].name_, buf) != 0) {
                ret = true;
            }
            break;
        }
        case 20:
            if (checkHaveItem(0xd8) == true || checkHaveItem(0xd9) == true || checkHaveItem(0xda) == true) {
                ret = true;
            }
            break;
        case 21: {
            int museumLevel = status::g_MuseumStatus.getMuseumLevel();
            if (museumLevel == 5) {
                switch (status::g_MuseumStatus.getMuseumTrend()) {
                    case status::MUSEUMTREND_BEAUTIFUL:
                        museumLevel = 5;
                        break;
                    case status::MUSEUMTREND_FUNNY:
                        museumLevel = 6;
                        break;
                    case status::MUSEUMTREND_FEAR:
                        museumLevel = 7;
                        break;
                }
            }
            if (value / 1000000 == museumLevel) {
                ret = true;
            }
            if (value % 1000000 / 100000 == museumLevel) {
                ret = true;
            }
            if (value % 100000 / 10000 == museumLevel) {
                ret = true;
            }
            if (value % 10000 / 1000 == museumLevel) {
                ret = true;
            }
            if (value % 1000 / 100 == museumLevel) {
                ret = true;
            }
            if (value % 100 / 10 == museumLevel) {
                ret = true;
            }
            if (value % 10 == museumLevel) {
                ret = true;
            }
        }
        case 22: {
            status::g_Party.setBattleModeAndCarriage();
            int partyCount = status::g_Party.getCount();
            for (int i = 0; i < partyCount; i++) {
                if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().isFriendMonster()) {
                    ret = true;
                    break;
                }
            }
            status::g_Party.setDisplayMode();
            break;
        }
        case 23:
            if (useItem_ == value) {
                ret = true;
            }
            break;
        case 24: {
            int son = ret;
            int daughter = ret;
            checkNameGorosute(son, daughter);
            if (son == false && daughter == false) {
                ret = true;
            }
            break;
        }
        case 25:
            if (lastExit_ == value) {
                ret = true;
            }
            break;
        case 26:
            ret = status::g_StageAttribute.isEncount();
            break;
        case 27:
            if (status::g_StageAttribute.isEncount() == false) {
                ret = true;
            }
            break;
        case 28: {
            int index = status::g_Party.getSortIndex(getPlayerIndex(value));
            if (index == -1 || index >= status::g_Party.getCarriageOutCount()) {
                ret = true;
            } else if (status::g_Party.getPlayerStatus(index).getHaveStatusInfo().isDeath() == true) {
                ret = true;
            }
            break;
        }
        case 29: {
            int sonIndex = status::g_Party.getSortIndex(13);
            int daughterIndex = status::g_Party.getSortIndex(14);
            if (sonIndex != -1 && daughterIndex != -1
                && status::g_Party.getPlayerStatus(sonIndex).getHaveStatusInfo().isDeath() == false
                && status::g_Party.getPlayerStatus(daughterIndex).getHaveStatusInfo().isDeath() == false) {
                ret = true;
            }
            break;
        }
    }
    return ret;
}

THUMB int cmn::PartyTalk::getPlayerIndex(int character)
{
    switch (character) {
        case 1:
            return 2;
        case 2:
            if (chapter_ == dq5::CHAPTER_YOUNENKI) {
                return 3;
            }
            return 4;
        case 3:
            return 5;
        case 4:
            if (chapter_ == dq5::CHAPTER_YOUNENKI) {
                return 6;
            }
            return 7;
        case 5:
            return 8;
        case 6:
            return 9;
        case 7:
            return 10;
        case 8:
            return 11;
        case 9:
            return 12;
        case 10:
            return 15;
        case 12:
            if (g_AreaFlag.check(0xeb) == true) {
                return 4;
            }
            if (g_AreaFlag.check(0xec) == true) {
                return 9;
            }
            return 10;
        case 13:
            return 13;
        case 14:
            return 14;
    }
    if (character == 0x10 && chapter_ > dq5::CHAPTER_YOUNENKI) {
        character = 0x11;
    }
    return status::PlayerDataAll::getCtrlFromFriendMonsterIndex(character);
}

THUMB bool cmn::PartyTalk::checkHaveItem(int itemID)
{
    status::g_Party.setBattleModeAndCarriage();
    bool ret = false;
    int playerCount = status::g_Party.getCount();
    for (int j = 0; j < playerCount; j++) {
        if (status::g_Party.getPlayerStatus(j).getHaveStatusInfo().getHaveItem().isItem(itemID)) {
            ret = true;
            break;
        }
    }
    if (ret == false) {
        ret = status::g_Party.haveItemSack_.isItem(itemID);
    }
    status::g_Party.setDisplayMode();
    return ret;
}

THUMB void cmn::PartyTalk::setPickMessage(int message, int record)
{
    if (noChangeObjectLimitCount_ == PRE_MESSAGE_COUNT_MAX) {
        return;
    }
    for (int j = 0; j < saveMessageCount_; j++) {
        if (message == saveMessage_[j]) {
            return;
        }
    }
    dq5::level::PartytalkYounen* partyTalk = getPartytalkRecord(record);
    int addMesCount = 0;
    int format = partyTalk->getFormat();
    int value = partyTalk->getValue4();
    switch (partyTalk->getConduct()) {
        case 10:
            if (g_AreaFlag.check(value) == true) {
                addMesCount = format % 10;
            }
            break;
        case 11:
            if (g_AreaFlag.check(value) == false) {
                addMesCount = format % 10;
            }
            break;
        case 12:
            if (checkHaveItem(value) == true) {
                addMesCount = format % 10;
            }
            break;
        case 13:
            if (checkHaveItem(value) == false) {
                addMesCount = format % 10;
            }
            break;
        case 14: {
            int index = status::g_Party.getSortIndex(getPlayerIndex(value));
            if (index < carriageOutCount_ && index != -1 && status::g_Party.getPlayerStatus(index).getHaveStatusInfo().isDeath() == false) {
                addMesCount = format % 10;
            }
            break;
        }
        case 15:
            for (int i = 0; i < carriageOutCount_; i++) {
                if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().isFriendMonster()) {
                    addMesCount = format % 10;
                    break;
                }
            }
            break;
        case 16: {
            int son = status::g_Party.getSortIndex(13);
            int daughter = status::g_Party.getSortIndex(14);
            if ((son != -1 && son < carriageOutCount_) || (daughter != -1 && daughter < carriageOutCount_)) {
                addMesCount = format % 10;
            }
            break;
        }
        case 17: {
            int son = addMesCount;
            int daughter = addMesCount;
            checkNameGorosute(son, daughter);
            if (son == true || daughter == true) {
                addMesCount = format % 10;
            }
            break;
        }
    }
    setMessage(partyTalk, addMesCount);
    int checkFormat1 = format / 10000;
    int checkFormat2 = format % 10000 / 1000;
    if (checkFormat1 != 0) {
        if (checkFormat1 == 9) {
            partyTalk_[mesCount_].mesSoundIndex_[6] = 0x31;
        } else {
            partyTalk_[mesCount_].mesSoundIndex_[checkFormat1 - 1] = 0x30;
        }
    }
    if (checkFormat2 != 0) {
        char addPC = status::g_Party.getSortIndex(getPlayerIndex(partyTalk->getValue4()));
        if (addPC == -1) {
            partyTalk_[mesCount_].record_ = record;
            mesCount_++;
            saveMessageFlag_ = 1;
            findPriorityMessage_ = 1;
            return;
        }
        int sound = g_talkSound.getPlayerVoice(status::g_Party.getPlayerStatus(addPC).getHaveStatusInfo().getCharaIndex());
        switch (checkFormat2) {
            case 1:
            case 2:
            case 3:
                partyTalk_[mesCount_].mesSoundIndex_[checkFormat2] = sound;
                break;
            case 4:
                if (addPC == 1) {
                    char count = partyTalk_[mesCount_].mesCount_ - 1;
                    for (int i = 1; i < count; i++) {
                        partyTalk_[mesCount_].message_[i] = partyTalk_[mesCount_].message_[i + 1];
                    }
                    partyTalk_[mesCount_].mesCount_ = count;
                } else {
                    partyTalk_[mesCount_].mesSoundIndex_[4] = sound;
                }
                break;
            case 5:
                partyTalk_[mesCount_].mesSoundIndex_[1] = sound;
                partyTalk_[mesCount_].mesSoundIndex_[3] = sound;
                break;
            case 6: {
                char count = partyTalk_[mesCount_].mesCount_ - 1;
                for (int i = 1; i < count; i++) {
                    partyTalk_[mesCount_].message_[i] = partyTalk_[mesCount_].message_[i + 1];
                }
                partyTalk_[mesCount_].mesCount_ = count;
                partyTalk_[mesCount_].mesSoundIndex_[1] = sound;
                break;
            }
            case 7:
                partyTalk_[mesCount_].mesSoundIndex_[1] = sound;
                partyTalk_[mesCount_].mesSoundIndex_[2] = sound;
                break;
            case 8:
                partyTalk_[mesCount_].mesSoundIndex_[2] = sound;
                partyTalk_[mesCount_].mesSoundIndex_[4] = sound;
                break;
            case 9:
                partyTalk_[mesCount_].mesSoundIndex_[2] = sound;
                partyTalk_[mesCount_].mesSoundIndex_[3] = sound;
                break;
        }
    }
    partyTalk_[mesCount_].record_ = record;
    mesCount_++;
    saveMessageFlag_ = 1;
    findPriorityMessage_ = 1;
}

THUMB void cmn::PartyTalk::setMessage(dq5::level::PartytalkYounen* talk, int addCount)
{
    int format = (int)talk->getFormat() % 1000;
    int messageNo = talk->getMessage();
    int playerIndex = getPlayerIndex(talk->getAlivePC());
    int index = format % 100;
    int count = index / 10;
    if (talk->getConduct() == 9 || talk->getConduct() == 22) {
        int defaultCount = format / 100;
        int yesCount = index / 10;
        int noCount = index % 10;
        partyTalk_[mesCount_].mesCount_ += defaultCount;
        partyTalk_[mesCount_].yesnoCount_[0] = defaultCount;
        for (int i = 0; i < defaultCount; i++) {
            partyTalk_[mesCount_].message_[i] = messageNo + i;
        }
        messageNo += defaultCount;
        partyTalk_[mesCount_].mesCount_ += yesCount;
        partyTalk_[mesCount_].yesnoCount_[1] = yesCount;
        for (int i = 0; i < yesCount; i++) {
            partyTalk_[mesCount_].message_[defaultCount + i] = messageNo + i;
        }
        messageNo += yesCount;
        partyTalk_[mesCount_].mesCount_ += noCount;
        partyTalk_[mesCount_].yesnoCount_[2] = noCount;
        for (int i = 0; i < noCount; i++) {
            partyTalk_[mesCount_].message_[defaultCount + yesCount + i] = messageNo + i;
        }
        partyTalk_[mesCount_].messageType_ = TYPE_YESNO;
    } else {
        for (int i = 0; i < count; i++) {
            partyTalk_[mesCount_].message_[i] = messageNo + i;
        }
        if (count == 0) {
            addCount = index % 10;
        }
        for (int i = 0; i < addCount; i++) {
            partyTalk_[mesCount_].message_[count + i] = messageNo + count + i;
        }
        partyTalk_[mesCount_].mesCount_ = count + addCount;
    }
    if (talk->getConduct() == 18) {
        partyTalk_[mesCount_].messageType_ = TYPE_SHAKE;
    }
    int sortIndex;
    if (playerIndex == 0xf) {
        sortIndex = status::g_Party.getSortIndex(1);
    } else if (playerIndex == status::g_Party.getNpcPlayerIndex()) {
        sortIndex = status::g_Party.getSortIndex(8);
    } else {
        sortIndex = status::g_Party.getSortIndex(playerIndex);
    }
    int charaIndex = status::g_Party.getPlayerStatus(sortIndex).getHaveStatusInfo().getCharaIndex();
    for (int i = 0; i < partyTalk_[mesCount_].mesCount_; i++) {
        partyTalk_[mesCount_].mesSoundIndex_[i] = g_talkSound.getPlayerVoice(charaIndex);
    }
}

THUMB void cmn::PartyTalk::setPartyTalkFlag(int conduct, unsigned int value)
{
    switch (conduct) {
        case 1:
            g_AreaFlag.set(value);
            break;
        case 2:
            g_AreaFlag.remove(value);
            break;
        case 3:
            g_LocalFlag.set(value);
            break;
        case 4:
            g_LocalFlag.remove(value);
            break;
        case 5:
            g_GlobalFlag.set(value);
            break;
        case 6:
            g_GlobalFlag.remove(value);
            break;
    }
}

THUMB void cmn::PartyTalk::saveMessageUpdate()
{
    if (saveMessageCount_ == SAVE_MESSAGE_COUNT_MAX) {
        for (int i = 0; i < SAVE_MESSAGE_COUNT_MAX - 1; i++) {
            saveMessage_[i] = saveMessage_[i + 1];
        }
        saveMessage_[saveMessageCount_ - 1] = partyTalk_[partyTalkNo_].message_[0];
    } else {
        saveMessage_[saveMessageCount_] = partyTalk_[partyTalkNo_].message_[0];
        saveMessageCount_++;
    }
}

THUMB void cmn::PartyTalk::setPreMessageNo(int mesNo)
{
    preMessage_ = mesNo;
    noChangeObjectLimitCount_ = 0;
}

THUMB void cmn::PartyTalk::getFloorPartyTalkRecord(int& start, int& end)
{
    for (int i = 0; i < size_; i++) {
        dq5::level::PartytalkYounenIndex* partyTalk = getPartytalkRecordIndex(i);
        if (floor_ == partyTalk->getFloor()) {
            start = partyTalk->getOffset();
            end = start + partyTalk->getSize();
            return;
        }
    }
}

THUMB void cmn::PartyTalk::checkNameGorosute(int& son, int& daughter)
{
    char buf1[25];
    char buf2[25];
    char name1[25] = "\x83\x53\x83\x8d\x83\x58\x83\x65";
    char name2[25] = "\x82\xb2\x82\xeb\x82\xb7\x82\xc4";
    convertSjisToUtf8(buf1, 25, name1);
    convertSjisToUtf8(buf2, 25, name2);
    if (dss::strcmp(status::PlayerDataAll::playerData_[13].name_, buf1) == 0 || dss::strcmp(status::PlayerDataAll::playerData_[13].name_, buf2) == 0) {
        son = true;
    }
    if (dss::strcmp(status::PlayerDataAll::playerData_[14].name_, buf1) == 0 || dss::strcmp(status::PlayerDataAll::playerData_[14].name_, buf2) == 0) {
        daughter = true;
    }
}
