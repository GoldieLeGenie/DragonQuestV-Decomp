#include "ov030/materielmenu/bank/MaterielMenu_BANK_DRAW.hpp"
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

THUMB void MaterielMenu_BANK_DRAW::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_UP);
    menuItem_.active_ = 2;
    navigator_.setupBase();
    bankMoney_ = MenuStatusInfo::getBank();
    drawMoney_ = 0;
    mode_ = DRAW_START;
}

THUMB void MaterielMenu_BANK_DRAW::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menu::MenuTemplate_materiel::MATERIEL_MONEY_SELECT(&menuItem_, menuItem_.active_, 3);
}

THUMB void MaterielMenu_BANK_DRAW::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (mode_ == DRAW_START) {
        drawMoneyAndPartyWindows();
        return;
    }
    int open = gTownMenu_MESSAGE.isOpen();
    drawBankAmountScreen(open, 0, drawMoney_);
    if (open == 0) {
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_BANK_DRAW::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (!messageUpdate()) {
        bankUpdate();
    }
}

THUMB bool MaterielMenu_BANK_DRAW::messageUpdate()
{
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (mode_ == DRAW_END) {
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            }
        }
        return true;
    }
    if (mode_ == DRAW_START) {
        if (bankMoney_ == 0) {
            showMessage(15, 22);
            mode_ = DRAW_END;
        }
        else {
            TextAPI::setMACRO0(0x30, 0xf0000000, bankMoney_);
            showMessage(16, 0);
            mode_ = DRAW_SELECT;
        }
        return true;
    }
    return false;
}

THUMB void MaterielMenu_BANK_DRAW::bankUpdate()
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
            cancelDrawfrom();
            return;
        }
        if (result == 2) {
            if (drawMoney_ == 0) {
                cancelDrawfrom();
            }
            else {
                bankDraw();
            }
        }
        if (result == 4) {
            drawMoney_ += price;
            if (drawMoney_ > 999000) {
                drawMoney_ = 999000;
            }
        }
        if (result == 5) {
            drawMoney_ -= price;
            if (drawMoney_ < 0) {
                drawMoney_ = 0;
            }
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_BANK_DRAW::bankDraw()
{
    menuItem_.active_ = 2;
    unsigned int draw = drawMoney_;
    if (draw > bankMoney_) {
        showMessage(17, 0);
        drawMoney_ = 0;
        mode_ = DRAW_START;
        return;
    }
    if (draw + MenuStatusInfo::getGold() > 999999) {
        showMessage(18, 0);
        drawMoney_ = 0;
        mode_ = DRAW_START;
        return;
    }
    MenuStatusInfo::setBank(bankMoney_ - draw);
    MenuStatusInfo::setGold(drawMoney_ + MenuStatusInfo::getGold());
    TextAPI::setMACRO0(0x37, 0xf0000000, drawMoney_);
    if (MenuStatusInfo::getBank() == 0) {
        showMessage(19, 22);
    }
    else {
        TextAPI::setMACRO0(0x30, 0xf0000000, MenuStatusInfo::getBank());
        showMessage(19, 21);
    }
    mode_ = DRAW_END;
}

THUMB void MaterielMenu_BANK_DRAW::cancelDrawfrom()
{
    if (bankMoney_ == 0) {
        showMessage(20, 22);
    }
    else {
        TextAPI::setMACRO0(0x30, 0xf0000000, bankMoney_);
        showMessage(20, 21);
    }
    mode_ = DRAW_END;
}

THUMB void MaterielMenu_BANK_DRAW::showMessage(int index1, int index2)
{
    int mes1 = dq5::level::GoldMessage::getRecord(index1)->getMessage1();
    int mes2 = dq5::level::GoldMessage::getRecord(index2)->getMessage1();
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(mes1);
    if (mes2 != 0) {
        gTownMenu_MESSAGE.addMessage(mes2);
    }
}
