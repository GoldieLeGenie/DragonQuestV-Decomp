#pragma ipa file
#include "main/status/HaveAction.hpp"
#include "main/status/HaveStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/dss/DssUtils.hpp"

inline unsigned short dq5::level::PlayerData1::getBattleAction1()
{
    return battleAction1;
}

inline unsigned short dq5::level::PlayerData1::getBattleAction2()
{
    return battleAction2;
}

inline unsigned short dq5::level::PlayerData1::getBattleAction3()
{
    return battleAction3;
}

inline unsigned short dq5::level::PlayerData1::getBattleAction4()
{
    return battleAction4;
}

inline unsigned short dq5::level::PlayerData1::getNormalAction1()
{
    return normalAction1;
}

inline unsigned short dq5::level::PlayerData1::getNormalAction2()
{
    return normalAction2;
}

inline unsigned short dq5::level::PlayerData1::getNormalAction3()
{
    return normalAction3;
}

inline unsigned short dq5::level::PlayerData1::getNormalAction4()
{
    return normalAction4;
}

status::HaveAction::ActionMode status::HaveAction::mode_;
int status::HaveAction::addRulaLevel_;
int status::HaveAction::addParupunteLevel_;

inline status::PlayerData& status::PlayerDataAll::getPlayerData(int index)
{
    return playerData_[index];
}

inline int status::PlayerData::getKindIndex()
{
    return kindIndex_;
}

inline status::HaveAction& status::PlayerData::getHaveAction()
{
    return haveAction_;
}

inline void status::PlayerData::setHaveAction(HaveAction& action)
{
    haveAction_ = action;
}


THUMB status::HaveAction::HaveAction()
{
    clear();
}

THUMB status::HaveAction::~HaveAction()
{
}

THUMB void status::HaveAction::setBattleMode()
{
    mode_ = BattleMode;
}

THUMB bool status::HaveAction::isBattleMode()
{
    return mode_ == BattleMode;
}

THUMB void status::HaveAction::setTownMode()
{
    mode_ = TownMode;
}

THUMB bool status::HaveAction::isTownMode()
{
    return mode_ == TownMode;
}

THUMB status::HaveAction::ActionMode status::HaveAction::getActionMode()
{
    return mode_;
}

THUMB void status::HaveAction::setActionMode(ActionMode md)
{
    mode_ = md;
}

THUMB void status::HaveAction::setup(int index, int level)
{
    clear();
    PlayerData& playerData = PlayerDataAll::getPlayerData(index);
    *this = playerData.getHaveAction();
    index_ = index;
    kind_ = playerData.getKindIndex();
}

THUMB void status::HaveAction::cleanup(int index)
{
    PlayerData& playerData = PlayerDataAll::getPlayerData(index);
    playerData.setHaveAction(*this);
}

THUMB void status::HaveAction::clear()
{
    for (int i = 0; i < ACTION_MAX; i++) {
        action_[i].clear();
    }
    level_ = 0;
}

THUMB void status::HaveAction::execLevelup(int level, bool flag)
{
    if (level == level_) {
        return;
    }
    int tempLevel = dss::clamp<int>(level_ + 1, 1, 99);
    do {
        dq5::level::PlayerData1* playerData = HaveStatus::getLevelupData(kind_, tempLevel);
        if (playerData->getBattleAction1() != 0 || playerData->getNormalAction1() != 0) {
            level_ = tempLevel;
            add(playerData->getBattleAction1(), playerData->getNormalAction1(), flag);
            if (playerData->getBattleAction2() != 0 || playerData->getNormalAction2() != 0) {
                add(playerData->getBattleAction2(), playerData->getNormalAction2(), flag);
            }
            if (playerData->getBattleAction3() != 0 || playerData->getNormalAction3() != 0) {
                add(playerData->getBattleAction3(), playerData->getNormalAction3(), flag);
            }
            if (playerData->getBattleAction4() != 0 || playerData->getNormalAction4() != 0) {
                add(playerData->getBattleAction4(), playerData->getNormalAction4(), flag);
            }
            if (index_ == 1) {
                if (level_ == addRulaLevel_) {
                    add(0, 0x81, false);
                }
                if (level_ == addParupunteLevel_) {
                    add(0x42, 0, false);
                }
            }
        }
        tempLevel++;
    } while (tempLevel <= level);
}

THUMB void status::HaveAction::debugLevelup(int level)
{
    execLevelup(level, true);
}

THUMB void status::HaveAction::loadLevelup(int level, int rulaLevel, int parupunteLevel)
{
    clear();
    addRulaLevel_ = rulaLevel;
    addParupunteLevel_ = parupunteLevel;
    execLevelup(level, true);
    clearRememberingAction();
}

THUMB void status::HaveAction::levelup(int index, int level, bool flag)
{
    execLevelup(level, false);
}

THUMB void status::HaveAction::add(int battleAction, int usuallyAction, bool flag)
{
    if (index_ == 1 && usuallyAction == 0x81) {
        addRulaLevel_ = level_;
        flag = true;
    }
    if (index_ == 1 && battleAction == 0x42) {
        addParupunteLevel_ = level_;
        flag = true;
    }
    for (int i = 0; i < ACTION_MAX; i++) {
        if (!action_[i].isEnable()) {
            action_[i].add(battleAction, usuallyAction);
            if (!flag) {
                action_[i].remembering();
            }
            return;
        }
    }
}

THUMB int status::HaveAction::getAction(int index)
{
    if (isTownMode()) {
        int count = 0;
        for (int i = 0; i < ACTION_MAX; i++) {
            if (action_[i].getUsuallyAction() != ACTION_NONE) {
                if (count == index) {
                    return action_[i].getUsuallyAction();
                }
                count++;
            }
        }
    } else {
        int count = 0;
        for (int i = 0; i < ACTION_MAX; i++) {
            if (action_[i].getAction() != ACTION_NONE) {
                if (count == index) {
                    return action_[i].getAction();
                }
                count++;
            }
        }
    }
    return ACTION_NONE;
}

THUMB int status::HaveAction::getCount()
{
    int count = 0;
    for (int i = 0; i < ACTION_MAX; i++) {
        if (action_[i].isRemember()) {
            if (mode_ == TownMode && action_[i].getUsuallyAction() != ACTION_NONE) {
                count++;
            }
            if (mode_ == BattleMode && action_[i].getAction() != ACTION_NONE) {
                count++;
            }
        }
    }
    return count;
}

THUMB int status::HaveAction::getCountAll()
{
    int count = 0;
    for (int i = 0; i < ACTION_MAX; i++) {
        if (action_[i].isEnable()) {
            count++;
        }
    }
    return count;
}

THUMB int status::HaveAction::getActionAll(int index)
{
    int count = 0;
    for (int i = 0; i < ACTION_MAX; i++) {
        if (action_[i].getUsuallyAction() != ACTION_NONE) {
            if (count == index) {
                return action_[i].getUsuallyAction();
            }
            count++;
        } else {
            if (count == index) {
                return action_[i].getAction();
            }
            count++;
        }
    }
    return ACTION_NONE;
}

THUMB bool status::HaveAction::isAction(int actionIndex)
{
    int count = getCount();
    for (int i = 0; i < count; i++) {
        if (actionIndex == getAction(i)) {
            return true;
        }
    }
    return false;
}

THUMB int status::HaveAction::getRememberingAction()
{
    for (int i = 0; i < ACTION_MAX; i++) {
        if (action_[i].isRemembering()) {
            action_[i].clearRemembering();
            if (action_[i].getAction() != ACTION_NONE) {
                return action_[i].getAction();
            }
            if (action_[i].getUsuallyAction() != ACTION_NONE) {
                return action_[i].getUsuallyAction();
            }
        }
    }
    return ACTION_NONE;
}

THUMB void status::HaveAction::clearRememberingAction()
{
    for (int i = 0; i < ACTION_MAX; i++) {
        if (action_[i].isRemembering()) {
            action_[i].clearRemembering();
        }
    }
}
