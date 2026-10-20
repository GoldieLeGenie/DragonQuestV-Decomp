#pragma ipa file
#include "ov000/btl/BattleExecVictory.hpp"
#include "ov000/btl/BattleActorManager.hpp"
#include "ov000/btl/BattleMessage.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov000/status/MonsterStatus.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/btl/Encount.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/global/Global.hpp"
#include "main/global/GlobalGamePart.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/leveldata/MonsterData.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/text/TextAPI.hpp"

inline ExecTaskManager::ExecTaskManager() { flag_.clear(); }
inline ExecTaskManager::~ExecTaskManager() {}
inline int btl::Encount::getMonsterIndex(int group) { return monsterIndex_[group]; }
inline int btl::Encount::getMonsterCount(int group) { return monsterCount_[group]; }
inline int btl::Encount::getEncountNumberIndex() { return encountNumberIndex_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline int status::MonsterStatus::getMonsterIndex() { return characterIndex_; }
inline int status::MonsterStatus::getMonsterGroup() { return characterGroup_; }
inline int status::MonsterStatus::getSortIndexInGroup() { return sortIndex_; }
inline int status::HaveStatus::getPlayerIndex() const { return playerIndex_; }
inline int status::PlayerStatus::getPlayerIndex() { return haveStatusInfo_.haveStatus_.getPlayerIndex(); }
inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}
inline dq5::CHAPTER_NO status::StoryStatus::getChapter() { return chapter_; }
inline void status::BasePartyStatus::clearBattleMonsterCount() { battleMonsterCount_ = 0; }
inline void status::BasePartyStatus::clearBattleExp() { battleExp_ = 0; }
inline void status::BasePartyStatus::clearBattleGold() { battleGold_ = 0; }
inline bool btl::BattleActorManager::isSingleBeat() { return (winningStatus_ & FLAG_MASK) == DEATH_SINGLE; }
inline bool btl::BattleActorManager::isNumbersBeat() { return (winningStatus_ & FLAG_MASK) == DEATH_NUMBERS; }
inline bool btl::BattleActorManager::isMultipleBeat() { return (winningStatus_ & FLAG_MASK) == DEATH_MULTIPLE; }
inline int btl::BattleActorManager::getBeatIndex() { return winningStatus_ & INDEX_MASK; }
inline bool btl::BattleActorManager::isEscapeSuccess() { return escapeSuccess_; }
inline menu::MenuBase::MENUBASE_STAT menu::MenuBase::getStat() { return stat_; }
inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index) { return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned char dq5::level::MonsterData::getParty() { return party; }
inline void btl::BattleExecVictory30::setMonsterIndex(int monsterIndex) { monsterIndex_ = monsterIndex; }
inline void btl::BattleExecVictory30::setItemIndex(int itemIndex) { itemIndex_ = itemIndex; }
inline void btl::BattleExecVictory31a::setItemIndex(int itemIndex) { itemIndex_ = itemIndex; }
inline void btl::BattleExecVictory32::setItemIndex(int itemIndex) { itemIndex_ = itemIndex; }
inline void btl::BattleExecVictory33::setPlayerIndex(int playerIndex) { playerIndex_ = playerIndex; }
inline void btl::BattleExecVictory34::setPlayerIndex(int playerIndex) { playerIndex_ = playerIndex; }
inline void btl::BattleExecVictory35::setPlayerIndex(int playerIndex) { playerIndex_ = playerIndex; }
inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }
inline void btl::BattleExecVictory36::setPlayerIndex(int playerIndex) { playerIndex_ = playerIndex; }

THUMB void btl::BattleExecEncount::setup()
{
    Encount::getSingleton();
    BattleMessage::openEncountMessage();
    for (int i = 0; i < 4; i++) {
        int index = Encount::getSingleton()->getMonsterIndex(i);
        int count = Encount::getSingleton()->getMonsterCount(i);
        if (count != 0) {
            TextAPI::setMACRO0(0xD, 0x60000000, index);
            if (count == 1) {
                BattleMessage::addEncountMessage(0xC38EA);
            }
            else {
                BattleMessage::addEncountMessage(0xC38EE);
            }
        }
    }
    BattleAutoFeed::setCursor();
    BattleAutoFeed::setMessage();
    BattleAutoFeed::setEncountMessage();
}

THUMB bool btl::BattleExecEncount::isEnd()
{
    if (data_02101c88.getCurrentPart() == 5) {
        if (BattleAutoFeed::isEndEncountMessage()) {
            return true;
        }
    }
    else if (MenuAPI::isFinishMessageWindow()) {
        return true;
    }
    return false;
}

btl::BattleExecEncount btl::g_BattleExecEncount;

THUMB void btl::BattleExecStatus::setup()
{
    setupLast();
    group_ = 0;
    all_ = 0;
}

THUMB bool btl::BattleExecStatus::isEnd()
{
    if (data_02101c88.getCurrentPart() == 5) {
        if (BattleAutoFeed::isEndEncountMessage() && isNext()) {
            return true;
        }
    }
    else if (MenuAPI::isFinishMessageWindow() && isNext()) {
        return true;
    }
    return false;
}

THUMB void btl::BattleExecStatus::setupLast()
{
    index_ = 0;
    monsterCount_ = status::g_Monster.getCount();
}

THUMB bool btl::BattleExecStatus::isNext()
{
    int all = true;
    for (int i = 0; i < monsterCount_; i++) {
        if (!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
            all = false;
        }
    }
    if (all) {
        if (all_) {
            return true;
        }
        if (Encount::getSingleton()->getMonsterCount(1)) {
            TextAPI::setMACRO0(0xD, 0x60000000, 0xF6);
            BattleMessage::openEncountMessage();
            BattleMessage::addEncountMessage(0xC390E);
        }
        else {
            int index = status::g_Monster.getMonsterStatus(0).getMonsterIndex();
            TextAPI::setMACRO0(0xD, 0x60000000, index);
            BattleMessage::openEncountMessage();
            if (monsterCount_ == 1) {
                BattleMessage::addEncountMessage(0xC390A);
            }
            else {
                BattleMessage::addEncountMessage(0xC390C);
            }
        }
        all_ = true;
        return false;
    }
    int monsterIndex = 0;
    int monsterCount;
    for (int i = group_; i < 4; i++) {
        if (status::g_Monster.getMonsterCountInGroup(i) == 0) {
            continue;
        }
        all = true;
        monsterCount = 0;
        for (int j = 0; j < monsterCount_; j++) {
            if (i == status::g_Monster.getMonsterStatus(j).getMonsterGroup()) {
                if (!status::g_Monster.getMonsterStatus(j).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
                    all = false;
                }
                else {
                    monsterCount++;
                }
                monsterIndex = status::g_Monster.getMonsterStatus(j).getMonsterIndex();
            }
        }
        if (all && monsterCount > 1) {
            TextAPI::setMACRO0(0xD, 0x60000000, monsterIndex);
            BattleMessage::openEncountMessage();
            BattleMessage::addEncountMessage(0xC390C);
            group_ = i + 1;
            return false;
        }
        for (int j = index_; j < monsterCount_; j++) {
            if (i == status::g_Monster.getMonsterStatus(j).getMonsterGroup() && status::g_Monster.getMonsterStatus(j).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
                int index = status::g_Monster.getMonsterStatus(j).getMonsterIndex();
                if (status::g_Monster.getMonsterCountDeadOrAlive(index) == 1 && !Encount::getSingleton()->getMonsterCountName(index)) {
                    TextAPI::setMACRO0(0xD, 0x60000000, index);
                }
                else {
                    int sortIndex = status::g_Monster.getMonsterStatus(j).getSortIndexInGroup();
                    TextAPI::setMACRO0(0xD, 0x60000000, index, sortIndex);
                }
                BattleMessage::openEncountMessage();
                BattleMessage::addEncountMessage(0xC390A);
                index_ = j + 1;
                return false;
            }
        }
    }
    return true;
}

btl::BattleExecStatus btl::g_BattleExecStatus;

THUMB void btl::BattleExecFirstAttack::setup()
{
    FirstAttack firstAttack = BattleActorManager::getSingleton()->getFirstAttack();
    int type;
    if (firstAttack == FirstAttackPlayer) {
        type = UnkDssRand::rand(2);
    }
    else if (firstAttack == FirstAttackMonster) {
        type = UnkDssRand::rand(2) + 2;
    }
    else {
        return;
    }
    BattleMessage::openEncountMessage();
    int mess = 0;
    int callType = status::g_Monster.getMonsterCallType();
    switch (type) {
    case 0:
        if (callType == 0) {
            mess = 0xC38F2;
        }
        if (callType == 1) {
            mess = 0xC38F4;
        }
        if (callType == 2) {
            mess = 0xC38F6;
        }
        break;
    case 1:
        if (callType == 0) {
            mess = 0xC38F8;
        }
        if (callType == 1) {
            mess = 0xC38FA;
        }
        if (callType == 2) {
            mess = 0xC38FC;
        }
        break;
    case 2:
        if (callType == 0) {
            mess = 0xC38FE;
        }
        if (callType == 1) {
            mess = 0xC3900;
        }
        if (callType == 2) {
            mess = 0xC3902;
        }
        break;
    case 3:
        if (callType == 0) {
            mess = 0xC3904;
        }
        if (callType == 1) {
            mess = 0xC3906;
        }
        if (callType == 2) {
            mess = 0xC3908;
        }
        break;
    }
    if (callType == 2) {
        TextAPI::setMACRO0(0xD, 0x60000000, 0xF6);
    }
    else {
        int index = status::g_Monster.getMonsterCallIndex();
        TextAPI::setMACRO0(0xD, 0x60000000, index);
    }
    BattleMessage::addEncountMessage(mess);
    BattleAutoFeed::setCursor();
    BattleAutoFeed::setMessage();
    BattleAutoFeed::setEncountMessage();
}

THUMB bool btl::BattleExecFirstAttack::isEnd()
{
    if (data_02101c88.getCurrentPart() == 5) {
        if (BattleAutoFeed::isEndEncountMessage()) {
            return true;
        }
    }
    else if (MenuAPI::isFinishMessageWindow()) {
        return true;
    }
    return false;
}

btl::BattleExecFirstAttack btl::g_BattleExecFirstAttack;

THUMB void btl::BattleExecVictory00::setup()
{
    int index;
    int mess = 0;
    if (BattleActorManager::getSingleton()->isSingleBeat()) {
        index = BattleActorManager::getSingleton()->getBeatIndex();
        TextAPI::setMACRO0(0xD, 0x60000000, index);
        mess = 0xC3C81;
    }
    else if (BattleActorManager::getSingleton()->isNumbersBeat()) {
        index = BattleActorManager::getSingleton()->getBeatIndex();
        TextAPI::setMACRO0(0xD, 0x60000000, index);
        mess = 0xC3C83;
    }
    else if (BattleActorManager::getSingleton()->isMultipleBeat()) {
        TextAPI::setMACRO0(0xD, 0x60000000, 0xF6);
        mess = 0xC3C85;
    }
    BattleMessage::setMessage(mess, 0, 0, 0);
    BattleAutoFeed::setMessageSend();
    if (status::g_Party.getBattleExp() == 0) {
        BattleAutoFeed::setDisableCursor(true);
    }
    if (status::g_Party.getBattleGold() == 0) {
        BattleAutoFeed::setDisableCursor(true);
    }
}

THUMB void btl::BattleExecVictory01::setup()
{
    int exp = status::g_Party.getBattleExp();
    TextAPI::setMACRO0(0x2F, 0xF0000000, exp);
    BattleMessage::setMessage(0xC3C93, 0, 0, 0);
    BattleAutoFeed::setMessageSend();
    if (status::PartyStatusUtility::getLevelupPlayer() == -1 && status::g_Party.getBattleGold() == 0) {
        BattleAutoFeed::setDisableCursor(true);
        gTownMenu_MESSAGE.setMessageLastCursor(false);
    }
}

THUMB void btl::BattleExecVictory02::setup()
{
    int type = Encount::getSingleton()->getEncountNumberType();
    int index = Encount::getSingleton()->getEncountNumberIndex();
    TextAPI::setMACRO0(0xD, 0x60000000, index);
    int mess;
    switch (type) {
    case Encount::EncountSingle:
        mess = 0xC3C8D;
        break;
    case Encount::EncountNumbers:
        mess = 0xC3C8F;
        break;
    case Encount::EncountMultiple:
        TextAPI::setMACRO0(0xD, 0x60000000, 0xF6);
        mess = 0xC3C91;
        break;
    default:
        TextAPI::setMACRO0(0xD, 0x60000000, 0xF6);
        mess = 0xC3C91;
        break;
    }
    BattleAutoFeed::setCursor();
    BattleMessage::setMessage(mess, 0, 0, 0);
    BattleAutoFeed::setMessageSend();
    BattleAutoFeed::setDisableCursor(true);
}

THUMB void btl::BattleExecVictory03::setup()
{
    int type = 0;
    int oldIndex = 0;
    for (int i = 0; i < 4; i++) {
        int index = Encount::getSingleton()->getMonsterIndex(i);
        int count = Encount::getSingleton()->getMonsterCount(i);
        if (count == 0) {
            continue;
        }
        if (i == 0) {
            if (count == 1) {
                type = 0;
                TextAPI::setMACRO0(0xD, 0x60000000, index);
                oldIndex = index;
            }
            else {
                type = 1;
                TextAPI::setMACRO0(0xD, 0x60000000, index);
                oldIndex = index;
            }
        }
        if (i > 0) {
            if (oldIndex != index) {
                type = 2;
                TextAPI::setMACRO0(0xD, 0x60000000, index);
            }
            else {
                type = 1;
                TextAPI::setMACRO0(0xD, 0x60000000, index);
            }
        }
    }
    int mess;
    switch (type) {
    case 0:
        mess = 0xC3C87;
        break;
    case 1:
        mess = 0xC3C89;
        break;
    case 2:
        TextAPI::setMACRO0(0xD, 0x60000000, 0xF6);
        mess = 0xC3C8B;
        break;
    default:
        TextAPI::setMACRO0(0xD, 0x60000000, 0xF6);
        mess = 0xC3C8B;
        break;
    }
    BattleAutoFeed::setCursor();
    BattleMessage::setMessage(mess, 0, 0, 0);
    BattleAutoFeed::setMessageSend();
    BattleAutoFeed::setDisableCursor(true);
}

THUMB void btl::BattleExecVictory20::setup()
{
    int gold = status::g_Party.getBattleGold();
    if (gold != 0) {
        TextAPI::setMACRO0(0x32, 0xF0000000, gold);
        BattleMessage::setMessage(0xC3CA5, 0, 0, 0);
        BattleAutoFeed::setMessageSend();
        if (status::g_Monster.getDropItem() == 0) {
            BattleAutoFeed::setDisableCursor(true);
        }
    }
}

THUMB void btl::BattleExecVictory30::setup()
{
    TextAPI::setMACRO0(0x12, 0x60000000, monsterIndex_);
    TextAPI::setMACRO0(0xA, 0x40000000, itemIndex_);
    BattleMessage::setMessage(0xC3CA8, 0, 0, 0);
    BattleAutoFeed::setMessageSend();
}

THUMB void btl::BattleExecVictory31::setup()
{
    status::g_Party.getPlayerStatus(status::PartyStatusUtility::getLeaderIndex());
    BattleMessage::setMessage(0xC3D64, 0, 0, 0);
    BattleAutoFeed::setMessageSend();
    SoundManager::playSe(0x13A, 0);
}

THUMB void btl::BattleExecVictory31a::setup()
{
    TextAPI::setMACRO0(0xA, 0x40000000, itemIndex_);
    BattleMessage::setMessage(0xC3CAA, 0, 0, 0);
    BattleAutoFeed::setMessageSend();
}

THUMB void btl::BattleExecVictory32::setup()
{
    if (itemIndex_ == 0xD1) {
        status::g_Party.addMedalCoin(1);
        if (!status::g_Story.isMedalFlag()) {
            BattleMessage::setMessage(0xC3D26, 0, 0, 0);
        }
        status::g_Story.setMedalFlag(true);
    }
    else {
        int index = status::PartyStatusUtility::giveItem(itemIndex_);
        if (index != -1) {
            int playerIndex = status::g_Party.getPlayerStatus(index).getPlayerIndex();
            TextAPI::setMACRO0(0x12, 0x50000000, playerIndex);
            TextAPI::setMACRO0(0xA, 0x40000000, itemIndex_);
            BattleMessage::setMessage(0xC3CAD, 0, 0, 0);
        }
        else {
            TextAPI::setMACRO0(0xA, 0x40000000, itemIndex_);
            BattleMessage::setMessage(0xC3CB0, 0, 0, 0);
        }
    }
    BattleAutoFeed::setMessageSend();
    BattleAutoFeed::setDisableCursor(true);
}

THUMB void btl::BattleExecVictory33::setup()
{
    TextAPI::setMACRO0(1, 0x50000000, playerIndex_);
    BattleMessage::setMessage(0xC3C75, 0, 0, 0);
    BattleAutoFeed::setMessage();
}

THUMB bool btl::BattleExecVictory33::isEnd()
{
    if (BattleAutoFeed::isEndMessage()) {
        return true;
    }
    return false;
}

THUMB void btl::BattleExecVictory34::setup()
{
    TextAPI::setMACRO0(1, 0x50000000, playerIndex_);
    BattleMessage::setMessage(0xC3C75, 0, 0, 0);
    BattleAutoFeed::setMessage();
}

THUMB bool btl::BattleExecVictory34::isEnd()
{
    if (BattleAutoFeed::isEndMessage()) {
        return true;
    }
    return false;
}

THUMB void btl::BattleExecVictory35::setup()
{
    TextAPI::setMACRO0(1, 0x50000000, playerIndex_);
    BattleMessage::setMessage(0xC3C75, 0, 0, 0);
    BattleAutoFeed::setMessage();
}

THUMB bool btl::BattleExecVictory35::isEnd()
{
    if (BattleAutoFeed::isEndMessage()) {
        return true;
    }
    return false;
}

THUMB void btl::BattleExecVictory36::setup()
{
    TextAPI::setMACRO0(1, 0x50000000, playerIndex_);
    BattleMessage::setMessage(0xC3C75, 0, 0, 0);
    BattleAutoFeed::setMessage();
}

THUMB bool btl::BattleExecVictory36::isEnd()
{
    if (BattleAutoFeed::isEndMessage()) {
        return true;
    }
    return false;
}

THUMB void btl::BattleExecVictory37::setup()
{
    if (status::g_Story.getChapter() == 1) {
        BattleMessage::setMessage(0xC3C77, 0, 0, 0);
    }
    else {
        status::g_Party.setBattleMode();
        int count = status::g_Party.getCount();
        if (count == 1) {
            BattleMessage::setMessage(0xC3C7A, 0, 0, 0);
        }
        else {
            BattleMessage::setMessage(0xC3C7D, 0, 0, 0);
        }
    }
    BattleAutoFeed::setMessageSend();
    BattleAutoFeed::setDisableCursor(true);
    BattleAutoFeed::disableAutoFeed();
}

THUMB void btl::BattleExecVictory37::cleanup()
{
}

THUMB void btl::BattleExecVictory38::setup()
{
    SoundManager::play(0x17, 5);
    data_0211b27c.state_ = FadeEffector::FADE_NONE;
    data_0211b27c.count_ = 0;
    data_0211b27c.frames_ = 30;
    data_0211b27c.sprite_[0].setColor(0, 0, 0);
    data_0211b27c.sprite_[1].setColor(0, 0, 0);
    data_02101d14.addPart(&data_0211b27c);
    MenuAPI::closeMenu();
    counter_ = 0;
}

THUMB bool btl::BattleExecVictory38::isEnd()
{
    if (counter_ > 120) {
        return true;
    }
    counter_++;
    return false;
}

THUMB void btl::BattleExecVictory39::setup()
{
    BattleMessage::setMessageInTown(0xC3C27, 0, 0, 0);
    BattleAutoFeed::disableAutoFeed();
    BattleAutoFeed::setMessageSend();
}

THUMB void btl::BattleExecVictory40::setup()
{
    g_Global.fadeOutBlack(30, true);
    counter_ = 0;
}

THUMB void btl::BattleExecVictory40::cleanup()
{
}

THUMB bool btl::BattleExecVictory40::isEnd()
{
    if (counter_ > 30) {
        return true;
    }
    if (counter_ == 25) {
        switch (data_0211b27c.state_) {
        case FadeEffector::FADE_NONE:
            data_0211b27c.state_ = FadeEffector::FADE_OUT_BLACK;
            break;
        case FadeEffector::FADE_IN_BLACK:
            data_0211b27c.state_ = FadeEffector::FADE_OUT_WHITE;
            break;
        default:
            data_0211b27c.state_ = FadeEffector::FADE_OUT_BLACK;
            break;
        }
        data_0211b27c.count_ = 0;
        data_0211b27c.frames_ = 5;
        data_02101d14.addPart(&data_0211b27c);
    }
    counter_++;
    return false;
}

namespace btl {
    int VELORINMAN_POS[4];
    static const int VELORINMAN_POS2[4] = { -0xF6CC, -0x5244, 0x5244, 0xF6CC };
    int nowRealVelorinmanIdx;
    static int preRealVelorinmanIdx = -1;
    dss::Fix32Vector3 verolinmanPos[4];
}

const int btl::BattleExecEvent00b::COUNT = 120;

// The BattleExecEvent* tasks below are not linked in the ROM: only their data
// (the positions above and their vtables) remains, so they follow the mobile code.
THUMB int btl::BattleExecEvent00::getRealVelorinman()
{
    return nowRealVelorinmanIdx;
}

THUMB void btl::BattleExecEvent00::setup()
{
    counter_ = 0;
    for (int i = 0; i < 4; i++) {
        setupMonster(i);
    }
    if (preRealVelorinmanIdx == -1) {
        for (int i = 0; i < 4; i++) {
            dss::Fix32Vector3 pos(0, 0, 0);
            pos.vx.value = VELORINMAN_POS[i];
            BattleMonsterDraw2::getSingleton().getMonster(i).setPosition(pos);
            BattleMonsterDraw2::getSingleton().getMonster(i).startAnimation(0x25);
        }
    }
    else {
        VELORINMAN_POS[nowRealVelorinmanIdx] = VELORINMAN_POS2[nowRealVelorinmanIdx];
        for (int i = 0; i < 4; i++) {
            if (!status::g_Monster.getMonsterStatus(i).eventFlag_.check(1)) {
                BattleMonsterDraw2::getSingleton().getMonster(i).startAnimation(0x24);
            }
        }
    }
    int count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        status::g_Monster.getMonsterStatus(i).eventFlag_.remove(1);
    }
    preRealVelorinmanIdx = nowRealVelorinmanIdx;
    nowRealVelorinmanIdx = UnkDssRand::rand(4);
    status::g_Monster.getMonsterStatus(nowRealVelorinmanIdx).eventFlag_.set(1);
}

THUMB void btl::BattleExecEvent00::cleanup()
{
    for (int i = 0; i < 4; i++) {
        verolinmanPos[i].set(0, 0, 0);
        verolinmanPos[i].vx.value = VELORINMAN_POS[preRealVelorinmanIdx];
        int ctrl = status::g_Monster.getMonsterInGroup(i, 0).getCtrlId();
        BattleMonsterDraw2::getSingleton().getMonster(ctrl).setPosition(verolinmanPos[i]);
    }
}

THUMB bool btl::BattleExecEvent00::isEnd()
{
    if (counter_++ > 59) {
        return true;
    }
    return false;
}

THUMB int btl::BattleExecEvent00::setupMonster(int group)
{
    if (status::g_Monster.getMonsterCountInGroup(group) == 0) {
        return status::g_Monster.add(group, 0xAA, true);
    }
    return status::g_Monster.getMonsterInGroup(group, 0).getCtrlId();
}

THUMB void btl::BattleExecEvent00b::setup()
{
    counter_ = 0;
}

THUMB void btl::BattleExecEvent00b::cleanup()
{
    for (int i = 0; i < 4; i++) {
        verolinmanPos[i].set(0, 0, 0);
        verolinmanPos[i].vx.value = VELORINMAN_POS2[i];
        int ctrl = status::g_Monster.getMonsterInGroup(i, 0).getCtrlId();
        BattleMonsterDraw2::getSingleton().getMonster(ctrl).setPosition(verolinmanPos[i]);
    }
}

THUMB bool btl::BattleExecEvent00b::isEnd()
{
    counter_++;
    move();
    if (counter_ > COUNT) {
        return true;
    }
    return false;
}

THUMB void btl::BattleExecEvent00b::move()
{
    for (int i = 0; i < 4; i++) {
        verolinmanPos[i].set(0, 0, 0);
        int pos = VELORINMAN_POS[preRealVelorinmanIdx];
        verolinmanPos[i].vx.value = pos + (unsigned int)((VELORINMAN_POS2[i] - pos) * counter_) / COUNT;
        verolinmanPos[i].vz.value += i * 0x400;
        int ctrl = status::g_Monster.getMonsterInGroup(i, 0).getCtrlId();
        BattleMonsterDraw2::getSingleton().getMonster(ctrl).setPosition(verolinmanPos[i]);
    }
}

THUMB void btl::BattleExecEvent14::setup()
{
    TextAPI::setMACRO0(1, 0x60000000, 0xAE);
    TextAPI::setMACRO0(0x11, 0x70000000, 0x23);
    BattleMessage::setMessage(0xC3931, 0, 0, 0);
    BattleAutoFeed::setMessage();
}

THUMB bool btl::BattleExecEvent14::isEnd()
{
    return BattleAutoFeed::isEndMessage();
}

THUMB void btl::BattleExecEvent15::setup()
{
    TextAPI::setMACRO0(1, 0x60000000, 0xAE);
    BattleMessage::setMessage(0xC3B31, 0, 0, 0);
    BattleAutoFeed::setMessage();
    counter = 0;
}

THUMB bool btl::BattleExecEvent15::isEnd()
{
    bool end = false;
    if (BattleAutoFeed::isEndMessage()) {
        if (counter > 59) {
            end = true;
        }
        else {
            counter++;
        }
    }
    return end;
}

namespace btl {
    static int monsterAddEnable;
}

THUMB void btl::BattleExecMonster00::setup()
{
    MenuAPI::openFriendMenu();
}

THUMB bool btl::BattleExecMonster00::isEnd()
{
    if (MenuAPI::isFinishMenu()) {
        return true;
    }
    return false;
}

THUMB void btl::BattleExecMonster01::setup()
{
    monsterAddEnable = false;
    BattleMessage::setMessage(0xC3D22, 0, 0, 0);
    gTownMenu_MESSAGE.setYesNo();
    BattleAutoFeed::setMessageSend();
    BattleAutoFeed::setDisableCursor(true);
}

THUMB bool btl::BattleExecMonster01::isEnd()
{
    if (gTownMenu_MESSAGE.getStat() == menu::MenuBase::MENUBASE_STAT_OK) {
        monsterAddEnable = true;
        return true;
    }
    if (gTownMenu_MESSAGE.getStat() == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        monsterAddEnable = false;
        return true;
    }
    return false;
}

THUMB void btl::BattleExecMonster02::setup()
{
    if (!monsterAddEnable) {
        int monster = status::g_Monster.getPartyMonster();
        TextAPI::setMACRO0(0xD, 0x60000000, monster);
        BattleMessage::setMessage(0xC3CB6, 0, 0, 0);
        BattleAutoFeed::setMessageSend();
        BattleAutoFeed::setDisableCursor(true);
    }
}

THUMB bool btl::BattleExecMonster02::isEnd()
{
    if (monsterAddEnable) {
        return true;
    }
    return ExecTask::isEnd();
}

THUMB void btl::BattleExecMonster03::setup()
{
    if (monsterAddEnable) {
        int monster = status::g_Monster.getPartyMonster();
        int playerIndex = dq5::level::MonsterData::getRecord(monster)->getParty();
        if (status::PlayerDataAll::getFriendMonsterCountInMonster(playerIndex) == 0) {
            int index = status::PlayerDataAll::addFriendMonster(playerIndex);
            status::g_Party.add(index, true);
        }
        TextAPI::setMACRO0(0xD, 0x60000000, monster);
        BattleMessage::setMessage(0xC3CB9, 0, 0, 0);
        BattleAutoFeed::setMessageSend();
        BattleAutoFeed::setDisableCursor(true);
    }
}

THUMB bool btl::BattleExecMonster03::isEnd()
{
    if (monsterAddEnable) {
        return ExecTask::isEnd();
    }
    return true;
}

THUMB void btl::BattleExecMonsterEscape::initialize()
{
    ExecTaskManager::initialize();
    resister(0, &battleExecVictory02);
}

THUMB void btl::BattleExecMonsterEscape::terminate()
{
}

btl::BattleExecMonsterEscape btl::g_BattleExecMonsterEscape;

THUMB void btl::BattleExecMonsterDisappear::initialize()
{
    ExecTaskManager::initialize();
    resister(0, &battleExecVictory03);
}

THUMB void btl::BattleExecMonsterDisappear::terminate()
{
}

btl::BattleExecMonsterDisappear btl::g_BattleExecMonsterDisappear;

THUMB void btl::BattleExecDefeatMonster::initialize()
{
    ExecTaskManager::initialize();
    resister(0, &battleExecVictory00);
}

THUMB void btl::BattleExecDefeatMonster::terminate()
{
}

btl::BattleExecDefeatMonster btl::g_BattleExecDefeatMonster;

THUMB void btl::BattleExecExp::initialize()
{
    ExecTaskManager::initialize();
    resister(0, &battleExecVictory01);
}

THUMB void btl::BattleExecExp::terminate()
{
    status::g_Party.clearBattleExp();
    status::g_Party.clearBattleMonsterCount();
}

btl::BattleExecExp btl::g_BattleExecExp;

THUMB void btl::BattleExecGold::initialize()
{
    ExecTaskManager::initialize();
    status::g_Party.reflectBattleGold();
    resister(0, &battleExecVictory20);
}

THUMB void btl::BattleExecGold::terminate()
{
    status::g_Party.clearBattleGold();
}

btl::BattleExecGold btl::g_BattleExecGold;

THUMB void btl::BattleExecItem::initialize()
{
    ExecTaskManager::initialize();
    int itemIndex = status::g_Monster.getDropItem();
    if (itemIndex) {
        resister(0, &battleExecVictory30);
        int monsterIndex = status::g_Monster.getDropItemMonster();
        battleExecVictory30.setMonsterIndex(monsterIndex);
        battleExecVictory30.setItemIndex(itemIndex);
        resister(1, &battleExecVictory31);
        resister(2, &battleExecVictory31a);
        battleExecVictory31a.setItemIndex(itemIndex);
        resister(3, &battleExecVictory32);
        battleExecVictory32.setItemIndex(itemIndex);
    }
}

THUMB void btl::BattleExecItem::terminate()
{
}

btl::BattleExecItem btl::g_BattleExecItem;

THUMB void btl::BattleExecMonster::initialize()
{
    ExecTaskManager::initialize();
    resister(0, &battleExecMonster00);
}

THUMB void btl::BattleExecMonster::terminate()
{
}

btl::BattleExecMonster btl::g_BattleExecMonster;

THUMB void btl::BattleExecReorder::initialize()
{
    status::PartyStatusUtility::forceReorderBattle();
    ExecTaskManager::initialize();
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    int resisterIndex = 0;
    for (int i = 0; i < count; i++) {
        if (!status::g_Party.getPlayerStatus(i).getHaveStatusInfo().haveStatus_.isPlayer()) {
            continue;
        }
        if (resisterIndex == 0 && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
            resister(resisterIndex, &battleExecVictory33);
            resisterIndex++;
            battleExecVictory33.setPlayerIndex(status::g_Party.getPlayerStatus(i).getPlayerIndex());
        }
        else if (resisterIndex == 1 && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
            resister(resisterIndex, &battleExecVictory34);
            resisterIndex++;
            battleExecVictory34.setPlayerIndex(status::g_Party.getPlayerStatus(i).getPlayerIndex());
        }
        else if (resisterIndex == 2 && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
            resister(resisterIndex, &battleExecVictory35);
            resisterIndex++;
            battleExecVictory35.setPlayerIndex(status::g_Party.getPlayerStatus(i).getPlayerIndex());
        }
        else if (resisterIndex == 3 && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
            resister(resisterIndex, &battleExecVictory36);
            resisterIndex++;
            battleExecVictory36.setPlayerIndex(status::g_Party.getPlayerStatus(i).getPlayerIndex());
        }
    }
}

btl::BattleExecReorder btl::g_BattleExecReorder;

THUMB void btl::BattleExecDemolition::initialize()
{
    ExecTaskManager::initialize();
    resister(0, &battleExecVictory37);
}

THUMB void btl::BattleExecDemolition::terminate()
{
}

btl::BattleExecDemolition btl::g_BattleExecDemolition;

THUMB void btl::BattleExecEscape::setup()
{
    status::g_Party.getPlayerStatus(status::PartyStatusUtility::getLeaderIndex());
    status::g_Party.setBattleMode();
    int count = 0;
    int partyCount = status::g_Party.getCount();
    for (int i = 0; i < partyCount; i++) {
        if (!status::g_Party.isInsideCarriage(i)) {
            count++;
        }
    }
    if (BattleActorManager::getSingleton()->isEscapeSuccess()) {
        if (count == 1) {
            BattleMessage::setMessage(0xC39B8, 0, 0, 0);
            BattleAutoFeed::setDisableCursor(true);
        }
        else {
            BattleMessage::setMessage(0xC39BD, 0, 0, 0);
            BattleAutoFeed::setDisableCursor(true);
        }
    }
    else if (count == 1) {
        BattleMessage::setMessage(0xC39B8, 0xC39BB, 0, 0);
    }
    else {
        BattleMessage::setMessage(0xC39BD, 0xC39BB, 0, 0);
    }
    SoundManager::playSe(0x198, 0);
    BattleAutoFeed::setCursor();
    BattleAutoFeed::setMessage();
}

THUMB bool btl::BattleExecEscape::isEnd()
{
    if (BattleAutoFeed::isEndMessage()) {
        return true;
    }
    return false;
}

btl::BattleExecEscape btl::g_BattleExecEscape;
