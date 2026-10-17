#include "ov027/materielmenu/medalking/MaterielMenu_MEDALKING_SELECTCHARA.hpp"
#include "ov027/materielmenu/medalking/MaterielMenuMedalKingManager.hpp"
#include "ov027/materielmenu/medalking/MaterielMenu_MEDALKING_EQUIP.hpp"
#include "ov027/materielmenu/medalking/MaterielMenu_MEDALKING_SELECTITEM.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

THUMB void MaterielMenu_MEDALKING_SELECTCHARA::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    m_mode = MODE_SELECT_CHARA;
}

THUMB void MaterielMenu_MEDALKING_SELECTCHARA::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menu::MenuTemplate_materiel::MATERIEL_ICON32_5x2(&menuItem_, menuItem_.active_, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) + 1);
}

THUMB void MaterielMenu_MEDALKING_SELECTCHARA::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == false) {
        unkfunc_0217be90(2, 0);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_MEDALKING_SELECTCHARA::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        TextAPI::setMACRO0(10, 0x40000000, MaterielMenuMedalKingManager::getItemID());
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            selectYes();
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            selectNo();
        }
        return;
    }
    navigator_.setup(5, 2, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) + 1);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara((char)menuItem_.active_);
        if (result == 3) {
            MaterielMenuMedalKingManager::showMessage(0x12, 0, 0);
            gTownMenu_MESSAGE.setYesNo();
            m_mode = MODE_CANCEL;
        }
        if (result == 2) {
            int active = menuItem_.active_;
            if (active == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
                selectReturnMessage();
            }
            else if (MenuStatusInfo::getPlayerItemCount(menuItem_.active_) == 12) {
                TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(menuItem_.active_));
                MaterielMenuMedalKingManager::showMessage(9, 0, 0);
                gTownMenu_MESSAGE.setYesNo();
                m_mode = MODE_SORT;
            }
            else {
                close();
                gMaterielMenu_MEDALKING_EQUIP.open();
            }
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_MEDALKING_SELECTCHARA::selectYes()
{
    gTownMenu_MESSAGE.close();
    switch (m_mode) {
        case MODE_SELECT_CHARA:
            break;
        case MODE_NEXT:
            close();
            gMaterielMenu_MEDALKING_EQUIP.open();
            break;
        case MODE_SORT:
            if (MenuStatusInfo::isPlayerItemSort(menuItem_.active_) == true) {
                MenuStatusInfo::sortPlayerItem(menuItem_.active_);
                MaterielMenuMedalKingManager::showMessage(0xc, 0, 0);
                m_mode = MODE_NEXT;
                return;
            }
            TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(menuItem_.active_));
            MaterielMenuMedalKingManager::showMessage(10, 0xb, 0);
            gTownMenu_MESSAGE.setYesNo();
            m_mode = MODE_RETURN;
            break;
        case MODE_RETURN:
            break;
        case MODE_CANCEL:
            close();
            gMaterielMenu_MEDALKING_SELECTITEM.open();
            break;
        case MODE_END:
            unkfunc_0204c9c8();
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_MEDALKING_SELECTCHARA::selectNo()
{
    gTownMenu_MESSAGE.close();
    switch (m_mode) {
        case MODE_SELECT_CHARA:
        case MODE_NEXT:
            break;
        case MODE_SORT:
            MaterielMenuMedalKingManager::showMessage(0xb, 0, 0);
            m_mode = MODE_RETURN;
            break;
        case MODE_RETURN:
            MaterielMenuMedalKingManager::showMessage(0x12, 0, 0);
            gTownMenu_MESSAGE.setYesNo();
            m_mode = MODE_CANCEL;
            break;
        case MODE_CANCEL:
            MaterielMenuMedalKingManager::showMessage(0x13, 0, 0);
            m_mode = MODE_END;
            break;
        case MODE_END:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_MEDALKING_SELECTCHARA::selectReturnMessage()
{
    MaterielMenuMedalKingManager::getItem();
    if (MenuStatusInfo::getMedal() < MaterielMenuMedalKingManager::getItemPrice(0)) {
        MaterielMenuMedalKingManager::showMessage(0x11, 0x13, 0);
        m_mode = MODE_END;
        return;
    }
    MaterielMenuMedalKingManager::showMessage(0x11, 0x12, 0);
    gTownMenu_MESSAGE.setYesNo();
    m_mode = MODE_CANCEL;
}
