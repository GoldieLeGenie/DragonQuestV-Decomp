#include "ov000/btl/BattleActorMacro.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov000/status/MonsterStatus.hpp"
#include "main/btl/Encount.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/UseActionMacro.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/text/TextAPI.hpp"

inline int status::HaveStatus::getPlayerIndex() const { return playerIndex_; }
inline int status::HaveStatusInfo::getPlayerIndex() const { return haveStatus_.getPlayerIndex(); }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline int status::MonsterStatus::getMonsterIndex() { return characterIndex_; }
inline int status::MonsterStatus::getSortIndexInGroup() { return sortIndex_; }
inline int status::MonsterStatus::getMosyasIndex() { return mosyasIndex_; }
inline int status::HaveStatusInfo::getAddDamage() { return addDamage_; }
inline int status::HaveStatusInfo::getUseActionEffectValue() { return effectValue_; }

THUMB void btl::BattleActorMacro::setExecMacro(status::UseActionParam& useActionParam)
{
    int actionIndex = useActionParam.getActionIndex();
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    status::CharacterStatus* target = useActionParam.getTargetCharacterStatus(0);
    status::UseActionMacro::setExecMacro(actor, target, actionIndex);
    setMacroActor(actor, actionIndex);
    setMacroTarget(target, actionIndex, 0);
}

THUMB void btl::BattleActorMacro::setResultMacro(status::UseActionParam& useActionParam, int currentTarget)
{
    int actionIndex = useActionParam.getActionIndex();
    status::CharacterStatus* actor = useActionParam.getActorCharacterStatus();
    status::CharacterStatus* target = useActionParam.getTargetCharacterStatus(currentTarget);
    if (target) {
        status::UseActionMacro::setResultMacro(actor, target, actionIndex);
    }
    setMacroActor(actor, actionIndex);
    setMacroTarget(target, actionIndex, currentTarget);
}

THUMB void btl::BattleActorMacro::setMacroActor(status::CharacterStatus* actor, int actionIndex)
{
    if (actor == NULL) {
        return;
    }
    if (actor->getCharacterType() == PLAYER) {
        TextAPI::setMACRO0(1, 0x50000000, actor->getHaveStatusInfo().getPlayerIndex());
    }
    if (actor->getCharacterType() == MONSTER) {
        status::MonsterStatus* monster = (status::MonsterStatus*)actor;
        int monsterIndex = monster->getMonsterIndex();
        if (status::g_Monster.getMonsterCountDeadOrAlive(monsterIndex) == 1 && !Encount::getSingleton()->getMonsterCountName(monsterIndex)) {
            TextAPI::setMACRO0(1, 0x60000000, monsterIndex);
        }
        else {
            int sortIndex = monster->getSortIndexInGroup();
            TextAPI::setMACRO0(1, 0x60000000, monsterIndex, sortIndex);
        }
        if (!actor->getHaveStatusInfo().isFirstMosyas() && actor->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU)) {
            int playerIndex = monster->getMosyasIndex();
            TextAPI::setMACRO0(1, 0x50000000, playerIndex, 1, -1);
        }
    }
    if (actor->getHaveStatusInfo().getAddDamage()) {
        TextAPI::setMACRO2(0x2B, 0xF0000000, actor->getHaveStatusInfo().getAddDamage());
    }
}

THUMB void btl::BattleActorMacro::setMacroTarget(status::CharacterStatus* target, int actionIndex, int currentTarget)
{
    if (target == NULL) {
        return;
    }
    if (target->getCharacterType() == PLAYER) {
        TextAPI::setMACRO0(0x12, 0x50000000, target->getHaveStatusInfo().getPlayerIndex());
    }
    if (target->getCharacterType() == MONSTER) {
        status::MonsterStatus* monsterStatus = (status::MonsterStatus*)target;
        int monsterIndex = monsterStatus->getMonsterIndex();
        if (status::g_Monster.getMonsterCountDeadOrAlive(monsterIndex) == 1 && !Encount::getSingleton()->getMonsterCountName(monsterIndex)) {
            TextAPI::setMACRO0(0x12, 0x60000000, monsterIndex);
        }
        else {
            int sortIndex = monsterStatus->getSortIndexInGroup();
            TextAPI::setMACRO0(0x12, 0x60000000, monsterIndex, sortIndex);
        }
        if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU)) {
            int playerIndex = monsterStatus->getMosyasIndex();
            TextAPI::setMACRO0(0x12, 0x50000000, playerIndex, 1, -1);
        }
    }
    TextAPI::setMACRO0(0x2B, 0xF0000000, target->getHaveStatusInfo().getUseActionEffectValue());
}

THUMB void btl::BattleActorMacro::setAddMacro(status::UseActionParam& useActionParam, int currentTarget)
{
    status::UseActionMacro::setAddMacro(useActionParam.getActorCharacterStatus(), useActionParam.getTargetCharacterStatus(currentTarget), useActionParam.getActionIndex());
    setMacroActor(useActionParam.getActorCharacterStatus(), 0);
    setMacroTarget(useActionParam.getTargetCharacterStatus(currentTarget), 0, 0);
}
