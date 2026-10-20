#pragma ipa file
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_VALUE.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_ROOT.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_WHO_SELL.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void MaterielMenu_SHOP_VALUE::menuExecute()
{
}

inline void MaterielMenu_SHOP_VALUE::menuDraw()
{
}

inline void menu::MenuPlayerControl::setActiveItem(short item)
{
    activeItem_ = item;
}

inline void menu::MaterielMenuPlayerControl::setActiveItemPage(int active)
{
    activeItemPage_ = active;
}

THUMB void MaterielMenu_SHOP_VALUE::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    endMessage_ = 0;
    isEndMessage_ = 0;
    activeChara_ = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
    activeItem_ = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
    page_ = menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_;
    int itemID;
    if (activeChara_ == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        fukuro_ = 1;
        itemID = MenuStatusInfo::getFukuroItemID(activeItem_, page_);
    }
    else {
        fukuro_ = 0;
        menu::MaterielMenuPlayerControl* control = menu::MaterielMenuPlayerControl::getSingleton();
        itemID = MenuStatusInfo::getPlayerItemID(activeChara_, control->activeItem_ + control->activeItemPage_ * 6);
    }
    int price = status::UseItem::getSellPrice(itemID);
    int total = price * MaterielMenu_SHOP_MANAGER::getSingleton()->getSellQuantity();
    int quantity = MaterielMenu_SHOP_MANAGER::getSingleton()->getSellQuantity();
    sellType_ = status::UseItem::getSellType(itemID);
    switch (sellType_) {
        case status::UseItem::SELL_OK:
            TextAPI::setMACRO0(10, 0x40000000, itemID);
            TextAPI::setMACRO0(0x3e, 0xf0000000, total);
            TextAPI::setMACRO0(0x54, 0xf0000000, quantity);
            if (quantity != 1) {
                showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->sellPluralSellOK(), 0, 0);
            }
            else {
                showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->sellOK(), 0, 0);
            }
            gTownMenu_MESSAGE.setYesNo();
            break;
        case status::UseItem::SELL_NG: {
            int mes[3] = {0, 0, 0};
            for (int i = 0; i < 3; i++) {
                mes[i] = 0;
            }
            TextAPI::setMACRO0(10, 0x40000000, itemID);
            if (MaterielMenu_SHOP_MANAGER::getSingleton()->sellOK() == false) {
                MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->sellNG(true, mes);
                showMessage(mes[0], mes[1], 0);
                endMessage_ = mes[2];
                isEndMessage_ = 1;
                return;
            }
            MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->sellNG(false, mes);
            showMessage(mes[0], mes[1], mes[2]);
            gTownMenu_MESSAGE.setMessageLastCursor(true);
            menu::MaterielMenuPlayerControl::getSingleton()->activeItem_ = 0;
            menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_ = 0;
            close();
            gMaterielMenu_SHOP_WHO_SELL.open();
            break;
        }
        case status::UseItem::SELL_DIFFICULT:
            TextAPI::setMACRO0(10, 0x40000000, itemID);
            TextAPI::setMACRO0(0x54, 0xf0000000, quantity);
            showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->sellDifficult(), 0, 0);
            gTownMenu_MESSAGE.setYesNo();
            break;
    }
}

THUMB void MaterielMenu_SHOP_VALUE::menuUpdate()
{
    if (gTownMenu_MESSAGE.isOpen()) {
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

THUMB void MaterielMenu_SHOP_VALUE::selectYes()
{
    if (isEndMessage_ == 1) {
        menu::MaterielMenuPlayerControl::getSingleton()->activeItem_ = 0;
        menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_ = 0;
        gTownMenu_MESSAGE.openMessageForTALK();
        gTownMenu_MESSAGE.addMessageNOWAIT(endMessage_);
        gTownMenu_MESSAGE.addMessageWAITKEY();
        close();
        gMaterielMenu_SHOP_ROOT.open();
        gMaterielMenu_SHOP_ROOT.mode_ = MaterielMenu_SHOP_ROOT::SHOP_MESWAIT;
        return;
    }
    int itemID;
    if (fukuro_ == 1) {
        itemID = MenuStatusInfo::getFukuroItemID(activeItem_, page_);
    }
    else {
        menu::MaterielMenuPlayerControl* control = menu::MaterielMenuPlayerControl::getSingleton();
        itemID = MenuStatusInfo::getPlayerItemID(activeChara_, control->activeItem_ + control->activeItemPage_ * 6);
    }
    int price = status::UseItem::getSellPrice(itemID);
    int total = price * MaterielMenu_SHOP_MANAGER::getSingleton()->getSellQuantity();
    switch (sellType_) {
        case status::UseItem::SELL_OK:
            checkHaveMoney();
            break;
        case status::UseItem::SELL_NG:
            break;
        case status::UseItem::SELL_DIFFICULT: {
            TextAPI::setMACRO0(10, 0x40000000, itemID);
            TextAPI::setMACRO0(0x3e, 0xf0000000, total);
            int quantity = MaterielMenu_SHOP_MANAGER::getSingleton()->getSellQuantity();
            TextAPI::setMACRO0(0x54, 0xf0000000, quantity);
            if (quantity != 1) {
                showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->sellPluralSellOK(), 0, 0);
            }
            else {
                showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->sellOK(), 0, 0);
            }
            gTownMenu_MESSAGE.setYesNo();
            sellType_ = status::UseItem::SELL_OK;
            break;
        }
    }
}

THUMB void MaterielMenu_SHOP_VALUE::selectNo()
{
    switch (sellType_) {
        case status::UseItem::SELL_OK: {
            int mes[2] = {0, 0};
            for (int i = 0; i < 2; i++) {
                mes[i] = 0;
            }
            if (MaterielMenu_SHOP_MANAGER::getSingleton()->sellOK() == false) {
                MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->celectNo(true, mes);
                showMessage(mes[0], 0, 0);
                endMessage_ = mes[1];
                isEndMessage_ = 1;
                return;
            }
            MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->celectNo(false, mes);
            showMessage(mes[0], mes[1], 0);
            gTownMenu_MESSAGE.setMessageLastCursor(true);
            menu::MaterielMenuPlayerControl::getSingleton()->activeItem_ = 0;
            menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_ = 0;
            close();
            gMaterielMenu_SHOP_WHO_SELL.open();
            break;
        }
        case status::UseItem::SELL_NG:
            break;
        case status::UseItem::SELL_DIFFICULT:
            menu::MaterielMenuPlayerControl::getSingleton()->activeItem_ = 0;
            menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_ = 0;
            close();
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->cancel());
            gMaterielMenu_SHOP_ROOT.open();
            gMaterielMenu_SHOP_ROOT.mode_ = MaterielMenu_SHOP_ROOT::SHOP_MESWAIT;
            gTownMenu_MESSAGE.addMessageWAITKEY();
            break;
    }
}

THUMB void MaterielMenu_SHOP_VALUE::checkHaveMoney()
{
    int mes[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        mes[i] = 0;
    }
    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    if (MaterielMenu_SHOP_MANAGER::getSingleton()->sellItem(activeItem_, activeChara_, page_) == true) {
        if (MaterielMenu_SHOP_MANAGER::getSingleton()->sellOK() == false) {
            MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->sellEnd(true, mes);
            showMessage(mes[0], 0, 0);
            endMessage_ = mes[1];
            isEndMessage_ = 1;
        }
        else {
            MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->sellEnd(false, mes);
            showMessage(mes[0], mes[1], 0);
            gTownMenu_MESSAGE.setMessageLastCursor(true);
            menu::MaterielMenuPlayerControl::getSingleton()->activeItem_ = 0;
            menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_ = 0;
            close();
            gMaterielMenu_SHOP_WHO_SELL.open();
        }
    }
    else {
        int index;
        if (activeChara_ == partyCount) {
            int chara = 0;
            while (MenuStatusInfo::isPlayerCondition(chara, MenuStatusInfo::CONDITION_DEATH) == true) {
                chara++;
                if (chara > partyCount) {
                    chara = 0;
                    break;
                }
            }
            index = MenuStatusInfo::getPlayerIndex(chara);
        }
        else {
            index = MenuStatusInfo::getPlayerIndex(activeChara_);
        }
        TextAPI::setMACRO0(0x12, 0x50000000, index);
        MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->overMoney(mes);
        showMessage(mes[0], mes[1], 0);
        endMessage_ = mes[2];
        isEndMessage_ = 1;
    }
    int index = activeItem_ + page_ * 6;
    bool over = false;
    if (activeChara_ == partyCount) {
        if (index >= MenuStatusInfo::getFukuroItemCount()) {
            over = true;
        }
    }
    else if (index >= MenuStatusInfo::getPlayerItemCount(activeChara_)) {
        over = true;
    }
    if (over == true) {
        activeItem_--;
        if (activeItem_ < 0) {
            activeItem_ = 0;
            page_--;
        }
        if (page_ < 0) {
            page_ = 0;
        }
    }
    menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(activeItem_);
    menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(page_);
}

THUMB void MaterielMenu_SHOP_VALUE::showMessage(int mes1, int mes2, int mes3)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(mes1);
    if (mes2 != 0) {
        gTownMenu_MESSAGE.addMessage(mes2);
    }
    if (mes3 != 0) {
        gTownMenu_MESSAGE.addMessage(mes3);
    }
}
