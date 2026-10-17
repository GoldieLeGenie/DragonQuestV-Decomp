#include "main/status/ActionEffectValue.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/dss/UnkRandom.hpp"

inline status::HaveEquipment& status::HaveStatusInfo::getHaveEquipment()
{
    return haveEquipment_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline status::ActionDefence& status::HaveStatusInfo::getActionDefence() { return actionDefence_; }
inline unsigned char status::ActionDefence::getZaki() { return zaki_; }
inline bool status::HaveBattleStatus::isZombi() { return zombi_; }
inline bool status::HaveBattleStatus::isDragon() { return dragon_; }
inline bool status::HaveBattleStatus::isMetal() { return metal_; }
inline int status::HaveBattleStatus::getActionIndex() { return actionIndex_; }
inline void status::UseActionFlag::setTimeReverse(bool flag) { timeReverseFlag_ = flag; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline void status::UseActionParam::setAddActionIndex(int actionIndex)
{
    preActionIndex_ = actionIndex_;
    addActionIndex_ = actionIndex;
}
inline int status::UseActionParam::getCurrentTargetIndex() { return currentTargetIndex_; }
inline void status::UseActionParam::setEffectValue(int value) { effectValue_ = value; }
inline int status::UseActionParam::getEffectValue() { return effectValue_; }
inline int status::UseActionParam::getPlayerEffectValue() { return playerEffectValue_; }
inline int status::UseActionParam::getMonsterEffectValue() { return monsterEffectValue_; }
inline int status::UseActionParam::getActionDefenceValue() { return actionDefenceValue_; }
inline void status::UseActionParam::setActionDefenceValue(int value) { actionDefenceValue_ = value; }
inline void status::ActionEffectValue::clearEffectValue() { specialTargetEffectValue_ = 0; }

int status::ActionEffectValue::specialTargetEffectValue_;

THUMB void status::ActionEffectValue::execActionDefence(UseActionParam* useActionParam)
{
    execActionDefenceBasic(useActionParam);
    execActionDefenceException(useActionParam);
    setEffectValueWithEquipmentActionDefence(useActionParam);
}

THUMB void status::ActionEffectValue::execActionDefenceBasic(UseActionParam* useActionParam)
{
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    int actionIndex = useActionParam->getActionIndex();
    if (target == NULL) {
        useActionParam->setActionDefenceValue(1000);
    } else {
        useActionParam->setActionDefenceValue(target->getHaveStatusInfo().getActionDefence().getEffectValue(actionIndex));
    }
    useActionParam->setPlayerEffectValue(useActionParam->getPlayerEffectValue() * useActionParam->getActionDefenceValue() / 1000);
    useActionParam->setMonsterEffectValue(useActionParam->getMonsterEffectValue() * useActionParam->getActionDefenceValue() / 1000);
}

THUMB void status::ActionEffectValue::execActionDefenceException(UseActionParam* useActionParam)
{
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target == NULL) {
        return;
    }
}

THUMB void status::ActionEffectValue::addActionDefence(UseActionParam* useActionParam, int ratio)
{
    useActionParam->setActionDefenceValue(useActionParam->getActionDefenceValue() * ratio / 1000);
}

THUMB void status::ActionEffectValue::setEffectValue(UseActionParam* useActionParam, bool flag)
{
    checkMultiAttack(useActionParam);
    if (specialTargetEffectValue_ == 0) {
        if (flag) {
            specialTargetEffectValue_ = 1;
        }
        setEffectValueNormalAttack(useActionParam);
        setEffectValueBasic(useActionParam);
        setEffectValueException(useActionParam);
    }
}

THUMB void status::ActionEffectValue::checkMultiAttack(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    int actionIndex = useActionParam->getActionIndex();
    if (isDoubleAction(actor, actionIndex)) {
        if (actor->getHaveStatusInfo().isMultiAttack()) {
            if (useActionParam->getCurrentTargetIndex() == 1) {
                clearEffectValue();
            }
        }
    }
}

THUMB void status::ActionEffectValue::setEffectValueNormalAttack(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (actor != NULL && target != NULL) {
        int effectValue = getUsuallyAttackEffectValue(actor, target);
        useActionParam->setEffectValue(effectValue);
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
}

THUMB void status::ActionEffectValue::setEffectValueBasic(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    int actionIndex = useActionParam->getActionIndex();
    if (target == NULL) {
        return;
    }
    int playerEffectValue = UseAction::getEffectValueToPlayer(actionIndex);
    int monsterEffectValue = UseAction::getEffectValueToMonster(actionIndex);
    if (playerEffectValue + monsterEffectValue == 0) {
        return;
    }
    useActionParam->setPlayerEffectValue(playerEffectValue);
    useActionParam->setMonsterEffectValue(monsterEffectValue);
    if (target->getCharacterType() == PLAYER) {
        useActionParam->setEffectValue(useActionParam->getPlayerEffectValue());
    } else {
        useActionParam->setEffectValue(useActionParam->getMonsterEffectValue());
    }
    if (actor != NULL && target != NULL) {
        useActionParam->setEffectValue(getUsuallyAttackEffectValue(actor, target));
    }
}

THUMB void status::ActionEffectValue::setEffectValueAdd(UseActionParam* useActionParam, int ratio, int offset)
{
    useActionParam->setEffectValue(useActionParam->getEffectValue() * ratio / 1000 + offset);
    useActionParam->setPlayerEffectValue(useActionParam->getPlayerEffectValue() * ratio / 1000 + offset);
    useActionParam->setMonsterEffectValue(useActionParam->getMonsterEffectValue() * ratio / 1000 + offset);
}

THUMB void status::ActionEffectValue::execEffectValueWithEquipment(UseActionParam* useActionParam)
{
    setEffectValueWithEquipmentAttack(useActionParam);
    setEffectValueWithEquipmentDefence(useActionParam);
}

THUMB void status::ActionEffectValue::setEffectValueWithEquipmentAttack(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (!UseAction::isDamageC(useActionParam->getActionIndex())) {
        return;
    }
    if ((actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x13) || actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x1a)) && !actor->getHaveStatusInfo().isKaishin()) {
        int rate = target->getHaveStatusInfo().getActionDefence().getEffectValue(10);
        int DM = useActionParam->getEffectValue();
        DM += DM * rate / 1000 / 2;
        useActionParam->setEffectValue(DM);
        useActionParam->setPlayerEffectValue(DM);
        useActionParam->setMonsterEffectValue(DM);
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x2e) && !actor->getHaveStatusInfo().isKaishin()) {
        int rate = target->getHaveStatusInfo().getActionDefence().getEffectValue(4);
        int DM = useActionParam->getEffectValue();
        DM += DM * rate / 1000 / 2;
        useActionParam->setEffectValue(DM);
        useActionParam->setPlayerEffectValue(DM);
        useActionParam->setMonsterEffectValue(DM);
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x14) && target->getHaveBattleStatus().isZombi() && !actor->getHaveStatusInfo().isKaishin()) {
        useActionParam->setPlayerEffectValue(useActionParam->getPlayerEffectValue() * 3 / 2);
        useActionParam->setMonsterEffectValue(useActionParam->getMonsterEffectValue() * 3 / 2);
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x16) && target->getHaveBattleStatus().isDragon() && !actor->getHaveStatusInfo().isKaishin()) {
        useActionParam->setPlayerEffectValue(useActionParam->getPlayerEffectValue() * 3 / 2);
        useActionParam->setMonsterEffectValue(useActionParam->getMonsterEffectValue() * 3 / 2);
    }
}

THUMB void status::ActionEffectValue::setEffectValueWithEquipmentDefence(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target == NULL) {
        return;
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x5d)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_MERA:
        case dq5::level::ActionParam::DEFENCE_GIRA:
            setEffectValueAdd(useActionParam, 1000, -15);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x64)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_FIRE:
            setEffectValueAdd(useActionParam, 1000, -15);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x65)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_MERA:
        case dq5::level::ActionParam::DEFENCE_GIRA:
        case dq5::level::ActionParam::DEFENCE_HYADO:
        case dq5::level::ActionParam::DEFENCE_BAGI:
            setEffectValueAdd(useActionParam, 1000, -15);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x67)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_MERA:
        case dq5::level::ActionParam::DEFENCE_GIRA:
        case dq5::level::ActionParam::DEFENCE_FIRE:
            setEffectValueAdd(useActionParam, 1000, -25);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x68)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_MERA:
        case dq5::level::ActionParam::DEFENCE_GIRA:
        case dq5::level::ActionParam::DEFENCE_HYADO:
        case dq5::level::ActionParam::DEFENCE_BAGI:
            setEffectValueAdd(useActionParam, 1000, -20);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x69)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_MERA:
        case dq5::level::ActionParam::DEFENCE_GIRA:
        case dq5::level::ActionParam::DEFENCE_HYADO:
        case dq5::level::ActionParam::DEFENCE_BAGI:
            setEffectValueAdd(useActionParam, 1000, -10);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x6c)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_HYADO:
        case dq5::level::ActionParam::DEFENCE_BLIZZARD:
            setEffectValueAdd(useActionParam, 1000, -15);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x6d)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_HYADO:
        case dq5::level::ActionParam::DEFENCE_BLIZZARD:
            setEffectValueAdd(useActionParam, 1000, -25);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x70)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_FIRE:
        case dq5::level::ActionParam::DEFENCE_BLIZZARD:
            setEffectValueAdd(useActionParam, 1000, -40);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x71)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_GIRA:
        case dq5::level::ActionParam::DEFENCE_FIRE:
        case dq5::level::ActionParam::DEFENCE_BLIZZARD:
            setEffectValueAdd(useActionParam, 1000, -20);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x72)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_MERA:
        case dq5::level::ActionParam::DEFENCE_GIRA:
        case dq5::level::ActionParam::DEFENCE_HYADO:
        case dq5::level::ActionParam::DEFENCE_BAGI:
        case dq5::level::ActionParam::DEFENCE_FIRE:
        case dq5::level::ActionParam::DEFENCE_BLIZZARD:
            setEffectValueAdd(useActionParam, 1000, -30);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x73)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_MERA:
        case dq5::level::ActionParam::DEFENCE_GIRA:
        case dq5::level::ActionParam::DEFENCE_HYADO:
        case dq5::level::ActionParam::DEFENCE_BAGI:
        case dq5::level::ActionParam::DEFENCE_FIRE:
        case dq5::level::ActionParam::DEFENCE_BLIZZARD:
            setEffectValueAdd(useActionParam, 1000, -30);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x75)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_MERA:
        case dq5::level::ActionParam::DEFENCE_GIRA:
        case dq5::level::ActionParam::DEFENCE_HYADO:
        case dq5::level::ActionParam::DEFENCE_BAGI:
            setEffectValueAdd(useActionParam, 1000, 20);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x7a)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_FIRE:
        case dq5::level::ActionParam::DEFENCE_BLIZZARD:
            setEffectValueAdd(useActionParam, 1000, -4);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x7b)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_MERA:
        case dq5::level::ActionParam::DEFENCE_GIRA:
        case dq5::level::ActionParam::DEFENCE_FIRE:
            setEffectValueAdd(useActionParam, 1000, -7);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x7c)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_FIRE:
        case dq5::level::ActionParam::DEFENCE_BLIZZARD:
            setEffectValueAdd(useActionParam, 1000, -10);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x7d)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_FIRE:
        case dq5::level::ActionParam::DEFENCE_BLIZZARD:
            setEffectValueAdd(useActionParam, 1000, -10);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x7f)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_HYADO:
        case dq5::level::ActionParam::DEFENCE_BLIZZARD:
            setEffectValueAdd(useActionParam, 1000, -15);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x81)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_FIRE:
        case dq5::level::ActionParam::DEFENCE_BLIZZARD:
            setEffectValueAdd(useActionParam, 1000, -10);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x82)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_MERA:
        case dq5::level::ActionParam::DEFENCE_GIRA:
        case dq5::level::ActionParam::DEFENCE_FIRE:
            setEffectValueAdd(useActionParam, 1000, -15);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x83)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_FIRE:
        case dq5::level::ActionParam::DEFENCE_BLIZZARD:
            setEffectValueAdd(useActionParam, 1000, -15);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x84)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_FIRE:
        case dq5::level::ActionParam::DEFENCE_BLIZZARD:
            setEffectValueAdd(useActionParam, 1000, -20);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x9e)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_IO:
        case dq5::level::ActionParam::DEFENCE_HYADO:
            setEffectValueAdd(useActionParam, 1000, -10);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x9f)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_MERA:
        case dq5::level::ActionParam::DEFENCE_GIRA:
        case dq5::level::ActionParam::DEFENCE_BAGI:
            setEffectValueAdd(useActionParam, 1000, -10);
        }
    }
}

THUMB void status::ActionEffectValue::setEffectValueWithEquipmentActionDefence(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target == NULL) {
        return;
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x6d)) {
        if (UseAction::getActionDefenceKind2(actionIndex) == dq5::level::ActionParam::DEFENCE_ZAKI) {
            addActionDefence(useActionParam, UnkDssRand::rand(2) * 1000);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x85)) {
        bool flag = false;
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_ZAKI:
        case dq5::level::ActionParam::DEFENCE_MANUSA:
        case dq5::level::ActionParam::DEFENCE_MEDAPANI:
        case dq5::level::ActionParam::DEFENCE_RARIHO:
        case dq5::level::ActionParam::DEFENCE_RARIHOMA:
            flag = true;
        }
        if (flag) {
            if (UnkDssRand::rand(2) == 0) {
                addActionDefence(useActionParam, 1000);
            } else {
                addActionDefence(useActionParam, 0);
            }
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x95)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_ZAKI:
        case dq5::level::ActionParam::DEFENCE_MEDAPANI:
        case dq5::level::ActionParam::DEFENCE_RARIHO:
        case dq5::level::ActionParam::DEFENCE_MAHOTOON:
        case dq5::level::ActionParam::DEFENCE_RARIHOMA:
            if (UnkDssRand::rand(2) == 0) {
                addActionDefence(useActionParam, 1000);
            } else {
                addActionDefence(useActionParam, 0);
            }
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x98)) {
        if (UseAction::getActionDefenceKind2(actionIndex) == dq5::level::ActionParam::DEFENCE_MEGANTE) {
            addActionDefence(useActionParam, 0);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x9d)) {
        switch (UseAction::getActionDefenceKind2(actionIndex)) {
        case dq5::level::ActionParam::DEFENCE_ZAKI:
        case dq5::level::ActionParam::DEFENCE_MEDAPANI:
        case dq5::level::ActionParam::DEFENCE_RARIHO:
        case dq5::level::ActionParam::DEFENCE_MAHOTOON:
        case dq5::level::ActionParam::DEFENCE_RARIHOMA:
            if (UnkDssRand::rand(4) == 0) {
                addActionDefence(useActionParam, 1000);
            } else {
                addActionDefence(useActionParam, 0);
            }
        }
    }
}

THUMB void status::ActionEffectValue::setEffectValueException(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    int actionIndex = useActionParam->getActionIndex();
    int effectValue;
    if (actionIndex == 0x42) {
        actor->getHaveBattleStatus().setupParupunteAction();
        int action = actor->getHaveBattleStatus().getActionIndex();
        useActionParam->setAddActionIndex(action);
    }
    if (isNormalAttack(actionIndex)) {
        effectValue = useActionParam->getEffectValue();
        if (actor->getHaveStatusInfo().isKaishin()) {
            effectValue = useActionParam->getEffectValue();
        }
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
        setEffectValueWithDoubleAttack(useActionParam);
    }
    if (actionIndex == 0x1de) {
        effectValue = actor->getHaveStatusInfo().getHpMax() / 6;
        if (effectValue == 0) {
            effectValue = 1;
        }
        useActionParam->setEffectValue(effectValue);
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
    if (actionIndex == 0x53) {
        effectValue = useActionParam->getEffectValue();
        useActionParam->setEffectValue(effectValue);
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
    if (actionIndex == 0x54) {
        effectValue = useActionParam->getEffectValue();
        useActionParam->setEffectValue(effectValue);
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
    if (actionIndex == 0x55) {
        effectValue = useActionParam->getEffectValue();
        useActionParam->setEffectValue(effectValue);
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
    if (actionIndex == 0x6a) {
        effectValue = useActionParam->getEffectValue();
        if (!target->getHaveBattleStatus().isMetal()) {
            effectValue += 60;
        }
        useActionParam->setEffectValue(effectValue);
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
    if (actionIndex == 0xa1) {
        effectValue = useActionParam->getEffectValue() * 150 / 100;
        useActionParam->setEffectValue(effectValue);
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
    if ((unsigned int)(actionIndex - 0xa2) <= 0xa) {
        effectValue = useActionParam->getEffectValue() * 125 / 100;
        useActionParam->setEffectValue(effectValue);
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
    if (actionIndex == 0x52) {
        useActionParam->setAddActionIndex(0x1e0);
    }
    if (actionIndex == 0x56) {
        effectValue = getRandomVariation(actor->getHaveStatusInfo().getAttack(0), 0, 5);
        if (target->getHaveStatusInfo().getActionDefence().getZaki() == 3) {
            effectValue = UnkDssRand::rand(2);
        }
        useActionParam->setEffectValue(effectValue);
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
    if (actionIndex == 0x1a5) {
        effectValue = useActionParam->getEffectValue() / 4;
        useActionParam->setEffectValue(effectValue);
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
    if (actionIndex == 0x103) {
        UseActionFlag::setTimeReverse(true);
    }
    if (actionIndex == 0x6b) {
        if (useActionParam->getEffectValue() == 1) {
            effectValue = 1;
        } else {
            effectValue = useActionParam->getEffectValue() / 2;
        }
        useActionParam->setEffectValue(effectValue);
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
    if (actionIndex == 0x19b) {
        effectValue = useActionParam->getEffectValue() / 4;
        useActionParam->setEffectValue(effectValue);
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
    if (actionIndex == 0x1d2) {
        UseActionFlag::setTimeReverse(true);
    }
}

THUMB void status::ActionEffectValue::setEffectValueWithDoubleAttack(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    int count = 0;
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x11)) {
        count++;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x103)) {
        count++;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x102)) {
        count++;
    }
    if (count != 0) {
        int effectValue = useActionParam->getEffectValue() * 75 / 100;
        useActionParam->setEffectValue(effectValue);
        useActionParam->setPlayerEffectValue(effectValue);
        useActionParam->setMonsterEffectValue(effectValue);
    }
}
