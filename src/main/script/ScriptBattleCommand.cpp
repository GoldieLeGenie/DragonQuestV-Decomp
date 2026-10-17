#pragma ipa file
#include "main/script/ScriptBattleCommand.hpp"
#include "main/script/CommandParam.hpp"
#include "main/script/ScriptSystem.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/btl/BattleScriptManager.hpp"
#include "main/btl/Encount.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/HaveBattleStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "ov000/btl/BattleActorManager.hpp"
#include "ov000/btl/BattleEffectManager.hpp"
#include "ov000/btl/BattleMessage.hpp"
#include "ov000/btl/BattleRoot.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"

#pragma thumb on

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
}

inline void ScriptSystem::setEnableExecute(bool flag)
{
    executeEnable_ = flag;
}

inline void btl::Encount::setEnable(int flag)
{
    enable_ = flag;
}

inline int status::BattleResult::getBattleTurnCount()
{
    return battleTurnCount_;
}

inline void status::BattleResult::setPlayerVictory(bool flag)
{
    playerVictory_ = flag;
}

inline void status::BattleResult::setPlayerDemolition(bool flag)
{
    playerDemolition_ = flag;
}

inline void status::BattleResult::setDemolitionPartyTalk(bool flag)
{
    demolitionPartyTalk_ = flag;
}

inline void btl::BattleRoot::setExecuteEnable(int flag)
{
    executeFlag_ = flag;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::PlayerStatus::getPlayerIndex()
{
    return getHaveStatusInfo().getHaveStatus().getPlayerIndex();
}

inline void status::HaveBattleStatus::setIndex(int index)
{
    index_ = index;
}

inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus()
{
    return haveBattleStatus_;
}

inline void status::HaveBattleStatus::clearMulti()
{
    multi_ = 0;
}

inline int status::MonsterStatus::getMonsterIndex()
{
    return characterIndex_;
}

inline int status::HaveStatusInfo::getDrawCtrlId()
{
    return drawCtrlId_;
}

inline void btl::BattleActorManager::setDisableEscapeFlag(int flag)
{
    disableEscapeFlag_ = flag;
}

inline void btl::BattleEffectManager::setSpecialTarget(int index, int ctrlId, int anim)
{
    unit_[index].setSpecialTarget(ctrlId, anim);
}

inline void BattleMessage2::terminate()
{
}

inline void BattleMessage::terminate()
{
}

BattleMessage g_BattleMessage;
BattleMessage2 g_BattleMessage2;
BattleEffect g_BattleEffect;

bool cmd_battle_end_flag_set(void* scriptParam)
{
    PARAM_BATTLE_END_FLAG_SET* param = (PARAM_BATTLE_END_FLAG_SET*)scriptParam;
    if (param->type == 0) {
        btl::Encount::getSingleton()->forceBrew(param->tile);
    } else if (param->type == 1) {
        btl::Encount::getSingleton()->forceEventBrew(param->tile);
    }
    btl::gBattleScriptManager.setScriptBattleResult(param->winFlagType, param->winFlagIndex, 0);
    btl::gBattleScriptManager.setScriptBattleResult(param->loseFlagType, param->loseFlagIndex, 1);
    return true;
}

bool cmdEncount(void* scriptParam)
{
    PARAM_ENCOUNT* param = (PARAM_ENCOUNT*)scriptParam;
    if (param->type == 0) {
        btl::Encount::getSingleton()->forceBrew(param->tile);
    } else if (param->type == 1) {
        btl::Encount::getSingleton()->forceEventBrew(param->tile);
    }
    ScriptSystem::getSingleton()->setEnableExecute(false);
    return true;
}

bool cmd_encount_set_flag(void* scriptParam)
{
    PARAM_ENCOUNT_SET_FLAG* param = (PARAM_ENCOUNT_SET_FLAG*)scriptParam;
    if (param->type == 0) {
        btl::Encount::getSingleton()->forceBrew(param->tile);
    } else if (param->type == 1) {
        btl::Encount::getSingleton()->forceEventBrew(param->tile);
    }
    btl::gBattleScriptManager.setScriptBattleResult(param->flagType, param->index, 0);
    ScriptSystem::getSingleton()->setEnableExecute(false);
    return true;
}

bool cmd_disable_demolition()
{
    status::g_BattleResult.setDisablePlayerDemolition(true);
    return true;
}

bool cmd_set_encount_disable(void* scriptParam)
{
    PARAM_SET_ENCOUNT_DISABLE* param = (PARAM_SET_ENCOUNT_DISABLE*)scriptParam;
    bool flag = param->flag == 0 ? true : false;
    btl::Encount::getSingleton()->setEnable(flag);
    return true;
}

bool cmd_set_encount_stage_disable(void* scriptParam)
{
    PARAM_SET_ENCOUNT_STAGE_DISABLE* param = (PARAM_SET_ENCOUNT_STAGE_DISABLE*)scriptParam;
    bool flag = param->flag == 0 ? true : false;
    status::g_StageAttribute.setEncount(flag);
    return true;
}

bool cmd_is_battle_turn(void* scriptParam)
{
    PARAM_IS_BATTLE_TURN* param = (PARAM_IS_BATTLE_TURN*)scriptParam;
    int count = status::g_BattleResult.getBattleTurnCount();
    bool ret;
    if (param->flag == 0) {
        if (param->turn < count) {
            ret = true;
        } else {
            ret = false;
        }
    } else {
        if (param->turn >= count) {
            ret = true;
        } else {
            ret = false;
        }
    }
    return ret;
}

bool cmdGetBattleTransition(void* scriptParam)
{
    PARAM_GET_BATTLE_TRANSITION* param = (PARAM_GET_BATTLE_TRANSITION*)scriptParam;
    switch (param->status) {
    case 0:
        if (btl::BattleRoot::getSingleton()->isRoundEnd()) {
            return true;
        }
        break;
    case 1:
        if (btl::BattleRoot::getSingleton()->isMenuEnd()) {
            return true;
        }
        break;
    case 2:
        if (btl::BattleRoot::getSingleton()->isBattleStart()) {
            return true;
        }
        break;
    case 3:
        if (btl::BattleRoot::getSingleton()->isEncountMenuEnd()) {
            return true;
        }
        break;
    }
    return false;
}

bool cmdBattleSystemLock(void* scriptParam)
{
    PARAM_BATTLE_SYSTEM_LOCK* param = (PARAM_BATTLE_SYSTEM_LOCK*)scriptParam;
    btl::BattleRoot::getSingleton()->setExecuteEnable(param->flag);
    return true;
}

bool cmdBattlePartyAdd(void* scriptParam)
{
    PARAM_BATTLE_PARTY_ADD* param = (PARAM_BATTLE_PARTY_ADD*)scriptParam;
    status::g_Party.add(param->index, true);
    return true;
}

bool cmdBattlePartyReorder(void* scriptParam)
{
    PARAM_BATTLE_PARTY_REORDER* param = (PARAM_BATTLE_PARTY_REORDER*)scriptParam;
    int ctrl[4] = { -1, -1, -1, -1 };
    if (param->member1 != 4) {
        ctrl[0] = param->member1;
    }
    if (param->member2 != 4) {
        ctrl[1] = param->member2;
    }
    if (param->member3 != 4) {
        ctrl[2] = param->member3;
    }
    if (param->member4 != 4) {
        ctrl[3] = param->member4;
    }
    status::g_Party.reorder(ctrl[0], ctrl[1], ctrl[2], ctrl[3]);
    return true;
}

bool cmdBattleEnd(void* scriptParam)
{
    PARAM_BATTLE_END* param = (PARAM_BATTLE_END*)scriptParam;
    btl::BattleRoot::getSingleton()->setBattleEnd();
    switch (param->result) {
    case 0:
        status::g_BattleResult.setPlayerVictory(true);
        status::g_BattleResult.setPlayerDemolition(false);
        status::g_BattleResult.setDemolitionPartyTalk(false);
        break;
    case 1:
        status::g_BattleResult.setPlayerVictory(false);
        status::g_BattleResult.setPlayerDemolition(true);
        status::g_BattleResult.setDemolitionPartyTalk(true);
        break;
    }
    return true;
}

bool cmdIsBattleUseItem(void* scriptParam)
{
    PARAM_IS_BATTLE_USE_ITEM* param = (PARAM_IS_BATTLE_USE_ITEM*)scriptParam;
    return btl::BattleRoot::getSingleton()->isUseItem(param->item);
}

bool cmdSetBattleNpcMonsterIndex(void* scriptParam)
{
    PARAM_SET_BATTLE_NPC_MONSTER_INDEX* param = (PARAM_SET_BATTLE_NPC_MONSTER_INDEX*)scriptParam;
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (param->id == status::g_Party.getPlayerStatus(i).getPlayerIndex()) {
            status::g_Party.getPlayerStatus(i).getHaveBattleStatus().setIndex(param->monsterId);
            status::g_Party.getPlayerStatus(i).getHaveBattleStatus().setupMonster();
            status::g_Party.getPlayerStatus(i).getHaveBattleStatus().clearMulti();
        }
    }
    return true;
}

bool cmdSetBattleMonsterIndex(void* scriptParam)
{
    PARAM_SET_BATTLE_MONSTER_INDEX* param = (PARAM_SET_BATTLE_MONSTER_INDEX*)scriptParam;
    int count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        if (param->id == status::g_Monster.getMonsterStatus(i).getMonsterIndex()) {
            status::g_Monster.getMonsterStatus(i).changeMonsterWithHPMP(param->monsterId);
            break;
        }
    }
    return true;
}

bool cmdSetBattleMonsterAnimationIndex(void* scriptParam)
{
    PARAM_SET_BATTLE_MONSTER_ANIMATION_INDEX* param = (PARAM_SET_BATTLE_MONSTER_ANIMATION_INDEX*)scriptParam;
    int count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        if (param->id == status::g_Monster.getMonsterStatus(i).getMonsterIndex()) {
            status::MonsterStatus& monster = status::g_Monster.getMonsterStatus(i);
            btl::BattleMonsterDraw2::getSingleton().startAnimationWithLoop(monster.getHaveStatusInfo().getDrawCtrlId(), param->animId, param->loopFlag);
            break;
        }
    }
    return true;
}

bool cmdSetBattleMonsterLoopAnimationIndex(void* scriptParam)
{
    PARAM_SET_BATTLE_MONSTER_LOOP_ANIMATION_INDEX* param = (PARAM_SET_BATTLE_MONSTER_LOOP_ANIMATION_INDEX*)scriptParam;
    int count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        if (param->id == status::g_Monster.getMonsterStatus(i).getMonsterIndex()) {
            status::g_Monster.getMonsterStatus(i);
            break;
        }
    }
    return true;
}

bool cmdSetDisableEscape(void* scriptParam)
{
    PARAM_SET_DISABLE_ESCAPE* param = (PARAM_SET_DISABLE_ESCAPE*)scriptParam;
    if (param->flag != 0) {
        btl::BattleActorManager::getSingleton()->setDisableEscapeFlag(true);
    } else {
        btl::BattleActorManager::getSingleton()->setDisableEscapeFlag(false);
    }
    return true;
}

void BattleMessage::initialize(char* scriptParam)
{
    PARAM_BATTLE_MESSAGE* param = (PARAM_BATTLE_MESSAGE*)scriptParam;
    BattleAutoFeed::setCursor();
    BattleAutoFeed::setExecuteMessage();
    btl::BattleMessage::setMessage(param->message0, 0, 0, 0);
    BattleAutoFeed::setMessageSend();
    BattleAutoFeed::disableAutoFeed();
}

void BattleMessage::execute()
{
}

int BattleMessage::isEnd()
{
    if (BattleAutoFeed::isEndMessageSend()) {
        return true;
    }
    return false;
}

void BattleMessage2::initialize(char* scriptParam)
{
    PARAM_BATTLE_MESSAGE* param = (PARAM_BATTLE_MESSAGE*)scriptParam;
    BattleAutoFeed::setCursor();
    BattleAutoFeed::setExecuteMessage();
    btl::BattleMessage::setMessageNoSeqNum(param->message0, param->message1, param->message2, param->message3,
                                           param->message4, param->message5, param->message6, param->message7);
    BattleAutoFeed::setMessageSend();
    BattleAutoFeed::disableAutoFeed();
}

void BattleMessage2::execute()
{
}

int BattleMessage2::isEnd()
{
    if (BattleAutoFeed::isEndMessageSend()) {
        return true;
    }
    return false;
}

void BattleEffect::initialize(char* scriptParam)
{
    PARAM_BATTLE_EFFECT* param = (PARAM_BATTLE_EFFECT*)scriptParam;
    ctrlIndex_ = btl::BattleEffectManager::getSingleton()->setupEffect(param->effect);
    if (ctrlIndex_ >= 0) {
        btl::BattleEffectManager::getSingleton()->setSpecialTarget(ctrlIndex_, param->target, 1);
    }
}

void BattleEffect::execute()
{
}

int BattleEffect::isEnd()
{
    if (ctrlIndex_ < 0) {
        return true;
    }
    if (btl::BattleEffectManager::getSingleton()->isEnd()) {
        return true;
    }
    return false;
}

void BattleEffect::terminate()
{
}
