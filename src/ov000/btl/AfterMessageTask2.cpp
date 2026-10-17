#include "ov000/btl/AfterMessageTask2.hpp"
#include "ov000/btl/BattleActorAnimation.hpp"
#include "ov000/btl/BattleActorMacro.hpp"
#include "ov000/btl/BattleEffectManager.hpp"
#include "ov000/btl/BattleMessage.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/BaseAction.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/UseActionParam.hpp"

inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline int status::UseActionParam::getCurrentTargetIndex() { return currentTargetIndex_; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int status::HaveStatusInfo::getDrawCtrlId() { return drawCtrlId_; }
inline int status::HaveStatusInfo::getAddDamage() { return addDamage_; }
inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }
inline void btl::BattleEffectManager::setTarget(int index, status::UseActionParam& useActionParam) { unit_[index].setTarget(useActionParam); }

status::UseActionParam* btl::AfterMessageTask2::useActionParam_;

THUMB void btl::AfterMessageTask2::setup(status::UseActionParam* useActionParam)
{
    useActionParam_ = useActionParam;
}

THUMB void btl::AfterMessageTask2::cleanup()
{
}

THUMB void btl::AfterMessageTask2::initialize()
{
    status::BaseAction::execActionAfter();
    status::BaseAction::execActionAfterAfter();
    int targetIndex = useActionParam_->getCurrentTargetIndex();
    BattleActorMacro::setAddMacro(*useActionParam_, targetIndex);
    message_ = BattleMessage::setAfterMessage(*useActionParam_, targetIndex);
    if (useActionParam_->getTargetCharacterStatus(targetIndex) == 0) {
        return;
    }
    if (useActionParam_->getTargetCharacterStatus(targetIndex)->getHaveStatusInfo().isAddEffectDamage()) {
        if (useActionParam_->getActorCharacterStatus()->getCharacterType() == MONSTER) {
            int drawCtrlId = useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().getDrawCtrlId();
            if (useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().getAddDamage() > 0) {
                if (useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().isDeath()) {
                    BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x22);
                }
                else {
                    BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x23);
                }
                SoundManager::playSe(0x192, 0);
            }
        }
        else if (useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().getAddDamage() > 0) {
            SoundManager::playSe(0x193, 0);
            MenuAPI::shakeMessage();
        }
        useActionParam_->getTargetCharacterStatus(targetIndex)->getHaveStatusInfo().setAddEffectDamage(false);
    }
    if (useActionParam_->getTargetCharacterStatus(targetIndex)->getHaveStatusInfo().isAddEffectRecovery()) {
        SoundManager::playSe(0x1f5, 0);
        useActionParam_->getTargetCharacterStatus(targetIndex)->getHaveStatusInfo().setAddEffectRecovery(false);
    }
    if (useActionParam_->getTargetCharacterStatus(targetIndex)->getHaveStatusInfo().isTargetJouk()) {
        useActionParam_->getTargetCharacterStatus(targetIndex)->getHaveStatusInfo().setTargetJouk(false);
    }
    if (useActionParam_->getTargetCharacterStatus(targetIndex)->getHaveStatusInfo().isAddEffectMahotora()) {
        if (useActionParam_->getActorCharacterStatus()->getCharacterType() != MONSTER && useActionParam_->getActionIndex() == 0x47) {
            int index = BattleEffectManager::getSingleton()->setupEffect(0x1e);
            if (index < 0) {
                return;
            }
            status::UseActionParam* useActionParam = useActionParam_;
            BattleEffectManager::getSingleton()->setTarget(index, *useActionParam);
        }
        useActionParam_->getTargetCharacterStatus(targetIndex)->getHaveStatusInfo().setAddEffectMahotora(false);
    }
    BattleActorAnimation::setAfterAnimation(useActionParam_->getActorCharacterStatus(), 0, useActionParam_->targetCount_, targetIndex);
}

THUMB void btl::AfterMessageTask2::terminate()
{
    if (useActionParam_->getActorCharacterStatus() != 0 && useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().isFirstMosyas()) {
        useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().setFirstMosyas(false);
    }
    useActionParam_->currentTargetIndex_++;
}

THUMB void btl::AfterMessageTask2::execute()
{
    if (useActionParam_->getActorCharacterStatus() != 0 && useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().isMonsterChange()) {
        if (!BattleEffectManager::getSingleton()->isAllEnd()) {
            return;
        }
    }
}

THUMB int btl::AfterMessageTask2::isEnd()
{
    if (message_) {
        if (BattleAutoFeed::isEndAfterMessage()) {
            cleanup();
            return true;
        }
    }
    else {
        cleanup();
        return true;
    }
    return false;
}
