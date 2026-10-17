#pragma ipa file
#include "ov019/townmenu/town_operation/UnkTownMenuOperationEquipItem.hpp"
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_EQUIP.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/HaveItem.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline status::HaveItem& status::HaveStatusInfo::getHaveItem()
{
    return haveItem_;
}

inline void status::HaveItem::setSortEnable(bool flag)
{
    sortEnable_ = flag;
}

inline void TownMenuPlayerControl::setActiveItem(short item)
{
    activeItem_ = item;
}

inline char TownMenuPlayerControl::getActiveItemPage()
{
    return activeItemPage_;
}

inline void TownMenuPlayerControl::setActiveItemPage(char page)
{
    activeItemPage_ = page;
}

THUMB void UnkTownMenuOperationEquipItem::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    itemItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    removeItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    itemNavigator_.setupBase();
    removeNavigator_.setupBase();
    itemType_ = ITEM_WEAPON;
    itemCount_ = 0;
    itemListActive_ = 1;
    for (int i = 0; i < 12; i++) {
        itemPosList_[i] = 0;
    }
    setItemTypeList();
    itemNavigator_.setup(2, 3, itemCount_);
}

THUMB void UnkTownMenuOperationEquipItem::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    unkfunc_0201c8e8(&itemItem_, itemNavigator_.getCountInPage(), itemItem_.active_);
    unkfunc_02171584(&removeItem_);
}

THUMB void UnkTownMenuOperationEquipItem::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (!gTownMenu_MESSAGE.isOpen()) {
        unkfunc_02173894(itemPosList_, itemCount_, itemType_, itemListActive_);
        itemItem_.drawActive();
        removeItem_.drawActive();
    }
}

THUMB void UnkTownMenuOperationEquipItem::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
        }
        return;
    }
    itemNavigator_.setup(2, 3, itemCount_);
    int result = MenuUpdate_Assist::menuSelect(itemItem_, itemNavigator_);
    if (result != 0) {
        TownMenuPlayerControl::getSingleton()->setActiveItemPage(itemNavigator_.getPageNo());
        TownMenuPlayerControl::getSingleton()->setActiveItem(itemItem_.active_);
        if (result == 3) {
            itemType_--;
            if (itemType_ < 0) {
                close();
                gTownMenu_OPERATION_EQUIP.open();
                return;
            }
            setItemTypeList();
            itemItem_.active_ = 0;
            itemNavigator_.setPageNo(0);
            TownMenuPlayerControl::getSingleton()->setActiveItemPage(0);
        }
        if (result == 2) {
            if (itemType_ >= ITEM_WEAPON && itemType_ < ITEM_ACCESSORY) {
                unkfunc_02176424();
            } else if (itemType_ == ITEM_ACCESSORY) {
                unkfunc_02176528();
            } else if (itemType_ > ITEM_ACCESSORY) {
                int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
                status::HaveItem::setSortEnable(true);
                MenuStatusInfo::getHaveStatusInfo(activeChara).getHaveItem().sortEquipment();
                close();
                gTownMenu_ROOT.open();
                gTownMenu_ROOT.menuItem_.active_ = TownMenu_ROOT::ROOT_OPERATION;
            }
        }
        if (result == 4 || result == 5) {
            int active = itemItem_.active_;
            itemItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
            removeItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
            if (itemType_ == ITEM_ACCESSORY) {
                if (active % 2 == 1) {
                    removeItem_.active_ = 1;
                    itemListActive_ = 1;
                } else {
                    removeItem_.active_ = 0;
                    itemListActive_ = 0;
                }
            }
            TownMenuPlayerControl::getSingleton()->setActiveItem(-1);
        }
        redraw_ = 1;
        return;
    }
    if (itemType_ == ITEM_ACCESSORY) {
        removeNavigator_.setup(2, 1, 2);
    } else {
        removeNavigator_.setup(1, 1, 1);
    }
    int removeActive = removeItem_.active_;
    int removeResult = MenuUpdate_Assist::menuSelect(removeItem_, removeNavigator_);
    if (removeResult == 0) {
        return;
    }
    if (removeResult == 3) {
        itemType_--;
        if (itemType_ < 0) {
            int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
            status::HaveItem::setSortEnable(true);
            MenuStatusInfo::getHaveStatusInfo(activeChara).getHaveItem().sortEquipment();
            close();
            gTownMenu_OPERATION_EQUIP.open();
            return;
        }
        setItemTypeList();
    }
    if (removeResult == 2) {
        if (itemType_ >= ITEM_WEAPON && itemType_ < ITEM_ACCESSORY) {
            int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
            status::HaveItem::setSortEnable(true);
            MenuStatusInfo::getHaveStatusInfo(activeChara).getHaveItem().sortEquipment();
            unkfunc_021764c0();
        } else if (itemType_ >= ITEM_ACCESSORY) {
            if (removeItem_.active_ == 0) {
                for (int i = 0; i < itemCount_; i++) {
                    MenuStatusInfo::resetEquipItemForIndex(TownMenuPlayerControl::getSingleton()->activeChara_, itemPosList_[i]);
                }
            } else {
                int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
                status::HaveItem::setSortEnable(true);
                MenuStatusInfo::getHaveStatusInfo(activeChara).getHaveItem().sortEquipment();
                close();
                gTownMenu_ROOT.open();
                gTownMenu_ROOT.menuItem_.active_ = TownMenu_ROOT::ROOT_OPERATION;
                return;
            }
        }
    }
    if (removeResult == 4 && itemCount_ != 0) {
        int active2 = removeItem_.active_;
        int active = 4;
        itemItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
        removeItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
        while (active >= itemCount_ - itemNavigator_.getIndex(itemItem_.active_)) {
            active -= 2;
        }
        if (itemType_ == ITEM_ACCESSORY) {
            int page = TownMenuPlayerControl::getSingleton()->getActiveItemPage();
            if (active2 == 1) {
                int count = itemCount_ - page * 6;
                if (active + 1 < count) {
                    active = active + 1;
                } else if (count != 1) {
                    active--;
                }
            }
        }
        itemItem_.active_ = active;
        TownMenuPlayerControl::getSingleton()->setActiveItem(active);
        itemListActive_ = 0;
    }
    if (removeResult == 5 && itemCount_ != 0) {
        int active2 = removeItem_.active_;
        itemItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
        removeItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
        if (itemType_ == ITEM_ACCESSORY) {
            int page = TownMenuPlayerControl::getSingleton()->getActiveItemPage();
            if (active2 == 1 && itemCount_ - page * 6 >= 2) {
                itemItem_.active_ = 1;
            }
        }
        TownMenuPlayerControl::getSingleton()->setActiveItem(itemItem_.active_);
    }
    if (removeResult == 7 || (itemType_ < ITEM_ACCESSORY && removeActive < removeItem_.active_)) {
        if (itemType_ < ITEM_ACCESSORY) {
            removeItem_.active_ = 0;
        }
        if (itemCount_ > 6) {
            int page = TownMenuPlayerControl::getSingleton()->getActiveItemPage() + 1 > 1 ? 0 : 1;
            TownMenuPlayerControl::getSingleton()->setActiveItemPage(page);
            removeNavigator_.setPageNo(page);
            itemNavigator_.setPageNo(page);
            itemListActive_ = 0;
        }
    }
    if (removeResult == 6 && itemCount_ > 6) {
        int page = TownMenuPlayerControl::getSingleton()->getActiveItemPage() - 1 < 0 ? 1 : 0;
        TownMenuPlayerControl::getSingleton()->setActiveItemPage(page);
        removeNavigator_.setPageNo(page);
        itemNavigator_.setPageNo(page);
    }
    if (itemType_ == ITEM_ACCESSORY && removeItem_.active_ == 1) {
        itemListActive_ = 1;
    } else {
        itemListActive_ = 0;
    }
    redraw_ = 1;
}

THUMB void UnkTownMenuOperationEquipItem::setItemTypeList()
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int count = MenuStatusInfo::getPlayerItemCount(activeChara);
    int page;
    int active = itemItem_.active_;
    page = itemNavigator_.getPageNo();
    itemCount_ = 0;
    for (int i = 0; i < 12; i++) {
        itemPosList_[i] = 0;
    }
    for (int i = 0; i < count; i++) {
        if (itemType_ == status::UseItem::getEquipItemType(MenuStatusInfo::getPlayerItemID(activeChara, i))) {
            itemPosList_[itemCount_] = i;
            itemCount_++;
        }
    }
    if (itemCount_ == 0) {
        itemItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
        removeItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
        TownMenuPlayerControl::getSingleton()->setActiveItem(-1);
    } else {
        itemItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
        removeItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
        TownMenuPlayerControl::getSingleton()->setActiveItem(0);
        if (itemType_ == ITEM_ACCESSORY) {
            itemItem_.active_ = active;
            TownMenuPlayerControl::getSingleton()->setActiveItem(active);
        }
    }
    if (itemType_ == ITEM_ACCESSORY) {
        if (itemCount_ != 0) {
            TownMenuPlayerControl::getSingleton()->setActiveItem(active);
        }
        TownMenuPlayerControl::getSingleton()->setActiveItemPage(page);
        status::HaveItem::setSortEnable(false);
    } else {
        status::HaveItem::setSortEnable(true);
    }
}

THUMB void UnkTownMenuOperationEquipItem::unkfunc_02176424()
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int activeItem = itemPosList_[itemNavigator_.getIndex(itemItem_.active_)];
    if (MenuStatusInfo::setEquipItem(activeChara, activeItem, (ItemType)itemType_) == MenuStatusInfo::EQUIP_FAILED) {
        int itemID = MenuStatusInfo::getPlayerItemID(activeChara, activeItem);
        gTownMenu_MESSAGE.openMessageForMENU();
        TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara));
        TextAPI::setMACRO0(10, 0x40000000, itemID);
        gTownMenu_MESSAGE.addMessage(0xc4227);
    } else {
        itemType_++;
        setItemTypeList();
    }
    itemItem_.active_ = 0;
    itemNavigator_.setPageNo(0);
    TownMenuPlayerControl::getSingleton()->setActiveItemPage(0);
}

THUMB void UnkTownMenuOperationEquipItem::unkfunc_021764c0()
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int activeItem = itemPosList_[itemNavigator_.getIndex(itemItem_.active_)];
    if (itemType_ == status::UseItem::getEquipItemType(MenuStatusInfo::getPlayerItemID(activeChara, activeItem))) {
        MenuStatusInfo::resetEquipItemForIndex(activeChara, activeItem);
    }
    itemType_++;
    setItemTypeList();
    itemItem_.active_ = 0;
    itemNavigator_.setPageNo(0);
    TownMenuPlayerControl::getSingleton()->setActiveItemPage(0);
}

THUMB void UnkTownMenuOperationEquipItem::unkfunc_02176528()
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int activeItem = itemPosList_[itemNavigator_.getIndex(itemItem_.active_)];
    switch (MenuStatusInfo::setEquipItem(activeChara, activeItem, ITEM_ACCESSORY)) {
        case MenuStatusInfo::EQUIP_FAILED: {
            int itemID = MenuStatusInfo::getPlayerItemID(activeChara, activeItem);
            gTownMenu_MESSAGE.openMessageForMENU();
            TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(activeChara));
            TextAPI::setMACRO0(10, 0x40000000, itemID);
            gTownMenu_MESSAGE.addMessage(0xc4227);
            break;
        }
        case MenuStatusInfo::EQUIP_ALREADY:
            MenuStatusInfo::resetEquipItemForIndex(activeChara, activeItem);
            break;
    }
    setItemTypeList();
}
