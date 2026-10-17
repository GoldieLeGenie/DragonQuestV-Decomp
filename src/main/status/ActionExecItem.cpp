#include "main/status/ActionExecItem.hpp"
#include "main/status/ActionMessage.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/HaveAction.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "main/dss/UnkRandom.hpp"
#include "ov000/status/MonsterParty.hpp"

inline status::HaveItem& status::HaveStatusInfo::getHaveItem()
{
    return haveItem_;
}

inline status::HaveEquipment& status::HaveStatusInfo::getHaveEquipment()
{
    return haveEquipment_;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index) { return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline char dq5::level::ActionParam::getMohokite() { return (byte_2 & 0x8) >> 3; }
inline int status::UseActionMessage::getAddMessage(int index) { return addMessage_[index]; }
inline void status::UseActionMessage::setAddMessage(int index, int message) { addMessage_[index] = message; }
inline void status::HaveStatusInfo::setAddDamage(int dm) { addDamage_ = dm; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline int status::UseActionParam::getCurrentTargetIndex() { return currentTargetIndex_; }
inline int status::UseActionParam::getPlayerEffectValue() { return playerEffectValue_; }
inline int status::UseActionParam::getMonsterEffectValue() { return monsterEffectValue_; }
inline status::UseActionMessage& status::UseActionParam::getUseActionMessage(int index) { return message_[index]; }

THUMB bool status::ActionExecItem::checkItemForceE(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->actionIndex_;
    CharacterStatus* actor = useActionParam->actorCharacterStatus_;
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (target == NULL) {
        return true;
    }
    if (UseAction::isForceE(actionIndex)) {
        HaveEquipment& haveEquipment = actor->getHaveStatusInfo().getHaveEquipment();
        if (haveEquipment.isEquipment(0x33)) {
            if (actor->getHaveStatusInfo().isImmediateDeathItem()) {
                target->getHaveStatusInfo().addHpInBattle(HaveStatusInfo::ResultAction, -1023);
                target->getHaveStatusInfo().setUseActionEffectValue(0);
                target->setDeathAnimation();
                target->getHaveStatusInfo().setImmidiateDeath(true);
                ActionMessage::setExecMessage(actionIndex, useActionParam->message_[0]);
                ActionMessage::setResultMessage(useActionParam->message_[0], 0xc3b61, 0);
                int count = g_Monster.getCount();
                for (int i = 0; i < count; i++) {
                    if (&g_Monster.getMonsterStatus(i) == target) {
                        g_Monster.checkDropItemMonster(i);
                        break;
                    }
                }
                return false;
            }
            useActionParam->setPlayerEffectValue(1);
            useActionParam->setMonsterEffectValue(1);
        }
        if (haveEquipment.isEquipment(0x40)) {
            if (actor->getHaveStatusInfo().isImmediateDeathItem()) {
                actor->getHaveStatusInfo().setWeaponAddDamage(true);
                target->getHaveStatusInfo().addHpInBattle(HaveStatusInfo::ResultAction, -1023);
                target->getHaveStatusInfo().setUseActionEffectValue(0);
                target->setDeathAnimation();
                target->getHaveStatusInfo().setImmidiateDeath(true);
                ActionMessage::setExecMessage(actionIndex, useActionParam->message_[0]);
                ActionMessage::setResultMessage(useActionParam->message_[0], 0xc3b61, 0);
                int count = g_Monster.getCount();
                for (int i = 0; i < count; i++) {
                    if (&g_Monster.getMonsterStatus(i) == target) {
                        g_Monster.checkDropItemMonster(i);
                        break;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

THUMB void status::ActionExecItem::checkItemOther(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->actionIndex_;
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    CharacterStatus* target = useActionParam->getTargetCharacterStatus(useActionParam->getCurrentTargetIndex());
    if (actor == NULL || target == NULL || HaveAction::isTownMode()) {
        return;
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x5c) && dq5::level::ActionParam::getRecord(actionIndex)->getMohokite()
        && useActionParam->getPlayerEffectValue() && UnkDssRand::rand(6) == 0 && actor != target) {
        int mp = UseAction::getUseMp(actionIndex);
        if (mp) {
            target->getHaveStatusInfo().addMpInBattle(HaveStatusInfo::ResultAction, mp);
            target->getHaveStatusInfo().setAddMahotoraExecute(true);
            target->getHaveStatusInfo().setAddDamage(mp);
            int index = useActionParam->getCurrentTargetIndex();
            ActionMessage::setAddMessage(useActionParam->getUseActionMessage(index), 0, 0xc3b5f);
        }
    }
    if (target->getHaveStatusInfo().getHaveEquipment().isEquipment(0x66) && useActionParam->getPlayerEffectValue() && UnkDssRand::rand(2) == 0
        && UseAction::isYaibaArmor(actionIndex) && UseAction::getDamageType(actionIndex) == UseAction::DamageTypeDamage
        && !actor->getHaveStatusInfo().isDeath()) {
        actor->getHaveStatusInfo().addHpInBattle(HaveStatusInfo::ResultAction, -useActionParam->getPlayerEffectValue() / 4);
        target->getHaveStatusInfo().setAddEffectDamage(true);
        target->setAddDamageAnimation();
        if (useActionParam->getPlayerEffectValue() / 4) {
            actor->getHaveStatusInfo().setCounterDamage(true);
            actor->getHaveStatusInfo().setAddDamage(useActionParam->getPlayerEffectValue() / 4);
            int index = useActionParam->getCurrentTargetIndex();
            if (!actor->getHaveStatusInfo().isDeath()) {
                int mess = useActionParam->getUseActionMessage(index).getAddMessage(0);
                if (mess) {
                    useActionParam->getUseActionMessage(index).setAddMessage(0, 0xc3ce5);
                    useActionParam->getUseActionMessage(index).setAddMessage(1, mess);
                } else {
                    useActionParam->getUseActionMessage(index).setAddMessage(0, 0xc3ce5);
                }
            } else {
                int mess = useActionParam->getUseActionMessage(index).getAddMessage(0);
                if (mess) {
                    useActionParam->getUseActionMessage(index).setAddMessage(0, 0xc3cf9);
                    useActionParam->getUseActionMessage(index).setAddMessage(1, mess);
                } else {
                    useActionParam->getUseActionMessage(index).setAddMessage(0, 0xc3cf9);
                }
            }
        }
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x18) && UseAction::isDamageC(actionIndex) && useActionParam->getMonsterEffectValue()
        && UseAction::getDamageType(actionIndex) == UseAction::DamageTypeDamage) {
        int effectValue = useActionParam->getMonsterEffectValue() / 4;
        actor->getHaveStatusInfo().addHpInBattle(HaveStatusInfo::ResultAction, -effectValue);
        target->getHaveStatusInfo().setAddEffectDamage(true);
        target->setAddDamageAnimation();
        if (effectValue) {
            actor->getHaveStatusInfo().setDamageMyself(true);
            actor->getHaveStatusInfo().setAddDamage(effectValue);
            int index = useActionParam->getCurrentTargetIndex();
            ActionMessage::setAddMessage(useActionParam->getUseActionMessage(index), 0xc3ce5, 0);
            if (actor->getHaveStatusInfo().isDeath()) {
                if (g_Story.getChapter() == dq5::CHAPTER_YOUNENKI) {
                    ActionMessage::setAddMessage(useActionParam->getUseActionMessage(index), 0xc3cf7, 0);
                } else {
                    ActionMessage::setAddMessage(useActionParam->getUseActionMessage(index), 0xc3cf9, 0);
                }
            }
        }
    }
}

THUMB bool status::ActionExecItem::checkLifeStone(int actionIndex, CharacterStatus* actor, CharacterStatus* target)
{
    if (actor == target) {
        return false;
    }
    if (actionIndex == 0x1e0) {
        return false;
    }
    if (target->getHaveStatusInfo().getHaveItem().isItem(0xbb)) {
        target->getHaveStatusInfo().setLifeStoneEnable(true);
        int count = target->getHaveStatusInfo().getHaveItem().getCount();
        for (int i = 0; i < count; i++) {
            if (target->getHaveStatusInfo().getHaveItem().getItem(i) == 0xbb) {
                target->getHaveStatusInfo().execThrow(i);
                break;
            }
        }
        return true;
    }
    return false;
}
