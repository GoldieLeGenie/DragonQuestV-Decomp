#include "main/status/BattleResult.hpp"
#include "main/leveldata/MonsterData.hpp"
#include "main/leveldata/BookData.hpp"

inline unsigned short dq5::level::BookData::getIndex()
{
    return index;
}

inline unsigned char dq5::level::BookData::getFriendly()
{
    return friendly;
}

inline unsigned short dq5::level::MonsterData::getMoney()
{
    return money;
}

inline unsigned short dq5::level::MonsterData::getExp()
{
    return exp;
}

inline unsigned short dq5::level::MonsterData::getItem()
{
    return item;
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline unsigned int dq5::level::BookData::getArraySize()
{
    return binary_.getRecordCount();
}

inline dq5::level::BookData* dq5::level::BookData::getRecord(int index)
{
    return (BookData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index)
{
    return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

status::BattleResult status::g_BattleResult;

THUMB status::BattleResult::BattleResult()
{
}

THUMB status::BattleResult::~BattleResult()
{
}

THUMB void status::BattleResult::initialize()
{
    for (int i = 0; i < 202; i++) {
        result_[i].monsterCount_ = 0;
        result_[i].itemCount_ = 0;
        result_[i].level_ = 0;
        setMonsterEncount(i, false);
    }
    playerVictory_ = 0;
    playerDemolition_ = 0;
    playerDemolitionMessage_ = 2;
    disablePlayerDemolition_ = 0;
    battleExecute_ = 0;
    demolitionPartyTalk_ = 0;
    firstAttack_ = 2;
    debugFirstAttack_ = 2;
    battleTurnCount_ = 0;
}

THUMB void status::BattleResult::addMonsterCount(int index)
{
    result_[index].monsterCount_++;
    result_[index].monsterCount_ = dss::clamp<unsigned short>(result_[index].monsterCount_, 0, 999);
}

THUMB void status::BattleResult::addMonsterItemCount(int index)
{
    result_[index].itemCount_++;
    result_[index].itemCount_ = dss::clamp<unsigned short>(result_[index].itemCount_, 0, 999);
}

THUMB unsigned int status::BattleResult::getMonsterExp(int index)
{
    return dq5::level::MonsterData::getRecord(getMonsterIndex(index))->getExp();
}

THUMB unsigned int status::BattleResult::getMonsterGold(int index)
{
    return dq5::level::MonsterData::getRecord(getMonsterIndex(index))->getMoney();
}

THUMB void status::BattleResult::regenesisMonsterLevel(int index, unsigned char level)
{
    if (result_[index].level_ == 0) {
        result_[index].level_ = level;
        result_[index].level_ = dss::clamp<unsigned int>(result_[index].level_, 1, 99);
    }
}

THUMB void status::BattleResult::setMonsterEncount(unsigned int index, bool flag)
{
    if (flag == true) {
        encountFlag_.flag_[index >> 5].flag_ |= 1 << (index & 0x1f);
    }
    else {
        encountFlag_.flag_[index >> 5].flag_ &= ~(1 << (index & 0x1f));
    }
}

THUMB bool status::BattleResult::isMonsterEncount(unsigned int index)
{
    return encountFlag_.flag_[index >> 5].check(1 << (index & 0x1f));
}

THUMB int status::BattleResult::getMonsterEncountCount()
{
    int count = 0;
    for (unsigned int i = 0; i < 210; i++) {
        if (encountFlag_.flag_[i >> 5].check(1 << (i & 0x1f)) == true) {
            count++;
        }
    }
    return count;
}

THUMB unsigned int status::BattleResult::getMonsterTotalExp(int index)
{
    return getMonsterExp(index) * result_[index].monsterCount_;
}

THUMB unsigned int status::BattleResult::getMonsterTotalGold(int index)
{
    return getMonsterGold(index) * result_[index].monsterCount_;
}

THUMB short status::BattleResult::getMonsterItemIndex(int index)
{
    short item = -1;
    int monsterIndex = getMonsterIndex(index);
    if (monsterIndex == -1) {
        return 0;
    }
    if (result_[index].itemCount_ == 0) {
        if (result_[index].monsterCount_ > 10) {
            item = dq5::level::MonsterData::getRecord(monsterIndex)->getItem();
        }
    }
    else {
        item = dq5::level::MonsterData::getRecord(monsterIndex)->getItem();
    }
    return item;
}

THUMB int status::BattleResult::getMonsterIndex(int index)
{
    return dq5::level::BookData::getRecord(index + 1)->getIndex();
}

THUMB int status::BattleResult::getMonsterFriendly(int index)
{
    return dq5::level::BookData::getRecord(index + 1)->getFriendly();
}

THUMB int status::BattleResult::getMonsterBookIndex(int monsterIndex)
{
    unsigned int max = dq5::level::BookData::getArraySize();
    int i = 0;
    while (i < max) {
        if (monsterIndex == dq5::level::BookData::getRecord(i)->getIndex()) {
            return i - 1;
        }
        i++;
    }
    return -1;
}

THUMB void status::BattleResult::setDisablePlayerDemolition(bool flag)
{
    disablePlayerDemolition_ = flag;
}

THUMB int status::BattleResult::isDisablePlayerDemolition()
{
    return disablePlayerDemolition_;
}
