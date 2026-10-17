#include "ov000/btl/AutoAction.hpp"
#include "ov000/btl/BattleSelectTarget.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/UseAction.hpp"

inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int status::CharacterStatus::getGroupIndex() { return characterGroup_; }
inline status::ActionDefence& status::HaveStatusInfo::getActionDefence() { return actionDefence_; }
inline int btl::BattleSelectTargetParam::getSourceCount() { return sourceCount_; }

THUMB status::GameFlag btl::AutoActionParam::actionFlag_[5];
int btl::AutoActionParam::turnCount_;
int btl::AutoActionParam::bossFlag_;

THUMB btl::AutoActionParam::AutoActionParam()
{
    clear();
}

THUMB btl::AutoActionParam::~AutoActionParam()
{
}

THUMB void btl::AutoActionParam::setup(int actionIndex, int itemIndex, status::CharacterStatus* player)
{
    clear();
    actionIndex_ = actionIndex;
    itemIndex_ = itemIndex;
    player_ = player;
    setupTarget();
    calcEffectValue();
    calcEffectValueException();
    calcActionDefence();
    calcTargetEffectValue();
    calcCorrectEffectVelue();
    calcCorrectEffectVelueException();
    calcGroupValue();
    calcAllValue();
    calcTargetCount();
    calcSelectGroup();
    calcSelectIndex();
}

THUMB void btl::AutoActionParam::clear()
{
    actionIndex_ = 0;
    itemIndex_ = 0;
    for (int i = 0; i < MONSTER_MAX; i++) {
        targetActionDefence_[i] = 0;
        targetEffectValue_[i] = 0;
        lastEffectValue_[i] = 0;
    }
    for (int i = 0; i < 5; i++) {
        targetGroupEffectValue_[i] = 0;
        targetGroupEffectValueCount_[i] = 0;
    }
}

THUMB void btl::AutoActionParam::setupTarget()
{
    battleSelectTargetParam_.clear();
    if (player_->getCharacterType() == MONSTER) {
        BattleSelectTarget::setTargetMonster(&battleSelectTargetParam_);
    }
    if (player_->getCharacterType() == PLAYER) {
        BattleSelectTarget::setTargetPlayer(&battleSelectTargetParam_);
    }
}

THUMB void btl::AutoActionParam::calcEffectValue()
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

THUMB void btl::AutoActionParam::calcEffectValueException()
{
    if (actionIndex_ == 0x47) {
        targetCount_ = battleSelectTargetParam_.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            status::CharacterStatus* target = battleSelectTargetParam_.getSourceCharacterStatus(i);
            targetEffectValue_[i] = status::getUsuallyAttackEffectValue(player_, target);
        }
    }
}

THUMB void btl::AutoActionParam::calcActionDefence()
{
    status::UseAction::getActionDefenceKind(actionIndex_);
    status::UseAction::getActionDefenceType(actionIndex_);
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        targetActionDefence_[i] = battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().getActionDefence().getEffectValue(actionIndex_);
    }
}

THUMB void btl::AutoActionParam::calcTargetEffectValue()
{
    for (int i = 0; i < targetCount_; i++) {
        lastEffectValue_[i] = (short)(targetActionDefence_[i] * targetEffectValue_[i] / 1000);
    }
}

THUMB void btl::AutoActionParam::calcCorrectEffectVelue()
{
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        lastEffectValue_[i] = dss::clamp<int>(lastEffectValue_[i], 0, battleSelectTargetParam_.getSourceCharacterStatus(i)->getHaveStatusInfo().getHp());
    }
}

THUMB void btl::AutoActionParam::calcCorrectEffectVelueException()
{
}

THUMB void btl::AutoActionParam::calcGroupValue()
{
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        int group = battleSelectTargetParam_.getSourceCharacterStatus(i)->getGroupIndex();
        targetGroupEffectValue_[group] += lastEffectValue_[i];
        if (lastEffectValue_[i] != 0) {
            targetGroupEffectValueCount_[group]++;
        }
    }
}

THUMB void btl::AutoActionParam::calcAllValue()
{
}

THUMB void btl::AutoActionParam::calcTargetCount()
{
    switch (status::UseAction::getUseArea(actionIndex_)) {
    case status::UseAction::Zero:
        break;
    case status::UseAction::One:
        for (int i = 0; i < 4; i++) {
            int count = battleSelectTargetParam_.getSourceCountForGroup(i);
            if (count) {
                targetGroupEffectValue_[i] /= count;
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

THUMB void btl::AutoActionParam::calcSelectGroup()
{
    maxGroup_ = -1;
    int maxValue = 0;
    for (int i = 0; i < 5; i++) {
        if (maxValue < targetGroupEffectValue_[i]) {
            maxValue = targetGroupEffectValue_[i];
            maxGroup_ = i;
        }
    }
}

THUMB void btl::AutoActionParam::calcSelectIndex()
{
    maxIndex_ = -1;
    int maxValue = 0;
    for (int i = 0; i < MONSTER_MAX; i++) {
        if (maxValue < lastEffectValue_[i]) {
            maxValue = lastEffectValue_[i];
            maxIndex_ = i;
        }
    }
}

THUMB int btl::AutoActionParam::getSelectValue()
{
    int value = -1;
    if (maxGroup_ != -1) {
        value = targetGroupEffectValue_[maxGroup_];
    }
    return value;
}

THUMB void btl::AutoActionParam::enableTargetMahotone(int action, BattleSelectTargetParam& param)
{
    if (actionIndex_ == action) {
        targetCount_ = param.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            param.getSourceCharacterStatus(i);
            if (!checkTargetHaveMahotoneAction(i, param)) {
                targetEffectValue_[i] = 0;
            }
        }
    }
}

THUMB void btl::AutoActionParam::enableTargetFubaha(int action, BattleSelectTargetParam& player, BattleSelectTargetParam& monster)
{
    if (actionIndex_ == action) {
        int count = 0;
        targetCount_ = monster.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            monster.getSourceCharacterStatus(i);
            if (checkTargetHaveFubahaAction(i, monster)) {
                count++;
            }
        }
        if (count == 0) {
            targetCount_ = player.getSourceCount();
            for (int i = 0; i < targetCount_; i++) {
                targetEffectValue_[i] = 0;
            }
        }
    }
}

THUMB void btl::AutoActionParam::enableTargetMahokite(int action, BattleSelectTargetParam& monster, BattleSelectTargetParam& player)
{
    if (actionIndex_ == action) {
        bool flag = false;
        targetCount_ = monster.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            monster.getSourceCharacterStatus(i);
            if (checkTargetHaveMahokiteAction(i, monster)) {
                flag = true;
            }
        }
        if (!flag) {
            targetCount_ = player.getSourceCount();
            for (int i = 0; i < targetCount_; i++) {
                targetEffectValue_[i] = 0;
            }
        }
    }
}

THUMB void btl::AutoActionParam::enableTargetInstantDeath(int action, BattleSelectTargetParam& monster, BattleSelectTargetParam& player)
{
    if (actionIndex_ == action) {
        bool flag = false;
        int count = monster.getSourceCount();
        for (int i = 0; i < count; i++) {
            monster.getSourceCharacterStatus(i);
            if (!checkTargetHaveInstantDeathAction(i, monster)) {
                flag = true;
            }
        }
        if (flag) {
            count = player.getSourceCount();
            for (int i = 0; i < count; i++) {
                targetEffectValue_[i] = 0;
            }
        }
    }
}

THUMB void btl::AutoActionParam::enableTargetRukaniRukanan(int action, BattleSelectTargetParam& monster, BattleSelectTargetParam& player)
{
    if (actionIndex_ == action) {
        bool flag = false;
        targetCount_ = monster.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            monster.getSourceCharacterStatus(i);
            if (checkTargetHaveRukaniRukanan(i, monster)) {
                flag = true;
            }
        }
        if (!flag) {
            targetCount_ = player.getSourceCount();
            for (int i = 0; i < targetCount_; i++) {
                targetEffectValue_[i] = 0;
            }
        }
    }
}

THUMB void btl::AutoActionParam::enableMpZeroTargetEnable(int action, BattleSelectTargetParam& param)
{
    if (actionIndex_ != action) {
        return;
    }
    if (player_->getHaveStatusInfo().getMp() != 0) {
        targetCount_ = param.getSourceCount();
        for (int i = 0; i < targetCount_; i++) {
            targetEffectValue_[i] = 0;
        }
        return;
    }
    targetCount_ = param.getSourceCount();
    for (int i = 0; i < targetCount_; i++) {
        status::CharacterStatus* target = param.getSourceCharacterStatus(i);
        if (target->getHaveStatusInfo().getMp() == 0) {
            targetEffectValue_[i] = 0;
        }
    }
}

THUMB bool btl::AutoActionParam::checkTargetHaveMahotoneAction(int index, BattleSelectTargetParam& param)
{
    status::HaveBattleStatus& battleStatus = param.getSourceCharacterStatus(index)->getHaveBattleStatus();
    int count = 0;
    for (int i = 0; i < 6; i++) {
        int actionIndex = battleStatus.getActionIndex(index);
        if (status::UseAction::isMahoton(actionIndex)) {
            count++;
        }
    }
    if (count) {
        return true;
    }
    return false;
}

THUMB bool btl::AutoActionParam::checkTargetHaveFubahaAction(int index, BattleSelectTargetParam& param)
{
    status::HaveBattleStatus& battleStatus = param.getSourceCharacterStatus(index)->getHaveBattleStatus();
    int count = 0;
    for (int i = 0; i < 6; i++) {
        int actionIndex = battleStatus.getActionIndex(i);
        if (status::UseAction::isFubaha(actionIndex)) {
            count++;
        }
    }
    if (count) {
        return true;
    }
    return false;
}

THUMB bool btl::AutoActionParam::checkTargetHaveMahokiteAction(int index, BattleSelectTargetParam& param)
{
    status::HaveBattleStatus& battleStatus = param.getSourceCharacterStatus(index)->getHaveBattleStatus();
    int count = 0;
    for (int i = 0; i < 6; i++) {
        int actionIndex = battleStatus.getActionIndex(index);
        if (status::UseAction::isMahokite(actionIndex)) {
            count++;
        }
    }
    if (count) {
        return true;
    }
    return false;
}

THUMB bool btl::AutoActionParam::checkTargetHaveInstantDeathAction(int index, BattleSelectTargetParam& param)
{
    status::HaveBattleStatus& battleStatus = param.getSourceCharacterStatus(index)->getHaveBattleStatus();
    int count = 0;
    for (int i = 0; i < 6; i++) {
        int actionIndex = battleStatus.getActionIndex(i);
        if (actionIndex == 0x13) {
            count++;
        }
        if (actionIndex == 0x14) {
            count++;
        }
        if (actionIndex == 0x15) {
            count++;
        }
        if (actionIndex == 0x16) {
            count++;
        }
    }
    if (count) {
        return true;
    }
    return false;
}

THUMB bool btl::AutoActionParam::checkTargetHaveRukaniRukanan(int index, BattleSelectTargetParam& param)
{
    status::HaveBattleStatus& battleStatus = param.getSourceCharacterStatus(index)->getHaveBattleStatus();
    int count = 0;
    for (int i = 0; i < 6; i++) {
        int actionIndex = battleStatus.getActionIndex(i);
        if (actionIndex == 0x26) {
            count++;
        }
        if (actionIndex == 0x27) {
            count++;
        }
        if (actionIndex == 0x28) {
            count++;
        }
    }
    if (count) {
        return true;
    }
    return false;
}

THUMB void btl::AutoActionParam::disableTarget2Count(int action, BattleSelectTargetParam& param)
{
    if (actionIndex_ == action) {
        disableTarget2CountInGroup(0, action, param);
        disableTarget2CountInGroup(1, action, param);
        disableTarget2CountInGroup(2, action, param);
        disableTarget2CountInGroup(3, action, param);
    }
}

THUMB void btl::AutoActionParam::disableTarget2CountInGroup(int group, int action, BattleSelectTargetParam& param)
{
    bool ret0 = false;
    bool ret1 = false;
    if (param.getSourceCountForGroup(group) > 1) {
        ret0 = true;
    }
    if (!actionFlag_[group].check(action)) {
        ret1 = true;
    }
    if (!ret0 || !ret1) {
        int count = param.getSourceCount();
        for (int i = 0; i < count; i++) {
            if (group == param.getSourceGroup(i)) {
                lastEffectValue_[i] = 0;
            }
        }
    }
}

THUMB void btl::AutoActionParam::disableOnceUse(int action, BattleSelectTargetParam& param)
{
    if (actionIndex_ == action) {
        disableOnceUseInGroup(0, action, param);
        disableOnceUseInGroup(1, action, param);
        disableOnceUseInGroup(2, action, param);
        disableOnceUseInGroup(3, action, param);
    }
}

THUMB void btl::AutoActionParam::disableOnceUseInGroup(int group, int action, BattleSelectTargetParam& param)
{
    if (actionFlag_[group].check(action)) {
        int count = param.getSourceCount();
        for (int i = 0; i < count; i++) {
            lastEffectValue_[i] = 0;
        }
    }
}

THUMB void btl::AutoActionParam::disableStatusChange(int action, dq5::level::ActionParam::ACTIONTYPE type, BattleSelectTargetParam& param)
{
    if (actionIndex_ == action) {
        int count = param.getSourceCount();
        for (int i = 0; i < count; i++) {
            status::StatusChange& statusChange = param.getSourceCharacterStatus(i)->getHaveStatusInfo().getStatusChange();
            if (statusChange.isEnable(type)) {
                lastEffectValue_[i] = 0;
            }
        }
    }
}

THUMB void btl::AutoActionParam::disableStatusChange2(int action, dq5::level::ActionParam::ACTIONTYPE type, int action1, int action2, int action3, BattleSelectTargetParam& param)
{
    if (actionIndex_ == action) {
        int targetCount = 0;
        int count = param.getSourceCount();
        for (int i = 0; i < count; i++) {
            status::StatusChange& statusChange = param.getSourceCharacterStatus(i)->getHaveStatusInfo().getStatusChange();
            if (statusChange.isEnable(type)) {
                if (action1 == statusChange.getActionIndex(type)) {
                    targetCount++;
                }
                if (action2 == statusChange.getActionIndex(type)) {
                    targetCount++;
                }
                if (action3 == statusChange.getActionIndex(type)) {
                    targetCount++;
                }
            }
        }
        if (targetCount) {
            for (int i = 0; i < count; i++) {
                lastEffectValue_[i] = 0;
            }
        }
    }
}
