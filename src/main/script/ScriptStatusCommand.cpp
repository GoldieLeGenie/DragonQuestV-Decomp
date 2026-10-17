#pragma ipa file
#include "main/script/ScriptStatusCommand.hpp"
#include "main/script/CommandParam.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/object/DSSAObject.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/StageInfo.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"

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

inline status::StatusChange& status::HaveStatusInfo::getStatusChange()
{
    return statusChange_;
}

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatusInfo::getPlayerIndex() const
{
    return haveStatus_.getPlayerIndex();
}

inline bool status::HaveStatus::isBattleNpc() const
{
    return playerType_ == TYPE_BATTLENPC;
}

inline bool status::HaveStatus::isNoBattleNpc() const
{
    return playerType_ == TYPE_NOBATTLENPC;
}

inline bool status::HaveStatus::isFriendMonster() const
{
    return playerType_ == TYPE_FRIENDMONSTER;
}

inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

inline int status::PlayerData::getKindIndex()
{
    return kindIndex_;
}

inline int status::BasePartyStatus::isFukuro()
{
    return fukuro_;
}

inline status::HaveItemSack& status::BasePartyStatus::getFukuro()
{
    return haveItemSack_;
}

inline int status::PartyStatus::isCarriage()
{
    return carriage_;
}

inline void status::StageInfo::setReturnChurch(int church)
{
    returnChurchData_ = church;
}

inline void status::StageInfo::setStageSepia(bool sep)
{
    DSSAObject::setHueChange(sep);
    sepiaFlag_ = sep;
}

bool isTargetGender(int playerNum, unsigned int param);
bool isTargetType(int playerNum, unsigned int param);
void searchItem(int index, int* findItem, unsigned int* itemID);
bool checkPartyHead(int active, unsigned int type, unsigned int life);
void setPlayerCondition(int active, unsigned int conditionType, unsigned int curseType);

bool cmd_is_procure_item(void* scriptParam)
{
    PARAM_IS_PROCURE_ITEM* param = (PARAM_IS_PROCURE_ITEM*)scriptParam;
    for (int i = 0; i < status::g_Party.getCount(); i++) {
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveItem().isItem(param->item)) {
            return true;
        }
    }
    if (status::g_Party.isFukuro()) {
        if (status::g_Party.getFukuro().isItem(param->item)) {
            return true;
        }
    }
    return false;
}

bool cmd_is_party_top(void* scriptParam)
{
    PARAM_IS_PARTY_TOP* param = (PARAM_IS_PARTY_TOP*)scriptParam;
    status::g_Party.setMemberShiftMode();
    status::g_Party.getPlayerStatus(0);
    status::HaveStatusInfo* statusInfo = &status::g_Party.getPlayerStatus(0).getHaveStatusInfo();
    int num;
    for (num = 0; num < status::g_Party.getCarriageOutCount(); num++) {
        statusInfo = &status::g_Party.getPlayerStatus(num).getHaveStatusInfo();
        if (!statusInfo->isDeath()) {
            break;
        }
    }
    unsigned int idList[5] = {param->player0, param->player1, param->player2, param->player3, param->player4};
    bool isTarget = false;
    for (int i = 0; i < 5; i++) {
        if (idList[i] == statusInfo->getPlayerIndex()) {
            isTarget = true;
        }
    }
    if (!isTarget && param->player0 != 0) {
        return false;
    }
    if (param->type != 0 && !isTargetType(num, param->type)) {
        return false;
    }
    if (param->sex != 0 && !isTargetGender(num, param->sex)) {
        return false;
    }
    return true;
}

bool cmd_is_not_party_top(void* scriptParam)
{
    if (!cmd_is_party_top(scriptParam)) {
        return true;
    }
    return false;
}

bool cmd_set_party_reserve_order(void* scriptParam)
{
    status::g_Party.setBattleModeAndCarriage();
    int memberCount = status::g_Party.getCarriageOutCount();
    if (memberCount < 4) {
        return true;
    }
    int alive[4] = {-1};
    for (int i = 0; i < 4; i++) {
        alive[i] = -1;
    }
    int death[4] = {-1};
    for (int i = 0; i < 4; i++) {
        death[i] = -1;
    }
    int aliveCount = 0, deathCount = 0;
    for (int i = 0; i < memberCount; i++) {
        if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() == true) {
            death[deathCount] = i;
            deathCount++;
        } else {
            alive[aliveCount] = i;
            aliveCount++;
        }
    }
    for (int i = 0; i < deathCount; i++) {
        alive[aliveCount + i] = death[i];
    }
    alive[3] = -1;
    status::g_Party.reorder(alive[0], alive[1], alive[2], alive[3]);
    cmn::GameManager::getSingleton().resetParty();
    return true;
}

bool cmd_party_copy_character(void* scriptParam)
{
    PARAM_PARTY_COPY_CHARACTER* param = (PARAM_PARTY_COPY_CHARACTER*)scriptParam;
    int ctrl = getPlacementCtrlId(param->objNo);
    status::g_Party.setDisplayMode();
    int index = param->order;
    if (status::g_Party.isCarriageEnter() && param->order >= 1) {
        index += 2;
    }
    twn::TownPlayerManager& player = twn::TownPlayerManager::getSingleton();
    TownCharacterManager::getSingleton()->setPosing(ctrl, player.partyDraw_.charaIndex_[index]);
    return true;
}

bool isTargetGender(int playerNum, unsigned int param)
{
    status::g_Party.setMemberShiftMode();
    status::g_Party.getPlayerStatus(playerNum);
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(playerNum).getHaveStatusInfo();
    if (statusInfo.getHaveStatus().getSex() == 0) {
        if (param != 1) {
            return false;
        }
    } else if (statusInfo.getHaveStatus().getSex() == 1) {
        if (param != 2) {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool isTargetType(int playerNum, unsigned int param)
{
    status::g_Party.setMemberShiftMode();
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(playerNum).getHaveStatusInfo();
    if (statusInfo.getHaveStatus().isBattleNpc()) {
        if (param != 2) {
            return false;
        }
    } else if (statusInfo.getHaveStatus().isPlayer()) {
        if (param == 2) {
            return false;
        }
        if (statusInfo.getPlayerIndex() == 1 && param == 1) {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool cmd_check_player_item(void* scriptParam)
{
    PARAM_CHECK_PLAYER_ITEM* param = (PARAM_CHECK_PLAYER_ITEM*)scriptParam;
    status::g_Party.setPlayerMode();
    int countEnd, countStart = 0;
    if (param->flag == 0) {
        countEnd = status::g_Party.getCarriageOutCount();
    } else if (param->flag == 1) {
        countStart = status::g_Party.getCarriageOutCount();
        countEnd = status::g_Party.getCount();
    } else {
        countEnd = status::g_Party.getCount();
    }
    for (int i = countStart; i < countEnd; i++) {
        if (param->index == 0) {
            if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveItem().getCount() < 12) {
                return true;
            }
        } else if (param->index == status::g_Party.getPlayerIndex(i)) {
            if (status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveItem().getCount() < 12) {
                return true;
            }
            return false;
        }
    }
    return false;
}

bool cmdIsPartyRideCarriage(void* scriptParam)
{
    PARAM_IS_PARTY_RIDE_CARRIAGE* param = (PARAM_IS_PARTY_RIDE_CARRIAGE*)scriptParam;
    if (status::PartyStatus::isInsideCarriageForPlayerIndex(param->index) != false) {
        return true;
    }
    return false;
}

bool cmdIsPartyMember(void* scriptParam)
{
    PARAM_IS_PARTY_MEMBER* param = (PARAM_IS_PARTY_MEMBER*)scriptParam;
    status::g_Party.setAllPlayerMode();
    int count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        bool friendMonster = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().isFriendMonster();
        int playerIndex = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getPlayerIndex();
        if (param->index >= 16) {
            if (friendMonster && param->index == status::PlayerDataAll::playerData_[playerIndex].getKindIndex()) {
                return true;
            }
        } else if (friendMonster != true && playerIndex == param->index) {
            return true;
        }
    }
    return false;
}

bool cmd_check_player_hp_mp(void* scriptParam)
{
    PARAM_CHECK_PLAYER_HP_MP* param = (PARAM_CHECK_PLAYER_HP_MP*)scriptParam;
    bool ret = false;
    status::g_Party.setPlayerMode();
    int index = status::g_Party.getSortIndex(param->index);
    if (index == -1) {
        return ret;
    }
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(index).getHaveStatusInfo();
    if (param->hpFlag != 0) {
        int nowHp = statusInfo.getHp();
        int maxHp = statusInfo.getHpMax();
        switch (param->hpFlag) {
        case 1:
            if (nowHp == maxHp) {
                ret = true;
            }
            break;
        case 2:
            if (nowHp == 0) {
                ret = true;
            }
            break;
        case 3:
            if (nowHp != maxHp && nowHp > 0) {
                ret = true;
            }
            break;
        }
    }
    if (param->mpFlag != 0) {
        int nowMp = statusInfo.getMp();
        int maxMp = statusInfo.getMpMax();
        switch (param->mpFlag) {
        case 1:
            if (nowMp == maxMp) {
                ret = true;
            } else {
                ret = false;
            }
            break;
        case 2:
            if (nowMp == 0) {
                ret = true;
            } else {
                ret = false;
            }
            break;
        case 3:
            if (nowMp != maxMp && nowMp > 0) {
                ret = true;
            }
            break;
        }
    }
    return ret;
}

bool cmdCheckPlayerHpMp(void* scriptParam)
{
    PARAM_CHECK_PLAYER_HP_MP2* param = (PARAM_CHECK_PLAYER_HP_MP2*)scriptParam;
    bool ret = false;
    status::g_Party.setPlayerMode();
    int index = status::g_Party.getSortIndex(param->index);
    if (index == -1) {
        return ret;
    }
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(index).getHaveStatusInfo();
    if (param->hpFlag != 0) {
        int nowHp = statusInfo.getHp();
        int maxHp = statusInfo.getHpMax();
        switch (param->hpFlag) {
        case 1:
            if (nowHp == maxHp) {
                ret = true;
            }
            break;
        case 2:
            if (nowHp == 0) {
                ret = true;
            }
            break;
        case 3:
            if (nowHp != maxHp && nowHp > 0) {
                ret = true;
            }
            break;
        case 4: {
            int percent = nowHp / maxHp * 100;
            if (param->hpCheckFlag == 0) {
                if (percent >= param->checkHp) {
                    ret = true;
                }
            } else if (percent < param->checkHp) {
                ret = true;
            }
            break;
        }
        case 5:
            if (param->hpCheckFlag == 0) {
                if (nowHp >= param->checkHp) {
                    ret = true;
                }
            } else if (nowHp < param->checkHp) {
                ret = true;
            }
            break;
        }
    }
    if (param->mpFlag != 0) {
        int nowMp = statusInfo.getMp();
        int maxMp = statusInfo.getMpMax();
        switch (param->mpFlag) {
        case 1:
            if (nowMp == maxMp) {
                ret = true;
            } else {
                ret = false;
            }
            break;
        case 2:
            if (nowMp == 0) {
                ret = true;
            } else {
                ret = false;
            }
            break;
        case 3:
            if (nowMp != maxMp && nowMp > 0) {
                ret = true;
            }
            break;
        case 4: {
            int percent = nowMp / maxMp * 100;
            if (param->mpCheckFlag == 0) {
                if (percent >= param->checkMp) {
                    ret = true;
                }
            } else if (percent < param->checkMp) {
                ret = true;
            }
            break;
        }
        case 5:
            if (param->mpCheckFlag == 0) {
                if (nowMp >= param->checkMp) {
                    ret = true;
                }
            } else if (nowMp < param->checkMp) {
                ret = true;
            }
            break;
        }
    }
    return ret;
}

bool cmd_set_player_hp_mp(void* scriptParam)
{
    PARAM_SET_PLAYER_HP_MP* param = (PARAM_SET_PLAYER_HP_MP*)scriptParam;
    status::g_Party.setPlayerMode();
    int index = status::g_Party.getSortIndex(param->index);
    unsigned short hp = 0, mp = 0;
    if (index == -1) {
        return true;
    }
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(index).getHaveStatusInfo();
    switch (param->hpFlag) {
    case 0:
        hp = statusInfo.getHp();
        break;
    case 1:
        hp = statusInfo.getHpMax();
        break;
    case 2:
        hp = 0;
        break;
    case 3:
        hp = 1;
        break;
    case 4:
        hp = statusInfo.getHpMax() * param->percentHP / 100;
        break;
    }
    switch (param->mpFlag) {
    case 0:
        mp = statusInfo.getMp();
        break;
    case 1:
        mp = statusInfo.getMpMax();
        break;
    case 2:
        mp = 0;
        break;
    case 3:
        mp = statusInfo.getMpMax() * param->percentMP / 100;
        break;
    }
    statusInfo.setHp(hp);
    statusInfo.setMp(mp);
    cmn::GameManager::getSingleton().resetParty();
    return true;
}

bool cmd_is_party_item(void* scriptParam)
{
    PARAM_IS_PARTY_ITEM* param = (PARAM_IS_PARTY_ITEM*)scriptParam;
    status::g_Party.setBattleModeAndCarriage();
    int findItem[4] = {0};
    for (int i = 0; i < 4; i++) {
        findItem[i] = false;
    }
    unsigned int itemID[4] = {param->item0, param->item1, param->item2, param->item3};
    int partyCount = status::g_Party.getCount();
    int carriageOutCount = status::g_Party.getCarriageOutCount();
    switch (param->carriage) {
    case 0:
        for (int i = 0; i < partyCount; i++) {
            searchItem(i, findItem, itemID);
        }
        break;
    case 1:
        for (int i = 0; i < carriageOutCount; i++) {
            searchItem(i, findItem, itemID);
        }
        break;
    case 2:
        for (int i = carriageOutCount; i < partyCount; i++) {
            searchItem(i, findItem, itemID);
        }
        break;
    }
    if (param->bag == 0) {
        status::HaveItemSack& sackInfo = status::g_Party.getFukuro();
        for (int i = 0; i < sackInfo.getCount(); i++) {
            for (int j = 0; j < 4; j++) {
                if (itemID[j] == sackInfo.getItem(i)) {
                    findItem[j] = true;
                }
            }
        }
    }
    if (param->rule == 0) {
        if (findItem[0] == true || findItem[1] == true || findItem[2] == true || findItem[3] == true) {
            return true;
        }
    } else if (findItem[0] == true && findItem[1] == true && findItem[2] == true && findItem[3] == true) {
        return true;
    }
    return false;
}

bool cmd_is_not_party_item(void* scriptParam)
{
    if (!cmd_is_party_item(scriptParam)) {
        return true;
    }
    return false;
}

bool cmdIsPlayerItem(void* scriptParam)
{
    PARAM_IS_PLAYER_ITEM* param = (PARAM_IS_PLAYER_ITEM*)scriptParam;
    status::g_Party.setPlayerMode();
    int findItem[4] = {0};
    unsigned int itemID[4] = {param->item0, param->item1, param->item2, param->item3};
    int active;
    if (param->flag == 0) {
        active = status::g_Party.getSortIndex(param->index);
        if (active == -1) {
            return false;
        }
    } else {
        active = param->index;
        if ((unsigned int)active >= status::g_Party.getCount()) {
            return false;
        }
    }
    searchItem(active, findItem, itemID);
    if (param->rule == 0) {
        for (int i = 0; i < 4; i++) {
            if (findItem[i] == true) {
                return true;
            }
        }
    } else if ((findItem[0] == true || itemID[0] == 0) && (findItem[1] == true || itemID[1] == 0) &&
               (findItem[2] == true || itemID[2] == 0) && (findItem[3] == true || itemID[3] == 0)) {
        return true;
    }
    return false;
}

bool cmdIsNotPlayerItem(void* scriptParam)
{
    if (!cmdIsPlayerItem(scriptParam)) {
        return true;
    }
    return false;
}

void searchItem(int index, int* findItem, unsigned int* itemID)
{
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(index).getHaveStatusInfo();
    if (statusInfo.getHaveStatus().isPlayer() != false ? 1 : 0) {
        int itemCount = statusInfo.getHaveItem().getCount();
        for (int i = 0; i < itemCount; i++) {
            for (int j = 0; j < 4; j++) {
                if (itemID[j] == statusInfo.getHaveItem().getItem(i)) {
                    findItem[j] = true;
                }
            }
        }
    }
}

bool cmd_is_party_head_count(void* scriptParam)
{
    PARAM_IS_PARTY_HEAD_COUNT* param = (PARAM_IS_PARTY_HEAD_COUNT*)scriptParam;
    status::g_Party.setAllPlayerMode();
    int carriageOutIndex[4] = {-1};
    for (int i = 0; i < 4; i++) {
        carriageOutIndex[i] = -1;
    }
    int carriageInIndex[8] = {-1};
    for (int i = 0; i < 8; i++) {
        carriageInIndex[i] = -1;
    }
    int allCount = status::g_Party.getCount();
    status::g_Party.setPlayerMode();
    int checkCountOut = status::g_Party.getCarriageOutCount();
    int checkCountIn = allCount - checkCountOut;
    int checkCount = 0;
    for (int i = 0; i < checkCountOut; i++) {
        carriageOutIndex[i] = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getPlayerIndex();
    }
    status::g_Party.setAllPlayerMode();
    for (int i = 0; i < allCount; i++) {
        status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
        int checkIndex = statusInfo.getPlayerIndex();
        bool carriageOut = false;
        for (int j = 0; j < checkCountOut; j++) {
            if (checkIndex == carriageOutIndex[j]) {
                carriageOut = true;
                break;
            }
        }
        if (!carriageOut && !statusInfo.getHaveStatus().isNoBattleNpc()) {
            carriageInIndex[checkCount] = checkIndex;
            checkCount++;
        }
    }
    checkCount = 0;
    switch (param->carriage) {
    case 0:
        for (int i = 0; i < allCount; i++) {
            if (checkPartyHead(i, param->select, param->life) == true) {
                checkCount++;
            }
        }
        break;
    case 1:
        for (int i = 0; i < checkCountOut; i++) {
            for (int j = 0; j < allCount; j++) {
                if (carriageOutIndex[i] == status::g_Party.getPlayerStatus(j).getHaveStatusInfo().getPlayerIndex()) {
                    if (checkPartyHead(j, param->select, param->life) == true) {
                        checkCount++;
                    }
                    break;
                }
            }
        }
        break;
    case 2:
        if (status::g_Party.isCarriage()) {
            for (int i = 0; i < checkCountIn; i++) {
                for (int j = 0; j < allCount; j++) {
                    if (carriageInIndex[i] == status::g_Party.getPlayerStatus(j).getHaveStatusInfo().getPlayerIndex()) {
                        if (checkPartyHead(i, param->select, param->life) == true) {
                            checkCount++;
                        }
                        break;
                    }
                }
            }
        }
        break;
    }
    bool ret = false;
    switch (param->operation) {
    case 0:
        if (checkCount == param->value) {
            ret = true;
        }
        break;
    case 1:
        if (checkCount <= param->value) {
            ret = true;
        }
        break;
    case 2:
        if (checkCount >= param->value) {
            ret = true;
        }
        break;
    }
    return ret;
}

bool cmd_is_not_party_head_count(void* scriptParam)
{
    if (!cmd_is_party_head_count(scriptParam)) {
        return true;
    }
    return false;
}

bool checkPartyHead(int active, unsigned int type, unsigned int life)
{
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(active).getHaveStatusInfo();
    if (type == 1 && statusInfo.getHaveStatus().isFriendMonster()) {
        return false;
    }
    if (type == 2 && !statusInfo.getHaveStatus().isFriendMonster()) {
        return false;
    }
    if (life == 1) {
        if (!statusInfo.isDeath()) {
            return true;
        }
        return false;
    }
    if (life == 2) {
        return statusInfo.isDeath();
    }
    return true;
}

bool cmdSetPlayerParam(void* scriptParam)
{
    PARAM_SET_PLAYER_PARAM* param = (PARAM_SET_PLAYER_PARAM*)scriptParam;
    status::g_Party.setPlayerMode();
    int active = status::g_Party.getSortIndex(param->index);
    if (active == -1) {
        return true;
    }
    char value = param->value;
    if (param->flag == 1) {
        value *= -1;
    }
    status::HaveStatus& status = status::g_Party.getPlayerStatus(active).getHaveStatusInfo().getHaveStatus();
    switch (param->change) {
    case 0:
        status.addStrength(value);
        break;
    case 1:
        status.addAgility(value);
        break;
    case 2:
        status.addProtection(value);
        break;
    case 3:
        status.addWisdom(value);
        break;
    case 4:
        status.addLuck(value);
        break;
    case 5:
        status.addHpMax(value);
        break;
    case 6:
        status.addMpMax(value);
        break;
    }
    return true;
}

bool cmdSetPlayerCondition(void* scriptParam)
{
    PARAM_SET_PLAYER_CONDITION* param = (PARAM_SET_PLAYER_CONDITION*)scriptParam;
    status::g_Party.setBattleModeAndCarriage();
    int carriageOut[4] = {0};
    for (int i = 0; i < 4; i++) {
        carriageOut[i] = 0;
    }
    int carriageIn[8] = {0};
    for (int i = 0; i < 8; i++) {
        carriageIn[i] = 0;
    }
    int allCount = status::g_Party.getCount();
    int carriageOutCount = status::g_Party.getCarriageOutCount();
    int count = 0;
    for (int i = 0; i < carriageOutCount; i++) {
        carriageOut[i] = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getPlayerIndex();
    }
    for (int i = carriageOutCount; i < allCount; i++) {
        carriageIn[count] = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getPlayerIndex();
        count++;
    }
    switch (param->select) {
    case 0: {
        int active = status::g_Party.getSortIndex(param->index);
        if (active != -1) {
            setPlayerCondition(active, param->condition, param->curse);
        }
        break;
    }
    case 1: {
        int active = param->index - 1;
        if (active < allCount) {
            setPlayerCondition(active, param->condition, param->curse);
        }
        break;
    }
    case 2:
        for (int i = 0; i < carriageOutCount; i++) {
            int active = status::g_Party.getSortIndex(carriageOut[i]);
            setPlayerCondition(active, param->condition, param->curse);
        }
        break;
    case 3: {
        int count = allCount - carriageOutCount;
        for (int i = 0; i < count; i++) {
            int active = status::g_Party.getSortIndex(carriageIn[i]);
            setPlayerCondition(active, param->condition, param->curse);
        }
        break;
    }
    case 4:
        for (int i = 0; i < allCount; i++) {
            setPlayerCondition(i, param->condition, param->curse);
        }
        break;
    }
    cmn::GameManager::getSingleton().resetParty();
    return true;
}

void setPlayerCondition(int active, unsigned int conditionType, unsigned int curseType)
{
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(active).getHaveStatusInfo();
    switch (conditionType) {
    case 0:
        statusInfo.setHp(0);
        break;
    case 1:
        statusInfo.setHp(1);
        break;
    case 2:
        if (statusInfo.isDeath() == true) {
            break;
        }
        statusInfo.getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_DOKU, false);
        break;
    case 3: {
        if (statusInfo.isDeath() == true) {
            break;
        }
        dq5::level::ActionParam::ACTIONTYPE param = dq5::level::ActionParam::ACTIONTYPE_NONE;
        switch (curseType) {
        case 0:
            param = dq5::level::ActionParam::ACTIONTYPE_CURSE1;
            break;
        case 1:
            param = dq5::level::ActionParam::ACTIONTYPE_CURSE2;
            break;
        case 2:
            param = dq5::level::ActionParam::ACTIONTYPE_CURSE3;
            break;
        case 3:
            param = dq5::level::ActionParam::ACTIONTYPE_CURSE4;
            break;
        case 4:
            param = dq5::level::ActionParam::ACTIONTYPE_CURSE5;
            break;
        }
        statusInfo.getStatusChange().setup(param, false);
        break;
    }
    case 4:
        statusInfo.getStatusChange().clear();
        break;
    }
}

bool cmdCheckJisanMax(void* scriptParam)
{
    int jisanCount = status::PlayerDataAll::getMonsterCountInOldMan();
    int eventMonsterCount = 0;
    if (status::PlayerDataAll::getFriendMonsterCountInMonster(0x11)) {
        eventMonsterCount++;
    }
    if (status::PlayerDataAll::getFriendMonsterCountInMonster(0x3a)) {
        eventMonsterCount++;
    }
    if (status::PlayerDataAll::getFriendMonsterCountInMonster(0x3b)) {
        eventMonsterCount++;
    }
    if (status::PlayerDataAll::getFriendMonsterCountInMonster(0x52)) {
        eventMonsterCount++;
    }
    if (jisanCount - eventMonsterCount == 0x4c) {
        return true;
    }
    return false;
}

bool cmdIsPutinMonsterJisan(void* scriptParam)
{
    PARAM_IS_PUTIN_MONSTER_JISAN* param = (PARAM_IS_PUTIN_MONSTER_JISAN*)scriptParam;
    if (param->index < 15) {
        return status::PlayerDataAll::isRuidaFlag(param->index);
    }
    int ctrl = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(param->index);
    for (int i = 0; i < 3; i++) {
        if (status::PlayerDataAll::isMonsterOldManFlag(ctrl + i) == true) {
            return true;
        }
    }
    return false;
}

bool cmdSetReturnChurch(void* scriptParam)
{
    PARAM_SET_RETURN_CHURCH* param = (PARAM_SET_RETURN_CHURCH*)scriptParam;
    status::g_StageInfo.setReturnChurch((unsigned short)param->index);
    return true;
}

bool cmd_map_effect_sepia()
{
    status::g_StageInfo.setStageSepia(true);
    return true;
}
