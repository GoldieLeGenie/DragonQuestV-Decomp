#include "ov000/btl/BattleSelectTargetParam.hpp"
#include "main/status/CharacterStatus.hpp"

inline int status::CharacterStatus::getGroupIndex() { return characterGroup_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }

THUMB btl::BattleSelectTargetParam::BattleSelectTargetParam()
{
    clear();
}

THUMB btl::BattleSelectTargetParam::~BattleSelectTargetParam()
{
}

THUMB void btl::BattleSelectTargetParam::clear()
{
    for (int i = 0; i < CHARACTER_MAX; i++) {
        sourceCharacterStatus[i] = NULL;
    }
    for (int i = 0; i < CHARACTER_MAX; i++) {
        targetCharacterStatus[i] = NULL;
    }
    sourceCount_ = 0;
    targetCount_ = 0;
    actionIndex_ = 0;
    targetGroup_ = -1;
    targetIndex_ = -1;
    callTarget_ = StartRound;
}

THUMB void btl::BattleSelectTargetParam::setSourceCharacterStatus(int index, status::CharacterStatus* characterStatus)
{
    sourceCharacterStatus[index] = characterStatus;
}

THUMB status::CharacterStatus* btl::BattleSelectTargetParam::getSourceCharacterStatus(int index)
{
    return sourceCharacterStatus[index];
}

THUMB int btl::BattleSelectTargetParam::getSourceGroup(int index)
{
    return sourceCharacterStatus[index]->getGroupIndex();
}

THUMB int btl::BattleSelectTargetParam::getSourceCountForGroup(int group)
{
    int count = 0;
    for (int i = 0; i < sourceCount_; i++) {
        if (group == sourceCharacterStatus[i]->getGroupIndex() && !sourceCharacterStatus[i]->getHaveStatusInfo().isDeath()) {
            count++;
        }
    }
    return count;
}

THUMB status::CharacterStatus* btl::BattleSelectTargetParam::getSourceCharacterStatusForGroup(int group, int index)
{
    int count = 0;
    for (int i = 0; i < sourceCount_; i++) {
        if (group == sourceCharacterStatus[i]->getGroupIndex() && !sourceCharacterStatus[i]->getHaveStatusInfo().isDeath()) {
            if (count == index) {
                return sourceCharacterStatus[i];
            }
            count++;
        }
    }
    return NULL;
}

THUMB int btl::BattleSelectTargetParam::getSourceCountForGroupDead(int group)
{
    int count = 0;
    for (int i = 0; i < sourceCount_; i++) {
        if (group == sourceCharacterStatus[i]->getGroupIndex()) {
            count++;
        }
    }
    return count;
}

THUMB status::CharacterStatus* btl::BattleSelectTargetParam::getSourceCharacterStatusForGroupDead(int group, int index)
{
    int count = 0;
    for (int i = 0; i < sourceCount_; i++) {
        if (group == sourceCharacterStatus[i]->getGroupIndex()) {
            if (count == index) {
                return sourceCharacterStatus[i];
            }
            count++;
        }
    }
    return NULL;
}

THUMB void btl::BattleSelectTargetParam::setTargetCharacterStatus(int index, status::CharacterStatus* characterStatus)
{
    targetCharacterStatus[index] = characterStatus;
}

THUMB status::CharacterStatus* btl::BattleSelectTargetParam::getTargetCharacterStatus(int index)
{
    return targetCharacterStatus[index];
}
