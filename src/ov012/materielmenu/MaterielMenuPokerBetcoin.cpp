#include "ov012/materielmenu/MaterielMenuPokerBetcoin.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/sound/SoundManager.hpp"
#include "ov012/casino/CasinoPokerDraw.hpp"
#include "ov012/casino/PokerManager.hpp"
#include "ov012/materielmenu/MaterielMenuPokerChangecard.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"

THUMB void MaterielMenuPokerBetcoin::menuSetup()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    menuItem_.active_ = 0;
    messageMode_ = 0;
    blinkCount_ = 0;
    blink_ = 0;
    casino::CasinoPokerDraw::getSingleton()->setPoolPosition();
    casino::PokerManager::getSingleton()->winningCombination_ = 0;
}

THUMB void MaterielMenuPokerBetcoin::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_POKER_BET_COIN(&menuItem_, menuItem_.active_);
}

THUMB void MaterielMenuPokerBetcoin::menuDraw()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    int bet = casino::PokerManager::getSingleton()->betCoin_;
    int coin = menu::MenuStatusInfo::getCoin();
    if (coin < bet) {
        bet = coin;
    }
    drawPokerBetCoinScreen(coin - bet, bet, blink_);
}

THUMB void MaterielMenuPokerBetcoin::menuUpdate()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    if (updateBetInput() != 1) {
        updateMessage();
    }
}

THUMB int MaterielMenuPokerBetcoin::updateBetInput()
{
    if (messageMode_ == 0) {
        char mode;
        if (menu::MenuStatusInfo::getCoin() == 0) {
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xc92ca);
            mode = 4;
        } else {
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessageNOWAIT(0xc92cd);
            gTownMenu_MESSAGE.addMessageWAITKEY();
            mode = 2;
        }
        messageMode_ = mode;
        return 1;
    }
    if (!gTownMenu_MESSAGE.isOpen() || !gTownMenu_MESSAGE.isMessageWAITPROG()) {
        return 0;
    }
    updateBlink();
    navigator_.setup(1, 1, 1);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        int bet = casino::PokerManager::getSingleton()->betCoin_;
        switch (result) {
        case 4:
            if (bet == menu::MenuStatusInfo::getCoin() || bet == 10) {
                casino::PokerManager::getSingleton()->setBetCoin(bet);
                casino::PokerManager::getSingleton()->cardPosition_ = 0;
                gTownMenu_MESSAGE.close();
                gTownMenu_MESSAGE.clearMessageWAITPROG();
                close();
                gMaterielMenu_POKER_CHANGECARD.open();
            } else {
                bet++;
                SoundManager::playSe(0x154, 0);
            }
            break;
        case 5:
            if (bet > 0) {
                bet--;
                SoundManager::playSe(0x154, 0);
            }
            break;
        case 2:
            if (bet != 0) {
                casino::PokerManager::getSingleton()->setBetCoin(bet);
                casino::PokerManager::getSingleton()->cardPosition_ = 0;
                gTownMenu_MESSAGE.close();
                gTownMenu_MESSAGE.clearMessageWAITPROG();
                close();
                gMaterielMenu_POKER_CHANGECARD.open();
            }
            break;
        case 3:
            gTownMenu_MESSAGE.close();
            gTownMenu_MESSAGE.clearMessageWAITPROG();
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xc92f4);
            gTownMenu_MESSAGE.setYesNo();
            messageMode_ = 3;
            blinkCount_ = 0;
            bet = 0;
            break;
        }
        casino::PokerManager::getSingleton()->setBetCoin(bet);
        redraw_ = 1;
    }
    return 1;
}

THUMB void MaterielMenuPokerBetcoin::updateMessage()
{
    int stat = gTownMenu_MESSAGE.stat_;
    if (stat == MENUBASE_STAT_OK) {
        if (messageMode_ == 4) {
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
        }
        if (messageMode_ == 3) {
            messageMode_ = 0;
        }
    } else if (stat == MENUBASE_STAT_CANCEL) {
        gTownMenu_MESSAGE.close();
        MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
    }
}

THUMB void MaterielMenuPokerBetcoin::updateBlink()
{
    if (blinkCount_ > 30) {
        blinkCount_ = 0;
        blink_ = 1;
        redraw_ = 1;
        return;
    }
    if (blinkCount_ == 10) {
        blink_ = 0;
        redraw_ = 1;
    }
    blinkCount_++;
}
