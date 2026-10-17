#include "ov000/btl/BattleTask.hpp"
#include "ov000/btl/BattleActorManager.hpp"
#include "ov000/btl/BattleExecVictory.hpp"
#include "ov000/btl/BattleMessage.hpp"
#include "ov000/btl/BattleRoot.hpp"
#include "ov000/btl/BattleRound.hpp"
#include "ov000/btl/BattleTaskManager.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "ov018/menu/BattleMenu.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/btl/BattleExecLevelup.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/menu/StadiumData.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/text/TextAPI.hpp"

inline bool StadiumData::isStadiumBattle() { return stadiumFlag_; }
inline bool btl::BattleActorManager::isEscape() { return escape_; }
inline bool btl::BattleActorManager::isEscapeSuccess() { return escapeSuccess_; }
inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }
inline void BattleMenuSub_HISTORY::setUpdate(bool flag) { update_ = flag; }
inline unsigned char StadiumData::getBetArray() { return monsterArray_; }

THUMB void btl::EncountTask::initialize()
{
}

THUMB void btl::EncountTask::terminate()
{
}

THUMB void btl::EncountTask::execute()
{
    if (!g_BattleExecEncount.execute()) {
        taskManager_.setNextTask(2);
    }
}

THUMB void btl::FirstAttackTask::initialize()
{
}

THUMB void btl::FirstAttackTask::terminate()
{
}

THUMB void btl::FirstAttackTask::execute()
{
    if (!g_BattleExecFirstAttack.execute()) {
        taskManager_.setNextTask(1);
    }
}

THUMB void btl::StatusTask::initialize()
{
}

THUMB void btl::StatusTask::terminate()
{
}

THUMB void btl::StatusTask::execute()
{
    if (!g_BattleExecStatus.execute()) {
        if (status::PartyStatusUtility::getAliveCountOutsideCarriagePlayerOnly() == 0) {
            taskManager_.setNextTaskWithSleep(9);
            taskManager_.setNextTaskWithSleep(4);
            return;
        }
        if (BattleActorManager::getSingleton()->getFirstAttack() == FirstAttackMonster) {
            taskManager_.setNextTask(17);
            return;
        }
        BattleActorManager::getSingleton()->getFirstAttack();
        taskManager_.setNextTask(3);
    }
}

THUMB void btl::FirstReorderTask::initialize()
{
}

THUMB void btl::FirstReorderTask::terminate()
{
}

THUMB void btl::FirstReorderTask::execute()
{
    if (status::PartyStatusUtility::getAliveCountOutsideCarriagePlayerOnly() == 0) {
        taskManager_.setNextTaskWithSleep(9);
        return;
    }
    taskManager_.setNextTask(4);
}

THUMB void btl::CommandTask::initialize()
{
    if (!status::PartyStatusUtility::isPartyActionEnable()) {
        taskManager_.setNextTask(4);
        return;
    }
    if (status::PartyStatusUtility::isPapasBattle()) {
        taskManager_.setNextTask(4);
        return;
    }
    if (status::PartyStatusUtility::isPapasBattle2()) {
        if (!status::PartyStatusUtility::isAlivePapasOnly()) {
            taskManager_.setNextTask(4);
            return;
        }
        MenuAPI::openBattleMenu();
        return;
    }
    if (!g_StadiumData.isStadiumBattle()) {
        MenuAPI::openBattleMenu();
    }
}

THUMB void btl::CommandTask::terminate()
{
}

THUMB void btl::CommandTask::execute()
{
    if (status::PartyStatusUtility::getAliveWithoutSpazzCountOutsideCarriagePlayerOnly() == 0) {
        taskManager_.setNextTaskWithSleep(9);
        return;
    }
    if (!status::PartyStatusUtility::isPartyActionEnable()) {
        taskManager_.setNextTask(4);
        return;
    }
    if (MenuAPI::isFinishMenu()) {
        if (BattleActorManager::getSingleton()->isEscape()) {
            taskManager_.setNextTask(15);
        }
        else {
            taskManager_.setNextTask(4);
        }
    }
    if (g_StadiumData.isStadiumBattle()) {
        taskManager_.setNextTask(4);
    }
}

namespace btl {
    static int playerDemolitionFlag;
}

THUMB void btl::RoundTask::initialize()
{
    if (!g_StadiumData.isStadiumBattle() || !g_StadiumData.retire_) {
        battleRound_.initialize();
    }
    if (!g_StadiumData.isStadiumBattle()) {
        MenuAPI::openBattleStadiumAbort();
    }
    if (status::PartyStatusUtility::getAliveWithoutSpazzCountOutsideCarriagePlayerOnly() == 0) {
        taskManager_.setNextTaskWithSleep(9);
    }
    waitFlag_ = false;
}

THUMB void btl::RoundTask::terminate()
{
    if (!g_StadiumData.isStadiumBattle() || !g_StadiumData.retire_) {
        battleRound_.terminate();
    }
    MenuAPI::closeBattleStadiumAbort();
}

THUMB void btl::RoundTask::execute()
{
    if (g_StadiumData.isStadiumBattle()) {
        if (dss::g_Pad.edge() & 2) {
            waitFlag_ = true;
        }
        else {
            g_StadiumData.retire_ = false;
        }
    }
    playerDemolitionFlag = false;
    if (battleRound_.execute()) {
        playerDemolitionFlag = false;
        taskManager_.setNextTask(5);
    }
    if (battleRound_.isTurnEnd()) {
        if (status::UseActionFlag::timeReverseFlag_) {
            status::UseActionFlag::timeReverseFlag_ = false;
            taskManager_.setNextTask(13);
            return;
        }
        if (waitFlag_) {
            taskManager_.setNextTaskWithSleep(19);
            g_StadiumData.retire_ = true;
            waitFlag_ = false;
            return;
        }
        if (status::PartyStatusUtility::isDemolition()) {
            if (status::HaveStatusInfo::isGlbMeganteRing() && status::HaveStatusInfo::isGlbRebirthStone()) {
                return;
            }
            if (status::HaveStatusInfo::isGlbRebirthStone()) {
                return;
            }
            playerDemolitionFlag = true;
            taskManager_.setNextTask(5);
            return;
        }
        if (status::PartyStatusUtility::getAliveWithoutSpazzCountOutsideCarriagePlayerOnly() == 0) {
            if (status::HaveStatusInfo::isGlbMeganteRing()) {
                if (status::g_Monster.getAliveCount() != 0) {
                    return;
                }
                status::HaveStatusInfo::setGlbMeganteRing(false);
            }
            if (!status::HaveStatusInfo::isGlbRebirthStone()) {
                taskManager_.setNextTaskWithSleep(9);
            }
        }
    }
}

THUMB void btl::RoundEndTask::initialize()
{
}

THUMB void btl::RoundEndTask::terminate()
{
}

THUMB void btl::RoundEndTask::execute()
{
    if (g_StadiumData.isStadiumBattle()) {
        if (status::g_Monster.getBattleCount() <= 1) {
            taskManager_.setNextTask(21);
            return;
        }
        if (status::g_BattleResult.battleTurnCount_ >= 10) {
            taskManager_.setNextTask(20);
            return;
        }
    }
    if (BattleActorManager::getSingleton()->isBattleEnd(playerDemolitionFlag)) {
        gBattleMenuSub_HISTORY.setUpdate(false);
        if (status::g_BattleResult.playerDemolition_) {
            if (status::g_BattleResult.isDisablePlayerDemolition()) {
                taskManager_.setNextTask(7);
                return;
            }
            taskManager_.setNextTask(10);
            return;
        }
        taskManager_.setNextTask(6);
        if (g_StadiumData.isStadiumBattle()) {
            taskManager_.setNextTask(7);
        }
        return;
    }
    if (status::PartyStatusUtility::isPartyActionEnable()) {
        taskManager_.setNextTask(3);
        return;
    }
    taskManager_.setNextTask(4);
}

namespace btl {
    static int levelupBgmCount;
    static int endTaskIndex;
}

THUMB void btl::BattleEndTask::initialize()
{
    SoundManager::battleStop();
    SoundManager::playSe(0x199, 0);
    BattleActorManager::getSingleton()->execEndOfBattle();
    int escapeCount = BattleActorManager::getSingleton()->getMonsterEscapeCount();
    int deathCount = BattleActorManager::getSingleton()->getMonsterDeathCount();
    if (BattleActorManager::getSingleton()->getMonsterDisappearCount() != 0 && deathCount == 0) {
        endTaskIndex = 9;
        return;
    }
    if (escapeCount != 0 && deathCount == 0) {
        endTaskIndex = 0;
        return;
    }
    endTaskIndex = 1;
}

THUMB void btl::BattleEndTask::terminate()
{
    endTaskIndex = 0;
}

THUMB void btl::BattleEndTask::execute()
{
    if (endTaskIndex == 0) {
        if (!g_BattleExecMonsterEscape.execute()) {
            g_BattleExecMonsterEscape.terminate();
            taskManager_.setNextTask(7);
        }
    }
    if (endTaskIndex == 9) {
        if (!g_BattleExecMonsterDisappear.execute()) {
            g_BattleExecMonsterDisappear.terminate();
            taskManager_.setNextTask(7);
        }
    }
    if (endTaskIndex == 1) {
        if (!g_BattleExecDefeatMonster.execute()) {
            g_BattleExecDefeatMonster.terminate();
            endTaskIndex = 8;
            if (status::g_Party.getBattleExp() != 0) {
                status::PartyStatusUtility::reflectBattleExp();
                endTaskIndex = 2;
            }
            if (status::PartyStatusUtility::isPapasBattle()) {
                SoundManager::battleStop();
                endTaskIndex = 8;
            }
            if (status::PartyStatusUtility::isPapasBattle2() && !status::PartyStatusUtility::isAlivePapasOnly()) {
                SoundManager::battleStop();
                endTaskIndex = 8;
            }
        }
    }
    if (endTaskIndex == 2) {
        if (!g_BattleExecExp.execute()) {
            g_BattleExecExp.terminate();
            if (status::PartyStatusUtility::getLevelupPlayer() != -1) {
                endTaskIndex = 3;
                levelupBgmCount = 0;
                SoundManager::interrupt_ = true;
                SoundManager::playBgm(0x2A, 0);
            }
            else {
                endTaskIndex = 5;
            }
        }
    }
    if (endTaskIndex == 3) {
        if (++levelupBgmCount == 180) {
            endTaskIndex = 4;
        }
    }
    if (endTaskIndex == 4) {
        if (!g_BattleExecLevelup.execute()) {
            g_BattleExecLevelup.terminate();
            if (status::PartyStatusUtility::getLevelupPlayer() != -1) {
                endTaskIndex = 4;
            }
            else {
                endTaskIndex = 5;
            }
        }
    }
    if (endTaskIndex == 5) {
        if (!g_BattleExecGold.execute()) {
            g_BattleExecGold.terminate();
            endTaskIndex = 6;
        }
    }
    if (endTaskIndex == 6) {
        if (status::g_Monster.getDropItem() != 0) {
            if (!g_BattleExecItem.execute()) {
                g_BattleExecItem.terminate();
                if (BattleActorManager::getSingleton()->isAddMonster()) {
                    endTaskIndex = 7;
                }
                else {
                    endTaskIndex = 8;
                }
            }
        }
        else {
            if (BattleActorManager::getSingleton()->isAddMonster()) {
                endTaskIndex = 7;
            }
            else {
                endTaskIndex = 8;
            }
        }
    }
    if (endTaskIndex == 7) {
        if (!g_BattleExecMonster.execute()) {
            g_BattleExecMonster.terminate();
            endTaskIndex = 8;
        }
    }
    if (endTaskIndex == 8) {
        endTaskIndex = 10;
        taskManager_.setNextTask(7);
    }
}

THUMB void btl::ExitTask::initialize()
{
}

THUMB void btl::ExitTask::terminate()
{
    if (status::g_BattleResult.playerVictory_) {
        g_Global.endBattle(false);
    }
    else if (status::g_BattleResult.playerDemolition_) {
        if (status::g_BattleResult.isDisablePlayerDemolition()) {
            g_Global.endBattle(false);
        }
        else {
            SoundManager::stopBgmForce(0);
            g_Global.endBattle(true);
        }
    }
    else {
        g_Global.endBattle(false);
    }
    SoundManager::finalFormBGM_ = false;
}

THUMB void btl::ExitTask::execute()
{
    taskManager_.setNextTask(8);
}

THUMB void btl::ExitWaitTask::initialize()
{
    BattleActorManager::getSingleton()->setEscape(false);
}

THUMB void btl::ExitWaitTask::terminate()
{
}

THUMB void btl::ExitWaitTask::execute()
{
}

THUMB void btl::PartyReorderTask::initialize()
{
}

THUMB void btl::PartyReorderTask::terminate()
{
}

THUMB void btl::PartyReorderTask::execute()
{
    if (!g_BattleExecReorder.execute()) {
        taskManager_.wakeup();
        if (taskManager_.getCurrentTask() == 3) {
            MenuAPI::openBattleMenu();
        }
    }
}

THUMB void btl::DemolitionTask::initialize()
{
    SoundManager::battleStop();
}

THUMB void btl::DemolitionTask::terminate()
{
}

THUMB void btl::DemolitionTask::execute()
{
    if (!g_BattleExecDemolition.execute()) {
        g_BattleExecDemolition.terminate();
        taskManager_.setNextTask(7);
    }
}

namespace btl {
    static int battleBgm;
}

THUMB void btl::TimeReverseTask::initialize()
{
    battleBgm = SoundManager::bgmIndex_;
    SoundManager::battleStop();
    int count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        int drawCtrlId = status::g_Monster.getMonsterStatus(i).haveStatusInfo_.drawCtrlId_;
        if (drawCtrlId != -1) {
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 31);
        }
    }
    counter_ = 0;
}

THUMB void btl::TimeReverseTask::terminate()
{
    status::g_Monster.clear();
    SoundManager::battlePlay(battleBgm);
}

THUMB void btl::TimeReverseTask::execute()
{
    if (++counter_ > 30) {
        taskManager_.setNextTask(14);
    }
}

THUMB void btl::TimeReverseEndTask::initialize()
{
}

THUMB void btl::TimeReverseEndTask::terminate()
{
    BattleRoot::getSingleton()->cleanupMonster();
    BattleRoot::getSingleton()->restore();
    BattleRoot::getSingleton()->setupMonster();
    BattleActorManager::getSingleton()->initialize();
}

THUMB void btl::TimeReverseEndTask::execute()
{
    taskManager_.setNextTask(0);
}

THUMB void btl::EscapeTask::initialize()
{
}

THUMB void btl::EscapeTask::terminate()
{
}

THUMB void btl::EscapeTask::execute()
{
    if (!g_BattleExecEscape.execute()) {
        if (BattleActorManager::getSingleton()->isEscapeSuccess()) {
            taskManager_.setNextTask(7);
            return;
        }
        taskManager_.setNextTask(4);
    }
}

THUMB void btl::StadiumEndTask::initialize()
{
}

THUMB void btl::StadiumEndTask::terminate()
{
}

THUMB void btl::StadiumEndTask::execute()
{
    if (messageCount_ == 0) {
        if (g_StadiumData.monsterDeath_) {
            BattleMessage::openMessage();
            BattleMessage::setMessageNoSeqNum(0xC8F04, 0, 0, 0, 0, 0, 0, 0);
            messageCount_ += 3;
        }
        else {
            gTownMenu_MESSAGE.openMessageForBATTLE();
            gTownMenu_MESSAGE.addMessage(0xC8EFA);
            gTownMenu_MESSAGE.setMessageCursor(false);
            gTownMenu_MESSAGE.setYesNo(1);
            messageCount_++;
        }
    }
    else if (messageCount_ == 1) {
        if (gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            BattleMessage::openMessage();
            BattleMessage::setMessageNoSeqNum(0xC8EFD, 0, 0, 0, 0, 0, 0, 0);
            messageCount_++;
            messageCount_++;
        }
        else if (gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            BattleMessage::openMessage();
            BattleMessage::setMessage(0xC8F01, 0, 0, 0);
            messageCount_++;
        }
    }
    else if (messageCount_ == 2) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == menu::MenuBase::MENUBASE_STAT_OK || stat == menu::MenuBase::MENUBASE_STAT_CANCEL || BattleAutoFeed::isEndMessage()) {
            gTownMenu_MESSAGE.close();
            taskManager_.wakeup();
            taskManager_.setNextTask(taskManager_.getCurrentTask());
            messageCount_ = 0;
            return;
        }
    }
    else if (messageCount_ == 3) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == menu::MenuBase::MENUBASE_STAT_OK || stat == menu::MenuBase::MENUBASE_STAT_CANCEL || BattleAutoFeed::isEndMessage()) {
            gTownMenu_MESSAGE.close();
            g_StadiumData.result_ = 4;
            battleRound_.terminate();
            taskManager_.wakeup();
            taskManager_.setNextTask(7);
            return;
        }
    }
    taskManager_.setNextTask(19);
}

THUMB void btl::StadiumDrawTask::initialize()
{
}

THUMB void btl::StadiumDrawTask::terminate()
{
}

THUMB void btl::StadiumDrawTask::execute()
{
    if (messageCount_ == 0) {
        bool death = true;
        int number = g_StadiumData.getBetArray();
        for (int i = 0; i < status::g_Monster.getCount(); i++) {
            if (number == status::g_Monster.getMonsterStatus(i).characterGroup_ && status::g_Monster.getMonsterStatus(i).isBattleEnable()) {
                death = false;
            }
        }
        int leader = 0;
        status::g_Party.setBattleMode();
        for (int i = 0; i < status::g_Party.getCount(); i++) {
            if (!status::g_Party.getPlayerStatus(i).haveStatusInfo_.isDeath()) {
                leader = status::g_Party.getPlayerIndex(i);
                break;
            }
        }
        gTownMenu_MESSAGE.openMessageForBATTLE();
        TextAPI::setMACRO0(0xC, 0x50000000, leader);
        if (death) {
            g_StadiumData.result_ = 2;
            BattleMessage::openMessage();
            BattleMessage::setMessageNoSeqNum(0xC8F09, 0xC8F0A, 0, 0, 0, 0, 0, 0);
        }
        else {
            g_StadiumData.result_ = 3;
            BattleMessage::openMessage();
            BattleMessage::setMessageNoSeqNum(0xC8F09, 0xC8F0A, 0xC8F0B, 0, 0, 0, 0, 0);
        }
        messageCount_++;
    }
    else if (BattleAutoFeed::isEndMessage()) {
        taskManager_.setNextTask(7);
        return;
    }
    taskManager_.setNextTask(20);
}

THUMB void btl::StadiumResultTask::initialize()
{
}

THUMB void btl::StadiumResultTask::terminate()
{
}

THUMB void btl::StadiumResultTask::execute()
{
    if (messageCount_ == 0) {
        cmn::g_cmnSoundManager.initialize();
        bool death = true;
        int monsterID = g_StadiumData.monsterID_;
        int number = g_StadiumData.getBetArray();
        int symbol = g_StadiumData.monsterNumber_;
        for (int i = 0; i < status::g_Monster.getCount(); i++) {
            if (status::g_Monster.getMonsterStatus(i).isBattleEnable() && number == status::g_Monster.getMonsterStatus(i).characterGroup_) {
                death = false;
            }
        }
        gTownMenu_MESSAGE.openMessageForBATTLE();
        if (symbol != -1) {
            TextAPI::setMACRO0(3, 0x60000000, monsterID, symbol);
        }
        else {
            TextAPI::setMACRO0(3, 0x60000000, monsterID);
        }
        if (death) {
            g_StadiumData.result_ = 2;
            BattleMessage::openMessage();
            BattleMessage::setMessageNoSeqNum(0xC8EF6, 0, 0, 0, 0, 0, 0, 0);
        }
        else {
            BattleMessage::openMessage();
            BattleMessage::setMessageNoSeqNum(0xC8EEC, 0, 0, 0, 0, 0, 0, 0);
            g_StadiumData.result_ = 1;
        }
        messageCount_++;
    }
    else if (BattleAutoFeed::isEndMessage()) {
        taskManager_.setNextTask(7);
        return;
    }
    taskManager_.setNextTask(21);
}
