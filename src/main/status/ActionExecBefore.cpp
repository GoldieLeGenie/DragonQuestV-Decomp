#include "main/status/ActionExecBefore.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/dss/UnkRandom.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int status::HaveStatusInfo::getDrawCtrlId() { return drawCtrlId_; }
inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }
inline void status::UseActionFlag::setWorkParam(int index, int param) { workParam_[index] = param; }
inline void status::UseActionMessage::setAddMessage(int index, int message) { addMessage_[index] = message; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline void status::UseActionParam::setActorCharacterStatus(CharacterStatus* info) { actorCharacterStatus_ = info; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline void status::UseActionParam::setTargetCharacterStatus(int index, CharacterStatus* info) { targetCharacterStatus_[index] = info; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline int status::UseActionParam::getPreActionIndex() { return preActionIndex_; }
inline int status::UseActionParam::getCurrentTargetIndex() { return currentTargetIndex_; }
inline void status::UseActionParam::setTargetCount(int count) { targetCount_ = count; }
inline int status::UseActionParam::getTargetCount() { return targetCount_; }
inline status::UseActionMessage& status::UseActionParam::getUseActionMessage(int index) { return message_[index]; }

THUMB bool status::ActionExecBefore::execBefore(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    if (actionIndex == 0xcc) {
        int work = UnkDssRand::rand(5);
        UseActionFlag::setWorkParam(0, work);
    }
    if (actionIndex == 0x18) {
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setKillMyself(true);
    }
    if (actionIndex == 0x3f && useActionParam->getActorCharacterStatus()->getCharacterType() == MONSTER) {
        int drawCtrlId = useActionParam->getActorCharacterStatus()->getHaveStatusInfo().getDrawCtrlId();
        btl::BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setTransOfEnd();
    }
    if (actionIndex == 0xb4) {
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setKillMyself(true);
    }
    if (actionIndex == 0x52) {
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setKillMyself(true);
    }
    if (useActionParam->getActorCharacterStatus() != NULL && !UseAction::isBaikiruto(useActionParam->getActionIndex())) {
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setBaikirutoDisable(true);
    }
    if (isDoubleAction(useActionParam->getActorCharacterStatus(), useActionParam->getActionIndex())) {
        useActionParam->setTargetCharacterStatus(1, useActionParam->getTargetCharacterStatus(0));
        useActionParam->setTargetCount(2);
    }
    if (actionIndex == 0x1b9) {
        UseActionFlag::setWorkParam(0, g_Monster.getMonsterCallIndex());
    }
    if (actionIndex == 0x1c3) {
        UseActionFlag::setWorkParam(0, g_Monster.getMonsterCallIndex());
    }
    if (actionIndex == 0x10c) {
        UseActionFlag::setWorkParam(0, g_Monster.getMonsterCallIndex());
    }
    if (actionIndex == 0x1ec && useActionParam->getActorCharacterStatus() != NULL) {
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setHp(0);
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().setExecuteMeganteRing(true);
        useActionParam->getActorCharacterStatus()->getHaveStatusInfo().clearHpInBattle();
    }
    if (actionIndex == 0x1c8) {
        int count = g_Party.getCarriageAliveCount();
        for (int i = 0; i < count; i++) {
            useActionParam->setTargetCharacterStatus(i, useActionParam->getTargetCharacterStatus(0));
        }
        useActionParam->setTargetCount(count);
    }
    if (actionIndex == 0x1bf) {
        int index = useActionParam->getTargetCount();
        useActionParam->getUseActionMessage(index - 1).setAddMessage(0, 0xc3c38);
    }
    return true;
}

THUMB bool status::ActionExecBefore::execBeforeOne(UseActionParam* useActionParam)
{
    int actionIndex = useActionParam->getActionIndex();
    CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (actionIndex == 0x1c8) {
        g_Party.setBattleMode();
        int count = g_Party.getCount();
        int index = 0;
        for (int i = 0; i < count; i++) {
            if (g_Party.isInsideCarriage(i) && !g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
                if (index == useActionParam->getCurrentTargetIndex()) {
                    useActionParam->setActorCharacterStatus(&g_Party.getPlayerStatus(i));
                    break;
                }
                index++;
            }
        }
    }
    if (actionIndex == 0x1e0) {
        if (useActionParam->getPreActionIndex() == 0x3f) {
            actor->getHaveStatusInfo().setActionDisable(true);
        }
        if (useActionParam->getPreActionIndex() == 0x18) {
            actor->getHaveStatusInfo().setActionDisable(true);
        }
        if (useActionParam->getPreActionIndex() == 0x52) {
            actor->getHaveStatusInfo().setActionDisable(true);
        }
    }
    if (actionIndex == 0x1e4 && useActionParam->getPreActionIndex() == 0xb4) {
        actor->getHaveStatusInfo().setActionDisable(true);
    }
    return true;
}
