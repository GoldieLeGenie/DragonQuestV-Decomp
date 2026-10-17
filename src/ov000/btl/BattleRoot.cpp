#pragma ipa file
#include "ov000/btl/BattleRoot.hpp"
#include "ov000/btl/BattleActorManager.hpp"
#include "ov000/btl/BattleMonsterMask.hpp"
#include "ov000/btl/BattleRound.hpp"
#include "ov000/btl/BattleTaskManager.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "ov018/menu/BattleMenu.hpp"
#include "main/btl/Encount.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/global/Global.hpp"
#include "main/global/GlobalGamePart.hpp"
#include "main/menu/StadiumData.hpp"
#include "main/object/GameMonster.hpp"
#include "main/status/BaseActionStatus.hpp"
#include "main/status/HaveAction.hpp"
#include "main/status/HaveBattleStatus.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/StatusChange.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/UseActionFlag.hpp"

inline bool StadiumData::isStadiumBattle() { return stadiumFlag_; }
inline int btl::Encount::getMonsterIndex(int group) { return monsterIndex_[group]; }
inline int btl::Encount::getMonsterCount(int group) { return monsterCount_[group]; }
inline void btl::Encount::setMonsterIndex(int group, int index) { monsterIndex_[group] = index; }
inline void btl::Encount::setMonsterCount(int group, int count) { monsterCount_[group] = count; }
inline void btl::RoundTask::setWaitFlag(bool flag) { waitFlag_ = flag; }
inline void btl::StadiumEndTask::setCount(int count) { messageCount_ = count; }
inline void btl::StadiumDrawTask::setCount(int count) { messageCount_ = count; }
inline void btl::StadiumResultTask::setCount(int count) { messageCount_ = count; }
inline void btl::BattleActorManager::setDisableEscapeFlag(int flag) { disableEscapeFlag_ = flag; }
inline void status::MenuStatus::setActorIndex(short actor) { actorIndex_ = actor; }
inline void status::BattleResult::setPlayerVictory(bool flag) { playerVictory_ = flag; }
inline int status::BattleResult::getDebugFirstAttack() { return debugFirstAttack_; }
inline void status::BattleResult::setDemolitionPartyTalk(bool flag) { demolitionPartyTalk_ = flag; }
inline void status::BattleResult::setBattleTurnCount(int count) { battleTurnCount_ = count; }

btl::BattleRound btl::battleRound_;
RandomTaskManager btl::taskManager_;

THUMB btl::BattleRoot::BattleRoot()
{
}

THUMB btl::BattleRoot::~BattleRoot()
{
}

THUMB btl::BattleRoot* btl::BattleRoot::getSingleton()
{
    static BattleRoot m_singleton;
    return &m_singleton;
}

THUMB void btl::BattleRoot::initialize()
{
    status::HaveAction::setBattleMode();
    setupBattle();
    unkfunc_0204afdc();
    executeFlag_ = true;
}

THUMB void btl::BattleRoot::terminate()
{
    cleanupBattle();
    switch (data_0211b27c.state_) {
    case FadeEffector::FADE_NONE:
        data_0211b27c.state_ = FadeEffector::FADE_OUT_BLACK;
        break;
    case FadeEffector::FADE_IN_BLACK:
        data_0211b27c.state_ = FadeEffector::FADE_OUT_WHITE;
        break;
    default:
        data_0211b27c.state_ = FadeEffector::FADE_OUT_BLACK;
        break;
    }
    data_0211b27c.count_ = 0;
    data_0211b27c.frames_ = 3;
    data_02101d14.unkfunc_020519a8(&data_0211b27c);
}

THUMB void btl::BattleRoot::execute()
{
    if (executeFlag_) {
        taskManager_.run();
        unkfunc_0204afdc();
    }
}

THUMB void btl::BattleRoot::draw()
{
}

THUMB void btl::BattleRoot::setupBattle()
{
    backupPartyStatus_ = (status::PartyStatus*)unkfunc_0204c5bc(&data_020fd24c, sizeof(status::PartyStatus), 0x20);
    BattleActorManager::getSingleton()->initialize();
    eventEncount_ = Encount::getSingleton()->encountData_.eventEncount_;
    int escapeDisable = Encount::getSingleton()->encountData_.escapeDisable_;
    BattleActorManager::getSingleton()->setDisableEscapeFlag(escapeDisable);
    setupMonster();
    taskManager_.registerTask(0, &encountTask_);
    taskManager_.registerTask(1, &statusTask_);
    taskManager_.registerTask(2, &firstAttackTask_);
    taskManager_.registerTask(3, &commandTask_);
    taskManager_.registerTask(4, &roundTask_);
    taskManager_.registerTask(5, &roundEndTask_);
    taskManager_.registerTask(6, &battleEndTask_);
    taskManager_.registerTask(7, &exitTask_);
    taskManager_.registerTask(8, &exitWaitTask_);
    taskManager_.registerTask(9, &partyReorderTask_);
    taskManager_.registerTask(10, &demolitionTask_);
    taskManager_.registerTask(13, &timeReverseTask_);
    taskManager_.registerTask(14, &timeReverseEndTask_);
    taskManager_.registerTask(15, &escapeTask_);
    taskManager_.registerTask(17, &firstReorderTask_);
    taskManager_.initialize();
    taskManager_.setNextTask(0);
    if (g_StadiumData.isStadiumBattle()) {
        taskManager_.registerTask(19, &stadiumEndTask_);
        taskManager_.registerTask(20, &stadiumDrawTask_);
        taskManager_.registerTask(21, &stadiumResultTask_);
        stadiumEndTask_.setCount(0);
        stadiumDrawTask_.setCount(0);
        stadiumResultTask_.setCount(0);
        roundTask_.setWaitFlag(false);
    }
    else {
        BattleMenuPlayerControl::getSingleton()->resetTargetGroup();
        BattleMenuPlayerControl::getSingleton()->allClear();
        BattleMenuPlayerControl::getSingleton()->activeChara_ = -1;
    }
    if (!g_StadiumData.isStadiumBattle()) {
        BattleMonsterMask::getSingleton()->setup();
    }
}

THUMB void btl::BattleRoot::cleanupBattle()
{
    cleanupMonster();
    status::PartyStatusUtility::recoveryBattleEnd();
    if (status::g_BattleResult.playerDemolition_) {
        if (status::g_BattleResult.isDisablePlayerDemolition()) {
            status::PartyStatusUtility::recoveryDisableDemolition();
            status::g_BattleResult.playerDemolitionMessage_ = true;
            status::g_BattleResult.setDisablePlayerDemolition(false);
            status::g_Party.getPlayerStatus(0).haveStatusInfo_.revival();
        }
        else if (status::g_Story.chapter_ == 1) {
            status::PartyStatusUtility::recovery();
        }
    }
    else {
        status::PartyStatusUtility::recoveryBattleEnd();
    }
    status::g_BattleResult.setDisablePlayerDemolition(false);
    unkfunc_0204c5c8(&data_020fd24c, backupPartyStatus_);
}

THUMB void btl::BattleRoot::setupMonster()
{
    store();
    status::StatusChange::StaticClear();
    status::g_Monster.clear();
    status::MonsterParty::initializeSortIndex();
    BattleMonsterDraw2::getSingleton().setup();
    if (!g_StadiumData.isStadiumBattle()) {
        int monsterIndex[4] = { 0, 0, 0, 0 };
        int monsterCount[4] = { 0, 0, 0, 0 };
        for (int i = 0; i < 4; i++) {
            monsterIndex[i] = Encount::getSingleton()->getMonsterIndex(i);
            monsterCount[i] = Encount::getSingleton()->getMonsterCount(i);
            for (int j = 0; j < monsterCount[i]; j++) {
                if (monsterIndex[i] != 0) {
                    int bookIndex = status::g_BattleResult.getMonsterBookIndex(monsterIndex[i]);
                    if (bookIndex != -1) {
                        status::g_BattleResult.setMonsterEncount(bookIndex, true);
                    }
                }
            }
        }
    }
    if (!eventEncount_) {
        int count = status::g_Monster.getCount();
        for (int i = 0; i < count; i++) {
            unsigned short hpMax = status::g_Monster.getMonsterStatus(i).haveStatusInfo_.getHpMax();
            unsigned short rate = UnkDssRand::rand(25) + 76;
            unsigned short hp = hpMax * rate / 100;
            if (hp == 0) {
                hp = 1;
            }
            status::g_Monster.getMonsterStatus(i).haveStatusInfo_.setHp(hp);
        }
    }
    {
        int count = status::g_Monster.getCount();
        for (int i = 0; i < count; i++) {
            if (status::g_Monster.getMonsterStatus(i).characterIndex_ == 0x36) {
                status::g_Monster.getMonsterStatus(i).haveStatusInfo_.setMp(3);
            }
        }
    }
    {
        int count = status::g_Monster.getCount();
        for (int i = 0; i < count; i++) {
            status::g_Monster.getMonsterStatus(i).setStartStatus();
        }
    }
    {
        status::g_Party.setBattleMode();
        int count = status::g_Party.getCount();
        for (int i = 0; i < count; i++) {
            int flag = status::PartyStatusUtility::noDamage_;
            status::g_Party.getPlayerStatus(i).haveStatusInfo_.noDamage_ = flag;
        }
    }
    status::g_Monster.setNoDamageEnable(status::PartyStatusUtility::noDamageForMonster_);
    int tile = Encount::getSingleton()->tileId_;
    status::HaveBattleStatus::eventFlag_ = eventEncount_;
    BattleActorManager::getSingleton()->setEventBattle(eventEncount_, tile);
    status::UseActionFlag::eventBattle_ = eventEncount_;
    status::BaseActionStatus::eventBattle_ = eventEncount_;
    status::PartyStatusUtility::startBattle();
    Encount::getSingleton()->encountData_.setupFirstAttack();
    BattleActorManager::getSingleton()->setFirstAttack(Encount::getSingleton()->getFirstAttack());
    if ((eventEncount_ || g_StadiumData.isStadiumBattle()) && status::g_BattleResult.getDebugFirstAttack() != 1) {
        BattleActorManager::getSingleton()->setFirstAttack(FirstAttackNone);
    }
    status::g_Party.battleExp_ = 0;
    status::g_Party.battleMonsterCount_ = 0;
    status::g_Party.battleGold_ = 0;
    status::g_BattleResult.setPlayerVictory(false);
    status::g_BattleResult.playerDemolition_ = false;
    status::g_BattleResult.setDemolitionPartyTalk(false);
    status::g_BattleResult.setBattleTurnCount(0);
    BattleActorManager::getSingleton()->execStartOfBattle();
}

THUMB void btl::BattleRoot::cleanupMonster()
{
    BattleActorManager::getSingleton()->execEndOfBattle();
    status::UseActionFlag::clear();
    status::g_BattleResult.setDisablePlayerDemolition(false);
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        status::g_Party.getPlayerStatus(i).haveStatusInfo_.noDamage_ = false;
    }
    BattleMonsterDraw2::getSingleton().cleanup();
    status::g_Monster.clear();
    GameMonster::clearGameMonsterData();
}

THUMB void btl::BattleRoot::store()
{
    dss::memcpy(backupPartyStatus_, &status::g_Party, sizeof(status::PartyStatus));
    dss::memcpy(&backupGlobalFlag_, &g_AreaFlag, sizeof(status::GameFlag));
    dss::memcpy(&backupAreaFlag_, &g_LocalFlag, sizeof(status::GameFlag));
    dss::memcpy(&backupLocalFlag_, &g_GlobalFlag, sizeof(status::GameFlag));
    dss::memcpy(&backupBattleResult_, &status::g_BattleResult, sizeof(status::BattleResult));
    for (int i = 0; i < 4; i++) {
        backupMonsterIndex_[i] = Encount::getSingleton()->monsterIndex_[i];
        backupMonsterCount_[i] = Encount::getSingleton()->monsterCount_[i];
    }
}

THUMB void btl::BattleRoot::restore()
{
    dss::memcpy(&status::g_Party, backupPartyStatus_, sizeof(status::PartyStatus));
    dss::memcpy(&g_AreaFlag, &backupGlobalFlag_, sizeof(status::GameFlag));
    dss::memcpy(&g_LocalFlag, &backupAreaFlag_, sizeof(status::GameFlag));
    dss::memcpy(&g_GlobalFlag, &backupLocalFlag_, sizeof(status::GameFlag));
    dss::memcpy(&status::g_BattleResult, &backupBattleResult_, sizeof(status::BattleResult));
    for (int i = 0; i < 4; i++) {
        Encount::getSingleton()->setMonsterIndex(i, backupMonsterIndex_[i]);
        Encount::getSingleton()->setMonsterCount(i, backupMonsterCount_[i]);
    }
}

THUMB bool btl::BattleRoot::isRoundEnd()
{
    if (BattleActorManager::getSingleton()->isBattleEnd(false) && status::g_BattleResult.playerDemolition_) {
        return false;
    }
    return taskManager_.checkTask(5) != 0;
}

THUMB bool btl::BattleRoot::isMenuEnd()
{
    if (taskManager_.checkTask(4) && taskManager_.getPreviousTask() == 3) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleRoot::isEncountMenuEnd()
{
    return taskManager_.getPreviousTask() == 2;
}

THUMB bool btl::BattleRoot::isBattleStart()
{
    return taskManager_.getPreviousTask() == 0;
}

THUMB void btl::BattleRoot::setBattleEnd()
{
    taskManager_.setNextTask(7);
}

THUMB bool btl::BattleRoot::isUseItem(int itemIndex)
{
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (status::g_Party.getPlayerStatus(i).haveBattleStatus_.getSelectCommand() == 3) {
            int useItemIndex = status::g_Party.getPlayerStatus(i).haveBattleStatus_.selectItemIndex_;
            if (itemIndex == useItemIndex) {
                status::g_Menu.setActorIndex(status::g_Party.getPlayerStatus(i).haveStatusInfo_.haveStatus_.playerIndex_);
                return true;
            }
        }
    }
    return false;
}
