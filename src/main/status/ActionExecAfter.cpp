#include "main/status/ActionExecAfter.hpp"
#include "main/status/ActionMessage.hpp"
#include "main/status/BaseActionStatus.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "main/dss/UnkRandom.hpp"

inline status::StatusChange& status::HaveStatusInfo::getStatusChange()
{
    return statusChange_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline int status::HaveBattleStatus::getItemSortIndex() { return sortIndex_; }
inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index) { return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned long dq5::level::ActionParam::getEndMes() { return endMes; }
inline bool status::BaseActionStatus::checkFlag(unsigned int flag) { return flag_.check(flag); }
inline void status::BaseActionStatus::removeFlag(unsigned int flag) { flag_.remove(flag); }
inline int status::BaseActionStatus::getWork() { return work_; }
inline bool status::BaseActionStatus::isMahokantaMessage() { return mahokantaMessFlag_; }
inline void status::BaseActionStatus::setMahokantaMessage(bool flag) { mahokantaMessFlag_ = flag; }
inline bool status::BaseActionStatus::isConfusionMessage() { return confusionMessFlag_; }
inline void status::BaseActionStatus::setConfusionMessage(bool flag) { confusionMessFlag_ = flag; }
inline bool status::BaseActionStatus::isSleepMessage() { return sleepMessFlag_; }
inline void status::BaseActionStatus::setSleepMessage(bool flag) { sleepMessFlag_ = flag; }
inline bool status::BaseActionStatus::isBaikirutoMessage() { return baikirutoMessFlag_; }
inline void status::BaseActionStatus::setBaikirutoMessage(bool flag) { baikirutoMessFlag_ = flag; }
inline void status::UseActionMessage::setExecMessage(int index, int message) { execMessage_[index] = message; }
inline void status::UseActionMessage::setResultMessage(int index, int message) { resultMessage_[index] = message; }
inline int status::UseActionMessage::getResultMessage(int index) { return resultMessage_[index]; }
inline void status::UseActionMessage::setAddMessage(int index, int message) { addMessage_[index] = message; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline void status::UseActionParam::setTargetCharacterStatus(int index, CharacterStatus* info) { targetCharacterStatus_[index] = info; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline void status::UseActionParam::setAddActionIndex(int actionIndex)
{
    preActionIndex_ = actionIndex_;
    addActionIndex_ = actionIndex;
}
inline int status::UseActionParam::getCurrentTargetIndex() { return currentTargetIndex_; }
inline void status::UseActionParam::setTargetCount(int count) { targetCount_ = count; }
inline int status::UseActionParam::getTargetCount() { return targetCount_; }
inline status::UseActionMessage& status::UseActionParam::getUseActionMessage(int index) { return message_[index]; }
inline void status::UseActionParam::setResult(bool flag) { result_ = flag; }
inline bool status::UseActionParam::isResult() { return result_; }
inline bool status::UseActionParam::isTargetResult(int index) { return targetResult_[index]; }

THUMB bool status::ActionExecAfter::execAfterOne(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    int index = useActionParam->getCurrentTargetIndex();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(index);
    if (index == 0 && isDoubleAction(useActionParam->getActorCharacterStatus(), actionIndex)) {
        if (useActionParam->getTargetCharacterStatus(0)->getHaveStatusInfo().isDeath()) {
            useActionParam->setTargetCharacterStatus(1, NULL);
            useActionParam->setTargetCount(1);
        }
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setKaishin(false);
    }
    if (useActionParam->getActionIndex() == 0xb4) {
        useActionParam->setAddActionIndex(0x1e4);
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setKillMyself(true);
    }
    if (BaseActionStatus::isMahokantaMessage()) {
        BaseActionStatus::setMahokantaMessage(false);
        int index = useActionParam->getCurrentTargetIndex();
        ActionMessage::setResultMessage(useActionParam->getUseActionMessage(index), 0, 0);
    }
    if (BaseActionStatus::isConfusionMessage()) {
        BaseActionStatus::setConfusionMessage(false);
        int index = useActionParam->getCurrentTargetIndex();
        ActionMessage::setResultMessage(useActionParam->getUseActionMessage(index), BaseActionStatus::getWork(), 0);
    }
    if (BaseActionStatus::isSleepMessage()) {
        BaseActionStatus::setSleepMessage(false);
        int index = useActionParam->getCurrentTargetIndex();
        ActionMessage::setResultMessage(useActionParam->getUseActionMessage(index), BaseActionStatus::getWork(), 0);
    }
    if (BaseActionStatus::isBaikirutoMessage()) {
        BaseActionStatus::setBaikirutoMessage(false);
        int index = useActionParam->getCurrentTargetIndex();
        ActionMessage::setResultMessage(useActionParam->getUseActionMessage(index), BaseActionStatus::getWork(), 0);
    }
    if (UseAction::getDamageType(useActionParam->getActionIndex()) == UseAction::DamageTypeSleep && !useActionParam->isResult()) {
        int index = useActionParam->getCurrentTargetIndex();
        CharacterStatus* target = useActionParam->getTargetCharacterStatus(index);
        if (target != NULL && target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
            ActionMessage::setResultMessage(useActionParam->getUseActionMessage(index), 0xc3b0f, 0);
        }
    }
    if (useActionParam->getTargetCharacterStatus(index) != NULL && target->getHaveStatusInfo().isLifeStoneEnable()) {
        ActionMessage::setResultMessage(useActionParam->getUseActionMessage(index), 0xc3b69, 0);
    }
    if (actionIndex == 0x1c8 && index == useActionParam->getTargetCount() - 1) {
        int mess = dq5::level::ActionParam::getRecord(actionIndex)->getEndMes();
        useActionParam->getUseActionMessage(index).setAddMessage(0, mess);
    }
    if (actionIndex == 0xf1 && useActionParam->isResult() && UnkDssRand::rand(8) == 0) {
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().execThrow(useActionParam->getActorCharacterStatus()->getHaveBattleStatus().getItemSortIndex());
        ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3ab3, 0);
    }
    if (actionIndex == 0x13f && useActionParam->isResult() && UnkDssRand::rand(8) == 0) {
        UseActionFlag::setBreakPrayRing(true);
        ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3ab3, 0);
    }
    if (actionIndex == 0x1a0) {
        ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3bfc, 0);
    }
    if (actionIndex == 0x1ec) {
        if (useActionParam->getActorCharacterStatus() != NULL) {
            int index = useActionParam->getTargetCount() - 1;
            if (index == useActionParam->getCurrentTargetIndex()) {
                useActionParam->getUseActionMessage(index).setAddMessage(0, 0xc3b67);
                useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setExecuteMeganteRing(true);
            }
        }
        HaveStatusInfo::setGlbMeganteRing(false);
    }
    if (actionIndex == 0x1eb) {
        ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3b6e, 0);
    }
    return true;
}

THUMB bool status::ActionExecAfter::execAfter(UseActionParam* useActionParam, int flag)
{
    int actionIndex = useActionParam->getActionIndex();
    if (useActionParam->getActorCharacterStatus() != NULL) {
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setKaishin(false);
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setTsukon1(false);
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setTsukon2(false);
    }
    if (actionIndex == 0x13d) {
        bool ret = false;
        int count = useActionParam->getTargetCount();
        for (int i = 0; i < count; i++) {
            if (useActionParam->isTargetResult(i)) {
                ret = true;
            }
        }
        if (!ret) {
            for (int i = 0; i < count; i++) {
                useActionParam->getUseActionMessage(i).setExecMessage(0, 0xc40fa);
                useActionParam->getUseActionMessage(i).setResultMessage(0, 0);
            }
        } else {
            for (int i = 0; i < count; i++) {
                useActionParam->getUseActionMessage(i).setResultMessage(0, 0);
                useActionParam->getUseActionMessage(0).setExecMessage(0, 0);
                useActionParam->getUseActionMessage(0).setResultMessage(0, 0xc40f7);
                if (useActionParam->getUseActionMessage(i).getResultMessage(0) == 0xc40fa) {
                    useActionParam->getUseActionMessage(i).setResultMessage(0, 0);
                }
            }
        }
    }
    if (!flag) {
        return true;
    }
    if (useActionParam->getActionIndex() == 0x3f && BaseActionStatus::checkFlag(4)) {
        BaseActionStatus::removeFlag(4);
    }
    if (useActionParam->getActorCharacterStatus() != NULL) {
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setBaikirutoDisable(false);
    }
    if (useActionParam->getActionIndex() == 0x31) {
        int count = useActionParam->getTargetCount();
        for (int i = 0; i < count; i++) {
            if (i != 0) {
                useActionParam->getUseActionMessage(i).setResultMessage(0, 0);
            }
        }
    }
    if (actionIndex == 0x7d) {
        int count = useActionParam->getTargetCount();
        for (int i = 0; i < count; i++) {
            if (useActionParam->isTargetResult(i)) {
                useActionParam->setResult(true);
            }
        }
        for (int i = 0; i < count; i++) {
            if (useActionParam->isResult()) {
                useActionParam->getUseActionMessage(i).setResultMessage(0, 0xc4254);
            } else {
                useActionParam->getUseActionMessage(0).setResultMessage(0, 0xc40d3);
                useActionParam->getUseActionMessage(i).setResultMessage(0, 0);
            }
        }
    }
    return true;
}
