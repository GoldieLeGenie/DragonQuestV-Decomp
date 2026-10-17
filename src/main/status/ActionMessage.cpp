#include "main/status/ActionMessage.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/GameFlag.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "main/menu/StadiumData.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "ov000/status/MonsterParty.hpp"

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline bool StadiumData::isStadiumBattle()
{
    return stadiumFlag_;
}

inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index) { return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned long dq5::level::ActionParam::getActionMes() { return actionMes; }
inline unsigned long dq5::level::ActionParam::getPlayerSuccess() { return playerSuccess; }
inline unsigned long dq5::level::ActionParam::getMonsterSuccess() { return monsterSuccess; }
inline unsigned long dq5::level::ActionParam::getPlayerFailed() { return playerFailed; }
inline unsigned long dq5::level::ActionParam::getMonsterFailed() { return monsterFailed; }
inline unsigned long dq5::level::ActionParam::getEndMes() { return endMes; }

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline int status::HaveBattleStatus::getSelectItemIndex() { return selectItemIndex_; }
inline int status::PlayerStatus::getPlayerIndex() { return getHaveStatusInfo().getHaveStatus().getPlayerIndex(); }
inline void status::UseActionMessage::setExecMessage(int index, int message) { execMessage_[index] = message; }
inline void status::UseActionMessage::setResultMessage(int index, int message) { resultMessage_[index] = message; }
inline int status::UseActionMessage::getResultMessage(int index) { return resultMessage_[index]; }
inline void status::UseActionMessage::setAddMessage(int index, int message) { addMessage_[index] = message; }
inline unsigned char StadiumData::getBetArray() { return monsterArray_; }
inline void StadiumData::betDeathON() { monsterDeath_ = true; }

namespace status {
static dq5::level::ActionParam* actionParam2_;

static THUMB void getRecord(int index)
{
    actionParam2_ = dq5::level::ActionParam::getRecord(index);
}
}

int status::ActionMessage::instantDeath_;

THUMB void status::ActionMessage::setExecMessage(int actionIndex, UseActionMessage& useActionMessage)
{
    useActionMessage.setExecMessage(0, getExecMessage(actionIndex, 0));
    useActionMessage.setExecMessage(1, getExecMessage(actionIndex, 1));
    useActionMessage.setExecMessage(2, getExecMessage(actionIndex, 2));
    useActionMessage.setExecMessage(3, getExecMessage(actionIndex, 3));
}

THUMB void status::ActionMessage::setResultMessage(int actionIndex, CharacterStatus& characterStatus, UseActionMessage& useActionMessage, int result)
{
    useActionMessage.setResultMessage(0, getResultMessage(actionIndex, characterStatus.getCharacterType(), result));
    if (useActionMessage.getResultMessage(0) == 0xc41ed) {
        useActionMessage.setExecMessage(0, 0xc41ed);
        useActionMessage.setResultMessage(0, 0);
        return;
    }
    if (characterStatus.getCharacterType() == MONSTER && characterStatus.getHaveStatusInfo().isDeath() && data_02101c88.unkfunc_02051818(dq5::BATTLE_PART)) {
        int maxCount = g_Monster.getCount();
        int index = 0;
        for (int i = 0; i < maxCount; i++) {
            if (&g_Monster.getMonsterStatus(i) == &characterStatus) {
                index = i;
            }
        }
        if (g_StadiumData.isStadiumBattle()) {
            if (index == g_StadiumData.getBetArray()) {
                g_StadiumData.betDeathON();
            }
        } else {
            g_Monster.checkDropItemMonster(index);
        }
    }
    if (instantDeath_) {
        int message = 0;
        if (characterStatus.getHaveStatusInfo().isDeath()) {
            if (characterStatus.getCharacterType() == PLAYER) {
                message = 0xc3926;
                if (g_Story.getChapter() == 1) {
                    message = 0xc3924;
                }
            }
            if (characterStatus.getCharacterType() == MONSTER) {
                message = 0xc391f;
                if (characterStatus.isDeathDisable()) {
                    message = 0;
                }
            }
        }
        if (message) {
            useActionMessage.setResultMessage(0, message);
        }
    }
}

THUMB int status::ActionMessage::getExecMessage(int actionIndex, int index)
{
    getRecord(actionIndex);
    if (index == 0) {
        return actionParam2_->getActionMes();
    } else if (index == 1) {
        return 0;
    } else if (index == 2) {
        return 0;
    } else if (index == 3) {
        return 0;
    } else {
        return 0;
    }
}

THUMB int status::ActionMessage::getResultMessage(int actionIndex, CharacterType type, int result)
{
    if (result) {
        return getResultSuccessMessage(actionIndex, type);
    }
    return getResultFailedMessage(actionIndex, type);
}

THUMB int status::ActionMessage::getResultSuccessMessage(int actionIndex, CharacterType type)
{
    int message;
    getRecord(actionIndex);
    if (type == PLAYER) {
        message = actionParam2_->getPlayerSuccess();
    } else {
        message = actionParam2_->getMonsterSuccess();
    }
    return message;
}

THUMB int status::ActionMessage::getResultFailedMessage(int actionIndex, CharacterType type)
{
    int message;
    getRecord(actionIndex);
    if (type == PLAYER) {
        message = actionParam2_->getPlayerFailed();
    } else {
        message = actionParam2_->getMonsterFailed();
    }
    return message;
}

THUMB int status::ActionMessage::getFinishMessage(int actionIndex)
{
    int message;
    getRecord(actionIndex);
    message = actionParam2_->getEndMes();
    return message;
}

THUMB void status::ActionMessage::setExecMessage(UseActionMessage& useActionMessage, int mes0, int mes1, int mes2, int mes3)
{
    if (mes0) {
        useActionMessage.setExecMessage(0, mes0);
    }
    if (mes1) {
        useActionMessage.setExecMessage(1, mes1);
    }
    if (mes2) {
        useActionMessage.setExecMessage(2, mes2);
    }
    if (mes3) {
        useActionMessage.setExecMessage(3, mes3);
    }
}

THUMB void status::ActionMessage::setResultMessage(UseActionMessage& useActionMessage, int mes0, int mes1)
{
    useActionMessage.setResultMessage(0, mes0);
    useActionMessage.setResultMessage(1, mes1);
}

THUMB void status::ActionMessage::setAddMessage(UseActionMessage& useActionMessage, int mes0, int mes1)
{
    useActionMessage.setAddMessage(0, mes0);
    if (mes1) {
        useActionMessage.setAddMessage(1, mes1);
    }
}

THUMB void status::ActionMessage::setMessageNotEnoughMp(int actionIndex, UseActionMessage& useActionMessage)
{
    useActionMessage.setExecMessage(0, getExecMessage(actionIndex, 0));
    useActionMessage.setExecMessage(1, getExecMessage(actionIndex, 1));
    useActionMessage.setExecMessage(2, getExecMessage(actionIndex, 2));
    useActionMessage.setExecMessage(3, getExecMessage(actionIndex, 3));
    useActionMessage.setResultMessage(0, 0xc393e);
    useActionMessage.setResultMessage(1, 0);
}

THUMB void status::ActionMessage::setExecMessageAdd(int actionIndex, UseActionMessage& useActionMessage)
{
    if (actionIndex == 0x229) {
        useActionMessage.setExecMessage(1, 0xc3ac4);
    }
}

THUMB void status::ActionMessage::setExecMessageAdd(UseActionParam* useActionParam)
{
    CharacterStatus* actor = useActionParam->actorCharacterStatus_;
    if (g_GlobalFlag.check(0x190) && ((PlayerStatus*)actor)->getPlayerIndex() != 1 && actor->getHaveBattleStatus().getSelectCommand() == 3) {
        int itemIndex = actor->getHaveBattleStatus().getSelectItemIndex();
        if (itemIndex == 0x9a) {
            useActionParam->message_[0].setExecMessage(0, 0x20df);
        }
    }
}
