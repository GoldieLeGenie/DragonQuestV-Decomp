#include "ov001/town/TownFurniture.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/leveldata/ItemData.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/text/TextAPI.hpp"

inline dq5::level::ItemData* dq5::level::ItemData::getRecord(int index)
{
    return (ItemData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline char dq5::level::ItemData::getImportant()
{
    return (byte_4 & 0x8) >> 3;
}

THUMB twn::TownFurnitureItem::TownFurnitureItem()
{
}

THUMB twn::TownFurnitureItem::~TownFurnitureItem()
{
}

THUMB void twn::TownFurnitureItem::setSecondMessage()
{
    status::g_Party.setPlayerMode();
    if (data_ == 0xffff) {
        data_ = 0;
    }
    TextAPI::setMACRO0(0xa, 0x40000000, data_);
    addMessage(0xc44bd, true);
    int result = addPlayerItem();
    int player = 0;
    for (int i = 0; i < status::g_Party.getCarriageOutCount(); i++) {
        if (!status::g_Party.getPlayerStatus(i).haveStatusInfo_.isDeath()) {
            player = status::g_Party.getPlayerIndex(i);
            break;
        }
    }
    if (data_ != 0xd1) {
        if (dq5::level::ItemData::getRecord(data_)->getImportant() || data_ == 0xd1) {
            TownWindowSystem::getSingleton().waitCommonMessage();
        }
        TextAPI::setMACRO0(0xa, 0x40000000, data_);
        if (result > -1) {
            TextAPI::setMACRO0(0x12, 0x50000000, result);
            addMessage(0xc44c0, true);
            return;
        }
        TextAPI::setMACRO0(0xa, 0x40000000, data_);
        addMessage(0xc44c2, true);
        return;
    }
    if (data_ == 0xd1 && !status::g_Story.isMedalFlag()) {
        addMessage(0xc45c2, true);
        addMessage(0xc45c3, true);
        status::g_Story.setMedalFlag(true);
    }
}

THUMB void twn::TownFurnitureItem::startRiseup()
{
    if (data_ == 0xd1) {
        index_ = TownRiseupManager::getSingleton().setupMedal(getFurnPosition());
    } else {
        index_ = TownRiseupManager::getSingleton().setup(data_, getFurnPosition());
    }
    counter_ = 0;
}

THUMB bool twn::TownFurnitureItem::endRiseup()
{
    TownFurnitureObject::endRiseup();
    return false;
}

THUMB int twn::TownFurnitureItem::addPlayerItem()
{
    status::g_Party.setPlayerMode();
    cmn::PartyTalk::getSingleton().resetPartyTalk();
    cmn::PartyTalk::getSingleton().setPreItem(data_);
    cmn::PartyTalk::getSingleton().setTreasureUid(uid_);
    if (data_ == 0xd1) {
        status::g_Party.addMedalCoin(1);
        return status::g_Party.getPlayerIndex(0);
    }
    for (int i = 0; i < status::g_Party.getCount(); i++) {
        if (!status::g_Party.getPlayerStatus(i).haveStatusInfo_.isDeath() && status::g_Party.getPlayerStatus(i).haveStatusInfo_.haveItem_.getCount() < 12) {
            status::g_Party.getPlayerStatus(i).haveStatusInfo_.haveItem_.add(data_);
            return status::g_Party.getPlayerIndex(i);
        }
    }
    status::g_Party.haveItemSack_.add(data_);
    return -1;
}

THUMB bool twn::TownFurnitureItem::isRiseupEnd()
{
    return TownRiseupManager::getSingleton().isFinish(index_);
}

THUMB bool twn::TownFurnitureItem::soundStart()
{
    if (counter_ == 0) {
        if (data_ == 0xd1) {
            SoundManager::playRestart(0x2b, 5);
        } else {
            SoundManager::playRestart(0x2c, 10);
        }
    }
    if (counter_ == SOUND_WAIT) {
        TownWindowSystem::getSingleton().clearCommonMessage();
        if (data_ == 0xd1) {
            status::g_Story.isMedalFlag();
        }
        return true;
    }
    counter_++;
    return false;
}
