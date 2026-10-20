#include "ov027/materielmenu/shop/UnkMaterielMenu_0218a624.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_VALUE.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_WHO_SELL.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"

using menu::MenuStatusInfo;

inline void menu::MenuPlayerControl::setActiveItem(short item)
{
    activeItem_ = item;
}

inline void menu::MaterielMenuPlayerControl::setActiveItemPage(int active)
{
    activeItemPage_ = active;
}

THUMB void UnkMaterielMenu_0218a624::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    menu::MaterielMenuPlayerControl::getSingleton()->activeItem_ = 0;
    menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_ = 0;
    int chara = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
    int itemCount = MenuStatusInfo::getPlayerItemCount(chara);
    int equipCount = 0;
    navigator_.setupBase();
    navigator_.setup(2, 3, itemCount);
    navigator_.setPageNo(0);
    for (int i = 0; i < itemCount; i++) {
        if (MenuStatusInfo::isPlayerEquipItemIndex(chara, i) == true) {
            equipCount++;
        }
    }
    if (equipCount == itemCount) {
        equipCount = 0;
    }
    if (equipCount >= 6) {
        menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_ = 1;
        navigator_.setPageNo(1);
    }
    int active = equipCount - navigator_.getPageNo() * 6;
    active = dss::clamp<int>(0, active, 5);
    menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(active);
    menuItem_.active_ = active;
}

THUMB void UnkMaterielMenu_0218a624::menuExecute()
{
    setupItemIcon32Layout2x3(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void UnkMaterielMenu_0218a624::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        drawShopScreen();
        return;
    }
    drawShopSellItemScreen(0);
    menuItem_.drawActive();
}

THUMB void UnkMaterielMenu_0218a624::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
        }
        return;
    }
    int chara = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
    navigator_.setup(2, 3, MenuStatusInfo::getPlayerItemCount(chara));
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(menuItem_.active_);
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(navigator_.getPageNo());
        if (result == 3) {
            menu::MaterielMenuPlayerControl::getSingleton()->activeItem_ = 0;
            menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_ = 0;
            close();
            gMaterielMenu_SHOP_WHO_SELL.open();
        }
        if (result == 2) {
            MenuStatusInfo::getPlayerItemID(chara, navigator_.getIndex(menuItem_.active_));
            MaterielMenu_SHOP_MANAGER::getSingleton()->setSellQuantity(1);
            close();
            gMaterielMenu_SHOP_VALUE.open();
        }
        redraw_ = 1;
    }
}
