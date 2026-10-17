#pragma ipa file
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_LEAVE_MESSAGE.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_LEAVE_MONSTER.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_ROOT.hpp"
#include "main/cmn/GameManager.hpp"
#include "ov032/leveldata/JisanMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline dq5::level::JisanMessage* dq5::level::JisanMessage::getRecord(int index)
{
    return (JisanMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::JisanMessage::getMessage1()
{
    return message1;
}

inline void MaterielMenu_JISAN_ROOT::setActiveMenu(char select)
{
    active_ = select;
}

inline void MaterielMenu_JISAN_LEAVE_MESSAGE::menuExecute()
{
}

inline void MaterielMenu_JISAN_LEAVE_MESSAGE::menuDraw()
{
}

THUMB void MaterielMenu_JISAN_LEAVE_MESSAGE::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    mode_ = MODE_END;
    activeChara_ = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
    activeCharaIndex_ = MenuStatusInfo::getPlayerIndex(activeChara_);
    if (status::g_Menu.returnMenuType_ != 0) {
        status::g_Menu.bookingFlag_ = 0;
        status::g_Menu.returnMenuType_ = 0;
        returnMenuMessage();
        return;
    }
    gTownMenu_MESSAGE.openMessageForTALK();
    TextAPI::setMACRO0(0x12, 0x50000000, activeCharaIndex_);
    if (activeCharaIndex_ == 1) {
        gTownMenu_MESSAGE.addMessage(getMessageNo(7));
        return;
    }
    if (MenuStatusInfo::isPlayerType(activeChara_, MenuStatusInfo::TYPE_FRIEND_MONSTER) == true) {
        bool allDeath = true;
        int carriageOut = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
        for (int i = 0; i < carriageOut; i++) {
            if (i != activeChara_ && MenuStatusInfo::isPlayerCondition(i, MenuStatusInfo::CONDITION_DEATH) == false) {
                allDeath = false;
                break;
            }
        }
        if (MenuStatusInfo::isCarriagePosition(activeChara_, MenuStatusInfo::POSITION_CARRIAGE_OUT) == true &&
            MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT) == 1) {
            gTownMenu_MESSAGE.addMessage(getMessageNo(10));
            return;
        }
        if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) == 1) {
            gTownMenu_MESSAGE.addMessage(getMessageNo(10));
            return;
        }
        if (allDeath == true) {
            gTownMenu_MESSAGE.addMessage(getMessageNo(10));
            return;
        }
        if (MenuStatusInfo::isPlayerCondition(activeChara_, MenuStatusInfo::CONDITION_DEATH) == true) {
            gTownMenu_MESSAGE.addMessage(getMessageNo(11));
            gTownMenu_MESSAGE.addMessage(getMessageNo(12));
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_DEATH;
            return;
        }
        gTownMenu_MESSAGE.addMessage(getMessageNo(15));
        mode_ = MODE_LEAVE;
        return;
    }
    gTownMenu_MESSAGE.addMessage(getMessageNo(8));
    gTownMenu_MESSAGE.addMessage(getMessageNo(9));
}

THUMB void MaterielMenu_JISAN_LEAVE_MESSAGE::menuUpdate()
{
    if (gTownMenu_MESSAGE.isOpen() == true) {
        MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            selectYes();
            return;
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            selectNo();
        }
    }
}

THUMB int MaterielMenu_JISAN_LEAVE_MESSAGE::getMessageNo(int index)
{
    return dq5::level::JisanMessage::getRecord(index)->getMessage1();
}

THUMB void MaterielMenu_JISAN_LEAVE_MESSAGE::selectYes()
{
    switch (mode_) {
        case MODE_START:
            break;
        case MODE_DEATH:
            gTownMenu_MESSAGE.openMessageForTALK();
            TextAPI::setMACRO0(0x12, 0x50000000, activeCharaIndex_);
            gTownMenu_MESSAGE.addMessage(getMessageNo(13));
            mode_ = MODE_LEAVE;
            break;
        case MODE_LEAVE:
            leaveMonster();
            break;
        case MODE_RETURN:
            menu::MaterielMenuPlayerControl::getSingleton()->activeChara_ = 0;
            close();
            gMaterielMenu_JISAN_LEAVE_MONSTER.open();
            break;
        case MODE_END:
            returnRoot();
            break;
    }
}

THUMB void MaterielMenu_JISAN_LEAVE_MESSAGE::selectNo()
{
    switch (mode_) {
        case MODE_START:
            break;
        case MODE_DEATH:
            gTownMenu_MESSAGE.openMessageForTALK();
            TextAPI::setMACRO0(0x12, 0x50000000, activeCharaIndex_);
            gTownMenu_MESSAGE.addMessage(getMessageNo(14));
            mode_ = MODE_END;
            break;
        case MODE_LEAVE:
            close();
            gMaterielMenu_JISAN_LEAVE_MONSTER.open();
            break;
        case MODE_RETURN:
            break;
        case MODE_END:
            returnRoot();
            break;
    }
}

THUMB void MaterielMenu_JISAN_LEAVE_MESSAGE::leaveMonster()
{
    int equipCount = 0;
    int itemCount = MenuStatusInfo::getPlayerItemCount(activeChara_);
    for (int i = 0; i < itemCount; i++) {
        if (MenuStatusInfo::isPlayerEquipItemIndex(activeChara_, i) == true) {
            equipCount++;
        }
    }
    if (equipCount == itemCount) {
        status::g_Menu.playerItemFlag_ = 1;
    }
    while (equipCount < MenuStatusInfo::getPlayerItemCount(activeChara_)) {
        MenuStatusInfo::addFukuroItem(MenuStatusInfo::getPlayerItemID(activeChara_, equipCount), 1);
        MenuStatusInfo::throwPlayerItem(activeChara_, equipCount);
    }
    MenuStatusInfo::delPlayer(activeChara_);
    status::PlayerDataAll::setMonsterOldManFlag(activeCharaIndex_, true);
    cmn::GameManager::getSingleton().resetParty();
    status::g_Menu.bookingFlag_ = menu::BOOKING_JISAN;
    status::g_Menu.returnMenuType_ = 2;
    MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
}

THUMB void MaterielMenu_JISAN_LEAVE_MESSAGE::returnMenuMessage()
{
    bool returnSelectMonster = false;
    int playerCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    for (int i = 0; i < playerCount; i++) {
        if (MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_FRIEND_MONSTER) == true) {
            returnSelectMonster = true;
            break;
        }
    }
    if (returnSelectMonster == true) {
        if (status::PlayerDataAll::getMonsterCountInOldMan() < 80) {
            returnSelectMonster = true;
        }
        else {
            returnSelectMonster = false;
        }
    }
    if (status::g_Menu.playerItemFlag_ == 1) {
        status::g_Menu.playerItemFlag_ = 0;
        if (returnSelectMonster == true) {
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(18));
            mode_ = MODE_RETURN;
            return;
        }
        returnRoot();
        return;
    }
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(getMessageNo(16));
    if (status::g_Story.isJisanSack() == false) {
        gTownMenu_MESSAGE.addMessage(getMessageNo(17));
        status::g_Story.setJisanSack(true);
    }
    if (returnSelectMonster == true) {
        gTownMenu_MESSAGE.addMessage(getMessageNo(18));
        mode_ = MODE_RETURN;
        return;
    }
    mode_ = MODE_END;
}

THUMB void MaterielMenu_JISAN_LEAVE_MESSAGE::returnRoot()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(0x48));
    gTownMenu_MESSAGE.addMessageWAITKEY();
    close();
    gMaterielMenu_JISAN_ROOT.setActiveMenu(0);
    gMaterielMenu_JISAN_ROOT.open();
}
