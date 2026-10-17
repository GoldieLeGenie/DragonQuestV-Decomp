#pragma ipa file
#include "ov000/btl/BattleActorManager.hpp"
#include "ov000/btl/AutoAction.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "main/btl/BattleScriptManager.hpp"
#include "main/btl/Encount.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/leveldata/MonsterData.hpp"
#include "main/menu/StadiumData.hpp"
#include "main/object/GameMonster.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"

inline bool StadiumData::isStadiumBattle() { return stadiumFlag_; }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline void status::HaveStatusInfo::allFlagClear()
{
    flag_.clear();
    flag2_.clear();
    testFlag_.clear();
}
inline int status::PartyStatus::isCarriage() { return carriage_; }
inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index) { return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned char dq5::level::MonsterData::getParty() { return party; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline void status::CharacterStatus::setNoneSound() { damageSound_ = NoSe; }
inline void status::CharacterStatus::clearTsukonSound() { damageSound_ = NoSe; }
inline int status::MonsterStatus::getMonsterIndex() { return characterIndex_; }
inline void status::MonsterStatus::setMonsterIndex(int index) { characterIndex_ = index; }
inline int status::MonsterStatus::getMosyasMonsterIndex() { return mosyasMonsterIndex_; }
inline int status::HaveBattleStatus::getActionIndex() { return actionIndex_; }
inline int status::HaveBattleStatus::getSelectCommandIndex() { return selectIndex_; }
inline void status::HaveStatusInfo::setAddDamage(int dm) { addDamage_ = dm; }
inline int status::HaveStatusInfo::getDrawCtrlId() { return drawCtrlId_; }
inline status::ActionDefence& status::HaveStatusInfo::getActionDefence() { return actionDefence_; }
inline void status::ActionDefence::setDisable(bool flag) { disable_ = flag; }
inline void status::BasePartyStatus::addBattleMonsterCount(int num) { battleMonsterCount_ += num; }
inline void status::BasePartyStatus::addBattleExp(int exp) { battleExp_ += exp; }
inline void status::BasePartyStatus::addBattleGold(int gold) { battleGold_ += gold; }
inline void status::BattleResult::setPlayerVictory(bool flag) { playerVictory_ = flag; }
inline void status::BattleResult::setPlayerDemolition(bool flag) { playerDemolition_ = flag; }
inline void status::BattleResult::setDemolitionPartyTalk(bool flag) { demolitionPartyTalk_ = flag; }
inline int status::BattleResult::getBattleTurnCount() { return battleTurnCount_; }
inline void status::BattleResult::setBattleTurnCount(int count) { battleTurnCount_ = count; }
inline int btl::EncountData::getTileLevel() { return tileLevel_; }
inline bool btl::EncountData::isTeamAddEnable() { return teamAddEnable_; }
inline int btl::Encount::getLevel() { return encountData_.getTileLevel(); }
inline bool btl::Encount::isFriendMonster() { return encountData_.isTeamAddEnable(); }
inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }
inline status::CharacterStatus* btl::BattleActor::getCharacterStatus() { return characterStatus_; }
inline int btl::BattleActor::getAgility() { return agility_; }
inline void btl::BattleActor::setAgility(int ag) { agility_ = ag; }
inline bool btl::BattleActorManager::isEscape() { return escape_; }
inline void btl::BattleActorManager::setDeathLog(int deathLog) { deathLog_ = deathLog; }
inline int btl::BattleActorManager::getDeathLog() { return deathLog_; }

inline void btl::AutoActionParam::clearFlag()
{
    for (int i = 0; i < 4; i++) {
        actionFlag_[i].clear();
    }
}

THUMB btl::BattleActorManager::BattleActorManager()
{
    escape_ = false;
    escapeSuccess_ = false;
    escapeCount_ = 0;
}

THUMB btl::BattleActorManager::~BattleActorManager()
{
}

THUMB btl::BattleActorManager* btl::BattleActorManager::getSingleton()
{
    static BattleActorManager battleActorManager2;
    return &battleActorManager2;
}

THUMB void btl::BattleActorManager::initialize()
{
    setDeathLog(0);
    status::g_Monster.setDropItem(0);
    status::g_Monster.setDropItemMonster(-1);
}

THUMB void btl::BattleActorManager::selectActor()
{
    actorCount_ = 0;
    selectActorPlayer();
    selectActorMonster();
    clearFirstAttack();
}

THUMB void btl::BattleActorManager::selectActorPlayer()
{
    if (g_StadiumData.isStadiumBattle()) {
        return;
    }
    if (getFirstAttack() == FirstAttackMonster || isEscape()) {
        return;
    }
    status::g_Party.setBattleMode();
    int playerCount = status::g_Party.getCarriageOutCount();
    bool minadein = false;
    for (int i = 0; i < playerCount; i++) {
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveBattleStatus().getSelectCommand() != status::HaveBattleStatus::UseAction) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveBattleStatus().getSelectCommandIndex() != 0x12) {
            continue;
        }
        minadein = true;
        actor_[actorCount_++].setup(&status::g_Party.getPlayerStatus(i));
    }
    if (!minadein) {
        for (int i = 0; i < playerCount; i++) {
            if (!status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
                status::g_Party.getPlayerStatus(i).print();
                actor_[actorCount_++].setup(&status::g_Party.getPlayerStatus(i));
            }
        }
    }
}

THUMB void btl::BattleActorManager::selectActorMonster()
{
    if (getFirstAttack() == FirstAttackPlayer && !isEscape()) {
        return;
    }
    if (eventFlag_) {
        int monsterCount = status::g_Monster.getCount();
        for (int i = 0; i < monsterCount; i++) {
            if (!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
                status::g_Monster.getMonsterStatus(i).print();
                actor_[actorCount_++].setup(&status::g_Monster.getMonsterStatus(i));
            }
        }
    }
    else {
        int monsterCount = status::g_Monster.getCount();
        for (int i = 0; i < monsterCount; i++) {
            if (!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
                status::g_Monster.getMonsterStatus(i).print();
                actor_[actorCount_++].setup(&status::g_Monster.getMonsterStatus(i));
            }
        }
    }
}

THUMB btl::BattleActor* btl::BattleActorManager::add(status::CharacterStatus* actor)
{
    int index = actorCount_++;
    actor_[index].setup(actor);
    return &actor_[index];
}

THUMB void btl::BattleActorManager::selectVenomActor()
{
    actorCount_ = 0;
    if (!g_StadiumData.isStadiumBattle()) {
        status::g_Party.setBattleMode();
        int playerCount = status::g_Party.getCarriageOutCount();
        for (int i = 0; i < playerCount; i++) {
            if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
                continue;
            }
            if (!status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
                continue;
            }
            status::g_Party.getPlayerStatus(i).getHaveBattleStatus().clearSelectCommand();
            status::g_Party.getPlayerStatus(i).getHaveBattleStatus().setActionIndex(0x1DE);
            status::g_Party.getPlayerStatus(i).getHaveStatusInfo().setStatusChangeRelease(false);
            status::g_Party.getPlayerStatus(i).getHaveStatusInfo().setVenomAction(true);
            actor_[actorCount_++].setup(&status::g_Party.getPlayerStatus(i));
        }
    }
    int monsterCount = status::g_Monster.getCount();
    for (int i = 0; i < monsterCount; i++) {
        if (status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        if (!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
            continue;
        }
        status::g_Monster.getMonsterStatus(i).getHaveBattleStatus().clearSelectCommand();
        status::g_Monster.getMonsterStatus(i).getHaveBattleStatus().setActionIndex(0x1DE);
        status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().setStatusChangeRelease(false);
        status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().setVenomAction(true);
        actor_[actorCount_++].setup(&status::g_Monster.getMonsterStatus(i));
    }
}

THUMB void btl::BattleActorManager::setActorOrder(bool defence)
{
    if (defence) {
        for (int i = 0; i < actorCount_; i++) {
            switch (actor_[i].getCharacterStatus()->getHaveBattleStatus().getActionIndex()) {
            case 0x49:
            case 0x4A:
                if (!actor_[i].getCharacterStatus()->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN)) {
                    actor_[i].setAgility(100000);
                }
                break;
            }
        }
    }
    for (int j = 0; j < actorCount_ - 1; j++) {
        for (int i = 0; i < actorCount_ - 1; i++) {
            if (actor_[i].getAgility() < actor_[i + 1].getAgility()) {
                dss::swap(&actor_[i], &actor_[i + 1]);
            }
        }
    }
}

THUMB void btl::BattleActorManager::setActorAction()
{
    for (int i = 0; i < actorCount_; i++) {
        actor_[i].setActionTargetOnRound();
    }
}

THUMB int btl::BattleActorManager::getActorCount()
{
    return actorCount_;
}

THUMB btl::BattleActor* btl::BattleActorManager::getBattleActor(int index)
{
    return &actor_[index];
}

THUMB void btl::BattleActorManager::execStartOfRound()
{
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        status::g_Party.getPlayerStatus(i).getHaveStatusInfo().setUseActionEffectValue(0);
        status::g_Party.getPlayerStatus(i).getHaveStatusInfo().setAddDamage(0);
        status::g_Party.getPlayerStatus(i).getHaveStatusInfo().setStatusChangeRelease(false);
        status::g_Party.getPlayerStatus(i).getHaveBattleStatus().execStartOfRound();
        status::g_Party.getPlayerStatus(i).setNoneAnimation();
        status::g_Party.getPlayerStatus(i).setNoneSound();
        status::g_Party.getPlayerStatus(i).execStartOfRound();
    }
    for (int i = 0; i < status::g_Monster.getCount(); i++) {
        status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().setUseActionEffectValue(0);
        status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().setAddDamage(0);
        status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().setStatusChangeRelease(false);
        status::g_Monster.getMonsterStatus(i).getHaveBattleStatus().execStartOfRound();
        status::g_Monster.getMonsterStatus(i).setNoneAnimation();
        status::g_Monster.getMonsterStatus(i).setNoneSound();
        status::g_Monster.getMonsterStatus(i).execStartOfRound();
    }
}

THUMB void btl::BattleActorManager::execEndOfRound()
{
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().execEndOfRound();
        status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().printAll();
        status::g_Party.getPlayerStatus(i).getHaveBattleStatus().clearGroupControl();
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_TAMEKEI)) {
            status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().setCount(dq5::level::ActionParam::ACTIONTYPE_TAMEKEI, 1);
        }
    }
    status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getStatusChange().execEndOfRoundForAll();
    for (int i = 0; i < status::g_Monster.getCount(); i++) {
        status::CharacterStatus* target = &status::g_Monster.getMonsterStatus(i);
        status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getStatusChange().execEndOfRound();
        status::g_Monster.getMonsterStatus(i).getHaveBattleStatus().clearGroupControl();
        status::g_Monster.getMonsterStatus(i).naturalRecovery();
        if (status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_TAMEKEI)) {
            status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getStatusChange().setCount(dq5::level::ActionParam::ACTIONTYPE_TAMEKEI, 1);
        }
        if (target->getHaveStatusInfo().getStatusChange().isRelease() == dq5::level::ActionParam::ACTIONTYPE_DEFENCE) {
            int drawCtrlId = target->getHaveStatusInfo().getDrawCtrlId();
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0x10);
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setNextAnimationIndex(0);
        }
    }
    int turn = status::g_BattleResult.getBattleTurnCount();
    status::g_BattleResult.setBattleTurnCount(turn + 1);
    escape_ = false;
    escapeSuccess_ = false;
}

THUMB void btl::BattleActorManager::execEndOfTurn()
{
    int count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        status::MonsterStatus* target = &status::g_Monster.getMonsterStatus(i);
        if (target->getHaveStatusInfo().isDeathFlag()) {
            if (target->getMonsterIndex() == 0xE8) {
                target->setMonsterIndex(0xE9);
                target->getHaveStatusInfo().setupMonster(0xE9);
                target->getHaveBattleStatus().setup(MONSTER, 0, 0xE9);
                target->getHaveStatusInfo().setDeathFlag(false);
                target->getHaveStatusInfo().setDeathLessly(true);
                continue;
            }
            if (target->getMonsterIndex() == 0xE9) {
                target->setMonsterIndex(0xEA);
                target->getHaveStatusInfo().setupMonster(0xEA);
                target->getHaveBattleStatus().setup(MONSTER, 0, 0xEA);
                target->getHaveStatusInfo().setDeathFlag(false);
                target->getHaveStatusInfo().setDeathLessly(false);
                continue;
            }
            if (status::g_Monster.getMonsterStatus(i).getMonsterIndex() == 0xE7) {
                int monsterCount = status::g_Monster.getCount();
                for (int j = 0; j < monsterCount; j++) {
                    status::g_Monster.getMonsterStatus(j).getHaveStatusInfo().addHp(-1023);
                }
                break;
            }
            target->getHaveStatusInfo().setDeathFlag(false);
            int drawCtrlId = target->getHaveStatusInfo().getDrawCtrlId();
            if (drawCtrlId != -1) {
                BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0x21);
                BattleMonsterDraw2::getSingleton().delBattleArray(drawCtrlId);
                BattleMonsterDraw2::getSingleton().cleanup(drawCtrlId);
                target->getHaveStatusInfo().setDrawCtrlId(-1);
                target->getHaveStatusInfo().setDrawCtrlId(-1);
            }
            if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU)) {
                GameMonster::cleanupTexture(target->getMosyasMonsterIndex());
                target->getHaveStatusInfo().getStatusChange().release(dq5::level::ActionParam::ACTIONTYPE_MOSYASU);
                target->setMosyasRelease();
            }
            if (target->getHaveStatusInfo().isCloseDoor()) {
                target->getHaveStatusInfo().setCloseDoor(false);
                target->getHaveStatusInfo().getStatusChange().release(dq5::level::ActionParam::ACTIONTYPE_CLOSEDOOR);
            }
            if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DEFENCE)) {
                target->getHaveStatusInfo().getStatusChange().release(dq5::level::ActionParam::ACTIONTYPE_DEFENCE);
                int drawCtrlId = target->getHaveStatusInfo().getDrawCtrlId();
                if (drawCtrlId != -1) {
                    BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0x10);
                    BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setNextAnimationIndex(0);
                }
            }
            status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getStatusChange().clear();
        }
        if (target->getHaveStatusInfo().isCloseDoor() && !target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_CLOSEDOOR)) {
            target->getHaveStatusInfo().setCloseDoor(false);
        }
        target->getHaveStatusInfo().setCurse1(false);
        target->getHaveStatusInfo().setCurse2(false);
        target->getHaveStatusInfo().setMagicDisable(false);
        target->getHaveStatusInfo().setActionDisable(false);
        target->getHaveStatusInfo().setMahokantaCounter(false);
        target->getHaveStatusInfo().setMagicDisable(false);
        target->getHaveStatusInfo().setMpFailure(false);
        target->getHaveStatusInfo().setSleepTurn(false);
        target->getHaveStatusInfo().setAddEffectDamage(false);
        target->getHaveStatusInfo().setAddDamage(0);
        target->getHaveStatusInfo().setAddEffectSleep(false);
        target->getHaveStatusInfo().setVenomAction(false);
        target->getHaveStatusInfo().setRebirthFailed(false);
        target->clearEscapeAnimation();
        target->clearRebirthAnimation();
        target->clearDeathAnimation();
        target->clearDisappearAnimation();
        target->clearDamageAnimation();
        target->setNoneSound();
        target->clearTsukonSound();
        target->clearAddDamageAnimation();
    }
    status::g_Party.setBattleMode();
    count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        status::CharacterStatus* target = &status::g_Party.getPlayerStatus(i);
        if (target->getHaveStatusInfo().isDeathFlag()) {
            target->getHaveStatusInfo().allFlagClear();
            target->getHaveStatusInfo().getStatusChange().clear();
        }
        target->getHaveStatusInfo().setCurse1(false);
        target->getHaveStatusInfo().setCurse2(false);
        target->getHaveStatusInfo().setMagicDisable(false);
        target->getHaveStatusInfo().setActionDisable(false);
        target->getHaveStatusInfo().setMahokantaCounter(false);
        target->getHaveStatusInfo().setSleepAttack(false);
        target->getHaveStatusInfo().setMagicDisable(false);
        target->getHaveStatusInfo().setMpFailure(false);
        target->getHaveStatusInfo().setSleepTurn(false);
        target->getHaveStatusInfo().setCounterDamage(false);
        target->getHaveStatusInfo().setAddDamage(0);
        target->getHaveStatusInfo().setAddEffectSleep(false);
        target->getHaveStatusInfo().setMultiAttack(false);
        target->getHaveStatusInfo().setVenomAction(false);
        target->getHaveStatusInfo().setRebirthFailed(false);
        target->setNoneSound();
        target->clearTsukonSound();
    }
}

THUMB void btl::BattleActorManager::retireActor()
{
    int monsterCount = status::g_Monster.getCount();
    if (status::g_Monster.getBattleCount() == 1) {
        checkDeathMonster();
        return;
    }
    if (status::g_Monster.getBattleCount() != 0) {
        checkDeathMonster();
        return;
    }
    execMonsterDeathForItem();
    checkDeathMonster();
    int monsterCtrlId[MONSTER_MAX];
    for (int i = 0; i < MONSTER_MAX; i++) {
        monsterCtrlId[i] = -1;
    }
    for (int i = 0; i < monsterCount; i++) {
        monsterCtrlId[i] = status::g_Monster.getCtrlId(i);
    }
    for (int i = 0; i < monsterCount; i++) {
        if (monsterCtrlId[i] != -1) {
            status::g_Monster.del(monsterCtrlId[i]);
        }
    }
}

THUMB void btl::BattleActorManager::checkDeathMonster()
{
    short deathFlag_ = 0;
    for (int i = 0; i < status::g_Monster.getCount(); i++) {
        if (!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        int ctrlId = 1 << status::g_Monster.getCtrlId(i);
        deathFlag_ |= ctrlId;
        if (getDeathLog() & ctrlId) {
            continue;
        }
        if (status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isEscapeFlag()) {
            addMonsterEscapeCount(1);
        }
        else if (status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDisappearFlag()) {
            addMonsterDisappearCount(1);
        }
        else if (status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
            if (!status::g_Monster.getMonsterStatus(i).isTakeUpMonsterDrop()) {
                addMonsterDeathCount(1);
                execMonsterDeath(i);
                status::g_Monster.getMonsterStatus(i).setTakeUpMonsterDrop(true);
            }
            int oldIndex = winningStatus_ & INDEX_MASK;
            switch (winningStatus_ & FLAG_MASK) {
            case DEATH_NUMBERS:
                if (oldIndex != status::g_Monster.getMonsterIndex(i)) {
                    winningStatus_ = status::g_Monster.getMonsterIndex(i) | DEATH_MULTIPLE;
                }
                break;
            case DEATH_MULTIPLE:
                break;
            case DEATH_SINGLE:
                if (oldIndex != status::g_Monster.getMonsterIndex(i)) {
                    winningStatus_ = status::g_Monster.getMonsterIndex(i) | DEATH_MULTIPLE;
                }
                else {
                    winningStatus_ = status::g_Monster.getMonsterIndex(i) | DEATH_NUMBERS;
                }
                break;
            default:
                winningStatus_ = status::g_Monster.getMonsterIndex(i) | DEATH_SINGLE;
                break;
            }
        }
    }
    setDeathLog(deathFlag_);
    if (status::isCallMonster()) {
        clearDeadMonster(true);
        status::setCallMonster(false);
    }
}

THUMB void btl::BattleActorManager::clearDeadMonster(bool all)
{
    int monsterCtrlId[MONSTER_MAX] = { -1 };
    for (int i = 0; i < MONSTER_MAX; i++) {
        monsterCtrlId[i] = -1;
    }
    int monsterCount = status::g_Monster.getCount();
    for (int i = 0; i < MONSTER_MAX; i++) {
        monsterCtrlId[i] = -1;
    }
    for (int i = 0; i < monsterCount; i++) {
        if (!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        monsterCtrlId[i] = status::g_Monster.getCtrlId(i);
        if (!all && !status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isEscapeFlag() && !status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDisappearFlag()) {
            monsterCtrlId[i] = -1;
        }
        if (status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isEscapeFlag() || status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDisappearFlag()) {
            status::g_Monster.getMonsterStatus(monsterCtrlId[i]).getHaveStatusInfo().setEscapeFlag(false);
            status::g_Monster.getMonsterStatus(monsterCtrlId[i]).getHaveStatusInfo().setDisappearFlag(false);
        }
    }
    for (int i = 0; i < monsterCount; i++) {
        if (monsterCtrlId[i] != -1) {
            status::g_Monster.del(monsterCtrlId[i]);
            if (getDeathLog() & (1 << monsterCtrlId[i])) {
                deathLog_ ^= (1 << monsterCtrlId[i]);
            }
        }
    }
}

THUMB bool btl::BattleActorManager::isAddMonster()
{
    if (!status::g_Party.isCarriage()) {
        return false;
    }
    if (!g_AreaFlag.check(0x8A)) {
        return false;
    }
    if (!Encount::getSingleton()->isFriendMonster()) {
        return false;
    }
    if (status::PlayerDataAll::getFriendMonsterCountWithoutEventMonster() >= 0x4C) {
        return false;
    }
    {
        int playerLevel = status::PartyStatusUtility::getPlayerMaxLevel();
        int tileLevel = Encount::getSingleton()->getLevel();
        if (playerLevel < tileLevel - 7) {
            return false;
        }
    }
    int monsterIndex = status::g_Monster.getPartyMonster();
    if (monsterIndex == 0) {
        return false;
    }
    int friendCount = status::PlayerDataAll::getFriendMonsterCountInMonster(dq5::level::MonsterData::getRecord(monsterIndex)->getParty());
    if (status::g_Monster.isAddParty(friendCount)) {
        return true;
    }
    return false;
}

THUMB void btl::BattleActorManager::execStartOfBattle()
{
    status::g_Party.setMemberShiftMode();
    int count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        status::g_Party.getPlayerStatus(i).getHaveStatusInfo().execStartOfBattle();
    }
    count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().execStartOfBattle();
    }
    for (int i = 0; i < count; i++) {
        if (status::g_Monster.getMonsterStatus(i).getMonsterIndex() == 0xE8) {
            status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().setDeathLessly(true);
        }
    }
    monsterDeathCount_ = 0;
    monsterEscapeCount_ = 0;
    monsterDisappearCount_ = 0;
    winningStatus_ = 0;
}

THUMB void btl::BattleActorManager::execEndOfBattle()
{
    status::g_Party.setMemberShiftMode();
    int count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        status::g_Party.getPlayerStatus(i).getHaveBattleStatus().changeMonsterReverse();
        status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().execEndOfBattle();
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().clear();
        }
        status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getActionDefence().setDisable(false);
        status::g_Party.getPlayerStatus(i).getHaveStatusInfo().clearDefenceChange();
        status::g_Party.getPlayerStatus(i).getHaveStatusInfo().clearAgilityChange();
    }
    count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        status::MonsterStatus* target = &status::g_Monster.getMonsterStatus(i);
        if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU)) {
            int monsterIndex = target->getMosyasMonsterIndex();
            GameMonster::cleanupTexture(monsterIndex);
            target->getHaveStatusInfo().getStatusChange().release(dq5::level::ActionParam::ACTIONTYPE_MOSYASU);
            target->setMosyasRelease();
        }
        if (status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
            status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getStatusChange().clear();
        }
    }
    AutoActionParam::clearFlag();
}

THUMB bool btl::BattleActorManager::isBattleEnd(int playerDemolitionFlag)
{
    if (status::PartyStatusUtility::isDemolition() || playerDemolitionFlag) {
        status::g_BattleResult.setPlayerDemolition(true);
        status::g_BattleResult.setDemolitionPartyTalk(true);
        status::g_BattleResult.setPlayerVictory(false);
        gBattleScriptManager.checkScriptBattleResult();
        return true;
    }
    int monsterCount = 0;
    for (int i = 0; i < status::g_Monster.getCount(); i++) {
        if (status::g_Monster.getMonsterStatus(i).isBattleEnable()) {
            monsterCount++;
        }
        if (status::g_Monster.getMonsterStatus(i).getMonsterIndex() == 0xE7 && status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
            monsterCount = 0;
            break;
        }
    }
    if (monsterCount == 0) {
        status::g_BattleResult.setPlayerDemolition(false);
        status::g_BattleResult.setDemolitionPartyTalk(false);
        status::g_BattleResult.setPlayerVictory(true);
        gBattleScriptManager.checkScriptBattleResult();
        return true;
    }
    return false;
}

THUMB void btl::BattleActorManager::execMonsterDeath(int index)
{
    status::g_Party.addBattleMonsterCount(1);
    status::MonsterStatus& monsterStatus = status::g_Monster.getMonsterStatus(index);
    int exp = monsterStatus.getHaveStatusInfo().getExp();
    status::g_Party.addBattleExp(exp);
    int gold = monsterStatus.getHaveStatusInfo().getGold();
    status::g_Party.addBattleGold(gold);
    if (monsterStatus.getHaveStatusInfo().isEscapeFlag() == true) {
        return;
    }
    if (monsterStatus.getHaveStatusInfo().isDisappearFlag() == true) {
        return;
    }
    int bookIndex = status::g_BattleResult.getMonsterBookIndex(monsterStatus.getMonsterIndex());
    if (bookIndex != -1) {
        status::g_BattleResult.addMonsterCount(bookIndex);
        status::g_BattleResult.regenesisMonsterLevel(bookIndex, status::PartyStatusUtility::getMaxLevel());
    }
}

THUMB void btl::BattleActorManager::execMonsterDeathForItem()
{
    int bookIndex = status::g_BattleResult.getMonsterBookIndex(status::g_Monster.getDropItemMonster());
    if (status::g_Monster.getDropItem() && bookIndex != -1) {
        status::g_BattleResult.addMonsterItemCount(bookIndex);
    }
}

THUMB void btl::BattleActorManager::setFirstAttack(FirstAttack atk)
{
    firstAttack_ = atk;
}

THUMB btl::FirstAttack btl::BattleActorManager::getFirstAttack()
{
    return firstAttack_;
}

THUMB void btl::BattleActorManager::clearFirstAttack()
{
    firstAttack_ = FirstAttackNone;
}

THUMB void btl::BattleActorManager::setEscape(bool flag)
{
    escape_ = flag;
    if (eventFlag_ && disableEscapeFlag_) {
        escapeSuccess_ = false;
        return;
    }
    if (getFirstAttack() == FirstAttackPlayer) {
        escapeSuccess_ = true;
        return;
    }
    {
        int count = status::g_Monster.getCount();
        int disableCount = 0;
        for (int i = 0; i < count; i++) {
            if (!status::g_Monster.getMonsterStatus(i).isActionEnable()) {
                disableCount++;
            }
        }
        if (disableCount == count) {
            escapeSuccess_ = true;
            return;
        }
    }
    int tileLevel = Encount::getSingleton()->getLevel();
    int playerLevel = status::PartyStatusUtility::getPlayerMaxLevel();
    switch (escapeCount_) {
    case 0:
        if (UnkDssRand::rand(2) == 0) {
            escapeSuccess_ = true;
        }
        break;
    case 1:
        if (UnkDssRand::rand(2) == 0) {
            escapeSuccess_ = true;
        }
        break;
    case 2:
        if (UnkDssRand::rand(4) != 3) {
            escapeSuccess_ = true;
        }
        break;
    case 3:
    default:
        if (UnkDssRand::rand(8) != 7) {
            escapeSuccess_ = true;
        }
        break;
    }
    if (playerLevel >= tileLevel + 5) {
        escapeSuccess_ = true;
    }
    escapeCount_++;
}

THUMB void btl::BattleActorManager::setEventBattle(int flag, int tile)
{
    eventFlag_ = flag;
    eventTile_ = tile;
    eventEnd_ = false;
}

THUMB void btl::BattleActorManager::addMonsterDeathCount(int count)
{
    monsterDeathCount_ += count;
}

THUMB int btl::BattleActorManager::getMonsterDeathCount()
{
    return monsterDeathCount_;
}

THUMB void btl::BattleActorManager::addMonsterEscapeCount(int count)
{
    monsterEscapeCount_ += count;
}

THUMB int btl::BattleActorManager::getMonsterEscapeCount()
{
    return monsterEscapeCount_;
}

THUMB void btl::BattleActorManager::addMonsterDisappearCount(int count)
{
    monsterDisappearCount_ += count;
}

THUMB int btl::BattleActorManager::getMonsterDisappearCount()
{
    return monsterDisappearCount_;
}
