#pragma ipa file
#include "main/status/CharacterStatus.hpp"

inline bool status::CharacterStatus::isDeathDisable()
{
    return false;
}

inline void status::CharacterStatus::setMosyasRelease()
{
}

inline void status::CharacterStatus::setMosyasChange(int monsterIndex)
{
}

inline void status::CharacterStatus::setMosyasChange(CharacterStatus* target)
{
}

inline void status::CharacterStatus::printAction()
{
}

inline void status::CharacterStatus::print()
{
}

THUMB status::CharacterStatus::CharacterStatus()
    : characterIndex_(-1), damageAnimation_(NoAnim), damageAnimationMulti_(NoAnim)
{
}

THUMB status::CharacterStatus::~CharacterStatus()
{
}

THUMB bool status::CharacterStatus::isActionEnable()
{
    return haveStatusInfo_.isActionEnable();
}

THUMB bool status::CharacterStatus::isActionEnableWithoutDragoram()
{
    return haveStatusInfo_.isActionEnableWithoutDragoram();
}

THUMB void status::CharacterStatus::setup(CharacterType type, int group, int index)
{
    if (type == MONSTER) {
        haveStatusInfo_.setup(index, false);
        haveStatusInfo_.haveBattleStatus_ = &haveBattleStatus_;
        haveBattleStatus_.setup(MONSTER, group, index);
        haveBattleStatus_.haveStatusInfo_ = &haveStatusInfo_;
    }
    menuStatusFlag_.clear();
}

THUMB void status::CharacterStatus::setMenuStatusFlag(HaveStatusInfo::DiffStatus status)
{
    menuStatusFlag_.clear();
    menuStatusFlag_.set(1 << status);
}

THUMB void status::CharacterStatus::setNoneAnimation()
{
    damageAnimationFlag_.clear();
    damageAnimation_ = NoAnim;
    damageAnimationMulti_ = NoAnim;
}

THUMB void status::CharacterStatus::setDamageAnimation()
{
    damageAnimationFlag_.set(FLAG_ANIMATION_DAMAGE);
}

THUMB void status::CharacterStatus::clearDamageAnimation()
{
    damageAnimationFlag_.remove(FLAG_ANIMATION_DAMAGE);
}

THUMB bool status::CharacterStatus::isDamageAnimation()
{
    return damageAnimationFlag_.check(FLAG_ANIMATION_DAMAGE);
}

THUMB void status::CharacterStatus::setAddDamageAnimation()
{
    damageAnimationFlag_.set(FLAG_ANIMATION_DAMAGE_ADD);
}

THUMB void status::CharacterStatus::clearAddDamageAnimation()
{
    damageAnimationFlag_.remove(FLAG_ANIMATION_DAMAGE_ADD);
}

THUMB void status::CharacterStatus::setDeathAnimation()
{
    damageAnimationFlag_.set(FLAG_ANIMATION_DEATH);
}

THUMB void status::CharacterStatus::clearDeathAnimation()
{
    damageAnimationFlag_.remove(FLAG_ANIMATION_DEATH);
}

THUMB bool status::CharacterStatus::isDeathAnimation()
{
    return damageAnimationFlag_.check(FLAG_ANIMATION_DEATH);
}

THUMB void status::CharacterStatus::setDisappearAnimation()
{
    damageAnimationFlag_.set(FLAG_ANIMATION_DISAPPEAR);
}

THUMB void status::CharacterStatus::clearDisappearAnimation()
{
    damageAnimationFlag_.remove(FLAG_ANIMATION_DISAPPEAR);
}

THUMB bool status::CharacterStatus::isDisappearAnimation()
{
    return damageAnimationFlag_.check(FLAG_ANIMATION_DISAPPEAR);
}

THUMB void status::CharacterStatus::setEscapeAnimation()
{
    damageAnimationFlag_.set(FLAG_ANIMATION_ESCAPE);
}

THUMB void status::CharacterStatus::clearEscapeAnimation()
{
    damageAnimationFlag_.remove(FLAG_ANIMATION_ESCAPE);
}

THUMB bool status::CharacterStatus::isEscapeAnimation()
{
    return damageAnimationFlag_.check(FLAG_ANIMATION_ESCAPE);
}

THUMB void status::CharacterStatus::setRebirthAnimation()
{
    damageAnimationFlag_.set(FLAG_ANIMATION_REBIRTH);
}

THUMB void status::CharacterStatus::clearRebirthAnimation()
{
    damageAnimationFlag_.remove(FLAG_ANIMATION_REBIRTH);
}

THUMB bool status::CharacterStatus::isRebirthAnimation()
{
    return damageAnimationFlag_.check(FLAG_ANIMATION_REBIRTH);
}
