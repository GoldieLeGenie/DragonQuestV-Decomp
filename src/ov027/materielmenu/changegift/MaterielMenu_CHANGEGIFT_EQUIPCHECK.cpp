#pragma ipa file
#include "ov027/materielmenu/changegift/MaterielMenu_CHANGEGIFT_EQUIPCHECK.hpp"
#include "ov027/materielmenu/changegift/MaterielMenu_CHANGEGIFT_ROOT.hpp"
#include "ov027/materielmenu/changegift/MaterielMenu_CHANGEGIFT_SELECTCHARA.hpp"
#include "ov027/materielmenu/changegift/MaterielMenu_CHANGEGIFT_SELECTGIFT.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void MaterielMenu_CHANGEGIFT_EQUIPCHECK::menuExecute()
{
}

THUMB void MaterielMenu_CHANGEGIFT_EQUIPCHECK::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    mode_ = ITEM_NORMAL;
    fukuro_ = 0;
    activeChara_ = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
    if (activeChara_ == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        fukuro_ = 1;
    }
    menu::MaterielMenuPlayerControl* control = menu::MaterielMenuPlayerControl::getSingleton();
    itemID_ = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(control->activeItem_);
}

THUMB void MaterielMenu_CHANGEGIFT_EQUIPCHECK::menuDraw()
{
    unkfunc_0217bfe8();
}

THUMB void MaterielMenu_CHANGEGIFT_EQUIPCHECK::menuUpdate()
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
    if (mode_ == ITEM_NORMAL) {
        checkTarget();
    }
}

THUMB void MaterielMenu_CHANGEGIFT_EQUIPCHECK::checkTarget()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menu::MaterielMenuPlayerControl::getSingleton();
    if (fukuro_ == 0) {
        TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara_));
    }
    if (fukuro_ == 1) {
        getGift();
        openMessage(7, 0);
        mode_ = ITEM_COIN_CHECK;
        return;
    }
    if (MenuStatusInfo::getPlayerItemCount(activeChara_) == 12) {
        openMessage(8, 0);
        gTownMenu_MESSAGE.setYesNo();
        mode_ = ITEM_HAVEMAX;
        return;
    }
    checkEquipItem();
}

THUMB void MaterielMenu_CHANGEGIFT_EQUIPCHECK::selectYes()
{
    switch (mode_) {
        case ITEM_NORMAL:
            break;
        case ITEM_HAVEMAX:
            if (MenuStatusInfo::isPlayerItemSort(activeChara_) == true) {
                MenuStatusInfo::sortPlayerItem(activeChara_);
                openMessage(0xb, 0);
                mode_ = ITEM_SORT;
                return;
            }
            TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara_));
            openMessage(9, 10);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = ITEM_RETURN_CHARA;
            break;
        case ITEM_EQUIP: {
            ItemType type = status::UseItem::getEquipItemType(itemID_);
            MenuStatusInfo::getPlayerEquipItemID(activeChara_, type, 0);
            getGift();
            int count = MenuStatusInfo::getPlayerItemCount(activeChara_) - 1;
            MenuStatusInfo::setEquipItem(activeChara_, count, type);
            if (fukuro_ == 0) {
                TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara_));
            }
            TextAPI::setMACRO0(10, 0x40000000, itemID_);
            cmn::g_talkSound.setOrderMessage(0x31);
            cmn::g_talkSound.setOrderMessage(0x30);
            cmn::g_talkSound.setMessageSound(2, -1);
            openMessage(0xe, 0xf);
            ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(cmn::g_cmnPartyInfo.ctrlID_));
            mode_ = ITEM_COIN_CHECK;
            break;
        }
        case ITEM_NOEQUIP:
            aliveCheck();
            break;
        case ITEM_SORT:
            checkEquipItem();
            break;
        case ITEM_RETURN_CHARA:
            close();
            gMaterielMenu_CHANGEGIFT_SELECTCHARA.open();
            break;
        case ITEM_RETURN_ITEM:
            openMessage(3, 0);
            menu::MaterielMenuPlayerControl::getSingleton()->activeItem_ = 0;
            close();
            gMaterielMenu_CHANGEGIFT_SELECTGIFT.open();
            break;
        case ITEM_COIN_CHECK:
            if (MenuStatusInfo::getCoin() >= MaterielMenu_SHOP_MANAGER::getSingleton()->getItemPrice(0)) {
                openMessage(0x13, 0);
                gTownMenu_MESSAGE.setYesNo();
                mode_ = ITEM_RETURN_ITEM;
                return;
            }
            openMessage(0x14, 0);
            mode_ = ITEM_END;
            break;
        case ITEM_END:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_CHANGEGIFT_EQUIPCHECK::selectNo()
{
    switch (mode_) {
        case ITEM_NORMAL:
            break;
        case ITEM_HAVEMAX:
            openMessage(10, 0);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = ITEM_RETURN_CHARA;
            break;
        case ITEM_EQUIP:
            aliveCheck();
            break;
        case ITEM_NOEQUIP:
        case ITEM_RETURN_CHARA:
            openMessage(0x13, 0);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = ITEM_RETURN_ITEM;
            break;
        case ITEM_SORT:
            break;
        case ITEM_RETURN_ITEM:
            openMessage(0x14, 0);
            mode_ = ITEM_END;
            break;
    }
}

THUMB void MaterielMenu_CHANGEGIFT_EQUIPCHECK::aliveCheck()
{
    getGift();
    gTownMenu_MESSAGE.openMessageForTALK();
    if (fukuro_ == 0) {
        TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara_));
    }
    if (MenuStatusInfo::isCarriagePosition(activeChara_, MenuStatusInfo::POSITION_CARRIAGE_IN) == true) {
        gTownMenu_MESSAGE.addMessage(gMaterielMenu_CHANGEGIFT_ROOT.getMessageNo(0x10));
    }
    else if (MenuStatusInfo::isPlayerCondition(activeChara_, MenuStatusInfo::CONDITION_DEATH) == false) {
        gTownMenu_MESSAGE.addMessage(gMaterielMenu_CHANGEGIFT_ROOT.getMessageNo(0x11));
    }
    else {
        gTownMenu_MESSAGE.addMessage(gMaterielMenu_CHANGEGIFT_ROOT.getMessageNo(0x12));
    }
    mode_ = ITEM_COIN_CHECK;
}

THUMB void MaterielMenu_CHANGEGIFT_EQUIPCHECK::getGift()
{
    menu::MaterielMenuPlayerControl* control = menu::MaterielMenuPlayerControl::getSingleton();
    int price = MaterielMenu_SHOP_MANAGER::getSingleton()->getItemPrice(control->activeItem_);
    if (fukuro_ == 1) {
        MenuStatusInfo::addFukuroItem(itemID_, 1);
    }
    else {
        MenuStatusInfo::addPlayerItem(activeChara_, itemID_);
    }
    MenuStatusInfo::setCoin(MenuStatusInfo::getCoin() - price);
}

THUMB void MaterielMenu_CHANGEGIFT_EQUIPCHECK::checkEquipItem()
{
    if (status::UseItem::getEquipItemType(itemID_) > ITEM_ACCESSORY) {
        aliveCheck();
        return;
    }
    if (MenuStatusInfo::isPlayerEquipEnable(activeChara_, itemID_) == false) {
        TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara_));
        TextAPI::setMACRO0(10, 0x40000000, itemID_);
        openMessage(0xc, 0);
        gTownMenu_MESSAGE.setYesNo();
        mode_ = ITEM_NOEQUIP;
        return;
    }
    TextAPI::setMACRO0(10, 0x40000000, itemID_);
    openMessage(0xd, 0);
    gTownMenu_MESSAGE.setYesNo();
    mode_ = ITEM_EQUIP;
}

THUMB void MaterielMenu_CHANGEGIFT_EQUIPCHECK::openMessage(int mes1, int mes2)
{
    int m1 = gMaterielMenu_CHANGEGIFT_ROOT.getMessageNo(mes1);
    int m2 = gMaterielMenu_CHANGEGIFT_ROOT.getMessageNo(mes2);
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(m1);
    if (m2 != 0) {
        gTownMenu_MESSAGE.addMessage(m2);
    }
}
