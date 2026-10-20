#include "ov027/materielmenu/shop/MaterielMenu_SHOP_WHOSE.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_BUYMENU.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_EQUIPCHECK.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_ROOT.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/global/Global.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

THUMB void MaterielMenu_SHOP_WHOSE::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
    mode_ = 0;
    endMessage_ = 0;
    activeItem_ = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
    navigator_.setupBase();
}

THUMB void MaterielMenu_SHOP_WHOSE::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menu::MenuTemplate_materiel::MATERIEL_ICON32_5x2(&menuItem_, menuItem_.active_, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) + 1);
}

THUMB void MaterielMenu_SHOP_WHOSE::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() == false) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        drawShopWhoseScreen(0, 0);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_SHOP_WHOSE::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            selectYes();
            return;
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            selectNo();
            return;
        }
        return;
    }
    navigator_.setup(5, 2, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) + 1);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(menuItem_.active_);
        if (result == 3) {
            close();
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->cancel());
            gTownMenu_MESSAGE.addMessageWAITKEY();
            gMaterielMenu_SHOP_ROOT.open();
            gMaterielMenu_SHOP_ROOT.mode_ = MaterielMenu_SHOP_ROOT::SHOP_MESWAIT;
        }
        if (result == 2) {
            haveMaxCheck();
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_SHOP_WHOSE::haveMaxCheck()
{
    int active = menuItem_.active_;
    if (active == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        MaterielMenu_SHOP_MANAGER::getSingleton()->buyItem(activeItem_, active);
        TextAPI::setMACRO0(0x54, 0xf0000000, MaterielMenu_SHOP_MANAGER::getSingleton()->getItemQuantity(activeItem_));
        TextAPI::setMACRO0(10, 0x40000000, MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(activeItem_));
        int mes[2] = {0, 0};
        for (int i = 0; i < 2; i++) {
            mes[i] = 0;
        }
        int portSelmi = getPortSelmiMes();
        if (MenuStatusInfo::getGold() < MaterielMenu_SHOP_MANAGER::getSingleton()->getMinimumPrice()) {
            MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->buyToSack(false, mes);
            showMessage(mes[0], portSelmi);
            endMessage_ = mes[1];
            mode_ = 8;
            return;
        }
        MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->buyToSack(true, mes);
        gTownMenu_MESSAGE.openMessageForTALK();
        gTownMenu_MESSAGE.addMessage(mes[0]);
        if (portSelmi != 0) {
            gTownMenu_MESSAGE.addMessage(portSelmi);
        }
        gTownMenu_MESSAGE.addMessage(mes[1]);
        gTownMenu_MESSAGE.setMessageLastCursor(true);
        MaterielMenu_SHOP_MANAGER::getSingleton()->resetItemQuantity();
        mode_ = 7;
        return;
    }
    if (MenuStatusInfo::getPlayerItemCount(active) == 12) {
        TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(active));
        showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->haveItemMax(), 0);
        gTownMenu_MESSAGE.setYesNo();
        mode_ = 1;
        return;
    }
    if (status::UseItem::getEquipItemType(MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(activeItem_)) <= ITEM_ACCESSORY) {
        close();
        gMaterielMenu_SHOP_EQUIPCHECK.open();
        mode_ = 0;
        return;
    }
    gTownMenu_MESSAGE.openMessageForTALK();
    giveBuyItem();
}

THUMB void MaterielMenu_SHOP_WHOSE::selectYes()
{
    switch (mode_) {
        case 0:
            break;
        case 1:
            yesSort();
            break;
        case 2:
            showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->haveWhose(), 0);
            gTownMenu_MESSAGE.setMessageLastCursor(true);
            mode_ = 5;
            break;
        case 3:
            checkMoney();
            break;
        case 4:
            break;
        case 5:
            menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
            mode_ = -1;
            break;
        case 6:
            close();
            gMaterielMenu_SHOP_EQUIPCHECK.open();
            break;
        case 7:
            close();
            gMaterielMenu_SHOP_BUYMENU.open();
            break;
        case 8:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(endMessage_);
            gTownMenu_MESSAGE.addMessageWAITKEY();
            close();
            gMaterielMenu_SHOP_ROOT.open();
            gMaterielMenu_SHOP_ROOT.mode_ = MaterielMenu_SHOP_ROOT::SHOP_MESWAIT;
            break;
    }
}

THUMB void MaterielMenu_SHOP_WHOSE::selectNo()
{
    switch (mode_) {
        case 1:
            showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->haveOther(), 0);
            menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = 2;
            break;
        case 2:
            close();
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->cancel());
            gTownMenu_MESSAGE.addMessageWAITKEY();
            gMaterielMenu_SHOP_ROOT.open();
            gMaterielMenu_SHOP_ROOT.mode_ = MaterielMenu_SHOP_ROOT::SHOP_MESWAIT;
            mode_ = 0;
            break;
        case 3:
            checkMoney();
            break;
    }
}

THUMB void MaterielMenu_SHOP_WHOSE::yesSort()
{
    int active = menuItem_.active_;
    TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(active));
    if (MenuStatusInfo::isPlayerItemSort(active) == false) {
        showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->haveSomething(), MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->haveOther());
        gTownMenu_MESSAGE.setYesNo();
        mode_ = 2;
        return;
    }
    MenuStatusInfo::sortPlayerItem(active);
    showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->sortEnd(), 0);
    gTownMenu_MESSAGE.setMessageLastCursor(true);
    if (status::UseItem::getEquipItemType(MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(activeItem_)) <= ITEM_ACCESSORY) {
        mode_ = 6;
        return;
    }
    giveBuyItem();
}

THUMB void MaterielMenu_SHOP_WHOSE::checkMoney()
{
    int haveItemOver = 0;
    int haveNoMoney = 0;
    int mes[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        mes[i] = 0;
    }
    int portSelmi = getPortSelmiMes();
    if (!MaterielMenu_SHOP_MANAGER::getSingleton()->buyItem(activeItem_, menuItem_.active_)) {
        haveItemOver = 1;
    }
    if (MenuStatusInfo::getGold() < MaterielMenu_SHOP_MANAGER::getSingleton()->getMinimumPrice()) {
        haveNoMoney = 1;
    }
    int count = MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->checkMoney(haveItemOver, haveNoMoney, mes);
    gTownMenu_MESSAGE.openMessageForTALK();
    if (haveNoMoney) {
        if (count == 1) {
            if (portSelmi != 0) {
                gTownMenu_MESSAGE.addMessage(portSelmi);
            }
            gTownMenu_MESSAGE.addMessageNOWAIT(mes[0]);
        }
        else {
            gTownMenu_MESSAGE.addMessage(mes[0]);
            if (portSelmi != 0) {
                gTownMenu_MESSAGE.addMessage(portSelmi);
            }
            gTownMenu_MESSAGE.addMessageNOWAIT(mes[1]);
        }
        gTownMenu_MESSAGE.addMessageWAITKEY();
        close();
        gMaterielMenu_SHOP_ROOT.open();
        gMaterielMenu_SHOP_ROOT.mode_ = MaterielMenu_SHOP_ROOT::SHOP_MESWAIT;
        return;
    }
    if (count == 1) {
        if (portSelmi != 0) {
            gTownMenu_MESSAGE.addMessage(portSelmi);
        }
        gTownMenu_MESSAGE.addMessage(mes[0]);
    }
    else {
        gTownMenu_MESSAGE.addMessage(mes[0]);
        if (portSelmi != 0) {
            gTownMenu_MESSAGE.addMessage(portSelmi);
        }
        gTownMenu_MESSAGE.addMessage(mes[1]);
    }
    gTownMenu_MESSAGE.setMessageLastCursor(true);
    for (int i = 0; i < MaterielMenu_SHOP_MANAGER::getSingleton()->getSellItemCount(); i++) {
        MaterielMenu_SHOP_MANAGER::getSingleton()->setItemQuantity(i, 1);
    }
    close();
    gMaterielMenu_SHOP_BUYMENU.open();
    gMaterielMenu_SHOP_BUYMENU.unk_80 = 1;
}

THUMB void MaterielMenu_SHOP_WHOSE::giveBuyItem()
{
    int active = menuItem_.active_;
    bool isBasha = MenuStatusInfo::isCarriagePosition(active, MenuStatusInfo::POSITION_CARRIAGE_IN);
    bool isDeath = MenuStatusInfo::isPlayerCondition(active, MenuStatusInfo::CONDITION_DEATH);
    TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(active));
    gTownMenu_MESSAGE.addMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->getItem(isBasha, isDeath));
    gTownMenu_MESSAGE.setMessageLastCursor(true);
    mode_ = 3;
}

THUMB void MaterielMenu_SHOP_WHOSE::showMessage(int mes1, int mes2)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(mes1);
    if (mes2 != 0) {
        gTownMenu_MESSAGE.addMessage(mes2);
    }
}

THUMB int MaterielMenu_SHOP_WHOSE::getPortSelmiMes()
{
    int mes = 0;
    if (g_Global.getMapNameId() == 0x9b && UnkDssRand::rand(3) == 0) {
        mes = MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->portSelmi();
        MenuStatusInfo::addFukuroItem(0xb3, 1);
    }
    return mes;
}
