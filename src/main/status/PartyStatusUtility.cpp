#pragma ipa file
#include "main/status/PartyStatus.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StatusChange.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/CharacterInitData.hpp"
#include "main/leveldata/PlayerCarriage.hpp"
#include "main/cmn/GameManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"

inline dq5::level::CharacterInitData* dq5::level::CharacterInitData::getRecord(int index)
{
    return (CharacterInitData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatus::getPlayerKindIndex() const
{
    return playerKindIndex_;
}

inline bool status::HaveStatus::isBattleNpc() const
{
    return playerType_ == TYPE_BATTLENPC;
}

inline bool status::HaveStatus::isFriendMonster() const
{
    return playerType_ == TYPE_FRIENDMONSTER;
}

inline int status::HaveStatus::getLevel() const
{
    return level_;
}

inline int status::HaveStatusInfo::getPlayerIndex() const
{
    return haveStatus_.getPlayerIndex();
}

inline status::StatusChange& status::HaveStatusInfo::getStatusChange()
{
    return statusChange_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline status::HaveItem& status::HaveStatusInfo::getHaveItem()
{
    return haveItem_;
}

inline status::HaveAction& status::HaveStatusInfo::getHaveAction()
{
    return haveAction_;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline int Global::getMapNameId() { return nextMapNameId; }

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline bool status::PlayerStatus::isAlive() const { return !haveStatusInfo_.isDeath(); }
inline bool status::UseActionFlag::isDouble() { return doubleFlag_; }
inline char dq5::level::CharacterInitData::getDemolition() { return (byte_1 & 6) >> 1; }
inline unsigned short dq5::level::PlayerCarriage::getFloor() { return floor; }
inline char dq5::level::PlayerCarriage::getSorting() { return byte_1 & 1; }
inline char dq5::level::PlayerCarriage::getMostRelive() { return (byte_1 & 2) >> 1; }
inline dq5::level::PlayerCarriage* dq5::level::PlayerCarriage::getRecord(int index) { return (PlayerCarriage*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned int dq5::level::PlayerCarriage::getArraySize() { return binary_.getRecordCount(); }

inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

int status::PartyStatusUtility::noDamage_;
int status::PartyStatusUtility::noDamageForMonster_;
int status::PartyStatusUtility::separateFlag_;
int status::PartyStatusUtility::separatePlayer_[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int status::PartyStatusUtility::separateCarriageOutPlayer_[5] = { -1, -1, -1, -1, -1 };
int status::PartyStatusUtility::formerParty_[4] = { -1, -1, -1, -1 };

THUMB void status::PartyStatusUtility::setNoDamageEnable(int flag)
{
    noDamage_ = flag;
}

THUMB void status::PartyStatusUtility::setNoDamageEnableForMonster(bool flag)
{
    noDamageForMonster_ = flag;
}

THUMB bool status::PartyStatusUtility::isExecMinadein()
{
    int playerCount = 0;
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.isInsideCarriage(i) && isMinadeinEnable(&g_Party.getPlayerStatus(i))) {
            playerCount++;
        }
    }
    if (playerCount == 4) {
        return true;
    }
    return false;
}

THUMB bool status::PartyStatusUtility::isMinadeinEnable(PlayerStatus* player)
{
    if (player->getHaveStatusInfo().isDeath()) {
        return false;
    }
    if (player->getHaveStatusInfo().getMp() < 10) {
        return false;
    }
    StatusChange& statusChange = player->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
        return false;
    }
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
        return false;
    }
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOTON)) {
        return false;
    }
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN)) {
        return false;
    }
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_PATH_1)) {
        return false;
    }
    return true;
}

THUMB int status::PartyStatusUtility::getMaxLevel()
{
    g_Party.setPlayerMode();
    int count = g_Party.getCount();
    int level;
    int levelMax = 0;
    for (int i = 0; i < count; i++) {
        level = g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getLevel();
        if (level > levelMax) {
            levelMax = level;
        }
    }
    return levelMax;
}

THUMB int status::PartyStatusUtility::getPlayerMaxLevel()
{
    g_Party.setAllPlayerMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getPlayerIndex() == 1) {
            return g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getLevel();
        }
    }
    return 0;
}

THUMB bool status::PartyStatusUtility::isPartyActionEnable()
{
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    int enableCount = 0;
    for (int i = 0; i < count; i++) {
        if (!g_Party.isInsideCarriage(i) && g_Party.getPlayerStatus(i).isActionEnableWithoutDragoram()) {
            enableCount++;
        }
    }
    if (enableCount != 0) {
        return true;
    }
    return false;
}

THUMB bool status::PartyStatusUtility::isPoisonForMantan()
{
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU)) {
                return true;
            }
            if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
                return true;
            }
        }
    }
    return false;
}

THUMB bool status::PartyStatusUtility::destroyPoisonForMantan(UseActionParam& useActionParam)
{
    HaveAction::setTownMode();
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    for (int i = count - 1; i >= 0; i--) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() &&
            g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveAction().isAction(0x7e) &&
            g_Party.getPlayerStatus(i).getHaveStatusInfo().getMp() >= UseAction::getUseMp(0x7e)) {
            useActionParam.actorCharacterStatus_ = &g_Party.getPlayerStatus(i);
            break;
        }
    }
    if (useActionParam.actorCharacterStatus_ == NULL) {
        return false;
    }
    useActionParam.setActionIndex(0x7e);
    for (int i = 0; i < count; i++) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU) ||
                g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
                useActionParam.targetCount_ = 1;
                useActionParam.targetCharacterStatus_[0] = &g_Party.getPlayerStatus(i);
                break;
            }
        }
    }
    UseAction::execUse(useActionParam);
    return true;
}

THUMB bool status::PartyStatusUtility::isRecoveryForMantan()
{
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getHpMax() != g_Party.getPlayerStatus(i).getHaveStatusInfo().getHp()) {
                return true;
            }
        }
    }
    return false;
}

THUMB bool status::PartyStatusUtility::recoveryForMantan(UseActionParam& useActionParam)
{
    int hoimiB[12];
    int hoimiC[12];
    int behoimiB[12];
    int behoimiC[12];
    int behomaB[12];
    int behomaC[12];
    int behomalaB[12];
    int behomalaC[12];
    int hoimiActorIndex = -1;
    int hoimiTargetIndex = -1;
    int behoimiActorIndex = -1;
    int behoimiTargetIndex = -1;
    int behomaActorIndex = -1;
    int behomaTargetIndex = -1;
    int behomalaActorIndex = -1;
    int behomalaTargetIndex[12] = { -1 };
    for (int i = 0; i < 12; i++) {
        behomalaTargetIndex[i] = -1;
    }
    for (int i = 0; i < 12; i++) {
        hoimiB[i] = 0;
    }
    for (int i = 0; i < 12; i++) {
        hoimiC[i] = 0;
    }
    for (int i = 0; i < 12; i++) {
        behoimiB[i] = 0;
    }
    for (int i = 0; i < 12; i++) {
        behoimiC[i] = 0;
    }
    for (int i = 0; i < 12; i++) {
        behomaB[i] = 0;
    }
    for (int i = 0; i < 12; i++) {
        behomaC[i] = 0;
    }
    for (int i = 0; i < 12; i++) {
        behomalaB[i] = 0;
    }
    for (int i = 0; i < 12; i++) {
        behomalaC[i] = 0;
    }
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    for (int i = count - 1; i >= 0; i--) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() &&
            g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveAction().isAction(0x7a) &&
            g_Party.getPlayerStatus(i).getHaveStatusInfo().getMp() >= UseAction::getUseMp(0x7a)) {
            hoimiTargetIndex = calcRecoveryValue(0x7a, hoimiB, hoimiC);
            hoimiActorIndex = i;
            break;
        }
    }
    for (int i = count - 1; i >= 0; i--) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() &&
            g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveAction().isAction(0x7b) &&
            g_Party.getPlayerStatus(i).getHaveStatusInfo().getMp() >= UseAction::getUseMp(0x7b)) {
            behoimiTargetIndex = calcRecoveryValue(0x7b, behoimiB, behoimiC);
            behoimiActorIndex = i;
            break;
        }
    }
    for (int i = count - 1; i >= 0; i--) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() &&
            g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveAction().isAction(0x7c) &&
            g_Party.getPlayerStatus(i).getHaveStatusInfo().getMp() >= UseAction::getUseMp(0x7c)) {
            behomaTargetIndex = calcRecoveryValue(0x7c, behomaB, behomaC);
            behomaActorIndex = i;
            break;
        }
    }
    for (int i = count - 1; i >= 0; i--) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() &&
            g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveAction().isAction(0x7d) &&
            g_Party.getPlayerStatus(i).getHaveStatusInfo().getMp() >= UseAction::getUseMp(0x7d)) {
            calcRecoveryValue(0x7d, behomalaB, behomalaC);
            getBehomalaTargetIndex(behomalaTargetIndex);
            behomalaActorIndex = i;
            break;
        }
    }
    int BMax = -1;
    int CMax = -1;
    int actionIndex = 0;
    int actorIndex = -1;
    int targetIndex = -1;
    for (int i = 0; i < count; i++) {
        if (hoimiC[i] != 0 && hoimiB[i] > BMax) {
            actionIndex = 0x7a;
            BMax = hoimiB[i];
            actorIndex = hoimiActorIndex;
            CMax = hoimiC[i];
            targetIndex = hoimiTargetIndex;
        }
    }
    for (int i = 0; i < count; i++) {
        if (behoimiB[i] != 0 && behoimiB[i] > BMax) {
            BMax = behoimiB[i];
            CMax = behoimiC[i];
            actorIndex = behoimiActorIndex;
            actionIndex = 0x7b;
            targetIndex = behoimiTargetIndex;
        }
    }
    for (int i = 0; i < count; i++) {
        if (behomaC[i] != 0 && behomaB[i] > BMax) {
            actionIndex = 0x7c;
            BMax = behomaB[i];
            actorIndex = behomaActorIndex;
            CMax = behomaC[i];
            targetIndex = behomaTargetIndex;
        }
    }
    for (int i = 0; i < count; i++) {
        if (behomalaB[i] != 0) {
            if (behomalaB[i] > BMax) {
                actionIndex = 0x7d;
                BMax = behomalaB[i];
                actorIndex = behomalaActorIndex;
            } else if (BMax == behomalaB[i] && behomalaC[i] > CMax) {
                actionIndex = 0x7d;
                BMax = behomalaB[i];
                actorIndex = behomalaActorIndex;
            }
        }
    }
    if (actorIndex == -1) {
        return false;
    }
    useActionParam.setActionIndex(actionIndex);
    useActionParam.actorCharacterStatus_ = &g_Party.getPlayerStatus(actorIndex);
    if (actionIndex != 0x7d) {
        useActionParam.targetCount_ = 1;
        useActionParam.targetCharacterStatus_[0] = &g_Party.getPlayerStatus(targetIndex);
    } else {
        int count = 0;
        for (int i = 0; i < 12; i++) {
            if (behomalaTargetIndex[i] != -1) {
                useActionParam.targetCharacterStatus_[count] = &g_Party.getPlayerStatus(i);
                count++;
            }
        }
        useActionParam.targetCount_ = count;
    }
    UseAction::execUse(useActionParam);
    return true;
}

THUMB int status::PartyStatusUtility::calcRecoveryValue(int actionIndex, int* valueBMax, int* valueCMax)
{
    int valueA[12];
    int valueB[12];
    int valueC[12];
    for (int i = 0; i < 12; i++) {
        valueA[i] = 0;
    }
    for (int i = 0; i < 12; i++) {
        valueB[i] = 0;
    }
    for (int i = 0; i < 12; i++) {
        valueC[i] = 0;
    }
    calcRecoveryLocal(actionIndex, valueA, valueB, valueC);
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    int ret = calcRecoveryLocalMax(count, valueA, valueB, valueC, valueBMax, valueCMax);
    return ret;
}

THUMB void status::PartyStatusUtility::calcRecoveryLocal(int actionIndex, int* valueA, int* valueB, int* valueC)
{
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getHpMax() != g_Party.getPlayerStatus(i).getHaveStatusInfo().getHp()) {
                HaveStatusInfo& hpInfo = g_Party.getPlayerStatus(i).getHaveStatusInfo();
                HaveStatusInfo& hpMaxInfo = g_Party.getPlayerStatus(i).getHaveStatusInfo();
                int hp = hpInfo.getHp();
                valueA[i] = hpMaxInfo.getHpMax() - hp;
                valueB[i] = UseAction::getEffectValueForAvarage(actionIndex) * 100 / valueA[i];
                if (actionIndex == 0x7c) {
                    valueB[i] = 100;
                }
                if (valueB[i] > 100) {
                    valueB[i] = 100;
                }
                valueC[i] = valueB[i] / UseAction::getUseMp(actionIndex);
            }
        }
    }
    if (actionIndex == 0x7d) {
        int sum = 0;
        for (int i = 0; i < count; i++) {
            sum += valueB[i];
        }
        for (int i = 0; i < count; i++) {
            if (valueB[i] != 0) {
                valueB[i] = sum;
                valueC[i] = sum / UseAction::getUseMp(actionIndex);
                if (valueB[i] > 100) {
                    valueB[i] = 100;
                }
            }
        }
    }
}

THUMB int status::PartyStatusUtility::calcRecoveryLocalMax(int count, int* valueA, int* valueB, int* valueC, int* valueBMax, int* valueCMax)
{
    int index = -1;
    int BMax = -1;
    int CMax = -1;
    for (int i = 0; i < count; i++) {
        if (valueA[i] != 0) {
            if (valueB[i] > BMax) {
                CMax = valueC[i];
                index = i;
                BMax = valueB[i];
            }
            if (BMax == valueB[i] && CMax < valueC[i]) {
                index = i;
                BMax = valueB[i];
                CMax = valueC[i];
            }
        }
    }
    valueBMax[index] = BMax;
    valueCMax[index] = CMax;
    return index;
}

THUMB void status::PartyStatusUtility::getBehomalaTargetIndex(int* target)
{
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getHpMax() != g_Party.getPlayerStatus(i).getHaveStatusInfo().getHp()) {
                target[i] = i;
            }
        }
    }
}

THUMB bool status::PartyStatusUtility::isDemolition()
{
    int playerCount = 0;
    g_Party.setBattleModeWithCarriage();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getPlayerIndex() == 2) {
            playerCount++;
        }
    }
    if (g_Story.getChapter() == dq5::CHAPTER_YOUNENKI && playerCount == 0) {
        if (g_Party.getPlayerStatusForPlayerIndex(1).getHaveStatusInfo().isDeath()) {
            return true;
        }
    }
    playerCount = 0;
    for (int i = 0; i < count; i++) {
        if (StatusChange::statusCloseDoor_.isEnable() && g_Party.isInsideCarriage(i)) {
            continue;
        }
        if (g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
            continue;
        }
        if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().isPlayer()) {
            playerCount++;
        }
        if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getPlayerIndex() == 2) {
            playerCount++;
        }
    }
    if (playerCount == 0 && !isPapasBattle()) {
        return true;
    }
    playerCount = 0;
    for (int i = 0; i < count; i++) {
        if (StatusChange::statusCloseDoor_.isEnable() && g_Party.isInsideCarriage(i)) {
            continue;
        }
        if (g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().isPlayer()) {
            playerCount++;
        }
        if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getPlayerIndex() == 2) {
            playerCount++;
        }
    }
    if (playerCount == 0 && !isPapasBattle()) {
        return true;
    }
    return false;
}

THUMB bool status::PartyStatusUtility::isPapasBattle()
{
    g_Party.setBattleModeWithCarriage();
    int count = g_Party.getCount();
    if (count != 1) {
        return false;
    }
    for (int i = 0; i < count; i++) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() &&
            g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getPlayerIndex() == 2) {
            return true;
        }
    }
    return false;
}

THUMB bool status::PartyStatusUtility::isPapasBattle2()
{
    g_Party.setBattleModeWithCarriage();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() &&
            g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getPlayerIndex() == 2) {
            return true;
        }
    }
    return false;
}

THUMB bool status::PartyStatusUtility::isAlivePapasOnly()
{
    g_Party.setPlayerMode();
    int count = g_Party.getCount();
    int aliveCount = 0;
    for (int i = 0; i < count; i++) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            aliveCount++;
        }
    }
    if (aliveCount == 0) {
        return false;
    }
    return true;
}

THUMB void status::PartyStatusUtility::recoveryBattleEnd()
{
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            int kindIndex = g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getPlayerKindIndex();
            dq5::level::CharacterInitData* charaInitData = dq5::level::CharacterInitData::getRecord(kindIndex);
            switch (charaInitData->getDemolition()) {
            case 0:
                if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getPlayerIndex() == 1 && g_Story.getChapter() == dq5::CHAPTER_YOUNENKI) {
                    g_Party.getPlayerStatus(i).getHaveStatusInfo().setHp(1);
                }
                break;
            case 1:
                g_Party.getPlayerStatus(i).getHaveStatusInfo().setHp(1);
                break;
            case 2: {
                unsigned short value = g_Party.getPlayerStatus(i).getHaveStatusInfo().getHpMax();
                g_Party.getPlayerStatus(i).getHaveStatusInfo().setHp(value);
                value = g_Party.getPlayerStatus(i).getHaveStatusInfo().getMpMax();
                g_Party.getPlayerStatus(i).getHaveStatusInfo().setMp(value);
                break;
            }
            }
        }
    }
}

THUMB status::PlayerStatus& status::PartyStatusUtility::getStoryPlayerStatus()
{
    g_Party.setMemberShiftMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getPlayerIndex() == 1) {
            return g_Party.getPlayerStatus(i);
        }
    }
    return g_Party.getPlayerStatus(0);
}

THUMB int status::PartyStatusUtility::getLevelupPlayer()
{
    g_Party.setPlayerMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().isLevelup()) {
            return i;
        }
    }
    return -1;
}

THUMB void status::PartyStatusUtility::recovery()
{
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        g_Party.getPlayerStatus(i).getHaveStatusInfo().recovery();
    }
}

THUMB void status::PartyStatusUtility::kaifukuyuka()
{
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (g_Party.getPlayerStatus(i).isAlive()) {
            g_Party.getPlayerStatus(i).getHaveStatusInfo().recovery();
        }
    }
}

THUMB void status::PartyStatusUtility::startBattle()
{
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        g_Party.getPlayerStatus(i).getHaveBattleStatus().startBattle();
    }
}

THUMB void status::PartyStatusUtility::execOfRoundInCarriage()
{
    g_Party.setBattleModeWithCarriage();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.isOutsideCarriage(i)) {
            g_Party.getPlayerStatus(i).execOfRound();
        }
    }
}

THUMB int status::PartyStatusUtility::giveItem(int itemIndex)
{
    g_Party.setPlayerMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() && g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveItem().isSpace()) {
            g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveItem().add(itemIndex);
            return i;
        }
    }
    g_Party.haveItemSack_.add(itemIndex);
    return -1;
}

THUMB int status::PartyStatusUtility::getLeaderIndex()
{
    g_Party.setPlayerMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() && g_Party.isOutsideCarriage(i)) {
            return i;
        }
    }
    return -1;
}

THUMB void status::PartyStatusUtility::reflectBattleExp()
{
    if (UseActionFlag::isDouble()) {
        int exp = g_Party.getBattleExp();
        g_Party.battleExp_ = exp * 2;
    }
    g_Party.setPlayerMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().isBattleNpc()) {
                int exp = g_Party.getBattleExp();
                g_Party.getPlayerStatus(i).getHaveStatusInfo().addExp(exp);
            }
        }
    }
}

THUMB int status::PartyStatusUtility::getAlivePlayerCountOutsideCarriage()
{
    int playerCount = 0;
    g_Party.setPlayerMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.isInsideCarriage(i) && g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().isPlayer() &&
            !g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            playerCount++;
        }
    }
    return playerCount;
}

THUMB int status::PartyStatusUtility::getAliveCountOutsideCarriagePlayerOnly()
{
    if (isPapasBattle()) {
        return 1;
    }
    int playerCount = 0;
    g_Party.setPlayerMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.isInsideCarriage(i) && !g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            playerCount++;
        }
    }
    return playerCount;
}

THUMB int status::PartyStatusUtility::getAliveWithoutSpazzCountOutsideCarriagePlayerOnly()
{
    int playerCount = 0;
    if (isPapasBattle()) {
        return 1;
    }
    if (isPapasBattle2()) {
        return 1;
    }
    g_Party.setPlayerMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!g_Party.isInsideCarriage(i) && !g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() &&
            !g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
            playerCount++;
        }
    }
    return playerCount;
}

THUMB void status::PartyStatusUtility::forceReorderBattle()
{
    if (g_StageAttribute.isCarriageEnter()) {
        int member[4];
        for (int i = 0; i < 4; i++) {
            member[i] = -1;
        }
        int playerCount = 0;
        g_Party.setMemberShiftMode();
        int count = g_Party.getCount();
        for (int i = 0; i < count; i++) {
            if (!g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() &&
                !g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
                member[playerCount] = i;
                playerCount++;
                if (playerCount >= 4) {
                    break;
                }
            }
        }
        g_Party.reorder(member[0], member[1], member[2], member[3]);
    }
}

THUMB void status::PartyStatusUtility::forceReorderTown(bool notCheck)
{
    dq5::level::PlayerCarriage::setup();
    g_Party.setBattleModeAndCarriage();
    int outCount = g_Party.getCarriageOutCount();
    unsigned int max = dq5::level::PlayerCarriage::getArraySize();
    for (unsigned int i = 0; i < max; i++) {
        dq5::level::PlayerCarriage* data = dq5::level::PlayerCarriage::getRecord(i);
        if (!notCheck) {
            if (g_Global.getMapNameId() != data->getFloor()) {
                continue;
            }
            if (!data->getSorting()) {
                break;
            }
        }
        if (!data->getMostRelive() && g_StageInfo.reliveMessageFlag_ == 1) {
            bool aliveHuman = false;
            for (int i = 0; i < outCount; i++) {
                if (i == g_Party.getSortIndex(1)) {
                    continue;
                }
                HaveStatus& haveStatus = g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus();
                if (haveStatus.playerType_ == HaveStatus::TYPE_BATTLENPC || haveStatus.playerType_ == HaveStatus::TYPE_NOBATTLENPC ||
                    haveStatus.playerType_ == HaveStatus::TYPE_FRIENDMONSTER) {
                    continue;
                }
                if (haveStatus.getHp() != 0) {
                    aliveHuman = true;
                    break;
                }
            }
            if (aliveHuman == true) {
                break;
            }
        }
        bool notDrawParty = twn::TownPlayerManager::getSingleton().partyDraw_.isPartyDrawNone();
        int partyIndex[10] = { -1 };
        for (int i = 0; i < 10; i++) {
            partyIndex[i] = -1;
        }
        int reorderMember[4] = { -1 };
        for (int i = 0; i < 4; i++) {
            reorderMember[i] = -1;
        }
        int human[10] = { -1 };
        for (int i = 0; i < 10; i++) {
            human[i] = -1;
        }
        int monster[10] = { -1 };
        for (int i = 0; i < 10; i++) {
            monster[i] = -1;
        }
        int alive[10] = { -1 };
        for (int i = 0; i < 10; i++) {
            alive[i] = -1;
        }
        int death[10] = { -1 };
        for (int i = 0; i < 10; i++) {
            death[i] = -1;
        }
        int partyCount = g_Party.getCount();
        int count = 0;
        int humanCount = 0;
        int monsterCount = 0;
        int aliveCount = 0;
        int deathCount = 0;
        bool savePartyFlag = false;
        if (formerParty_[0] == -1) {
            savePartyFlag = true;
        }
        for (int i = 0; i < partyCount; i++) {
            HaveStatusInfo& statusInfo = g_Party.getPlayerStatus(i).getHaveStatusInfo();
            if (statusInfo.getHaveStatus().isFriendMonster()) {
                monster[monsterCount] = statusInfo.getPlayerIndex();
                monsterCount++;
            } else {
                human[humanCount] = statusInfo.getPlayerIndex();
                humanCount++;
            }
            if (i < outCount && savePartyFlag == true) {
                formerParty_[i] = statusInfo.getPlayerIndex();
            }
        }
        for (int i = 0; i < humanCount; i++) {
            if (human[i] == 1) {
                for (int j = i; j > 0; j--) {
                    human[j] = human[j - 1];
                }
                human[0] = 1;
                break;
            }
        }
        for (int i = 0; i < humanCount; i++) {
            if (g_Party.getPlayerStatusForPlayerIndex(human[i]).getHaveStatusInfo().isDeath() == true) {
                death[deathCount] = human[i];
                deathCount++;
            } else {
                alive[aliveCount] = human[i];
                aliveCount++;
            }
        }
        for (int i = 0; i < monsterCount; i++) {
            if (g_Party.getPlayerStatusForPlayerIndex(monster[i]).getHaveStatusInfo().isDeath() == true) {
                death[deathCount] = monster[i];
                deathCount++;
            } else {
                alive[aliveCount] = monster[i];
                aliveCount++;
            }
        }
        for (int i = 0; i < aliveCount; i++) {
            partyIndex[count] = alive[i];
            count++;
        }
        for (int i = 0; i < deathCount; i++) {
            partyIndex[count] = death[i];
            count++;
        }
        for (int i = 0; i < outCount; i++) {
            reorderMember[i] = g_Party.getSortIndex(partyIndex[i]);
        }
        if (g_Story.getChapter() == dq5::CHAPTER_YOUNENKI && g_Global.getMapNameId() == 0x82) {
            reorderMember[0] = g_Party.getSortIndex(1);
            reorderMember[1] = g_Party.getSortIndex(0x10);
            reorderMember[2] = g_Party.getSortIndex(5);
            reorderMember[3] = -1;
        }
        g_Party.reorder(reorderMember[0], reorderMember[1], reorderMember[2], reorderMember[3]);
        cmn::GameManager::getSingleton().resetParty();
        if (notDrawParty == true) {
            twn::TownPlayerManager::getSingleton().partyDraw_.setDrawPartyNone();
        }
        break;
    }
    dq5::level::PlayerCarriage::cleanup();
}

THUMB void status::PartyStatusUtility::resetForceReorderMember()
{
    for (int i = 0; i < 4; i++) {
        formerParty_[i] = -1;
    }
}

THUMB void status::PartyStatusUtility::reorderFormerMember()
{
    if (formerParty_[0] != -1) {
        g_Party.setBattleModeAndCarriage();
        int partyIndex[10] = { -1 };
        int defaultParty[4] = { -1 };
        for (int i = 0; i < 4; i++) {
            defaultParty[i] = -1;
        }
        int count = g_Party.getCount();
        count = 0;
        for (int i = 0; i < 4; i++) {
            if (formerParty_[i] != -1) {
                int index = g_Party.getSortIndex(formerParty_[i]);
                if (index != -1) {
                    defaultParty[count] = index;
                    count++;
                }
            }
        }
        g_Party.reorder(defaultParty[0], defaultParty[1], defaultParty[2], defaultParty[3]);
        cmn::GameManager::getSingleton().resetParty();
    }
    for (int i = 0; i < 4; i++) {
        formerParty_[i] = -1;
    }
}

THUMB void status::PartyStatusUtility::recoveryDisableDemolition()
{
    if (!g_Party.isSugorokuMode()) {
        g_Party.setBattleMode();
        int count = g_Party.getCount();
        for (int i = 0; i < count; i++) {
            int hp = g_Party.getPlayerStatus(i).getHaveStatusInfo().getHpMax();
            g_Party.getPlayerStatus(i).getHaveStatusInfo().setHp(hp);
        }
    }
}

THUMB void status::PartyStatusUtility::separateParty(bool resetFlag)
{
    separateFlag_ = 1;
    g_Party.setAllPlayerMode();
    int count = g_Party.getCount();
    int carriageOut = g_Party.getCarriageOutCount();
    int headPlayer = 0;
    carriageOut = dss::clamp<int>(1, carriageOut, 4);
    for (int i = 0; i < count; i++) {
        HaveStatusInfo& statusInfo = g_Party.getPlayerStatus(i).getHaveStatusInfo();
        int index = statusInfo.getPlayerIndex();
        separatePlayer_[i] = index;
        if (headPlayer == 0 && !statusInfo.isDeath()) {
            headPlayer = index;
        }
    }
    g_Party.setDisplayMode();
    int outCount = g_Party.getCount();
    for (int i = 0; i < outCount; i++) {
        separateCarriageOutPlayer_[i] = g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getPlayerIndex();
    }
    g_Party.clear();
    g_Party.add(headPlayer, true);
    if (resetFlag == true) {
        cmn::GameManager::getSingleton().resetParty();
    }
}

THUMB void status::PartyStatusUtility::resetSeparateParty(bool resetFlag)
{
    int count = 0;
    separateFlag_ = 0;
    g_Party.clear();
    while (separatePlayer_[count] != -1) {
        g_Party.add(separatePlayer_[count], true);
        count++;
        if (count > 9) {
            break;
        }
    }
    count = 0;
    g_Party.setBattleModeAndCarriage();
    int partyCount = g_Party.getCount();
    int temp[4] = { -1 };
    for (int i = 0; i < 4; i++) {
        temp[i] = -1;
    }
    for (int i = 0; i < 4; i++) {
        if (separateCarriageOutPlayer_[i] != -1) {
            for (int j = 0; j < partyCount; j++) {
                int index = g_Party.getPlayerStatus(j).getHaveStatusInfo().getPlayerIndex();
                if (index == separateCarriageOutPlayer_[i]) {
                    temp[count] = j;
                    count++;
                    break;
                }
            }
        }
    }
    g_Party.reorder(temp[0], temp[1], temp[2], temp[3]);
    if (resetFlag == true) {
        cmn::GameManager::getSingleton().resetParty();
    }
    for (int i = 0; i < 10; i++) {
        separatePlayer_[i] = -1;
    }
    for (int i = 0; i < 5; i++) {
        separateCarriageOutPlayer_[i] = -1;
    }
}

THUMB void status::PartyStatusUtility::clearWalkDamage()
{
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    for (int i = 0; i < count; i++) {
        g_Party.getPlayerStatus(i).clearWalkDamage(true);
    }
}
