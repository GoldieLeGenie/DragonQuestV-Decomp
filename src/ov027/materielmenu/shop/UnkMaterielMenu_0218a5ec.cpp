#include "ov027/materielmenu/shop/UnkMaterielMenu_0218a5ec.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_VALUE.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_WHO_SELL.hpp"
#include "ov027/materielmenu/shop/UnkMaterielMenu_0218a5d0.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/UseItem.hpp"

using menu::MenuStatusInfo;

inline void menu::MenuPlayerControl::setActiveItem(short item)
{
    activeItem_ = item;
}

inline void menu::MaterielMenuPlayerControl::setActiveItemPage(int active)
{
    activeItemPage_ = active;
}

THUMB void UnkMaterielMenu_0218a5ec::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    navigator_.setup(2, 3, MenuStatusInfo::getFukuroItemCount());
    navigator_.setPageNo(0);
    int count = MenuStatusInfo::getFukuroItemCount();
    menu::MaterielMenuPlayerControl* control = menu::MaterielMenuPlayerControl::getSingleton();
    int index = control->activeItem_ + control->activeItemPage_ * 6;
    int active = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
    int page = menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_;
    while (index >= count) {
        active--;
        if (active < 0) {
            active = 0;
            page--;
            if (page < 0) {
                page = 0;
            }
        }
        index = active + page * 6;
        if (index == 0) {
            break;
        }
    }
    menuItem_.active_ = active;
    navigator_.setPageNo(page);
    menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(active);
    menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(page);
}

THUMB void UnkMaterielMenu_0218a5ec::menuExecute()
{
    unkfunc_0201c8e8(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void UnkMaterielMenu_0218a5ec::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        unkfunc_0217bf68();
        return;
    }
    unkfunc_0217bf14();
    menuItem_.drawActive();
}

THUMB void UnkMaterielMenu_0218a5ec::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
        }
        return;
    }
    navigator_.setup(2, 3, MenuStatusInfo::getFukuroItemCount());
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(menuItem_.active_);
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(navigator_.getPageNo());
        if (result == 3) {
            close();
            gMaterielMenu_SHOP_WHO_SELL.open();
        }
        if (result == 2) {
            unkfunc_021887c0();
        }
        redraw_ = 1;
    }
}

THUMB void UnkMaterielMenu_0218a5ec::unkfunc_021887c0()
{
    int active = menuItem_.active_;
    int itemID = MenuStatusInfo::getFukuroItemID(active, navigator_.getPageNo());
    close();
    if (status::UseItem::getSellType(itemID) == status::UseItem::SELL_NG) {
        gMaterielMenu_SHOP_VALUE.open();
        return;
    }
    if (MenuStatusInfo::getFukuroItemCount(navigator_.getIndex(menuItem_.active_)) == 1) {
        MaterielMenu_SHOP_MANAGER::getSingleton()->setSellQuantity(1);
        gMaterielMenu_SHOP_VALUE.open();
        return;
    }
    data_ov019_021853a8.open();
}
