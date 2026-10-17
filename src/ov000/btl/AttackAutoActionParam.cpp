#include "ov000/btl/AutoAction.hpp"
#include "ov000/btl/BattleSelectTarget.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/UseAction.hpp"

inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int status::CharacterStatus::getGroupIndex() { return characterGroup_; }
inline int btl::BattleSelectTargetParam::getSourceCount() { return sourceCount_; }
inline int btl::AutoActionParam::isBossMode() { return bossFlag_; }

int btl::AttackAutoActionParam::normalAttack_;
int btl::AttackAutoActionParam::attackActionRatio_ = 100;
int btl::AttackAutoActionParam::normalAttackRatio_ = 120;

THUMB void btl::AttackAutoActionParam::setupTarget()
{
    battleSelectTargetParam_.clear();
    if (player_->getCharacterType() == MONSTER) {
        BattleSelectTarget::setTargetPlayer(&battleSelectTargetParam_);
    }
    if (player_->getCharacterType() == PLAYER) {
        BattleSelectTarget::setTargetMonster(&battleSelectTargetParam_);
    }
}

THUMB void btl::AttackAutoActionParam::calcEffectValue()
{
    if (player_->getCharacterType() == PLAYER) {
        effectValue_ = status::UseAction::getEffectValueToMonsterMin(actionIndex_);
    }
    if (player_->getCharacterType() == MONSTER) {
        effectValue_ = status::UseAction::getEffectValueToPlayerMin(actionIndex_);
    }
    for (int i = 0; i < MONSTER_MAX; i++) {
        targetEffectValue_[i] = effectValue_;
    }
}

THUMB void btl::AttackAutoActionParam::calcEffectValueException()
{
    if (actionIndex_ == 0x47) {
        targetCount_ = battleSelectTargetParam_.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            status::CharacterStatus* target = battleSelectTargetParam_.getSourceCharacterStatus(i);
            targetEffectValue_[i] = status::getUsuallyAttackEffectValueForAI(player_, target);
            if (targetEffectValue_[i] == 0) {
                targetEffectValue_[i] = 1;
            }
            if (player_->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_TAMEKEI)) {
                targetEffectValue_[i] = targetEffectValue_[i] * 17 / 10;
            }
            if (status::isDoubleAction(player_, actionIndex_)) {
                targetEffectValue_[i] = targetEffectValue_[i] * 75 / 100 * 2;
            }
            if (status::isAllTargetEquipment(player_)) {
                switch (i) {
                case 0:
                    break;
                case 1:
                    targetEffectValue_[i] = targetEffectValue_[i] * 80 / 100;
                    break;
                case 2:
                    targetEffectValue_[i] = targetEffectValue_[i] * 70 / 100;
                    break;
                case 3:
                    targetEffectValue_[i] = targetEffectValue_[i] * 50 / 100;
                    break;
                case 4:
                    targetEffectValue_[i] = targetEffectValue_[i] * 30 / 100;
                    break;
                default:
                    targetEffectValue_[i] = targetEffectValue_[i] * 20 / 100;
                    break;
                }
            }
        }
        if (status::isGroupTargetEquipment(player_)) {
            for (int j = 0; j < 4; j++) {
                int index = 0;
                for (int i = 0; i < targetCount_; i++) {
                    if (j == battleSelectTargetParam_.getSourceGroup(i)) {
                        switch (index) {
                        case 0:
                            break;
                        case 1:
                            targetEffectValue_[i] = targetEffectValue_[i] * 80 / 100;
                            break;
                        case 2:
                            targetEffectValue_[i] = targetEffectValue_[i] * 70 / 100;
                            break;
                        case 3:
                            targetEffectValue_[i] = targetEffectValue_[i] * 50 / 100;
                            break;
                        case 4:
                            targetEffectValue_[i] = targetEffectValue_[i] * 30 / 100;
                            break;
                        default:
                            targetEffectValue_[i] = targetEffectValue_[i] * 20 / 100;
                            break;
                        }
                        index++;
                    }
                }
            }
        }
    }
    if (actionIndex_ == 0x13 || actionIndex_ == 0x15 || actionIndex_ == 0x15) {
        targetCount_ = battleSelectTargetParam_.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            battleSelectTargetParam_.getSourceCharacterStatus(i);
            targetEffectValue_[i] = 1024;
        }
    }
    if (actionIndex_ == 0x5E || actionIndex_ == 0x5F) {
        targetCount_ = battleSelectTargetParam_.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            status::CharacterStatus* target = battleSelectTargetParam_.getSourceCharacterStatus(i);
            targetEffectValue_[i] = status::getUsuallyAttackEffectValue(player_, target);
            targetEffectValue_[i] = targetEffectValue_[i] * 13 / 10;
        }
    }
    if (normalAttack_) {
        if (status::UseAction::getUseMp(actionIndex_) == 0) {
            int ratio;
            if (actionIndex_ == 0x47) {
                ratio = normalAttackRatio_;
            }
            else {
                ratio = attackActionRatio_;
            }
            for (int i = 0; i < targetCount_; i++) {
                targetEffectValue_[i] = targetEffectValue_[i] * ratio / 100;
            }
        }
        if (actionIndex_ == 0x10 || actionIndex_ == 0x11) {
            int ratio = 50;
            for (int i = 0; i < targetCount_; i++) {
                targetEffectValue_[i] = targetEffectValue_[i] * ratio / 100;
            }
        }
    }
}

THUMB void btl::AttackAutoActionParam::calcCorrectEffectVelue()
{
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        int hp = battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().getHp();
        if (lastEffectValue_[i] != 0) {
            lastDamageRate_[i] = lastEffectValue_[i] * 100 / hp;
        }
        else {
            lastDamageRate_[i] = 0;
        }
    }
    for (int i = 0; i < targetCount_; i++) {
        int temp = battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().getHp() - lastEffectValue_[i];
        if (!isBossMode()) {
            temp = dss::clamp<int>(temp, 0, 9999);
        }
        lastEffectValue_[i] = 9999 - temp;
        if (targetActionDefence_[i] == 0) {
            lastEffectValue_[i] = 0;
        }
    }
}

THUMB void btl::AttackAutoActionParam::calcCorrectEffectVelueException()
{
    calcCorrectEffectVelueMahokanta();
    calcCorrectEffectVelueMahosute();
}

THUMB void btl::AttackAutoActionParam::calcCorrectEffectVelueMahokanta()
{
    if (!status::UseAction::isMahokanta(actionIndex_)) {
        return;
    }
    bool flag = false;
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        status::CharacterStatus* target = battleSelectTargetParam_.getSourceCharacterStatus(i);
        if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA)) {
            flag = true;
        }
    }
    if (flag) {
        for (int i = 0; i < targetCount_; i++) {
            lastEffectValue_[i] = 0;
        }
    }
}

THUMB void btl::AttackAutoActionParam::calcCorrectEffectVelueMahosute()
{
}

THUMB void btl::AttackAutoActionParam::calcTargetCount()
{
    status::UseAction::UseArea useArea = status::UseAction::getUseArea(actionIndex_);
    if (status::UseAction::isErrorB(actionIndex_)) {
        if (status::isGroupTargetEquipment(player_)) {
            useArea = status::UseAction::Group;
        }
        if (status::isAllTargetEquipment(player_)) {
            useArea = status::UseAction::All;
        }
    }
    switch (useArea) {
    case status::UseAction::Zero:
        break;
    case status::UseAction::One:
    case status::UseAction::Group:
        {
            int groupMax[4] = {}; for (int i = 0; i < 4; i++) { groupMax[i] = 0; }
            int count = battleSelectTargetParam_.getSourceCount();
            for (int i = 0; i < count; i++) {
                int group = battleSelectTargetParam_.getSourceCharacterStatus(i)->getGroupIndex();
                if (groupMax[group] < lastEffectValue_[i]) {
                    groupMax[group] = lastEffectValue_[i];
                }
            }
            for (int i = 0; i < 4; i++) {
                targetGroupEffectValue_[i] = groupMax[i];
            }
        }
        break;
    case status::UseAction::All:
        {
            int max = 0;
            int count = battleSelectTargetParam_.getSourceCount();
            for (int i = 0; i < count; i++) {
                if (max < lastEffectValue_[i]) {
                    max = lastEffectValue_[i];
                }
            }
            for (int i = 0; i < 5; i++) {
                targetGroupEffectValue_[i] = 0;
            }
            targetGroupEffectValue_[4] = max;
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
