#include "ov000/btl/AutoAction.hpp"
#include "ov000/btl/BattleSelectTarget.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/UseAction.hpp"

inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int btl::BattleSelectTargetParam::getSourceCount() { return sourceCount_; }

THUMB void btl::RecoveryAutoActionParam::setupTarget()
{
    battleSelectTargetParam_.clear();
    if (player_->getCharacterType() == PLAYER) {
        BattleSelectTarget::setTargetPlayerWithDeath(&battleSelectTargetParam_);
        status::UseAction::getUseType(actionIndex_);
    }
    if (player_->getCharacterType() == MONSTER) {
        BattleSelectTarget::setTargetMonster(&battleSelectTargetParam_);
    }
}

THUMB void btl::RecoveryAutoActionParam::calcEffectValue()
{
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        status::CharacterStatus* target = battleSelectTargetParam_.getSourceCharacterStatus(i);
        if (target->getHaveStatusInfo().isDeath()) {
            targetEffectValue_[i] = 0;
        }
        else {
            targetEffectValue_[i] = status::UseAction::getEffectValueToPlayerMin(actionIndex_);
        }
    }
}

THUMB void btl::RecoveryAutoActionParam::calcEffectValueException()
{
    if (actionIndex_ == 0xED) {
        targetCount_ = battleSelectTargetParam_.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            if (player_ != battleSelectTargetParam_.getSourceCharacterStatus(i)) {
                targetEffectValue_[i] = 0;
            }
        }
    }
    if (actionIndex_ == 0x68) {
        targetCount_ = battleSelectTargetParam_.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            if (player_ != battleSelectTargetParam_.getSourceCharacterStatus(i)) {
                targetEffectValue_[i] = 0;
            }
        }
    }
    if (actionIndex_ == 0x3D) {
        targetCount_ = battleSelectTargetParam_.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            status::CharacterStatus* target = battleSelectTargetParam_.getSourceCharacterStatus(i);
            if (target->getHaveStatusInfo().isDeath()) {
                int maxHp = target->getHaveStatusInfo().getHpMax();
                targetEffectValue_[i] = (maxHp - target->getHaveStatusInfo().getHp()) / 2;
            }
        }
    }
    if (actionIndex_ == 0x3E) {
        targetCount_ = battleSelectTargetParam_.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            status::CharacterStatus* target = battleSelectTargetParam_.getSourceCharacterStatus(i);
            if (target->getHaveStatusInfo().isDeath()) {
                int maxHp = target->getHaveStatusInfo().getHpMax();
                targetEffectValue_[i] = maxHp - target->getHaveStatusInfo().getHp();
            }
        }
    }
    if (actionIndex_ == 0x40) {
        targetCount_ = battleSelectTargetParam_.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            status::CharacterStatus* target = battleSelectTargetParam_.getSourceCharacterStatus(i);
            if (!target->getHaveStatusInfo().isDeath()) {
                bool flag = false;
                if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU)) {
                    flag = true;
                }
                if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
                    flag = true;
                }
                if (flag) {
                    targetEffectValue_[i] = 1000;
                }
            }
        }
    }
    if (actionIndex_ == 0x41) {
        targetCount_ = battleSelectTargetParam_.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            status::CharacterStatus* target = battleSelectTargetParam_.getSourceCharacterStatus(i);
            if (!target->getHaveStatusInfo().isDeath()) {
                bool flag = false;
                if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
                    flag = true;
                }
                if (flag) {
                    targetEffectValue_[i] = 1000;
                }
            }
        }
    }
}

THUMB void btl::RecoveryAutoActionParam::calcCorrectEffectVelue()
{
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        int maxHp = battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().getHpMax();
        int nowHp = battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().getHp();
        lastEffectValue_[i] = dss::clamp<int>(lastEffectValue_[i], 0, maxHp - nowHp);
    }
}

THUMB void btl::RecoveryAutoActionParam::calcCorrectEffectVelueException()
{
    int minIndex = -1;
    int minRatio = 100;
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        int maxHp = battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().getHpMax();
        int nowHp = battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().getHp();
        int ratio = nowHp * 100 / maxHp;
        if (minRatio > ratio) {
            minRatio = ratio;
            minIndex = i;
        }
    }
    if (minIndex != -1 && lastEffectValue_[minIndex] != 0) {
        lastEffectValue_[minIndex] += 500;
    }
    if (actionIndex_ == 0x40) {
        targetCount_ = battleSelectTargetParam_.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            status::CharacterStatus* target = battleSelectTargetParam_.getSourceCharacterStatus(i);
            if (!target->getHaveStatusInfo().isDeath()) {
                bool flag = false;
                if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU)) {
                    flag = true;
                }
                if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
                    flag = true;
                }
                if (flag) {
                    lastEffectValue_[i] = 1000;
                }
                else {
                    lastEffectValue_[i] = 0;
                }
            }
        }
    }
    if (actionIndex_ == 0x41) {
        targetCount_ = battleSelectTargetParam_.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            status::CharacterStatus* target = battleSelectTargetParam_.getSourceCharacterStatus(i);
            if (!target->getHaveStatusInfo().isDeath()) {
                bool flag = false;
                if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
                    flag = true;
                }
                if (flag) {
                    lastEffectValue_[i] = 1000;
                }
                else {
                    lastEffectValue_[i] = 0;
                }
            }
        }
    }
}

THUMB void btl::RecoveryAutoActionParam::calcTargetCount()
{
    switch (status::UseAction::getUseArea(actionIndex_)) {
    case status::UseAction::Zero:
        break;
    case status::UseAction::One:
        for (int i = 0; i < 4; i++) {
            int count = battleSelectTargetParam_.getSourceCountForGroup(i);
            if (count != 0 && targetGroupEffectValueCount_[i] != 0) {
                targetGroupEffectValue_[i] /= targetGroupEffectValueCount_[i];
            }
        }
        break;
    case status::UseAction::Group:
        break;
    case status::UseAction::All:
        for (int i = 0; i < 4; i++) {
            targetGroupEffectValue_[4] += targetGroupEffectValue_[i];
        }
        for (int i = 0; i < 4; i++) {
            targetGroupEffectValue_[i] = 0;
        }
        break;
    case status::UseAction::Horse:
        break;
    case status::UseAction::UsuallyHorse:
        break;
    case status::UseAction::BattleHorse:
        break;
    }
}

THUMB bool btl::RecoveryAutoActionParam::isMemberHpDown(int persent)
{
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        if (!battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().isDeath()) {
            int maxHp = battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().getHpMax();
            int hp = 100 - persent;
            int nowHp = battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().getHp();
            if (nowHp < maxHp * hp / 100) {
                return true;
            }
        }
    }
    return false;
}

THUMB bool btl::RecoveryAutoActionParam::isMemberDeath()
{
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        if (battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().isDeath()) {
            return true;
        }
    }
    return false;
}

THUMB int btl::RecoveryAutoActionParam::getMemberSpazz()
{
    int count = 0;
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        status::StatusChange& statusChange = battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
            count++;
        }
    }
    return count;
}

THUMB int btl::RecoveryAutoActionParam::getMemberPoison()
{
    int count = 0;
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        status::StatusChange& statusChange = battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU)) {
            count++;
        }
    }
    return count;
}

THUMB int btl::RecoveryAutoActionParam::getMemberVenom()
{
    int count = 0;
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        status::StatusChange& statusChange = battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
            count++;
        }
    }
    return count;
}
