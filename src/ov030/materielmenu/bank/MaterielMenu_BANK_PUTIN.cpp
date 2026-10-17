#include "ov030/materielmenu/bank/MaterielMenu_BANK_PUTIN.hpp"
#include "ov030/leveldata/GoldMessage.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline dq5::level::GoldMessage* dq5::level::GoldMessage::getRecord(int index)
{
    return (GoldMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::GoldMessage::getMessage1()
{
    return message1;
}

THUMB void MaterielMenu_BANK_PUTIN::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_UP);
    menuItem_.active_ = 2;
    navigator_.setupBase();
    bankMoney_ = MenuStatusInfo::getBank();
    putinMoney_ = 0;
    mode_ = PUTIN_START;
}

THUMB void MaterielMenu_BANK_PUTIN::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_MONEY_SELECT(&menuItem_, menuItem_.active_, 3);
}

THUMB void MaterielMenu_BANK_PUTIN::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (mode_ == PUTIN_START) {
        unkfunc_0217c504();
        return;
    }
    int open = gTownMenu_MESSAGE.isOpen();
    unkfunc_0217c000(open, 1, putinMoney_);
    if (open == 0) {
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_BANK_PUTIN::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (!messageUpdate()) {
        bankUpdate();
    }
}

THUMB bool MaterielMenu_BANK_PUTIN::messageUpdate()
{
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            if (mode_ == PUTIN_END) {
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            }
            if (mode_ == PUTIN_MAX) {
                unsigned int maxBalance = 99999000 - bankMoney_;
                MenuStatusInfo::setBank(99999000);
                MenuStatusInfo::setGold(MenuStatusInfo::getGold() - maxBalance);
                TextAPI::setMACRO0(0x34, 0xf0000000, maxBalance);
                TextAPI::setMACRO0(0x30, 0xf0000000, 99999000);
                showMessage(13, 21);
                mode_ = PUTIN_END;
            }
        }
        else if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (mode_ == PUTIN_MAX) {
                mode_ = PUTIN_START;
            }
        }
        return true;
    }
    if (mode_ == PUTIN_START) {
        if ((unsigned int)bankMoney_ >= 99999000) {
            TextAPI::setMACRO0(0x30, 0xf0000000, bankMoney_);
            showMessage(8, 21);
            mode_ = PUTIN_END;
        }
        else {
            showMessage(9, 0);
            mode_ = PUTIN_SELECT;
        }
        return true;
    }
    return false;
}

THUMB void MaterielMenu_BANK_PUTIN::bankUpdate()
{
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
    }
    navigator_.setup(3, 1, 3);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        if (result == 3) {
            cancelPutin();
        }
        if (result == 2) {
            if (putinMoney_ == 0) {
                cancelPutin();
            }
            else {
                bankPutin();
            }
        }
        if (result == 4) {
            putinMoney_ += price;
            if (putinMoney_ > 999000) {
                putinMoney_ = 999000;
            }
        }
        if (result == 5) {
            putinMoney_ -= price;
            if (putinMoney_ < 0) {
                putinMoney_ = 0;
            }
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_BANK_PUTIN::bankPutin()
{
    menuItem_.active_ = 2;
    unsigned int putin = putinMoney_;
    if (putin > MenuStatusInfo::getGold()) {
        showMessage(10, 0);
        putinMoney_ = 0;
        mode_ = PUTIN_START;
        return;
    }
    unsigned int bank = bankMoney_;
    if (putin + bank > 99999000) {
        TextAPI::setMACRO0(0x34, 0xf0000000, 99999000 - bank);
        showMessage(11, 12);
        gTownMenu_MESSAGE.setYesNo();
        putinMoney_ = 0;
        mode_ = PUTIN_MAX;
        return;
    }
    MenuStatusInfo::setBank(putin + bank);
    MenuStatusInfo::setGold(MenuStatusInfo::getGold() - putinMoney_);
    TextAPI::setMACRO0(0x31, 0xf0000000, putinMoney_);
    TextAPI::setMACRO0(0x30, 0xf0000000, MenuStatusInfo::getBank());
    showMessage(14, 21);
    mode_ = PUTIN_END;
}

THUMB void MaterielMenu_BANK_PUTIN::cancelPutin()
{
    gTownMenu_MESSAGE.close();
    gTownMenu_MESSAGE.openMessageForTALK();
    if (bankMoney_ == 0) {
        showMessage(20, 22);
    }
    else {
        TextAPI::setMACRO0(0x30, 0xf0000000, bankMoney_);
        showMessage(20, 21);
    }
    mode_ = PUTIN_END;
}

THUMB void MaterielMenu_BANK_PUTIN::showMessage(int index1, int index2)
{
    int mes1 = dq5::level::GoldMessage::getRecord(index1)->getMessage1();
    int mes2 = dq5::level::GoldMessage::getRecord(index2)->getMessage1();
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(mes1);
    if (mes2 != 0) {
        gTownMenu_MESSAGE.addMessage(mes2);
    }
}
