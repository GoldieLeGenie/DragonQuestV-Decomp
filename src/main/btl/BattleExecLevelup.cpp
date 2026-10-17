#include "main/btl/BattleExecLevelup.hpp"
#include "main/btl/BattleAutoFeed.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/text/TextAPI.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/HaveAction.hpp"
#include "main/status/UseAction.hpp"
#include "ov000/btl/BattleMessage.hpp"

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline ExecTaskManager::ExecTaskManager()
{
    flag_.clear();
}

inline ExecTaskManager::~ExecTaskManager()
{
}

inline void btl::BattleExecVictory10::setPlayerIndex(int index)
{
    index_ = index;
}

inline void btl::BattleExecVictory10::setLevel(int index)
{
    level_ = index;
}

inline void btl::BattleExecVictory11::setHpMax(int hp)
{
    hpMax_ = hp;
}

inline void btl::BattleExecVictory12::setMpMax(int mp)
{
    mpMax_ = mp;
}

inline void btl::BattleExecVictory12a::setPlayerIndex(int index)
{
    playerIndex_ = index;
}

inline void btl::BattleExecVictory13::setStatus(int st, int ag, int pr, int ws, int lk)
{
    strength_ = st;
    agility_ = ag;
    protection_ = pr;
    wisdom_ = ws;
    luck_ = lk;
}

inline void btl::BattleExecVictory15::setPlayerIndex(int playerIndex)
{
    playerIndex_ = playerIndex;
}

inline void btl::BattleExecVictory15::setActionIndex(int index, int actionIndex)
{
    actionIndex_[index] = actionIndex;
}

btl::BattleExecLevelup btl::g_BattleExecLevelup;

THUMB void btl::setMessage(int mes0, int mes1, int mes2, int mes3)
{
    if (data_02101c88.unkfunc_02051810() == 5) {
        BattleMessage::setMessage(mes0, mes1, mes2, mes3);
        return;
    }
    MenuAPI::openMessageWindowMenu();
    if (mes0 != 0) {
        MenuAPI::addMessageSerial(mes0);
    }
    if (mes1 != 0) {
        MenuAPI::addMessageSerial(mes1);
    }
    if (mes2 != 0) {
        MenuAPI::addMessageSerial(mes2);
    }
    if (mes3 != 0) {
        MenuAPI::addMessageSerial(mes3);
    }
}

THUMB void btl::BattleExecVictory10::setup()
{
    TextAPI::setMACRO0(0x12, 0x50000000, index_);
    TextAPI::setMACRO0(0x50, 0xf0000000, level_);
    setMessage(0xc3c96, 0, 0, 0);
    BattleAutoFeed::setMessageSend();
}

THUMB void btl::BattleExecVictory11::setup()
{
    if (hpMax_ != 0) {
        TextAPI::setMACRO0(0x4d, 0xf0000000, hpMax_);
        setMessage(0xc3c98, 0, 0, 0);
        BattleAutoFeed::setMessageSend();
    }
}

THUMB void btl::BattleExecVictory12::setup()
{
    if (mpMax_ != 0) {
        TextAPI::setMACRO0(0x51, 0xf0000000, mpMax_);
        setMessage(0xc3c9a, 0, 0, 0);
        BattleAutoFeed::setMessageSend();
    }
}

THUMB void btl::BattleExecVictory12a::setup()
{
    TextAPI::setMACRO0(0x12, 0x50000000, playerIndex_);
    setMessage(0xc3c9c, 0, 0, 0);
    BattleAutoFeed::setMessageSend();
}

THUMB void btl::BattleExecVictory13::setup()
{
    TextAPI::setMACRO1(0x52, 0xf0000000, strength_);
    TextAPI::setMACRO2(0x52, 0xf0000000, agility_);
    TextAPI::setMACRO3(0x52, 0xf0000000, protection_);
    TextAPI::setMACRO4(0x52, 0xf0000000, wisdom_);
    TextAPI::setMACRO5(0x52, 0xf0000000, luck_);
    if (status::HaveAction::isBattleMode()) {
        setMessage(0xc3c9e, 0, 0, 0);
    } else {
        setMessage(0xc3da9, 0, 0, 0);
    }
    BattleAutoFeed::setMessageSend();
}

THUMB void btl::BattleExecVictory15::setup()
{
    TextAPI::setMACRO0(0x12, 0x50000000, playerIndex_);
    int word = status::UseAction::getWordDBIndex(actionIndex_[0]);
    TextAPI::setMACRO0(0x11, 0x70000000, word);
    TextAPI::setMACRO0(0, 0x70000000, word);
    switch (status::UseAction::getActionType(actionIndex_[0])) {
        case dq5::level::ActionParam::KIND_BATTLE_MAGIC:
        case dq5::level::ActionParam::KIND_NORMAL_MAGIC:
            setMessage(0xc3ca0, 0, 0, 0);
            break;
        case dq5::level::ActionParam::KIND_BATTLE_SKILL:
        case dq5::level::ActionParam::KIND_NORMAL_SKILL:
            setMessage(0xc3ca2, 0, 0, 0);
            break;
    }
    BattleAutoFeed::setMessageSend();
    index_ = 1;
}

THUMB void btl::BattleExecVictory15::exec()
{
    if (isEnd()) {
        if (actionIndex_[index_] != 0) {
            int word = status::UseAction::getWordDBIndex(actionIndex_[index_]);
            index_++;
            TextAPI::setMACRO0(0x12, 0x50000000, playerIndex_);
            TextAPI::setMACRO0(0x11, 0x70000000, word);
            TextAPI::setMACRO0(0, 0x70000000, word);
            setMessage(0xc3ca0, 0, 0, 0);
        } else {
            terminate();
        }
    }
}

THUMB void btl::BattleExecVictory16::setup()
{
    if (status::PartyStatusUtility::getLevelupPlayer() != -1) {
        counter_ = 1;
        SoundManager::interrupt_ = 1;
        SoundManager::playBgm(0x2a, 0);
    } else {
        counter_ = 0xb4;
    }
}

THUMB bool btl::BattleExecVictory16::isEnd()
{
    if (counter_ > 0xb4) {
        return true;
    }
    counter_++;
    return false;
}

THUMB void btl::BattleExecLevelup::initialize()
{
    ExecTaskManager::initialize();
    int index = status::PartyStatusUtility::getLevelupPlayer();
    status::g_Party.getPlayerStatus(index).haveStatusInfo_.levelup(0);
    status::g_Party.getPlayerStatus(index).haveStatusInfo_.haveStatus_.getDiffStatus();
    battleExecVictory10.setPlayerIndex(status::g_Party.getPlayerStatus(index).haveStatusInfo_.haveStatus_.getPlayerIndex());
    battleExecVictory10.setLevel(status::g_Party.getPlayerStatus(index).haveStatusInfo_.haveStatus_.level_);
    int action = status::g_Party.getPlayerStatus(index).haveStatusInfo_.haveAction_.getRememberingAction();
    resister(0, &battleExecVictory10);
    resister(1, &battleExecVictory11);
    resister(2, &battleExecVictory12);
    resister(3, &battleExecVictory12a);
    resister(4, &battleExecVictory13);
    resister(5, &battleExecVictory15);
    int playerIndex = status::g_Party.getPlayerStatus(index).haveStatusInfo_.haveStatus_.getPlayerIndex();
    const status::BaseStatus& diffStatus = status::g_Party.getPlayerStatus(index).haveStatusInfo_.haveStatus_.getDiffStatus();
    battleExecVictory11.setHpMax(diffStatus.hpMax_);
    battleExecVictory12.setMpMax(diffStatus.mpMax_);
    battleExecVictory12a.setPlayerIndex(playerIndex);
    battleExecVictory13.setStatus(diffStatus.strength_, diffStatus.agility_, diffStatus.protection_, diffStatus.wisdom_, diffStatus.luck_);
    if (action != 0) {
        resister(5, &battleExecVictory15);
        resister(6, &battleExecVictory16);
        battleExecVictory15.setPlayerIndex(playerIndex);
        battleExecVictory15.setActionIndex(0, action);
        battleExecVictory15.setActionIndex(1, status::g_Party.getPlayerStatus(index).haveStatusInfo_.haveAction_.getRememberingAction());
        battleExecVictory15.setActionIndex(4, 0);
    } else {
        resister(5, &battleExecVictory16);
    }
}

inline status::BaseStatus& status::HaveStatus::getDiffStatus()
{
    return diffStatus_;
}

THUMB void btl::BattleExecLevelup::terminate()
{
    ExecTaskManager::terminate();
}

THUMB btl::BattleExecLevelup::~BattleExecLevelup()
{
}
