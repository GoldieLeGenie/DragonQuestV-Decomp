#include "main/status/StatusChangeOne.hpp"
#include "main/dss/UnkRandom.hpp"

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::level::ActionTypeList* dq5::level::ActionTypeList::getRecord(int index)
{
    return (ActionTypeList*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::EffectMessage* dq5::level::EffectMessage::getRecord(int index)
{
    return (EffectMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned char dq5::level::ActionTypeList::getTurn()
{
    return turn;
}

inline unsigned char dq5::level::ActionTypeList::getPattern()
{
    return pattern;
}

inline unsigned long dq5::level::EffectMessage::getConditionMsg()
{
    return ConditionMsg;
}

inline unsigned long dq5::level::EffectMessage::getOriginalCondMsg()
{
    return OriginalCondMsg;
}

inline unsigned long dq5::level::EffectMessage::getPlayerCondMsg()
{
    return PlayerCondMsg;
}

inline unsigned long dq5::level::EffectMessage::getMonsterCondMsg()
{
    return MonsterCondMsg;
}

inline unsigned long dq5::level::EffectMessage::getOverlapMsg()
{
    return OverlapMsg;
}

inline unsigned long dq5::level::EffectMessage::getNotLapMsg()
{
    return NotLapMsg;
}

inline unsigned long dq5::level::EffectMessage::getNaturalClearMsg()
{
    return NaturalClearMsg;
}

inline unsigned short dq5::level::EffectMessage::getAction()
{
    return action;
}

inline unsigned char dq5::level::EffectMessage::getTypeID()
{
    return typeID;
}

inline unsigned int dq5::level::EffectMessage::getArraySize()
{
    return binary_.getRecordCount();
}


dq5::level::ActionTypeList* status::actionType_;

THUMB void status::getActionType(int index)
{
    actionType_ = dq5::level::ActionTypeList::getRecord(index);
}

dq5::level::EffectMessage* status::effectMessage_;

THUMB int status::StatusChangeOne::getEffectMessage(int index, int actionIndex)
{
    int i;
    for (i = 0; i < dq5::level::EffectMessage::getArraySize(); i++) {
        if (dq5::level::EffectMessage::getRecord(i)->getTypeID() == index && dq5::level::EffectMessage::getRecord(i)->getAction() == actionIndex) {
            effectMessage_ = dq5::level::EffectMessage::getRecord(i);
            return i;
        }
    }
    for (i = 0; i < dq5::level::EffectMessage::getArraySize(); i++) {
        dq5::level::EffectMessage::getRecord(i);
        if (dq5::level::EffectMessage::getRecord(i)->getTypeID() == index && dq5::level::EffectMessage::getRecord(i)->getAction() == 0) {
            effectMessage_ = dq5::level::EffectMessage::getRecord(i);
            return i;
        }
    }
    for (i = 0; i < dq5::level::EffectMessage::getArraySize(); i++) {
        dq5::level::EffectMessage::getRecord(i);
        if (dq5::level::EffectMessage::getRecord(i)->getTypeID() == index) {
            effectMessage_ = dq5::level::EffectMessage::getRecord(i);
            return i;
        }
    }
    effectMessage_ = dq5::level::EffectMessage::getRecord(0);
    return 0;
}

THUMB status::StatusChangeOne::StatusChangeOne()
{
    damageType_ = 0;
    count_ = 0;
    turn_ = 0;
    pattern_ = 0;
    astron_ = 0;
    flag_.clear();
}

THUMB status::StatusChangeOne::~StatusChangeOne()
{
}

THUMB void status::StatusChangeOne::setup(dq5::level::ActionParam::ACTIONTYPE release, int actionIndex, bool flag)
{
    clear();
    flag_.flag_ |= FLAG_ENABLE;
    damageType_ = release;
    actionIndex_ = actionIndex;
    count_ = 0;
    getActionType(damageType_);
    turn_ = actionType_->getTurn();
    pattern_ = actionType_->getPattern();
    if (flag) {
        turn_ += addTurn();
    }
}

THUMB void status::StatusChangeOne::cleanup()
{
    clear();
}

THUMB void status::StatusChangeOne::clear()
{
    flag_.clear();
    count_ = 0;
    turn_ = 0;
    pattern_ = 0;
}

THUMB int status::StatusChangeOne::addTurn()
{
    switch (pattern_) {
        case 0:
            return 0;
        case 1:
            return UnkDssRand::rand(1) + 1;
        case 2:
            if (UnkDssRand::rand(8) <= 0) {
                return 1;
            }
            if (UnkDssRand::rand(8) <= 2) {
                return 2;
            }
            if (UnkDssRand::rand(8) <= 4) {
                return 3;
            }
            UnkDssRand::rand(8);
            return 4;
        case 3:
            if (UnkDssRand::rand(8) <= 2) {
                return 1;
            }
            if (UnkDssRand::rand(8) <= 4) {
                return 2;
            }
            if (UnkDssRand::rand(8) <= 6) {
                return 3;
            }
            UnkDssRand::rand(8);
            return 4;
        case 4:
            if (UnkDssRand::rand(8) <= 4) {
                return 1;
            }
            if (UnkDssRand::rand(8) <= 5) {
                return 2;
            }
            if (UnkDssRand::rand(8) <= 6) {
                return 3;
            }
            UnkDssRand::rand(8);
            return 4;
        case 5:
            return 1;
        case 6:
            return 0x80;
    }
    return 0;
}

THUMB bool status::StatusChangeOne::isCancel()
{
    bool result = true;
    if (!flag_.check(FLAG_ENABLE)) {
        return false;
    }
    if (count_ < turn_) {
        result = false;
    }
    return result;
}

THUMB void status::StatusChangeOne::execStartOfTurn()
{
    if (flag_.check(FLAG_ENABLE)) {
        getActionType(damageType_);
        if ((char)((actionType_->byte_1 & 2) >> 1)) {
            count_++;
        }
    }
}

THUMB void status::StatusChangeOne::execEndOfTurn()
{
    if (flag_.check(FLAG_ENABLE) && turn_ != 0xff) {
        getActionType(damageType_);
        if ((char)((actionType_->byte_1 & 4) >> 2)) {
            count_++;
        }
        if (astron_) {
            count_++;
        }
    }
}

THUMB void status::StatusChangeOne::execEndOfRound()
{
    if (flag_.check(FLAG_ENABLE) && turn_ != 0xff) {
        getActionType(damageType_);
        if ((char)((actionType_->byte_1 & 8) >> 3)) {
            count_++;
        }
    }
}

THUMB void status::StatusChangeOne::execWalk()
{
    if (flag_.check(FLAG_ENABLE) && turn_ != 0xff) {
        count_++;
    }
}

THUMB void status::StatusChangeOne::setEnable(bool flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_ENABLE;
    } else {
        flag_.flag_ &= ~FLAG_ENABLE;
    }
}

THUMB bool status::StatusChangeOne::isEnable() const
{
    return flag_.check(FLAG_ENABLE);
}

THUMB void status::StatusChangeOne::setRelease(bool flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_RELEASE;
    } else {
        flag_.flag_ &= ~FLAG_RELEASE;
    }
}

THUMB bool status::StatusChangeOne::isRelease() const
{
    return flag_.check(FLAG_RELEASE);
}

THUMB bool status::StatusChangeOne::isValidOnAstron(int damageType)
{
    getActionType(damageType);
    if ((char)((actionType_->byte_1 & 0x40) >> 6) != 1) {
        return true;
    }
    return false;
}

THUMB bool status::StatusChangeOne::isValidOnSpazz(int damageType)
{
    getActionType(damageType);
    if ((char)((actionType_->byte_1 & 0x80) >> 7) != 1) {
        return true;
    }
    return false;
}

THUMB bool status::StatusChangeOne::isAfterOnSleep(int damageType)
{
    getActionType(damageType);
    if ((char)((actionType_->byte_2 & 2) >> 1) != 1) {
        return true;
    }
    return false;
}

THUMB bool status::StatusChangeOne::isAfterOnPath1(int damageType)
{
    getActionType(damageType);
    if ((char)((actionType_->byte_2 & 4) >> 2) != 1) {
        return true;
    }
    return false;
}

THUMB bool status::StatusChangeOne::isAfterOnConfuze(int damageType)
{
    getActionType(damageType);
    if ((char)((actionType_->byte_2 & 8) >> 3) != 1) {
        return true;
    }
    return false;
}

THUMB bool status::StatusChangeOne::isAfterOnPowerSave(int damageType)
{
    getActionType(damageType);
    if ((char)((actionType_->byte_2 & 0x10) >> 4) != 1) {
        return true;
    }
    return false;
}

THUMB int status::StatusChangeOne::getExecMessage()
{
    getEffectMessage(damageType_, actionIndex_);
    return effectMessage_->getConditionMsg();
}

THUMB int status::StatusChangeOne::getExecMessage2()
{
    getEffectMessage(damageType_, actionIndex_);
    return effectMessage_->getOriginalCondMsg();
}

THUMB int status::StatusChangeOne::getResultPlayerMessage()
{
    getEffectMessage(damageType_, actionIndex_);
    return effectMessage_->getPlayerCondMsg();
}

THUMB int status::StatusChangeOne::getResultMonsterMessage()
{
    getEffectMessage(damageType_, actionIndex_);
    return effectMessage_->getMonsterCondMsg();
}

THUMB int status::StatusChangeOne::getAgainEnableMessage()
{
    getEffectMessage(damageType_, actionIndex_);
    return effectMessage_->getOverlapMsg();
}

THUMB int status::StatusChangeOne::getAgainDisableMessage()
{
    getEffectMessage(damageType_, actionIndex_);
    return effectMessage_->getNotLapMsg();
}

THUMB int status::StatusChangeOne::getReleaseMessage()
{
    getEffectMessage(damageType_, actionIndex_);
    return effectMessage_->getNaturalClearMsg();
}
