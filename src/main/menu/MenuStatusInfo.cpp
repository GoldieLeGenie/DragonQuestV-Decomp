#include "main/menu/MenuStatusInfo.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/OptionStatus.hpp"
#include "main/status/UseItem.hpp"
#include "main/status/UseAction.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/cmn/GameManager.hpp"

inline bool status::HaveStatusInfo::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)haveStatus_.playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

THUMB void menu::MenuStatusInfo::setMode(ACCESS_MODE mode)
{
    if (mode == NORMAL_MODE) {
        status::g_Party.setNormalMode();
    }
    if (mode == PLAYER_MODE) {
        status::g_Party.setPlayerMode();
    }
    if (mode == BATTLE_MODE) {
        status::g_Party.setBattleMode();
    }
    if (mode == BATTLE_CARRIAGE_MODE) {
        status::g_Party.setBattleModeWithCarriage();
    }
    if (mode == BATTLE_AND_CARRIAGE_MODE) {
        status::g_Party.setBattleModeAndCarriage();
    }
    if (mode == DISPLAY_MODE) {
        status::g_Party.setDisplayMode();
    }
    if (mode == SHIFT_MEMBER_MODE) {
        status::g_Party.setMemberShiftMode();
    }
    if (mode == ALL_PLAYER_MODE) {
        status::g_Party.setAllPlayerMode();
    }
}

THUMB void menu::MenuStatusInfo::setMode(unsigned int mode)
{
    status::g_Party.setAccessMode(mode);
}

THUMB unsigned int menu::MenuStatusInfo::getMode()
{
    return status::g_Party.getAccessMode();
}

THUMB unsigned int menu::MenuStatusInfo::getGold()
{
    return status::g_Party.gold_;
}

THUMB void menu::MenuStatusInfo::setGold(unsigned int gold)
{
    status::g_Party.setGold(gold);
}

THUMB unsigned int menu::MenuStatusInfo::getCoin()
{
    return status::g_Party.casinoCoin_;
}

THUMB void menu::MenuStatusInfo::setCoin(unsigned int coin)
{
    status::g_Party.setCasinoCoin(coin);
}

THUMB unsigned int menu::MenuStatusInfo::getBank()
{
    return status::g_Party.bankMoney_;
}

THUMB void menu::MenuStatusInfo::setBank(unsigned int bank)
{
    status::g_Party.setBankMoney(bank);
}

THUMB unsigned int menu::MenuStatusInfo::getMedal()
{
    return status::g_Party.medalCoin_;
}

THUMB void menu::MenuStatusInfo::setMedal(unsigned int medal)
{
    status::g_Party.setMedalCoin(medal);
}

THUMB int menu::MenuStatusInfo::getPartyCount(PARTY_COUNT mode)
{
    int count = 0;
    switch (status::g_Menu.drawFlag_) {
        case 0:
            if (mode == COUNT_ALL) {
                count = status::g_Party.getCount();
            }
            if (mode == COUNT_CARRIAGE_IN) {
                count = status::g_Party.getCarriageCount();
            }
            if (mode == COUNT_CARRIAGE_OUT) {
                count = status::g_Party.getCarriageOutCount();
            }
            break;
        case 1:
            count = status::PlayerDataAll::getMonsterCountInOldMan();
            break;
        case 2:
            count = status::PlayerDataAll::getPlayerCountInRuida();
            break;
    }
    return count;
}

THUMB bool menu::MenuStatusInfo::isCarriageEnable()
{
    return status::g_Party.isCarriageEnableOnGame();
}

THUMB bool menu::MenuStatusInfo::isCarriagePosition(int playerIndex, PLAYER_POSITION position)
{
    if (position == POSITION_CARRIAGE_IN) {
        return status::g_Party.isInsideCarriage(playerIndex);
    }
    if (position == POSITION_CARRIAGE_OUT) {
        if (status::g_Party.isInsideCarriage(playerIndex)) {
            return false;
        }
        return true;
    }
    return false;
}

THUMB bool menu::MenuStatusInfo::ableToShow()
{
    status::HaveAction::ActionMode mode = status::HaveAction::getActionMode();
    status::HaveAction::setTownMode();
    int charMax = getPartyCount(COUNT_ALL);
    for (int i = 0; i < charMax; i++) {
        int actionCount = getPlayerActionCount(i, USE_TOWN);
        for (int j = 0; j < actionCount; j++) {
            if (getPlayerActionID(i, j) == 0x84) {
                status::HaveAction::setActionMode(mode);
                return true;
            }
        }
    }
    status::HaveAction::setActionMode(mode);
    return false;
}

THUMB void menu::MenuStatusInfo::reorder(int index0, int index1, int index2, int index3)
{
    status::g_Party.reorder(index0, index1, index2, index3);
    if (!data_02101c88.unkfunc_02051818(5)) {
        unsigned int mode = getMode();
        cmn::GameManager::getSingleton().resetParty();
        setMode(mode);
    }
}

THUMB void menu::MenuStatusInfo::addPlayer(int activeChara)
{
    status::g_Party.add(activeChara, true);
    status::PartyStatusUtility::resetForceReorderMember();
}

THUMB void menu::MenuStatusInfo::delPlayer(int activeChara)
{
    status::g_Party.del(activeChara);
    status::PartyStatusUtility::resetForceReorderMember();
}

THUMB int menu::MenuStatusInfo::getPlayerIndex(int activeChara)
{
    int playerIndex = 0;
    switch (status::g_Menu.drawFlag_) {
        case 0:
            playerIndex = status::g_Party.getPlayerStatus(activeChara).haveStatusInfo_.haveStatus_.playerIndex_;
            break;
        case 1:
            playerIndex = status::PlayerDataAll::getMonsterCtrlInOldMan(activeChara);
            break;
        case 2:
            playerIndex = status::PlayerDataAll::getPlayerCtrlInRuida(activeChara);
            break;
    }
    return playerIndex;
}

THUMB int menu::MenuStatusInfo::getPlayerKindIndex(int activeChara)
{
    int kindIndex = 0;
    if (status::g_Menu.drawFlag_ == 0) {
        kindIndex = status::g_Party.getPlayerStatus(activeChara).haveStatusInfo_.haveStatus_.playerKindIndex_;
    }
    return kindIndex;
}

THUMB int menu::MenuStatusInfo::getPlayerIconIndex(int activeChara)
{
    int iconIndex = 0;
    switch (status::g_Menu.drawFlag_) {
        case 0:
            iconIndex = getHaveStatusInfo(activeChara).getIconIndex();
            break;
        case 1:
            iconIndex = getPlayerData(activeChara).getIconIndex();
            break;
        case 2:
            iconIndex = getPlayerData(activeChara).getIconIndex();
            break;
    }
    return iconIndex;
}

THUMB int menu::MenuStatusInfo::getPlayerCharaIndex(int activeChara)
{
    return getHaveStatusInfo(activeChara).getCharaIndex();
}

THUMB int menu::MenuStatusInfo::getPlayerJob(int activeChara)
{
    int job = 0;
    switch (status::g_Menu.drawFlag_) {
        case 0:
            if (isPlayerType(activeChara, TYPE_FRIEND_MONSTER) == true) {
                job = getHaveStatusInfo(activeChara).haveStatus_.monsterId_;
            } else {
                job = getHaveStatusInfo(activeChara).haveStatus_.jobId_;
            }
            break;
        case 1:
            job = getPlayerData(activeChara).getMonsterIndex();
            break;
        case 2:
            job = getPlayerData(activeChara).getJob();
            break;
    }
    return job;
}

THUMB int menu::MenuStatusInfo::getPlayerSex(int activeChara)
{
    int sex = 0;
    switch (status::g_Menu.drawFlag_) {
        case 0:
            sex = getHaveStatusInfo(activeChara).haveStatus_.sexId_;
            break;
        case 1:
            sex = getPlayerData(activeChara).getSexId();
            break;
        case 2:
            sex = getPlayerData(activeChara).getSexId();
            break;
    }
    return sex;
}

THUMB int menu::MenuStatusInfo::getPlayerSortIndex(int activeChara)
{
    return status::g_Party.getSortIndex(activeChara);
}

THUMB int menu::MenuStatusInfo::getPlayerItemID(int activeChara, int activeItem)
{
    int itemID = 0;
    switch (status::g_Menu.drawFlag_) {
        case 0:
            itemID = getHaveStatusInfo(activeChara).haveItem_.getItem(activeItem);
            break;
        case 1:
        case 2:
            itemID = getPlayerData(activeChara).haveItem_.getItem(activeItem);
            break;
    }
    return itemID;
}

THUMB bool menu::MenuStatusInfo::isPlayerType(int activeChara, PLAYER_TYPE type)
{
    bool ret = false;
    int flag = status::g_Menu.drawFlag_;
    switch (type) {
        case TYPE_PLAYER:
            if (flag == 0) {
                if (getHaveStatusInfo(activeChara).isPlayer()) {
                    ret = true;
                } else {
                    ret = false;
                }
            }
            if (flag == 1) {
                ret = false;
            }
            if (flag == 2) {
                ret = true;
            }
            break;
        case TYPE_FRIEND_MONSTER:
            if (flag == 0) {
                if (getHaveStatusInfo(activeChara).haveStatus_.playerType_ == status::HaveStatus::TYPE_FRIENDMONSTER) {
                    ret = true;
                } else {
                    ret = false;
                }
            }
            if (flag == 1) {
                ret = true;
            }
            if (flag == 2) {
                ret = false;
            }
            break;
        case TYPE_BATTLE_NPC:
            if (flag == 0) {
                if (getHaveStatusInfo(activeChara).haveStatus_.playerType_ == status::HaveStatus::TYPE_BATTLENPC) {
                    ret = true;
                } else {
                    ret = false;
                }
            }
            if (flag == 1 || flag == 2) {
                ret = false;
            }
            break;
        case TYPE_NORMAL_NPC:
            if (flag == 0) {
                if (getHaveStatusInfo(activeChara).haveStatus_.playerType_ == status::HaveStatus::TYPE_NOBATTLENPC) {
                    ret = true;
                } else {
                    ret = false;
                }
            }
            if (flag == 1 || flag == 2) {
                ret = false;
            }
            break;
    }
    return ret;
}

THUMB int menu::MenuStatusInfo::getPlayerItemCount(int activeChara)
{
    int count = 0;
    switch (status::g_Menu.drawFlag_) {
        case 0:
            count = getHaveStatusInfo(activeChara).haveItem_.getCount();
            break;
        case 1:
        case 2:
            count = getPlayerData(activeChara).haveItem_.getCount();
            break;
    }
    return count;
}

THUMB bool menu::MenuStatusInfo::isPlayerHaveItem(int activeChara, int itemID)
{
    return getHaveStatusInfo(activeChara).haveItem_.isItem(itemID);
}

THUMB bool menu::MenuStatusInfo::isPlayerEquipItem(int activeChara, int itemID)
{
    status::HaveItem& haveItem = getHaveStatusInfo(activeChara).haveItem_;
    for (int i = 0; i < ITEM_ACCESSORY; i++) {
        int id = haveItem.getEquipmentItem((ItemType)i, 0);
        if (id == itemID) {
            return true;
        }
    }
    for (int i = 0; i < 7; i++) {
        int id = haveItem.getEquipmentItem(ITEM_ACCESSORY, i);
        if (id == itemID) {
            return true;
        }
    }
    return false;
}

THUMB bool menu::MenuStatusInfo::isPlayerEquipItemIndex(int activeChara, int activeItem)
{
    bool equip = false;
    switch (status::g_Menu.drawFlag_) {
        case 0:
            equip = getHaveStatusInfo(activeChara).haveItem_.isEquipment(activeItem);
            break;
        case 1:
        case 2:
            equip = getPlayerData(activeChara).haveItem_.isEquipment(activeItem);
            break;
    }
    return equip;
}

THUMB bool menu::MenuStatusInfo::isPlayerEquipEnable(int activeChara, int itemID)
{
    return getHaveStatusInfo(activeChara).isEquipEnable(itemID);
}

THUMB int menu::MenuStatusInfo::getPlayerEquipItemID(int activeChara, ItemType type, int index)
{
    int itemID = 0;
    switch (status::g_Menu.drawFlag_) {
        case 0:
            itemID = getHaveStatusInfo(activeChara).haveItem_.getEquipmentItem(type, index);
            break;
        case 1:
        case 2:
            itemID = getPlayerData(activeChara).haveItem_.getEquipmentItem(type, index);
            break;
    }
    return itemID;
}

THUMB bool menu::MenuStatusInfo::isAbleToEqip(int activeChara, int activeItem)
{
    if (getPartyCount(COUNT_ALL) <= activeChara) {
        return false;
    }
    status::HaveStatusInfo& info = getHaveStatusInfo(activeChara);
    return info.isEquipEnable(getPlayerItemID(activeChara, activeItem));
}

THUMB void menu::MenuStatusInfo::throwPlayerItem(int activeChara, int activeItem)
{
    switch (status::g_Menu.drawFlag_) {
        case 0:
            getHaveStatusInfo(activeChara).execThrow(activeItem);
            break;
        case 1:
        case 2:
            getPlayerData(activeChara).haveItem_.del(activeItem);
            break;
    }
}

THUMB void menu::MenuStatusInfo::addPlayerItem(int activeChara, int itemID)
{
    getHaveStatusInfo(activeChara).haveItem_.add(itemID);
}

THUMB int menu::MenuStatusInfo::getPlayerItemCommandFlag(int activeChara, int activeItem)
{
    int flag = 0;
    if (isAbleToEqip(activeChara, activeItem) == true) {
        flag |= 1;
    }
    if (ableToShow() == true) {
        flag |= 2;
    }
    return flag;
}

THUMB menu::MenuStatusInfo::EQUIP_RESULT menu::MenuStatusInfo::setEquipItem(int activeChara, int activeItem, ItemType type)
{
    status::HaveStatusInfo& info = getHaveStatusInfo(activeChara);
    int itemID = getPlayerItemID(activeChara, activeItem);
    ItemType itemType = status::UseItem::getEquipItemType(itemID);
    if (info.isEquipEnable(itemID) == true && itemType == type) {
        if (isPlayerEquipItem(activeChara, itemID) == false) {
            info.setEquipment(activeItem);
            if (getPlayerIndex(activeChara) == 7) {
                unsigned int mode = getMode();
                cmn::GameManager::getSingleton().resetParty();
                setMode(mode);
            }
            return EQUIP_SUCCESS;
        }
        return EQUIP_ALREADY;
    }
    return EQUIP_FAILED;
}

THUMB void menu::MenuStatusInfo::resetEquipItemForIndex(int activeChara, int activeItem)
{
    getHaveStatusInfo(activeChara).haveItem_.resetEquipment(activeItem);
}

THUMB bool menu::MenuStatusInfo::isPlayerCondition(int activeChara, PLAYER_CONDITION condition)
{
    bool ret = false;
    int flag = status::g_Menu.drawFlag_;
    switch (condition) {
        case CONDITION_ALIVE:
            if (flag == 0) {
                if (!getHaveStatusInfo(activeChara).isDeath()) {
                    ret = true;
                }
            } else if (getPlayerData(activeChara).baseStatus_.hp_ != 0) {
                ret = true;
            }
            break;
        case CONDITION_DEATH:
            if (flag == 0) {
                ret = getHaveStatusInfo(activeChara).isDeath();
            } else if (getPlayerData(activeChara).baseStatus_.hp_ == 0) {
                ret = true;
            }
            break;
        case CONDITION_NEARDEATH:
            if (flag == 0) {
                ret = getHaveStatusInfo(activeChara).isNearDeath();
            } else {
                int hp = getPlayerData(activeChara).baseStatus_.hp_;
                int hpMax = getPlayerData(activeChara).baseStatus_.hpMax_;
                if (hp > 0 && hp <= hpMax / 4 - 1) {
                    ret = true;
                }
            }
            break;
        case CONDITION_POISON:
            if (flag == 0) {
                if (getHaveStatusInfo(activeChara).isPoison() == true) {
                    ret = true;
                }
            } else if (getPlayerData(activeChara).isPoison() == true) {
                ret = true;
            }
            break;
        case CONDITION_VENOM:
            if (flag == 0) {
                if (getHaveStatusInfo(activeChara).statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU) == true) {
                    ret = true;
                }
            } else if (getPlayerData(activeChara).isVenom() == true) {
                ret = true;
            }
            break;
        case CONDITION_SPELL:
            if (flag == 0) {
                ret = getHaveStatusInfo(activeChara).isSpell();
            } else if (getPlayerData(activeChara).isCurse4() == true || getPlayerData(activeChara).isCurse5() == true) {
                ret = true;
            }
            break;
        case CONDITION_ITEM_SPELL:
            int count = getPlayerItemCount(activeChara);
            for (int i = 0; i < count; i++) {
                if (isPlayerEquipItemIndex(activeChara, i) == true && status::UseItem::isCurse(getPlayerItemID(activeChara, i)) == true) {
                    ret = true;
                }
            }
            break;
    }
    return ret;
}

THUMB void menu::MenuStatusInfo::setPlayerCondition(int activeChara, PLAYER_CONDITION condition)
{
    status::HaveStatusInfo& info = getHaveStatusInfo(activeChara);
    switch (condition) {
        case CONDITION_ALIVE:
            info.revival();
            break;
        case CONDITION_DEATH:
            info.setDeath();
            break;
        case CONDITION_NEARDEATH:
            break;
        case CONDITION_POISON:
            info.setPoison();
            break;
        case CONDITION_VENOM:
            info.statusChange_.setup(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU, false);
            break;
        case CONDITION_SPELL:
            info.statusChange_.setup(dq5::level::ActionParam::ACTIONTYPE_CURSE4, false);
            break;
    }
}

THUMB void menu::MenuStatusInfo::resetPlayerCondition(int activeChara, PLAYER_CONDITION condition)
{
    status::HaveStatusInfo& info = getHaveStatusInfo(activeChara);
    switch (condition) {
        case CONDITION_ALIVE:
        case CONDITION_DEATH:
            info.revival();
            break;
        case CONDITION_POISON:
            info.detoxPoison();
            break;
        case CONDITION_VENOM:
            info.statusChange_.release(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU);
            break;
        case CONDITION_SPELL:
            info.breakSpell();
            break;
    }
}

THUMB bool menu::MenuStatusInfo::isPlayerItemSort(int activeChara)
{
    int count = 0;
    for (int i = 0; i < getPlayerItemCount(activeChara); i++) {
        if (!status::UseItem::isOrder(getPlayerItemID(activeChara, i)) || isPlayerEquipItemIndex(activeChara, i) == true) {
            count++;
        }
    }
    if (count == 12) {
        return false;
    }
    return true;
}

THUMB bool menu::MenuStatusInfo::isPlayerClever(int activeChara)
{
    if (getHaveStatusInfo(activeChara).statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN)) {
        return false;
    }
    if (getHaveStatusInfo(activeChara).haveStatus_.playerType_ != status::HaveStatus::TYPE_FRIENDMONSTER) {
        return true;
    }
    if (getHaveStatusInfo(activeChara).haveStatus_.getWisdom() >= 20) {
        return true;
    }
    return false;
}

THUMB bool menu::MenuStatusInfo::isPlayerActionEnable(int activeChara)
{
    bool enable = false;
    status::HaveAction::ActionMode mode = status::HaveAction::getActionMode();
    status::HaveAction::setBattleMode();
    int battleCount = getPlayerActionCount(activeChara, USE_BATTLE);
    status::HaveAction::setTownMode();
    int townCount = getPlayerActionCount(activeChara, USE_TOWN);
    if (battleCount > 0 || townCount > 0) {
        enable = true;
    }
    status::HaveAction::setActionMode(mode);
    return enable;
}

THUMB int menu::MenuStatusInfo::getPlayerActionCount(int activeChara, USE_MAGIC_TYPE type)
{
    status::HaveAction& action = getHaveAction(activeChara);
    if (type == USE_ALL) {
        return action.getCountAll();
    }
    int count = 0;
    int actionCount = action.getCount();
    for (int i = 0; i < actionCount; i++) {
        if (isPlayerActionUseType(getPlayerActionID(activeChara, i), type) == true) {
            count++;
        }
    }
    return count;
}

THUMB int menu::MenuStatusInfo::getPlayerActionID(int activeChara, int activeAction)
{
    return getHaveAction(activeChara).getAction(activeAction);
}

THUMB int menu::MenuStatusInfo::getPlayerActionID(int activeChara, int activeAction, USE_MAGIC_TYPE type)
{
    if (type == USE_ALL) {
        return getHaveAction(activeChara).getActionAll(activeAction);
    }
    int magicList[24] = {0};
    for (int i = 0; i < 24; i++) {
        magicList[i] = 0;
    }
    int magicCount = getPlayerActionCount(activeChara, type);
    for (int i = 0; i < 24; i++) {
        magicList[i] = 0;
    }
    int count = 0;
    for (int i = 0; i < magicCount; i++) {
        int magicID = getPlayerActionID(activeChara, i);
        if (isPlayerActionUseType(magicID, type) == true) {
            magicList[count] = magicID;
            count++;
        }
    }
    return magicList[activeAction];
}

THUMB bool menu::MenuStatusInfo::isPlayerActionUseType(int magicID, USE_MAGIC_TYPE type)
{
    if (type == USE_TOWN) {
        return status::UseAction::isUsuallyUse(magicID);
    }
    return status::UseAction::isBattleUse(magicID);
}

THUMB int menu::MenuStatusInfo::getPlayerTactics(int activeChara)
{
    return getPlayerStatus(activeChara).haveStatusInfo_.haveStatus_.command_;
}

THUMB void menu::MenuStatusInfo::setPlayerTactics(int activeChara, CommandType command)
{
    getPlayerStatus(activeChara).haveStatusInfo_.haveStatus_.command_ = command;
}

THUMB status::HaveStatusInfo& menu::MenuStatusInfo::getHaveStatusInfo(int activeChara)
{
    if (status::g_Menu.drawFlag_ != 0) {
        return status::g_Party.getPlayerStatus(0).haveStatusInfo_;
    }
    return status::g_Party.getPlayerStatus(activeChara).haveStatusInfo_;
}

THUMB status::HaveBattleStatus& menu::MenuStatusInfo::getHaveBattleStatus(int activeChara)
{
    return status::g_Party.getPlayerStatus(activeChara).haveBattleStatus_;
}

THUMB status::PlayerData& menu::MenuStatusInfo::getPlayerData(int activeChara)
{
    int ctrl = 1;
    switch (status::g_Menu.drawFlag_) {
        case 0:
            ctrl = getPlayerIndex(activeChara);
            break;
        case 1:
            ctrl = status::PlayerDataAll::getMonsterCtrlInOldMan(activeChara);
            break;
        case 2:
            ctrl = status::PlayerDataAll::getPlayerCtrlInRuida(activeChara);
            break;
    }
    return status::PlayerDataAll::playerData_[ctrl];
}

THUMB int menu::MenuStatusInfo::getFukuroItemCount()
{
    return status::g_Party.haveItemSack_.getCount();
}

THUMB int menu::MenuStatusInfo::getFukuroItemCount(int activeItem)
{
    return status::g_Party.haveItemSack_.getItemCount(activeItem);
}

THUMB int menu::MenuStatusInfo::getFukuroMaxPage()
{
    return (getFukuroItemCount() - 1) / 6 + 1;
}

THUMB int menu::MenuStatusInfo::getFukuroItemID(int activeItem, int page)
{
    int index = activeItem;
    if (page != 0) {
        index = getFukuroItemIndexToAll(activeItem, page);
    }
    return status::g_Party.haveItemSack_.getItem(index);
}

THUMB int menu::MenuStatusInfo::getFukuroItemIndexToAll(int activeItem, int page)
{
    getFukuroItemCount();
    return activeItem + page * 6;
}

THUMB int menu::MenuStatusInfo::getFukuroItemCountInPage(int page)
{
    getFukuroMaxPage();
    return dss::max(dss::min(getFukuroItemCount() - page * 6, 6), 0);
}

THUMB int menu::MenuStatusInfo::getFukuroItemCommandFlag()
{
    int flag = 0;
    if (ableToShow() == true) {
        flag |= 2;
    }
    return flag;
}

THUMB void menu::MenuStatusInfo::throwFukuroItem(int activeItem, int page)
{
    status::g_Party.haveItemSack_.execThrow(getFukuroItemIndexToAll(activeItem, page));
}

THUMB void menu::MenuStatusInfo::throwFukuroItemForID(int itemID)
{
    int count = getFukuroItemCount();
    for (int i = 0; i < count; i++) {
        if (itemID == getFukuroItemID(i, 0)) {
            throwFukuroItem(i, 0);
            return;
        }
    }
}

THUMB void menu::MenuStatusInfo::addFukuroItem(int itemID, int count)
{
    status::g_Party.haveItemSack_.add(itemID, count);
}

THUMB int menu::MenuStatusInfo::isFukuroHaveItem(int itemID)
{
    int count = 0;
    if (status::g_Party.haveItemSack_.isItem(itemID) == true) {
        int itemCount = getFukuroItemCount();
        for (int i = 0; i < itemCount; i++) {
            if (itemID == getFukuroItemID(i, 0)) {
                count = getFukuroItemCount(i);
                break;
            }
        }
    }
    return count;
}

THUMB void menu::MenuStatusInfo::setFukuroName(char* name)
{
    status::g_Party.haveItemSack_.setNameString(name);
}

THUMB char* menu::MenuStatusInfo::getFukuroName()
{
    return status::g_Party.haveItemSack_.name_;
}

THUMB status::HaveItemSack& menu::MenuStatusInfo::getHaveItemSack()
{
    return status::g_Party.haveItemSack_;
}

THUMB void menu::MenuStatusInfo::changeItemPlayertoPlayer(int activeChara0, int activeItem0, int activeChara1, int activeItem1)
{
    status::UseItem::give2(getHaveStatusInfo(activeChara0), activeItem0, getHaveStatusInfo(activeChara1), activeItem1);
    getHaveStatusInfo(activeChara0).haveItem_.sortEquipment();
    getHaveStatusInfo(activeChara1).haveItem_.sortEquipment();
    if (getPlayerIndex(activeChara0) == 7) {
        unsigned int mode = getMode();
        cmn::GameManager::getSingleton().resetParty();
        setMode(mode);
    }
}

THUMB void menu::MenuStatusInfo::changeItemPlayertoSack(int activeChara, int activeItem)
{
    status::UseItem::give2(getHaveStatusInfo(activeChara), activeItem, status::g_Party.haveItemSack_, -1);
    if (getPlayerIndex(activeChara) == 7) {
        unsigned int mode = getMode();
        cmn::GameManager::getSingleton().resetParty();
        setMode(mode);
    }
}

THUMB void menu::MenuStatusInfo::changeItemSacktoPlayer(int activeItem, int activeChara, int activeItem1)
{
    status::UseItem::give2(status::g_Party.haveItemSack_, activeItem, getHaveStatusInfo(activeChara), activeItem1);
    getHaveStatusInfo(activeChara).haveItem_.sortEquipment();
}

THUMB int menu::MenuStatusInfo::usePlayerItem(status::UseActionParam& param, int activeChara, int activeItem, int target)
{
    int itemID = getPlayerItemID(activeChara, activeItem);
    param.clear();
    param.actorCharacterStatus_ = &status::g_Party.getPlayerStatus(activeChara);
    if (target == -1) {
        if (itemID == 0xa8) {
            param.targetCount_ = 1;
            param.targetCharacterStatus_[0] = &status::g_Party.getPlayerStatus(activeChara);
        } else {
            status::g_Party.setBattleMode();
            int count = 0;
            for (int i = 0; i < status::g_Party.getCount(); i++) {
                if (!status::g_Party.getPlayerStatus(i).haveStatusInfo_.isDeath()) {
                    param.targetCharacterStatus_[count] = &status::g_Party.getPlayerStatus(i);
                    count++;
                }
            }
            param.targetCount_ = count;
            status::g_Party.setPlayerMode();
        }
    } else {
        param.targetCount_ = 1;
        param.targetCharacterStatus_[0] = &status::g_Party.getPlayerStatus(target);
    }
    param.itemSortIndex_ = activeItem;
    status::UseItem::execUse(param);
    return param.result_;
}

THUMB int menu::MenuStatusInfo::useFukuroItem(status::UseActionParam& param, int activeItem, int target)
{
    int actor = 0;
    status::g_Party.haveItemSack_.getItem(activeItem);
    while (isPlayerCondition(actor, CONDITION_DEATH) == true) {
        actor++;
        if (actor == getPartyCount(COUNT_ALL)) {
            break;
        }
    }
    param.clear();
    param.actorHaveItemSack_ = &status::g_Party.haveItemSack_;
    param.actorCharacterStatus_ = &getPlayerStatus(actor);
    if (target == -1) {
        setMode(BATTLE_MODE);
        int count = 0;
        for (int i = 0; i < getPartyCount(COUNT_ALL); i++) {
            if (isPlayerCondition(i, CONDITION_DEATH) == false) {
                param.targetCharacterStatus_[count] = &getPlayerStatus(i);
                count++;
            }
        }
        param.targetCount_ = count;
        setMode(PLAYER_MODE);
    } else {
        param.targetCount_ = 1;
        param.targetCharacterStatus_[0] = &getPlayerStatus(target);
    }
    param.itemSortIndex_ = activeItem;
    status::UseItem::execUse(param);
    return param.result_;
}

THUMB int menu::MenuStatusInfo::usePlayerMagic(status::UseActionParam& param, int activeChara, int target, int magicID)
{
    int count = 1;
    param.clear();
    param.actorCharacterStatus_ = &getPlayerStatus(activeChara);
    if (target == -1) {
        count = 0;
        for (int i = 0; i < getPartyCount(COUNT_ALL); i++) {
            if (isPlayerCondition(i, CONDITION_DEATH) == false) {
                param.targetCharacterStatus_[count] = &getPlayerStatus(i);
                count++;
            }
        }
    } else {
        param.targetCharacterStatus_[0] = &getPlayerStatus(target);
    }
    param.targetCount_ = count;
    param.setActionIndex(magicID);
    status::UseAction::execUse(param);
    return count;
}

THUMB bool menu::MenuStatusInfo::isCheckRecoveryPlayer()
{
    return status::PartyStatusUtility::isRecoveryForMantan();
}

THUMB bool menu::MenuStatusInfo::isRecoveryPlayer(status::UseActionParam& param)
{
    return status::PartyStatusUtility::recoveryForMantan(param);
}

THUMB bool menu::MenuStatusInfo::isCheckPosonPlayer()
{
    return status::PartyStatusUtility::isPoisonForMantan();
}

THUMB bool menu::MenuStatusInfo::isPoisonPlayer(status::UseActionParam& param)
{
    return status::PartyStatusUtility::destroyPoisonForMantan(param);
}

THUMB void menu::MenuStatusInfo::sortPlayerItem(int activeChara)
{
    status::g_Party.haveItemSack_.sortOutItem(getHaveStatusInfo(activeChara).haveItem_);
}

THUMB void menu::MenuStatusInfo::sortFukuroItem()
{
    status::g_Party.haveItemSack_.sortOutSack((status::HaveItemSack::SortType)g_Option.getSackSort());
}

THUMB int menu::MenuStatusInfo::getWordDBIndex(int magicID)
{
    return status::UseAction::getWordDBIndex(magicID);
}

THUMB status::PlayerStatus& menu::MenuStatusInfo::getPlayerStatus(int activeChara)
{
    return status::g_Party.getPlayerStatus(activeChara);
}

THUMB status::HaveAction& menu::MenuStatusInfo::getHaveAction(int activeChara)
{
    switch (status::g_Menu.drawFlag_) {
        case 0:
            return getHaveStatusInfo(activeChara).haveAction_;
        case 1:
        case 2:
            return getPlayerData(activeChara).haveAction_;
    }
    return getHaveStatusInfo(0).haveAction_;
}
