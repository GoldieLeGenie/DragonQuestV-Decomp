#pragma ipa file
#include "ov019/townmenu/town_item/TownMenu_ITEM_EQUIPCHECK.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectChara.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectTargetChara.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectTargetItem.hpp"
#include "ov019/townmenu/town_item/UnkTownMenuItemCharaSelect.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline void TownMenu_ITEM_EQUIPCHECK::menuExecute()
{
}

THUMB void TownMenu_ITEM_EQUIPCHECK::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    target_ = TownMenuPlayerControl::getSingleton()->targetChara_;
    if (TownMenuPlayerControl::getSingleton()->targetItem_ == -1) {
        targetItem_ = (char)(MenuStatusInfo::getPlayerItemCount(target_) - 1);
    } else {
        targetItem_ = TownMenuPlayerControl::getSingleton()->getTargetItemIndexToAll();
    }
    itemID_ = MenuStatusInfo::getPlayerItemID(target_, targetItem_);
    mode_ = 0;
}

THUMB void TownMenu_ITEM_EQUIPCHECK::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    unkfunc_0201b158();
}

THUMB void TownMenu_ITEM_EQUIPCHECK::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            equipItem();
        } else if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            close();
            openItemRoot();
        }
        return;
    }
    if (mode_ == 2) {
        openItemRoot();
    }
}

THUMB void TownMenu_ITEM_EQUIPCHECK::equipItem()
{
    switch (mode_) {
        case 0:
            if (MenuStatusInfo::isPlayerEquipEnable(target_, itemID_)) {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xc4229);
                gTownMenu_MESSAGE.setYesNo();
                mode_ = 1;
            } else {
                openItemRoot();
            }
            break;
        case 1: {
            mode_ = 2;
            ItemType equipType = status::UseItem::getEquipItemType(itemID_);
            MenuStatusInfo::setEquipItem(target_, targetItem_, equipType);
            gTownMenu_MESSAGE.openMessageForMENU();
            TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(target_));
            TextAPI::setMACRO0(10, 0x40000000, itemID_);
            if (MenuStatusInfo::isPlayerCondition(target_, MenuStatusInfo::CONDITION_DEATH) == true) {
                gTownMenu_MESSAGE.addMessage(0xc421f);
            } else {
                gTownMenu_MESSAGE.addMessage(0xc421d);
            }
            break;
        }
        case 2:
            openItemRoot();
            break;
    }
}

THUMB void TownMenu_ITEM_EQUIPCHECK::openItemRoot()
{
    close();
    gTownMenuItemSelectTargetChara.close();
    gTownMenuItemSelectTargetItem.close();
    int count;
    if (TownMenuPlayerControl::getSingleton()->activeFukuro_) {
        count = MenuStatusInfo::getFukuroItemCount();
    } else {
        count = MenuStatusInfo::getPlayerItemCount(TownMenuPlayerControl::getSingleton()->activeChara_);
    }
    if (count == 0) {
        data_ov019_02183524.fromMateriel_ = 0;
        data_ov019_02183524.open();
    } else {
        gTownMenuItemSelectChara.meisanhinFlag_ = 0;
        gTownMenuItemSelectChara.open();
    }
}
