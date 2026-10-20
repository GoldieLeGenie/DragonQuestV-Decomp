#include "ov027/materielmenu/changegift/MaterielMenu_CHANGEGIFT_SELECTGIFT.hpp"
#include "ov027/materielmenu/changegift/MaterielMenu_CHANGEGIFT_ROOT.hpp"
#include "ov027/materielmenu/changegift/MaterielMenu_CHANGEGIFT_SELECTCHARA.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void menu::MenuPlayerControl::setActiveItem(short item)
{
    activeItem_ = item;
}

THUMB void MaterielMenu_CHANGEGIFT_SELECTGIFT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    setCaptureOffset(-4, 0);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    navigator_.setupBase();
    itemCount_ = MaterielMenu_SHOP_MANAGER::getSingleton()->getSellItemCount();
    menu::MaterielMenuPlayerControl::getSingleton()->activeChara_ = 0;
    mode_ = MODE_NONE;
}

THUMB void MaterielMenu_CHANGEGIFT_SELECTGIFT::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_CELECT_BUY(&menuItem_, menuItem_.active_, itemCount_);
}

THUMB void MaterielMenu_CHANGEGIFT_SELECTGIFT::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        drawChangeGiftScreen();
        return;
    }
    drawShopBuyScreen(1);
    menuItem_.drawActive();
}

THUMB void MaterielMenu_CHANGEGIFT_SELECTGIFT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (mode_ == MODE_MESSAGE) {
                cancelChange();
            }
            if (mode_ == MODE_SELECT) {
                close();
                gMaterielMenu_CHANGEGIFT_SELECTCHARA.open();
                resetCaptureOffset();
            }
        }
        return;
    }
    navigator_.setup(1, 6, itemCount_);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem((char)menuItem_.active_);
        if (result == 3) {
            cancelChange();
        }
        if (result == 2) {
            checkAmount();
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_CHANGEGIFT_SELECTGIFT::checkAmount()
{
    int active = menuItem_.active_;
    int itemID = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(active);
    int price = MaterielMenu_SHOP_MANAGER::getSingleton()->getItemPrice(active);
    gTownMenu_MESSAGE.openMessageForTALK();
    TextAPI::setMACRO0(10, 0x40000000, itemID);
    if (MenuStatusInfo::getCoin() < price) {
        gTownMenu_MESSAGE.addMessage(gMaterielMenu_CHANGEGIFT_ROOT.getMessageNo(6));
        mode_ = MODE_MESSAGE;
        return;
    }
    gTownMenu_MESSAGE.addMessage(gMaterielMenu_CHANGEGIFT_ROOT.getMessageNo(4), gMaterielMenu_CHANGEGIFT_ROOT.getMessageNo(5));
    mode_ = MODE_SELECT;
}

THUMB void MaterielMenu_CHANGEGIFT_SELECTGIFT::cancelChange()
{
    close();
    gMaterielMenu_CHANGEGIFT_ROOT.open();
    gMaterielMenu_CHANGEGIFT_ROOT.mode_ = MaterielMenu_CHANGEGIFT_ROOT::CHANGEGIFT_BACK;
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(gMaterielMenu_CHANGEGIFT_ROOT.getMessageNo(0x13));
    gTownMenu_MESSAGE.setYesNo();
}
