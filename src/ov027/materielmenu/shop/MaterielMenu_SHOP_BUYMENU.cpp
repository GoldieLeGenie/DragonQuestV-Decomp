#include "ov027/materielmenu/shop/MaterielMenu_SHOP_BUYMENU.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_ROOT.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_WHOSE.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void menu::MenuPlayerControl::setActiveItem(short item)
{
    activeItem_ = item;
}

THUMB void MaterielMenu_SHOP_BUYMENU::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    unkfunc_0204c9bc(-4, 0);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
    navigator_.setupBase();
    mode_ = MODE_SELECT;
}

THUMB void MaterielMenu_SHOP_BUYMENU::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_CELECT_BUY(&menuItem_, menuItem_.active_, MaterielMenu_SHOP_MANAGER::getSingleton()->getSellItemCount());
}

THUMB void MaterielMenu_SHOP_BUYMENU::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true && mode_ != MODE_RETURN) {
        unkfunc_0217bf68();
        return;
    }
    if (mode_ != MODE_RETURN) {
        unkfunc_0217be4c(0);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_SHOP_BUYMENU::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (mode_ == MODE_NEXT) {
                unkfunc_0204c9c8();
                close();
                gMaterielMenu_SHOP_WHOSE.open();
            }
            if (mode_ == MODE_RETURN) {
                int mes[2] = {0, 0};
                for (int i = 0; i < 2; i++) {
                    mes[i] = 0;
                }
                MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->noMoney(mes);
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessageNOWAIT(mes[1]);
                gTownMenu_MESSAGE.addMessageWAITKEY();
                close();
                gMaterielMenu_SHOP_ROOT.open();
                gMaterielMenu_SHOP_ROOT.mode_ = MaterielMenu_SHOP_ROOT::SHOP_MESWAIT;
            }
        }
        return;
    }
    navigator_.setup(1, 6, MaterielMenu_SHOP_MANAGER::getSingleton()->getSellItemCount());
    int active = menuItem_.active_;
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(menuItem_.active_);
        if (result == 3) {
            close();
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->cancel());
            gTownMenu_MESSAGE.addMessageWAITKEY();
            gMaterielMenu_SHOP_ROOT.open();
            gMaterielMenu_SHOP_ROOT.mode_ = MaterielMenu_SHOP_ROOT::SHOP_MESWAIT;
        }
        if (result == 2) {
            checkBuy();
        }
        else if (result == 6) {
            unkfunc_02186c58(false);
        }
        else if (result == 7) {
            unkfunc_02186c58(true);
        }
        else {
            MaterielMenu_SHOP_MANAGER::getSingleton()->setItemQuantity(active, 1);
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_SHOP_BUYMENU::checkBuy()
{
    MaterielMenu_SHOP_MANAGER* manager = MaterielMenu_SHOP_MANAGER::getSingleton();
    gTownMenu_MESSAGE.openMessageForTALK();
    int active = menuItem_.active_;
    if (MenuStatusInfo::getGold() < manager->getItemPriceSum(active)) {
        int mes[2] = {0, 0};
        for (int i = 0; i < 2; i++) {
            mes[i] = 0;
        }
        MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->noMoney(mes);
        gTownMenu_MESSAGE.addMessage(mes[0]);
        gTownMenu_MESSAGE.setMessageLastCursor(true);
        mode_ = MODE_RETURN;
        return;
    }
    int plural = false;
    bool battleUse = false;
    int mes[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        mes[i] = 0;
    }
    int index = menuItem_.active_;
    int itemID = manager->getItem(index);
    if (manager->getItemQuantity(index) > 1) {
        plural = true;
    }
    if (status::UseItem::isBattleUse(itemID) == true && status::UseItem::getEquipItemType(itemID) <= ITEM_ACCESSORY) {
        battleUse = true;
    }
    MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->buyItem(plural, battleUse, mes);
    TextAPI::setMACRO0(10, 0x40000000, itemID);
    TextAPI::setMACRO0(0x54, 0xf0000000, manager->getItemQuantity(index));
    if (mes[2] == 0) {
        gTownMenu_MESSAGE.addMessage(mes[0], mes[1]);
    }
    else {
        gTownMenu_MESSAGE.addMessage(mes[0], mes[1], mes[2]);
    }
    gTownMenu_MESSAGE.setMessageLastCursor(true);
    mode_ = MODE_NEXT;
}

THUMB void MaterielMenu_SHOP_BUYMENU::unkfunc_02186c58(bool add)
{
    int active = menuItem_.active_;
    if (add == true) {
        MaterielMenu_SHOP_MANAGER::getSingleton()->addItem(active);
        return;
    }
    MaterielMenu_SHOP_MANAGER::getSingleton()->subItem(active);
}
