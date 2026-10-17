#include "main/status/ActionCheckTarget.hpp"
#include "main/status/ActionMessage.hpp"
#include "main/status/ActionEffectValue.hpp"
#include "main/status/BaseActionStatus.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/HaveAction.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "main/menu/StadiumData.hpp"
#include "main/dss/UnkRandom.hpp"
#include "ov000/btl/BattleSelectTarget.hpp"

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline status::StatusChange& status::HaveStatusInfo::getStatusChange()
{
    return statusChange_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline status::HaveEquipment& status::HaveStatusInfo::getHaveEquipment()
{
    return haveEquipment_;
}

inline bool StadiumData::isStadiumBattle()
{
    return stadiumFlag_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline int status::PlayerStatus::getPlayerIndex() { return getHaveStatusInfo().getHaveStatus().getPlayerIndex(); }
inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index) { return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline char dq5::level::ActionParam::getMohokite() { return (byte_2 & 0x8) >> 3; }
inline char dq5::level::ActionParam::getSeisi() { return (byte_4 & 0x2) >> 1; }
inline void status::HaveStatusInfo::setAddDamage(int dm) { addDamage_ = dm; }
inline int status::UseActionMessage::getAddMessage(int index) { return addMessage_[index]; }
inline void status::UseActionMessage::setAddMessage(int index, int message) { addMessage_[index] = message; }
inline void status::UseActionMessage::setSpclMessage(int index, int message) { spclMessage_[index] = message; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline void status::UseActionParam::setTargetCharacterStatus(int index, CharacterStatus* info) { targetCharacterStatus_[index] = info; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
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
inline void status::UseActionParam::setEffectValue(int value) { effectValue_ = value; }
inline int status::UseActionParam::getEffectValue() { return effectValue_; }
inline int status::UseActionParam::getPlayerEffectValue() { return playerEffectValue_; }
inline int status::UseActionParam::getMonsterEffectValue() { return monsterEffectValue_; }
inline void status::UseActionParam::setResult(bool flag) { result_ = flag; }
inline bool status::UseActionParam::isResult() { return result_; }
inline void status::UseActionFlag::setMultiAttack(bool flag) { multiFlag_ = flag; }
inline void status::ActionEffectValue::clearEffectValue() { specialTargetEffectValue_ = 0; }

THUMB void status::ActionCheckTarget::setTargetReSelect(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (g_StadiumData.isStadiumBattle()) {
        return;
    }
    CharacterStatus* tmp = checkTargetSpecialSelect(useActionParam);
    if (tmp) {
        tmp->getHaveStatusInfo().clearHpInBattle();
        tmp->getHaveStatusInfo().clearMpInBattle();
        tmp->getHaveStatusInfo().clearStatusChangeInBattle();
    }
    if (isDoubleAction(useActionParam->getActorCharacterStatus(), actionIndex) && useActionParam->getTargetCount() != 2) {
        actor->getHaveStatusInfo().setMultiAttack(true);
        UseActionFlag::setMultiAttack(true);
        useActionParam->setTargetCharacterStatus(1, useActionParam->getTargetCharacterStatus(0));
        useActionParam->setTargetCount(2);
    }
}

THUMB status::CharacterStatus* status::ActionCheckTarget::checkTargetSpecialSelect(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (actor == NULL) {
        return NULL;
    }
    if (target == NULL) {
        return NULL;
    }
    if (isMultiTargetEquipment(actor)) {
        return NULL;
    }
    if (actor->getHaveStatusInfo().isMultiAttack()) {
        ActionEffectValue::clearEffectValue();
        return NULL;
    }
    if (UseAction::isCrossFire(actionIndex) && actor->getCharacterType() == MONSTER) {
        bool ret = btl::BattleSelectTarget::setTargetCrossFire(useActionParam);
        if (ret) {
            return useActionParam->getTargetCharacterStatus(0);
        }
    }
    if (UseAction::isSpecialSelectTarget(actionIndex)) {
        ActionEffectValue::setEffectValue(useActionParam, true);
        if (target->getCharacterType() == PLAYER) {
            btl::BattleSelectTarget::setTargetSpecial(useActionParam);
            int effectValue = useActionParam->getEffectValue();
            useActionParam->setEffectValue(effectValue);
            useActionParam->setPlayerEffectValue(effectValue);
            useActionParam->setMonsterEffectValue(0);
        }
        if (target->getCharacterType() == MONSTER) {
            btl::BattleSelectTarget::setTargetSpecial(useActionParam);
            int effectValue = useActionParam->getEffectValue();
            useActionParam->setEffectValue(effectValue);
            useActionParam->setPlayerEffectValue(0);
            useActionParam->setMonsterEffectValue(effectValue);
        }
        return useActionParam->getTargetCharacterStatus(0);
    }
    return NULL;
}

THUMB bool status::ActionCheckTarget::changeMahokantaTarget(UseActionParam* useActionParam)
{
    if (useActionParam->getActionIndex() == 0x1b9) {
        return true;
    }
    if (useActionParam->getActionIndex() == 0x1ec) {
        return true;
    }
    if (useActionParam->getActionIndex() == 0x1eb) {
        return true;
    }
    int index = useActionParam->getCurrentTargetIndex();
    if (useActionParam->getTargetCharacterStatus(index) == NULL) {
        return true;
    }
    if (useActionParam->getActorCharacterStatus()->getHaveStatusInfo().isDeath()) {
        return false;
    }
    if (checkTargetMahokanta(useActionParam)) {
        useActionParam->setTargetCharacterStatus(index, useActionParam->getActorCharacterStatus());
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setMahokantaCounter(true);
    }
    return true;
}

THUMB bool status::ActionCheckTarget::isActionEnable(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (actionIndex == 0x3f && actor == target) {
        useActionParam->setAddActionIndex(0x1e0);
        return false;
    }
    if (isCarriageInside(useActionParam)) {
        return false;
    }
    if (!checkZaoraruZaoriku(useActionParam)) {
        return false;
    }
    if (!checkDeadOrAlive(useActionParam)) {
        return false;
    }
    checkMpZero(useActionParam);
    checkBaikiruto(useActionParam);
    if (!checkAstoron(useActionParam)) {
        return false;
    }
    checkFubaha(useActionParam);
    checkDefence(useActionParam);
    if (!checkJouk(useActionParam)) {
        return false;
    }
    if (!checkSplitJouk(useActionParam)) {
        return false;
    }
    if (checkPoison(useActionParam) != false) {
        return true;
    }
    return false;
}

THUMB bool status::ActionCheckTarget::checkZaoraruZaoriku(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (HaveAction::isTownMode()) {
        if ((actionIndex == 0x7f || actionIndex == 0x80) && !target->getHaveStatusInfo().isDeath()) {
            UseActionFlag::setFailedNoUseMp(true);
        }
    } else {
        if ((actionIndex == 0x3d || actionIndex == 0x3e) && !target->getHaveStatusInfo().isDeath()) {
            ActionMessage::setResultMessage(useActionParam->getUseActionMessage(0), 0xc3af9, 0);
            return false;
        }
    }
    return true;
}

THUMB bool status::ActionCheckTarget::checkDeadOrAlive(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target == NULL) {
        return true;
    }
    if (dq5::level::ActionParam::getRecord(actionIndex)->getSeisi() == 1 && target->getHaveStatusInfo().isDeath()) {
        return false;
    }
    return true;
}

THUMB void status::ActionCheckTarget::checkBaikiruto(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target != NULL && actionIndex == 0x2c) {
        StatusChange& statusChange = target->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_BAIKIRUTO)) {
            ActionMessage::setExecMessage(actionIndex, useActionParam->getUseActionMessage(0));
            int mess = statusChange.getAgainDisableMessage(dq5::level::ActionParam::ACTIONTYPE_BAIKIRUTO);
            ActionMessage::setResultMessage(useActionParam->getUseActionMessage(0), mess, 0);
        }
    }
}

THUMB bool status::ActionCheckTarget::checkAstoron(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target == NULL) {
        return true;
    }
    if (UseAction::isAstoron(actionIndex)) {
        StatusChange& statusChange = target->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_ASTORON)) {
            int index = useActionParam->getCurrentTargetIndex();
            ActionMessage::setExecMessage(actionIndex, useActionParam->getUseActionMessage(index));
            int mess = statusChange.getResultMessage(dq5::level::ActionParam::ACTIONTYPE_ASTORON, useActionParam->getActorCharacterStatus()->getCharacterType());
            ActionMessage::setResultMessage(useActionParam->getUseActionMessage(index), mess, 0);
            return false;
        }
    }
    return true;
}

THUMB void status::ActionCheckTarget::checkFubaha(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target != NULL && UseAction::isFubaha(actionIndex)) {
        target->getHaveStatusInfo().setFubahaFlag(true);
        StatusChange& statusChange = target->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_FUBAHA)) {
            useActionParam->setPlayerEffectValue(useActionParam->getPlayerEffectValue() / 2);
            useActionParam->setMonsterEffectValue(useActionParam->getMonsterEffectValue() / 2);
        }
    }
}

THUMB void status::ActionCheckTarget::checkDefence(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target == NULL || actionIndex == 0x1de) {
        return;
    }
    if (UseAction::getDamageType(actionIndex) == UseAction::DamageTypeDamage) {
        StatusChange& statusChange = target->getHaveStatusInfo().getStatusChange();
        if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x5a)) {
            if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
                statusChange.setup(dq5::level::ActionParam::ACTIONTYPE_DEFENCE, false);
            }
            if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
                statusChange.setup(dq5::level::ActionParam::ACTIONTYPE_DEFENCE, false);
            }
            if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_DEFENCE)) {
                if (useActionParam->getPlayerEffectValue() != 1) {
                    useActionParam->setPlayerEffectValue(useActionParam->getPlayerEffectValue() / 2);
                }
                if (useActionParam->getMonsterEffectValue() != 1) {
                    useActionParam->setMonsterEffectValue(useActionParam->getMonsterEffectValue() / 2);
                }
            }
        } else if (!statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI) && !statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_PATH_1)
                   && !statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI) && !statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN)
                   && statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_DEFENCE)) {
            if (statusChange.getActionIndex(dq5::level::ActionParam::ACTIONTYPE_DEFENCE) == 0x49) {
                if (useActionParam->getPlayerEffectValue() != 1) {
                    useActionParam->setPlayerEffectValue(useActionParam->getPlayerEffectValue() / 2);
                }
                if (useActionParam->getMonsterEffectValue() != 1) {
                    useActionParam->setMonsterEffectValue(useActionParam->getMonsterEffectValue() / 2);
                }
            } else if (statusChange.getActionIndex(dq5::level::ActionParam::ACTIONTYPE_DEFENCE) == 0x4a) {
                useActionParam->setPlayerEffectValue(useActionParam->getPlayerEffectValue() / 4);
                useActionParam->setMonsterEffectValue(useActionParam->getMonsterEffectValue() / 4);
            }
        }
    }
}

THUMB bool status::ActionCheckTarget::checkJouk(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (actor == NULL) {
        return true;
    }
    if (target == NULL) {
        return true;
    }
    if (actor->getHaveStatusInfo().isKaishin()) {
        return true;
    }
    if (useActionParam->getActorCharacterStatus()->getHaveStatusInfo().isTsukon1()) {
        return true;
    }
    if (useActionParam->getActorCharacterStatus()->getHaveStatusInfo().isTsukon2()) {
        return true;
    }
    if (UseAction::isJouk(actionIndex)) {
        StatusChange& statusChange = target->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
            return true;
        }
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
            return true;
        }
        if (target->getHaveBattleStatus().isJouk()) {
            int index = useActionParam->getCurrentTargetIndex();
            ActionMessage::setExecMessage(actionIndex, useActionParam->getUseActionMessage(index));
            ActionMessage::setResultMessage(useActionParam->getUseActionMessage(index), 0xc392c, 0);
            useActionParam->setResult(false);
            target->getHaveStatusInfo().setTargetJouk(true);
            target->getHaveStatusInfo().setTargetJoukForTest(true);
            target->getHaveStatusInfo().setUseActionEffectValue(0);
            return false;
        }
        if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x57) && UnkDssRand::rand(6) == 0) {
            int index = useActionParam->getCurrentTargetIndex();
            ActionMessage::setExecMessage(actionIndex, useActionParam->getUseActionMessage(index));
            ActionMessage::setResultMessage(useActionParam->getUseActionMessage(index), 0xc392c, 0);
            useActionParam->setResult(false);
            target->getHaveStatusInfo().setTargetJouk(true);
            target->getHaveStatusInfo().setTargetJoukForTest(true);
            target->getHaveStatusInfo().setUseActionEffectValue(0);
            return false;
        }
    }
    return true;
}

THUMB bool status::ActionCheckTarget::checkSplitJouk(UseActionParam* useActionParam)
{
    return true;
}

THUMB bool status::ActionCheckTarget::checkPoison(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target == NULL) {
        return true;
    }
    if (actionIndex == 0x5b) {
        StatusChange& statusChange = target->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU)) {
            int mess = statusChange.getAgainEnableMessage(dq5::level::ActionParam::ACTIONTYPE_DOKU);
            int index = useActionParam->getCurrentTargetIndex();
            ActionMessage::setResultMessage(useActionParam->getUseActionMessage(index), mess, 0);
            useActionParam->setResult(false);
            return false;
        }
    }
    if (actionIndex == 0x5c) {
        StatusChange& statusChange = target->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
            int mess = statusChange.getAgainEnableMessage(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU);
            int index = useActionParam->getCurrentTargetIndex();
            ActionMessage::setResultMessage(useActionParam->getUseActionMessage(index), mess, 0);
            useActionParam->setResult(false);
            return false;
        }
    }
    return true;
}

THUMB void status::ActionCheckTarget::checkMpZero(UseActionParam* useActionParam)
{
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target != NULL) {
        if (target->getHaveStatusInfo().getMp() == 0) {
            BaseActionStatus::setMpZero(true);
        } else {
            BaseActionStatus::setMpZero(false);
        }
    }
}

THUMB bool status::ActionCheckTarget::checkUseMp(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    if (actionIndex == 0x7a || actionIndex == 0x7b || actionIndex == 0x7c) {
        if (useActionParam->isResult()) {
            return true;
        }
        return false;
    }
    if (actionIndex == 0x7d) {
        if (useActionParam->isResult()) {
            return true;
        }
        return false;
    }
    if (actionIndex == 0x81) {
        if (isExecRula() != false) {
            return true;
        }
        return false;
    }
    if (actionIndex == 0x82) {
        if (isExecRiremito() != false) {
            return true;
        }
        return false;
    }
    if (actionIndex == 0x84) {
        if (isExecImpas() != false) {
            return true;
        }
        return false;
    }
    if (actionIndex == 0x86) {
        if (isExecLanaruta() != false) {
            return true;
        }
        return false;
    }
    if (actionIndex == 0x88) {
        if (isExecFloomi() != false) {
            return true;
        }
        return false;
    }
    if (actionIndex == 0x83) {
        if (isExecToherosu() != false) {
            return true;
        }
        return false;
    }
    if (actionIndex == 0x7e) {
        if (useActionParam->isResult()) {
            return true;
        }
        return false;
    }
    if (actionIndex == 0x87) {
        if (useActionParam->isResult()) {
            return true;
        }
        return false;
    }
    if (actionIndex == 0x7f) {
        return !UseActionFlag::isZaoraruInvalid();
    }
    if (actionIndex == 0x80) {
        if (useActionParam->isResult()) {
            return true;
        }
        return false;
    }
    return true;
}

THUMB void status::ActionCheckTarget::checkTarget(UseActionParam* useActionParam)
{
}

THUMB void status::ActionCheckTarget::checkActionEnd(UseActionParam* useActionParam)
{
    checkReleaseConfusionSleep(useActionParam);
    checkReleaseItetsukuhadou(useActionParam);
    checkMahokite(useActionParam);
}

THUMB void status::ActionCheckTarget::checkReleaseConfusionSleep(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (actor == NULL || target == NULL || actor->getHaveStatusInfo().isMiss() || target->getHaveStatusInfo().isSleepTurn() || useActionParam->getEffectValue() == 0) {
        return;
    }
    if (UseAction::isReleaseConfusion(actionIndex) && !target->getHaveStatusInfo().isDeath()) {
        StatusChange& statusChange = target->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN)) {
            bool success = false;
            if (target->getCharacterType() == PLAYER) {
                success = UnkDssRand::rand(2) == 0 ? true : false;
            }
            if (target->getCharacterType() == MONSTER) {
                success = UnkDssRand::rand(4) == 0 ? true : false;
            }
            if (success) {
                statusChange.release(dq5::level::ActionParam::ACTIONTYPE_KONRAN);
                target->getHaveStatusInfo().setStatusChangeInBattle(HaveStatusInfo::ResultAction);
                target->getHaveStatusInfo().setStatusChangeRelease(true);
                int index = useActionParam->getCurrentTargetIndex();
                ActionMessage::setAddMessage(useActionParam->getUseActionMessage(index), 0xc3c70, 0);
            }
        }
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
            bool success = false;
            if (target->getCharacterType() == PLAYER) {
                success = UnkDssRand::rand(2) == 0 ? true : false;
            }
            if (target->getCharacterType() == MONSTER) {
                success = UnkDssRand::rand(4) == 0 ? true : false;
            }
            if (success) {
                statusChange.release(dq5::level::ActionParam::ACTIONTYPE_NEMURI);
                target->getHaveStatusInfo().setStatusChangeInBattle(HaveStatusInfo::ResultAction);
                target->getHaveStatusInfo().setStatusChangeRelease(true);
                int index = useActionParam->getCurrentTargetIndex();
                int mess = useActionParam->getUseActionMessage(index).getAddMessage(0);
                if (mess) {
                    useActionParam->getUseActionMessage(index).setAddMessage(1, 0xc3c6a);
                } else {
                    ActionMessage::setAddMessage(useActionParam->getUseActionMessage(index), 0xc3c6a, 0);
                }
            }
        }
    }
}

THUMB void status::ActionCheckTarget::checkReleaseItetsukuhadou(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target != NULL && (actionIndex == 0x69 || actionIndex == 0xea)) {
        int index = useActionParam->getCurrentTargetIndex();
        ActionMessage::setExecMessage(useActionParam->getUseActionMessage(index), 0, 0xaae66, 0, 0);
    }
}

THUMB void status::ActionCheckTarget::checkMahokite(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (actor == NULL || target == NULL || actionIndex == 0x24 || HaveAction::isTownMode()) {
        return;
    }
    if (dq5::level::ActionParam::getRecord(actionIndex)->getMohokite() && !target->getHaveStatusInfo().isDeath()
        && target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOKITE)
        && useActionParam->getPlayerEffectValue() && actor != target) {
        int mp = UseAction::getUseMp(actionIndex);
        if (mp) {
            target->getHaveStatusInfo().addMpInBattle(HaveStatusInfo::ResultAction, mp);
            target->getHaveStatusInfo().setAddMahotoraExecute(true);
            target->getHaveStatusInfo().setAddDamage(mp);
            int index = useActionParam->getCurrentTargetIndex();
            ActionMessage::setAddMessage(useActionParam->getUseActionMessage(index), 0, 0xc3b5f);
        }
    }
}

THUMB bool status::ActionCheckTarget::checkTargetMahokanta(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (actor == NULL) {
        return false;
    }
    if (target == NULL) {
        return false;
    }
    if (actor == target) {
        return false;
    }
    if (actor->getHaveStatusInfo().isDeath()) {
        return false;
    }
    if (target->getCharacterType() == PLAYER && PartyStatus::isInsideCarriageForPlayerIndex(((PlayerStatus*)target)->getPlayerIndex())) {
        return false;
    }
    if (UseAction::isMahokanta(actionIndex)) {
        StatusChange& statusChange = target->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA)) {
            int index = useActionParam->getCurrentTargetIndex();
            int mess = statusChange.getResultMessage(dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA, target->getCharacterType());
            useActionParam->getUseActionMessage(index).setSpclMessage(0, mess);
            return true;
        }
        if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x63) && UnkDssRand::rand(3) == 0) {
            int index = useActionParam->getCurrentTargetIndex();
            int mess = statusChange.getResultMessage2(dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA, target->getCharacterType());
            mess = 0xc3938;
            useActionParam->getUseActionMessage(index).setSpclMessage(0, mess);
            return true;
        }
        if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x6f) && UnkDssRand::rand(3) == 0) {
            int index = useActionParam->getCurrentTargetIndex();
            int mess = statusChange.getResultMessage2(dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA, target->getCharacterType());
            mess = 0xc3938;
            useActionParam->getUseActionMessage(index).setSpclMessage(0, mess);
            return true;
        }
    }
    return false;
}

THUMB bool status::ActionCheckTarget::isCarriageInside(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (actor == NULL) {
        return false;
    }
    if (target == NULL) {
        return false;
    }
    if (HaveAction::isTownMode()) {
        return false;
    }
    if (UseAction::getUseArea(actionIndex) != 6) {
        return false;
    }
    if (target->getCharacterType() == PLAYER && PartyStatus::isInsideCarriageForPlayerIndex(((PlayerStatus*)actor)->getPlayerIndex())) {
        return true;
    }
    return false;
}
