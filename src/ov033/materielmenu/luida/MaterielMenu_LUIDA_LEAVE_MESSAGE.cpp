#pragma ipa file
#include "ov033/materielmenu/luida/MaterielMenu_LUIDA_LEAVE_MESSAGE.hpp"
#include "ov033/materielmenu/luida/MaterielMenu_LUIDA_LEAVE_PLAYER.hpp"
#include "ov033/materielmenu/luida/MaterielMenu_LUIDA_ROOT.hpp"
#include "main/cmn/GameManager.hpp"
#include "ov033/leveldata/LuidaMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline dq5::level::LuidaMessage* dq5::level::LuidaMessage::getRecord(int index)
{
    return (LuidaMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::LuidaMessage::getMessage1()
{
    return message1;
}

inline void MaterielMenu_LUIDA_ROOT::setActiveMenu(char active)
{
    active_ = active;
}

inline void MaterielMenu_LUIDA_LEAVE_MESSAGE::menuExecute()
{
}

inline void MaterielMenu_LUIDA_LEAVE_MESSAGE::menuDraw()
{
}

THUMB void MaterielMenu_LUIDA_LEAVE_MESSAGE::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    mode_ = MODE_END;
    if (status::g_Menu.bookingFlag_ == menu::BOOKING_RETURN) {
        status::g_Menu.bookingFlag_ = 0;
        status::g_Menu.returnMenuType_ = 0;
        returnMenuMessage();
        return;
    }
    activeChara_ = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
    activeCharaIndex_ = MenuStatusInfo::getPlayerIndex(activeChara_);
    TextAPI::setMACRO0(0x12, 0x50000000, activeCharaIndex_);
    gTownMenu_MESSAGE.openMessageForTALK();
    if (activeCharaIndex_ == 1) {
        gTownMenu_MESSAGE.addMessage(getMessageNo(15));
        return;
    }
    if (MenuStatusInfo::isPlayerType(activeChara_, MenuStatusInfo::TYPE_FRIEND_MONSTER) == true) {
        gTownMenu_MESSAGE.addMessage(getMessageNo(16), getMessageNo(17));
        return;
    }
    if (MenuStatusInfo::isPlayerCondition(activeChara_, MenuStatusInfo::CONDITION_DEATH) == true) {
        gTownMenu_MESSAGE.addMessage(getMessageNo(18));
        return;
    }
    if (MenuStatusInfo::isCarriagePosition(activeChara_, MenuStatusInfo::POSITION_CARRIAGE_OUT) == true) {
        gTownMenu_MESSAGE.addMessage(getMessageNo(19));
    }
    else {
        gTownMenu_MESSAGE.addMessage(getMessageNo(20), getMessageNo(21));
    }
    status::g_Menu.targetIndex_ = activeCharaIndex_;
    mode_ = MODE_LEAVE;
}

THUMB void MaterielMenu_LUIDA_LEAVE_MESSAGE::menuUpdate()
{
    if (gTownMenu_MESSAGE.isOpen() == true) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
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

THUMB int MaterielMenu_LUIDA_LEAVE_MESSAGE::getMessageNo(int index)
{
    return dq5::level::LuidaMessage::getRecord(index)->getMessage1();
}

THUMB void MaterielMenu_LUIDA_LEAVE_MESSAGE::selectYes()
{
    switch (mode_) {
        case MODE_START:
            break;
        case MODE_LEAVE:
            leavePlayer();
            break;
        case MODE_RETURN:
            menu::MaterielMenuPlayerControl::getSingleton()->activeChara_ = 0;
            close();
            gMaterielMenu_LUIDA_LEAVE_PLAYER.open();
            break;
        case MODE_END:
            returnRoot();
            break;
    }
}

THUMB void MaterielMenu_LUIDA_LEAVE_MESSAGE::selectNo()
{
    switch (mode_) {
        case MODE_START:
        case MODE_LEAVE:
        case MODE_RETURN:
            break;
        case MODE_END:
            returnRoot();
            break;
    }
}

THUMB void MaterielMenu_LUIDA_LEAVE_MESSAGE::leavePlayer()
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
    status::PlayerDataAll::setRuidaFlag(activeCharaIndex_, true);
    cmn::GameManager::getSingleton().resetParty();
    status::g_Menu.bookingFlag_ = menu::BOOKING_LUIDA;
    status::g_Menu.returnMenuType_ = 5;
    MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
}

THUMB void MaterielMenu_LUIDA_LEAVE_MESSAGE::returnMenuMessage()
{
    bool returnSelectPlayer = false;
    int playerCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    if (playerCount > 1) {
        for (int i = 0; i < playerCount; i++) {
            if (MenuStatusInfo::getPlayerIndex(i) != 1) {
                if (!MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_FRIEND_MONSTER)) {
                    returnSelectPlayer = true;
                }
                break;
            }
        }
    }
    if (status::g_Menu.playerItemFlag_ == 1) {
        status::g_Menu.playerItemFlag_ = 0;
        if (returnSelectPlayer == true) {
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(23));
            mode_ = MODE_RETURN;
        }
        else {
            returnRoot();
        }
    }
    else {
        gTownMenu_MESSAGE.openMessageForTALK();
        TextAPI::setMACRO0(0x12, 0x50000000, status::g_Menu.targetIndex_);
        gTownMenu_MESSAGE.addMessage(getMessageNo(22));
        if (returnSelectPlayer == true) {
            gTownMenu_MESSAGE.addMessage(getMessageNo(23));
            mode_ = MODE_RETURN;
        }
        else {
            mode_ = MODE_END;
        }
    }
    status::g_Menu.targetIndex_ = 0;
}

THUMB void MaterielMenu_LUIDA_LEAVE_MESSAGE::returnRoot()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(28));
    gTownMenu_MESSAGE.addMessageWAITKEY();
    close();
    gMaterielMenu_LUIDA_ROOT.setActiveMenu(1);
    gMaterielMenu_LUIDA_ROOT.open();
}
