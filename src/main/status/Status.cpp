#include "main/status/Status.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/HaveBattleStatus.hpp"
#include "main/status/UseItem.hpp"
#include "main/status/BaseItem.hpp"
#include "main/status/ShopList.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/OptionStatus.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/GameStatus.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/TouchData.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/cmn/CommonCounterInfo.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/leveldata/EventList.hpp"
#include "main/leveldata/EventFlag.hpp"
#include "main/leveldata/FukuroWeapon.hpp"
#include "main/leveldata/FukuroArmor.hpp"
#include "main/leveldata/FukuroItem.hpp"
#include "main/dss/DssUtils.hpp"

inline status::HaveAction& status::HaveStatusInfo::getHaveAction()
{
    return haveAction_;
}

inline void status::ShopList::setSection(int section)
{
    section_ = section;
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::level::FukuroArmor* dq5::level::FukuroArmor::getRecord(int index)
{
    return (FukuroArmor*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::FukuroItem* dq5::level::FukuroItem::getRecord(int index)
{
    return (FukuroItem*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::FukuroWeapon* dq5::level::FukuroWeapon::getRecord(int index)
{
    return (FukuroWeapon*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::EventList* dq5::level::EventList::getRecord(int index)
{
    return (EventList*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::EventList::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned short dq5::level::EventList::getIndex()
{
    return index;
}

inline unsigned short dq5::level::EventList::getGold()
{
    return gold;
}

inline unsigned short dq5::level::EventList::getWeapon()
{
    return weapon;
}

inline unsigned short dq5::level::EventList::getArmor()
{
    return armor;
}

inline unsigned short dq5::level::EventList::getShield()
{
    return shield;
}

inline unsigned short dq5::level::EventList::getHelmet()
{
    return helmet;
}

inline unsigned short dq5::level::EventList::getAccessory()
{
    return accessory;
}

inline unsigned char dq5::level::EventList::getLevel()
{
    return level;
}

inline unsigned char dq5::level::EventList::getCharacter()
{
    return character;
}

inline char* dq5::level::EventList::getFloor()
{
    return floor;
}

inline char dq5::level::EventList::getChapter()
{
    return byte_1 & 0xf;
}

inline dq5::level::EventFlag* dq5::level::EventFlag::getRecord(int index)
{
    return (EventFlag*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned short dq5::level::EventFlag::getFlag1() { return flag1; }
inline unsigned short dq5::level::EventFlag::getFlag2() { return flag2; }
inline unsigned short dq5::level::EventFlag::getFlag3() { return flag3; }
inline unsigned short dq5::level::EventFlag::getFlag4() { return flag4; }
inline unsigned short dq5::level::EventFlag::getFlag5() { return flag5; }
inline unsigned short dq5::level::EventFlag::getFlag6() { return flag6; }
inline unsigned short dq5::level::EventFlag::getFlag7() { return flag7; }
inline unsigned short dq5::level::EventFlag::getFlag8() { return flag8; }
inline unsigned short dq5::level::EventFlag::getFlag9() { return flag9; }
inline unsigned short dq5::level::EventFlag::getFlag10() { return flag10; }
inline unsigned short dq5::level::EventFlag::getFlag11() { return flag11; }
inline unsigned short dq5::level::EventFlag::getFlag12() { return flag12; }
inline unsigned short dq5::level::EventFlag::getWaitFlag1() { return waitFlag1; }
inline unsigned short dq5::level::EventFlag::getWaitFlag2() { return waitFlag2; }
inline unsigned short dq5::level::EventFlag::getWaitFlag3() { return waitFlag3; }
inline unsigned short dq5::level::EventFlag::getWaitFlag4() { return waitFlag4; }
inline unsigned short dq5::level::EventFlag::getWaitFlag5() { return waitFlag5; }
inline unsigned short dq5::level::EventFlag::getWaitFlag6() { return waitFlag6; }
inline unsigned char dq5::level::EventFlag::getNPC() { return NPC; }
inline char dq5::level::EventFlag::getTownFlag1() { return (byte_1 & 0x02) >> 1; }
inline char dq5::level::EventFlag::getTownFlag2() { return (byte_1 & 0x04) >> 2; }
inline char dq5::level::EventFlag::getTownFlag3() { return (byte_1 & 0x08) >> 3; }
inline char dq5::level::EventFlag::getTownFlag4() { return (byte_1 & 0x10) >> 4; }
inline char dq5::level::EventFlag::getTownFlag5() { return (byte_1 & 0x20) >> 5; }
inline char dq5::level::EventFlag::getTownFlag6() { return (byte_1 & 0x40) >> 6; }
inline char dq5::level::EventFlag::getTownFlag7() { return (byte_1 & 0x80) >> 7; }
inline char dq5::level::EventFlag::getTownFlag8() { return byte_2 & 0x01; }
inline char dq5::level::EventFlag::getTownFlag9() { return (byte_2 & 0x02) >> 1; }
inline char dq5::level::EventFlag::getTownFlag10() { return (byte_2 & 0x04) >> 2; }
inline char dq5::level::EventFlag::getTownFlag11() { return (byte_2 & 0x08) >> 3; }
inline char dq5::level::EventFlag::getTownFlag12() { return (byte_2 & 0x10) >> 4; }
inline char dq5::level::EventFlag::getTownFlag13() { return (byte_2 & 0x20) >> 5; }
inline char dq5::level::EventFlag::getTownFlag14() { return (byte_2 & 0x40) >> 6; }
inline char dq5::level::EventFlag::getTownFlag15() { return (byte_2 & 0x80) >> 7; }
inline char dq5::level::EventFlag::getTownFlag16() { return byte_3 & 0x01; }
inline char dq5::level::EventFlag::getTownFlag17() { return (byte_3 & 0x02) >> 1; }
inline char dq5::level::EventFlag::getTownFlag18() { return (byte_3 & 0x04) >> 2; }
inline char dq5::level::EventFlag::getTownFlag19() { return (byte_3 & 0x08) >> 3; }
inline char dq5::level::EventFlag::getTownFlag20() { return byte_1 & 0x01; }

inline unsigned char dq5::level::FukuroWeapon::getItemID() { return itemID; }
inline unsigned char dq5::level::FukuroArmor::getItemID1() { return itemID1; }
inline unsigned char dq5::level::FukuroArmor::getItemID2() { return itemID2; }
inline unsigned char dq5::level::FukuroArmor::getItemID3() { return itemID3; }
inline unsigned char dq5::level::FukuroItem::getItemID1() { return itemID1; }
inline unsigned char dq5::level::FukuroItem::getItemID2() { return itemID2; }
inline unsigned char dq5::level::FukuroItem::getItemID3() { return itemID3; }
inline unsigned char dq5::level::FukuroItem::getItemID4() { return itemID4; }
inline unsigned char dq5::level::FukuroItem::getItemID5() { return itemID5; }
inline unsigned char dq5::level::FukuroItem::getItemID6() { return itemID6; }
inline unsigned char dq5::level::FukuroItem::getItemID7() { return itemID7; }
inline unsigned char dq5::level::FukuroItem::getItemID8() { return itemID8; }
inline unsigned char dq5::level::FukuroItem::getItemID9() { return itemID9; }
inline unsigned char dq5::level::FukuroItem::getItemID10() { return itemID10; }
inline unsigned char dq5::level::FukuroItem::getItemID11() { return itemID11; }
inline unsigned char dq5::level::FukuroItem::getItemID12() { return itemID12; }
inline unsigned char dq5::level::FukuroItem::getItemID13() { return itemID13; }
inline unsigned char dq5::level::FukuroItem::getItemID14() { return itemID14; }
inline unsigned char dq5::level::FukuroItem::getItemID15() { return itemID15; }
inline unsigned char dq5::level::FukuroItem::getItemID16() { return itemID16; }
inline unsigned char dq5::level::FukuroItem::getItemID17() { return itemID17; }

inline void status::HaveAction::setRulaLevel(unsigned char level)
{
    addRulaLevel_ = level;
}

inline void status::HaveAction::setParupunteLevel(unsigned char level)
{
    addParupunteLevel_ = level;
}

inline void status::BasePartyStatus::setCarriage(int flag)
{
    carriage_ = flag;
}

inline void status::BasePartyStatus::setFukuro(bool flag)
{
    fukuro_ = flag;
}

inline void status::HaveStatus::setCommand(CommandType type)
{
    command_ = type;
}

inline void status::HaveStatusInfo::setCommandType(CommandType cmd)
{
    haveStatus_.setCommand(cmd);
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline void status::StageInfo::setShipPosition(int index, dss::Fix32Vector3& pos)
{
    shipPosition_[index] = pos;
}

inline void status::StageInfo::setFieldChange(int ch)
{
    fieldChangeIndex_ = ch;
}

inline void status::StageAttribute::setTimestopFlag(int flag)
{
    timestop_ = flag;
}

inline void cmn::CommonPartyInfo::setRideOn(PARTY_RIDE_ON_TYPE type)
{
    rideOnType_ = type;
}

int status::flagShopIndex = -1;
int status::Status::flagShopInit;

THUMB void status::Status::initialize()
{
    PlayerDataAll::initialize(false);
    g_Party.initialize();
    g_Party.clear();
    g_Party.setFukuro(true);
    UseAction::initialize();
    HaveBattleStatus::initialize();
    UseItem::initialize();
    BaseItem::initialize();
    g_Shop.initialize();
    g_StageAttribute.initialize();
    g_StageInfo.initialize();
    g_Story.initialize();
    cmn::g_CommonCounterInfo.initialize();
    g_BattleResult.initialize();
    g_Option.initialize();
    g_AreaFlag.initialize();
    g_LocalFlag.initialize();
    g_GlobalFlag.initialize();
    g_Game.initialize();
    g_Menu.initialize();
    g_TouchData.cleanUp();
    cmn::PartyTalk::getSingleton().initialize();
    g_MuseumStatus.initialize();
}

THUMB void status::Status::initialize_character()
{
    g_Party.clear();
    setEventParty(0x1c);
    g_Party.setBattleMode();
    g_Party.getCount();
}

THUMB void status::Status::setEventParty(unsigned int index)
{
    dq5::level::EventList* pEvent = 0;
    int recordNum = 0;
    cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_NONE);
    dq5::level::EventList::setup();
    for (int i = 0; i < dq5::level::EventList::getArraySize(); i++) {
        if (index == dq5::level::EventList::getRecord(i)->getIndex()) {
            pEvent = dq5::level::EventList::getRecord(i);
            recordNum = i;
            break;
        }
    }

    g_Party.initialize();
    g_Party.clear();
    if (index >= 0x1d) {
        g_Party.setCarriage(true);
    } else {
        g_Party.setCarriage(false);
    }
    g_Party.setGold(pEvent->getGold());
    g_Party.setFukuro(true);
    g_Party.haveItemSack_.clear();

    int chapter = pEvent->getChapter();
    int i = 0;
    do {
        unsigned char partyIndex = changeIndexForChapter(chapter, pEvent->getCharacter());
        g_Party.add(partyIndex, true);
        i++;
        pEvent = dq5::level::EventList::getRecord(i + recordNum);
    } while (pEvent->getIndex() == 0);

    pEvent = dq5::level::EventList::getRecord(recordNum);
    g_Party.setAllPlayerMode();
    g_Story.setChapter((dq5::CHAPTER_NO)dq5::level::EventList::getRecord(recordNum)->getChapter());
    if (index - 0x14d <= 2) {
        g_Story.setChapter((dq5::CHAPTER_NO)5);
    }
    ShopList::setSection(dq5::level::EventList::getRecord(recordNum)->getChapter() - 1);
    HaveAction::setRulaLevel(0);
    HaveAction::setParupunteLevel(0);

    i = 0;
    do {
        int playerID = dq5::level::EventList::getRecord(i + recordNum)->getCharacter();
        playerID = changeIndexForChapter(chapter, playerID);
        PlayerStatus& eventPlayer = g_Party.getPlayerStatus(i);
        eventPlayer.setup(playerID);
        eventPlayer.levelup(dq5::level::EventList::getRecord(i + recordNum)->getLevel());
        eventPlayer.getHaveStatusInfo().clearAllItem();
        eventPlayer.getHaveStatusInfo().setItemEquipment(dq5::level::EventList::getRecord(i + recordNum)->getWeapon());
        eventPlayer.getHaveStatusInfo().setItemEquipment(dq5::level::EventList::getRecord(i + recordNum)->getArmor());
        eventPlayer.getHaveStatusInfo().setItemEquipment(dq5::level::EventList::getRecord(i + recordNum)->getShield());
        eventPlayer.getHaveStatusInfo().setItemEquipment(dq5::level::EventList::getRecord(i + recordNum)->getHelmet());
        eventPlayer.getHaveStatusInfo().setItemEquipment(dq5::level::EventList::getRecord(i + recordNum)->getAccessory());
        if (i == 0) {
            dq5::level::FukuroWeapon::setup();
            dq5::level::FukuroArmor::setup();
            dq5::level::FukuroItem::setup();
            setSackWeapon(index);
            setSackArmor(index);
            setSackItem(index);
            dq5::level::FukuroWeapon::cleanup();
            dq5::level::FukuroArmor::cleanup();
            dq5::level::FukuroItem::cleanup();
        }
        eventPlayer.getHaveStatusInfo().setCommandType(COMMAND_MEIREISASERO);
        i++;
    } while (dq5::level::EventList::getRecord(i + recordNum)->getIndex() == 0);

    dq5::level::EventFlag::setup();
    if (dq5::level::EventFlag::getRecord(index)->getNPC()) {
        g_Party.add(dq5::level::EventFlag::getRecord(index)->getNPC(), true);
    }
    dq5::level::EventFlag::cleanup();

    int hero = g_Party.getSortIndex(1);
    if (index >= 0x34) {
        g_Party.getPlayerStatus(hero).getHaveStatusInfo().getHaveAction().add(0, 0x81, false);
    }
    if (index >= 0x108) {
        g_Party.getPlayerStatus(hero).getHaveStatusInfo().getHaveAction().add(0x42, 0, false);
    }

    setEventFlag(index);

    if (g_AreaFlag.check(0xd9)) {
        g_Story.setVehicleEnable(0, true);
    } else {
        g_Story.setVehicleEnable(0, false);
    }
    if (g_AreaFlag.check(0xef)) {
        g_Story.setVehicleEnable(1, true);
    } else {
        g_Story.setVehicleEnable(1, false);
    }
    if (g_AreaFlag.check(0x19a)) {
        g_Story.setVehicleEnable(3, true);
    } else {
        g_Story.setVehicleEnable(3, false);
    }
    if (g_AreaFlag.check(0x176)) {
        g_StageInfo.setFieldChange(true);
    } else {
        g_StageInfo.setFieldChange(false);
    }

    dss::Fix32Vector3 pos;
    char* map = dq5::level::EventList::getRecord(recordNum)->getFloor();
    if (map[0] == 'M' && map[1] == 'I') {
        pos.vx.value = 0x13cb0c;
        pos.vy.value = 0x81cf84;
        pos.vz.value = 0;
        g_StageInfo.setShipPosition(0, pos);
    } else {
        pos.vx = 578.5f;
        pos.vy = 2397.0f;
        pos.vz = 0L;
        g_StageInfo.setShipPosition(0, pos);
    }

    if (index == 0x40) {
        cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_SHIP_IKADA);
    }
    dq5::level::EventList::cleanup();
}

THUMB void status::Status::setSackWeapon(int index)
{
    if (dq5::level::FukuroWeapon::getRecord(index)->getItemID()) {
        g_Party.haveItemSack_.add(dq5::level::FukuroWeapon::getRecord(index)->getItemID());
    }
}

THUMB void status::Status::setSackArmor(int index)
{
    if (dq5::level::FukuroArmor::getRecord(index)->getItemID1()) {
        g_Party.haveItemSack_.add(dq5::level::FukuroArmor::getRecord(index)->getItemID1());
        if (dq5::level::FukuroArmor::getRecord(index)->getItemID2()) {
            g_Party.haveItemSack_.add(dq5::level::FukuroArmor::getRecord(index)->getItemID2());
            if (dq5::level::FukuroArmor::getRecord(index)->getItemID3()) {
                g_Party.haveItemSack_.add(dq5::level::FukuroArmor::getRecord(index)->getItemID3());
            }
        }
    }
}

#define SACK_ITEM(n) \
    if (!dq5::level::FukuroItem::getRecord(index)->getItemID##n()) { \
        return; \
    } \
    g_Party.haveItemSack_.add(dq5::level::FukuroItem::getRecord(index)->getItemID##n());

THUMB void status::Status::setSackItem(int index)
{
    SACK_ITEM(1)
    SACK_ITEM(2)
    SACK_ITEM(3)
    SACK_ITEM(4)
    SACK_ITEM(5)
    SACK_ITEM(6)
    SACK_ITEM(7)
    SACK_ITEM(8)
    SACK_ITEM(9)
    SACK_ITEM(10)
    SACK_ITEM(11)
    SACK_ITEM(12)
    SACK_ITEM(13)
    SACK_ITEM(14)
    SACK_ITEM(15)
    SACK_ITEM(16)
    SACK_ITEM(17)
}

THUMB int status::Status::changeIndexForChapter(int chapter, int index)
{
    if (chapter >= 2) {
        switch (index) {
            case 3:
            case 6:
            case 16:
                return index + 1;
        }
    }
    return index;
}

THUMB void status::Status::setEventFlag(unsigned int index)
{
    dq5::level::EventFlag::setup();
    g_AreaFlag.clear();
    for (int i = 0; i <= index; i++) {
        dq5::level::EventFlag* pFlag = dq5::level::EventFlag::getRecord(i);
        if (pFlag->getFlag1()) {
            g_AreaFlag.set(pFlag->getFlag1());
        }
        if (pFlag->getFlag2()) {
            g_AreaFlag.set(pFlag->getFlag2());
        }
        if (pFlag->getFlag3()) {
            g_AreaFlag.set(pFlag->getFlag3());
        }
        if (pFlag->getFlag4()) {
            g_AreaFlag.set(pFlag->getFlag4());
        }
        if (pFlag->getFlag5()) {
            g_AreaFlag.set(pFlag->getFlag5());
        }
        if (pFlag->getFlag6()) {
            g_AreaFlag.set(pFlag->getFlag6());
        }
        if (pFlag->getFlag7()) {
            g_AreaFlag.set(pFlag->getFlag7());
        }
        if (pFlag->getFlag8()) {
            g_AreaFlag.set(pFlag->getFlag8());
        }
        if (pFlag->getFlag9()) {
            g_AreaFlag.set(pFlag->getFlag9());
        }
        if (pFlag->getFlag10()) {
            g_AreaFlag.set(pFlag->getFlag10());
        }
        if (pFlag->getFlag11()) {
            g_AreaFlag.set(pFlag->getFlag11());
        }
        if (pFlag->getFlag12()) {
            g_AreaFlag.set(pFlag->getFlag12());
        }
    }

    dq5::level::EventFlag* pFlag = dq5::level::EventFlag::getRecord(index);
    if (pFlag->getWaitFlag1()) {
        g_AreaFlag.set(pFlag->getWaitFlag1());
    }
    if (pFlag->getWaitFlag2()) {
        g_AreaFlag.set(pFlag->getWaitFlag2());
    }
    if (pFlag->getWaitFlag3()) {
        g_AreaFlag.set(pFlag->getWaitFlag3());
    }
    if (pFlag->getWaitFlag4()) {
        g_AreaFlag.set(pFlag->getWaitFlag4());
    }
    if (pFlag->getWaitFlag5()) {
        g_AreaFlag.set(pFlag->getWaitFlag5());
    }
    if (pFlag->getWaitFlag6()) {
        g_AreaFlag.set(pFlag->getWaitFlag6());
    }
    if (pFlag->getTownFlag1()) {
        g_AreaFlag.set(1);
    }
    if (pFlag->getTownFlag2()) {
        g_AreaFlag.set(2);
    }
    if (pFlag->getTownFlag3()) {
        g_AreaFlag.set(3);
    }
    if (pFlag->getTownFlag4()) {
        g_AreaFlag.set(4);
    }
    if (pFlag->getTownFlag5()) {
        g_AreaFlag.set(5);
    }
    if (pFlag->getTownFlag6()) {
        g_AreaFlag.set(6);
    }
    if (pFlag->getTownFlag7()) {
        g_AreaFlag.set(7);
    }
    if (pFlag->getTownFlag8()) {
        g_AreaFlag.set(8);
    }
    if (pFlag->getTownFlag9()) {
        g_AreaFlag.set(9);
    }
    if (pFlag->getTownFlag10()) {
        g_AreaFlag.set(10);
    }
    if (pFlag->getTownFlag11()) {
        g_AreaFlag.set(11);
    }
    if (pFlag->getTownFlag12()) {
        g_AreaFlag.set(12);
    }
    if (pFlag->getTownFlag13()) {
        g_AreaFlag.set(13);
    }
    if (pFlag->getTownFlag14()) {
        g_AreaFlag.set(14);
    }
    if (pFlag->getTownFlag15()) {
        g_AreaFlag.set(15);
    }
    if (pFlag->getTownFlag16()) {
        g_AreaFlag.set(16);
    }
    if (pFlag->getTownFlag17()) {
        g_AreaFlag.set(17);
    }
    if (pFlag->getTownFlag18()) {
        g_AreaFlag.set(18);
    }
    if (pFlag->getTownFlag19()) {
        g_AreaFlag.set(19);
    }
    if (pFlag->getTownFlag20()) {
        g_AreaFlag.set(20);
    }
    g_StageAttribute.setTimestopFlag(false);
    dq5::level::EventFlag::cleanup();
}

THUMB void status::Status::setFlagShopIndex(int index)
{
    flagShopIndex = index;
}

THUMB void status::Status::setFlagShopExec()
{
    if (flagShopIndex == -1) {
        return;
    }
    dq5::level::EventList::setup();
    char buff[10];
    dss::memset(buff, 0, sizeof(buff));
    dss::strcpy_s(buff, sizeof(buff), dq5::level::EventList::getRecord(flagShopIndex)->getFloor());
    dq5::level::EventList::cleanup();
    initialize();
    setEventParty(flagShopIndex);
    flagShopIndex = -1;
}
