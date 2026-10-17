#include "ov000/btl/BeforeMessageTask2.hpp"
#include "ov000/btl/BattleActorMacro.hpp"
#include "ov000/btl/BattleMessage.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/status/UseActionMacro.hpp"

inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }

status::UseActionParam* btl::BeforeMessageTask2::useActionParam_;

THUMB void btl::BeforeMessageTask2::setup(status::UseActionParam* useActionParam)
{
    useActionParam_ = useActionParam;
}

THUMB void btl::BeforeMessageTask2::initialize()
{
    BattleActorMacro::setMacroActor(useActionParam_->getActorCharacterStatus(), 0);
    BattleActorMacro::setMacroTarget(useActionParam_->getTargetCharacterStatus(0), 0, 0);
    status::UseActionMacro::setBeforeMacro(useActionParam_->getActorCharacterStatus(), useActionParam_->getActionIndex());
    message_ = BattleMessage::setBeforeMessage(*useActionParam_);
    BattleAutoFeed::setAfterMessage();
}

THUMB void btl::BeforeMessageTask2::terminate()
{
}

THUMB void btl::BeforeMessageTask2::execute()
{
}

THUMB int btl::BeforeMessageTask2::isEnd()
{
    if (message_) {
        return BattleAutoFeed::isEndAfterMessage() != 0;
    }
    return true;
}
