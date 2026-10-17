#include "ov027/materielmenu/shop/MaterielMenu_SHOP_ROOT.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_BUYMENU.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_WHO_SELL.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"

using menu::MenuStatusInfo;

THUMB void MaterielMenu_SHOP_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = MaterielMenu_SHOP_MANAGER::getSingleton()->getShopAction();
    navigator_.setupBase();
    menu::MaterielMenuPlayerControl::getSingleton()->initialize();
    MaterielMenu_SHOP_MANAGER::getSingleton()->resetItemQuantity();
    mode_ = SHOP_START;
}

THUMB void MaterielMenu_SHOP_ROOT::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_SHOP_ROOT(&menuItem_, menuItem_.active_);
}

THUMB void MaterielMenu_SHOP_ROOT::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isMessageWAITPROG() == true) {
        unkfunc_0217be3c();
        menuItem_.drawActive();
        return;
    }
    if (gTownMenu_MESSAGE.isOpen() == true && mode_ != SHOP_MESWAIT) {
        unkfunc_0217bf68();
    }
}

THUMB void MaterielMenu_SHOP_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        if (gTownMenu_MESSAGE.isMessageWAITPROG() == true) {
            if (mode_ == SHOP_MESWAIT) {
                redraw_ = 1;
                mode_ = SHOP_SELECT;
            }
            navigator_.setup(1, 3, 3);
            int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
            if (result != 0) {
                if (result == 3) {
                    gTownMenu_MESSAGE.clearMessageWAITPROG();
                    MaterielMenu_SHOP_MANAGER::getSingleton()->setShopAction((char)menuItem_.active_);
                    showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->yameru());
                    mode_ = SHOP_NEXT;
                }
                if (result == 2) {
                    gTownMenu_MESSAGE.clearMessageWAITPROG();
                    switch (menuItem_.active_) {
                        case BUY_ITEM:
                            MaterielMenu_SHOP_MANAGER::getSingleton()->setShopAction(BUY_ITEM);
                            showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->buy());
                            gTownMenu_MESSAGE.setMessageLastCursor(true);
                            mode_ = SHOP_SELECT;
                            break;
                        case SELL_ITEM:
                            MaterielMenu_SHOP_MANAGER::getSingleton()->setShopAction(SELL_ITEM);
                            showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->sell());
                            gTownMenu_MESSAGE.setMessageLastCursor(true);
                            mode_ = SHOP_SELECT;
                            break;
                        case CANCEL_ITEM:
                            MaterielMenu_SHOP_MANAGER::getSingleton()->setShopAction(CANCEL_ITEM);
                            showMessage(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->yameru());
                            mode_ = SHOP_NEXT;
                            break;
                    }
                }
                redraw_ = 1;
            }
            return;
        }
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            execConduct();
        }
        return;
    }
    if (mode_ == SHOP_START) {
        unkfunc_0204c9c8();
        gTownMenu_MESSAGE.openMessageForTALK();
        gTownMenu_MESSAGE.addMessageNOWAIT(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->idle());
        gTownMenu_MESSAGE.addMessageWAITKEY();
        mode_ = SHOP_MESWAIT;
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_SHOP_ROOT::execConduct()
{
    if (mode_ == SHOP_SELECT) {
        close();
        if (menuItem_.active_ == BUY_ITEM) {
            gMaterielMenu_SHOP_BUYMENU.open();
        }
        else {
            gMaterielMenu_SHOP_WHO_SELL.open();
        }
    }
    if (mode_ == SHOP_NEXT) {
        unkfunc_0204c9c8();
        MaterielMenu_SHOP_MANAGER::getSingleton()->initialize();
        MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
    }
}

THUMB void MaterielMenu_SHOP_ROOT::showMessage(int mes)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(mes);
}
