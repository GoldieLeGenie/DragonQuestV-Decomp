#include "ov000/btl/BattleRound.hpp"
#include "ov000/btl/BattleActor.hpp"
#include "ov000/btl/BattleActorManager.hpp"
#include "ov000/btl/BattleRoundStart.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov000/status/MonsterStatus.hpp"
#include "main/menu/StadiumData.hpp"
#include "main/status/BaseActionStatus.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/UseActionFlag.hpp"

inline bool StadiumData::isStadiumBattle() { return stadiumFlag_; }
inline int status::HaveStatus::getPlayerIndex() const { return playerIndex_; }
inline int status::HaveStatusInfo::getPlayerIndex() const { return haveStatus_.getPlayerIndex(); }
inline ExecTaskManager2::ExecTaskManager2() { flag_.clear(); }
inline status::CharacterStatus* btl::BattleActor::getCharacterStatus() { return characterStatus_; }
inline btl::BattleActor* btl::BattleTurn::getBattleActor() { return battleActor_; }
inline bool btl::BattleTurn::isActionEnable() { return battleActor_->isActionEnable(); }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int status::PlayerStatus::getPlayerIndex() { return haveStatusInfo_.getPlayerIndex(); }
inline int status::MonsterStatus::getMonsterIndex() { return characterIndex_; }

THUMB btl::BattleRound::BattleRound()
{
}

inline btl::BattleTaskVenom::BattleTaskVenom() {}
inline btl::BattleTaskVenom::~BattleTaskVenom() {}
inline btl::BattleTaskVenom2::BattleTaskVenom2() {}
inline btl::BattleTaskVenom2::~BattleTaskVenom2() {}
inline btl::BattleTaskLifeRing::BattleTaskLifeRing() {}
inline btl::BattleTaskLifeRing::~BattleTaskLifeRing() {}
inline btl::BattleTaskMysteriousArmor::BattleTaskMysteriousArmor() {}
inline btl::BattleTaskMysteriousArmor::~BattleTaskMysteriousArmor() {}
inline btl::BattleTaskOracle::BattleTaskOracle() {}
inline btl::BattleTaskOracle::~BattleTaskOracle() {}

THUMB btl::BattleRound::~BattleRound()
{
}

THUMB void btl::BattleRound::initialize()
{
    BattleActorManager::getSingleton()->selectActor();
    BattleActorManager::getSingleton()->setActorOrder(false);
    BattleActorManager::getSingleton()->setActorAction();
    BattleActorManager::getSingleton()->setActorOrder(true);
    countBattleTurn_ = BattleActorManager::getSingleton()->getActorCount();
    for (int i = 0; i < countBattleTurn_; i++) {
        BattleActor* battleActor = BattleActorManager::getSingleton()->getBattleActor(i);
        battleTurn_[i].setBattleActor(battleActor);
    }
    currentBattleTurn_ = 0;
    BattleActorManager::getSingleton()->execStartOfRound();
    turnEndFlag_ = false;
    venomActionFlag_ = false;
    roundMode_ = RoundStart;
}

THUMB void btl::BattleRound::terminate()
{
    BattleActorManager::getSingleton()->execEndOfRound();
    BattleActorManager::getSingleton()->retireActor();
    status::PartyStatusUtility::execOfRoundInCarriage();
}

THUMB bool btl::BattleRound::execute()
{
    static int count;
    if (roundMode_ == RoundStart) {
        if (!g_BattleExecRoundStart.execute()) {
            roundMode_ = RoundExecute;
        }
    }
    else if (roundMode_ == RoundExecute) {
        battleTurn_[currentBattleTurn_].execute();
        if (isEnd()) {
            roundMode_ = RoundEnd;
        }
    }
    else if (roundMode_ == RoundEnd) {
        if (BattleActorManager::getSingleton()->isBattleEnd(false)) {
            roundMode_ = RoundAllEnd;
        }
        else {
            if (!roundEnd_.execute()) {
                roundMode_ = RoundAllEnd;
                count = 0;
            }
            count++;
        }
    }
    else if (roundMode_ == RoundAllEnd) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleRound::isEnd()
{
    turnEndFlag_ = false;
    if (battleTurn_[currentBattleTurn_].isEnd()) {
        turnEndFlag_ = true;
        for (int i = 0; i < countBattleTurn_; i++) {
            if (i != currentBattleTurn_ && battleTurn_[i].getBattleActor() != NULL) {
                if (battleTurn_[i].getBattleActor()->getCharacterStatus()->getHaveStatusInfo().isDeath()) {
                    battleTurn_[i].setBattleActor(NULL);
                }
            }
        }
        if (status::UseActionFlag::timeReverseFlag_) {
            return true;
        }
        if (status::BaseActionStatus::execCallFriend_) {
            status::BaseActionStatus::execCallFriend_ = false;
            int count = status::getCallMonsterCount();
            if (count != 0) {
                add(status::getCallMonsterStatus(0));
            }
        }
        if (status::BaseActionStatus::execCallKingSlime_) {
            status::BaseActionStatus::execCallKingSlime_ = false;
            int count = status::g_Monster.getCount();
            for (int i = 0; i < count; i++) {
                if (status::g_Monster.getMonsterStatus(i).getMonsterIndex() == 0x6B) {
                    add(&status::g_Monster.getMonsterStatus(i));
                    break;
                }
            }
        }
        if (execMeganteRing()) {
            currentBattleTurn_++;
            return false;
        }
        if (execRebirthStone()) {
            currentBattleTurn_++;
            return false;
        }
        if (BattleActorManager::getSingleton()->isBattleEnd(false)) {
            return true;
        }
        if (status::PartyStatusUtility::getAliveWithoutSpazzCountOutsideCarriagePlayerOnly() == 0) {
            return false;
        }
        if (g_StadiumData.isStadiumBattle() && status::g_Monster.getBattleCount() <= 1) {
            return true;
        }
        if (battleTurn_[currentBattleTurn_].getBattleActor() != NULL && battleTurn_[currentBattleTurn_].getBattleActor()->getCharacterStatus()->getHaveBattleStatus().isMultiAction()) {
            battleTurn_[currentBattleTurn_].getBattleActor()->getCharacterStatus()->getHaveBattleStatus().setMultiAction();
            battleTurn_[currentBattleTurn_].getBattleActor()->getCharacterStatus()->getHaveBattleStatus().multiExecCount_++;
            if (battleTurn_[currentBattleTurn_].getBattleActor()->getCharacterStatus()->getHaveBattleStatus().multiExecCount_ < 2) {
                if (battleTurn_[currentBattleTurn_].isActionEnable()) {
                    battleTurn_[currentBattleTurn_].reattack();
                    return false;
                }
            }
            else {
                battleTurn_[currentBattleTurn_].getBattleActor()->getCharacterStatus()->getHaveBattleStatus().multiExecCount_ = 0;
            }
        }
        while (true) {
            currentBattleTurn_++;
            if (currentBattleTurn_ >= countBattleTurn_) {
                return !setupVenomActor();
            }
            if (battleTurn_[currentBattleTurn_].getBattleActor() == NULL) {
                continue;
            }
            if (currentBattleTurn_ == countBattleTurn_ - 1) {
                battleTurn_[currentBattleTurn_].getBattleActor()->getCharacterStatus()->getHaveStatusInfo().setLastActor(true);
            }
            if (battleTurn_[currentBattleTurn_].getBattleActor()->getCharacterStatus()->getCharacterType() == PLAYER) {
                if (status::PartyStatus::isInsideCarriageForPlayerIndex(((status::PlayerStatus*)battleTurn_[currentBattleTurn_].getBattleActor()->getCharacterStatus())->getPlayerIndex())) {
                    continue;
                }
            }
            if (battleTurn_[currentBattleTurn_].isActionEnable()) {
                break;
            }
        }
    }
    return false;
}

THUMB int btl::BattleRound::isTurnEnd()
{
    return turnEndFlag_;
}

THUMB bool btl::BattleRound::setupVenomActor()
{
    if (venomActionFlag_) {
        return false;
    }
    venomActionFlag_ = true;
    BattleActorManager::getSingleton()->selectVenomActor();
    countBattleTurn_ = BattleActorManager::getSingleton()->getActorCount();
    for (int i = 0; i < countBattleTurn_; i++) {
        BattleActor* battleActor = BattleActorManager::getSingleton()->getBattleActor(i);
        battleTurn_[i].setBattleActor(battleActor);
    }
    currentBattleTurn_ = 0;
    return countBattleTurn_ != 0;
}

THUMB btl::BattleActor* btl::BattleRound::add(status::CharacterStatus* character)
{
    for (int i = countBattleTurn_ - 1; i > currentBattleTurn_; i--) {
        battleTurn_[i + 1] = battleTurn_[i];
    }
    BattleActor* actor = BattleActorManager::getSingleton()->add(character);
    battleTurn_[currentBattleTurn_ + 1].setBattleActor(actor);
    countBattleTurn_++;
    return actor;
}

THUMB bool btl::BattleRound::execMeganteRing()
{
    if (status::g_Monster.getAliveCount() == 0) {
        return false;
    }
    if (status::HaveStatusInfo::isGlbMeganteRing()) {
        status::g_Party.setPlayerMode();
        int count = status::g_Party.getCount();
        for (int i = 0; i < count; i++) {
            status::CharacterStatus* target = &status::g_Party.getPlayerStatus(i);
            if (target->getHaveStatusInfo().isMeganteRing()) {
                target->getHaveStatusInfo().setMeganteRing(false);
                target->getHaveStatusInfo().setStatusChangeRelease(false);
                BattleActor* actor = add(target);
                target->getHaveBattleStatus().setActionIndex(0x1EC);
                actor->meganteRing();
                return true;
            }
        }
    }
    return false;
}

THUMB bool btl::BattleRound::execRebirthStone()
{
    if (status::HaveStatusInfo::isGlbRebirthStone()) {
        status::g_Party.setBattleMode();
        int count = status::g_Party.getCount();
        for (int i = 0; i < count; i++) {
            status::CharacterStatus* target = &status::g_Party.getPlayerStatus(i);
            if (target->getHaveStatusInfo().isInvokeRebirthStone()) {
                target->getHaveStatusInfo().setInvokeRebirthStone(false);
                target->getHaveStatusInfo().setStatusChangeRelease(false);
                BattleActor* actor = add(target);
                target->getHaveStatusInfo().setHp(0);
                actor->rebirthStone();
                status::HaveStatusInfo& haveStatusInfo = target->getHaveStatusInfo();
                int count = haveStatusInfo.haveItem_.getCount();
                for (int i = 0; i < count; i++) {
                    if (haveStatusInfo.haveItem_.getItem(i) == 0xB8) {
                        haveStatusInfo.execThrow(i);
                        break;
                    }
                }
                return true;
            }
        }
    }
    return false;
}
