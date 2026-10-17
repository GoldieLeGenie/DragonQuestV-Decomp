#include "main/status/BaseAction.hpp"
#include "main/status/BaseActionStatus.hpp"
#include "main/status/ActionCheckActor.hpp"
#include "main/status/ActionCheckTarget.hpp"
#include "main/status/ActionEffectValue.hpp"
#include "main/status/ActionExecAfter.hpp"
#include "main/status/ActionExecBefore.hpp"
#include "main/status/ActionExecItem.hpp"
#include "main/status/ActionExecRefrection.hpp"
#include "main/status/ActionMessage.hpp"
#include "main/status/ActionMessageSplit.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/leveldata/ActionParam.hpp"

using namespace dq5::level;

status::UseActionParam* status::BaseAction::useActionParam_;
int status::BaseAction::actionIndex_;
int status::BaseAction::executeAction_;
int status::BaseAction::executeActor_;
int status::BaseAction::executeTarget_;
int status::BaseAction::resultFlag_;

inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index)
{
    return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned char dq5::level::ActionParam::getTypeID()
{
    return typeID;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline void status::UseActionParam::setAddActionIndex(int index)
{
    preActionIndex_ = actionIndex_;
    addActionIndex_ = index;
}

THUMB void status::BaseAction::exec(UseActionParam& useActionParam, bool battle)
{
    executeAction_ = 0;
    BaseActionStatus::flag_.clear();
    BaseActionStatus::clear();
    actionIndex_ = useActionParam.actionIndex_;
    useActionParam_ = &useActionParam;
    CharacterStatus* actor = useActionParam.actorCharacterStatus_;
    UseActionFlag::setZaoraruInvalid(false);
    if (actionIndex_ == 0x7f && !useActionParam.targetCharacterStatus_[0]->haveStatusInfo_.isDeath()) {
        UseActionFlag::setZaoraruInvalid(true);
    }
    if (actor != 0) {
        actor->haveStatusInfo_.clearHpInBattle();
        actor->haveStatusInfo_.clearMpInBattle();
        actor->haveStatusInfo_.clearStatusChangeInBattle();
    }
    int targetCount = useActionParam_->targetCount_;
    for (int i = 0; i < targetCount; i++) {
        CharacterStatus* target = useActionParam.targetCharacterStatus_[i];
        if (target != 0) {
            target->haveStatusInfo_.clearHpInBattle();
            target->haveStatusInfo_.clearMpInBattle();
            target->haveStatusInfo_.clearStatusChangeInBattle();
        }
    }

    if (useActionParam_->actorHaveItemSack_ != 0) {
        executeActor_ = 1;
        if (actor != 0) {
            actor->haveStatusInfo_.clearHpInBattle();
            actor->haveStatusInfo_.clearMpInBattle();
            actor->haveStatusInfo_.clearStatusChangeInBattle();
        }
        int count = useActionParam_->targetCount_;
        for (int i = 0; i < count; i++) {
            useActionParam_->currentTargetIndex_ = i;
            execMainRoot(0, useActionParam_->targetCharacterStatus_[i]);
            useActionParam_->targetResult_[i] = resultFlag_;
            ActionMessage::setExecMessage(actionIndex_, useActionParam_->message_[i]);
            ActionMessage::setResultMessage(actionIndex_, *useActionParam_->targetCharacterStatus_[i], useActionParam_->message_[i], useActionParam_->result_);
            ActionMessageSplit::setSplitMessage(useActionParam_->actorCharacterStatus_, useActionParam_->targetCharacterStatus_[i], useActionParam_->message_[0], actionIndex_);
            ActionExecAfter::execAfterOne(useActionParam_);
        }
        afterAction();
        return;
    }

    if (battle) {
        ActionCheckActor::checkStatusRelease(useActionParam_);
    }
    if (!ActionCheckActor::isActionEnable(useActionParam_)) {
        if (useActionParam_->actorCharacterStatus_ != 0) {
            useActionParam_->actorCharacterStatus_->haveBattleStatus_.setActionFailed(actionIndex_);
        }
        executeActor_ = 0;
        return;
    }
    executeActor_ = 1;
    ActionCheckActor::checkConfusion(useActionParam_);
    ActionExecBefore::execBefore(useActionParam_);
    int count = useActionParam_->targetCount_;
    if (count == 0) {
        if (actor != 0) {
            actor->haveStatusInfo_.clearHpInBattle();
            actor->haveStatusInfo_.clearMpInBattle();
            actor->haveStatusInfo_.clearStatusChangeInBattle();
        }
        ActionMessage::setExecMessage(actionIndex_, useActionParam_->message_[0]);
        ActionMessage::setResultMessage(actionIndex_, *useActionParam_->actorCharacterStatus_, useActionParam_->message_[0], useActionParam_->result_);
        execMainRoot(useActionParam_->actorCharacterStatus_, 0);
        ActionMessageSplit::setSplitMessage(useActionParam_->actorCharacterStatus_, 0, useActionParam_->message_[0], actionIndex_);
    } else {
        for (int i = 0; i < count; i++) {
            useActionParam_->currentTargetIndex_ = i;
            ActionExecBefore::execBeforeOne(useActionParam_);
            ActionMessage::setExecMessage(actionIndex_, useActionParam_->message_[i]);
            ActionMessage::setExecMessageAdd(actionIndex_, useActionParam_->message_[i]);
            if (!useActionParam_->targetCharacterStatus_[i]->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_ASTORON) &&
                ActionCheckTarget::checkTargetMahokanta(useActionParam_)) {
                useActionParam_->targetCharacterStatus_[i] = useActionParam_->actorCharacterStatus_;
                useActionParam_->actorCharacterStatus_->haveStatusInfo_.setMahokantaCounter(true);
            }
            if (execMainRoot(useActionParam_->actorCharacterStatus_, useActionParam_->targetCharacterStatus_[i])) {
                useActionParam_->targetResult_[i] = resultFlag_;
                ActionMessage::setResultMessage(actionIndex_, *useActionParam_->targetCharacterStatus_[i], useActionParam_->message_[i], useActionParam_->result_);
                if (actor != 0 && actor->getHaveStatusInfo().isKaishin()) {
                    actor->getHaveStatusInfo().setKaishin(false);
                    useActionParam_->message_[i].spclMessage_[0] = 0xc3916;
                    useActionParam_->actorCharacterStatus_->damageSound_ = CharacterStatus::KaishinSe;
                    if (!UseActionFlag::multiFlag_ || i != 1) {
                        useActionParam_->actorCharacterStatus_->haveStatusInfo_.setFirstKaishin(true);
                    }
                    if (UseActionFlag::multiFlag_ && i == 1) {
                        useActionParam_->actorCharacterStatus_->haveStatusInfo_.setSecondKaishin(true);
                    }
                }
                if ((actionIndex_ == 0x9f || actionIndex_ == 0xa0) && (actor->getHaveStatusInfo().isTsukon1() || actor->getHaveStatusInfo().isTsukon2())) {
                    if (useActionParam_->actorCharacterStatus_->characterType_ == PLAYER) {
                        useActionParam_->message_[0].spclMessage_[0] = 0xc3916;
                        useActionParam_->actorCharacterStatus_->damageSound_ = CharacterStatus::TsukonSe;
                    } else {
                        useActionParam_->message_[0].spclMessage_[1] = 0xc3919;
                        useActionParam_->actorCharacterStatus_->damageSound_ = CharacterStatus::TsukonSe;
                    }
                }
            }
            ActionExecAfter::execAfterOne(useActionParam_);
            ActionMessageSplit::setSplitMessage(useActionParam_->actorCharacterStatus_, useActionParam_->targetCharacterStatus_[i], useActionParam_->message_[i], actionIndex_);
            if (i == 0 && isDoubleAction(useActionParam_->actorCharacterStatus_, actionIndex_) &&
                useActionParam_->targetCharacterStatus_[0]->haveStatusInfo_.isDeath()) {
                useActionParam_->targetCharacterStatus_[1] = 0;
                useActionParam_->targetCount_ = 1;
                break;
            }
        }
    }
    afterAction();
    if (ActionCheckTarget::checkUseMp(useActionParam_)) {
        ActionCheckActor::useMp(useActionParam_);
    }
}

THUMB int status::BaseAction::execMainRoot(CharacterStatus* actor, CharacterStatus* target)
{
    executeTarget_ = 1;
    resultFlag_ = 0;
    if (target != 0) {
        target->haveStatusInfo_.rebirthFlag_ = 0;
    }
    if (target != 0) {
        target->haveStatusInfo_.clearHpInBattle();
        target->haveStatusInfo_.clearMpInBattle();
        target->haveStatusInfo_.clearStatusChangeInBattle();
    }
    execActionSetup();
    execActionExecute();
    execActionAfter();
    useActionParam_->result_ = resultFlag_;
    return executeTarget_;
}

THUMB void status::BaseAction::beforeAction(UseActionParam* useActionParam)
{
    useActionParam_ = useActionParam;
    actionIndex_ = useActionParam->actionIndex_;
    UseActionFlag::addExecActionCount(actionIndex_);
    executeAction_ = 0;
    BaseActionStatus::flag_.clear();
    BaseActionStatus::clear();
    if (useActionParam_->actorCharacterStatus_ != 0) {
        useActionParam_->actorCharacterStatus_->haveStatusInfo_.setMultiAttack(false);
    }
    ActionCheckActor::checkStatusRelease(useActionParam_);
    if (!ActionCheckActor::isActionEnable(useActionParam_)) {
        if (useActionParam_->actorCharacterStatus_ != 0) {
            useActionParam_->actorCharacterStatus_->haveBattleStatus_.setActionFailed(actionIndex_);
        }
        executeActor_ = 0;
        return;
    }
    executeActor_ = 1;
    ActionCheckActor::checkConfusion(useActionParam_);
    ActionExecBefore::execBefore(useActionParam_);
    if (ActionCheckTarget::checkUseMp(useActionParam_)) {
        ActionCheckActor::useMp(useActionParam_);
    }
}

THUMB void status::BaseAction::execActionSetupPre()
{
    if (executeActor_) {
        executeTarget_ = 1;
        resultFlag_ = 0;
        int index = useActionParam_->currentTargetIndex_;
        ActionExecBefore::execBeforeOne(useActionParam_);
        ActionMessage::setExecMessage(useActionParam_->actionIndex_, useActionParam_->message_[index]);
        ActionMessage::setExecMessageAdd(useActionParam_->actionIndex_, useActionParam_->message_[index]);
        ActionMessage::setExecMessageAdd(useActionParam_);
        ActionMessageSplit::useActionParam_ = useActionParam_;
        ActionMessageSplit::setSplitMessage(useActionParam_->actorCharacterStatus_, useActionParam_->targetCharacterStatus_[index], useActionParam_->message_[index], useActionParam_->actionIndex_);
        if (useActionParam_->actionIndex_ == 0xcc) {
            g_Party.setBattleMode();
            if (g_Party.getCarriageOutAliveCount() == 1) {
                useActionParam_->message_[0].spclMessage_[0] = 0xc3a07;
            } else {
                useActionParam_->message_[0].spclMessage_[0] = 0xc3a09;
            }
        }
    }
}

THUMB void status::BaseAction::execActionAfterAfter()
{
    if (executeActor_) {
        int index = useActionParam_->currentTargetIndex_;
        useActionParam_->result_ = resultFlag_;
        ActionMessageSplit::setSplitMessage(useActionParam_->actorCharacterStatus_, useActionParam_->targetCharacterStatus_[index], useActionParam_->message_[index], useActionParam_->actionIndex_);
        ActionExecAfter::execAfterOne(useActionParam_);
    }
}

THUMB void status::BaseAction::execActionTargetSetup()
{
    if (executeActor_ && executeTarget_) {
        if (!ActionCheckActor::isAlive(useActionParam_)) {
            executeActor_ = 0;
            executeTarget_ = 0;
            return;
        }
        if (!ActionCheckTarget::changeMahokantaTarget(useActionParam_)) {
            executeActor_ = 0;
        }
    }
}

THUMB void status::BaseAction::execActionSetup()
{
    if (executeActor_ && executeTarget_) {
        ActionCheckActor::checkActorImmediateItem(useActionParam_);
        ActionCheckActor::checkActorKaishin(useActionParam_);
        ActionEffectValue::specialTargetEffectValue_ = 0;
        ActionCheckTarget::setTargetReSelect(useActionParam_);
    }
}

THUMB bool status::BaseAction::execActionExecute()
{
    if (!executeActor_) {
        return true;
    }
    executeTarget_ = 1;
    int index = useActionParam_->currentTargetIndex_;
    if (!ActionCheckActor::isAlive(useActionParam_)) {
        executeActor_ = 0;
        return false;
    }
    ActionEffectValue::setEffectValue(useActionParam_, false);
    ActionCheckActor::checkEffectValue(useActionParam_);
    ActionEffectValue::execEffectValueWithEquipment(useActionParam_);
    ActionCheckActor::checkActor(useActionParam_);
    if (!ActionCheckTarget::isActionEnable(useActionParam_)) {
        resultFlag_ = 0;
        executeTarget_ = 0;
        return true;
    }
    ActionCheckTarget::checkTarget(useActionParam_);
    if (!ActionExecItem::checkItemForceE(useActionParam_)) {
        executeTarget_ = 0;
        return true;
    }
    ActionEffectValue::execActionDefence(useActionParam_);
    resultFlag_ = ActionExecRefrection::execActionEffect(useActionParam_);
    useActionParam_->targetResult_[index] = resultFlag_;
    execActionResultMessage();
    return true;
}

THUMB void status::BaseAction::execActionExecuteSpecial()
{
    int actionIndex = useActionParam_->actionIndex_;
    if (useActionParam_->currentTargetIndex_ == 1 && isDoubleAction(useActionParam_->actorCharacterStatus_, actionIndex)) {
        ActionCheckActor::checkActorKaishin(useActionParam_);
    }
}

THUMB void status::BaseAction::execActionResultMessage()
{
    int actionIndex = useActionParam_->actionIndex_;
    CharacterStatus* actor = useActionParam_->actorCharacterStatus_;
    int index = useActionParam_->currentTargetIndex_;
    CharacterStatus* target = useActionParam_->targetCharacterStatus_[index];
    if (target != 0) {
        ActionMessage::setResultMessage(actionIndex, *target, useActionParam_->message_[index], resultFlag_);
    } else {
        ActionMessage::setResultMessage(actionIndex, *actor, useActionParam_->message_[index], resultFlag_);
    }
    ActionMessageSplit::setSplitMessage(useActionParam_->actorCharacterStatus_, useActionParam_->targetCharacterStatus_[index], useActionParam_->message_[index], useActionParam_->actionIndex_);

    if (BaseActionStatus::mahokantaMessFlag_) {
        BaseActionStatus::mahokantaMessFlag_ = 0;
        ActionMessage::setResultMessage(useActionParam_->message_[useActionParam_->currentTargetIndex_], BaseActionStatus::work_, 0);
    }
    if (ActionParam::getRecord(actionIndex)->getTypeID() == ActionParam::ACTIONTYPE_MANUSA) {
        if (BaseActionStatus::manusaMessFlag_) {
            BaseActionStatus::manusaMessFlag_ = 0;
            ActionMessage::setResultMessage(useActionParam_->message_[useActionParam_->currentTargetIndex_], BaseActionStatus::work_, 0);
        }
        if (!resultFlag_ && target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MANUSA)) {
            ActionMessage::setResultMessage(useActionParam_->message_[index], target->haveStatusInfo_.statusChange_.getAgainDisableMessage(ActionParam::ACTIONTYPE_MANUSA), 0);
        }
    }
    if (ActionParam::getRecord(actionIndex)->getTypeID() == ActionParam::ACTIONTYPE_KONRAN) {
        if (BaseActionStatus::confusionMessFlag_) {
            BaseActionStatus::confusionMessFlag_ = 0;
            ActionMessage::setResultMessage(useActionParam_->message_[useActionParam_->currentTargetIndex_], BaseActionStatus::work_, 0);
        }
        if (!resultFlag_ && target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_KONRAN)) {
            ActionMessage::setResultMessage(useActionParam_->message_[index], target->haveStatusInfo_.statusChange_.getAgainDisableMessage(ActionParam::ACTIONTYPE_KONRAN), 0);
        }
    }
    if (BaseActionStatus::sleepMessFlag_) {
        BaseActionStatus::sleepMessFlag_ = 0;
        ActionMessage::setResultMessage(useActionParam_->message_[useActionParam_->currentTargetIndex_], BaseActionStatus::work_, 0);
    }
    if (ActionParam::getRecord(actionIndex)->getTypeID() == ActionParam::ACTIONTYPE_NEMURI && !resultFlag_ &&
        target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_NEMURI)) {
        ActionMessage::setResultMessage(useActionParam_->message_[index], target->haveStatusInfo_.statusChange_.getAgainDisableMessage(ActionParam::ACTIONTYPE_NEMURI), 0);
    }
    if (BaseActionStatus::spazzMessFlag_) {
        BaseActionStatus::spazzMessFlag_ = 0;
        ActionMessage::setResultMessage(useActionParam_->message_[useActionParam_->currentTargetIndex_], BaseActionStatus::work_, 0);
    }
    if (BaseActionStatus::baikirutoMessFlag_) {
        BaseActionStatus::baikirutoMessFlag_ = 0;
        ActionMessage::setResultMessage(useActionParam_->message_[useActionParam_->currentTargetIndex_], BaseActionStatus::work_, 0);
    }
    if (BaseActionStatus::poisonMessFlag_) {
        BaseActionStatus::poisonMessFlag_ = 0;
        ActionMessage::setResultMessage(useActionParam_->message_[useActionParam_->currentTargetIndex_], BaseActionStatus::work_, 0);
    }
    if (BaseActionStatus::dragoramMessFlag_) {
        BaseActionStatus::dragoramMessFlag_ = 0;
        ActionMessage::setResultMessage(useActionParam_->message_[useActionParam_->currentTargetIndex_], 0xc3b5d, 0);
    }
    if (BaseActionStatus::mahotoneMessFlag_) {
        BaseActionStatus::mahotoneMessFlag_ = 0;
        ActionMessage::setResultMessage(useActionParam_->message_[useActionParam_->currentTargetIndex_], BaseActionStatus::work_, 0);
    }
    if (ActionParam::getRecord(actionIndex)->getTypeID() == ActionParam::ACTIONTYPE_MAHOTON && !resultFlag_ &&
        target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MAHOTON)) {
        ActionMessage::setResultMessage(useActionParam_->message_[index], target->haveStatusInfo_.statusChange_.getAgainDisableMessage(ActionParam::ACTIONTYPE_MAHOTON), 0);
    }

    if (actionIndex_ == 0x3f) {
        if (BaseActionStatus::flag_.check(3)) {
            if (BaseActionStatus::flag_.check(1)) {
                BaseActionStatus::flag_.remove(1);
                ActionMessage::setResultMessage(useActionParam_->message_[index], 0xc3b4f, 0);
            }
            if (BaseActionStatus::flag_.check(2)) {
                BaseActionStatus::flag_.remove(2);
                ActionMessage::setResultMessage(useActionParam_->message_[index], 0xc3b4b, 0);
            }
        }
        if (!resultFlag_) {
            ActionMessage::setResultMessage(useActionParam_->message_[index], 0, 0);
        }
        useActionParam_->setAddActionIndex(0x1e0);
    }
    if (actionIndex == 0x1e0) {
        if (useActionParam_->preActionIndex_ == 0x3f) {
            actor->haveStatusInfo_.setActionDisable(true);
            actor->haveStatusInfo_.setKillMyself(false);
        }
        if (useActionParam_->preActionIndex_ == 0x18) {
            actor->haveStatusInfo_.setActionDisable(true);
        }
    }
    if (actionIndex == 0x1d4) {
        if (BaseActionStatus::flag_.check(1)) {
            BaseActionStatus::flag_.remove(1);
            ActionMessage::setResultMessage(useActionParam_->message_[index], 0xc3b4f, 0);
        }
        if (BaseActionStatus::flag_.check(2)) {
            BaseActionStatus::flag_.remove(2);
            ActionMessage::setResultMessage(useActionParam_->message_[index], 0xc3b4b, 0);
        }
    }
    if (actionIndex_ == 0x1d6 && target->haveStatusInfo_.isDeath()) {
        ActionMessage::setResultMessage(useActionParam_->message_[index], 0, 0);
    }
    if (actionIndex == 0x18) {
        int current = useActionParam_->currentTargetIndex_;
        if (useActionParam_->targetCharacterStatus_[current]->haveStatusInfo_.isDeath()) {
            if (BaseActionStatus::meganteDamage_) {
                BaseActionStatus::meganteDamage_ = 0;
                useActionParam_->message_[current].resultMessage_[0] = 0xc391c;
            }
        } else if (BaseActionStatus::meganteDamage_) {
            BaseActionStatus::meganteDamage_ = 0;
            useActionParam_->message_[current].resultMessage_[0] = 0xc391c;
            if (useActionParam_->actionDefenceValue_ == 0) {
                useActionParam_->message_[current].resultMessage_[0] = 0xc3af7;
            }
        }
        useActionParam_->setAddActionIndex(0x1e0);
    }
    if (target != 0 && target->haveStatusInfo_.isLifeStoneEnable()) {
        ActionMessage::setResultMessage(useActionParam_->message_[index], 0xc3b69, 0);
    }
    if (actionIndex == 0x1ec) {
        if (useActionParam_->targetCharacterStatus_[index]->haveStatusInfo_.isDeath()) {
            if (BaseActionStatus::meganteDamage_) {
                BaseActionStatus::meganteDamage_ = 0;
                useActionParam_->message_[index].resultMessage_[0] = 0xc391c;
            }
        } else if (BaseActionStatus::meganteDamage_) {
            BaseActionStatus::meganteDamage_ = 0;
            useActionParam_->message_[index].resultMessage_[0] = 0xc391c;
            if (useActionParam_->actionDefenceValue_ == 0) {
                useActionParam_->message_[index].resultMessage_[0] = 0xc3af7;
            }
        }
        HaveStatusInfo& info = actor->getHaveStatusInfo();
        int count = info.haveItem_.getCount();
        for (int i = 0; i < count; i++) {
            if (info.haveItem_.isEquipment(i) && info.haveItem_.getItem(i) == 0x9c) {
                info.execThrow(i);
                break;
            }
        }
    }
    if (useActionParam_->actionIndex_ == 0x2d) {
        int i;
        int count = useActionParam_->targetCount_;
        for (i = 0; i < count; i++) {
            if (i != 0) {
                useActionParam_->message_[i].resultMessage_[0] = 0;
            }
        }
    }
    if (useActionParam_->actionIndex_ == 0x10c) {
        int i;
        int count = useActionParam_->targetCount_;
        for (i = 0; i < count; i++) {
            if (i != 0) {
                useActionParam_->message_[i].resultMessage_[0] = 0;
            }
        }
    }
    if (useActionParam_->actionIndex_ == 0x1c2 && resultFlag_ && useActionParam_->targetCharacterStatus_[0]->haveStatusInfo_.getHp() != 0) {
        int message = useActionParam_->message_[0].resultMessage_[0];
        useActionParam_->message_[0].resultMessage_[0] = 0xc3ce5;
        useActionParam_->message_[0].resultMessage_[1] = message;
    }
    if (actionIndex == 0x1ad) {
        int message = ActionMessage::getFinishMessage(actionIndex);
        useActionParam_->message_[0].resultMessage_[0] = 0xc3d7b;
        useActionParam_->message_[0].addMessage_[0] = message;
    }
    if (actionIndex == 0x1a0) {
        useActionParam_->message_[0].addMessage_[0] = ActionMessage::getFinishMessage(actionIndex);
    }
    if (actionIndex == 0x30) {
        actor->haveBattleStatus_.setActionSelect(HaveBattleStatus::StartTurn, false);
        useActionParam_->setAddActionIndex(actor->haveBattleStatus_.actionIndex_);
    }
    if (actionIndex == 0xe7) {
        actor->haveBattleStatus_.setActionSelect(HaveBattleStatus::StartTurn, false);
        useActionParam_->setAddActionIndex(actor->haveBattleStatus_.actionIndex_);
    }
    if (actionIndex == 0x23 && actor->haveStatusInfo_.effectValue_ == 0) {
        useActionParam_->message_[0].resultMessage_[0] = 0xc3af9;
    }
    if (actionIndex == 0x1de && actor->haveStatusInfo_.isDeath()) {
        useActionParam_->message_[0].resultMessage_[0] = 0xc3926;
    }
}

THUMB void status::BaseAction::execActionAfter()
{
    if (executeActor_ && executeTarget_) {
        ActionExecRefrection::execAddDamage(useActionParam_);
        ActionExecRefrection::execAddDamageItemForceE(useActionParam_);
        ActionCheckActor::checkActionEnd(useActionParam_);
        ActionCheckTarget::checkActionEnd(useActionParam_);
        ActionExecItem::checkItemOther(useActionParam_);
        executeAction_ = 1;
    }
}

THUMB void status::BaseAction::afterAction()
{
    if (executeActor_) {
        ActionExecAfter::execAfter(useActionParam_, true);
        int i;
        int count = useActionParam_->targetCount_;
        for (i = 0; i < count; i++) {
            if (useActionParam_->targetResult_[i]) {
                useActionParam_->result_ = 1;
            }
        }
    }
}
