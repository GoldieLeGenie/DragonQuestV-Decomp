#pragma ipa file
#include "ov000/btl/BattleRoundEnd.hpp"
#include "ov000/btl/BattleActorMacro.hpp"
#include "ov000/btl/BattleMessage.hpp"
#include "ov000/btl/BattleMonster.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov000/status/MonsterStatus.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "main/btl/Encount.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/menu/StadiumData.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/text/TextAPI.hpp"

THUMB inline int status::HaveStatus::getPlayerIndex() const { return playerIndex_; }
THUMB inline int status::HaveStatusInfo::getPlayerIndex() const { return haveStatus_.getPlayerIndex(); }
THUMB inline int status::PlayerStatus::getPlayerIndex() { return haveStatusInfo_.getPlayerIndex(); }
THUMB inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
// out-of-line copy used by the venom setups: a file-local helper, because a weak copy of the member
// would be merged with the one ov005 (FieldPartyDraw) emits for the same inline
namespace status {
    static THUMB inline HaveStatusInfo& getHaveStatusInfo(CharacterStatus& characterStatus) { return characterStatus.haveStatusInfo_; }
}
THUMB inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
THUMB inline status::HaveEquipment& status::HaveStatusInfo::getHaveEquipment() { return haveEquipment_; }
THUMB inline int status::HaveStatusInfo::getDrawCtrlId() { return drawCtrlId_; }
THUMB inline int status::MonsterStatus::getMonsterIndex() { return characterIndex_; }
THUMB inline int status::MonsterStatus::getSortIndexInGroup() { return sortIndex_; }
THUMB inline int status::MonsterStatus::getMosyasIndex() { return mosyasIndex_; }
THUMB inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index) { return monsters_[index]; }
THUMB inline bool StadiumData::isStadiumBattle() { return stadiumFlag_; }
THUMB inline void ExecTask2::setAutoMessage(bool flag) { autoMessage_ = flag; }
THUMB inline void btl::BattleTaskVenom::setSortIndex(int sortIndex) { sortIndex_ = sortIndex; }
THUMB inline void btl::BattleTaskVenom2::setSortIndex(int sortIndex) { sortIndex_ = sortIndex; }
THUMB inline void btl::BattleTaskLifeRing::setSortIndex(int sortIndex) { sortIndex_ = sortIndex; }
THUMB inline void btl::BattleTaskMysteriousArmor::setSortIndex(int sortIndex) { sortIndex_ = sortIndex; }
THUMB inline void btl::BattleTaskOracle::setSortIndex(int sortIndex) { sortIndex_ = sortIndex; }
THUMB inline void btl::BattleTaskVenom::cleanup() {}
THUMB inline void btl::BattleTaskVenom2::cleanup() {}
THUMB inline void btl::BattleExecVenom::terminate_user() {}

THUMB void btl::BattleTaskVenom::setup()
{
    int playerIndex = status::g_Party.getPlayerStatus(sortIndex_).getPlayerIndex();
    TextAPI::setMACRO0(0x12, 0x50000000, playerIndex);
    int hp = status::getHaveStatusInfo(status::g_Party.getPlayerStatus(sortIndex_)).getHpMax() / 6;
    status::getHaveStatusInfo(status::g_Party.getPlayerStatus(sortIndex_)).addHp(-hp);
    TextAPI::setMACRO0(0x2B, 0xF0000000, hp);
    if (status::getHaveStatusInfo(status::g_Party.getPlayerStatus(sortIndex_)).isDeath()) {
        BattleMessage::setMessage(0xC3B92, 0xC3926, 0, 0);
    }
    else {
        BattleMessage::setMessage(0xC3B92, 0xC3921, 0, 0);
    }
    setAutoMessage(true);
}

#pragma dont_inline on
THUMB void btl::BattleTaskVenom2::setup()
{
    int monsterIndex = status::g_Monster.getMonsterStatus(sortIndex_).getMonsterIndex();
    if (status::g_Monster.getMonsterCountDeadOrAlive(monsterIndex) == 1 && !Encount::getSingleton()->getMonsterCountName(monsterIndex)) {
        TextAPI::setMACRO0(0x12, 0x60000000, monsterIndex);
        if (status::getHaveStatusInfo(status::g_Monster.getMonsterStatus(sortIndex_)).getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU)) {
            int playerIndex = status::MonsterStatus(status::g_Monster.getMonsterStatus(sortIndex_)).getMosyasIndex();
            TextAPI::setMACRO0(0x12, 0x50000000, playerIndex, 1, -1);
        }
    }
    else {
        int sortIndex = status::g_Monster.getMonsterStatus(sortIndex_).getSortIndexInGroup();
        TextAPI::setMACRO0(0x12, 0x60000000, monsterIndex, sortIndex);
        if (status::getHaveStatusInfo(status::g_Monster.getMonsterStatus(sortIndex_)).getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU)) {
            int playerIndex = status::MonsterStatus(status::g_Monster.getMonsterStatus(sortIndex_)).getMosyasIndex();
            TextAPI::setMACRO0(0x12, 0x50000000, playerIndex, 1, -1);
        }
    }
    int hp = status::getHaveStatusInfo(status::g_Monster.getMonsterStatus(sortIndex_)).getHpMax() / 6;
    status::getHaveStatusInfo(status::g_Monster.getMonsterStatus(sortIndex_)).addHp(-hp);
    TextAPI::setMACRO0(0x2B, 0xF0000000, hp);
    if (status::getHaveStatusInfo(status::g_Monster.getMonsterStatus(sortIndex_)).isDeath()) {
        status::g_Monster.checkDropItem(sortIndex_);
        BattleMessage::setMessage(0xC3D2C, 0, 0, 0);
        int drawCtrlId = status::getHaveStatusInfo(status::g_Monster.getMonsterStatus(sortIndex_)).getDrawCtrlId();
        BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0, 0x1F);
    }
    else {
        BattleMessage::setMessage(0xC3B92, 0, 0, 0);
    }
    setAutoMessage(true);
}

#pragma dont_inline reset

THUMB void btl::BattleExecVenom::initialize_user()
{
    int venomCount = 0;
    int playerCount = 0;
    if (!g_StadiumData.isStadiumBattle()) {
        status::g_Party.setBattleMode();
        int count = status::g_Party.getCount();
        for (int i = 0; i < count; i++) {
            if (status::g_Party.isInsideCarriage(i)) {
                continue;
            }
            if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
                continue;
            }
            if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
                resister(venomCount, &battleTaskVenom_[playerCount]);
                battleTaskVenom_[playerCount].setSortIndex(i);
                venomCount++;
                playerCount++;
            }
        }
    }
    {
        int monsterCount = 0;
        int count = status::g_Monster.getCount();
        for (int i = 0; i < count; i++) {
            if (status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
                continue;
            }
            if (status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
                resister(venomCount, &battleTaskVenom2_[monsterCount]);
                battleTaskVenom2_[monsterCount].setSortIndex(i);
                venomCount++;
                monsterCount++;
            }
        }
    }
}

THUMB void btl::BattleTaskLifeRing::setup()
{
    int hp = status::g_Party.getPlayerStatus(sortIndex_).getHaveStatusInfo().getHpMax();
    if (status::g_Party.getPlayerStatus(sortIndex_).getHaveStatusInfo().getHp() < hp) {
        status::g_Party.getPlayerStatus(sortIndex_).getHaveStatusInfo().addHp(10);
    }
    int playerIndex = status::g_Party.getPlayerStatus(sortIndex_).getPlayerIndex();
    TextAPI::setMACRO0(1, 0x50000000, playerIndex);
    BattleMessage::setMessage(0xC3CD2, 0, 0, 0);
    setAutoMessage(true);
    SoundManager::playSe(0x1F5, 0);
}

THUMB void btl::BattleTaskLifeRing::cleanup()
{
}

THUMB void btl::BattleExecLifeRing::initialize_user()
{
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    int ringCount = 0;
    for (int i = 0; i < count; i++) {
        if (status::g_Party.isInsideCarriage(i)) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveEquipment().isEquipment(0xA0)) {
            resister(ringCount, &battleTaskLifeRing_[ringCount]);
            battleTaskLifeRing_[ringCount].setSortIndex(i);
            ringCount++;
        }
    }
}

THUMB void btl::BattleExecLifeRing::terminate_user()
{
}

THUMB void btl::BattleTaskMysteriousArmor::setup()
{
    int hp = status::g_Party.getPlayerStatus(sortIndex_).getHaveStatusInfo().getHpMax();
    if (status::g_Party.getPlayerStatus(sortIndex_).getHaveStatusInfo().getHp() < hp) {
        status::g_Party.getPlayerStatus(sortIndex_).getHaveStatusInfo().addHp(30);
    }
    int playerIndex = status::g_Party.getPlayerStatus(sortIndex_).getPlayerIndex();
    TextAPI::setMACRO0(1, 0x50000000, playerIndex);
    BattleMessage::setMessage(0xC3CD2, 0, 0, 0);
    setAutoMessage(true);
    SoundManager::playSe(0x1F5, 0);
}

THUMB void btl::BattleTaskMysteriousArmor::cleanup()
{
}

THUMB void btl::BattleExecMysteriousArmor::initialize_user()
{
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    int targetCount = 0;
    for (int i = 0; i < count; i++) {
        if (status::g_Party.isInsideCarriage(i)) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveEquipment().isEquipment(0x6E)) {
            resister(targetCount, &battleTaskMysteriousArmor_[targetCount]);
            battleTaskMysteriousArmor_[targetCount].setSortIndex(i);
            targetCount++;
        }
    }
}

THUMB void btl::BattleExecMysteriousArmor::terminate_user()
{
}

THUMB void btl::BattleTaskOracle::setup()
{
    int hp = status::g_Party.getPlayerStatus(sortIndex_).getHaveStatusInfo().getHpMax();
    if (status::g_Party.getPlayerStatus(sortIndex_).getHaveStatusInfo().getHp() < hp) {
        int hp = UnkDssRand::rand(6) + 10;
        status::g_Party.getPlayerStatus(sortIndex_).getHaveStatusInfo().addHp(hp);
    }
    int playerIndex = status::g_Party.getPlayerStatus(sortIndex_).getPlayerIndex();
    TextAPI::setMACRO0(1, 0x50000000, playerIndex);
    BattleMessage::setMessage(0xC3CD2, 0, 0, 0);
    setAutoMessage(true);
    SoundManager::playSe(0x1F5, 0);
}

THUMB void btl::BattleTaskOracle::cleanup()
{
}

THUMB void btl::BattleExecOracle::initialize_user()
{
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    int targetCount = 0;
    for (int i = 0; i < count; i++) {
        if (status::g_Party.isInsideCarriage(i)) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveEquipment().isEquipment(0xE2)) {
            resister(targetCount, &battleTaskOracle_[targetCount]);
            battleTaskOracle_[targetCount].setSortIndex(i);
            targetCount++;
        }
    }
}

THUMB void btl::BattleExecOracle::terminate_user()
{
}

THUMB void btl::BattleRoundEndVenom::setup()
{
}

THUMB void btl::BattleRoundEndVenom::cleanup()
{
}

THUMB bool btl::BattleRoundEndVenom::isEnd()
{
    if (!battleExecVenom_.execute()) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleRoundEndVenom::isEnable()
{
    int venomCount = 0;
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (status::g_Party.isInsideCarriage(i)) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
            venomCount++;
        }
    }
    count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        if (status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        if (status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
            venomCount++;
        }
    }
    if (venomCount == 0) {
        return false;
    }
    return true;
}

THUMB void btl::BattleRoundEndLifeRing::setup()
{
}

THUMB void btl::BattleRoundEndLifeRing::cleanup()
{
}

THUMB bool btl::BattleRoundEndLifeRing::isEnd()
{
    if (!battleExecLifeRing_.execute()) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleRoundEndLifeRing::isEnable()
{
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    int ringCount = 0;
    for (int i = 0; i < count; i++) {
        if (status::g_Party.isInsideCarriage(i)) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveEquipment().isEquipment(0xA0)) {
            ringCount++;
        }
    }
    if (ringCount == 0) {
        return false;
    }
    return true;
}

THUMB void btl::BattleRoundEndMysteriousArmor::setup()
{
}

THUMB void btl::BattleRoundEndMysteriousArmor::cleanup()
{
}

THUMB bool btl::BattleRoundEndMysteriousArmor::isEnd()
{
    if (!battleExecMysteriousArmor_.execute()) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleRoundEndMysteriousArmor::isEnable()
{
    int count = status::g_Party.getCount();
    int targetCount = 0;
    for (int i = 0; i < count; i++) {
        if (status::g_Party.isInsideCarriage(i)) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveEquipment().isEquipment(0x6E)) {
            targetCount++;
        }
    }
    if (targetCount == 0) {
        return false;
    }
    return true;
}

THUMB void btl::BattleRoundEndOracle::setup()
{
}

THUMB void btl::BattleRoundEndOracle::cleanup()
{
}

THUMB bool btl::BattleRoundEndOracle::isEnd()
{
    if (!battleExecOracle_.execute()) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleRoundEndOracle::isEnable()
{
    int count = status::g_Party.getCount();
    int targetCount = 0;
    for (int i = 0; i < count; i++) {
        if (status::g_Party.isInsideCarriage(i)) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            continue;
        }
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveEquipment().isEquipment(0xE2)) {
            targetCount++;
        }
    }
    if (targetCount == 0) {
        return false;
    }
    return true;
}

THUMB void btl::BattleRoundEndAstoron::setup()
{
    int count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        status::StatusChange& status = status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getStatusChange();
        if (status.isEnable(dq5::level::ActionParam::ACTIONTYPE_ASTORON) && status.getRestTurn(dq5::level::ActionParam::ACTIONTYPE_ASTORON) == 1) {
            BattleActorMacro::setMacroActor(&status::g_Monster.getMonsterStatus(i), 0x31);
            TextAPI::setMACRO0(0x19, 0x70000000, 0x31);
            BattleMessage::setMessage(0xC3C68, 0, 0, 0);
            int drawCtrlId = status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getDrawCtrlId();
            BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setPaletteAstoron(0);
        }
    }
    setAutoMessage(true);
}

THUMB void btl::BattleRoundEndAstoron::cleanup()
{
}

THUMB bool btl::BattleRoundEndAstoron::isEnable()
{
    int astoronCount = 0;
    int count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        status::StatusChange& status = status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().getStatusChange();
        if (status.isEnable(dq5::level::ActionParam::ACTIONTYPE_ASTORON)) {
            astoronCount++;
        }
    }
    if (astoronCount == 0) {
        return false;
    }
    return true;
}

THUMB void btl::BattleRoundEnd::initialize_user()
{
    if (g_StadiumData.isStadiumBattle()) {
        int index = 0;
        if (venom_.isEnable()) {
            resister(index, &venom_);
            index++;
        }
        if (astoron_.isEnable()) {
            resister(index, &astoron_);
        }
    }
    else {
        int index = 0;
        if (lifeRing_.isEnable()) {
            resister(index, &lifeRing_);
            index++;
        }
        if (mysteriousArmor_.isEnable()) {
            resister(index, &mysteriousArmor_);
            index++;
        }
        if (oracle_.isEnable()) {
            resister(index, &oracle_);
        }
    }
}

THUMB void btl::BattleRoundEnd::terminate_user()
{
}
