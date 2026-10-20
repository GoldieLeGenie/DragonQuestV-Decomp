#pragma ipa file
#pragma thumb on
#include "main/status/PlayerData.hpp"
#include "main/text/TextAPI.hpp"

namespace dss {
    template <> unsigned int loop<unsigned int>(unsigned int x, unsigned int a, unsigned int b);
}

inline int status::PlayerData::getKindIndex()
{
    return kindIndex_;
}

status::PlayerData status::PlayerDataAll::playerData_[PLAYER_ALL_MAX];
dss::BitFlag<unsigned char> status::PlayerDataAll::playerFlag_[PLAYER_ALL_MAX];

THUMB void status::PlayerDataAll::initialize(bool flag)
{
    for (int i = 0; i < 88; i++) {
        nameIndex_[i] = 0;
    }
    if (flag) {
        TextAPI::Init();
        TextAPI::update();
    }
    for (int i = 1; i < 16; i++) {
        playerData_[i].setup(flag, i, i, 0);
    }
    for (int i = 0; i < 72; i++) {
        int kind = i + 16;
        int ctrl = getCtrlFromFriendMonsterIndex(kind);
        playerData_[ctrl].setup(flag, kind, ctrl, 0);
        playerData_[ctrl + 1].setup(flag, kind, ctrl + 1, 1);
        playerData_[ctrl + 2].setup(flag, kind, ctrl + 2, 2);
    }
    for (int i = 0; i < PLAYER_ALL_MAX; i++) {
        playerFlag_[i].clear();
    }
    if (flag) {
        TextAPI::terminate();
    }
}

unsigned char status::PlayerDataAll::nameIndex_[PLAYER_ALL_MAX];

THUMB int status::PlayerDataAll::getCtrlFromFriendMonsterIndex(int playerIndex)
{
    return (playerIndex - 16) * 3 + 16;
}

THUMB unsigned int status::PlayerDataAll::getStartIndexForName(int index)
{
    int temp = nameIndex_[index];
    return (temp >> 4) & 0xf;
}

THUMB unsigned int status::PlayerDataAll::getUseFlagForName(int index)
{
    int temp = nameIndex_[index];
    return temp & 0xf;
}

THUMB void status::PlayerDataAll::setStartIndexUseFlagForName(int index, unsigned int startIndex, unsigned int useFlag)
{
    unsigned int temp = (startIndex << 4) + useFlag;
    nameIndex_[index] = temp;
}

THUMB int status::PlayerDataAll::getNextAddFriendMonster(int playerKindIndex)
{
    int index = getCtrlFromFriendMonsterIndex(playerKindIndex);
    int friendNameIndex = 0;
    unsigned int startIndex = getStartIndexForName(playerKindIndex);
    unsigned int useFlag = getUseFlagForName(playerKindIndex);
    for (int i = 0; i < 4; i++) {
        if (!((1 << startIndex) & useFlag)) {
            friendNameIndex = startIndex;
            break;
        }
        startIndex = dss::loop<unsigned int>(startIndex + 1, 0, 3);
    }
    dss::loop<unsigned int>(startIndex + 1, 0, 3);
    if (!isFriendMonsterFlag(index)) {
        playerData_[index].setupNameId(playerKindIndex, friendNameIndex);
        playerData_[index].setFriendMonsterNameIndex(friendNameIndex, true);
        return index;
    }
    if (!isFriendMonsterFlag(index + 1)) {
        playerData_[index + 1].setupNameId(playerKindIndex, friendNameIndex);
        playerData_[index + 1].setFriendMonsterNameIndex(friendNameIndex, true);
        return index + 1;
    }
    if (!isFriendMonsterFlag(index + 2)) {
        playerData_[index + 2].setupNameId(playerKindIndex, friendNameIndex);
        playerData_[index + 2].setFriendMonsterNameIndex(friendNameIndex, true);
        return index + 2;
    }
    return -1;
}

template <> THUMB unsigned int dss::loop<unsigned int>(unsigned int x, unsigned int a, unsigned int b)
{
    if (x > b) {
        return a;
    }
    if (x < a) {
        return b;
    }
    return x;
}

THUMB int status::PlayerDataAll::addFriendMonster(int playerKindIndex)
{
    int index = getCtrlFromFriendMonsterIndex(playerKindIndex);
    int friendNameIndex = 0;
    unsigned int startIndex = getStartIndexForName(playerKindIndex);
    unsigned int useFlag = getUseFlagForName(playerKindIndex);
    for (int i = 0; i < 4; i++) {
        if (!(useFlag & (1 << startIndex))) {
            useFlag |= 1 << startIndex;
            friendNameIndex = startIndex;
            break;
        }
        startIndex = dss::loop<unsigned int>(startIndex + 1, 0, 3);
    }
    setStartIndexUseFlagForName(playerKindIndex, dss::loop<unsigned int>(startIndex + 1, 0, 3), useFlag);
    if (!isFriendMonsterFlag(index)) {
        playerData_[index].setupNameId(playerKindIndex, friendNameIndex);
        setFriendMonsterFlag(index, true);
        playerData_[index].setFriendMonsterNameIndex(friendNameIndex, true);
        return index;
    }
    if (!isFriendMonsterFlag(index + 1)) {
        playerData_[index + 1].setupNameId(playerKindIndex, friendNameIndex);
        setFriendMonsterFlag(index + 1, true);
        playerData_[index + 1].setFriendMonsterNameIndex(friendNameIndex, true);
        return index + 1;
    }
    if (!isFriendMonsterFlag(index + 2)) {
        playerData_[index + 2].setupNameId(playerKindIndex, friendNameIndex);
        setFriendMonsterFlag(index + 2, true);
        playerData_[index + 2].setFriendMonsterNameIndex(friendNameIndex, true);
        return index + 2;
    }
    return -1;
}

THUMB void status::PlayerDataAll::delFriendMonster(int index)
{
    setFriendMonsterFlag(index, false);
    int kind = playerData_[index].getKindIndex();
    unsigned int startIndex = getStartIndexForName(kind);
    unsigned int useFlag = getUseFlagForName(kind);
    int friendNameIndex = playerData_[index].getFriendMonsterNameIndex();
    useFlag &= ~(1 << friendNameIndex);
    setStartIndexUseFlagForName(kind, startIndex, useFlag);
    playerData_[index].setFriendMonsterNameIndex(-1, false);
    if (kind != 0x11 && kind != 0x10) {
        setupFriendMonster(index);
    }
}

THUMB int status::PlayerDataAll::getFriendMonsterCount()
{
    int count = 0;
    for (int i = 0; i < PLAYER_ALL_MAX; i++) {
        if (isFriendMonsterFlag(i)) {
            count++;
        }
    }
    return count;
}

THUMB int status::PlayerDataAll::getFriendMonsterCountWithoutEventMonster()
{
    int count = 0;
    for (int i = 0; i < PLAYER_ALL_MAX; i++) {
        int index = getCtrlFromFriendMonsterIndex(0x10);
        if (index == i || index + 1 == i || index + 2 == i) {
            continue;
        }
        index = getCtrlFromFriendMonsterIndex(0x11);
        if (index == i || index + 1 == i || index + 2 == i) {
            continue;
        }
        index = getCtrlFromFriendMonsterIndex(0x52);
        if (index == i || index + 1 == i || index + 2 == i) {
            continue;
        }
        index = getCtrlFromFriendMonsterIndex(0x3a);
        if (index == i || index + 1 == i || index + 2 == i) {
            continue;
        }
        index = getCtrlFromFriendMonsterIndex(0x3b);
        if (index == i || index + 1 == i || index + 2 == i) {
            continue;
        }
        if (isFriendMonsterFlag(i)) {
            count++;
        }
    }
    return count;
}

THUMB int status::PlayerDataAll::getFriendMonsterCtrl(int index)
{
    int count = 0;
    for (int i = 0; i < PLAYER_ALL_MAX; i++) {
        if (isFriendMonsterFlag(i)) {
            if (index == count) {
                return i;
            }
            count++;
        }
    }
    return -1;
}

THUMB int status::PlayerDataAll::getFriendMonsterCountInMonster(int playerKindIndex)
{
    int index = getCtrlFromFriendMonsterIndex(playerKindIndex);
    int count = 0;
    if (isFriendMonsterFlag(index)) {
        count++;
    }
    if (isFriendMonsterFlag(index + 1)) {
        count++;
    }
    if (isFriendMonsterFlag(index + 2)) {
        count++;
    }
    return count;
}

THUMB void status::PlayerDataAll::setupFriendMonster(int index)
{
    int kind = playerData_[index].getKindIndex();
    playerData_[index].setup(false, kind, index, 0);
}

THUMB int status::PlayerDataAll::getMonsterCountInOldMan()
{
    int count = 0;
    for (int i = 0; i < PLAYER_ALL_MAX; i++) {
        if (isMonsterOldManFlag(i)) {
            count++;
        }
    }
    return count;
}

THUMB int status::PlayerDataAll::getMonsterCtrlInOldMan(int index)
{
    int count = 0;
    for (int i = 0; i < PLAYER_ALL_MAX; i++) {
        if (isMonsterOldManFlag(i)) {
            if (index == count) {
                return i;
            }
            count++;
        }
    }
    return -1;
}

THUMB int status::PlayerDataAll::getPlayerCountInRuida()
{
    int count = 0;
    for (int i = 0; i < PLAYER_ALL_MAX; i++) {
        if (isRuidaFlag(i)) {
            count++;
        }
    }
    return count;
}

THUMB int status::PlayerDataAll::getPlayerCtrlInRuida(int index)
{
    int count = 0;
    for (int i = 0; i < PLAYER_ALL_MAX; i++) {
        if (isRuidaFlag(i)) {
            if (index == count) {
                return i;
            }
            count++;
        }
    }
    return -1;
}

THUMB void status::PlayerDataAll::setFriendMonsterFlag(int index, bool flag)
{
    if (flag) {
        playerFlag_[index].set(FLAG_FRIEND_MONSTER);
    } else {
        playerFlag_[index].remove(FLAG_FRIEND_MONSTER);
    }
}

THUMB bool status::PlayerDataAll::isFriendMonsterFlag(int index)
{
    return playerFlag_[index].check(FLAG_FRIEND_MONSTER);
}

THUMB void status::PlayerDataAll::setRuidaFlag(int index, bool flag)
{
    if (flag) {
        playerFlag_[index].set(FLAG_RUIDA);
    } else {
        playerFlag_[index].remove(FLAG_RUIDA);
    }
}

THUMB bool status::PlayerDataAll::isRuidaFlag(int index)
{
    return playerFlag_[index].check(FLAG_RUIDA);
}

THUMB void status::PlayerDataAll::setMonsterOldManFlag(int index, bool flag)
{
    if (flag) {
        playerFlag_[index].set(FLAG_MONSTER_OLDMAN);
    } else {
        playerFlag_[index].remove(FLAG_MONSTER_OLDMAN);
    }
}

THUMB bool status::PlayerDataAll::isMonsterOldManFlag(int index)
{
    return playerFlag_[index].check(FLAG_MONSTER_OLDMAN);
}
