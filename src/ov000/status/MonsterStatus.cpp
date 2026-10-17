#include "ov000/status/MonsterStatus.hpp"
#include "main/dss/UnkRandom.hpp"

inline unsigned short dq5::level::MonsterData::getItem()
{
    return item;
}

inline unsigned char dq5::level::MonsterData::getRatio()
{
    return ratio;
}

inline char dq5::level::MonsterData::getDragon()
{
    return (byte_8 & 0xC0) >> 6;
}

inline char dq5::level::MonsterData::getZombi()
{
    return (byte_9 & 0xC0) >> 6;
}

inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index)
{
    return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline int status::HaveStatus::getMonsterKind() const
{
    return monsterId_;
}

inline status::StatusChange& status::HaveStatusInfo::getStatusChange()
{
    return statusChange_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline status::HaveAction& status::HaveStatusInfo::getHaveAction()
{
    return haveAction_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline char dq5::level::MonsterData::getHeal() { return (byte_2 & 0x30) >> 4; }
inline char dq5::level::MonsterData::getInit() { return byte_3 & 0x3; }
inline char dq5::level::MonsterData::getInitRatio() { return (byte_3 & 0xC) >> 2; }
inline char dq5::level::MonsterData::getItemRatio() { return byte_11 & 0xF; }

namespace status {
static dq5::level::MonsterData* monsterData_;

static THUMB void getRecord(int monsterIndex)
{
    monsterData_ = dq5::level::MonsterData::getRecord(monsterIndex);
}
}

THUMB status::MonsterStatus::MonsterStatus()
{
    eventFlag_.clear();
}

THUMB status::MonsterStatus::~MonsterStatus()
{
}

THUMB void status::MonsterStatus::setup(int monsterGroup, int monsterIndex, int sortIndex)
{
    characterGroup_ = monsterGroup;
    characterIndex_ = monsterIndex;
    sortIndex_ = sortIndex;
    characterType_ = MONSTER;
    CharacterStatus::setup(MONSTER, monsterGroup, monsterIndex);
    flag_.clear();
    type_.clear();
    getRecord(monsterIndex);
    if (monsterData_->getDragon()) {
        type_.set(1);
    }
    if (monsterData_->getZombi()) {
        type_.set(4);
    }
}

THUMB void status::MonsterStatus::cleanup()
{
    type_.clear();
    characterIndex_ = -1;
}

THUMB bool status::MonsterStatus::isEnable()
{
    if (characterIndex_ != -1) {
        return true;
    }
    return false;
}

THUMB bool status::MonsterStatus::isBattleEnable()
{
    if (characterIndex_ == -1) {
        return false;
    }
    if (getHaveStatusInfo().isDeath()) {
        return false;
    }
    if (getHaveBattleStatus().escape_ == 0) {
        return true;
    }
    return false;
}

THUMB bool status::MonsterStatus::isBeingEnable()
{
    if (characterIndex_ != -1) {
        return true;
    }
    return false;
}

THUMB int status::MonsterStatus::getDropItem()
{
    getRecord(characterIndex_);
    int itemIndex = getHaveDropItem();
    int ret = 0;
    int rateIndex = monsterData_->getItemRatio();
    switch (rateIndex) {
    case 0:
        ret = 0;
        break;
    case 1:
        ret = itemIndex;
        break;
    case 2:
        if (UnkDssRand::rand(8) == 0) {
            ret = itemIndex;
        }
        break;
    case 3:
        if (UnkDssRand::rand(16) == 0) {
            ret = itemIndex;
        }
        break;
    case 4:
        if (UnkDssRand::rand(32) == 0) {
            ret = itemIndex;
        }
        break;
    case 5:
        if (UnkDssRand::rand(64) == 0) {
            ret = itemIndex;
        }
        break;
    case 6:
        if (UnkDssRand::rand(128) == 0) {
            ret = itemIndex;
        }
        break;
    case 7:
        if (UnkDssRand::rand(256) == 0) {
            ret = itemIndex;
        }
        break;
    case 8:
        if (UnkDssRand::rand(4096) == 0) {
            ret = itemIndex;
        }
        break;
    }
    return ret;
}

THUMB int status::MonsterStatus::getHaveDropItem()
{
    return monsterData_->getItem();
}

THUMB void status::MonsterStatus::print()
{
}

THUMB void status::MonsterStatus::printAction()
{
}

THUMB void status::MonsterStatus::naturalRecovery()
{
    if (getHaveStatusInfo().isDeath()) {
        return;
    }
    getRecord(characterIndex_);
    int hp = 0;
    int recoveryIndex = monsterData_->getHeal();
    switch (recoveryIndex) {
    case 0:
        hp = 0;
        break;
    case 1:
        hp = UnkDssRand::rand(9) + 16;
        break;
    case 2:
        hp = UnkDssRand::rand(13) + 44;
        break;
    case 3:
        hp = UnkDssRand::rand(21) + 90;
        break;
    }
    getHaveStatusInfo().addHp(hp);
}

THUMB void status::MonsterStatus::setStartStatus()
{
    getRecord(characterIndex_);
    bool setup = false;
    int rate = monsterData_->getInitRatio();
    switch (rate) {
    case 0:
        setup = false;
        break;
    case 1:
        if (UnkDssRand::rand(4) == 0) {
            setup = true;
        }
        break;
    case 2:
        if (UnkDssRand::rand(2) == 0) {
            setup = true;
        }
        break;
    case 3:
        setup = true;
        break;
    }
    if (setup) {
        getRecord(characterIndex_);
        int status = monsterData_->getInit();
        switch (status) {
        case 0:
            getHaveStatusInfo().getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_NEMURI, true);
            break;
        case 1:
            getHaveStatusInfo().getStatusChange().setup((int)dq5::level::ActionParam::ACTIONTYPE_CURSE2, true);
            break;
        }
    }
}

THUMB void status::MonsterStatus::execStartOfRound()
{
    getHaveBattleStatus().setSelectCommand(HaveBattleStatus::AISelect, 0);
}

THUMB bool status::MonsterStatus::isDeathDisable()
{
    return false;
}

THUMB void status::MonsterStatus::setMosyasChange(int monsterIndex)
{
    getHaveBattleStatus().newBaseChangeMonster(monsterIndex);
    getHaveStatusInfo().setFirstMosyas(true);
}

THUMB void status::MonsterStatus::setMosyasChange(CharacterStatus* target)
{
    int hp = getHaveStatusInfo().getHp();
    int hpMax = getHaveStatusInfo().getHpMax();
    int mp = getHaveStatusInfo().getMp();
    int mpMax = getHaveStatusInfo().getMpMax();
    int exp = getHaveStatusInfo().getHaveStatus().exp_;
    int gold = getHaveStatusInfo().getHaveStatus().gold_;
    getHaveStatusInfo().setMosyasExec(true);
    target->getHaveStatusInfo().setMosyasTarget(true);
    mosyasTarget_ = target;
    mosyasMonsterIndex_ = target->getHaveStatusInfo().getHaveStatus().getMonsterKind();
    getHaveStatusInfo().getHaveStatus() = target->getHaveStatusInfo().getHaveStatus();
    getHaveStatusInfo().getHaveStatus().baseStatus_.strength_ = target->getHaveStatusInfo().getAttack(0);
    getHaveStatusInfo().getHaveStatus().baseStatus_.protection_ = target->getHaveStatusInfo().getDefence(0);
    getHaveStatusInfo().getHaveStatus().baseStatus_.agility_ = target->getHaveStatusInfo().getAgility(0);
    getHaveStatusInfo().getHaveStatus().baseStatus_.wisdom_ = target->getHaveStatusInfo().getWisdom(0);
    getHaveStatusInfo().getHaveStatus().baseStatus_.luck_ = target->getHaveStatusInfo().getLuck(0);
    getHaveStatusInfo().getHaveAction() = target->getHaveStatusInfo().getHaveAction();
    int monsterIndex_ = getHaveStatusInfo().getHaveStatus().getMonsterKind();
    getHaveStatusInfo().actionDefence_.setup(monsterIndex_, MONSTER);
    haveBattleStatus_ = target->getHaveBattleStatus();
    getHaveBattleStatus().haveStatusInfo_ = &getHaveStatusInfo();
    getHaveBattleStatus().brains_ = 2;
    getHaveBattleStatus().type_ = MONSTER;
    getHaveStatusInfo().setFirstMosyas(true);
    getHaveStatusInfo().getHaveStatus().command_ = 1;
    getHaveStatusInfo().setHpMax(hpMax);
    getHaveStatusInfo().setHp(hp);
    getHaveStatusInfo().setMpMax(mpMax);
    getHaveStatusInfo().setMp(mp);
    getHaveStatusInfo().getHaveStatus().setExp(exp);
    getHaveStatusInfo().getHaveStatus().gold_ = gold;
}

THUMB void status::MonsterStatus::setMosyasRelease()
{
    mosyasTarget_->getHaveStatusInfo().setMosyasTarget(false);
    mosyasTarget_ = NULL;
    getHaveStatusInfo().setMosyasExec(false);
    getHaveStatusInfo().releaseMosyas();
    getHaveBattleStatus().setup(MONSTER, getHaveBattleStatus().groupIndex_, 0x7b);
    getHaveStatusInfo().actionDefence_.setup(0x7b, MONSTER);
    getHaveStatusInfo().setMosyasRelease(true);
    if (getHaveStatusInfo().isDeath()) {
        getHaveStatusInfo().setMosyasRelease(false);
    }
}

THUMB bool status::MonsterStatus::isAddParty(int monsterIndex, int count)
{
    getRecord(monsterIndex);
    int ratio = monsterData_->getRatio();
    if (count == 0) {
        return isAddPartyFirst(ratio);
    }
    if (count == 1) {
        return isAddPartySecond(ratio);
    }
    if (count == 2) {
        return isAddPartyTherd(ratio);
    }
    return false;
}

THUMB bool status::MonsterStatus::isAddPartyFirst(int ratio)
{
    bool ret = false;
    switch (ratio) {
    case 0:
        ret = false;
        break;
    case 1:
        if (UnkDssRand::rand(256) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 2:
        if (UnkDssRand::rand(64) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 3:
        if (UnkDssRand::rand(32) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 4:
        if (UnkDssRand::rand(16) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 5:
        if (UnkDssRand::rand(4) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 6:
        if (UnkDssRand::rand(2) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 7:
        if (UnkDssRand::rand(2) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 8:
        ret = true;
        break;
    }
    return ret;
}

THUMB bool status::MonsterStatus::isAddPartySecond(int ratio)
{
    bool ret = false;
    switch (ratio) {
    case 0:
        ret = false;
        break;
    case 1:
        if (UnkDssRand::rand(1024) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 2:
        if (UnkDssRand::rand(128) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 3:
        if (UnkDssRand::rand(64) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 4:
        if (UnkDssRand::rand(64) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 5:
        if (UnkDssRand::rand(64) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 6:
        if (UnkDssRand::rand(64) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 7:
        if (UnkDssRand::rand(32) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 8:
        ret = true;
        break;
    }
    return ret;
}

THUMB bool status::MonsterStatus::isAddPartyTherd(int ratio)
{
    bool ret = false;
    switch (ratio) {
    case 0:
        ret = false;
        break;
    case 1:
        if (UnkDssRand::rand(1024) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 2:
        if (UnkDssRand::rand(256) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 3:
        if (UnkDssRand::rand(128) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 4:
        if (UnkDssRand::rand(64) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 5:
        if (UnkDssRand::rand(64) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 6:
        if (UnkDssRand::rand(64) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 7:
        if (UnkDssRand::rand(16) == 0) {
            ret = true;
        } else {
            ret = false;
        }
        break;
    case 8:
        ret = true;
        break;
    }
    return ret;
}

THUMB void status::MonsterStatus::setTakeUpMonsterDrop(bool flag)
{
    if (flag) {
        flag_.set(FLAG_TAKE_UP_MONSTER_DROP);
    } else {
        flag_.remove(FLAG_TAKE_UP_MONSTER_DROP);
    }
}

THUMB bool status::MonsterStatus::isTakeUpMonsterDrop()
{
    return flag_.check(FLAG_TAKE_UP_MONSTER_DROP);
}

THUMB void status::MonsterStatus::changeMonsterWithHPMP(int monsterIndex)
{
    int hp = getHaveStatusInfo().getHp();
    int mp = getHaveStatusInfo().getMp();
    setup(characterGroup_, monsterIndex, sortIndex_);
    getHaveStatusInfo().setHp(hp);
    getHaveStatusInfo().setMp(mp);
}
