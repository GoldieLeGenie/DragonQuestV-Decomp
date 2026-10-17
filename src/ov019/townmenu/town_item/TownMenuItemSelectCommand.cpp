#include "ov019/townmenu/town_item/TownMenuItemSelectCommand.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectChara.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectCommandUse.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectTargetChara.hpp"
#include "ov019/townmenu/town_item/TownMenu_ITEM_USE.hpp"
#include "ov019/townmenu/town_item/UnkTownMenuItemCharaSelect.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/global/Global.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"
#include "main/text/TextHook.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline short TownMenuPlayerControl::getActiveItem()
{
    return activeItem_;
}

inline char TownMenuPlayerControl::getActiveItemPage()
{
    return activeItemPage_;
}

inline short TownMenuPlayerControl::getTargetChara()
{
    return targetChara_;
}

THUMB void TownMenuItemSelectCommand::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = TownMenuPlayerControl::getSingleton()->getActiveCommand();
    activeChara_ = 0;
    if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 1) {
        char page = TownMenuPlayerControl::getSingleton()->activeItemPage_;
        itemID_ = MenuStatusInfo::getFukuroItemID(TownMenuPlayerControl::getSingleton()->activeItem_, page);
    } else {
        activeChara_ = TownMenuPlayerControl::getSingleton()->activeChara_;
        itemID_ = MenuStatusInfo::getPlayerItemID(activeChara_, TownMenuPlayerControl::getSingleton()->getActiveItemIndexToAll());
    }
    navigator_.setupBase();
    throwType_ = 3;
}

THUMB void TownMenuItemSelectCommand::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (TownMenuPlayerControl::getSingleton()->activeFukuro_) {
        commandFlag_ = MenuStatusInfo::getFukuroItemCommandFlag();
    } else {
        commandFlag_ = MenuStatusInfo::getPlayerItemCommandFlag(activeChara_, TownMenuPlayerControl::getSingleton()->getActiveItemIndexToAll());
    }
    unkfunc_021713e0(&menuItem_, commandFlag_, menuItem_.active_);
}

THUMB void TownMenuItemSelectCommand::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int open = gTownMenu_MESSAGE.isOpen();
    unkfunc_02173098(open, 0, itemID_, TownMenuPlayerControl::getSingleton()->activeItemPage_);
    if (!open) {
        menuItem_.drawActive();
    }
}

THUMB void TownMenuItemSelectCommand::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            switch (throwType_) {
                case 0:
                    if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 1) {
                        int activeItem = TownMenuPlayerControl::getSingleton()->getActiveItem();
                        int page = TownMenuPlayerControl::getSingleton()->getActiveItemPage();
                        MenuStatusInfo::throwFukuroItem(activeItem, page);
                        TownMenuPlayerControl::getSingleton()->setFukuroActiveItemByChangeMax();
                        if (MenuStatusInfo::getFukuroItemCount() == 0) {
                            close();
                            data_ov019_02183524.fromMateriel_ = 0;
                            data_ov019_02183524.open();
                        }
                    } else {
                        MenuStatusInfo::throwPlayerItem(activeChara_, TownMenuPlayerControl::getSingleton()->getActiveItemIndexToAll());
                        TownMenuPlayerControl::getSingleton()->setPlayerActiveItemByChangeMax();
                        if (MenuStatusInfo::getPlayerItemCount(activeChara_) == 0) {
                            close();
                            data_ov019_02183524.fromMateriel_ = 0;
                            data_ov019_02183524.open();
                        }
                    }
                    gTownMenu_MESSAGE.openMessageForMENU();
                    TextAPI::setMACRO0(10, 0x40000000, itemID_);
                    gTownMenu_MESSAGE.addMessage(0xc4230);
                    TownMenuPlayerControl::getSingleton()->setActiveCommand(0);
                    throwType_ = 3;
                    break;
                case 1:
                    gTownMenu_MESSAGE.openMessageForMENU();
                    TextAPI::setMACRO0(10, 0x40000000, itemID_);
                    gTownMenu_MESSAGE.addMessage(0xc4232);
                    gTownMenu_MESSAGE.setYesNo();
                    throwType_ = 0;
                    break;
                case 2:
                    gTownMenu_MESSAGE.close();
                    throwType_ = 3;
                    break;
                default:
                    closeMenuCheck();
                    break;
            }
        } else if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            throwType_ = 3;
        }
        return;
    }
    navigator_.setup(3, 2, unkfunc_0216fb40());
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        TownMenuPlayerControl::getSingleton()->setActiveCommand(menuItem_.active_);
        if (result == 3) {
            close();
            gTownMenuItemSelectChara.meisanhinFlag_ = 0;
            gTownMenuItemSelectChara.open();
        }
        if (result == 2) {
            unsigned char activeCommand = TownMenuPlayerControl::getSingleton()->activeCommand_;
            if (activeCommand != TownMenuPlayerControl::getSingleton()->unk_26) {
                TownMenuPlayerControl::getSingleton()->targetChara_ = 0;
                TownMenuPlayerControl::getSingleton()->targetCharaPage_ = 0;
            }
            TownMenuPlayerControl::getSingleton()->unk_26 = activeCommand;
            if (activeCommand != 5 && checkSeinenStart() == true) {
                return;
            }
            switch (activeCommand) {
                case 0:
                    judgeUseItem();
                    break;
                case 1:
                    close();
                    gTownMenuItemSelectTargetChara.open();
                    break;
                case 2:
                    judgeThrowItem();
                    break;
                case 3:
                    judgeEquipItem();
                    break;
                case 4:
                    setItemShowAction();
                    break;
                case 5:
                    close();
                    gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
                    break;
            }
            return;
        }
        redraw_ = 1;
    }
}

THUMB void TownMenuItemSelectCommand::judgeUseItem()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (TownMenuPlayerControl::getSingleton()->getTargetChara() >= MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        TownMenuPlayerControl::getSingleton()->targetChara_ = 0;
    }
    int fukuro = TownMenuPlayerControl::getSingleton()->activeFukuro_;
    if (fukuro == 0 && MenuStatusInfo::isPlayerCondition(activeChara_, MenuStatusInfo::CONDITION_DEATH) == true) {
        gTownMenu_MESSAGE.openMessageForMENU();
        TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara_));
        TextAPI::setMACRO0(10, 0x40000000, itemID_);
        gTownMenu_MESSAGE.addMessage(0xc40dc);
        return;
    }
    if (status::UseItem::getUseArea(itemID_) == status::UseItem::One && status::UseItem::getUseType(itemID_) != status::UseItem::Myself) {
        close();
        gTownMenu_ITEM_USE.open();
        return;
    }
    if (itemID_ == 0xa8 && fukuro == 1) {
        close();
        gTownMenu_ITEM_USE.open();
        return;
    }
    if (itemID_ == 0xfe) {
        if (data_02101c88.unkfunc_02051818(6) == 1) {
            close();
            cmn::g_cmnPartyInfo.prevLocation_ = 1;
            g_Global.prevPartTown_ = 0;
            g_Global.startBook();
        } else {
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xc41eb);
        }
        return;
    }
    close();
    gTownMenuItemSelectCommandUse.open();
}

THUMB void TownMenuItemSelectCommand::judgeEquipItem()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int activeItem = TownMenuPlayerControl::getSingleton()->getActiveItemIndexToAll();
    MenuStatusInfo::setEquipItem(activeChara_, activeItem, status::UseItem::getEquipItemType(itemID_));
    gTownMenu_MESSAGE.openMessageForMENU();
    TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara_));
    TextAPI::setMACRO0(10, 0x40000000, itemID_);
    if (MenuStatusInfo::isPlayerCondition(activeChara_, MenuStatusInfo::CONDITION_DEATH) == true) {
        gTownMenu_MESSAGE.addMessage(0xc421f);
    } else {
        gTownMenu_MESSAGE.addMessage(0xc421d);
    }
    TownMenuPlayerControl::getSingleton()->setActiveCommand(0);
    menuItem_.active_ = 0;
}

THUMB void TownMenuItemSelectCommand::setItemShowAction()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int itemValue = status::UseItem::getSellPrice(itemID_);
    int equipMemberCount = 0;
    gTownMenu_MESSAGE.openMessageForMENU();
    TextAPI::setMACRO0(10, 0x40000000, itemID_);
    TextAPI::setMACRO0(0x4b, 0xf0000000, itemValue);
    if (status::UseItem::getEquipItemType(itemID_) <= 4) {
        gTextHook.resetEQUIPABLE_PC();
        for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL); i++) {
            if (MenuStatusInfo::isPlayerEquipEnable(i, itemID_) == true) {
                gTextHook.setEQUIPABLE_PC(MenuStatusInfo::getPlayerIndex(i));
                equipMemberCount++;
            }
        }
    }
    switch (itemID_) {
        case 0xac:
            TextAPI::setMACRO0(0x17, 0xe0000000, 0x11c);
            break;
        case 0xad:
            TextAPI::setMACRO0(0x17, 0xe0000000, 0x11e);
            break;
        case 0xae:
            TextAPI::setMACRO0(0x17, 0xe0000000, 0xd9);
            break;
        case 0xaf:
            TextAPI::setMACRO0(0x17, 0xe0000000, 0xda);
            break;
    }
    gTownMenu_MESSAGE.addMessage(status::UseItem::getJudgeMessage(itemID_, 0));
    int mes;
    for (int i = 1; i < 5; i++) {
        mes = status::UseItem::getJudgeMessage(itemID_, i);
        if (mes != 0) {
            gTownMenu_MESSAGE.addMessage(mes);
        }
    }
    if (equipMemberCount == 0) {
        mes = status::UseItem::getJudgeMessage(itemID_, 5);
        if (mes != 0) {
            gTownMenu_MESSAGE.addMessage(mes);
        }
    } else if (equipMemberCount == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        mes = status::UseItem::getJudgeMessage(itemID_, 6);
        if (mes != 0) {
            gTownMenu_MESSAGE.addMessage(mes);
        }
    } else {
        mes = status::UseItem::getJudgeMessage(itemID_, 7);
        if (mes != 0) {
            gTownMenu_MESSAGE.addMessage(mes);
        }
    }
    mes = status::UseItem::getJudgeMessage(itemID_, 8);
    if (mes != 0) {
        gTownMenu_MESSAGE.addMessage(mes);
    }
}

THUMB void TownMenuItemSelectCommand::judgeThrowItem()
{
    gTownMenu_MESSAGE.openMessageForMENU();
    TextAPI::setMACRO0(10, 0x40000000, itemID_);
    switch (status::UseItem::getThrowType(itemID_)) {
        case status::UseItem::THROW_OK:
            gTownMenu_MESSAGE.addMessage(0xc422d);
            gTownMenu_MESSAGE.setYesNo();
            throwType_ = 0;
            break;
        case status::UseItem::THROW_NG:
            gTownMenu_MESSAGE.addMessage(0xc4235);
            throwType_ = 3;
            break;
        case status::UseItem::THROW_DIFFICULT:
            gTownMenu_MESSAGE.addMessage(0xc422d);
            gTownMenu_MESSAGE.setYesNo();
            throwType_ = 1;
            break;
    }
}

THUMB int TownMenuItemSelectCommand::unkfunc_0216fb40()
{
    switch (commandFlag_) {
        case 1:
        case 2:
            return 5;
        case 3:
            return 6;
        default:
            return 4;
    }
}

THUMB void TownMenuItemSelectCommand::closeMenuCheck()
{
    int count = MenuStatusInfo::getFukuroItemCount();
    if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 0) {
        count = MenuStatusInfo::getPlayerItemCount(activeChara_);
    }
    close();
    if (count == 0) {
        data_ov019_02183524.fromMateriel_ = 0;
        data_ov019_02183524.open();
    } else {
        gTownMenuItemSelectChara.meisanhinFlag_ = 0;
        gTownMenuItemSelectChara.open();
    }
}

THUMB bool TownMenuItemSelectCommand::checkSeinenStart()
{
    bool seinenStart = false;
    if (g_AreaFlag.check(0x82) && !g_AreaFlag.check(0x84)) {
        gTownMenu_MESSAGE.openMessageForMENU();
        gTownMenu_MESSAGE.addMessage(0xc42a8);
        seinenStart = true;
    }
    return seinenStart;
}
