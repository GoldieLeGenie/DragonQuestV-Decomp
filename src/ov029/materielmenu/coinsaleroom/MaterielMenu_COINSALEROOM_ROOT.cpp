#include "ov029/materielmenu/coinsaleroom/MaterielMenu_COINSALEROOM_ROOT.hpp"
#include "ov029/materielmenu/coinsaleroom/MaterielMenu_COINSALEROOM_BUY.hpp"
#include "ov029/leveldata/CoinMessage.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void MaterielMenu_COINSALEROOM_BUY::setCoin(int coin)
{
    coin_ = coin;
}

inline dq5::level::CoinMessage* dq5::level::CoinMessage::getRecord(int index)
{
    return (CoinMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::CoinMessage::getMessage1()
{
    return message1;
}

THUMB void MaterielMenu_COINSALEROOM_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_UP);
    menuItem_.active_ = 5;
    navigator_.setupBase();
    mode_ = MODE_FIRST;
    unk_8c = 0;
    unk_94 = 0;
    coin_ = 0;
}

THUMB void MaterielMenu_COINSALEROOM_ROOT::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_COIN_SELECT(&menuItem_, menuItem_.active_, 6);
}

THUMB void MaterielMenu_COINSALEROOM_ROOT::menuDraw()
{
    if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        unkfunc_0217c034(coin_, 1);
        if (unk_8c) {
            if (unk_94 > 15) {
                menuItem_.drawActive();
            }
            if (unk_94 == 0 || unk_94 == 16) {
                redraw_ = 1;
            }
            unk_94++;
            if (unk_94 > 30) {
                unk_94 = 0;
            }
        }
        else {
            menuItem_.drawActive();
        }
    }
}

THUMB void MaterielMenu_COINSALEROOM_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (!messageUpdata()) {
        buyCoinUpdata();
    }
}

THUMB bool MaterielMenu_COINSALEROOM_ROOT::messageUpdata()
{
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (MenuStatusInfo::getCoin() == 9999999) {
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
                return true;
            }
        }
        return false;
    }
    switch (mode_) {
        case MODE_FIRST:
            if (MenuStatusInfo::getCoin() == 9999999) {
                showMessage(1, 2, 3);
                mode_ = MODE_END;
            }
            else {
                TextAPI::setMACRO0(0x2a, 0xf0000000, MenuStatusInfo::getCoin());
                showMessage(1, 4, 5);
                gTownMenu_MESSAGE.setMessageLastCursor(true);
                gTownMenu_MESSAGE.addMessageWAITKEY();
                unk_8c = 1;
            }
            break;
        case MODE_BACK:
            TextAPI::setMACRO0(0x2a, 0xf0000000, MenuStatusInfo::getCoin());
            showMessage(4, 5, 0);
            gTownMenu_MESSAGE.setMessageLastCursor(true);
            gTownMenu_MESSAGE.addMessageWAITKEY();
            unk_8c = 1;
            break;
        case MODE_END:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            return true;
    }
    return false;
}

THUMB void MaterielMenu_COINSALEROOM_ROOT::buyCoinUpdata()
{
    if (gTownMenu_MESSAGE.isOpen() != true || gTownMenu_MESSAGE.isMessageWAITPROG() != true) {
        return;
    }
    if (mode_ <= MODE_BACK) {
        redraw_ = 1;
        mode_ = MODE_SELECT;
        return;
    }
    int price = 0;
    switch (menuItem_.active_) {
        case 0:
            price = 100000;
            break;
        case 1:
            price = 10000;
            break;
        case 2:
            price = 1000;
            break;
        case 3:
            price = 100;
            break;
        case 4:
            price = 10;
            break;
        case 5:
            price = 1;
            break;
    }
    navigator_.setup(6, 1, 6);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result == 0) {
        return;
    }
    if (result == 3) {
        showMessage(12, 0, 0);
        mode_ = MODE_END;
    }
    if (result == 2) {
        if (coin_ == 0) {
            showMessage(12, 0, 0);
            mode_ = MODE_END;
        }
        else {
            gTownMenu_MESSAGE.close();
            close();
            gMaterielMenu_COINSALEROOM_BUY.setCoin(coin_);
            gMaterielMenu_COINSALEROOM_BUY.open();
        }
    }
    if (result == 4) {
        coin_ += price;
        if (coin_ > 99999) {
            coin_ = 99999;
        }
    }
    if (result == 5) {
        coin_ -= price;
        if (coin_ < 0) {
            coin_ = 0;
        }
    }
    if (result == 7) {
        menuItem_.active_ = 1;
    }
    if (menuItem_.active_ == 0) {
        menuItem_.active_ = 5;
    }
    redraw_ = 1;
}

THUMB void MaterielMenu_COINSALEROOM_ROOT::showMessage(int index1, int index2, int index3)
{
    int mes1 = dq5::level::CoinMessage::getRecord(index1)->getMessage1();
    int mes2 = dq5::level::CoinMessage::getRecord(index2)->getMessage1();
    int mes3 = dq5::level::CoinMessage::getRecord(index3)->getMessage1();
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(mes1);
    if (mes2 != 0) {
        gTownMenu_MESSAGE.addMessage(mes2);
    }
    if (mes3 != 0) {
        gTownMenu_MESSAGE.addMessage(mes3);
    }
}
