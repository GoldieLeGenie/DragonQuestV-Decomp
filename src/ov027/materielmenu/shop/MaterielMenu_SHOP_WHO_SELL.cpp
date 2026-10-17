#include "ov027/materielmenu/shop/MaterielMenu_SHOP_WHO_SELL.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_ROOT.hpp"
#include "ov027/materielmenu/shop/UnkMaterielMenu_0218a5ec.hpp"
#include "ov027/materielmenu/shop/UnkMaterielMenu_0218a624.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

THUMB void MaterielMenu_SHOP_WHO_SELL::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    unkfunc_0204c9c8();
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
    navigator_.setupBase();
    unk_1c = 0;
    unk_20 = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) + 1;
}

THUMB void MaterielMenu_SHOP_WHO_SELL::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_ICON32_5x2(&menuItem_, menuItem_.active_, unk_20);
}

THUMB void MaterielMenu_SHOP_WHO_SELL::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() == false) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        unkfunc_0217beb8();
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_SHOP_WHO_SELL::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (unk_1c != 0) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessageNOWAIT(unk_1c);
                gTownMenu_MESSAGE.addMessageWAITKEY();
                close();
                gMaterielMenu_SHOP_ROOT.open();
                gMaterielMenu_SHOP_ROOT.mode_ = MaterielMenu_SHOP_ROOT::SHOP_MESWAIT;
            }
        }
        return;
    }
    navigator_.setup(5, 2, unk_20);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(menuItem_.active_);
        if (result == 3) {
            close();
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->cancel());
            gTownMenu_MESSAGE.addMessageWAITKEY();
            gMaterielMenu_SHOP_ROOT.open();
            gMaterielMenu_SHOP_ROOT.mode_ = MaterielMenu_SHOP_ROOT::SHOP_MESWAIT;
        }
        if (result == 2) {
            unkfunc_0218910c();
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_SHOP_WHO_SELL::unkfunc_0218910c()
{
    bool fukuro = false;
    int active = menuItem_.active_;
    if (active == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        fukuro = true;
    }
    int count;
    if (fukuro == true) {
        count = MenuStatusInfo::getFukuroItemCount();
    }
    else {
        count = MenuStatusInfo::getPlayerItemCount(menuItem_.active_);
    }
    if (count > 0) {
        close();
        if (fukuro == true) {
            data_ov019_021843c0.open();
            return;
        }
        data_ov019_0218421c.open();
        return;
    }
    int mes[2] = {0, 0};
    for (int i = 0; i < 2; i++) {
        mes[i] = 0;
    }
    gTownMenu_MESSAGE.openMessageForTALK();
    if (fukuro == false) {
        TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(menuItem_.active_));
    }
    MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()->haveNoItem(fukuro, mes);
    gTownMenu_MESSAGE.addMessage(mes[0]);
    unk_1c = mes[1];
}
