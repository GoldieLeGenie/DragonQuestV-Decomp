#include "main/status/ActionExecRefrection.hpp"
#include "main/status/ActionMessage.hpp"
#include "main/status/BaseActionStatus.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/UseAction.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "main/dss/UnkRandom.hpp"

inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline void status::UseActionParam::setTargetCharacterStatus(int index, CharacterStatus* info) { targetCharacterStatus_[index] = info; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline int status::UseActionParam::getCurrentTargetIndex() { return currentTargetIndex_; }
inline int status::UseActionParam::getActionDefenceValue() { return actionDefenceValue_; }
inline int status::UseActionParam::getEffectValue() { return effectValue_; }
inline int status::UseActionParam::getPlayerEffectValue() { return playerEffectValue_; }
inline int status::UseActionParam::getMonsterEffectValue() { return monsterEffectValue_; }
inline void status::UseActionParam::setTargetCount(int count) { targetCount_ = count; }
inline status::UseActionMessage& status::UseActionParam::getUseActionMessage(int index) { return message_[index]; }
inline int status::UseActionMessage::getResultMessage(int index) { return resultMessage_[index]; }
inline void status::UseActionMessage::setResultMessage(int index, int message) { resultMessage_[index] = message; }
inline int status::UseActionMessage::getAddMessage(int index) { return addMessage_[index]; }
inline void status::UseActionMessage::setAddMessage(int index, int message) { addMessage_[index] = message; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline int status::HaveStatusInfo::getUseActionEffectValue() { return effectValue_; }
inline status::ActionDefence& status::HaveStatusInfo::getActionDefence() { return actionDefence_; }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::HaveEquipment& status::HaveStatusInfo::getHaveEquipment() { return haveEquipment_; }
inline unsigned char status::ActionDefence::getZaki() { return zaki_; }
inline int status::ActionDefence::getMedapani() { return medapani_; }
inline int status::ActionDefence::getRariho() { return rariho_; }
inline int status::ActionDefence::getVenom() { return venom_; }
inline void status::BaseActionStatus::setActionIndex(int actionIndex) { actionIndex_ = actionIndex; }
inline void status::ActionMessage::setInstantDeath(bool flag) { instantDeath_ = flag; }
inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index) { return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned char dq5::level::ActionParam::getTypeID() { return typeID; }

THUMB int status::ActionExecRefrection::execActionEffect(UseActionParam* useActionParam)
{
    int resultFlag;
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (useActionParam->getActionDefenceValue() == 0) {
        if (target != NULL) {
            target->getHaveStatusInfo().setUseActionEffectValue(0);
        }
        return false;
    }
    resultFlag = true;
    BaseActionStatus::setActionIndex(actionIndex);
    BaseActionStatus::setEffectValue(useActionParam->getEffectValue(), useActionParam->getPlayerEffectValue(), useActionParam->getMonsterEffectValue());
    if (target != NULL) {
        target->getHaveStatusInfo().setUseActionEffectValue(0);
    }
    ActionMessage::setInstantDeath(false);
    unsigned char type = dq5::level::ActionParam::getRecord(actionIndex)->getTypeID();
    switch (type) {
    case dq5::level::ActionParam::ACTIONTYPE_NONE:
        resultFlag = BaseActionStatus::actionTypeNone(actor, target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_DAMAGE:
        resultFlag = BaseActionStatus::actionTypeDamage(actor, target);
        ActionMessage::setInstantDeath(true);
        if (target->getHaveStatusInfo().isDeath() && actor == target) {
            target->getHaveStatusInfo().setDamageMyself(true);
        }
        if (actionIndex == 0x18) {
            ActionMessage::setInstantDeath(false);
        }
        if (actionIndex == 0x1ec) {
            ActionMessage::setInstantDeath(false);
        }
        break;
    case dq5::level::ActionParam::ACTIONTYPE_KAIFUKU:
        resultFlag = BaseActionStatus::actionTypeRecovery(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_SOKUSHI:
        BaseActionStatus::actionTypeInstantDeath(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_FUKKATSU:
        resultFlag = BaseActionStatus::actionTypeRebirth(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MP_ADD:
        resultFlag = BaseActionStatus::actionTypeAddMP(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MP_SUB:
        resultFlag = BaseActionStatus::actionTypeSubMP(actor, target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_ST_CLR:
        resultFlag = BaseActionStatus::actionTypeStatusClear(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_NAKAMAYOBI:
        if (useActionParam->getCurrentTargetIndex() == 0) {
            resultFlag = BaseActionStatus::actionTypeCallFriend(actor);
        }
        break;
    case dq5::level::ActionParam::ACTIONTYPE_PARTY_CHANGE:
        BaseActionStatus::actionTypePartyReorder(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_SAKUSENHENKOU:
        BaseActionStatus::actionTypeChangeTactics();
        break;
    case dq5::level::ActionParam::ACTIONTYPE_DISAPPEAR:
        resultFlag = BaseActionStatus::actionTypeDisappear(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_STR_PLUS:
        resultFlag = BaseActionStatus::actionTypeAddStrength(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_SPD_PLUS:
        resultFlag = BaseActionStatus::actionTypeAddAgility(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_DEF_PLUS:
        resultFlag = BaseActionStatus::actionTypeAddProtection(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_INT_PLUS:
        resultFlag = BaseActionStatus::actionTypeAddWisdom(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MAXHP_PLUS:
        resultFlag = BaseActionStatus::actionTypeAddMaxHp(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MAXMP_PLUS:
        resultFlag = BaseActionStatus::actionTypeAddMaxMp(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_ASTORON:
        BaseActionStatus::actionTypeAstoron(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MAHI:
        BaseActionStatus::actionTypeSpazz(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_NEMURI:
        resultFlag = BaseActionStatus::actionTypeSleep(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MANUSA:
        BaseActionStatus::actionTypeManusa(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_BAIKIRUTO:
        resultFlag = BaseActionStatus::actionTypeBaikiruto(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_DF_HENKA:
        resultFlag = BaseActionStatus::actionTypeDefenceChange(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_BUKIMINAHIKARI:
        BaseActionStatus::actionTypeEerieLight(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_FUBAHA:
        BaseActionStatus::actionTypeFubaha(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA:
        BaseActionStatus::actionTypeMahokanta(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MOSYASU:
        resultFlag = BaseActionStatus::actionTypeMosyas(actor, target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_TAMEKEI:
        BaseActionStatus::actionTypePowerSave(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MAHOTON:
        BaseActionStatus::actionTypeMahoton(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_DORAGORAM:
        BaseActionStatus::actionTypeDragoram(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_KONRAN:
        BaseActionStatus::actionTypeConfusion(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_PATH_1:
        BaseActionStatus::actionTypePath1(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_DOKU:
        BaseActionStatus::actionTypePoison(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MOUDOKU:
        BaseActionStatus::actionTypePoison(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_CLOSEDOOR:
        BaseActionStatus::actionTypeCloseDoor(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_CURSE1:
        resultFlag = BaseActionStatus::actionTypeCurse1(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_CURSE2:
        resultFlag = BaseActionStatus::actionTypeCurse2(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_CURSE3:
        resultFlag = BaseActionStatus::actionTypeCurse3(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_CURSE4:
        resultFlag = BaseActionStatus::actionTypeCurse4(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_CURSE5:
        resultFlag = BaseActionStatus::actionTypeCurse5(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MAHOKITE:
        BaseActionStatus::actionTypeMahokite(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_DEFENCE:
        BaseActionStatus::actionTypeDefence(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_FIZZLEZONE:
        BaseActionStatus::actionTypeFizzleZone(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_TIMESTOP:
        BaseActionStatus::actionTypeTimeStop(actor);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_TOHEROSU:
        resultFlag = BaseActionStatus::actionTypeToherosu(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_SINOBIASI:
        resultFlag = BaseActionStatus::actionTypeSinobiasi(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_NORMAL_MAMONONOESA:
        resultFlag = BaseActionStatus::actionTypeMonstersFood(target);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MSG_ONLY:
        resultFlag = BaseActionStatus::actionTypeMsgOnly(actor);
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MSG_SUCCESS:
        resultFlag = BaseActionStatus::actionTypeMsgSuccess();
        break;
    case dq5::level::ActionParam::ACTIONTYPE_MSG_FAILED:
        resultFlag = BaseActionStatus::actionTypeMsgFailed();
        break;
    default:
        resultFlag = BaseActionStatus::actionTypeNone(actor, target);
        break;
    }
    if (actionIndex >= 0xb5 && actionIndex <= 0xc1 && resultFlag) {
        int count = getCallMonsterCount();
        useActionParam->setTargetCount(count);
        for (int i = 0; i < count; i++) {
            useActionParam->setTargetCharacterStatus(i, getCallMonsterStatus(i));
            int mess = useActionParam->getUseActionMessage(0).getResultMessage(0);
            useActionParam->getUseActionMessage(i).setResultMessage(0, mess);
        }
    }
    return resultFlag;
}

THUMB void status::ActionExecRefrection::execAddDamage(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    int index = useActionParam->getCurrentTargetIndex();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(index);
    if (actor == NULL || target == NULL) {
        return;
    }
    if (actionIndex == 0x53) {
        if (target->getHaveStatusInfo().getUseActionEffectValue() == 0) {
            return;
        }
        if (target->getHaveStatusInfo().isDeath()) {
            return;
        }
        int effectValue = target->getHaveStatusInfo().getActionDefence().getEffectValue(0x1e6);
        if (effectValue) {
            checkCloseDoor(target);
            if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
                target->getHaveStatusInfo().getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_NEMURI, true);
                target->getHaveStatusInfo().setStatusChangeInBattle(HaveStatusInfo::ResultAction);
                target->getHaveStatusInfo().setStatusChangeInBattle(HaveStatusInfo::ResultAction);
                actor->getHaveStatusInfo().setAddEffectSleep(true);
                target->getHaveStatusInfo().setSleepTurn(true);
                ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3b0b, 0);
            } else {
                target->getHaveStatusInfo().getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_NEMURI, true);
                target->getHaveStatusInfo().setStatusChangeInBattle(HaveStatusInfo::ResultAction);
                target->getHaveStatusInfo().setStatusChangeInBattle(HaveStatusInfo::ResultAction);
                actor->getHaveStatusInfo().setAddEffectSleep(true);
                target->getHaveStatusInfo().setSleepTurn(true);
                ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3b0d, 0);
            }
        }
    }
    if (actionIndex == 0x54) {
        if (target->getHaveStatusInfo().getUseActionEffectValue() == 0) {
            return;
        }
        if (target->getHaveStatusInfo().isDeath()) {
            return;
        }
        int effectValue = target->getHaveStatusInfo().getActionDefence().getEffectValue(0x1e7);
        if (effectValue) {
            if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU)) {
                target->getHaveStatusInfo().getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_DOKU, false);
                target->getHaveStatusInfo().setStatusChangeInBattle(HaveStatusInfo::ResultAction);
                actor->getHaveStatusInfo().setAddEffectPoison(true);
                int mess = useActionParam->getUseActionMessage(index).getAddMessage(0);
                if (mess) {
                    useActionParam->getUseActionMessage(index).setAddMessage(1, 0xc3b15);
                } else {
                    ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3b15, 0);
                }
            } else {
                target->getHaveStatusInfo().getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_DOKU, false);
                target->getHaveStatusInfo().setStatusChangeInBattle(HaveStatusInfo::ResultAction);
                actor->getHaveStatusInfo().setAddEffectPoison(true);
                int mess = useActionParam->getUseActionMessage(index).getAddMessage(0);
                if (mess) {
                    useActionParam->getUseActionMessage(index).setAddMessage(1, 0xc3b13);
                } else {
                    ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3b13, 0);
                }
            }
        }
    }
    if (actionIndex == 0x55) {
        if (target->getHaveStatusInfo().getUseActionEffectValue() == 0) {
            return;
        }
        if (target->getHaveStatusInfo().isDeath()) {
            return;
        }
        int effectValue = target->getHaveStatusInfo().getActionDefence().getEffectValue(0x1e8);
        if (effectValue) {
            checkCloseDoor(target);
            if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
                actor->getHaveStatusInfo().setAddEffectSpazz(true);
                ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3b17, 0);
            } else {
                target->getHaveStatusInfo().getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_MAHI, true);
                target->getHaveStatusInfo().setStatusChangeInBattle(HaveStatusInfo::ResultAction);
                actor->getHaveStatusInfo().setAddEffectSpazz(true);
                ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3c3c, 0);
            }
        }
    }
}

THUMB void status::ActionExecRefrection::execAddDamageItemForceE(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (actor == NULL || target == NULL) {
        return;
    }
    if (!UseAction::isForceE(actionIndex)) {
        return;
    }
    if (target->getHaveStatusInfo().isDeath()) {
        return;
    }
    HaveEquipment& haveEquipment = actor->getHaveStatusInfo().getHaveEquipment();
    if (haveEquipment.isEquipment(0x10) && useActionParam->getMonsterEffectValue() && UnkDssRand::rand(4) == 0 &&
        target->getHaveStatusInfo().getActionDefence().getRariho() != 3) {
        checkCloseDoor(target);
        if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
            target->getHaveStatusInfo().getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_NEMURI, true);
            actor->getHaveStatusInfo().setAddEffectSleep(true);
            target->getHaveStatusInfo().setSleepTurn(true);
            ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3b0b, 0);
        } else {
            target->getHaveStatusInfo().getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_NEMURI, true);
            actor->getHaveStatusInfo().setAddEffectSleep(true);
            target->getHaveStatusInfo().setSleepTurn(true);
            ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3b09, 0);
        }
    }
    if (haveEquipment.isEquipment(0x12) && useActionParam->getMonsterEffectValue() && UnkDssRand::rand(4) == 0 &&
        target->getHaveStatusInfo().getActionDefence().getMedapani() != 3) {
        checkCloseDoor(target);
        if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN)) {
            target->getHaveStatusInfo().getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_KONRAN, true);
            target->getHaveStatusInfo().setSleepTurn(true);
            ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3b1d, 0);
        } else {
            target->getHaveStatusInfo().getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_KONRAN, true);
            target->getHaveStatusInfo().setSleepTurn(true);
            ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3b19, 0);
        }
    }
    if (haveEquipment.isEquipment(0x32) && useActionParam->getMonsterEffectValue() && UnkDssRand::rand(6) == 0 &&
        target->getHaveStatusInfo().getActionDefence().getZaki() != 3) {
        checkCloseDoor(target);
        target->getHaveStatusInfo().getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_MAHI, false);
        target->getHaveStatusInfo().setStatusChangeInBattle(HaveStatusInfo::ResultAction);
        actor->getHaveStatusInfo().setAddEffectSpazz(true);
        ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc3c3c, 0);
    }
    if (haveEquipment.isEquipment(0x2f) && useActionParam->getMonsterEffectValue() && UnkDssRand::rand(4) == 0 &&
        target->getHaveStatusInfo().getActionDefence().getVenom() != 3) {
        target->getHaveStatusInfo().getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU, true);
        actor->getHaveStatusInfo().setAddEffectPoison(true);
        ActionMessage::setAddMessage(useActionParam->getUseActionMessage(0), 0xc39d5, 0);
    }
}
