#include "ov000/btl/AutoAction.hpp"
#include "ov000/btl/BattleSelectTarget.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/UseAction.hpp"

inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int btl::BattleSelectTargetParam::getSourceCount() { return sourceCount_; }
inline int btl::AutoActionParam::isBossMode() { return bossFlag_; }

THUMB void btl::DefenceAutoActionParam::setupTarget()
{
    battleSelectTargetParam_.clear();
    status::UseAction::UseType useType = status::UseAction::getUseType(actionIndex_);
    if (useType == status::UseAction::Enemy) {
        BattleSelectTarget::setTargetMonster(&battleSelectTargetParam_);
    }
    if ((unsigned int)useType <= status::UseAction::Friend) {
        BattleSelectTarget::setTargetPlayer(&battleSelectTargetParam_);
    }
    if (player_->getCharacterType() == PLAYER) {
        if (actionIndex_ == 0xE6 || actionIndex_ == 0x49) {
            BattleSelectTarget::setTargetPlayerWithDeath(&battleSelectTargetParam_);
            if (status::UseAction::getUseType(actionIndex_) == status::UseAction::Myself) {
                battleSelectTargetParam_.sourceCount_ = 1;
                battleSelectTargetParam_.setSourceCharacterStatus(0, player_);
            }
        }
    }
}

THUMB void btl::DefenceAutoActionParam::calcEffectValue()
{
    if (player_->getCharacterType() == PLAYER) {
        effectValue_ = 1000;
        if (actionIndex_ == 0x1D) {
            effectValue_ = 500;
        }
        if (actionIndex_ == 0xE4) {
            effectValue_ = 400;
        }
        if (actionIndex_ == 0x1F) {
            effectValue_ = 500;
        }
        if (actionIndex_ == 0x65) {
            effectValue_ = 500;
        }
    }
    for (int i = 0; i < MONSTER_MAX; i++) {
        targetEffectValue_[i] = effectValue_;
    }
}

THUMB void btl::DefenceAutoActionParam::calcEffectValueException()
{
    BattleSelectTargetParam playerBattleSelectTargetParam;
    BattleSelectTargetParam monsterBattleSelectTargetParam;
    playerBattleSelectTargetParam.clear();
    BattleSelectTarget::setTargetPlayer(&playerBattleSelectTargetParam);
    monsterBattleSelectTargetParam.clear();
    BattleSelectTarget::setTargetMonster(&monsterBattleSelectTargetParam);
    if (!isBossMode()) {
        enableTargetRukaniRukanan(0x29, monsterBattleSelectTargetParam, playerBattleSelectTargetParam);
        enableTargetRukaniRukanan(0x2C, monsterBattleSelectTargetParam, playerBattleSelectTargetParam);
        enableTargetRukaniRukanan(0xE6, monsterBattleSelectTargetParam, playerBattleSelectTargetParam);
    }
    enableTargetMahotone(0x1D, monsterBattleSelectTargetParam);
    enableTargetMahotone(0xE4, monsterBattleSelectTargetParam);
    enableTargetInstantDeath(0x25, monsterBattleSelectTargetParam, playerBattleSelectTargetParam);
    enableMpZeroTargetEnable(0x60, monsterBattleSelectTargetParam);
    enableMpZeroTargetEnable(0x61, monsterBattleSelectTargetParam);
    enableMpZeroTargetEnable(0x62, monsterBattleSelectTargetParam);
    enableTargetFubaha(0x2D, playerBattleSelectTargetParam, monsterBattleSelectTargetParam);
}

THUMB void btl::DefenceAutoActionParam::calcCorrectEffectVelue()
{
    calcCorrectEffectValueForMonster();
    calcCorrectEffectValueForPlayer();
    calcCorrectEffectVelueMahokanta();
}

THUMB void btl::DefenceAutoActionParam::calcCorrectEffectValueForMonster()
{
    BattleSelectTargetParam tempBattleSelectTargetParam;
    tempBattleSelectTargetParam.clear();
    BattleSelectTarget::setTargetMonster(&tempBattleSelectTargetParam);
    disableTarget2Count(0x19, tempBattleSelectTargetParam);
    disableTarget2Count(0x1B, tempBattleSelectTargetParam);
    disableTarget2Count(0x5A, tempBattleSelectTargetParam);
    disableTarget2Count(0x5D, tempBattleSelectTargetParam);
    disableTarget2Count(0x1F, tempBattleSelectTargetParam);
    disableOnceUse(0x1D, tempBattleSelectTargetParam);
    disableOnceUse(0xE4, tempBattleSelectTargetParam);
    disableOnceUse(0x5C, tempBattleSelectTargetParam);
    disableOnceUse(0x65, tempBattleSelectTargetParam);
    disableOnceUse(0x63, tempBattleSelectTargetParam);
    disableOnceUse(0x64, tempBattleSelectTargetParam);
    disableOnceUse(0x66, tempBattleSelectTargetParam);
}

THUMB void btl::DefenceAutoActionParam::calcCorrectEffectValueForPlayer()
{
    BattleSelectTargetParam playerBattleSelectTargetParam;
    BattleSelectTargetParam monsterBattleSelectTargetParam;
    playerBattleSelectTargetParam.clear();
    BattleSelectTarget::setTargetPlayer(&playerBattleSelectTargetParam);
    BattleSelectTarget::setTargetMonster(&monsterBattleSelectTargetParam);
    if (isBossMode()) {
        disableStatusChange2(0x29, dq5::level::ActionParam::ACTIONTYPE_DF_HENKA, 0x29, 0x2C, 0xE6, playerBattleSelectTargetParam);
        disableStatusChange2(0x2C, dq5::level::ActionParam::ACTIONTYPE_DF_HENKA, 0x29, 0x2C, 0xE6, playerBattleSelectTargetParam);
        disableStatusChange2(0xE6, dq5::level::ActionParam::ACTIONTYPE_DF_HENKA, 0x29, 0x2C, 0xE6, playerBattleSelectTargetParam);
    }
    else {
        disableOnceUse(0x29, playerBattleSelectTargetParam);
        disableOnceUse(0x2C, playerBattleSelectTargetParam);
        disableOnceUse(0xE6, playerBattleSelectTargetParam);
    }
    if (isBossMode()) {
        disableStatusChange(0x2D, dq5::level::ActionParam::ACTIONTYPE_FUBAHA, playerBattleSelectTargetParam);
    }
    else {
        disableOnceUse(0x2D, playerBattleSelectTargetParam);
    }
    disableOnceUse(0x25, playerBattleSelectTargetParam);
}

THUMB void btl::DefenceAutoActionParam::calcCorrectEffectVelueMahokanta()
{
    if (!status::UseAction::isMahokanta(actionIndex_)) {
        return;
    }
    targetCount_ = battleSelectTargetParam_.getSourceCount();
    int count = 0;
    for (int i = 0; i < targetCount_; i++) {
        status::CharacterStatus* target = battleSelectTargetParam_.getSourceCharacterStatus(i);
        if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA)) {
            count++;
        }
    }
    if (count) {
        for (int i = 0; i < targetCount_; i++) {
            lastEffectValue_[i] = 0;
        }
    }
}
