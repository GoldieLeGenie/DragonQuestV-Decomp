#include "ov000/btl/AutoAction.hpp"
#include "ov000/btl/BattleSelectTarget.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/UseAction.hpp"

inline int status::HaveStatus::getPlayerIndex() const { return playerIndex_; }
inline int status::HaveStatusInfo::getPlayerIndex() const { return haveStatus_.getPlayerIndex(); }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int btl::BattleSelectTargetParam::getSourceCount() { return sourceCount_; }
inline int btl::AutoActionParam::isBossMode() { return bossFlag_; }

THUMB void btl::AssistAutoActionParam::setupTarget()
{
    battleSelectTargetParam_.clear();
    status::UseAction::UseType useType = status::UseAction::getUseType(actionIndex_);
    if (useType == status::UseAction::Enemy) {
        BattleSelectTarget::setTargetMonster(&battleSelectTargetParam_);
    }
    if ((unsigned int)useType <= status::UseAction::Friend) {
        BattleSelectTarget::setTargetPlayer(&battleSelectTargetParam_);
    }
}

THUMB void btl::AssistAutoActionParam::calcEffectValue()
{
    if (player_->getCharacterType() == PLAYER) {
        effectValue_ = 1000;
        if (actionIndex_ == 0x24) {
            effectValue_ = 500;
        }
        if (actionIndex_ == 0x26) {
            effectValue_ = 500;
        }
        if (actionIndex_ == 0x27) {
            effectValue_ = 500;
        }
        if (actionIndex_ == 0x60) {
            effectValue_ = 300;
        }
        if (actionIndex_ == 0x61) {
            effectValue_ = 310;
        }
        if (actionIndex_ == 0x62) {
            effectValue_ = 320;
        }
        if (actionIndex_ == 0x2E) {
            effectValue_ = 3000;
        }
    }
    for (int i = 0; i < MONSTER_MAX; i++) {
        targetEffectValue_[i] = effectValue_;
    }
}

THUMB void btl::AssistAutoActionParam::calcEffectValueException()
{
    BattleSelectTargetParam playerBattleSelectTargetParam;
    BattleSelectTargetParam monsterBattleSelectTargetParam;
    monsterBattleSelectTargetParam.clear();
    BattleSelectTarget::setTargetMonster(&monsterBattleSelectTargetParam);
    enableMpZeroTargetEnable(0x23, monsterBattleSelectTargetParam);
    playerBattleSelectTargetParam.clear();
    BattleSelectTarget::setTargetPlayer(&playerBattleSelectTargetParam);
    enableTargetMahokite(0x24, monsterBattleSelectTargetParam, playerBattleSelectTargetParam);
}

THUMB void btl::AssistAutoActionParam::calcCorrectEffectVelue()
{
    calcCorrectEffectValueForMonster();
    calcCorrectEffectValueForPlayer();
    calcCorrectEffectVelueMahokanta();
}

THUMB void btl::AssistAutoActionParam::calcCorrectEffectValueForMonster()
{
    BattleSelectTargetParam tempBattleSelectTargetParam;
    tempBattleSelectTargetParam.clear();
    BattleSelectTarget::setTargetMonster(&tempBattleSelectTargetParam);
    if (isBossMode()) {
        disableStatusChange2(0x26, dq5::level::ActionParam::ACTIONTYPE_DF_HENKA, 0x26, 0x27, 0, tempBattleSelectTargetParam);
        disableStatusChange2(0x27, dq5::level::ActionParam::ACTIONTYPE_DF_HENKA, 0x26, 0x27, 0, tempBattleSelectTargetParam);
    }
    else {
        disableTarget2Count(0x26, tempBattleSelectTargetParam);
        disableTarget2Count(0x27, tempBattleSelectTargetParam);
    }
}

THUMB void btl::AssistAutoActionParam::calcCorrectEffectValueForPlayer()
{
    BattleSelectTargetParam playerBattleSelectTargetParam;
    BattleSelectTargetParam monsterBattleSelectTargetParam;
    playerBattleSelectTargetParam.clear();
    monsterBattleSelectTargetParam.clear();
    BattleSelectTarget::setTargetPlayer(&playerBattleSelectTargetParam);
    BattleSelectTarget::setTargetMonster(&monsterBattleSelectTargetParam);
    disableStatusChange(0x2E, dq5::level::ActionParam::ACTIONTYPE_BAIKIRUTO, playerBattleSelectTargetParam);
    disableBaikiruto(playerBattleSelectTargetParam, monsterBattleSelectTargetParam);
    disableOnceUse(0x24, playerBattleSelectTargetParam);
}

THUMB void btl::AssistAutoActionParam::disableBaikiruto(BattleSelectTargetParam& player, BattleSelectTargetParam& monster)
{
    if (actionIndex_ != 0x2E) {
        return;
    }
    bool useChara = false;
    if (isBossMode()) {
        if (player_->getHaveStatusInfo().getPlayerIndex() == 4 || player_->getHaveStatusInfo().getPlayerIndex() == 9 || player_->getHaveStatusInfo().getPlayerIndex() == 0xE) {
            useChara = true;
        }
    }
    else {
        if (player_->getHaveStatusInfo().getPlayerIndex() == 4 || player_->getHaveStatusInfo().getPlayerIndex() == 9) {
            useChara = true;
        }
    }
    if (!useChara) {
        int targetCount = player.getSourceCount();
        for (int i = 0; i < targetCount; i++) {
            lastEffectValue_[i] = 0;
        }
        return;
    }
    int count = monster.getSourceCount();
    if (!isBossMode() && count < 2) {
        int targetCount2 = player.getSourceCount();
        for (int i = 0; i < targetCount2; i++) {
            lastEffectValue_[i] = 0;
        }
        return;
    }
    int targetCount = player.getSourceCount();
    for (int i = 0; i < targetCount; i++) {
        player.getSourceCharacterStatus(i);
        status::CharacterStatus* target = player.getSourceCharacterStatus(i);
        if (isBossMode()) {
            if (target->getHaveStatusInfo().getPlayerIndex() != 1 && target->getHaveStatusInfo().getPlayerIndex() != 0xD && target->getHaveStatusInfo().getPlayerIndex() != 0x11) {
                lastEffectValue_[i] = 0;
            }
        }
        else {
            if (target->getHaveStatusInfo().getPlayerIndex() != 1) {
                lastEffectValue_[i] = 0;
            }
        }
    }
}

THUMB void btl::AssistAutoActionParam::calcCorrectEffectVelueMahokanta()
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
