#include "ov027/materielmenu/shop/UnkMaterielMenu_0218a5d0.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_VALUE.hpp"
#include "ov027/materielmenu/shop/UnkMaterielMenu_0218a5ec.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

THUMB void UnkMaterielMenu_0218a5d0::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    quantity_ = 1;
    unk_1c = 0;
    int active = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
    TextAPI::setMACRO0(10, 0x40000000, MenuStatusInfo::getFukuroItemID(active, menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_));
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessageNOWAIT(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->sellHowMany());
    gTownMenu_MESSAGE.addMessageWAITKEY();
}

THUMB void UnkMaterielMenu_0218a5d0::menuExecute()
{
    menu::MenuTemplate_materiel::shopSellQuantity(&menuItem_, menuItem_.active_);
}

THUMB void UnkMaterielMenu_0218a5d0::menuDraw()
{
    if (gTownMenu_MESSAGE.isMessageWAITPROG() == true) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        unkfunc_0217bf44(quantity_);
        menuItem_.drawActive();
    }
}

THUMB void UnkMaterielMenu_0218a5d0::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        if (gTownMenu_MESSAGE.isMessageWAITPROG() == true) {
            if (unk_1c == 0) {
                redraw_ = 1;
                unk_1c = 1;
                return;
            }
            navigator_.setup(1, 1, 1);
            int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
            if (result != 0) {
                if (result == 3) {
                    int mes[2] = {0, 0};
                    for (int i = 0; i < 2; i++) {
                        mes[i] = 0;
                    }
                    gTownMenu_MESSAGE.clearMessageWAITPROG();
                    close();
                    MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->celectNo(false, mes);
                    gTownMenu_MESSAGE.openMessageForTALK();
                    gTownMenu_MESSAGE.addMessage(mes[0], mes[1]);
                    gTownMenu_MESSAGE.setMessageLastCursor(true);
                    data_ov019_021843c0.open();
                }
                if (result == 2) {
                    gTownMenu_MESSAGE.clearMessageWAITPROG();
                    MaterielMenu_SHOP_MANAGER::getSingleton()->setSellQuantity(quantity_);
                    close();
                    int active = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
                    MenuStatusInfo::getFukuroItemID(active, menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_);
                    gMaterielMenu_SHOP_VALUE.open();
                }
                if (result == 7) {
                    unkfunc_02188604(true);
                }
                if (result == 6) {
                    unkfunc_02188604(false);
                }
                redraw_ = 1;
            }
            return;
        }
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
        }
    }
}

THUMB void UnkMaterielMenu_0218a5d0::unkfunc_02188604(bool add)
{
    menu::MaterielMenuPlayerControl* control = menu::MaterielMenuPlayerControl::getSingleton();
    int count = MenuStatusInfo::getFukuroItemCount(control->activeItem_ + control->activeItemPage_ * 6);
    if (add == true) {
        quantity_++;
        if (quantity_ > count) {
            quantity_ = 1;
        }
        return;
    }
    quantity_--;
    if (quantity_ < 1) {
        quantity_ = count;
    }
}
