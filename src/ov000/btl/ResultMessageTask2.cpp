#include "ov000/btl/ResultMessageTask2.hpp"
#include "ov000/btl/BattleActorAnimation.hpp"
#include "ov000/btl/BattleActorEffect.hpp"
#include "ov000/btl/BattleActorMacro.hpp"
#include "ov000/btl/BattleMessage.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/status/BaseAction.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/UseActionParam.hpp"

inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline int status::UseActionParam::getCurrentTargetIndex() { return currentTargetIndex_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }

status::UseActionParam* btl::ResultMessageTask2::useActionParam_;

THUMB void btl::ResultMessageTask2::setup(status::UseActionParam* useActionParam)
{
    useActionParam_ = useActionParam;
}

THUMB void btl::ResultMessageTask2::initialize()
{
    bool ret = status::BaseAction::execActionExecute();
    if (ret) {
        int targetIndex = useActionParam_->getCurrentTargetIndex();
        if (useActionParam_->getTargetCharacterStatus(targetIndex) != 0 &&
            useActionParam_->getTargetCharacterStatus(targetIndex)->getHaveStatusInfo().isMosyasRelease()) {
            BattleActorAnimation::setMosyasReverse(useActionParam_->getTargetCharacterStatus(targetIndex));
        }
        BattleActorMacro::setResultMacro(*useActionParam_, targetIndex);
        message_ = BattleMessage::setResultMessage(*useActionParam_, targetIndex);
        BattleAutoFeed::setResultMessage();
        BattleMessage::setShakeMessage(*useActionParam_, targetIndex);
        BattleActorAnimation::setResultAnimation(*useActionParam_, targetIndex);
        status::CharacterStatus* actor = useActionParam_->getActorCharacterStatus();
        if (!actor->getHaveStatusInfo().isStatusChangeRelease()) {
            BattleActorEffect::setResultEffect(*useActionParam_);
        }
        BattleActorEffect::setResultBothEffect(*useActionParam_, targetIndex);
    }
}

THUMB void btl::ResultMessageTask2::terminate()
{
}

THUMB void btl::ResultMessageTask2::execute()
{
}

THUMB int btl::ResultMessageTask2::isEnd()
{
    return BattleAutoFeed::isEndResultMessage() || !message_;
}
