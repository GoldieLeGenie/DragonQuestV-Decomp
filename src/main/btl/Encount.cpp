#pragma ipa file
#include "main/btl/Encount.hpp"
#include "main/global/Global.hpp"
#include "main/status/StageAttribute.hpp"

inline bool btl::Encount::isEnable()
{
    return enable_;
}

inline void btl::Encount::setTileId(int id)
{
    tileId_ = id; encountData_.setTileId(id);
}

inline int btl::Encount::getMonsterIndex(int group)
{
    return monsterIndex_[group];
}

inline int btl::Encount::getMonsterCount(int group)
{
    return monsterCount_[group];
}

inline int btl::EncountTile::getTileId() const
{
    return tileId_;
}

inline int btl::EncountData::getStdRate()
{
    return stdTileRate_;
}

inline btl::FirstAttack btl::EncountData::getFirstAttack()
{
    return firstAttack_;
}

inline unsigned short btl::EncountData::getMonsterIndex(int group)
{
    return monsterIndex_[group];
}

inline unsigned short btl::EncountData::getMonsterCount(int group)
{
    return monsterCount_[group];
}

inline int btl::EncountCountDown::getCounter()
{
    return counter_;
}

THUMB btl::Encount::Encount()
    : tileId_(-1), timeZone_(TIME_ZONE_NONE), enable_(true), brewCount_(0)
{
}

THUMB btl::Encount* btl::Encount::getSingleton()
{
    static Encount encount;
    return &encount;
}

THUMB void btl::Encount::setupDungeon(int chapter, TIME_ZONE timeZone, int floorIndex)
{
    chapter_ = chapter;
    landType_ = 8;
    timeZone_ = timeZone;
    encountTile_.setupDungeon(chapter_, floorIndex);
    tileId_ = encountTile_.getTileId();
    if (tileId_ != 0) {
        encountData_.setup(tileId_, true);
        encountCountDown_.setup();
        encountCountDown_.setLandType(landType_);
        encountCountDown_.setTileIdRate(encountData_.getStdRate());
        walkCount_ = 0;
        totalWalkCount_ = 0;
        brewCount_ = 0;
    }
}

THUMB void btl::Encount::setupField(int chapter, TIME_ZONE timeZone)
{
    chapter_ = chapter;
    landType_ = 8;
    timeZone_ = timeZone;
    encountCountDown_.setup();
    encountCountDown_.setTileIdRate(3);
    walkCount_ = 0;
    totalWalkCount_ = 0;
    brewCount_ = 0;
}

THUMB void btl::Encount::execDungeon()
{
    if (isEncounted()) {
        exec();
        if (isEncountedNext() && brew()) {
            g_Global.startBattle();
        }
    }
}

THUMB void btl::Encount::execField()
{
    if (isEncounted()) {
        exec();
        if (isEncountedNext() && brew()) {
            g_Global.startBattle();
        }
    }
}

THUMB void btl::Encount::execWalk()
{
    walkCount_++;
    if (walkCount_ >= 16) {
        walkCount_ = 0;
        totalWalkCount_++;
        exec();
    }
}

THUMB void btl::Encount::exec()
{
    if (!enable_) {
        return;
    }
    if (brewCount_ > 2) {
        return;
    }
    if (!isEnable()) {
        return;
    }
    if (!status::g_StageAttribute.isEncount()) {
        return;
    }
    if (tileId_ == 0) {
        return;
    }
    if (tileId_ == -1) {
        return;
    }
    encountData_.setup(tileId_, true);
    encountCountDown_.setTileIdRate(encountData_.getStdRate());
    encountCountDown_.setLandType(landType_);
    encountCountDown_.exec();
    if (encountCountDown_.getCounter() < 0 || brewCount_ != 0) {
        if (brewCount_ == 0) {
            brewCount_ = 1;
        } else {
            brewCount_++;
        }
    }
}

THUMB btl::FirstAttack btl::Encount::getFirstAttack()
{
    return encountData_.getFirstAttack();
}

THUMB int btl::Encount::isEncounted()
{
    if (brewCount_ == 1) {
        return true;
    }
    return false;
}

THUMB bool btl::Encount::isEncountedNext()
{
    if (brewCount_ == 2) {
        return true;
    }
    return false;
}

THUMB void btl::Encount::setBlock(int type, int land, int x, int y)
{
    landType_ = land;
    encountTile_.setupField(chapter_, type, land, x, y);
    tileId_ = encountTile_.getTileId();
}

THUMB void btl::Encount::setTimeZone(TIME_ZONE timeZone)
{
}

THUMB bool btl::Encount::brew()
{
    if (tileId_ == 0) {
        return false;
    }
    encountData_.setup(tileId_, timeZone_, true);
    for (int i = 0; i < 4; i++) {
        monsterIndex_[i] = encountData_.getMonsterIndex(i);
        monsterCount_[i] = encountData_.getMonsterCount(i);
    }
    encountScreenOver_.setup(monsterIndex_, monsterCount_);
    encountScreenOver_.execThinning();
    setMonsterCountName();
    return true;
}

THUMB void btl::Encount::forceBrew(int tile)
{
    if (tile != -1) {
        setTileId(tile);
    }
    brew();
    g_Global.startBattle();
}

THUMB void btl::Encount::forceEventBrew(int tile)
{
    status::g_StageAttribute.setEvBtlMapToBtlMap();
    forceBrew(tile);
}

THUMB void btl::Encount::forceEncount()
{
    if (tileId_ != 0 && tileId_ != -1) {
        brewCount_ = 1;
    }
}

THUMB btl::Encount::EncountNumber btl::Encount::getEncountNumberType()
{
    int index[4] = { -1, -1, -1, -1 };
    int count[4] = { 0, 0, 0, 0 };

    for (int i = 0; i < 4; i++) {
        count[i] = getMonsterCount(i);
        if (count[i] != 0) {
            index[i] = getMonsterIndex(i);
        }
    }
    if (index[0] != index[1] && index[1] != -1) {
        encountNumberIndex_ = 0xF6;
        return EncountMultiple;
    }
    if (index[0] == index[1] || index[0] == index[2] || index[0] == index[3]) {
        if (count[0] + count[1] + count[2] + count[3] >= 1) {
            encountNumberIndex_ = index[0];
            return EncountNumbers;
        }
    }
    if (index[1] == -1 && count[0] >= 2) {
        encountNumberIndex_ = index[0];
        return EncountNumbers;
    }
    if (index[1] == -1 && count[0] == 1) {
        encountNumberIndex_ = index[0];
        return EncountSingle;
    }
    return EncountMultiple;
}

THUMB void btl::Encount::setMonsterCountName()
{
    int index[4] = { -1, -1, -1, -1 };
    int count[4] = { 0, 0, 0, 0 };
    int idx = 0;

    for (int i = 0; i < 4; i++) {
        if (index[idx] == -1) {
            count[idx] = monsterCount_[i];
            break;
        }
        if (index[idx] == monsterIndex_[i]) {
            count[idx] += monsterCount_[i];
            break;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (count[i] > 1) {
            encountCountType_[i] = true;
        } else {
            encountCountType_[i] = false;
        }
    }
}

THUMB bool btl::Encount::getMonsterCountName(int monsterIndex)
{
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (monsterIndex == monsterIndex_[i]) {
            count += monsterCount_[i];
        }
    }
    if (count > 1) {
        return true;
    }
    return false;
}
