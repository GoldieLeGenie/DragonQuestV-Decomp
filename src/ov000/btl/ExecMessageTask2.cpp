#include "ov000/btl/ExecMessageTask2.hpp"
#include "ov000/btl/BattleActorAnimation.hpp"
#include "ov000/btl/BattleActorEffect.hpp"
#include "ov000/btl/BattleActorMacro.hpp"
#include "ov000/btl/BattleActorSound.hpp"
#include "ov000/btl/BattleEffectManager.hpp"
#include "ov000/btl/BattleMessage.hpp"
#include "ov000/status/MonsterStatus.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/status/BaseAction.hpp"
#include "main/status/UseActionParam.hpp"

inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline int status::UseActionParam::getCurrentTargetIndex() { return currentTargetIndex_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int status::HaveStatusInfo::getDrawCtrlId() { return drawCtrlId_; }
inline int status::MonsterStatus::getMonsterIndex() { return characterIndex_; }
inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }

status::UseActionParam* btl::ExecMessageTask2::useActionParam_;

THUMB void btl::ExecMessageTask2::initialize()
{
    wait_ = false;
    if (useActionParam_->getCurrentTargetIndex() < 1) {
        execute_ = true;
    }
    else {
        status::BaseAction::execActionExecuteSpecial();
        execute_ = false;
        return;
    }
    BattleActorAnimation::setExecAnimation(*useActionParam_);
    BattleActorAnimation::gattaiSlimeStart(useActionParam_->getActorCharacterStatus(), useActionParam_->getActionIndex());
    BattleActorEffect::setExecEffect(*useActionParam_);
    BattleActorMacro::setExecMacro(*useActionParam_);
    message_ = BattleMessage::setExecMessage(*useActionParam_);
    BattleAutoFeed::setExecuteMessage();
    useActionParam_->getActorCharacterStatus()->setMenuStatusFlag(status::HaveStatusInfo::ExecuteAction);
    if (checkCommonExec(*useActionParam_)) {
        BattleActorSound::playActionStartSound(*useActionParam_);
        if (useActionParam_->getActionIndex() == 0x9e) {
            wait_ = true;
        }
        if (useActionParam_->getActionIndex() == 0x52) {
            status::CharacterStatus* actor = useActionParam_->getActorCharacterStatus();
            if (actor->getCharacterType() == MONSTER && ((status::MonsterStatus*)actor)->getMonsterIndex() == 0x9c) {
                wait_ = true;
            }
        }
    }
}

THUMB void btl::ExecMessageTask2::terminate()
{
}

THUMB void btl::ExecMessageTask2::execute()
{
    if (execute_) {
        bool kingSlimeFlag = BattleEffectManager::getSingleton()->isEndWait();
        if (useActionParam_->getActionIndex() == 0x9e && BattleMonsterDraw2::getSingleton().isAppearKingSlime2()) {
            BattleActorAnimation::gattaiSlime(useActionParam_->getActorCharacterStatus(), useActionParam_->getActionIndex());
            wait_ = false;
        }
        if (useActionParam_->getActionIndex() == 0x52) {
            status::CharacterStatus* actor = useActionParam_->getActorCharacterStatus();
            if (actor->getCharacterType() == MONSTER && ((status::MonsterStatus*)actor)->getMonsterIndex() == 0x9c) {
                if (BattleMonsterDraw2::getSingleton().getMonster(actor->getHaveStatusInfo().getDrawCtrlId()).isLastFrame()) {
                    wait_ = false;
                }
            }
        }
    }
}

THUMB int btl::ExecMessageTask2::isEnd()
{
    if (!execute_) {
        return true;
    }
    if (wait_) {
        return false;
    }
    if ((BattleAutoFeed::isEndExecuteMessage() || !message_) && BattleEffectManager::getSingleton()->isEndWait()) {
        return true;
    }
    return false;
}

THUMB bool btl::ExecMessageTask2::checkCommonExec(status::UseActionParam& useActionParam)
{
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    if (actor->getHaveStatusInfo().isStatusChangeRelease()) {
        return false;
    }
    if (actor->getHaveStatusInfo().isDeath()) {
        if (actor->getHaveStatusInfo().isSelfImmolation() == true) {
            return true;
        }
        if (actor->getHaveStatusInfo().isDamageMyself() == true) {
            return true;
        }
        if (actor->getHaveStatusInfo().isMahokantaCounter() == true) {
            return true;
        }
        if (useActionParam.getActionIndex() == 0x1eb) {
            return true;
        }
    }
    if (actor->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
        if (actor->getHaveStatusInfo().isMahokantaCounter() == true) {
            return true;
        }
    }
    if (!actor->getHaveStatusInfo().isAttackEnable()) {
        return false;
    }
    if (actor->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DORAGORAM) == 1) {
        return false;
    }
    if (actor->getHaveStatusInfo().isCurse1()) {
        return false;
    }
    return true;
}
