#include "ov027/materielmenu/shop/MaterielMenu_SHOP_EQUIPCHECK.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_BUYMENU.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_ROOT.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_WHOSE.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/global/Global.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

THUMB void MaterielMenu_SHOP_EQUIPCHECK::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    mode_ = 0;
    haveItemOver_ = 0;
    getItemFlag_ = 0;
    ctrlID_ = cmn::g_cmnPartyInfo.ctrlID_;
    if (MaterielMenu_SHOP_MANAGER::getSingleton()->getShopType() == MaterielMenu_SHOP_MANAGER::SHOP_TYPE_SUGOROKU) {
        ctrlID_ = -1;
    }
}

THUMB void MaterielMenu_SHOP_EQUIPCHECK::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            yesAdmin();
            return;
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            noAdmin();
        }
        return;
    }
    if (mode_ == 0) {
        messageSetup();
    }
}

THUMB void MaterielMenu_SHOP_EQUIPCHECK::yesAdmin()
{
    int haveNoMoney = 0;
    if (MenuStatusInfo::getGold() == 0) {
        haveNoMoney = 1;
    }
    switch (mode_) {
        case 0:
            messageSetup();
            return;
        case 1:
            break;
        case 2: {
            int active = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
            int chara = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
            int mes[2] = {0, 0};
            for (int i = 0; i < 2; i++) {
                mes[i] = 0;
            }
            ItemType type = status::UseItem::getEquipItemType(MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(active));
            if (!MaterielMenu_SHOP_MANAGER::getSingleton()->buyItem(active, chara)) {
                haveItemOver_ = 1;
            }
            int itemID = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(active);
            int count = MenuStatusInfo::getPlayerItemCount(chara) - 1;
            MenuStatusInfo::setEquipItem(chara, count, type);
            TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(chara));
            TextAPI::setMACRO0(10, 0x40000000, itemID);
            MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->equipItem(mes);
            if (ctrlID_ == -1) {
                cmn::g_talkSound.setOrderMessage(0x32);
            }
            else {
                cmn::g_talkSound.setOrderMessage(cmn::g_talkSound.getCharacterVoice(ctrlID_));
            }
            cmn::g_talkSound.setOrderMessage(0x30);
            cmn::g_talkSound.setMessageSound(2, ctrlID_);
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(mes[0], mes[1]);
            gTownMenu_MESSAGE.setMessageLastCursor(true);
            if (ctrlID_ == -1) {
                ui_MsgSndSet(0x32);
            }
            else {
                ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(ctrlID_));
            }
            getItemFlag_ = 1;
            mode_ = 5;
            return;
        }
        case 3:
            giveItem();
            return;
        case 4:
            break;
        case 5: {
            int mes[3] = {0, 0, 0};
            for (int i = 0; i < 3; i++) {
                mes[i] = 0;
            }
            int count = MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->checkMoney(haveItemOver_, haveNoMoney, mes);
            checkMoneyMessage(mes, count, haveNoMoney);
            if (haveNoMoney == 1) {
                returnRoot();
                return;
            }
            mode_ = 6;
            return;
        }
        case 6:
            for (int i = 0; i < MaterielMenu_SHOP_MANAGER::getSingleton()->getSellItemCount(); i++) {
                MaterielMenu_SHOP_MANAGER::getSingleton()->setItemQuantity(i, 1);
            }
            if (haveNoMoney == 1) {
                returnRoot();
                return;
            }
            close();
            gTownMenu_MESSAGE.setMessageLastCursor(true);
            menu::MaterielMenuPlayerControl::getSingleton()->activeItem_ = 0;
            gMaterielMenu_SHOP_BUYMENU.open();
            break;
    }
}

THUMB void MaterielMenu_SHOP_EQUIPCHECK::noAdmin()
{
    int chara = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
    int active = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
    int mes[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        mes[i] = 0;
    }
    switch (mode_) {
        case 0:
            messageSetup();
            return;
        case 1:
            break;
        case 2:
            giveItem();
            return;
        case 3: {
            int count = MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->checkMoney(haveItemOver_, 0, mes);
            checkMoneyMessage(mes, count, 0);
            ItemType type = status::UseItem::getEquipItemType(MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(active));
            if (status::UseItem::isCurse(MenuStatusInfo::getPlayerEquipItemID(chara, type, 0)) == true) {
                mode_ = 6;
                return;
            }
            for (int i = 0; i < MaterielMenu_SHOP_MANAGER::getSingleton()->getSellItemCount(); i++) {
                MaterielMenu_SHOP_MANAGER::getSingleton()->setItemQuantity(i, 1);
            }
            close();
            gMaterielMenu_SHOP_BUYMENU.open();
            return;
        }
        case 4: {
            if (!MaterielMenu_SHOP_MANAGER::getSingleton()->buyItem(active, chara)) {
                haveItemOver_ = 1;
            }
            int itemID = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(active);
            int count = MenuStatusInfo::getPlayerItemCount(chara) - 1;
            MenuStatusInfo::setEquipItem(chara, count, status::UseItem::getEquipItemType(itemID));
            TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(chara));
            TextAPI::setMACRO0(10, 0x40000000, itemID);
            MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->equipItem(mes);
            if (ctrlID_ == -1) {
                cmn::g_talkSound.setOrderMessage(0x32);
            }
            else {
                cmn::g_talkSound.setOrderMessage(cmn::g_talkSound.getCharacterVoice(ctrlID_));
            }
            cmn::g_talkSound.setOrderMessage(0x30);
            cmn::g_talkSound.setMessageSound(2, ctrlID_);
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(mes[0], mes[1]);
            close();
            gMaterielMenu_SHOP_WHOSE.open();
            gMaterielMenu_SHOP_WHOSE.mode_ = 4;
            return;
        }
        case 5:
            break;
        case 6:
            for (int i = 0; i < MaterielMenu_SHOP_MANAGER::getSingleton()->getSellItemCount(); i++) {
                MaterielMenu_SHOP_MANAGER::getSingleton()->setItemQuantity(i, 1);
            }
            close();
            gMaterielMenu_SHOP_BUYMENU.open();
            break;
    }
}

THUMB void MaterielMenu_SHOP_EQUIPCHECK::giveItem()
{
    int chara = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
    int active = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
    int index = MenuStatusInfo::getPlayerIndex(chara);
    gTownMenu_MESSAGE.close();
    if (!MaterielMenu_SHOP_MANAGER::getSingleton()->buyItem(active, chara)) {
        haveItemOver_ = 1;
    }
    bool isBasha = MenuStatusInfo::isCarriagePosition(chara, MenuStatusInfo::POSITION_CARRIAGE_IN);
    bool isDeath = MenuStatusInfo::isPlayerCondition(chara, MenuStatusInfo::CONDITION_DEATH);
    TextAPI::setMACRO0(0x12, 0x50000000, index);
    showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->getItem(isBasha, isDeath));
    gTownMenu_MESSAGE.setMessageLastCursor(true);
    getItemFlag_ = 1;
    mode_ = 5;
}

THUMB void MaterielMenu_SHOP_EQUIPCHECK::messageSetup()
{
    int chara = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
    menu::MaterielMenuPlayerControl* control = menu::MaterielMenuPlayerControl::getSingleton();
    int itemID = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(control->activeItem_);
    bool equip = MenuStatusInfo::isPlayerEquipEnable(chara, itemID);
    if (equip == true) {
        mode_ = 2;
    }
    else {
        mode_ = 3;
    }
    TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(chara));
    TextAPI::setMACRO0(10, 0x40000000, itemID);
    showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->checkEquip(equip));
    gTownMenu_MESSAGE.setYesNo();
}

THUMB void MaterielMenu_SHOP_EQUIPCHECK::showMessage(int mes)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(mes);
}

THUMB void MaterielMenu_SHOP_EQUIPCHECK::returnRoot()
{
    gTownMenu_MESSAGE.addMessageWAITKEY();
    close();
    gMaterielMenu_SHOP_ROOT.open();
    gMaterielMenu_SHOP_ROOT.mode_ = MaterielMenu_SHOP_ROOT::SHOP_MESWAIT;
}

THUMB void MaterielMenu_SHOP_EQUIPCHECK::checkMoneyMessage(int* mes, int mesCount, int haveNoMoney)
{
    int portSelmi = 0;
    if (getItemFlag_ == 1 && g_Global.getMapNameId() == 0x9b && UnkDssRand::rand(3) == 0) {
        portSelmi = MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->portSelmi();
        MenuStatusInfo::addFukuroItem(0xb3, 1);
    }
    gTownMenu_MESSAGE.openMessageForTALK();
    if (haveNoMoney) {
        if (mesCount == 1) {
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
        return;
    }
    if (mesCount == 1) {
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
}
