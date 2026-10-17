#include "ov000/btl/SpecialMessageTask2.hpp"
#include "ov000/btl/BattleActorMacro.hpp"
#include "ov000/btl/BattleActorSound.hpp"
#include "ov000/btl/BattleEffectManager.hpp"
#include "ov000/btl/BattleMessage.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/leveldata/EffectParam.hpp"
#include "main/status/BaseAction.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/status/UseActionParam.hpp"

inline dq5::level::EffectParam* dq5::level::EffectParam::getRecord(int index) { return (EffectParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline int status::UseActionParam::getCurrentTargetIndex() { return currentTargetIndex_; }
inline bool status::UseActionFlag::isMultiAttack() { return multiFlag_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline bool status::CharacterStatus::isTsukonSound() { return damageSound_ == TsukonSe; }
inline char dq5::level::EffectParam::getDisplay() { return (byte_1 & 0x78) >> 3; }
inline void dq5::level::EffectParam::setDisplay(char data)
{
    byte_1 &= ~0x78;
    byte_1 += (char)((data << 3) & 0x78);
}
inline void dq5::level::EffectParam::setFrame(unsigned short data) { frame = data; }
inline void btl::BattleEffectManager::setTarget(int index, status::UseActionParam& useActionParam) { unit_[index].setTarget(useActionParam); }
inline void btl::BattleEffectManager::setWaitTime(int index, int frame) { unit_[index].setWaitTime(frame); }

status::UseActionParam* btl::SpecialMessageTask2::useActionParam_;

THUMB void btl::SpecialMessageTask2::setup(status::UseActionParam* useActionParam)
{
    useActionParam_ = useActionParam;
}

THUMB void btl::SpecialMessageTask2::initialize()
{
    status::BaseAction::execActionTargetSetup();
    int targetIndex = useActionParam_->getCurrentTargetIndex();
    if (status::UseActionFlag::isMultiAttack() && useActionParam_->getTargetCharacterStatus(targetIndex) != 0 && targetIndex == 1 &&
        useActionParam_->getActorCharacterStatus()->getCharacterType() == PLAYER) {
        int effectID;
        if (useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().getCharaIndex() == 0x8a) {
            effectID = 0x159;
        }
        else {
            effectID = BattleEffectManager::getSingleton()->getWeaponEffectID((status::PlayerStatus*)useActionParam_->getActorCharacterStatus());
        }
        int effect = BattleEffectManager::getSingleton()->getEffectParam(effectID);
        if (useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().isSecondKaishin() ||
            useActionParam_->getActorCharacterStatus()->isTsukonSound()) {
            char nullpos = dq5::level::EffectParam::getRecord(effect)->getDisplay();
            if (nullpos < 3) {
                nullpos = 2;
            }
            effect = BattleEffectManager::getSingleton()->getEffectParam(0x16f);
            dq5::level::EffectParam::getRecord(effect)->setDisplay(nullpos);
            dq5::level::EffectParam::getRecord(effect)->setFrame(0);
            int index = BattleEffectManager::getSingleton()->setupEffect(0x16f);
            if (index >= 0) {
                status::UseActionParam* useActionParam = useActionParam_;
                BattleEffectManager::getSingleton()->setTarget(index, *useActionParam);
                BattleEffectManager::getSingleton()->setWaitTime(index, 0);
            }
            useActionParam_->getActorCharacterStatus()->getHaveStatusInfo().setSecondKaishin(false);
        }
    }
    BattleActorMacro::setExecMacro(*useActionParam_);
    message_ = BattleMessage::setSpecialMessage(*useActionParam_, targetIndex);
    counter_ = 0;
}

THUMB void btl::SpecialMessageTask2::terminate()
{
}

THUMB void btl::SpecialMessageTask2::execute()
{
    counter_++;
    if (counter_ == 4) {
        BattleActorSound::playCriticalSound(*useActionParam_);
    }
}

THUMB int btl::SpecialMessageTask2::isEnd()
{
    return BattleAutoFeed::isEndExecuteMessage() || !message_;
}
