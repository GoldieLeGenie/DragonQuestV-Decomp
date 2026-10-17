#include "ov000/btl/BattleActorEffect.hpp"
#include "ov000/btl/BattleEffectManager.hpp"
#include "ov000/btl/BattleMonster.hpp"
#include "ov000/btl/MonsterAnimInfo.hpp"
#include "ov000/status/MonsterStatus.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "main/leveldata/EffectParam.hpp"
#include "main/leveldata/MonsterAnim.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseActionParam.hpp"

int btl::BattleActorEffect::wait_;
int btl::BattleActorEffect::both_;

inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline dq5::level::EffectParam* dq5::level::EffectParam::getRecord(int index) { return (EffectParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline int status::UseActionParam::getCurrentTargetIndex() { return currentTargetIndex_; }
inline bool status::UseActionParam::isTargetResult(int index) { return targetResult_[index]; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline bool status::CharacterStatus::isTsukonSound() { return damageSound_ == TsukonSe; }
inline int status::HaveStatusInfo::getDrawCtrlId() { return drawCtrlId_; }
inline int status::MonsterStatus::getMosyasMonsterIndex() { return mosyasMonsterIndex_; }
inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index) { return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned short dq5::level::ActionParam::getEffectFriend() { return effectFriend; }
inline unsigned short dq5::level::ActionParam::getEffectEnemy() { return effectEnemy; }
inline unsigned short dq5::level::ActionParam::getActionSE() { return actionSE; }
inline unsigned char dq5::level::ActionParam::getUseMP() { return useMP; }
inline char dq5::level::ActionParam::getDirect() { return byte_6 & 0x7; }
inline unsigned char dq5::level::EffectParam::getInterval() { return interval; }
inline unsigned short dq5::level::EffectParam::getFrame() { return frame; }
inline char dq5::level::EffectParam::getDisplay() { return (byte_1 & 0x78) >> 3; }
inline void dq5::level::EffectParam::setDisplay(char data)
{
    byte_1 &= ~0x78;
    byte_1 += (char)((data << 3) & 0x78);
}
inline void dq5::level::EffectParam::setFrame(unsigned short data) { frame = data; }
inline void dq5::level::EffectParam::setScale(fx32 data) { scale = data; }
inline dq5::level::MonsterAnim* dq5::level::MonsterAnim::getRecord(int index) { return (MonsterAnim*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline fx32 dq5::level::MonsterAnim::getScale() { return scale; }
inline unsigned short dq5::level::MonsterAnim::getHitframe() { return hitframe; }
inline unsigned short dq5::level::MonsterAnim::getEffect() { return effect; }
inline unsigned char dq5::level::MonsterAnim::getAnimfile() { return animfile; }
inline unsigned char dq5::level::MonsterAnim::getStartframe() { return startframe; }
inline char dq5::level::MonsterAnim::getDisplay() { return byte_1 & 0xF; }
inline void btl::BattleEffectManager::setTarget(int index, status::UseActionParam& useActionParam) { unit_[index].setTarget(useActionParam); }
inline void btl::BattleEffectManager::setTarget(int index, status::CharacterStatus* actor, int anim) { unit_[index].setTarget(actor, anim); }
inline void btl::BattleEffectManager::setWaitTime(int index, int frame) { unit_[index].setWaitTime(frame); }
inline int btl::BattleEffectManager::getHitFrame(int index) { return unit_[index].getHitFrame(); }
inline void btl::BattleEffectManager::setMessageWait(int wait) { wait_ = wait; }
inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }
inline int btl::BattleMonster::getMonsterIndex() { return monsterIndex_; }

THUMB void btl::BattleActorEffect::setResultBothEffect(status::UseActionParam& useActionParam, int target)
{
    int actionIndex = useActionParam.getActionIndex();
    if (!checkCommonExecEffect(useActionParam) || !checkPlayerExecEffect(useActionParam)) {
        return;
    }
    if (useActionParam.getTargetCharacterStatus(target)->getCharacterType() == MONSTER) {
        if (!both_) {
            return;
        }
        both_ = false;
    }
    else {
        int ef = BattleEffectManager::getSingleton()->getEffectParam(dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getEffectFriend());
        if (dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getDirect() == 4 && dq5::level::EffectParam::getRecord(ef)->getInterval()) {
            int se = dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getActionSE();
            if (se) {
                SoundManager::playSe(se, 0);
            }
        }
        return;
    }
    int effectID = dq5::level::ActionParam::getRecord(actionIndex)->getEffectFriend();
    if (effectID) {
        int effect = BattleEffectManager::getSingleton()->getEffectParam(effectID);
        if (actionIndex == 0x1CB) {
            dq5::level::EffectParam::getRecord(effect)->setDisplay(3);
        }
        int index = BattleEffectManager::getSingleton()->setupEffect(effectID);
        if (index >= 0) {
            int wait = BattleAutoFeed::getMessageSpeed();
            BattleEffectManager::getSingleton()->setWaitTime(index, 0);
            BattleEffectManager::getSingleton()->setTarget(index, useActionParam);
        }
    }
}

THUMB void btl::BattleActorEffect::setExecEffect(status::UseActionParam& useActionParam)
{
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    wait_ = 0;
    if (!checkCommonExecEffect(useActionParam)) {
        return;
    }
    int ef = BattleEffectManager::getSingleton()->getEffectParam(dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getEffectFriend());
    if (dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getDirect() == 4 && dq5::level::EffectParam::getRecord(ef)->getInterval()) {
        both_ = true;
        return;
    }
    both_ = false;
    if (useActionParam.getActorCharacterStatus()->getCharacterType() == PLAYER) {
        wait_ = setPlayerEffect(useActionParam);
    }
    else if (useActionParam.getActorCharacterStatus()->getCharacterType() == MONSTER) {
        if ((status::UseAction::getActionType(useActionParam.getActionIndex()) == 1 || useActionParam.getActionIndex() == 0x19D) && actor->getHaveStatusInfo().isMagicDisable()) {
            BattleEffectManager::getSingleton()->setMessageWait(wait_);
            return;
        }
        wait_ = setEnemyEffect(useActionParam);
        if (!actor->getHaveStatusInfo().getActionDisable()) {
            switch (useActionParam.getActionIndex()) {
            case 0x3D:
            case 0x3E:
            case 0x3F:
            case 0xE2:
            case 0x100:
            case 0x1D4:
            case 0x1D6:
                break;
            default:
                wait_ += setResultEnemyEffect(useActionParam);
                break;
            }
        }
    }
    BattleEffectManager::getSingleton()->setMessageWait(wait_);
}

THUMB bool btl::BattleActorEffect::checkCommonExecEffect(status::UseActionParam& useActionParam)
{
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    if (actor->getHaveStatusInfo().isStatusChangeRelease()) {
        return false;
    }
    if (dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getUseMP() && actor->getHaveStatusInfo().isMpFailure()) {
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
        if (useActionParam.getActionIndex() == 0x1EC) {
            return true;
        }
    }
    if (actor->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
        if (useActionParam.getActionIndex() == 0x1D0) {
            return true;
        }
        if (actor->getHaveStatusInfo().isMahokantaCounter() == true) {
            return true;
        }
    }
    if (!actor->getHaveStatusInfo().isAttackEnable()) {
        return false;
    }
    return true;
}

THUMB int btl::BattleActorEffect::setPlayerEffect(status::UseActionParam& useActionParam)
{
    int actionIndex = useActionParam.getActionIndex();
    if (!checkPlayerExecEffect(useActionParam)) {
        return 0;
    }
    int effectID = dq5::level::ActionParam::getRecord(actionIndex)->getEffectFriend();
    if (effectID == 0x12C && useActionParam.getTargetCharacterStatus(0)->getCharacterType() == PLAYER) {
        return 0;
    }
    if (useActionParam.getActionIndex() == 0x56 && useActionParam.getTargetCharacterStatus(0)->getCharacterType() == PLAYER) {
        return 0;
    }
    if (useActionParam.getActionIndex() == 0x198) {
        return 0;
    }
    if (effectID) {
        if (effectID == 0x12C) {
            effectID = BattleEffectManager::getSingleton()->getWeaponEffectID((status::PlayerStatus*)useActionParam.getActorCharacterStatus());
        }
        int effect = BattleEffectManager::getSingleton()->getEffectParam(effectID);
        if (actionIndex == 0x1CB) {
            dq5::level::EffectParam::getRecord(effect)->setDisplay(3);
        }
        int index = BattleEffectManager::getSingleton()->setupEffect(effectID);
        if (index < 0) {
            return 0;
        }
        int wait = BattleAutoFeed::getMessageSpeed();
        if (wait < 0) {
            wait = 0x10;
        }
        BattleEffectManager::getSingleton()->setWaitTime(index, wait);
        BattleEffectManager::getSingleton()->setTarget(index, useActionParam);
        switch (useActionParam.getActorCharacterStatus()->damageSound_) {
        case status::CharacterStatus::KaishinSe:
        case status::CharacterStatus::TsukonSe:
            char nullpos = dq5::level::EffectParam::getRecord(effect)->getDisplay();
            unsigned short hitframe = dq5::level::EffectParam::getRecord(effect)->getFrame();
            effect = BattleEffectManager::getSingleton()->getEffectParam(0x16F);
            dq5::level::EffectParam::getRecord(effect)->setDisplay(nullpos);
            dq5::level::EffectParam::getRecord(effect)->setFrame(hitframe);
            index = BattleEffectManager::getSingleton()->setupEffect(0x16F);
            if (index >= 0) {
                BattleEffectManager::getSingleton()->setTarget(index, useActionParam);
                BattleEffectManager::getSingleton()->setWaitTime(index, hitframe + wait);
            }
            else {
                return 0;
            }
            break;
        }
        return wait + BattleEffectManager::getSingleton()->getHitFrame(index);
    }
    return 0;
}

THUMB bool btl::BattleActorEffect::checkPlayerExecEffect(status::UseActionParam& useActionParam)
{
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    if (useActionParam.getTargetCharacterStatus(0) == NULL) {
        return false;
    }
    if (useActionParam.getActionIndex() == 0) {
        return false;
    }
    if (actor->getHaveStatusInfo().isCurse1()) {
        return false;
    }
    if (actor->getHaveStatusInfo().isCurse2()) {
        return false;
    }
    if ((status::UseAction::getActionType(useActionParam.getActionIndex()) == 1 || useActionParam.getActionIndex() == 0x19D) && actor->getHaveStatusInfo().isMagicDisable()) {
        return false;
    }
    return true;
}

THUMB int btl::BattleActorEffect::setEnemyEffect(status::UseActionParam& useActionParam)
{
    int actionIndex = useActionParam.getActionIndex();
    int drawCtrlId = useActionParam.getActorCharacterStatus()->getHaveStatusInfo().getDrawCtrlId();
    int animation = useActionParam.getActorCharacterStatus()->getHaveBattleStatus().getActionAnimation();
    if (!checkEnemyExecEffect(useActionParam)) {
        return 0;
    }
    if (status::isNormalAttackForSE(actionIndex)) {
        actionIndex = 0x47;
        animation = 0;
    }
    if ((actionIndex == 0x9F || actionIndex == 0xA0) && !useActionParam.getActorCharacterStatus()->isTsukonSound()) {
        actionIndex = 0x47;
        animation = 0;
    }
    int animIndex;
    if (useActionParam.getActorCharacterStatus()->getHaveStatusInfo().isMosyasExec()) {
        int mosyasId = ((status::MonsterStatus*)useActionParam.getActorCharacterStatus())->getMosyasMonsterIndex();
        switch (actionIndex) {
        case 0x33:
        case 0x36:
        case 0x39:
            actionIndex -= 1;
            break;
        case 0x34:
        case 0x37:
        case 0x3A:
            actionIndex -= 2;
            break;
        }
        animIndex = getMonsterAnimIndex(mosyasId, actionIndex);
    }
    else {
        int monsterIndex = BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).getMonsterIndex();
        animIndex = getMonsterAnimIndex(monsterIndex, actionIndex, animation);
    }
    if (animIndex >= 0) {
        dq5::level::MonsterAnim* anim = dq5::level::MonsterAnim::getRecord(animIndex);
        int effectID = anim->getEffect();
        if (effectID == 0) {
            return anim->getStartframe() + anim->getHitframe();
        }
        int effect = BattleEffectManager::getSingleton()->getEffectParam(effectID);
        dq5::level::EffectParam::getRecord(effect)->setFrame(anim->getHitframe());
        dq5::level::EffectParam::getRecord(effect)->setDisplay(anim->getDisplay());
        dq5::level::EffectParam::getRecord(effect)->setScale(anim->getScale());
        int index = BattleEffectManager::getSingleton()->setupEffect(effectID);
        if (index < 0) {
            return anim->getStartframe();
        }
        BattleEffectManager::getSingleton()->setTarget(index, useActionParam.getActorCharacterStatus(), anim->getAnimfile());
        BattleEffectManager::getSingleton()->setWaitTime(index, anim->getStartframe());
        return anim->getStartframe() + anim->getHitframe();
    }
    return 0;
}

THUMB bool btl::BattleActorEffect::checkEnemyExecEffect(status::UseActionParam& useActionParam)
{
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    if (actor->getHaveStatusInfo().getActionDisable()) {
        return false;
    }
    if (actor->getHaveStatusInfo().isCurse1()) {
        return false;
    }
    if (useActionParam.getTargetCharacterStatus(0) == NULL) {
        return false;
    }
    if (useActionParam.getActionIndex() == 0) {
        return false;
    }
    return true;
}

THUMB int btl::BattleActorEffect::setResultEnemyEffect(status::UseActionParam& useActionParam)
{
    if (!checkEnemyResultEffect(useActionParam)) {
        return 0;
    }
    int effectID = dq5::level::ActionParam::getRecord(useActionParam.getActionIndex())->getEffectEnemy();
    if (effectID) {
        if (effectID == 0x73) {
            return 0;
        }
        int effect = BattleEffectManager::getSingleton()->getEffectParam(effectID);
        int index = BattleEffectManager::getSingleton()->setupEffect(effectID);
        if (index < 0) {
            return 0;
        }
        BattleEffectManager::getSingleton()->setTarget(index, useActionParam);
        BattleEffectManager::getSingleton()->setWaitTime(index, wait_);
        return BattleEffectManager::getSingleton()->getHitFrame(index);
    }
    return 0;
}

THUMB bool btl::BattleActorEffect::checkEnemyResultEffect(status::UseActionParam& useActionParam)
{
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    if (useActionParam.getTargetCharacterStatus(0) == NULL) {
        return false;
    }
    if (useActionParam.getActionIndex() == 0) {
        return false;
    }
    if ((status::UseAction::getActionType(useActionParam.getActionIndex()) == 1 || useActionParam.getActionIndex() == 0x19D) && actor->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_FIZZLEZONE)) {
        return false;
    }
    if ((useActionParam.getActionIndex() == 0x3F || useActionParam.getActionIndex() == 0x18) && actor->getHaveStatusInfo().isMagicDisable()) {
        return false;
    }
    return true;
}

THUMB void btl::BattleActorEffect::setResultEffect(status::UseActionParam& useActionParam)
{
    if (useActionParam.getActorCharacterStatus()->getCharacterType() == PLAYER) {
        switch (useActionParam.getActionIndex()) {
        case 0x3F:
        case 0x1D4:
            useActionParam.getTargetCharacterStatus(useActionParam.getCurrentTargetIndex())->getHaveStatusInfo().setMegazaruRebirth(false);
            break;
        case 0x1D6:
            if (checkEnemyExecEffect(useActionParam) && checkEnemyResultEffect(useActionParam)) {
                setMegazaruEffect(useActionParam);
            }
            break;
        }
    }
    else {
        switch (useActionParam.getActionIndex()) {
        case 0x3F:
        case 0x1D4:
        case 0x1D6:
            if (checkEnemyExecEffect(useActionParam) && checkEnemyResultEffect(useActionParam)) {
                setMegazaruEffect(useActionParam);
            }
            break;
        case 0x3D:
        case 0x3E:
        case 0xE2:
        case 0x100:
            if (useActionParam.isTargetResult(0)) {
                wait_ = 0;
                setResultEnemyEffect(useActionParam);
            }
            break;
        }
    }
}

THUMB int btl::BattleActorEffect::setMegazaruEffect(status::UseActionParam& useActionParam)
{
    int hitframe;
    int target = useActionParam.getCurrentTargetIndex();
    int index;
    int pos;
    if (target < 0) {
        return 0;
    }
    if (!useActionParam.getTargetCharacterStatus(target)->getHaveStatusInfo().isMegazaruRebirth()) {
        if (useActionParam.getActionIndex() == 0x1D6) {
            return 0;
        }
        index = BattleEffectManager::getSingleton()->setupEffect(0x6E);
        pos = 2;
    }
    else {
        if (useActionParam.getActionIndex() == 0x1D6 && useActionParam.getTargetCharacterStatus(target)->getCharacterType() == PLAYER) {
            useActionParam.getTargetCharacterStatus(target)->getHaveStatusInfo().setMegazaruRebirth(false);
            return 0;
        }
        if (useActionParam.getTargetCharacterStatus(target)->getHaveStatusInfo().isRebirthFailed()) {
            return 0;
        }
        index = BattleEffectManager::getSingleton()->setupEffect(0x71);
        pos = 3;
    }
    if (useActionParam.getTargetCharacterStatus(target)->getHaveStatusInfo().getDrawCtrlId() < 0) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    BattleEffectManager::getSingleton()->setTarget(index, useActionParam.getTargetCharacterStatus(target), pos);
    BattleEffectManager::getSingleton()->setWaitTime(index, 0);
    hitframe = BattleEffectManager::getSingleton()->getHitFrame(index);
    useActionParam.getTargetCharacterStatus(target)->getHaveStatusInfo().setMegazaruRebirth(false);
    return 0;
}
