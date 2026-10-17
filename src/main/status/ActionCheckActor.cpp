#include "main/status/ActionCheckActor.hpp"
#include "main/status/ActionMessage.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/HaveAction.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/dss/UnkRandom.hpp"

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

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline CharacterType status::StatusChange::getCharacterTypeForTimeStop() { return characterTypeForTimeStop_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline void status::CharacterStatus::setKaishinSound() { damageSound_ = KaishinSe; }
inline void status::CharacterStatus::setTsukonSound() { damageSound_ = TsukonSe; }
inline int status::PlayerStatus::getPlayerIndex() { return getHaveStatusInfo().getHaveStatus().getPlayerIndex(); }
inline int status::HaveStatusInfo::getUseActionEffectValue() { return effectValue_; }
inline bool status::HaveBattleStatus::isZombi() { return zombi_; }
inline bool status::HaveBattleStatus::isDragon() { return dragon_; }
inline void status::UseActionMessage::setBeforeMessage(int index, int message) { beforeMessage_[index] = message; }
inline void status::UseActionMessage::setExecMessage(int index, int message) { execMessage_[index] = message; }
inline void status::UseActionMessage::setSpclMessage(int index, int message) { spclMessage_[index] = message; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline void status::UseActionParam::setAddActionIndex(int actionIndex)
{
    preActionIndex_ = actionIndex_;
    addActionIndex_ = actionIndex;
}
inline int status::UseActionParam::getCurrentTargetIndex() { return currentTargetIndex_; }
inline status::UseActionMessage& status::UseActionParam::getUseActionMessage(int index) { return message_[index]; }
inline void status::UseActionParam::setEffectValue(int value) { effectValue_ = value; }
inline int status::UseActionParam::getEffectValue() { return effectValue_; }
inline int status::UseActionParam::getPlayerEffectValue() { return playerEffectValue_; }
inline int status::UseActionParam::getMonsterEffectValue() { return monsterEffectValue_; }
inline void status::UseActionParam::setResult(bool flag) { result_ = flag; }
inline bool status::UseActionFlag::isEventBattle() { return eventBattle_; }

THUMB bool status::ActionCheckActor::checkStatusRelease(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (actor == NULL) {
        return false;
    }
    if (useActionParam->getActionIndex() == 0x1de) {
        return false;
    }
    StatusChange& statusChange = actor->getHaveStatusInfo().getStatusChange();
    statusChange.execStartOfTurn();
    dq5::level::ActionParam::ACTIONTYPE release = statusChange.isRelease();
    if (release != dq5::level::ActionParam::ACTIONTYPE_NONE && release == dq5::level::ActionParam::ACTIONTYPE_NEMURI) {
        return true;
    }
    return false;
}

THUMB void status::ActionCheckActor::checkConfusion(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (actor == NULL) {
        return;
    }
    if (useActionParam->getActionIndex() == 0x1de) {
        return;
    }
    StatusChange& statusChange = actor->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN) || statusChange.isRelease(dq5::level::ActionParam::ACTIONTYPE_KONRAN)) {
        useActionParam->getUseActionMessage(0).setBeforeMessage(0, 0xc3b96);
    }
}

THUMB void status::ActionCheckActor::checkActorKaishin(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (actor == NULL || isMultiTargetEquipment(actor) || actor->getHaveStatusInfo().isConfuseMissAttack() || actor->getHaveStatusInfo().isImmediateDeathItem()
        || actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x33)) {
        return;
    }
    if (actor->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_BAIKIRUTO) && !actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x2c)) {
        return;
    }
    if (UseAction::isKaishin(actionIndex)) {
        if (actor->getCharacterType() == PLAYER) {
            if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x2c)) {
                if (UnkDssRand::rand(2) == 0) {
                    actor->getHaveStatusInfo().setKaishin(true);
                } else {
                    actor->getHaveStatusInfo().setMiss(true);
                }
            } else if (UnkDssRand::rand(32) == 0) {
                actor->getHaveStatusInfo().setKaishin(true);
            }
        }
        if (actor->getHaveStatusInfo().isAllKaishin()) {
            actor->getHaveStatusInfo().setKaishin(true);
        }
        if (actionIndex == 0x9f && UnkDssRand::rand(4) == 0) {
            actor->getHaveStatusInfo().setTsukon1(true);
        }
        if (actionIndex == 0xa0) {
            actor->getHaveStatusInfo().setTsukon2(true);
        }
    }
    if (actionIndex == 0xc9 && UnkDssRand::rand(4) == 0) {
        actor->getHaveStatusInfo().setTsukon1(true);
    }
    if (actor->getHaveStatusInfo().isMiss()) {
        actor->getHaveStatusInfo().setKaishin(false);
    }
    if (actor->getHaveStatusInfo().isKaishin()) {
        if (actor->getCharacterType() == PLAYER) {
            int index = useActionParam->getCurrentTargetIndex();
            useActionParam->getUseActionMessage(index).setSpclMessage(0, 0xc3916);
            useActionParam->getActorCharacterStatus()->setKaishinSound();
        } else {
            useActionParam->getUseActionMessage(0).setSpclMessage(0, 0xc3919);
            useActionParam->getActorCharacterStatus()->setTsukonSound();
        }
    }
    if (actor->getHaveStatusInfo().isTsukon1() || actor->getHaveStatusInfo().isTsukon2()) {
        if (actor->getCharacterType() == PLAYER) {
            useActionParam->getUseActionMessage(0).setSpclMessage(0, 0xc3916);
            useActionParam->getActorCharacterStatus()->setTsukonSound();
        } else {
            useActionParam->getUseActionMessage(0).setSpclMessage(1, 0xc3919);
            useActionParam->getActorCharacterStatus()->setTsukonSound();
        }
    }
}

THUMB void status::ActionCheckActor::checkActorImmediateItem(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    actor->getHaveStatusInfo().setImmediateDeathItem(false);
    if (target != NULL && !UseActionFlag::isEventBattle() && UseAction::isForceE(actionIndex)) {
        HaveEquipment& haveEquipment = actor->getHaveStatusInfo().getHaveEquipment();
        if (haveEquipment.isEquipment(0x33) && UnkDssRand::rand(6) == 0) {
            actor->getHaveStatusInfo().setImmediateDeathItem(true);
        }
        if (haveEquipment.isEquipment(0x40) && UnkDssRand::rand(6) == 0) {
            actor->getHaveStatusInfo().setImmediateDeathItem(true);
        }
    }
}

THUMB bool status::ActionCheckActor::isActionEnable(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (actor == NULL) {
        return true;
    }
    if (isCarriageInside(useActionParam)) {
        return false;
    }
    if (actor->getHaveStatusInfo().isRebirthForRebirthStone()) {
        actor->getHaveStatusInfo().setRebirthForRebirthStone(false);
    }
    if (useActionParam->getActionIndex() == 0x1de) {
        return true;
    }
    if (isAstoron(useActionParam)) {
        return false;
    }
    if (isSpazz(useActionParam)) {
        return false;
    }
    if (isSleep(useActionParam)) {
        return false;
    }
    if (isPath1(useActionParam)) {
        return false;
    }
    if (isTimeStop(useActionParam)) {
        return false;
    }
    if (isCloseDoor(useActionParam)) {
        return false;
    }
    if (HaveAction::isBattleMode()) {
        actor->getHaveBattleStatus().setLoopCount(false);
    }
    if (!isUseMp(useActionParam)) {
        return false;
    }
    if (isMahoton(useActionParam)) {
        return false;
    }
    if (isFizzleZone(useActionParam)) {
        return false;
    }
    if (isCurse(useActionParam)) {
        return false;
    }
    if (isMinadein(useActionParam) != false) {
        return true;
    }
    return false;
}

THUMB bool status::ActionCheckActor::isAstoron(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (actor == NULL) {
        return false;
    }
    StatusChange& statusChange = actor->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_ASTORON)) {
        useActionParam->setResult(false);
        int mess = statusChange.getExecMessage(dq5::level::ActionParam::ACTIONTYPE_ASTORON);
        ActionMessage::setExecMessage(useActionParam->getUseActionMessage(0), mess, 0, 0, 0);
        ActionMessage::setResultMessage(useActionParam->getUseActionMessage(0), 0, 0);
        actor->getHaveStatusInfo().setActionDisable(true);
        return true;
    }
    return false;
}

THUMB bool status::ActionCheckActor::isSpazz(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    StatusChange& statusChange = actor->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
        useActionParam->setResult(false);
        int mess = statusChange.getExecMessage(dq5::level::ActionParam::ACTIONTYPE_MAHI);
        ActionMessage::setExecMessage(useActionParam->getUseActionMessage(0), mess, 0, 0, 0);
        ActionMessage::setResultMessage(useActionParam->getUseActionMessage(0), 0, 0);
        actor->getHaveStatusInfo().setActionDisable(true);
        return true;
    }
    if (statusChange.isRelease(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
        useActionParam->setResult(false);
        int mess = statusChange.getReleaseMessage();
        ActionMessage::setExecMessage(useActionParam->getUseActionMessage(0), mess, 0, 0, 0);
        ActionMessage::setResultMessage(useActionParam->getUseActionMessage(0), 0, 0);
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setStatusChangeRelease(true);
        actor->getHaveStatusInfo().setActionDisable(true);
        return true;
    }
    return false;
}

THUMB bool status::ActionCheckActor::isSleep(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    StatusChange& statusChange = actor->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
        if (useActionParam->getActionIndex() == 0x6b) {
            int mess = statusChange.getExecMessage(dq5::level::ActionParam::ACTIONTYPE_NEMURI);
            useActionParam->getUseActionMessage(0).setBeforeMessage(0, mess);
            useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setSleepAttack(true);
            return false;
        }
        useActionParam->setResult(false);
        int mess = statusChange.getExecMessage(dq5::level::ActionParam::ACTIONTYPE_NEMURI);
        ActionMessage::setExecMessage(useActionParam->getUseActionMessage(0), mess, 0, 0, 0);
        ActionMessage::setResultMessage(useActionParam->getUseActionMessage(0), 0, 0);
        actor->getHaveStatusInfo().setActionDisable(true);
        return true;
    }
    if (statusChange.isRelease(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
        useActionParam->setResult(false);
        int mess = statusChange.getReleaseMessage();
        ActionMessage::setExecMessage(useActionParam->getUseActionMessage(0), mess, 0, 0, 0);
        ActionMessage::setResultMessage(useActionParam->getUseActionMessage(0), 0, 0);
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setStatusChangeRelease(true);
        return true;
    }
    return false;
}

THUMB bool status::ActionCheckActor::isPath1(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    StatusChange& statusChange = actor->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_PATH_1)) {
        useActionParam->setResult(false);
        int mess = statusChange.getExecMessage(dq5::level::ActionParam::ACTIONTYPE_PATH_1);
        ActionMessage::setExecMessage(useActionParam->getUseActionMessage(0), mess, 0, 0, 0);
        actor->getHaveStatusInfo().setActionDisable(true);
        return true;
    }
    return false;
}

THUMB bool status::ActionCheckActor::isTimeStop(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    StatusChange& statusChange = actor->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_TIMESTOP) && actor->getCharacterType() == StatusChange::getCharacterTypeForTimeStop()) {
        useActionParam->setResult(false);
        int mess = statusChange.getExecMessage(dq5::level::ActionParam::ACTIONTYPE_TIMESTOP);
        ActionMessage::setExecMessage(useActionParam->getUseActionMessage(0), mess, 0, 0, 0);
        return true;
    }
    return false;
}

THUMB bool status::ActionCheckActor::isCloseDoor(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    StatusChange& statusChange = actor->getHaveStatusInfo().getStatusChange();
    if (actor->getHaveStatusInfo().isCloseDoor()) {
        useActionParam->setResult(false);
        int mess = statusChange.getExecMessage(dq5::level::ActionParam::ACTIONTYPE_CLOSEDOOR);
        ActionMessage::setExecMessage(useActionParam->getUseActionMessage(0), mess, 0, 0, 0);
        actor->getHaveStatusInfo().setActionDisable(true);
        return true;
    }
    return false;
}

THUMB bool status::ActionCheckActor::isMahoton(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (UseAction::isMahoton(useActionParam->getActionIndex())) {
        StatusChange& statusChange = useActionParam->getActorCharacterStatus()->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOTON)) {
            useActionParam->setResult(false);
            ActionMessage::setExecMessage(useActionParam->getActionIndex(), useActionParam->getUseActionMessage(0));
            int mess = statusChange.getExecMessage2(dq5::level::ActionParam::ACTIONTYPE_MAHOTON);
            ActionMessage::setResultMessage(useActionParam->getUseActionMessage(0), mess, 0);
            useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setMahotoneFailure(true);
            useMp(useActionParam);
            actor->getHaveStatusInfo().setMagicDisable(true);
            if (useActionParam->getActionIndex() != 0) {
                ActionMessage::setExecMessage(useActionParam->getUseActionMessage(0), 0xc3931, 0, 0, 0);
            }
            return true;
        }
    }
    return false;
}

THUMB bool status::ActionCheckActor::isFizzleZone(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (UseAction::isMahoton(useActionParam->getActionIndex())) {
        StatusChange& statusChange = actor->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_FIZZLEZONE)) {
            useActionParam->setResult(false);
            ActionMessage::setExecMessage(useActionParam->getActionIndex(), useActionParam->getUseActionMessage(0));
            int mess = statusChange.getExecMessage2(dq5::level::ActionParam::ACTIONTYPE_FIZZLEZONE);
            ActionMessage::setResultMessage(useActionParam->getUseActionMessage(0), mess, 0);
            useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setMahotoneFailure(true);
            useMp(useActionParam);
            actor->getHaveStatusInfo().setMagicDisable(true);
            return true;
        }
    }
    return false;
}

THUMB bool status::ActionCheckActor::isCurse(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    StatusChange& statusChange = actor->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE1) && useActionParam->getActionIndex() != 0x1e0 && UnkDssRand::rand(4) == 0) {
        useActionParam->setResult(false);
        int mess = statusChange.getExecMessage2(dq5::level::ActionParam::ACTIONTYPE_CURSE1);
        ActionMessage::setExecMessage(useActionParam->getUseActionMessage(0), mess, 0, 0, 0);
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setCurse1(true);
        return true;
    }
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE3) && UseAction::isMahoton(useActionParam->getActionIndex()) && UnkDssRand::rand(4) == 0) {
        useActionParam->setResult(false);
        int mess = statusChange.getExecMessage2(dq5::level::ActionParam::ACTIONTYPE_CURSE3);
        ActionMessage::setExecMessage(useActionParam->getUseActionMessage(0), 0xc3931, 0, 0, 0);
        ActionMessage::setResultMessage(useActionParam->getUseActionMessage(0), mess, 0);
        useMp(useActionParam);
        actor->getHaveStatusInfo().setMagicDisable(true);
        return true;
    }
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_CURSE2) && g_Party.getCarriageOutAliveCount() != 0 && UnkDssRand::rand(2) == 0
        && useActionParam->getActionIndex() == 0x47) {
        int mess = statusChange.getExecMessage2(dq5::level::ActionParam::ACTIONTYPE_CURSE2);
        useActionParam->getUseActionMessage(0).setExecMessage(0, 0xc3913);
        useActionParam->setAddActionIndex(0x1f3);
        actor->getHaveStatusInfo().setCurse2(true);
        return true;
    }
    return false;
}

THUMB bool status::ActionCheckActor::isMinadein(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (useActionParam->getActionIndex() == 0x12 && !PartyStatusUtility::isExecMinadein()) {
        useActionParam->setResult(false);
        ActionMessage::setExecMessage(useActionParam->getUseActionMessage(0), 0xc3945, 0, 0, 0);
        actor->getHaveStatusInfo().setMagicDisable(true);
        return false;
    }
    return true;
}

THUMB bool status::ActionCheckActor::isCarriageInside(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (actor == NULL) {
        return false;
    }
    if (HaveAction::isTownMode()) {
        return false;
    }
    if (actor->getCharacterType() == PLAYER && PartyStatus::isInsideCarriageForPlayerIndex(((PlayerStatus*)actor)->getPlayerIndex())) {
        actor->getHaveStatusInfo().setActionDisable(true);
        return true;
    }
    return false;
}

THUMB bool status::ActionCheckActor::isUseMp(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (isUseMpMyself(useActionParam)) {
        return true;
    }
    useActionParam->setResult(false);
    actor->getHaveStatusInfo().setMagicDisable(true);
    if (useActionParam->getActorCharacterStatus() != NULL) {
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setMpFailure(true);
    }
    ActionMessage::setMessageNotEnoughMp(useActionParam->getActionIndex(), useActionParam->getUseActionMessage(0));
    return false;
}

THUMB bool status::ActionCheckActor::isUseMpMyself(UseActionParam* useActionParam)
{
    int useMp = UseAction::getUseMp(useActionParam->getActionIndex());
    if (useMp == 0xff && useActionParam->getActorCharacterStatus()->getHaveStatusInfo().getMp() != 0) {
        return true;
    }
    if (useActionParam->getActorCharacterStatus()->getHaveStatusInfo().getMp() >= useMp) {
        return true;
    }
    return false;
}

THUMB void status::ActionCheckActor::checkActor(UseActionParam* useActionParam)
{
    if (useActionParam->getActorCharacterStatus() != NULL) {
        checkPowerSave(useActionParam);
        checkManusa(useActionParam);
        checkBaikiruto(useActionParam);
    }
}

THUMB void status::ActionCheckActor::checkEffectValue(UseActionParam* useActionParam)
{
    if (useActionParam->getActorCharacterStatus() != NULL) {
        checkItemMissA(useActionParam);
        checkItemMuchiB(useActionParam);
        checkItemDamageC(useActionParam);
        checkItemDamageD(useActionParam);
    }
}

THUMB void status::ActionCheckActor::checkPowerSave(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    bool tukon = false;
    if (useActionParam->getActionIndex() == 0x9f && !actor->getHaveStatusInfo().isTsukon1()) {
        tukon = true;
    }
    if (useActionParam->getActionIndex() == 0xa0 && !actor->getHaveStatusInfo().isTsukon2()) {
        tukon = true;
    }
    if (UseAction::isPowerSave(useActionParam->getActionIndex()) || tukon) {
        StatusChange& statusChange = useActionParam->getActorCharacterStatus()->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_TAMEKEI)) {
            statusChange.release(dq5::level::ActionParam::ACTIONTYPE_TAMEKEI);
            if (!useActionParam->getActorCharacterStatus()->getHaveStatusInfo().isKaishin()) {
                int rate = UnkDssRand::rand(6) + 20;
                useActionParam->setEffectValue(useActionParam->getEffectValue() * rate / 10);
                useActionParam->setPlayerEffectValue(useActionParam->getPlayerEffectValue() * rate / 10);
                useActionParam->setMonsterEffectValue(useActionParam->getMonsterEffectValue() * rate / 10);
            }
        }
    }
}

THUMB void status::ActionCheckActor::checkBaikiruto(UseActionParam* useActionParam)
{
    if (UseAction::isBaikiruto(useActionParam->getActionIndex())) {
        StatusChange& statusChange = useActionParam->getActorCharacterStatus()->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_BAIKIRUTO) && !useActionParam->getActorCharacterStatus()->getHaveStatusInfo().isKaishin()
            && useActionParam->getCurrentTargetIndex() == 0) {
            useActionParam->setEffectValue(useActionParam->getEffectValue() * 18 / 10);
            useActionParam->setPlayerEffectValue(useActionParam->getPlayerEffectValue() * 18 / 10);
            useActionParam->setMonsterEffectValue(useActionParam->getMonsterEffectValue() * 18 / 10);
        }
    }
}

THUMB void status::ActionCheckActor::checkManusa(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (actor == NULL || target == NULL || actor->getHaveStatusInfo().isKaishin() || actor->getHaveStatusInfo().isTsukon1() || actor->getHaveStatusInfo().isTsukon2()) {
        return;
    }
    if (UseAction::isManusa(useActionParam->getActionIndex())) {
        StatusChange& statusChange = actor->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MANUSA)) {
            if (statusChange.getActionIndex(dq5::level::ActionParam::ACTIONTYPE_MANUSA) == 0x1f && UnkDssRand::rand(8) <= 4) {
                useActionParam->setEffectValue(0);
                useActionParam->setPlayerEffectValue(0);
                useActionParam->setMonsterEffectValue(0);
            }
            if (statusChange.getActionIndex(dq5::level::ActionParam::ACTIONTYPE_MANUSA) == 0x20 && UnkDssRand::rand(8) <= 4) {
                useActionParam->setEffectValue(0);
                useActionParam->setPlayerEffectValue(0);
                useActionParam->setMonsterEffectValue(0);
            }
            if (statusChange.getActionIndex(dq5::level::ActionParam::ACTIONTYPE_MANUSA) == 0xcd && UnkDssRand::rand(8) <= 2) {
                useActionParam->setEffectValue(0);
                useActionParam->setPlayerEffectValue(0);
                useActionParam->setMonsterEffectValue(0);
            }
            if (statusChange.getActionIndex(dq5::level::ActionParam::ACTIONTYPE_MANUSA) == 0x64 && UnkDssRand::rand(8) <= 2) {
                useActionParam->setEffectValue(0);
                useActionParam->setPlayerEffectValue(0);
                useActionParam->setMonsterEffectValue(0);
            }
        }
    }
}

THUMB void status::ActionCheckActor::checkItemMissA(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (actor == NULL) {
        return;
    }
    UseAction::isErrorA(actionIndex);
    if (actor->getHaveStatusInfo().isMiss()) {
        actor->getHaveStatusInfo().setMiss(false);
        useActionParam->setEffectValue(0);
        useActionParam->setPlayerEffectValue(0);
        useActionParam->setMonsterEffectValue(0);
    }
    if (actor->getHaveStatusInfo().isConfuseMissAttack()) {
        actor->getHaveStatusInfo().setConfuseMissAttack(false);
        useActionParam->setEffectValue(0);
        useActionParam->setPlayerEffectValue(0);
        useActionParam->setMonsterEffectValue(0);
    }
}

THUMB void status::ActionCheckActor::checkItemMuchiB(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (actor == NULL || target == NULL) {
        return;
    }
    if (UseAction::isErrorB(actionIndex) && isMultiTargetEquipment(actor)) {
        int effectValue = useActionParam->getEffectValue();
        int index = useActionParam->getCurrentTargetIndex();
        switch (index) {
        case 0:
            break;
        case 1:
            if (effectValue == 1) {
                effectValue = 1;
            } else {
                effectValue = effectValue * 80 / 100;
            }
            break;
        case 2:
            if (effectValue == 1) {
                effectValue = 1;
            } else {
                effectValue = effectValue * 70 / 100;
            }
            break;
        case 3:
            if (effectValue == 1) {
                effectValue = 1;
            } else {
                effectValue = effectValue * 50 / 100;
            }
            break;
        case 4:
            effectValue = effectValue * 30 / 100;
            if (effectValue == 0) {
                effectValue = UnkDssRand::rand(2);
            }
            break;
        default:
            effectValue = effectValue * 20 / 100;
            if (effectValue == 0) {
                effectValue = UnkDssRand::rand(2);
            }
            break;
        }
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
}

THUMB void status::ActionCheckActor::checkItemDamageC(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target == NULL || !UseAction::isDamageC(actionIndex)) {
        return;
    }
    HaveEquipment& haveEquipment = actor->getHaveStatusInfo().getHaveEquipment();
    if (haveEquipment.isEquipment(0x14) && target->getHaveBattleStatus().isZombi() && !actor->getHaveStatusInfo().isKaishin()) {
        useActionParam->setPlayerEffectValue(useActionParam->getPlayerEffectValue() * 3 / 2);
        useActionParam->setMonsterEffectValue(useActionParam->getMonsterEffectValue() * 3 / 2);
    }
    if (haveEquipment.isEquipment(0x16) && target->getHaveBattleStatus().isDragon() && !actor->getHaveStatusInfo().isKaishin()) {
        useActionParam->setPlayerEffectValue(useActionParam->getPlayerEffectValue() * 3 / 2);
        useActionParam->setMonsterEffectValue(useActionParam->getMonsterEffectValue() * 3 / 2);
    }
}

THUMB void status::ActionCheckActor::checkItemDamageD(UseActionParam* useActionParam)
{
}

THUMB void status::ActionCheckActor::checkActionEnd(UseActionParam* useActionParam)
{
    checkItemRecoveryI(useActionParam);
}

THUMB void status::ActionCheckActor::checkItemRecoveryI(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target == NULL || !UseAction::isAddHp(actionIndex)) {
        return;
    }
    HaveEquipment& haveEquipment = actor->getHaveStatusInfo().getHaveEquipment();
    if (haveEquipment.isEquipment(0x19)) {
        int effectValue = target->getHaveStatusInfo().getUseActionEffectValue() / 4;
        if (effectValue) {
            actor->getHaveStatusInfo().addHpInBattle(HaveStatusInfo::ResultAction, effectValue);
            target->getHaveStatusInfo().setAddEffectRecovery(true);
            ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3cd2, 0);
        }
    }
}

THUMB void status::ActionCheckActor::useMp(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    if (useActionParam->getActorCharacterStatus() == NULL) {
        return;
    }
    int useMp = UseAction::getUseMp(actionIndex);
    if (useActionParam->getActorCharacterStatus()->getHaveStatusInfo().getHaveEquipment().isEquipment(0x24) && isNormalAttack(actionIndex)) {
        useMp = 3;
    }
    if (useMp == 0xff) {
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().addMpInBattle(HaveStatusInfo::ExecuteAction, -1024);
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().addMpInBattle(HaveStatusInfo::ResultAction, 0);
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().addMpInBattle(HaveStatusInfo::SpecialAction, 0);
        return;
    }
    if (actionIndex == 0x12) {
        g_Party.setBattleMode();
        int count = g_Party.getCount();
        for (int i = 0; i < count; i++) {
            if (!g_Party.isInsideCarriage(i)) {
                g_Party.getPlayerStatus(i).getHaveStatusInfo().addMpInBattle(HaveStatusInfo::ExecuteAction, -useMp);
                g_Party.getPlayerStatus(i).getHaveStatusInfo().addMpInBattle(HaveStatusInfo::ResultAction, 0);
                g_Party.getPlayerStatus(i).getHaveStatusInfo().addMpInBattle(HaveStatusInfo::SpecialAction, 0);
            }
        }
        return;
    }
    if (useMp) {
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().addMpInBattle(HaveStatusInfo::ExecuteAction, -useMp);
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().addMpInBattle(HaveStatusInfo::ResultAction, 0);
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().addMpInBattle(HaveStatusInfo::SpecialAction, 0);
    }
}

THUMB bool status::ActionCheckActor::isAlive(UseActionParam* useActionParam)
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
    if (actor != target) {
        return true;
    }
    if (actionIndex == 0x1eb) {
        return true;
    }
    if (!actor->getHaveStatusInfo().isDeath()) {
        return true;
    }
    return false;
}
