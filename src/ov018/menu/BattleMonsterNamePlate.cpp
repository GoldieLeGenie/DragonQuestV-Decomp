#pragma ipa file
#include "ov018/menu/BattleMonsterNamePlate.hpp"
#include "ov000/btl/BattleMonsterMask.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/leveldata/MonsterData.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/text/TextAPI.hpp"

inline int status::CharacterStatus::getGroupIndex() { return characterGroup_; }
inline int status::MonsterStatus::getMonsterGroup() { return characterGroup_; }
inline int status::MonsterStatus::getMonsterIndex() { return characterIndex_; }
inline int status::MonsterStatus::getMosyasIndex() { return mosyasIndex_; }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline char dq5::level::MonsterData::getPosition() { return byte_1 & 0x1; }
inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index)
{
    return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

BattleMonsterNamePlate BattleMonsterNamePlate::m_singleton;

THUMB BattleMonsterNamePlate& BattleMonsterNamePlate::getSingleton()
{
    return m_singleton;
}

THUMB void BattleMonsterNamePlate::init()
{
    addCount_ = 0;
    for (int i = 0; i < 4; i++) {
        monsterData_[i].index = 0;
        monsterData_[i].name = 0;
        monsterData_[i].num = 0;
        monsterData_[i].drawID = 0;
        monsterData_[i].group = 0;
        monsterData_[i].center = 0;
        monsterData_[i].leng = 0;
        monsterData_[i].height = 0;
        monsterData_[i].flying = 0;
        sortList_[i] = 0;
    }
}

THUMB void BattleMonsterNamePlate::setMonster()
{
    addCount_ = 0;
    for (int i = 0; i < 4; i++) {
        monsterData_[i].name = -1;
        monsterData_[i].num = -1;
        monsterData_[i].center = -1;
        monsterData_[i].leng = -1;
        monsterData_[i].height = 0;
        monsterData_[i].drawID = -1;
        monsterData_[i].flying = 0;
    }
    int groupList[4] = {0, 0, 0, 0};
    for (int i = 0; i < status::g_Monster.getCount(); i++) {
        if (status::g_Monster.getMonsterStatus(i).isBattleEnable()) {
            groupList[status::g_Monster.getMonsterStatus(i).getGroupIndex()]++;
        }
    }
    int groupCount = 0;
    for (int i = 0; i < 4; i++) {
        if (groupList[i] > 0) {
            groupCount++;
        }
    }
    int group = 0;
    int flyFlag_ = false;
    int randFlag_ = false;
    for (; addCount_ < groupCount; group++) {
        int debug = 0;
        for (int monster = 0; monster < status::g_Monster.getCount(); monster++) {
            if (group == status::g_Monster.getMonsterGroup(monster) && status::g_Monster.getMonsterStatus(monster).isBattleEnable()) {
                debug++;
            }
        }
        if (debug > 0) {
            int monsterCount = seekMonster(group);
            if (monsterCount != -1) {
                setMonsterParameter(group, monsterCount);
                if (monsterData_[addCount_].flying) {
                    flyFlag_ = true;
                }
                if (!monsterData_[addCount_].flying) {
                    randFlag_ = true;
                }
                addCount_++;
            }
        }
    }
    flyAndRand_ = flyFlag_ & randFlag_;
    sortPosition();
}

THUMB BattleMonsterNamePlate::Monster_DATA& BattleMonsterNamePlate::getMonsterData(int index)
{
    return monsterData_[index];
}

THUMB int BattleMonsterNamePlate::seekMonster(int group)
{
    int monsterCount = status::g_Monster.getCount();
    for (int i = 0; i < monsterCount; i++) {
        if (group == status::g_Monster.getMonsterStatus(i).getMonsterGroup() && status::g_Monster.getMonsterStatus(i).isBattleEnable()) {
            return i;
        }
    }
    return -1;
}

THUMB void BattleMonsterNamePlate::setMonsterParameter(int group, int monsterCount)
{
    char text[MAX_STRING_SIZE];
    int* rect = btl::BattleMonsterMask::getSingleton()->getMonsterTouchRect(monsterCount);
    int index = status::g_Monster.getMonsterStatus(monsterCount).getMonsterIndex();
    monsterData_[addCount_].name = status::g_Monster.getMonsterIndex(monsterCount);
    monsterData_[addCount_].index = monsterCount;
    monsterData_[addCount_].num = 0;
    monsterData_[addCount_].group = rect[0];
    for (int i = 0; i < status::g_Monster.getCount(); i++) {
        if (rect[0] == status::g_Monster.getMonsterGroup(i) && status::g_Monster.getMonsterStatus(i).isBattleEnable()) {
            monsterData_[addCount_].num++;
        }
    }
    if (status::g_Monster.getMonsterStatus(monsterCount).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU)) {
        TextAPI::getPlayerNamePlateTextImitation(text, status::g_Monster.getMonsterStatus(monsterCount).getMosyasIndex(), monsterData_[addCount_].num);
    } else {
        TextAPI::getMonsterNamePlateTextImitation(text, monsterData_[addCount_].name, monsterData_[addCount_].num);
    }
    monsterData_[addCount_].leng = setNamePlateText(addCount_, text);
    monsterData_[addCount_].height = rect[2];
    monsterData_[addCount_].drawID = (addCount_ == 0) ? 1 : 2;
    if (dq5::level::MonsterData::getRecord(index)->getPosition()) {
        monsterData_[addCount_].height = rect[4];
        monsterData_[addCount_].flying = true;
    }
    monsterData_[addCount_].height = adjustPosition(monsterData_[addCount_].height, monsterData_[addCount_].flying);
    monsterData_[addCount_].center = getGroupCenter(group) + 2;
    adjustPlateCenter(monsterData_[addCount_], true);
}

THUMB short BattleMonsterNamePlate::getGroupCenter(int group)
{
    int* rect;
    int max = 0;
    int min = MAX_DISPLAY_SIZE_X;
    int maxCount = status::g_Monster.getCount();
    for (int i = 0; i < maxCount; i++) {
        if (status::g_Monster.getMonsterStatus(i).isBattleEnable()) {
            rect = btl::BattleMonsterMask::getSingleton()->getMonsterTouchRect(i);
            if (rect[0] == group) {
                if (rect[3] > max) {
                    max = rect[3];
                }
                if (rect[1] < min) {
                    min = rect[1];
                }
            }
        }
    }
    int leng = max - min;
    return min + (leng >> 1);
}

THUMB void BattleMonsterNamePlate::maxPriority(int group)
{
    monsterData_[group].drawID = 1;
    for (int i = 0; i < addCount_; i++) {
        if (i != group) {
            monsterData_[i].drawID = 2;
        }
    }
}

THUMB void BattleMonsterNamePlate::adjustFlyHeight()
{
    short flyHeight = 0;
    short randHeight = 0x7fff;
    for (int i = 0; i < addCount_; i++) {
        if (monsterData_[i].flying && flyHeight < monsterData_[i].height) {
            flyHeight = monsterData_[i].height;
        }
        if (!monsterData_[i].flying && randHeight > monsterData_[i].height) {
            randHeight = monsterData_[i].height;
        }
    }
    if (flyHeight == randHeight) {
        short adjustHeight = flyHeight - PLATE_SIZE;
        if (adjustHeight < BLANK_SIZE) {
            adjustHeight = flyHeight;
        }
        for (int i = 0; i < addCount_; i++) {
            if (monsterData_[i].flying && flyHeight == monsterData_[i].height) {
                monsterData_[i].height = adjustHeight;
            }
        }
    }
    if (flyHeight > randHeight) {
        for (int i = 0; i < addCount_; i++) {
            if (monsterData_[i].flying && randHeight < monsterData_[i].height) {
                monsterData_[i].height = randHeight;
            }
            if (!monsterData_[i].flying && flyHeight > monsterData_[i].height) {
                monsterData_[i].height = flyHeight;
            }
        }
    }
}

THUMB void BattleMonsterNamePlate::sortPosition()
{
    makeSortList();
    if (flyAndRand_) {
        adjustFlyHeight();
    }
    for (int i = 0; i < addCount_; i++) {
        Monster_DATA& m_from = monsterData_[sortList_[i]];
        int move = true;
        int moreHight = true;
        while (move && moreHight) {
            move = false;
            moreHight = false;
            for (int j = 0; j < i; j++) {
                Monster_DATA& m_to = monsterData_[sortList_[j]];
                if (m_from.height > m_to.height) {
                    moreHight = true;
                } else if (changeHeight(m_from, m_to)) {
                    move = true;
                }
            }
        }
    }
}

THUMB void BattleMonsterNamePlate::makeSortList()
{
    int centerLengList[4] = {MAX_DISPLAY_SIZE_Y};
    for (int i = 0; i < 4; i++) centerLengList[i] = MAX_DISPLAY_SIZE_Y;
    int heightLengList[4] = {MAX_DISPLAY_SIZE_Y};
    for (int i = 0; i < 4; i++) heightLengList[i] = MAX_DISPLAY_SIZE_Y;
    int flyingList[4] = {true};
    for (int i = 0; i < 4; i++) flyingList[i] = true;
    for (int i = 0; i < addCount_; i++) {
        int centerLeng = dss::abs(MAX_DISPLAY_SIZE_Y - monsterData_[i].center);
        int heightLeng = monsterData_[i].height;
        int flying = monsterData_[i].flying;
        int thisNum = i;
        for (int j = 0; j < i; j++) {
            if (!flyingList[j] && flying) {
                continue;
            }
            if (centerLengList[j] < centerLeng && (!flyingList[j] || flying)) {
                continue;
            }
            if (centerLeng == centerLengList[j]) {
                if (heightLengList[j] > heightLeng) {
                    continue;
                }
                if (heightLeng == heightLengList[j] && flying) {
                    continue;
                }
            }
            int temp = centerLengList[j];
            centerLengList[j] = centerLeng;
            centerLeng = temp;
            temp = heightLengList[j];
            heightLengList[j] = heightLeng;
            heightLeng = temp;
            int tempNum = sortList_[j];
            sortList_[j] = thisNum;
            thisNum = tempNum;
            int tempFly = flyingList[j];
            flyingList[j] = flying;
            flying = tempFly;
        }
        centerLengList[i] = centerLeng;
        heightLengList[i] = heightLeng;
        flyingList[i] = flying;
        sortList_[i] = thisNum;
    }
}

THUMB bool BattleMonsterNamePlate::changeHeight(Monster_DATA& m_from, Monster_DATA& m_to)
{
    if (m_from.height == m_to.height) {
        int leng = m_from.center - m_to.center;
        int interval = (m_from.leng >> 1) + (m_to.leng >> 1);
        if (interval > dss::abs(leng)) {
            int firstSride;
            if (leng < 0) {
                firstSride = -(m_from.leng >> 3);
            } else {
                firstSride = m_from.leng >> 3;
            }
            bool pumpUp = false;
            m_from.center += firstSride;
            leng = m_from.center - m_to.center;
            if ((interval >> 2) > interval - dss::abs(leng)) {
                int sride = interval - dss::abs(leng);
                if (leng < 0) {
                    m_from.center -= sride;
                } else {
                    m_from.center += sride;
                }
            } else {
                m_from.center -= firstSride;
                movePumpUp(m_from);
                pumpUp = true;
            }
            adjustPlateCenter(m_from, pumpUp);
            return true;
        }
    }
    return false;
}

THUMB void BattleMonsterNamePlate::movePumpUp(Monster_DATA& monster)
{
    int* rect = btl::BattleMonsterMask::getSingleton()->getMonsterTouchRect(monster.index);
    short baseBottom = adjustPosition(rect[4], false);
    short baseTop = adjustPosition(rect[2], false);
    if (monster.flying && monster.height >= baseBottom) {
        monster.height = baseTop;
        return;
    }
    monster.height -= PLATE_SIZE;
}

THUMB void BattleMonsterNamePlate::adjustPlateCenter(Monster_DATA& monster, bool pumpUp)
{
    int subCenter = monster.center - (monster.leng >> 1);
    int addCenter = monster.center + (monster.leng >> 1);
    if (subCenter < CURSOR_BLANK) {
        monster.center -= subCenter - CURSOR_BLANK;
        if (!pumpUp) {
            monster.height -= PLATE_SIZE;
        }
    }
    if (addCenter > MAX_DISPLAY_SIZE_X) {
        monster.center -= addCenter - MAX_DISPLAY_SIZE_X;
        if (!pumpUp) {
            monster.height -= PLATE_SIZE;
        }
    }
    if (monster.height < 0) {
        monster.height += PLATE_SIZE;
    }
}

THUMB short BattleMonsterNamePlate::adjustPosition(short height, int fly)
{
    if (height < PLATE_SIZE + BLANK_SIZE) {
        return BLANK_SIZE;
    }
    short base = height - BLANK_SIZE;
    int rectSize = base / PLATE_SIZE;
    if (fly) {
        if (base % PLATE_SIZE >= PLATE_SIZE / 2) {
            rectSize++;
        }
    } else {
        if (base % PLATE_SIZE < PLATE_SIZE / 2) {
            rectSize--;
        }
    }
    return rectSize * PLATE_SIZE + BLANK_SIZE;
}
