#include "ov000/btl/BattleActorSound.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseActionParam.hpp"

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline bool status::CharacterStatus::isKaishinSound() { return damageSound_ == KaishinSe; }
inline int status::HaveBattleStatus::getIndex() { return index_; }
inline int status::HaveStatusInfo::getUseActionEffectValue() { return effectValue_; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline bool status::UseActionParam::isTargetResult(int index) { return targetResult_[index]; }
inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index) { return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned short dq5::level::ActionParam::getEffectFriend() { return effectFriend; }
inline unsigned short dq5::level::ActionParam::getEffectEnemy() { return effectEnemy; }
inline unsigned short dq5::level::ActionParam::getActionSE() { return actionSE; }
inline unsigned short dq5::level::ActionParam::getStartSE() { return startSE; }
inline unsigned char dq5::level::ActionParam::getTypeID() { return typeID; }
inline char dq5::level::ActionParam::getYaiba() { return byte_1 & 0x1; }

THUMB void btl::BattleActorSound::playActionStartSound(status::UseActionParam& useActionParam)
{
    if (useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getActionDisable()) {
        int index = useActionParam.getActorCharacterStatus()->getHaveBattleStatus().getIndex();
        if (index == 0x6B || index == 0x9F) {
            return;
        }
    }
    switch (dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getStartSE()) {
    case 0:
        break;
    case 2:
        if (useActionParam.getActorCharacterStatus()->getCharacterType() == MONSTER) {
            SoundManager::playSe(0x191, 0);
        }
        else {
            SoundManager::playSe(0x190, 0);
        }
        break;
    case 1:
        SoundManager::playSe(0x132, 0);
        break;
    default:
        if (useActionParam.getActorCharacterStatus()->getCharacterType() == MONSTER) {
            if (useActionParam.getActionIndex() == 0x5E || useActionParam.getActionIndex() == 0x5F) {
                break;
            }
            if (dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getEffectEnemy() == 0) {
                SoundManager::playSe(dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getStartSE(), 0);
            }
        }
        else {
            if (dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getEffectFriend() == 0) {
                SoundManager::playSe(dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getStartSE(), 0);
            }
        }
        break;
    }
}

THUMB void btl::BattleActorSound::playActionResultSound(status::UseActionParam& useActionParam, int currentTarget)
{
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    status::CharacterStatus* target = useActionParam.getTargetCharacterStatus(currentTarget);
    if (actor->getHaveStatusInfo().isCurse2() && actor->getCharacterType() != target->getCharacterType()) {
        return;
    }
    if (useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getActionDisable()) {
        int index = useActionParam.getActorCharacterStatus()->getHaveBattleStatus().getIndex();
        if (index == 0x6B || index == 0x9F) {
            return;
        }
    }
    if (status::UseAction::getDamageType(useActionParam.getActionIndex()) == status::UseAction::DamageTypeDamage) {
        if (target->getHaveStatusInfo().isImmidiateDeath()) {
            SoundManager::playSe(0x192, 0);
            return;
        }
        bool flag = false;
        if ((useActionParam.getActionIndex() == 0x18 || useActionParam.getActionIndex() == 0x1EC) && target->getHaveStatusInfo().getUseActionEffectValue() == 0 && useActionParam.isTargetResult(currentTarget)) {
            flag = true;
        }
        if (target->getHaveStatusInfo().getUseActionEffectValue() > 0 || flag) {
            if (target->getCharacterType() == PLAYER) {
                SoundManager::playSe(0x193, 0);
            }
            else {
                SoundManager::playSe(0x192, 0);
            }
            return;
        }
        if (dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getYaiba()) {
            if (actor->getCharacterType() == MONSTER) {
                if (!useActionParam.isTargetResult(currentTarget)) {
                    SoundManager::playSe(0x194, 0);
                }
            }
            else {
                if (!useActionParam.isTargetResult(currentTarget)) {
                    SoundManager::playSe(0x195, 0);
                }
            }
        }
    }
    else {
        if (useActionParam.getActionIndex() == 0x1CB) {
            return;
        }
        switch (useActionParam.getActionIndex()) {
        case 0x3D:
        case 0x3E:
        case 0x40:
        case 0xE2:
        case 0xE8:
        case 0xF1:
        case 0xF2:
        case 0xF3:
        case 0xF5:
        case 0xFC:
        case 0xFD:
        case 0xFF:
        case 0x100:
            if (!useActionParam.isTargetResult(currentTarget)) {
                return;
            }
            break;
        case 0x1D6:
            if (target->getCharacterType() == PLAYER && useActionParam.getTargetCharacterStatus(currentTarget)->getHaveStatusInfo().isMegazaruRebirth()) {
                SoundManager::playSe(0x229, 0);
            }
            return;
        case 0x1D4:
            if (actor->getCharacterType() == MONSTER) {
                return;
            }
            if (actor->getCharacterType() == PLAYER) {
                if (useActionParam.getTargetCharacterStatus(currentTarget)->getHaveStatusInfo().isMegazaruRebirth()) {
                    SoundManager::playSe(0x229, 0);
                }
                else {
                    SoundManager::playSe(0x1F5, 0);
                }
            }
            return;
        case 0x3F:
            if (actor->getCharacterType() == PLAYER) {
                if (useActionParam.getTargetCharacterStatus(currentTarget)->getHaveStatusInfo().isMegazaruRebirth()) {
                    SoundManager::playSe(0x229, 0);
                }
                else {
                    SoundManager::playSe(0x1F5, 0);
                }
            }
        case 0x2D:
            if (currentTarget != 0) {
                return;
            }
            break;
        }
        if (target->getHaveStatusInfo().isTargetJouk()) {
            if (actor->getCharacterType() == MONSTER) {
                SoundManager::playSe(0x194, 0);
            }
            else {
                SoundManager::playSe(0x195, 0);
            }
            return;
        }
        if (dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getTypeID() == 0x17 && !useActionParam.isTargetResult(currentTarget)) {
            return;
        }
        if (actor->getCharacterType() == PLAYER) {
            if (dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getEffectFriend() == 0) {
                int se = dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getActionSE();
                if (se) {
                    SoundManager::playSe(se, 0);
                }
            }
        }
        else {
            if (useActionParam.getActionIndex() == 0x68) {
                return;
            }
            if (dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getEffectEnemy() == 0) {
                int se = dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getActionSE();
                if (se) {
                    SoundManager::playSe(se, 0);
                }
            }
        }
        if (useActionParam.getActionIndex() == 0x1B9 && target->getCharacterType() == MONSTER) {
            SoundManager::playSe(0x198, 0);
        }
    }
}

THUMB void btl::BattleActorSound::playCriticalSound(status::UseActionParam& useActionParam)
{
    if (useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getActionDisable()) {
        int index = useActionParam.getActorCharacterStatus()->getHaveBattleStatus().getIndex();
        if (index == 0x6B || index == 0x9F) {
            return;
        }
    }
    if (useActionParam.getActorCharacterStatus()->isKaishinSound()) {
        SoundManager::playSe(0x197, 0);
    }
    else if (useActionParam.getActorCharacterStatus()->damageSound_ == status::CharacterStatus::TsukonSe) {
        if (useActionParam.getActorCharacterStatus()->getCharacterType() == PLAYER) {
            SoundManager::playSe(0x197, 0);
        }
        else {
            SoundManager::playSe(0x196, 0);
        }
    }
}
