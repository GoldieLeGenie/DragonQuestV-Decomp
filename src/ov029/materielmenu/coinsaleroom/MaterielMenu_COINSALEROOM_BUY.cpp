#pragma ipa file
#include "ov029/materielmenu/coinsaleroom/MaterielMenu_COINSALEROOM_BUY.hpp"
#include "ov029/materielmenu/coinsaleroom/MaterielMenu_COINSALEROOM_ROOT.hpp"
#include "ov029/leveldata/CoinMessage.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void MaterielMenu_COINSALEROOM_BUY::menuExecute()
{
}

inline void MaterielMenu_COINSALEROOM_ROOT::setMode(char mode)
{
    mode_ = mode;
}

inline dq5::level::CoinMessage* dq5::level::CoinMessage::getRecord(int index)
{
    return (CoinMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::CoinMessage::getMessage1()
{
    return message1;
}

THUMB void MaterielMenu_COINSALEROOM_BUY::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
}

THUMB void MaterielMenu_COINSALEROOM_BUY::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    unkfunc_0217c034(coin_, 0);
}

THUMB void MaterielMenu_COINSALEROOM_BUY::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (!messageUpdata()) {
        buyCoinMessage();
    }
}

THUMB bool MaterielMenu_COINSALEROOM_BUY::messageUpdata()
{
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            selectYes();
        }
        else if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            close();
            gMaterielMenu_COINSALEROOM_ROOT.open();
            gMaterielMenu_COINSALEROOM_ROOT.setMode(MaterielMenu_COINSALEROOM_ROOT::MODE_BACK);
        }
        return true;
    }
    return false;
}

THUMB void MaterielMenu_COINSALEROOM_BUY::buyCoinMessage()
{
    int coin = coin_;
    if (MenuStatusInfo::getGold() < coin * 20) {
        showMessage(6, 0);
        mode_ = MODE_LACKING;
        return;
    }
    if (coin + MenuStatusInfo::getCoin() > 9999999) {
        int maxToken = 9999999 - MenuStatusInfo::getCoin();
        TextAPI::setMACRO0(0x38, 0xf0000000, maxToken);
        showMessage(9, 0);
        mode_ = MODE_OVER;
        return;
    }
    int totalGold = coin_ * 20;
    TextAPI::setMACRO0(0x49, 0xf0000000, coin);
    TextAPI::setMACRO0(0x46, 0xf0000000, totalGold);
    showMessage(7, 8);
    gTownMenu_MESSAGE.setYesNo();
    mode_ = MODE_BUY;
}

THUMB void MaterielMenu_COINSALEROOM_BUY::selectYes()
{
    gTownMenu_MESSAGE.close();
    switch (mode_) {
        case MODE_LACKING:
            close();
            gMaterielMenu_COINSALEROOM_ROOT.open();
            gMaterielMenu_COINSALEROOM_ROOT.setMode(MaterielMenu_COINSALEROOM_ROOT::MODE_BACK);
            break;
        case MODE_OVER: {
            int maxToken = 9999999 - MenuStatusInfo::getCoin();
            int tokenGold = maxToken * 20;
            TextAPI::setMACRO0(0x38, 0xf0000000, maxToken);
            TextAPI::setMACRO0(0x43, 0xf0000000, tokenGold);
            showMessage(10, 0);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_BUY;
            break;
        }
        case MODE_BUY:
            getCasinoCoin();
            break;
        case MODE_END:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_COINSALEROOM_BUY::getCasinoCoin()
{
    unsigned int nowCoin = MenuStatusInfo::getCoin();
    if (nowCoin + coin_ > 9999999) {
        MenuStatusInfo::setGold(MenuStatusInfo::getGold() - (9999999 - nowCoin) * 20);
        MenuStatusInfo::setCoin(9999999);
    }
    else {
        MenuStatusInfo::setGold(MenuStatusInfo::getGold() - coin_ * 20);
        MenuStatusInfo::setCoin(MenuStatusInfo::getCoin() + coin_);
    }
    showMessage(11, 0);
    mode_ = MODE_END;
}

THUMB void MaterielMenu_COINSALEROOM_BUY::showMessage(int index1, int index2)
{
    int mes1 = dq5::level::CoinMessage::getRecord(index1)->getMessage1();
    int mes2 = dq5::level::CoinMessage::getRecord(index2)->getMessage1();
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(mes1);
    if (mes2 != 0) {
        gTownMenu_MESSAGE.addMessage(mes2);
    }
}
