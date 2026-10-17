#pragma ipa file
#include "main/script/ScriptPlayerCommand.hpp"
#include "main/script/CommandParam.hpp"
#include "main/cmn/CommonCalculate.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/PartyMoveAction.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownSystem.hpp"
#include "ov005/fld/FieldActionCalculate.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldSystem.hpp"

#pragma thumb on

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
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

inline status::StatusChange& status::HaveStatusInfo::getStatusChange()
{
    return statusChange_;
}

inline status::HaveAction& status::HaveStatusInfo::getHaveAction()
{
    return haveAction_;
}

inline status::HaveItem& status::HaveStatusInfo::getHaveItem()
{
    return haveItem_;
}

inline char* status::PlayerData::getNameString()
{
    return name_;
}

inline status::HaveItem& status::PlayerData::getHaveItem()
{
    return haveItem_;
}

inline status::PlayerData& status::PlayerDataAll::getPlayerData(int index)
{
    return playerData_[index];
}

inline void status::BasePartyStatus::setCarriage(int flag)
{
    carriage_ = flag;
}

inline int status::PartyStatus::isCarriage()
{
    return carriage_;
}

inline void status::MenuStatus::setItemIndex(short index)
{
    itemIndex_ = index;
}

inline void status::MenuStatus::setBookingPantherNo(char no)
{
    pantherNo_ = no;
}

inline char status::MenuStatus::getBookingPantherNo()
{
    return pantherNo_;
}

inline void status::StageInfo::setShipPosition(int index, dss::Fix32Vector3& pos)
{
    shipPosition_[index] = pos;
}

inline void status::StageInfo::setFirmamentPosition(dss::Fix32Vector3& pos)
{
    firmamentPosition_ = pos;
}

inline void cmn::CommonPartyInfo::setRideOn(PARTY_RIDE_ON_TYPE type)
{
    rideOnType_ = type;
}

inline cmn::PlayerManager* cmn::GameManager::getPlayerManager()
{
    return playerManager_;
}

inline void cmn::PartyMoveAction::setMemberState(int no, short state)
{
    partyData_[no].state |= state;
}

inline void cmn::PartyMoveAction::removeMemberState(int no, short state)
{
    partyData_[no].state &= ~state;
}

inline void cmn::PartyMoveAction::setMemberDir(int index, short dir)
{
    partyData_[index].direction = dir;
}

inline void twn::TownPartyDraw::setMemberShadow(int index, int flag)
{
    partyCharacter_[index].setShadowFlag(flag);
}

inline void fld::FieldPartyDraw::setShadowFlag(int index, int flag)
{
    partyCharacter_[index].setShadowFlag(flag);
}

inline void twn::TownPlayerManager::setDrawPartyNone()
{
    partyDraw_.setDrawPartyNone();
}

inline void twn::TownPlayerManager::resetAlpha()
{
    partyDraw_.resetAlpha();
}

inline void twn::TownPlayerManager::setPartyDrawOne()
{
    partyDraw_.setDrawPartyOne();
}

inline void twn::TownPlayerManager::changePlayerPose(int index, int set)
{
    partyDraw_.changePose(index, set);
}

inline int twn::TownPlayerManager::getSearchMapUid()
{
    return searchMapUid_;
}

inline twn::TownPartyAction& twn::TownPlayerManager::getPartyAction()
{
    return party_;
}

inline fld::FieldPlayer& fld::FieldPlayerManager::getPlayerAction()
{
    return player_;
}

inline fld::FieldActionShip& fld::FieldPlayer::getActionShip()
{
    return fieldActionShip_;
}

inline void fld::FieldPlayerManager::changePlayerPose(int index, int charaIndex)
{
    partyDraw_.changePlayerPose(index, charaIndex);
}

inline void fld::FieldPlayerManager::setPartyToFirst()
{
    party_.setAllPlayerAtFirst();
}

inline int fld::FieldPlayerManager::getSearchMapUid()
{
    return searchMapUid_;
}

bool cmd_isMonster(void* scriptParam)
{
    PARAM_ISMONSTER* param = (PARAM_ISMONSTER*)scriptParam;
    status::g_Party.setBattleMode();
    bool ret = status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getHaveStatus().isFriendMonster();
    if (param->flag == 1) {
        return ret;
    }
    if (ret == false) {
        return true;
    }
    return false;
}

bool cmd_set_player_ride_on(void* scriptParam)
{
    PARAM_SET_PLAYER_RIDE_ON* param = (PARAM_SET_PLAYER_RIDE_ON*)scriptParam;
    int ride;
    switch (param->flag) {
    case 0:
        ride = cmn::RIDE_ON_NONE;
        if (data_02101c88.unkfunc_02051818(6)) {
            fld::FieldPlayerManager::getSingleton().getPlayerAction().setMoveType(ride);
        }
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        break;
    case 1:
        ride = cmn::RIDE_ON_SHIP_IKADA;
        if (data_02101c88.unkfunc_02051818(6)) {
            fld::FieldPlayerManager::getSingleton().getPlayerAction().getActionShip().scriptStart();
        }
        break;
    case 2:
        ride = cmn::RIDE_ON_NONE;
        cmn::g_cmnPartyInfo.setMenuAction(cmn::TENKU_CASTLE);
        break;
    case 3:
        ride = cmn::RIDE_ON_NONE;
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MASTER_DRAGON_DIRECT);
        break;
    case 4:
        break;
    default:
        ride = cmn::RIDE_ON_NONE;
        break;
    }
    cmn::g_cmnPartyInfo.setRideOn((cmn::PARTY_RIDE_ON_TYPE)ride);
    return true;
}

bool cmd_set_player_shadow_town(void* scriptParam)
{
    PARAM_SET_PLAYER_SHADOW* param = (PARAM_SET_PLAYER_SHADOW*)scriptParam;
    if (param->index == 0) {
        for (int i = 0; i < twn::TownPlayerManager::getSingleton().partyDraw_.countReal_; i++) {
            twn::TownPlayerManager::getSingleton().partyDraw_.setMemberShadow(i, param->flag);
        }
    } else {
        twn::TownPlayerManager::getSingleton().partyDraw_.setMemberShadow(param->index, param->flag);
    }
    return true;
}

bool cmd_set_player_shadow_field(void* scriptParam)
{
    PARAM_SET_FIELD_PLAYER_SHADOW* param = (PARAM_SET_FIELD_PLAYER_SHADOW*)scriptParam;
    for (int i = 0; i < fld::FieldPlayerManager::getSingleton().partyDraw_.countReal_; i++) {
        fld::FieldPlayerManager::getSingleton().partyDraw_.setShadowFlag(i, param->enable);
    }
    return true;
}

bool cmdCharacterSetPartyQuit(void* scriptParam)
{
    PARAM_SET_PARTY_QUIT* param = (PARAM_SET_PARTY_QUIT*)scriptParam;
    status::g_Party.setAllPlayerMode();
    int delIndex;
    if ((int)param->index > 16) {
        delIndex = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(param->index);
        status::PlayerDataAll::setFriendMonsterFlag(delIndex, false);
    } else {
        delIndex = status::g_Party.getSortIndex(param->index);
    }
    if (delIndex != -1) {
        TextAPI::setMACRO0(0x12, 0x50000000, status::g_Party.getPlayerStatus(delIndex).getHaveStatusInfo().getPlayerIndex());
        status::g_Party.del(delIndex);
        if (param->flag == 1) {
            int carriageOutCount = status::g_Party.getCarriageOutCount();
            int count = status::g_Party.getCount();
            if (carriageOutCount < 4 && count > 4) {
                status::g_Party.reorder(0, 1, 2, 3);
            }
        }
        cmn::GameManager::getSingleton().resetParty();
    }
    return true;
}

bool cmdCharacterSetPartyJoin(void* scriptParam)
{
    PARAM_SET_PARTY_JOIN* param = (PARAM_SET_PARTY_JOIN*)scriptParam;
    status::g_Party.setBattleModeAndCarriage();
    int partyCount = status::g_Party.getCount();
    int carriageOutCount = status::g_Party.getCarriageOutCount();
    int addIndex = param->index;
    int pos = param->pos - 1;
    if (addIndex > 16) {
        addIndex = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(addIndex);
    } else {
        for (int i = 0; i < partyCount; i++) {
            if (addIndex == status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getPlayerIndex()) {
                return true;
            }
        }
        status::PlayerDataAll::setRuidaFlag(addIndex, false);
    }
    status::g_Party.add(addIndex, true);
    if (pos != -1 && pos < carriageOutCount) {
        int count = 0;
        int playerPos[4] = {-1};
        for (int i = 0; i < 4; i++) {
            playerPos[i] = -1;
        }
        playerPos[pos] = carriageOutCount;
        for (int i = 0; i < carriageOutCount + 1; i++) {
            if (playerPos[i] != -1) {
                i++;
            }
            playerPos[i] = count;
            count++;
        }
        status::g_Party.reorder(playerPos[0], playerPos[1], playerPos[2], playerPos[3]);
    }
    cmn::PartyTalk::getSingleton().setAddPlayer(param->index);
    cmn::GameManager::getSingleton().resetParty();
    return true;
}

bool cmdSetPartyTotalRecovery(void* scriptParam)
{
    PARAM_SET_PARTY_TOTAL_RECOVERY* param = (PARAM_SET_PARTY_TOTAL_RECOVERY*)scriptParam;
    status::g_Party.setBattleModeAndCarriage();
    for (int i = 0; i < status::g_Party.getCount(); i++) {
        status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
        if (param->flag == 1) {
            statusInfo.revival();
            statusInfo.getStatusChange().clear();
        } else if (statusInfo.isDeath() == false) {
            statusInfo.revival();
        }
    }
    if (param->flag == 1) {
        cmn::GameManager::getSingleton().resetParty();
    }
    return true;
}

bool cmdIsPartyOrder(void* scriptParam)
{
    PARAM_IS_PARTY_ORDER* param = (PARAM_IS_PARTY_ORDER*)scriptParam;
    status::g_Party.setNormalMode();
    if (param->order == status::g_Party.getSortIndex(param->index)) {
        return true;
    }
    return false;
}

bool cmdIsPartyOrder2(void* scriptParam)
{
    PARAM_IS_PARTY_ORDER2* param = (PARAM_IS_PARTY_ORDER2*)scriptParam;
    status::g_Party.setDisplayMode();
    if (param->order == status::g_Party.getSortIndex(param->index)) {
        return true;
    }
    return false;
}

bool cmdIsPlayerStatusDead(void* scriptParam)
{
    PARAM_IS_PLAYER_STATUS_DEAD* param = (PARAM_IS_PLAYER_STATUS_DEAD*)scriptParam;
    if (param->type == 0) {
        if (!status::g_Party.getPlayerStatusForPlayerIndex(param->index).getHaveStatusInfo().isDeath() == true) {
            return true;
        }
        return false;
    }
    if (status::g_Party.getPlayerStatusForPlayerIndex(param->index).getHaveStatusInfo().isDeath() == true) {
        return true;
    }
    return false;
}

bool cmdSetPartyJoinCarriage()
{
    status::g_Party.setCarriage(true);
    cmn::GameManager::getSingleton().resetParty();
    return true;
}

bool cmd_set_party_call_carriage(void* scriptParam)
{
    cmn::g_cmnPartyInfo.callCarriage();
    return true;
}

bool cmd_set_player_recovery(void* scriptParam)
{
    PARAM_SET_PLAYER_RECOVERY* param = (PARAM_SET_PLAYER_RECOVERY*)scriptParam;
    status::g_Party.setBattleMode();
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatusForPlayerIndex(param->player).getHaveStatusInfo();
    if (param->flag == 0) {
        if (statusInfo.isDeath()) {
            return true;
        }
        statusInfo.recovery();
    } else {
        statusInfo.rebirth();
        status::g_Party.getPlayerStatusForPlayerIndex(param->player).setBestCondition();
        if (data_02101c88.unkfunc_02051818(5) == false) {
            statusInfo.getStatusChange().clear();
            cmn::GameManager::getSingleton().getPlayerManager()->resetParty();
        }
    }
    return true;
}

bool cmd_set_player_in_carriage(void* scriptParam)
{
    PARAM_SET_PLAYER_IN_CARRIAGE* param = (PARAM_SET_PLAYER_IN_CARRIAGE*)scriptParam;
    if (!status::g_Party.isCarriage()) {
        return true;
    }
    status::g_Party.setDisplayMode();
    int member[4] = {-1};
    for (int i = 0; i < 4; i++) {
        member[i] = -1;
    }
    int carriageOutCount = status::g_Party.getCarriageOutCount();
    int addIndex = param->index;
    for (int i = 0; i < carriageOutCount; i++) {
        member[i] = i;
    }
    if (addIndex > 16) {
        addIndex = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(addIndex);
        status::PlayerDataAll::setFriendMonsterFlag(addIndex, true);
    }
    status::g_Party.add(addIndex, true);
    status::g_Party.reorder(member[0], member[1], member[2], member[3]);
    cmn::GameManager::getSingleton().resetParty();
    cmn::PartyTalk::getSingleton().setAddPlayer(param->index);
    return true;
}

bool cmd_set_player_magic(void* scriptParam)
{
    PARAM_SET_PLAYER_MAGIC* param = (PARAM_SET_PLAYER_MAGIC*)scriptParam;
    status::g_Party.setPlayerMode();
    int active = status::g_Party.getSortIndex(param->index);
    if (active == -1) {
        return true;
    }
    int townMagic = 0, battleMagic = 0;
    if (status::UseAction::isUsuallyUse(param->magic) == true) {
        townMagic = param->magic;
    } else {
        battleMagic = param->magic;
    }
    status::g_Party.getPlayerStatus(active).getHaveStatusInfo().getHaveAction().add(battleMagic, townMagic, false);
    return true;
}

void setPlayerEquip(int active, ItemType type, int itemID);

bool cmd_set_player_equip(void* scriptParam)
{
    PARAM_SET_PLAYER_EQUIP* param = (PARAM_SET_PLAYER_EQUIP*)scriptParam;
    status::g_Party.setPlayerMode();
    int active = status::g_Party.getSortIndex(param->index);
    if (active == -1) {
        return true;
    }
    status::g_Party.getPlayerStatus(active);
    if (param->weaponID != 0) {
        setPlayerEquip(active, ITEM_WEAPON, param->weaponID);
    }
    if (param->armorID != 0) {
        setPlayerEquip(active, ITEM_ARMOR, param->armorID);
    }
    if (param->shieldID != 0) {
        setPlayerEquip(active, ITEM_SHIELD, param->shieldID);
    }
    if (param->helmetID != 0) {
        setPlayerEquip(active, ITEM_HELMET, param->helmetID);
    }
    if (param->accessoryID != 0) {
        setPlayerEquip(active, ITEM_ACCESSORY, param->accessoryID);
    }
    return true;
}

void setPlayerEquip(int active, ItemType type, int itemID)
{
    status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(active).getHaveStatusInfo();
    if (type != status::UseItem::getEquipItemType(itemID)) {
        return;
    }
    if (!statusInfo.isEquipEnable(itemID)) {
        return;
    }
    int nowEquipID, accessoryCount = 0;
    int itemCount = statusInfo.getHaveItem().getCount();
    if (type != ITEM_ACCESSORY) {
        nowEquipID = statusInfo.getHaveItem().getEquipmentItem(type, accessoryCount);
    } else {
        for (int i = 0; i < 5; i++) {
            if (statusInfo.getHaveItem().getEquipmentItem(ITEM_ACCESSORY, i) != 0) {
                accessoryCount++;
            }
        }
        nowEquipID = statusInfo.getHaveItem().getEquipmentItem(ITEM_ACCESSORY, accessoryCount - 1);
    }
    if (nowEquipID != 0 && accessoryCount == 5) {
        status::g_Party.haveItemSack_.add(nowEquipID);
        for (int i = 0; i < itemCount; i++) {
            int itemID = statusInfo.getHaveItem().getItem(i);
            if (itemID == nowEquipID) {
                status::g_Menu.setItemIndex(itemID);
                statusInfo.execThrow(i);
                break;
            }
        }
    }
    if (statusInfo.getHaveItem().getCount() == 12) {
        int itemID = statusInfo.getHaveItem().getItem(11);
        status::g_Party.haveItemSack_.add(itemID);
        status::g_Menu.setItemIndex(itemID);
        statusInfo.execThrow(11);
    }
    statusInfo.getHaveItem().add(itemID);
    statusInfo.setEquipment(statusInfo.getHaveItem().getCount() - 1);
}

bool cmdBookingPantherName(void* scriptParam)
{
    PARAM_BOOKING_PANTHER_NAME* param = (PARAM_BOOKING_PANTHER_NAME*)scriptParam;
    status::g_Menu.setBookingPantherNo(param->name);
    return true;
}

bool cmdSetPantherName(void* scriptParam)
{
    const int NAME_SIZE_MAX = 0x200;
    char panther[NAME_SIZE_MAX];
    for (int i = 0; i < NAME_SIZE_MAX; i++) {
        panther[i] = 0;
    }
    int no = status::g_Menu.getBookingPantherNo();
    switch (no) {
    case 0:
        TextAPI::extractText(panther, NAME_SIZE_MAX, 0x50000000, 0x259);
        break;
    case 1:
        TextAPI::extractText(panther, NAME_SIZE_MAX, 0x50000000, 0x25a);
        break;
    case 2:
        TextAPI::extractText(panther, NAME_SIZE_MAX, 0x50000000, 0x25b);
        break;
    case 3:
        TextAPI::extractText(panther, NAME_SIZE_MAX, 0x50000000, 0x25c);
        break;
    case 4:
        TextAPI::extractText(panther, NAME_SIZE_MAX, 0x50000000, 0x25d);
        break;
    case 5:
        TextAPI::extractText(panther, NAME_SIZE_MAX, 0x50000000, 0x25e);
        break;
    case 6:
        TextAPI::extractText(panther, NAME_SIZE_MAX, 0x50000000, 0x25f);
        break;
    case 7:
        TextAPI::extractText(panther, NAME_SIZE_MAX, 0x50000000, 0x260);
        break;
    case 8:
        TextAPI::extractText(panther, NAME_SIZE_MAX, 0x50000000, 0x261);
        break;
    case 9:
        TextAPI::extractText(panther, NAME_SIZE_MAX, 0x50000000, 0x262);
        break;
    }
    int bebi = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(16);
    int kira = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(17);
    status::PlayerDataAll::getPlayerData(bebi).setNameString(panther);
    status::PlayerDataAll::getPlayerData(kira).setNameString(panther);
    return true;
}

bool cmdChangePlayerDraw(void* scriptParam)
{
    PARAM_CHANGE_PLAYER_DRAW* param = (PARAM_CHANGE_PLAYER_DRAW*)scriptParam;
    if (data_02101c88.unkfunc_02051818(6) == true) {
        fld::FieldPlayerManager::getSingleton().changePlayerPose(param->id, param->charaId);
    } else {
        twn::TownPlayerManager::getSingleton().changePlayerPose(param->id, param->charaId);
    }
    return true;
}

bool cmdSetVehicle(void* scriptParam)
{
    PARAM_SET_VEHICLE* param = (PARAM_SET_VEHICLE*)scriptParam;
    dss::Fix32Vector3 data;
    data.vx.value = param->Xpos;
    data.vy.value = param->Ypos;
    data.vz.value = 0;
    switch (param->type) {
    case 1:
        status::g_Story.setVehicleEnable(0, param->flag == 0);
        status::g_StageInfo.setShipPosition(0, data);
        break;
    case 2:
        status::g_Story.setVehicleEnable(1, param->flag == 0);
        status::g_StageInfo.setShipPosition(1, data);
        break;
    case 3:
        status::g_Story.setVehicleEnable(3, param->flag == 0);
        status::g_StageInfo.setFirmamentPosition(data);
        break;
    }
    return true;
}

bool cmdSearchMapObject(void* scriptParam)
{
    PARAM_SEARCH_MAP_OBJECT* param = (PARAM_SEARCH_MAP_OBJECT*)scriptParam;
    if (data_02101c88.unkfunc_02051818(4)) {
        twn::TownPlayerManager::getSingleton().setScriptSearchObject(param->target);
        if (twn::TownSystem::getSingleton().townSystemScript_.scriptSearch_) {
            if (param->target == twn::TownPlayerManager::getSingleton().getSearchMapUid()) {
                cmn::PartyTalk::getSingleton().resetPartyTalk();
                return true;
            }
        }
        return false;
    }
    fld::FieldPlayerManager::getSingleton().setScriptSearchObject(param->target);
    if (fld::FieldSystem::getSingleton()->fieldSystemScript_.search_) {
        if (param->target == fld::FieldPlayerManager::getSingleton().getSearchMapUid()) {
            cmn::PartyTalk::getSingleton().resetPartyTalk();
            return true;
        }
    }
    return false;
}

bool cmdPlayerItemIntoFukuro(void* scriptParam)
{
    PARAM_PLAYER_ITEM_INTO_FUKURO* param = (PARAM_PLAYER_ITEM_INTO_FUKURO*)scriptParam;
    status::g_Party.setAllPlayerMode();
    int active = status::g_Party.getSortIndex(param->index);
    status::HaveItem* item;
    if (active == -1) {
        int ctrl = param->index;
        if (param->index > 15) {
            ctrl = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(ctrl);
        }
        item = &status::PlayerDataAll::getPlayerData(ctrl).getHaveItem();
    } else {
        item = &status::g_Party.getPlayerStatus(active).getHaveStatusInfo().getHaveItem();
    }
    while (item->getCount() > 0) {
        status::g_Party.haveItemSack_.add(item->getItem(0));
        item->del(0);
    }
    return true;
}

bool cmdSetPlayerAzuke(void* scriptParam)
{
    PARAM_SET_PLAYER_AZUKE* param = (PARAM_SET_PLAYER_AZUKE*)scriptParam;
    if (param->index > 15) {
        int ctrl = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(param->index);
        status::PlayerDataAll::setFriendMonsterFlag(ctrl, true);
    } else {
        status::PlayerDataAll::setRuidaFlag(param->index, true);
    }
    return true;
}

bool cmdIsPlayerName(void* scriptParam)
{
    PARAM_IS_PLAYER_NAME* param = (PARAM_IS_PLAYER_NAME*)scriptParam;
    char* heroName = status::PlayerDataAll::getPlayerData(1).getNameString();
    if (param->select == TextAPI::isGirlieName(heroName)) {
        return true;
    }
    return false;
}

bool cmd_party_display(void* scriptParam)
{
    PARAM_PARTY_DISPLAY* param = (PARAM_PARTY_DISPLAY*)scriptParam;
    if (data_02101c88.unkfunc_02051818(4)) {
        if (param->flag == 1) {
            twn::TownPlayerManager::getSingleton().resetDrawPartyCount();
            twn::TownPlayerManager::getSingleton().resetAlpha();
        } else {
            twn::TownPlayerManager::getSingleton().setDrawPartyNone();
        }
    } else if (param->flag == 1) {
        fld::FieldPlayerManager::getSingleton().resetDrawPartyCount();
    } else {
        fld::FieldPlayerManager::getSingleton().setDrawPartyNone();
    }
    return true;
}

bool cmd_party_display2(void* scriptParam)
{
    PARAM_PARTY_DISPLAY2* param = (PARAM_PARTY_DISPLAY2*)scriptParam;
    if (data_02101c88.unkfunc_02051818(4)) {
        if (param->flag == 0) {
            twn::TownPlayerManager::getSingleton().setPartyDrawOne();
        } else {
            dss::Fix32Vector3 pos(twn::TownPlayerManager::getSingleton().getPosition());
            twn::TownPlayerManager::getSingleton().setPartyToFirst(pos);
            twn::TownPlayerManager::getSingleton().resetDrawPartyCount();
            twn::TownPlayerManager::getSingleton().resetAlpha();
        }
    } else if (param->flag == 0) {
        fld::FieldPlayerManager::getSingleton().setPartyDrawOne();
    } else {
        dss::Fix32Vector3 pos(fld::FieldPlayerManager::getSingleton().getPosition());
        fld::FieldPlayerManager::getSingleton().setPartyToFirst();
        fld::FieldPlayerManager::getSingleton().resetDrawPartyCount();
    }
    return true;
}

bool cmd_party_redisplay(void* scriptParam)
{
    if (data_02101c88.unkfunc_02051818(4)) {
        twn::TownPlayerManager::getSingleton().resetDrawPartyCount();
        twn::TownPlayerManager::getSingleton().resetAlpha();
    } else {
        fld::FieldPlayerManager::getSingleton().resetDrawPartyCount();
    }
    return true;
}

bool cmdSetPartyDirectionByPlayerNo(void* scriptParam)
{
    PARAM_SET_PARTY_DIRECTION_BY_PLAYER_NO* param = (PARAM_SET_PARTY_DIRECTION_BY_PLAYER_NO*)scriptParam;
    short direction;
    status::g_Party.setDisplayMode();
    int index = status::g_Party.getSortIndex(param->playerNO);
    if (index != -1) {
        if (data_02101c88.unkfunc_02051818(4)) {
            direction = cmn::CommonCalculate::getIdxByParam(param->direction);
            twn::TownPlayerManager::getSingleton().getPartyAction().setMemberState(index, 1);
            twn::TownPlayerManager::getSingleton().getPartyAction().setMemberDir(index, direction);
        } else {
            direction = fld::FieldActionCalculate::getIdxByParam4(param->direction);
            fld::FieldPlayerManager::getSingleton().party_.setMemberState(index, 1);
            fld::FieldPlayerManager::getSingleton().party_.setMemberDir(index, direction);
        }
    }
    return true;
}

bool cmdResetPartyDirectionByPlayerNo(void* scriptParam)
{
    PARAM_RESET_PARTY_DIRECTION_BY_PLAYER_NO* param = (PARAM_RESET_PARTY_DIRECTION_BY_PLAYER_NO*)scriptParam;
    status::g_Party.setDisplayMode();
    int index = status::g_Party.getSortIndex(param->playerNO);
    if (index != -1) {
        if (data_02101c88.unkfunc_02051818(4)) {
            twn::TownPlayerManager::getSingleton().getPartyAction().removeMemberState(index, 1);
        } else {
            fld::FieldPlayerManager::getSingleton().party_.removeMemberState(index, 1);
        }
    }
    return true;
}
