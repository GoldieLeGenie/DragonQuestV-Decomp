#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/StageAttribute.hpp"

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

status::PartyStatus status::g_Party;

THUMB status::PartyStatus::PartyStatus()
{
    initialize();
}

THUMB status::PartyStatus::~PartyStatus()
{
}

THUMB void status::PartyStatus::initialize()
{
    partyStatusData_.clear();
    accessFlag_.clear();
    sugorokuMode_ = false;
}

THUMB void status::PartyStatus::add(int index, bool flag)
{
    if (index == 0) {
        return;
    }
    if (index >= 16) {
        PlayerDataAll::setFriendMonsterFlag(index, true);
    }
    bool ret;
    if (index == 8) {
        ret = partyStatusData_.add(index, false);
    } else if (index == 14) {
        ret = partyStatusData_.add(index, false);
    } else {
        ret = partyStatusData_.add(index, flag);
        if (!ret) {
            ret = partyStatusData_.add(index, false);
        }
    }
    if (ret) {
        return;
    }
}

THUMB void status::PartyStatus::addNpc(int charaIndex)
{
    add(8, false);
    int count = partyStatusData_.getBackCount();
    for (int i = 0; i < count; i++) {
        int ctrl = partyStatusData_.getBacksideOrder(i);
        if (ctrl != -1) {
            PlayerStatus& player = partyStatusData_.getPlayerStatusForCtrl(ctrl);
            if (player.haveStatusInfo_.haveStatus_.playerIndex_ == 8 && player.haveStatusInfo_.haveStatus_.getCharaIndex() == 61) {
                player.haveStatusInfo_.haveStatus_.setCharaIndex(charaIndex);
                return;
            }
        }
    }
}

THUMB void status::PartyStatus::del(int ctrlIndex)
{
    partyStatusData_.del(ctrlIndex);
}

THUMB void status::PartyStatus::clear()
{
    while (true) {
        int count = partyStatusData_.getCount();
        if (count == 0) {
            break;
        }
        del(0);
    }
    accessFlag_.clear();
    sugorokuMode_ = false;
}

THUMB void status::PartyStatus::store()
{
    int count = partyStatusData_.getCount();
    for (int i = 0; i < count; i++) {
        partyStatusData_.store(i);
    }
}

THUMB void status::PartyStatus::reorder(int a, int b, int c, int d)
{
    partyStatusData_.reorder(a, b, c, d);
}

THUMB int status::PartyStatus::getPlayerIndex(int index)
{
    return getPlayerStatus(index).haveStatusInfo_.haveStatus_.playerIndex_;
}

THUMB int status::PartyStatus::getNpcPlayerIndex()
{
    int count = 0;
    for (int i = 0; i < partyCount_; i++) {
        if (getPlayerStatus(i).haveStatusInfo_.haveStatus_.playerType_ == HaveStatus::TYPE_NOBATTLENPC) {
            count = i;
            break;
        }
    }
    if (count == 0) {
        return 8;
    }
    int npcNo = 8;
    switch (getPlayerStatus(count).haveStatusInfo_.haveStatus_.getCharaIndex()) {
        case 0x21:
            npcNo = 15;
            break;
        case 0xd3:
        case 0xd4:
            npcNo = 4;
            break;
        case 0xdb:
            npcNo = 6;
            break;
        case 0xe1:
            npcNo = 9;
            break;
        case 0xe3:
            npcNo = 5;
            break;
        case 0xe7:
            npcNo = 10;
            break;
        case 0x19c:
            npcNo = 16;
            break;
    }
    return npcNo;
}

THUMB status::PlayerStatus& status::PartyStatus::getPlayerStatus(int index)
{
    return partyStatusData_.getPlayerStatusForCtrl(party_[index]);
}

THUMB status::PlayerStatus& status::PartyStatus::getPlayerStatusForPlayerIndex(int playerIndex)
{
    for (int i = 0; i < partyCount_; i++) {
        if (playerIndex == partyStatusData_.getPlayerStatusForCtrl(party_[i]).haveStatusInfo_.haveStatus_.getPlayerIndex()) {
            return partyStatusData_.getPlayerStatusForCtrl(party_[i]);
        }
    }
    return partyStatusData_.getPlayerStatusForCtrl(0);
}

THUMB bool status::PartyStatus::isInsideCarriage(int index)
{
    if (index >= partyStatusData_.getOutsideCount()) {
        return true;
    }
    return false;
}

THUMB bool status::PartyStatus::isOutsideCarriage(int index)
{
    if (index < partyStatusData_.getOutsideCount()) {
        return true;
    }
    return false;
}

THUMB bool status::PartyStatus::isInsideCarriageForPlayerIndex(int playerIndex)
{
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.isOutsideCarriage(i) && playerIndex == g_Party.getPlayerStatus(i).haveStatusInfo_.haveStatus_.getPlayerIndex()) {
            return true;
        }
    }
    return false;
}

THUMB int status::PartyStatus::getSortIndex(int playerIndex)
{
    int count = getCount();
    for (int i = 0; i < count; i++) {
        if (playerIndex == getPlayerStatus(i).haveStatusInfo_.haveStatus_.getPlayerIndex()) {
            return i;
        }
    }
    return -1;
}

THUMB void status::PartyStatus::setNormalMode()
{
    accessFlag_.clear();
    accessFlag_.set(FLAG_PLAYER | FLAG_BATTLE_NPC | FLAG_NORMAL_NPC);
    setParty();
}

THUMB bool status::PartyStatus::isNormalMode()
{
    if (!accessFlag_.check(FLAG_PLAYER)) {
        return false;
    }
    if (!accessFlag_.check(FLAG_BATTLE_NPC)) {
        return false;
    }
    if (!accessFlag_.check(FLAG_NORMAL_NPC)) {
        return false;
    }
    return true;
}

THUMB void status::PartyStatus::setPlayerMode()
{
    accessFlag_.clear();
    accessFlag_.set(FLAG_PLAYER);
    setParty();
}

THUMB bool status::PartyStatus::isPlayerMode()
{
    if (!accessFlag_.check(FLAG_PLAYER)) {
        return false;
    }
    if (accessFlag_.check(FLAG_BATTLE_NPC)) {
        return false;
    }
    if (accessFlag_.check(FLAG_NORMAL_NPC)) {
        return false;
    }
    return true;
}

THUMB void status::PartyStatus::setBattleMode()
{
    accessFlag_.clear();
    accessFlag_.set(FLAG_PLAYER | FLAG_BATTLE_NPC);
    setParty();
}

THUMB bool status::PartyStatus::isBattleMode()
{
    if (!accessFlag_.check(FLAG_PLAYER)) {
        return false;
    }
    if (!accessFlag_.check(FLAG_BATTLE_NPC)) {
        return false;
    }
    if (accessFlag_.check(FLAG_NORMAL_NPC)) {
        return false;
    }
    if (accessFlag_.check(FLAG_BATTLE_NPC_CARRIAGE)) {
        return false;
    }
    return true;
}

THUMB void status::PartyStatus::setBattleModeWithCarriage()
{
    accessFlag_.clear();
    accessFlag_.set(FLAG_PLAYER | FLAG_BATTLE_NPC | FLAG_BATTLE_NPC_CARRIAGE);
    setParty();
}

THUMB bool status::PartyStatus::isBattleModeWithCarriage()
{
    if (!accessFlag_.check(FLAG_PLAYER)) {
        return false;
    }
    if (!accessFlag_.check(FLAG_BATTLE_NPC)) {
        return false;
    }
    if (!accessFlag_.check(FLAG_BATTLE_NPC_CARRIAGE)) {
        return false;
    }
    if (accessFlag_.check(FLAG_NORMAL_NPC)) {
        return false;
    }
    return true;
}

THUMB void status::PartyStatus::setBattleModeAndCarriage()
{
    accessFlag_.clear();
    accessFlag_.set(FLAG_PLAYER | FLAG_BATTLE_NPC | FLAG_BATTLE_NPC_IN_CARRIAGE);
    setParty();
}

THUMB bool status::PartyStatus::isBattleModeAndCarriage()
{
    if (!accessFlag_.check(FLAG_PLAYER)) {
        return false;
    }
    if (!accessFlag_.check(FLAG_BATTLE_NPC)) {
        return false;
    }
    if (!accessFlag_.check(FLAG_BATTLE_NPC_IN_CARRIAGE)) {
        return false;
    }
    if (accessFlag_.check(FLAG_NORMAL_NPC)) {
        return false;
    }
    return true;
}

THUMB void status::PartyStatus::setDisplayMode()
{
    accessFlag_.clear();
    accessFlag_.set(FLAG_DISPLAY);
    setParty();
}

THUMB bool status::PartyStatus::isDisplayMode()
{
    return accessFlag_.check(FLAG_DISPLAY);
}

THUMB void status::PartyStatus::setMemberShiftMode()
{
    accessFlag_.clear();
    accessFlag_.set(FLAG_MEMBER_SHIFT);
    setParty();
}

THUMB bool status::PartyStatus::isMemberShiftMode()
{
    if (!accessFlag_.check(FLAG_MEMBER_SHIFT)) {
        return false;
    }
    return true;
}

THUMB void status::PartyStatus::setAllPlayerMode()
{
    accessFlag_.clear();
    accessFlag_.set(FLAG_ALL_PLAYER);
    setParty();
}

THUMB bool status::PartyStatus::isAllPlayerMode()
{
    if (!accessFlag_.check(FLAG_ALL_PLAYER)) {
        return false;
    }
    return true;
}

THUMB int status::PartyStatus::isSugorokuMode()
{
    return sugorokuMode_;
}

THUMB void status::PartyStatus::setAccessMode(unsigned int mode)
{
    accessFlag_.clear();
    accessFlag_.set(mode);
    setParty();
}

THUMB unsigned int status::PartyStatus::getAccessMode()
{
    return accessFlag_.flag_;
}

THUMB void status::PartyStatus::setParty()
{
    for (int i = 0; i < 10; i++) {
        party_[i] = -1;
    }
    setPartyMemberShiftMode();
    setPartyDisplayMode();
    setPartyNormalMode();
    setPartyBattleModeWithCarriage();
    setPartyBattleModeAndCarriage();
    setPartyBattleMode();
    setPartyPlayerMode();
    setPartyAllPlayerMode();
    setPartySugorokuMode();
    partyCount_ = 0;
    for (int i = 0; i < 10; i++) {
        if (party_[i] != -1) {
            partyCount_++;
        }
    }
}

THUMB void status::PartyStatus::setPartyPlayerMode()
{
    if (!isPlayerMode()) {
        return;
    }
    int index = 0;
    int count = partyStatusData_.getOutsideCount();
    for (int i = 0; i < count; i++) {
        int ctrl = partyStatusData_.getOutsideOrder(i);
        if (ctrl != -1 && partyStatusData_.isPlayer(ctrl)) {
            party_[index++] = ctrl;
        }
    }
    if (carriage_ && g_StageAttribute.isCarriageEnable()) {
        count = partyStatusData_.getInsideCount();
        for (int i = 0; i < count; i++) {
            int ctrl = partyStatusData_.getInsideOrder(i);
            if (ctrl != -1 && partyStatusData_.isPlayer(ctrl)) {
                party_[index++] = ctrl;
            }
        }
    }
}

THUMB void status::PartyStatus::setPartyBattleMode()
{
    if (!isBattleMode()) {
        return;
    }
    int index = 0;
    int count = partyStatusData_.getOutsideCount();
    for (int i = 0; i < count; i++) {
        int ctrl = partyStatusData_.getOutsideOrder(i);
        if (ctrl != -1 && (partyStatusData_.isPlayer(ctrl) || partyStatusData_.isBattleNpc(ctrl))) {
            party_[index++] = ctrl;
        }
    }
    if (carriage_ && g_StageAttribute.isCarriageEnable()) {
        count = partyStatusData_.getInsideCount();
        for (int i = 0; i < count; i++) {
            int ctrl = partyStatusData_.getInsideOrder(i);
            if (ctrl != -1 && (partyStatusData_.isPlayer(ctrl) || partyStatusData_.isBattleNpc(ctrl))) {
                party_[index++] = ctrl;
            }
        }
    }
    partyCount_ = index;
}

THUMB void status::PartyStatus::setPartyBattleModeWithCarriage()
{
    if (!isBattleModeWithCarriage()) {
        return;
    }
    int index = 0;
    int count = partyStatusData_.getOutsideCount();
    for (int i = 0; i < count; i++) {
        int ctrl = partyStatusData_.getOutsideOrder(i);
        if (ctrl != -1 && (partyStatusData_.isPlayer(ctrl) || partyStatusData_.isBattleNpc(ctrl))) {
            party_[index++] = ctrl;
        }
    }
    if (carriage_ && g_StageAttribute.isCarriageEnable() && g_StageAttribute.isCarriageEnter()) {
        count = partyStatusData_.getInsideCount();
        for (int i = 0; i < count; i++) {
            int ctrl = partyStatusData_.getInsideOrder(i);
            if (ctrl != -1 && (partyStatusData_.isPlayer(ctrl) || partyStatusData_.isBattleNpc(ctrl))) {
                party_[index++] = ctrl;
            }
        }
    }
    partyCount_ = index;
}

THUMB void status::PartyStatus::setPartyBattleModeAndCarriage()
{
    if (!isBattleModeAndCarriage()) {
        return;
    }
    int index = 0;
    int count = partyStatusData_.getOutsideCount();
    for (int i = 0; i < count; i++) {
        int ctrl = partyStatusData_.getOutsideOrder(i);
        if (ctrl != -1 && (partyStatusData_.isPlayer(ctrl) || partyStatusData_.isBattleNpc(ctrl))) {
            party_[index++] = ctrl;
        }
    }
    if (carriage_) {
        count = partyStatusData_.getInsideCount();
        for (int i = 0; i < count; i++) {
            int ctrl = partyStatusData_.getInsideOrder(i);
            if (ctrl != -1 && (partyStatusData_.isPlayer(ctrl) || partyStatusData_.isBattleNpc(ctrl))) {
                party_[index++] = ctrl;
            }
        }
    }
    partyCount_ = index;
}

THUMB void status::PartyStatus::setPartyMemberShiftMode()
{
    if (!isMemberShiftMode()) {
        return;
    }
    int index = 0;
    int count = partyStatusData_.getOutsideCount();
    for (int i = 0; i < count; i++) {
        int ctrl = partyStatusData_.getOutsideOrder(i);
        if (ctrl != -1 && (partyStatusData_.isPlayer(ctrl) || partyStatusData_.isBattleNpc(ctrl))) {
            party_[index++] = ctrl;
        }
    }
    if (carriage_ && g_StageAttribute.isCarriageEnable() && g_StageAttribute.isCarriageEnter()) {
        count = partyStatusData_.getInsideCount();
        for (int i = 0; i < count; i++) {
            int ctrl = partyStatusData_.getInsideOrder(i);
            if (ctrl != -1 && (partyStatusData_.isPlayer(ctrl) || partyStatusData_.isBattleNpc(ctrl))) {
                party_[index++] = ctrl;
            }
        }
    }
    partyCount_ = index;
}

THUMB void status::PartyStatus::setPartyNormalMode()
{
    if (!isNormalMode()) {
        return;
    }
    int index = 0;
    int count = partyStatusData_.getOutsideCount();
    for (int i = 0; i < count; i++) {
        int ctrl = partyStatusData_.getOutsideOrder(i);
        if (ctrl != -1 && (partyStatusData_.isPlayer(ctrl) || partyStatusData_.isBattleNpc(ctrl))) {
            party_[index++] = ctrl;
        }
    }
    if (carriage_ && g_StageAttribute.isCarriageEnable()) {
        count = partyStatusData_.getInsideCount();
        for (int i = 0; i < count; i++) {
            int ctrl = partyStatusData_.getInsideOrder(i);
            if (ctrl != -1 && (partyStatusData_.isPlayer(ctrl) || partyStatusData_.isBattleNpc(ctrl))) {
                party_[index++] = ctrl;
            }
        }
    }
    partyCount_ = index;
}

THUMB void status::PartyStatus::setPartyDisplayMode()
{
    if (!isDisplayMode()) {
        return;
    }
    int index = 0;
    int count = partyStatusData_.getOutsideCount();
    for (int i = 0; i < count; i++) {
        int ctrl = partyStatusData_.getOutsideOrder(i);
        if (ctrl != -1 && !partyStatusData_.getPlayerStatusForCtrl(ctrl).haveStatusInfo_.isDeath()) {
            if (partyStatusData_.isPlayer(ctrl) || partyStatusData_.isBattleNpc(ctrl) || partyStatusData_.isNormalNpc(ctrl)) {
                party_[index++] = ctrl;
            }
        }
    }
    for (int i = 0; i < count; i++) {
        int ctrl = partyStatusData_.getOutsideOrder(i);
        if (ctrl != -1 && partyStatusData_.getPlayerStatusForCtrl(ctrl).haveStatusInfo_.isDeath()) {
            if (partyStatusData_.isPlayer(ctrl) || partyStatusData_.isBattleNpc(ctrl)) {
                party_[index++] = ctrl;
            }
        }
    }
    count = partyStatusData_.getBackCount();
    for (int i = 0; i < count; i++) {
        int ctrl = partyStatusData_.getBacksideOrder(i);
        if (ctrl != -1 && partyStatusData_.isNormalNpc(ctrl)) {
            party_[index++] = ctrl;
        }
    }
}

THUMB void status::PartyStatus::setPartyAllPlayerMode()
{
    if (!isAllPlayerMode()) {
        return;
    }
    int index = 0;
    int count = partyStatusData_.getCount();
    for (int i = 0; i < count; i++) {
        party_[index++] = partyStatusData_.getOrder(i);
    }
    partyCount_ = index;
}

THUMB void status::PartyStatus::setPartySugorokuMode()
{
    if (!isSugorokuMode()) {
        return;
    }
    for (int i = 0; i < 10; i++) {
        party_[i] = -1;
    }
    int index = 0;
    int count = partyStatusData_.getCount();
    for (int i = 0; i < count; i++) {
        int ctrl = partyStatusData_.getOrder(i);
        if (ctrl != -1 && !partyStatusData_.getPlayerStatusForCtrl(ctrl).haveStatusInfo_.isDeath() && partyStatusData_.isPlayer(ctrl)) {
            index++;
            party_[0] = ctrl;
            break;
        }
    }
    partyCount_ = index;
}

THUMB int status::PartyStatus::getCount()
{
    return partyCount_;
}

THUMB int status::PartyStatus::getCarriageCount()
{
    return partyStatusData_.getInsideCount();
}

THUMB int status::PartyStatus::getCarriageOutCount()
{
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (party_[i] != -1) {
            if (partyStatusData_.isCarriageOut(party_[i])) {
                count++;
            }
            if (partyStatusData_.isCarriageBack(party_[i])) {
                count++;
            }
        }
    }
    return count;
}

THUMB int status::PartyStatus::getCarriageOutAliveCount()
{
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (party_[i] != -1 && !partyStatusData_.getPlayerStatusForCtrl(i).haveStatusInfo_.isDeath()) {
            if (partyStatusData_.isCarriageOut(party_[i])) {
                count++;
            }
            if (partyStatusData_.isCarriageBack(party_[i])) {
                count++;
            }
        }
    }
    return count;
}

THUMB int status::PartyStatus::getCarriageAliveCount()
{
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (party_[i] != -1 && !partyStatusData_.getPlayerStatusForCtrl(i).haveStatusInfo_.isDeath()) {
            if (partyStatusData_.isCarriageIn(party_[i])) {
                count++;
            }
        }
    }
    return count;
}
