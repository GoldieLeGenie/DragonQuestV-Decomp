#include "ov000/status/MonsterParty.hpp"

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline void status::CharacterStatus::setArrayIndex(int index) { arrayIndex_ = index; }
inline int status::MonsterStatus::getMonsterIndex() { return characterIndex_; }
inline int status::MonsterStatus::getMonsterGroup() { return characterGroup_; }
inline int status::MonsterStatus::getSortIndexInGroup() { return sortIndex_; }
inline int status::MonsterStatus::getCtrlId() { return ctrlId_; }

inline void status::MonsterStatus::setCtrlId(int ctrlId)
{
    ctrlId_ = ctrlId;
    haveStatusInfo_.setDrawCtrlId(ctrlId);
}

int status::MonsterParty::sortIndex_[4] = { -1, -1, -1, -1 };
THUMB status::MonsterParty::MonsterParty()
{
}

THUMB status::MonsterParty::~MonsterParty()
{
}

THUMB int status::MonsterParty::add(int monsterGroup, int monsterIndex, bool flag)
{
    int sortIndex = getSortIndex(monsterIndex);
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (!monster_[i].isEnable()) {
            monster_[i].setup(monsterGroup, monsterIndex, sortIndex);
            monster_[i].setArrayIndex(i);
            monster_[i].setCtrlId(i);
            return i;
        }
    }
    return -1;
}

THUMB void status::MonsterParty::del(int ctrl)
{
    if (monster_[ctrl].isEnable()) {
        monster_[ctrl].cleanup();
    }
}

THUMB void status::MonsterParty::clear()
{
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monster_[i].isEnable()) {
            del(i);
        }
    }
    dropItem_ = 0;
    dropFlag_ = 0;
}

THUMB int status::MonsterParty::getCount()
{
    monsterCount_ = 0;
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monster_[i].isEnable()) {
            monsterCount_++;
        }
    }
    return monsterCount_;
}

THUMB int status::MonsterParty::getBattleCount()
{
    monsterCount_ = 0;
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monster_[i].isBattleEnable()) {
            monsterCount_++;
        }
    }
    return monsterCount_;
}

THUMB int status::MonsterParty::getAliveCount()
{
    monsterCount_ = 0;
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monster_[i].isEnable() && !monster_[i].getHaveStatusInfo().isDeath()) {
            monsterCount_++;
        }
    }
    return monsterCount_;
}

THUMB int status::MonsterParty::getMonsterCountDeadOrAlive(int monsterIndex)
{
    int count = 0;
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monster_[i].isBeingEnable() && monsterIndex == monster_[i].getMonsterIndex()) {
            count++;
        }
    }
    return count;
}

THUMB int status::MonsterParty::getMonsterCountInGroup(int groupIndex)
{
    int count = 0;
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monster_[i].isBattleEnable() && groupIndex == monster_[i].getMonsterGroup()) {
            count++;
        }
    }
    return count;
}

THUMB int status::MonsterParty::getMonsterCountInGroupAlive(int groupIndex)
{
    int count = 0;
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monster_[i].isEnable() && !monster_[i].getHaveStatusInfo().isDeath() && groupIndex == monster_[i].getMonsterGroup()) {
            count++;
        }
    }
    if (count == 0) {
        sortIndex_[groupIndex] = -1;
        sortCount_[groupIndex] = 0;
    }
    return count;
}

THUMB status::MonsterStatus& status::MonsterParty::getMonsterInGroup(int groupIndex, int index)
{
    int count = 0;
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monster_[i].isBattleEnable() && groupIndex == monster_[i].getMonsterGroup()) {
            if (count == index) {
                return monster_[i];
            }
            count++;
        }
    }
    return monster_[0];
}

THUMB int status::MonsterParty::getMonsterIndexInGroup(int groupIndex)
{
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monster_[i].isBattleEnable() && groupIndex == monster_[i].getMonsterGroup()) {
            return monster_[i].getMonsterIndex();
        }
    }
    return -1;
}

THUMB int status::MonsterParty::getMonsterGroup(int index)
{
    int count = 0;
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monster_[i].isEnable()) {
            if (count == index) {
                return monster_[i].getMonsterGroup();
            }
            count++;
        }
    }
    return -1;
}

THUMB int status::MonsterParty::getMonsterIndex(int index)
{
    int count = 0;
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monster_[i].isEnable()) {
            if (count == index) {
                return monster_[i].getMonsterIndex();
            }
            count++;
        }
    }
    return -1;
}

THUMB status::MonsterStatus& status::MonsterParty::getMonsterStatus(int index)
{
    int count = 0;
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monster_[i].isEnable()) {
            if (count == index) {
                return monster_[i];
            }
            count++;
        }
    }
    return monster_[0];
}

THUMB int status::MonsterParty::getCtrlId(int index)
{
    int count = 0;
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (monster_[i].isEnable()) {
            if (count == index) {
                return monster_[i].getCtrlId();
            }
            count++;
        }
    }
    return -1;
}

THUMB int status::MonsterParty::getGroupCount()
{
    int group[4] = { 0, 0, 0, 0 };
    for (int i = 0; i < getCount(); i++) {
        int groupIndex = getMonsterGroup(i);
        if (groupIndex != -1) {
            group[groupIndex]++;
        }
    }
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (group[i] != 0) {
            count++;
        }
    }
    return count;
}

THUMB int status::MonsterParty::getMonsterGroupForMonsterIndex(int monsterIndex)
{
    int count = getCount();
    for (int i = 0; i < count; i++) {
        if (monsterIndex == getMonsterIndex(i)) {
            return getMonsterGroup(i);
        }
    }
    return -1;
}

THUMB int status::MonsterParty::getMonsterCallType()
{
    int index[4] = { -1, -1, -1, -1 };
    int count[4] = { 0, 0, 0, 0 };
    for (int i = 0; i < 4; i++) {
        count[i] = getMonsterCountInGroup(i);
        if (count[i] != 0) {
            index[i] = getMonsterIndexInGroup(i);
        }
    }
    if (index[0] != index[1] && index[1] != -1) {
        return 2;
    }
    if (index[1] != index[2] && index[2] != -1) {
        return 2;
    }
    if (index[1] != index[3] && index[3] != -1) {
        return 2;
    }
    if (index[0] == index[1] || index[0] == index[2] || index[0] == index[3]) {
        if (count[0] + count[1] + count[2] + count[3] >= 1) {
            return 1;
        }
    }
    if (index[1] == -1 && count[0] >= 2) {
        return 1;
    }
    return 0;
}

THUMB int status::MonsterParty::getMonsterCallIndex()
{
    int index[4] = { -1, -1, -1, -1 };
    int count[4] = { 0, 0, 0, 0 };
    for (int i = 0; i < 4; i++) {
        count[i] = getMonsterCountInGroup(i);
        if (count[i] != 0) {
            index[i] = getMonsterIndexInGroup(i);
        }
    }
    if (index[0] != index[1] && index[1] != -1) {
        return 0xf6;
    }
    if ((index[0] == index[1] || index[0] == index[2] || index[0] == index[3]) && count[0] + count[1] + count[2] + count[3] >= 1) {
        if (count[0] != 0) {
            return index[0];
        }
        if (count[1] != 0) {
            return index[1];
        }
        if (count[2] != 0) {
            return index[2];
        }
        if (count[3] != 0) {
            return index[3];
        }
    } else {
        if (index[1] == -1 && count[0] >= 2) {
            return index[0];
        }
        if (index[1] == -1 && count[0] == 1) {
            return index[0];
        }
    }
    return 0;
}

THUMB void status::MonsterParty::initializeSortIndex()
{
    for (int i = 0; i < 4; i++) {
        sortIndex_[i] = -1;
        sortCount_[i] = 0;
    }
}

THUMB int status::MonsterParty::getSortIndex(int monsterIndex)
{
    int index = 0;
    for (int i = 0; i < 4; i++) {
        if (monsterIndex == sortIndex_[i]) {
            index = getSortIndexInGroup(i);
            break;
        }
        if (sortIndex_[i] == -1) {
            sortIndex_[i] = monsterIndex;
            index = getSortIndexInGroup(i);
            break;
        }
    }
    return index;
}

THUMB int status::MonsterParty::getSortIndexInGroup(int index)
{
    int sort;
    for (int j = 0; j < 16; j++) {
        sort = sortCount_[index];
        if (isSortIndex(sort, sortIndex_[index])) {
            sortCount_[index]++;
            if (sortCount_[index] > 15) {
                sortCount_[index] = 0;
            }
        } else {
            sortCount_[index]++;
            if (sortCount_[index] > 15) {
                sortCount_[index] = 0;
            }
            break;
        }
    }
    return sort;
}

THUMB bool status::MonsterParty::isSortIndex(int sortIndex, int monsterIndex)
{
    int count = g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        if (monsterIndex == g_Monster.getMonsterStatus(i).getMonsterIndex() && sortIndex == g_Monster.getMonsterStatus(i).getSortIndexInGroup()) {
            return true;
        }
    }
    return false;
}
