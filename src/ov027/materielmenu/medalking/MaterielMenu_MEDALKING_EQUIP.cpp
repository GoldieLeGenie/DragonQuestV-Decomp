#pragma ipa file
#include "ov027/materielmenu/medalking/MaterielMenu_MEDALKING_EQUIP.hpp"
#include "ov027/materielmenu/medalking/MaterielMenuMedalKingManager.hpp"
#include "ov027/materielmenu/medalking/MaterielMenu_MEDALKING_SELECTITEM.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void MaterielMenu_MEDALKING_EQUIP::menuExecute()
{
}

inline void MaterielMenu_MEDALKING_EQUIP::menuDraw()
{
}

THUMB void MaterielMenu_MEDALKING_EQUIP::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    m_mode = MODE_CHECK;
    m_equipItem = 0;
}

THUMB void MaterielMenu_MEDALKING_EQUIP::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            selectYes();
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            selectNo();
        }
        return;
    }
    if (m_mode == MODE_CHECK) {
        int active = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
        int itemID = MaterielMenuMedalKingManager::getItemID();
        TextAPI::setMACRO0(10, 0x40000000, itemID);
        if (MenuStatusInfo::isPlayerEquipEnable(active, itemID) == true) {
            MaterielMenuMedalKingManager::showMessage(0xe, 0, 0);
            m_mode = MODE_EQUIP;
        }
        else {
            TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(active));
            MaterielMenuMedalKingManager::showMessage(0xd, 0, 0);
            m_mode = MODE_NOEQUIP;
        }
        gTownMenu_MESSAGE.setYesNo();
    }
}

THUMB void MaterielMenu_MEDALKING_EQUIP::selectYes()
{
    gTownMenu_MESSAGE.close();
    switch (m_mode) {
        case MODE_CHECK:
            break;
        case MODE_EQUIP: {
            MaterielMenuMedalKingManager::getItem();
            int active = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
            int index = MenuStatusInfo::getPlayerItemCount(active) - 1;
            m_equipItem = MenuStatusInfo::getPlayerItemID(active, index);
            MenuStatusInfo::setEquipItem(active, index, status::UseItem::getEquipItemType(MenuStatusInfo::getPlayerItemID(active, index)));
            cmn::g_talkSound.setOrderMessage(0x32);
            cmn::g_talkSound.setOrderMessage(0x30);
            cmn::g_talkSound.setMessageSound(2, -1);
            TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(active));
            TextAPI::setMACRO0(10, 0x40000000, m_equipItem);
            if (MenuStatusInfo::getMedal() < MaterielMenuMedalKingManager::getItemPrice(0)) {
                MaterielMenuMedalKingManager::showMessage(0xf, 0x10, 0x13);
                m_mode = MODE_END;
                return;
            }
            MaterielMenuMedalKingManager::showMessage(0xf, 0x10, 0x12);
            gTownMenu_MESSAGE.setYesNo();
            m_mode = MODE_CANCEL;
            break;
        }
        case MODE_NOEQUIP:
            MaterielMenuMedalKingManager::getItem();
            selectReturnMessage();
            break;
        case MODE_EQUIPEND:
            selectReturnMessage();
            break;
        case MODE_CANCEL:
            menu::MaterielMenuPlayerControl::getSingleton()->activeItem_ = 0;
            close();
            gMaterielMenu_MEDALKING_SELECTITEM.open();
            break;
        case MODE_END:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_MEDALKING_EQUIP::selectNo()
{
    gTownMenu_MESSAGE.close();
    switch (m_mode) {
        case MODE_CHECK:
            break;
        case MODE_EQUIP:
            MaterielMenuMedalKingManager::getItem();
            selectReturnMessage();
            break;
        case MODE_NOEQUIP:
            MaterielMenuMedalKingManager::showMessage(0x12, 0, 0);
            gTownMenu_MESSAGE.setYesNo();
            m_mode = MODE_CANCEL;
            break;
        case MODE_EQUIPEND:
            break;
        case MODE_CANCEL:
            MaterielMenuMedalKingManager::showMessage(0x13, 0, 0);
            m_mode = MODE_END;
            break;
        case MODE_END:
            break;
    }
}

THUMB void MaterielMenu_MEDALKING_EQUIP::selectReturnMessage()
{
    if (MenuStatusInfo::getMedal() < MaterielMenuMedalKingManager::getItemPrice(0)) {
        MaterielMenuMedalKingManager::showMessage(0x11, 0x13, 0);
        m_mode = MODE_END;
        return;
    }
    MaterielMenuMedalKingManager::showMessage(0x11, 0x12, 0);
    gTownMenu_MESSAGE.setYesNo();
    m_mode = MODE_CANCEL;
}
