#pragma ipa file
#include "main/status/PartyStatus.hpp"

inline bool status::HaveStatus::isBattleNpc() const
{
    return playerType_ == TYPE_BATTLENPC;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }

inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

inline bool status::HaveStatus::isNoBattleNpc() const
{
    return playerType_ == TYPE_NOBATTLENPC;
}

THUMB status::PartyStatusData::PartyStatusData()
{
}

THUMB status::PartyStatusData::~PartyStatusData()
{
}

THUMB void status::PartyStatusData::clear()
{
    for (int i = 0; i < 10; i++) {
        playerStatusFlag_[i].clear();
    }
    for (int i = 0; i < CARRIAGE_OUTSIDE_MAX; i++) {
        orderOutside_[i] = -1;
    }
    for (int i = 0; i < CARRIAGE_INSIDE_MAX; i++) {
        orderInside_[i] = -1;
    }
    for (int i = 0; i < CARRIAGE_BACKSIDE_MAX; i++) {
        orderBackside_[i] = -1;
    }
}

THUMB bool status::PartyStatusData::add(int playerIndex, bool flag)
{
    if (flag) {
        for (int i = 0; i < 8; i++) {
            if (!playerStatusFlag_[i].check(1)) {
                setPlayerStatus(i, playerIndex);
                return true;
            }
        }
    } else {
        for (int i = 8; i < 10; i++) {
            if (!playerStatusFlag_[i].check(1)) {
                setPlayerStatus(i, playerIndex);
                return true;
            }
        }
    }
    return false;
}

THUMB void status::PartyStatusData::del(int index)
{
    int ctrlIndex = getOrder(index);
    playerStatus_[ctrlIndex].cleanup();
    playerStatusFlag_[ctrlIndex].clear();
    delOrder(index);
}

THUMB void status::PartyStatusData::store(int index)
{
    int ctrlIndex = getOrder(index);
    playerStatus_[ctrlIndex].cleanup();
}

THUMB void status::PartyStatusData::setPlayerStatus(int index, int playerIndex)
{
    playerStatus_[index].setup(playerIndex);
    playerStatusFlag_[index].set(1);
    addOrder(index);
}

THUMB void status::PartyStatusData::addOrder(int ctrlIndex)
{
    if (isNormalNpc(ctrlIndex)) {
        for (int i = 0; i < CARRIAGE_BACKSIDE_MAX; i++) {
            if (orderBackside_[i] == -1) {
                orderBackside_[i] = ctrlIndex;
                return;
            }
        }
    }
    for (int i = 0; i < CARRIAGE_OUTSIDE_MAX; i++) {
        if (orderOutside_[i] == -1) {
            orderOutside_[i] = ctrlIndex;
            return;
        }
    }
    for (int i = 0; i < CARRIAGE_INSIDE_MAX; i++) {
        if (orderInside_[i] == -1) {
            orderInside_[i] = ctrlIndex;
            return;
        }
    }
}

THUMB void status::PartyStatusData::delOrder(int index)
{
    int idx = 0;
    int count0 = getOutsideCount();
    for (int i = 0; i < count0; i++) {
        if (idx == index) {
            orderOutside_[i] = -1;
        }
        idx++;
    }
    for (int i = 0; i < CARRIAGE_OUTSIDE_MAX - 1; i++) {
        if (orderOutside_[i] == -1) {
            dss::swap(&orderOutside_[i], &orderOutside_[i + 1]);
        }
    }
    int count1 = getInsideCount();
    for (int i = 0; i < count1; i++) {
        if (idx == index) {
            orderInside_[i] = -1;
        }
        idx++;
    }
    for (int i = 0; i < CARRIAGE_INSIDE_MAX - 1; i++) {
        if (orderInside_[i] == -1) {
            dss::swap(&orderInside_[i], &orderInside_[i + 1]);
        }
    }
    int count2 = getBackCount();
    for (int i = 0; i < count2; i++) {
        if (idx == index) {
            orderBackside_[i] = -1;
        }
        idx++;
    }
    for (int i = 0; i < CARRIAGE_BACKSIDE_MAX - 1; i++) {
        if (orderBackside_[i] == -1) {
            dss::swap(&orderBackside_[i], &orderBackside_[i + 1]);
        }
    }
}

THUMB int status::PartyStatusData::getOrder(int index)
{
    int temp[13] = { -1 };
    for (int i = 0; i < 13; i++) {
        temp[i] = -1;
    }
    int idx = 0;
    int count0 = getOutsideCount();
    for (int i = 0; i < count0; i++) {
        temp[idx] = orderOutside_[i];
        idx++;
    }
    int count1 = getInsideCount();
    for (int i = 0; i < count1; i++) {
        temp[idx] = orderInside_[i];
        idx++;
    }
    int count2 = getBackCount();
    for (int i = 0; i < count2; i++) {
        temp[idx] = orderBackside_[i];
        idx++;
    }
    return temp[index];
}

THUMB int status::PartyStatusData::getOutsideOrder(int index)
{
    return orderOutside_[index];
}

THUMB int status::PartyStatusData::getInsideOrder(int index)
{
    return orderInside_[index];
}

THUMB int status::PartyStatusData::getBacksideOrder(int index)
{
    return orderBackside_[index];
}

THUMB void status::PartyStatusData::reorder(int ctrl0, int ctrl1, int ctrl2, int ctrl3)
{
    int temp[4] = { -1, -1, -1, -1 };
    if (ctrl0 != -1) {
        temp[0] = getOrder(ctrl0);
    }
    if (ctrl1 != -1) {
        temp[1] = getOrder(ctrl1);
    }
    if (ctrl2 != -1) {
        temp[2] = getOrder(ctrl2);
    }
    if (ctrl3 != -1) {
        temp[3] = getOrder(ctrl3);
    }
    int temp2[7];
    for (int i = 0; i < 7; i++) {
        temp2[i] = -1;
    }
    int idx = 0;
    int count = getCountForReorder();
    for (int i = 0; i < count; i++) {
        int order = getOrder(i);
        if (temp[0] != order && temp[1] != order && temp[2] != order && temp[3] != order) {
            temp2[idx++] = order;
        }
    }
    for (int i = 0; i < CARRIAGE_OUTSIDE_MAX; i++) {
        orderOutside_[i] = temp[i];
    }
    for (int i = 0; i < CARRIAGE_INSIDE_MAX; i++) {
        orderInside_[i] = temp2[i];
    }
}

THUMB int status::PartyStatusData::getCount()
{
    int count = getOutsideCount();
    count += getInsideCount();
    return count + getBackCount();
}

THUMB int status::PartyStatusData::getCountForReorder()
{
    int count = getOutsideCount();
    return count + getInsideCount();
}

THUMB int status::PartyStatusData::getOutsideCount()
{
    int count = 0;
    for (int i = 0; i < CARRIAGE_OUTSIDE_MAX; i++) {
        if (orderOutside_[i] != -1) {
            count++;
        }
    }
    return count;
}

THUMB int status::PartyStatusData::getInsideCount()
{
    int count = 0;
    for (int i = 0; i < CARRIAGE_INSIDE_MAX; i++) {
        if (orderInside_[i] != -1) {
            count++;
        }
    }
    return count;
}

THUMB int status::PartyStatusData::getBackCount()
{
    int count = 0;
    for (int i = 0; i < CARRIAGE_BACKSIDE_MAX; i++) {
        if (orderBackside_[i] != -1) {
            count++;
        }
    }
    return count;
}

THUMB bool status::PartyStatusData::isCarriageOut(int ctrl)
{
    for (int i = 0; i < CARRIAGE_OUTSIDE_MAX; i++) {
        if (orderOutside_[i] != -1 && ctrl == orderOutside_[i]) {
            return true;
        }
    }
    return false;
}

THUMB bool status::PartyStatusData::isCarriageIn(int ctrl)
{
    for (int i = 0; i < CARRIAGE_INSIDE_MAX; i++) {
        if (orderInside_[i] != -1 && ctrl == orderInside_[i]) {
            return true;
        }
    }
    return false;
}

THUMB bool status::PartyStatusData::isCarriageBack(int ctrl)
{
    for (int i = 0; i < CARRIAGE_BACKSIDE_MAX; i++) {
        if (orderBackside_[i] != -1 && ctrl == orderBackside_[i]) {
            return true;
        }
    }
    return false;
}

THUMB bool status::PartyStatusData::isPlayer(int ctrl)
{
    if (getPlayerStatusForCtrl(ctrl).getHaveStatusInfo().getHaveStatus().isPlayer() != false) {
        return true;
    }
    return false;
}

THUMB bool status::PartyStatusData::isBattleNpc(int ctrl)
{
    if (getPlayerStatusForCtrl(ctrl).getHaveStatusInfo().getHaveStatus().isBattleNpc()) {
        return true;
    }
    return false;
}

THUMB bool status::PartyStatusData::isNormalNpc(int ctrl)
{
    if (getPlayerStatusForCtrl(ctrl).getHaveStatusInfo().getHaveStatus().isNoBattleNpc()) {
        return true;
    }
    return false;
}

THUMB status::PlayerStatus& status::PartyStatusData::getPlayerStatusForCtrl(int ctrl)
{
    return playerStatus_[ctrl];
}

THUMB void status::PartyStatusData::setOutsideOrder(int index, int val)
{
    orderOutside_[index] = val;
}

THUMB void status::PartyStatusData::setInsideOrder(int index, int val)
{
    orderInside_[index] = val;
}

THUMB void status::PartyStatusData::setBacksideOrder(int index, int val)
{
    orderBackside_[index] = val;
}
