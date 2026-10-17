#pragma ipa file
#include "ov000/btl/BattleActorExec2.hpp"
#include "ov000/btl/BattleActor.hpp"
#include "main/status/BaseAction.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/status/UseItem.hpp"

inline status::HaveItem& status::HaveStatusInfo::getHaveItem() { return haveItem_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline void status::UseActionParam::setActorCharacterStatus(CharacterStatus* info) { actorCharacterStatus_ = info; }
inline int status::UseActionParam::getTargetCount() { return targetCount_; }
inline int status::UseActionParam::getAddActionIndex() { return addActionIndex_; }
inline void status::UseActionParam::clearAddActionIndex() { addActionIndex_ = 0; }
inline int status::UseActionParam::getItemSortIndex() { return itemSortIndex_; }
inline void status::UseActionParam::setCurrentTargetIndex(int index) { currentTargetIndex_ = index; }
inline bool status::UseActionParam::isResult() { return result_; }
inline void btl::ExecActionTask2::setup(status::UseActionParam* useActionParam) { useActionParam_ = useActionParam; }
inline void btl::ExecMessageTask2::setup(status::UseActionParam* useActionParam) { useActionParam_ = useActionParam; }
inline void btl::AfterActionTask2::setup(status::UseActionParam* useActionParam) { useActionParam_ = useActionParam; }
inline void btl::EndTask::setup(status::UseActionParam* useActionParam) { useActionParam_ = useActionParam; }

THUMB void btl::BattleActionExec::initialize_user()
{
    resister(0, &execActionTask_);
    resister(1, &beforeMessageTask_);
    resister(2, &execMessageTask_);
    resister(3, &specialMessageTask_);
    resister(4, &resultMessageTask_);
    resister(5, &afterMessageTask_);
    resister(6, &endTask_);
}

THUMB void btl::BattleActionExec::terminate_user()
{
}

THUMB void btl::BattleTargetExec::initialize()
{
    end_ = false;
}

THUMB void btl::BattleTargetExec::terminate()
{
}

THUMB void btl::BattleTargetExec::execute()
{
    if (!battleActionExec_.execute()) {
        end_ = true;
    }
}

THUMB int btl::BattleTargetExec::isEnd()
{
    return end_;
}

THUMB void btl::BattleActorExec2::initialize_user()
{
    if (useActionParam_->getTargetCount() == 0) {
        resister(0, &battleTargetExec_[0]);
        return;
    }
    for (int i = 0; i < useActionParam_->getTargetCount(); i++) {
        resister(i, &battleTargetExec_[i]);
    }
}

THUMB void btl::BattleActorExec2::interruptResister(int index)
{
    if (index < useActionParam_->getTargetCount()) {
        resister(index, &battleTargetExec_[index]);
    }
    if (useActionParam_->getAddActionIndex()) {
        int actionIndex = useActionParam_->getAddActionIndex();
        status::CharacterStatus* actor = useActionParam_->getActorCharacterStatus();
        useActionParam_->clear();
        useActionParam_->setActorCharacterStatus(actor);
        useActionParam_->getActorCharacterStatus()->getHaveBattleStatus().setActionIndex(actionIndex);
        useActionParam_->setActionIndex(actionIndex);
        useActionParam_->clearAddActionIndex();
        BattleActor::setActionTargetOnTurn(useActionParam_, false);
        clear();
        if (useActionParam_->getTargetCount() == 0) {
            resister(0, &battleTargetExec_[0]);
            return;
        }
        for (int i = 0; i < useActionParam_->getTargetCount(); i++) {
            resister(i, &battleTargetExec_[i]);
        }
    }
}

THUMB void btl::BattleActorExec2::terminate_user()
{
}

THUMB void btl::BattleActorExec2::setup(status::UseActionParam* useActionParam)
{
    useActionParam_ = useActionParam;
    BeforeMessageTask2::setup(useActionParam_);
    ExecActionTask2::setup(useActionParam_);
    ExecMessageTask2::setup(useActionParam_);
    SpecialMessageTask2::setup(useActionParam_);
    ResultMessageTask2::setup(useActionParam_);
    AfterMessageTask2::setup(useActionParam_);
    AfterActionTask2::setup(useActionParam_);
    EndTask::setup(useActionParam_);
    BattleActor::selectAI(useActionParam_, false);
    BattleActor::setActionTargetOnTurn(useActionParam_, true);
    BattleActor::selectMosyasTarget(useActionParam_);
    useActionParam_->setCurrentTargetIndex(0);
}

THUMB void btl::BattleActorExec2::cleanup()
{
    status::BaseAction::afterAction();
    if (useActionParam_->getActorCharacterStatus()->getHaveBattleStatus().getSelectCommand() == 3) {
        int sortIndex = useActionParam_->getItemSortIndex();
        int itemIndex_ = useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().getHaveItem().getItem(sortIndex);
        if (status::UseItem::isLost(itemIndex_)) {
            if (useActionParam_->isResult()) {
                useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().getHaveItem().del(sortIndex);
            }
            else if (itemIndex_ == 0xB6) {
                useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().getHaveItem().del(sortIndex);
            }
        }
    }
}

THUMB void btl::BattleActorFinish::initialize_user()
{
    resister(0, &afterActionTask_);
}

THUMB void btl::BattleActorFinish::terminate_user()
{
}
