#pragma ipa file
#include "main/script/ScriptPartyCommand.hpp"
#include "main/script/CommandParam.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/text/TextAPI.hpp"

#pragma thumb on

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline status::HaveItem& status::HaveStatusInfo::getHaveItem()
{
    return haveItem_;
}

inline bool status::HaveStatus::isFriendMonster() const
{
    return playerType_ == TYPE_FRIENDMONSTER;
}

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatusInfo::getPlayerIndex() const
{
    return haveStatus_.getPlayerIndex();
}

inline int status::PlayerData::getKindIndex()
{
    return kindIndex_;
}

inline int status::PlayerStatus::getCharaIndex()
{
    return haveStatusInfo_.getHaveStatus().getCharaIndex();
}

inline char status::MenuStatus::getInnCount()
{
    return innCount_;
}

bool cmd_is_party_all(void* scriptParam)
{
    PARAM_IS_PARTY_ALL* param = (PARAM_IS_PARTY_ALL*)scriptParam;
    status::g_Party.setPlayerMode();
    unsigned int checkIndex[4];
    checkIndex[0] = param->index0;
    checkIndex[1] = param->index1;
    checkIndex[2] = param->index2;
    checkIndex[3] = param->index3;
    int checkResult[4] = {true};
    for (int i = 0; i < 4; i++) {
        checkResult[i] = true;
    }
    bool result = false;
    int carriageOut = status::g_Party.getCarriageOutCount();
    int targetCount = 0;
    for (int i = 0; i < 4; i++) {
        if (checkIndex[i] != 0) {
            targetCount++;
        }
    }
    if (targetCount == 0) {
        for (int i = 0; i < carriageOut; i++) {
            checkIndex[i] = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getPlayerIndex();
        }
        targetCount = carriageOut;
    }
    switch (param->criterion) {
    case 0:
        for (int i = 0; i < targetCount; i++) {
            if (checkIndex[i] < 16) {
                int index = status::g_Party.getSortIndex(checkIndex[i]);
                if (index != -1 && index < carriageOut) {
                    result = true;
                    break;
                }
            } else {
                for (int j = 0; j < carriageOut; j++) {
                    int playerIndex = status::g_Party.getPlayerStatus(j).getHaveStatusInfo().getPlayerIndex();
                    if (checkIndex[i] == status::PlayerDataAll::playerData_[playerIndex].getKindIndex()) {
                        result = true;
                        break;
                    }
                }
            }
            if (result == true) {
                break;
            }
        }
        break;
    case 1:
        result = true;
        for (int i = 0; i < targetCount; i++) {
            if (checkIndex[i] < 16) {
                int index = status::g_Party.getSortIndex(checkIndex[i]);
                if (index == -1 || index >= carriageOut) {
                    result = false;
                    break;
                }
            } else {
                bool findMonster = false;
                for (int j = 0; j < carriageOut; j++) {
                    int playerIndex = status::g_Party.getPlayerStatus(j).getHaveStatusInfo().getPlayerIndex();
                    if (checkIndex[i] == status::PlayerDataAll::playerData_[playerIndex].getKindIndex()) {
                        findMonster = true;
                        break;
                    }
                }
                if (findMonster == false) {
                    result = false;
                    break;
                }
            }
        }
        break;
    case 2:
        int checkCount = 0;
        for (int i = 0; i < targetCount; i++) {
            for (int j = 0; j < carriageOut; j++) {
                if (checkIndex[i] < 16) {
                    if (checkIndex[i] == status::g_Party.getPlayerStatus(j).getHaveStatusInfo().getPlayerIndex()) {
                        checkCount++;
                        break;
                    }
                } else {
                    int playerIndex = status::g_Party.getPlayerStatus(j).getHaveStatusInfo().getPlayerIndex();
                    if (checkIndex[i] == status::PlayerDataAll::playerData_[playerIndex].getKindIndex()) {
                        checkCount++;
                        break;
                    }
                }
            }
        }
        if (targetCount == checkCount) {
            result = true;
        }
        break;
    }
    if (result == false) {
        return false;
    }
    if (param->sex == 0 && param->condition == 0) {
        return true;
    }
    for (int i = 0; i < targetCount; i++) {
        status::HaveStatusInfo* statusInfo = 0;
        if (checkIndex[i] < 16) {
            statusInfo = &status::g_Party.getPlayerStatusForPlayerIndex(checkIndex[i]).getHaveStatusInfo();
        } else {
            for (int j = 0; j < carriageOut; j++) {
                int playerIndex = status::g_Party.getPlayerStatus(j).getHaveStatusInfo().getPlayerIndex();
                if (checkIndex[i] == status::PlayerDataAll::playerData_[playerIndex].getKindIndex()) {
                    statusInfo = &status::g_Party.getPlayerStatusForPlayerIndex(j).getHaveStatusInfo();
                    break;
                }
            }
        }
        if (param->sex != 0) {
            int checkSex = 0;
            if (param->sex == 2) {
                checkSex = 1;
            }
            if (checkSex == statusInfo->getHaveStatus().getSex()) {
                checkResult[i] = true;
            } else {
                checkResult[i] = false;
            }
        }
        if (param->condition != 0) {
            if (param->condition == 1) {
                checkResult[i] = !statusInfo->isDeath();
            }
            if (param->condition == 2) {
                checkResult[i] = statusInfo->isDeath();
            }
        }
    }
    for (int i = 0; i < targetCount; i++) {
        if (checkResult[i] == true && param->andor == 1) {
            return true;
        }
        if (checkResult[i] == false && param->andor == 0) {
            return false;
        }
    }
    if (param->andor == 0) {
        return true;
    }
    return false;
}

bool cmd_is_not_party_all(void* scriptParam)
{
    bool ret = cmd_is_party_all(scriptParam);
    if (ret == false) {
        return true;
    }
    return false;
}

bool cmd_check_inn_count(void* scriptParam)
{
    PARAM_CHECK_INN_COUNT* param = (PARAM_CHECK_INN_COUNT*)scriptParam;
    int innCount = status::g_Menu.getInnCount();
    if (param->flag == 1) {
        if (innCount >= param->count) {
            return true;
        }
    } else {
        if (innCount <= param->count) {
            return true;
        }
    }
    return false;
}

bool cmd_party_add_npc(void* scriptParam)
{
    PARAM_PARTY_ADD_NPC* param = (PARAM_PARTY_ADD_NPC*)scriptParam;
    status::g_Party.addNpc(param->charNo);
    cmn::GameManager::getSingleton().resetParty();
    return true;
}

bool cmd_party_del_npc(void* scriptParam)
{
    PARAM_PARTY_DEL_NPC* param = (PARAM_PARTY_DEL_NPC*)scriptParam;
    status::g_Party.setAllPlayerMode();
    int count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (param->charNo == status::g_Party.getPlayerStatus(i).getCharaIndex()) {
            status::g_Party.del(i);
            break;
        }
    }
    cmn::GameManager::getSingleton().resetParty();
    return true;
}

bool cmdCheckAllPlayerCount(void* scriptParam)
{
    status::g_Party.setPlayerMode();
    if (status::g_Party.getCount() < 8) {
        return false;
    }
    if (status::PlayerDataAll::getMonsterCountInOldMan() >= 80) {
        return true;
    }
    return false;
}

bool cmdSetPartyQuitToAzuke(void* scriptParam)
{
    PARAM_SET_PARTY_QUIT_TO_AZUKE* param = (PARAM_SET_PARTY_QUIT_TO_AZUKE*)scriptParam;
    status::g_Party.setAllPlayerMode();
    int playerIndex, active;
    if (param->flag == 0) {
        active = status::g_Party.getSortIndex(param->index);
        if (active == -1) {
            return true;
        }
        playerIndex = param->index;
    } else {
        playerIndex = param->index;
        if (status::g_Party.getCount() < (unsigned int)(active = playerIndex - 1)) {
            return true;
        }
        playerIndex = status::g_Party.getPlayerStatus(active).getHaveStatusInfo().getPlayerIndex();
    }
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(active).getHaveStatusInfo();
    if (statusInfo.getHaveStatus().isFriendMonster()) {
        status::PlayerDataAll::setMonsterOldManFlag(playerIndex, true);
    } else {
        status::PlayerDataAll::setRuidaFlag(playerIndex, true);
    }
    int itemCount = statusInfo.getHaveItem().getCount();
    int equipCount = 0;
    for (int i = 0; i < itemCount; i++) {
        if (statusInfo.getHaveItem().isEquipment(i) == true) {
            equipCount++;
        }
    }
    for (int i = 0; i < itemCount - equipCount; i++) {
        status::g_Party.haveItemSack_.add(statusInfo.getHaveItem().getItem(equipCount));
        statusInfo.execThrow(equipCount);
    }
    TextAPI::setMACRO0(0x12, 0x50000000, status::g_Party.getPlayerStatus(active).getHaveStatusInfo().getPlayerIndex());
    status::g_Party.del(active);
    cmn::GameManager::getSingleton().resetParty();
    return true;
}

bool cmdSetHeadChara(void* scriptParam)
{
    PARAM_SET_HEAD_CHARA* param = (PARAM_SET_HEAD_CHARA*)scriptParam;
    status::g_Party.setBattleModeAndCarriage();
    int reorderChara[4] = {-1};
    for (int i = 0; i < 4; i++) {
        reorderChara[i] = -1;
    }
    int carriageOut = status::g_Party.getCarriageOutCount();
    int index = status::g_Party.getSortIndex(param->index);
    if (index == -1) {
        return true;
    }
    int count = 1;
    reorderChara[0] = index;
    for (int i = 0; i < carriageOut; i++) {
        if (reorderChara[0] != i) {
            reorderChara[count] = i;
            count++;
            if (count >= carriageOut) {
                break;
            }
        }
    }
    status::g_Party.reorder(reorderChara[0], reorderChara[1], reorderChara[2], reorderChara[3]);
    cmn::GameManager::getSingleton().resetParty();
    return true;
}

bool cmdReturnInCarriage(void* scriptParam)
{
    PARAM_RETURN_IN_CARRIAGE* param = (PARAM_RETURN_IN_CARRIAGE*)scriptParam;
    status::g_Party.setBattleModeAndCarriage();
    int reorderMember[4] = {-1};
    for (int i = 0; i < 4; i++) {
        reorderMember[i] = -1;
    }
    int carriageOutCount = status::g_Party.getCarriageOutCount();
    int count = 0;
    switch (param->flag) {
    case 0:
        if (param->index == 1) {
            return true;
        }
        for (int i = 0; i < carriageOutCount; i++) {
            status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
            if (statusInfo.getHaveStatus().isFriendMonster()) {
                if (param->index != status::PlayerDataAll::playerData_[statusInfo.getPlayerIndex()].getKindIndex()) {
                    reorderMember[count] = i;
                    count++;
                }
            } else if (param->index != statusInfo.getPlayerIndex()) {
                reorderMember[count] = i;
                count++;
            }
        }
        break;
    case 1:
        int active = param->index - 1;
        if (active >= carriageOutCount) {
            return true;
        }
        for (int i = 0; i < carriageOutCount; i++) {
            if (i != active) {
                reorderMember[count] = i;
                count++;
            }
        }
        break;
    case 2:
        for (int i = 0; i < carriageOutCount; i++) {
            status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
            if (statusInfo.getHaveStatus().isFriendMonster() || statusInfo.getPlayerIndex() == 1) {
                reorderMember[count] = i;
                count++;
            }
        }
        break;
    case 3:
        for (int i = 0; i < carriageOutCount; i++) {
            if (!status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().isFriendMonster()) {
                reorderMember[count] = i;
                count++;
            }
        }
        break;
    }
    if (reorderMember[0] == -1) {
        reorderMember[0] = status::g_Party.getSortIndex(1);
    }
    status::g_Party.reorder(reorderMember[0], reorderMember[1], reorderMember[2], reorderMember[3]);
    cmn::GameManager::getSingleton().resetParty();
    return true;
}

bool cmdSortPartyKind(void* scriptParam)
{
    PARAM_SORT_PARTY_KIND* param = (PARAM_SORT_PARTY_KIND*)scriptParam;
    status::g_Party.setBattleModeAndCarriage();
    int partyCount = status::g_Party.getCount();
    status::g_Party.getCarriageOutCount();
    int human[8] = {-1};
    for (int i = 0; i < 8; i++) {
        human[i] = -1;
    }
    int monster[8] = {-1};
    for (int i = 0; i < 8; i++) {
        monster[i] = -1;
    }
    int reorderMember[4] = {-1};
    for (int i = 0; i < 4; i++) {
        reorderMember[i] = -1;
    }
    int humanCount = 0, monsterCount = 0, reorderCount = 0;
    int heroIndex = status::g_Party.getSortIndex(1);
    for (int i = 0; i < partyCount; i++) {
        status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
        if (statusInfo.getPlayerIndex() == 1) {
            continue;
        }
        if (statusInfo.getHaveStatus().isFriendMonster()) {
            monster[monsterCount] = i;
            monsterCount++;
        } else {
            human[humanCount] = i;
            humanCount++;
        }
    }
    reorderMember[reorderCount] = heroIndex;
    reorderCount++;
    if (param->flag == 0) {
        for (int i = 0; i < 3; i++) {
            if (human[i] == -1) {
                break;
            }
            reorderMember[reorderCount] = human[i];
            reorderCount++;
        }
    } else {
        for (int i = 0; i < 3; i++) {
            if (monster[i] == -1) {
                break;
            }
            reorderMember[reorderCount] = monster[i];
            reorderCount++;
        }
    }
    for (int i = 0; i < 8; i++) {
        human[i] = -1;
        monster[i] = -1;
    }
    humanCount = 0;
    monsterCount = 0;
    for (int i = 0; i < reorderCount; i++) {
        if (status::g_Party.getPlayerStatus(reorderMember[i]).getHaveStatusInfo().isDeath() == true) {
            monster[monsterCount] = reorderMember[i];
            monsterCount++;
        } else {
            human[humanCount] = reorderMember[i];
            humanCount++;
        }
    }
    for (int i = 0; i < humanCount; i++) {
        reorderMember[i] = human[i];
    }
    for (int i = 0; i < monsterCount; i++) {
        reorderMember[humanCount + i] = monster[i];
    }
    status::g_Party.reorder(reorderMember[0], reorderMember[1], reorderMember[2], reorderMember[3]);
    cmn::GameManager::getSingleton().resetParty();
    status::PartyStatusUtility::resetForceReorderMember();
    return true;
}
