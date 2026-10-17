#include "ov027/materielmenu/medalking/MaterielMenuMedalKingManager.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov027/leveldata/MedalMessage.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"

using menu::MenuStatusInfo;

inline dq5::level::MedalMessage* dq5::level::MedalMessage::getRecord(int index)
{
    return (MedalMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::MedalMessage::getMessage1()
{
    return message1;
}

inline char dq5::level::MedalMessage::getVocalSound()
{
    return byte_1 & 1;
}

THUMB int MaterielMenuMedalKingManager::getItemID()
{
    menu::MaterielMenuPlayerControl* control = menu::MaterielMenuPlayerControl::getSingleton();
    return MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(control->activeItem_);
}

THUMB int MaterielMenuMedalKingManager::getItemPrice(int index)
{
    return MaterielMenu_SHOP_MANAGER::getSingleton()->getItemPrice(index);
}

THUMB bool MaterielMenuMedalKingManager::isNeedMedal()
{
    menu::MaterielMenuPlayerControl* control = menu::MaterielMenuPlayerControl::getSingleton();
    int price = MaterielMenu_SHOP_MANAGER::getSingleton()->getItemPrice(control->activeItem_);
    if (MenuStatusInfo::getMedal() >= price) {
        return true;
    }
    return false;
}

THUMB void MaterielMenuMedalKingManager::getItem()
{
    int active = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
    int itemIndex = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
    int itemID = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(itemIndex);
    int price = MaterielMenu_SHOP_MANAGER::getSingleton()->getItemPrice(itemIndex);
    if (active == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        MenuStatusInfo::addFukuroItem(itemID, 1);
    }
    else {
        MenuStatusInfo::addPlayerItem(active, itemID);
    }
    MenuStatusInfo::setMedal(MenuStatusInfo::getMedal() - price);
}

THUMB void MaterielMenuMedalKingManager::showMessage(int mesIndex0, int mesIndex1, int mesIndex2)
{
    dq5::level::MedalMessage* pMedalmes = dq5::level::MedalMessage::getRecord(mesIndex0);
    if (pMedalmes->getVocalSound() == 1) {
        gTownMenu_MESSAGE.openMessageForTALK();
    }
    else {
        gTownMenu_MESSAGE.openMessageForMENU();
    }
    gTownMenu_MESSAGE.addMessage(pMedalmes->getMessage1());
    if (mesIndex1 != 0) {
        gTownMenu_MESSAGE.addMessage(dq5::level::MedalMessage::getRecord(mesIndex1)->getMessage1());
    }
    if (mesIndex2 != 0) {
        gTownMenu_MESSAGE.addMessage(dq5::level::MedalMessage::getRecord(mesIndex2)->getMessage1());
    }
    int ctrlID = cmn::g_cmnPartyInfo.ctrlID_;
    ui_MsgSndSet(cmn::g_talkSound.getCharacterVoice(ctrlID));
}
