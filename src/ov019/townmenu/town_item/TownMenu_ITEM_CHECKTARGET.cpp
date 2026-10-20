#pragma ipa file
#include "ov019/townmenu/town_item/TownMenu_ITEM_CHECKTARGET.hpp"
#include "ov019/townmenu/town_item/TownMenu_ITEM_EQUIPCHECK.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectChara.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectTargetChara.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectTargetItem.hpp"
#include "ov019/townmenu/town_item/UnkTownMenuItemCharaSelect.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline void TownMenu_ITEM_CHECKTARGET::menuExecute()
{
}

inline short TownMenuPlayerControl::getActiveItem()
{
    return activeItem_;
}

inline char TownMenuPlayerControl::getActiveItemPage()
{
    return activeItemPage_;
}

THUMB void TownMenu_ITEM_CHECKTARGET::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    activeFukuro_ = TownMenuPlayerControl::getSingleton()->activeFukuro_;
    targetFukuro_ = TownMenuPlayerControl::getSingleton()->targetFukuro_;
    fromActiveChara_ = TownMenuPlayerControl::getSingleton()->activeChara_;
    toActiveChara_ = TownMenuPlayerControl::getSingleton()->targetChara_;
    activeItem_ = TownMenuPlayerControl::getSingleton()->getActiveItemIndexToAll();
    if (TownMenuPlayerControl::getSingleton()->targetItem_ == -1) {
        isSpace_ = 1;
        targetItem_ = -1;
        return;
    }
    isSpace_ = 0;
    if (targetFukuro_ == 0) {
        targetItem_ = TownMenuPlayerControl::getSingleton()->getTargetItemIndexToAll();
    }
}

THUMB void TownMenu_ITEM_CHECKTARGET::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    drawPartyStatusWindows();
}

THUMB void TownMenu_ITEM_CHECKTARGET::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            close();
            closeMenuCheck();
        }
        return;
    }
    unsigned int actor = 0, fromIname = 0, target = 0, toMaxIname = 0, fukuroIname = 0;
    unsigned int data[6] = {0};
    for (int i = 0; i < 6; i++) {
        data[i] = 0;
    }
    if (activeFukuro_ == 0) {
        actor = MenuStatusInfo::getPlayerIndex(fromActiveChara_);
        changeItemID_ = MenuStatusInfo::getPlayerItemID(fromActiveChara_, activeItem_);
        fromIname = MenuStatusInfo::getPlayerItemID(fromActiveChara_, activeItem_);
    }
    if (targetFukuro_ == 0) {
        target = MenuStatusInfo::getPlayerIndex(toActiveChara_);
        if (isSpace_ == 0) {
            toMaxIname = MenuStatusInfo::getPlayerItemID(toActiveChara_, targetItem_);
        }
    }
    if (activeFukuro_ == 1) {
        short item = TownMenuPlayerControl::getSingleton()->getActiveItem();
        char page = TownMenuPlayerControl::getSingleton()->getActiveItemPage();
        changeItemID_ = MenuStatusInfo::getFukuroItemID(item, page);
        fukuroIname = MenuStatusInfo::getFukuroItemID(item, page);
    }
    if (activeFukuro_ == 1 && targetFukuro_ == 1) {
        data[2] = fukuroIname;
        data[5] = 0xc421a;
    } else if (fromActiveChara_ == toActiveChara_ && activeFukuro_ == 0 && targetFukuro_ == 0) {
        data[2] = fromIname;
        data[0] = actor;
        if (MenuStatusInfo::isPlayerCondition(fromActiveChara_, MenuStatusInfo::CONDITION_DEATH) == true) {
            data[1] = target;
            data[5] = 0xc4218;
        } else {
            data[5] = 0xc4216;
        }
        changeItem(0x10);
    } else {
        unsigned int flag = checkGiveFlag();
        switch (flag) {
            case 2:
                data[2] = fromIname;
                data[0] = actor;
                data[5] = 0xc4206;
                break;
            case 6:
                data[2] = fromIname;
                data[0] = actor;
                data[5] = 0xc4208;
                break;
            case 8:
                data[1] = target;
                if (isSpace_) {
                    data[2] = fukuroIname;
                    data[5] = 0xc420a;
                } else {
                    data[4] = toMaxIname;
                    data[3] = fukuroIname;
                    data[5] = 0xc4210;
                }
                break;
            case 9:
                data[1] = target;
                if (isSpace_) {
                    data[2] = fukuroIname;
                    data[5] = 0xc420d;
                } else {
                    data[4] = toMaxIname;
                    data[3] = fukuroIname;
                    data[5] = 0xc4213;
                }
                break;
            case 1:
                data[1] = target;
                data[0] = actor;
                if (isSpace_) {
                    data[2] = fromIname;
                    data[5] = 0xc41fa;
                } else {
                    data[3] = fromIname;
                    data[4] = toMaxIname;
                    data[5] = 0xc4200;
                }
                break;
            case 4:
                data[1] = target;
                data[0] = actor;
                if (isSpace_) {
                    data[2] = fromIname;
                    data[5] = 0xc41f7;
                } else {
                    data[3] = fromIname;
                    data[4] = toMaxIname;
                    data[5] = 0xc4200;
                }
                break;
            case 5:
                data[1] = target;
                data[0] = actor;
                if (isSpace_) {
                    data[2] = fromIname;
                    data[5] = 0xc41fd;
                } else {
                    data[3] = fromIname;
                    data[4] = toMaxIname;
                    data[5] = 0xc4203;
                }
                break;
            default:
                data[1] = target;
                data[0] = actor;
                if (isSpace_) {
                    data[2] = fromIname;
                    data[5] = 0xc41f4;
                } else {
                    data[3] = fromIname;
                    data[4] = toMaxIname;
                    data[5] = 0xc4200;
                }
                break;
        }
        changeItem(flag);
    }
    gTownMenu_MESSAGE.openMessageForMENU();
    if (data[0]) {
        TextAPI::setMACRO0(1, 0x50000000, data[0]);
    }
    if (data[1]) {
        TextAPI::setMACRO0(0x12, 0x50000000, data[1]);
    }
    if (data[2]) {
        TextAPI::setMACRO0(10, 0x40000000, data[2]);
    }
    if (data[3]) {
        TextAPI::setMACRO1(10, 0x40000000, data[3]);
    }
    if (data[4]) {
        TextAPI::setMACRO2(10, 0x40000000, data[4]);
    }
    gTownMenu_MESSAGE.addMessage(data[5]);
}

THUMB unsigned int TownMenu_ITEM_CHECKTARGET::checkGiveFlag()
{
    unsigned int giveFlag = 0;
    if (targetFukuro_ == 0 && MenuStatusInfo::isPlayerCondition(toActiveChara_, MenuStatusInfo::CONDITION_DEATH) == true) {
        giveFlag |= 1;
    }
    if (activeFukuro_ == 0 && MenuStatusInfo::isPlayerCondition(fromActiveChara_, MenuStatusInfo::CONDITION_DEATH) == true) {
        giveFlag |= 4;
    }
    if (targetFukuro_ == 1) {
        giveFlag |= 2;
    }
    if (activeFukuro_ == 1) {
        giveFlag |= 8;
    }
    return giveFlag;
}

THUMB void TownMenu_ITEM_CHECKTARGET::changeItem(unsigned int flag)
{
    switch (flag) {
        case 2:
        case 6:
            MenuStatusInfo::changeItemPlayertoSack(fromActiveChara_, activeItem_);
            TownMenuPlayerControl::getSingleton()->setPlayerActiveItemByChangeMax();
            TownMenuPlayerControl::getSingleton()->setFukuroTargetItemByChangeMax();
            break;
        case 8:
        case 9:
            MenuStatusInfo::changeItemSacktoPlayer(activeItem_, toActiveChara_, targetItem_);
            TownMenuPlayerControl::getSingleton()->setFukuroActiveItemByChangeMax();
            TownMenuPlayerControl::getSingleton()->setPlayerTargetItemByChangeMax();
            setTargetItem();
            close();
            gTownMenu_ITEM_EQUIPCHECK.open();
            break;
        default:
            MenuStatusInfo::changeItemPlayertoPlayer(fromActiveChara_, activeItem_, toActiveChara_, targetItem_);
            TownMenuPlayerControl::getSingleton()->setPlayerActiveItemByChangeMax();
            TownMenuPlayerControl::getSingleton()->setPlayerTargetItemByChangeMax();
            setTargetItem();
            if (flag != 0x10) {
                close();
                gTownMenu_ITEM_EQUIPCHECK.open();
            }
            break;
    }
}

THUMB void TownMenu_ITEM_CHECKTARGET::setTargetItem()
{
    int itemCount = MenuStatusInfo::getPlayerItemCount(toActiveChara_);
    for (unsigned char i = 0; i < itemCount; i++) {
        if (changeItemID_ == MenuStatusInfo::getPlayerItemID(toActiveChara_, i) && !MenuStatusInfo::isPlayerEquipItemIndex(toActiveChara_, i)) {
            if (i > 6) {
                TownMenuPlayerControl::getSingleton()->targetItem_ = (unsigned char)(i - 6);
                TownMenuPlayerControl::getSingleton()->targetItemPage_ = 1;
            } else {
                TownMenuPlayerControl::getSingleton()->targetItem_ = i;
                TownMenuPlayerControl::getSingleton()->targetItemPage_ = 0;
            }
            return;
        }
    }
}

THUMB void TownMenu_ITEM_CHECKTARGET::closeMenuCheck()
{
    gTownMenuItemSelectTargetChara.close();
    gTownMenuItemSelectTargetItem.close();
    int count;
    if (activeFukuro_ == 1) {
        count = MenuStatusInfo::getFukuroItemCount();
    } else {
        count = MenuStatusInfo::getPlayerItemCount(fromActiveChara_);
    }
    if (count == 0) {
        data_ov019_02183524.fromMateriel_ = 0;
        data_ov019_02183524.open();
    } else {
        gTownMenuItemSelectChara.meisanhinFlag_ = 0;
        gTownMenuItemSelectChara.open();
    }
}
