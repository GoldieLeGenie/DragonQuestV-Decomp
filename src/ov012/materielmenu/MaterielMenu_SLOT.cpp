#include "ov012/materielmenu/MaterielMenu_SLOT.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/text/TextAPI.hpp"
#include "ov012/casino/CasinoSlot.hpp"
#include "ov012/casino/Casino_Slot.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

inline void casino::Casino_Slot::setBetCost(int cost)
{
    betCost_ = cost;
}

inline unsigned int status::BasePartyStatus::getCasinoCoin()
{
    return casinoCoin_;
}

THUMB void MaterielMenu_SLOT::menuSetup()
{
    status::g_Party.setPlayerMode();
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    int gameStatus = g_Global.getGameStatus();
    int reelType;
    if (gameStatus < 5) {
        betCost_ = 1;
        slotType_ = gameStatus - 1;
        reelType = slotType_;
    } else if (gameStatus < 9) {
        betCost_ = 10;
        slotType_ = gameStatus - 5;
        reelType = slotType_;
    } else {
        betCost_ = 100;
        slotType_ = 4;
        reelType = 0;
    }
    if (gameStatus == 0) {
        betCost_ = 100;
        slotType_ = 4;
        reelType = 0;
    }
    casino::Casino_Slot::getSingleton()->setSlotType(slotType_);
    casino::CasinoSlot::getSingleton()->setSlotType(reelType);
    casino::Casino_Slot::getSingleton()->setBetCost(betCost_);
    status_ = SLOT_START;
    messageCount_ = -1;
    haveCoin_ = 0;
    betCoin_ = 0;
}

THUMB void MaterielMenu_SLOT::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_GET_UPDOWN(&menuItem_);
}

THUMB void MaterielMenu_SLOT::menuDraw()
{
    drawSlotCoins(haveCoin_, 0);
}

THUMB void MaterielMenu_SLOT::menuUpdate()
{
    if (cmn::g_cmnSoundManager.isPlaySound() == true) {
        cmn::g_cmnSoundManager.execSound();
    } else if (!messageUpdate()) {
        statusUpdate();
    }
}

THUMB bool MaterielMenu_SLOT::messageUpdate()
{
    if (!gTownMenu_MESSAGE.isOpen()) {
        return false;
    }
    int stat = gTownMenu_MESSAGE.stat_;
    if (status_ == SLOT_RETRY && messageCount_ == 0) {
        if (stat == menu::MenuBase::MENUBASE_STAT_OK) {
            status_ = SLOT_START;
            messageCount_ = -1;
            gTownMenu_MESSAGE.close();
        } else if (stat == menu::MenuBase::MENUBASE_STAT_CANCEL) {
            status_ = SLOT_END;
            messageCount_ = -1;
            gTownMenu_MESSAGE.close();
        }
    }
    closeMessage();
    return true;
}

THUMB void MaterielMenu_SLOT::statusUpdate()
{
    switch (status_) {
    case SLOT_START:
        if (messageCount_ == -1) {
            haveCoin_ = status::g_Party.getCasinoCoin();
            if (status::g_Party.getCasinoCoin() == 0) {
                showMessage(0xc96af);
                status_ = SLOT_END;
                messageCount_ = -1;
                return;
            }
            if (status::g_Party.getCasinoCoin() < betCost_) {
                showMessage(0xc96c5);
                status_ = SLOT_END;
                messageCount_ = -1;
                return;
            }
            showMessage(0xc96b2);
            menuItem_.active_ = 0;
            messageCount_++;
            casino::Casino_Slot::getSingleton()->resetSlot();
            casino::Casino_Slot::getSingleton()->instantAddCoin(haveCoin_, betCoin_);
            betCoin_ = casino::Casino_Slot::getSingleton()->betCoin_;
        } else {
            inputUpdate();
        }
        break;
    case SLOT_GAME:
        startSlot();
        break;
    case SLOT_RESULT:
        if (resultCoin_ > 0) {
            TextAPI::setMACRO0(0x48, 0xf0000000, resultCoin_);
            showMessage(0xc96b7);
            status_ = SLOT_RESULT_EFFECT;
            messageCount_ = -1;
            if (casino::CasinoSlot::getSingleton()->bingoType_ == 2) {
                cmn::g_cmnSoundManager.setPlaySound(10, false);
            } else if (casino::CasinoSlot::getSingleton()->bingoType_ == 1) {
                cmn::g_cmnSoundManager.setPlaySound(9, false);
            } else {
                cmn::g_cmnSoundManager.setPlaySound(8, false);
            }
        } else {
            showMessage(0xc96bd);
            status::g_Party.setCasinoCoin(haveCoin_);
            casino::CasinoSlot::getSingleton()->setLampOff();
            status_ = SLOT_RETRY;
            messageCount_ = -1;
        }
        break;
    case SLOT_RESULT_EFFECT:
        showEffect();
        status::g_Party.setCasinoCoin(haveCoin_);
        break;
    case SLOT_RETRY:
        if (messageCount_ == -1) {
            showMessage(0xc96c0);
            gTownMenu_MESSAGE.setYesNo();
            messageCount_++;
        }
        break;
    case SLOT_END:
        gTownMenu_MESSAGE.close();
        close();
        stat_ = MENUBASE_STAT_OK;
        MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
        break;
    }
}

THUMB void MaterielMenu_SLOT::inputUpdate()
{
    menuItem_.execInput();
    switch (menuItem_.result_) {
    case menu::MenuItem::MENUITEM_RESULT_CANCEL:
    case menu::MenuItem::MENUITEM_RESULT_SUPERCANCEL:
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        status_ = SLOT_END;
        messageCount_ = -1;
        break;
    case menu::MenuItem::MENUITEM_RESULT_OK:
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        if (betCoin_ > 0) {
            casino::Casino_Slot::getSingleton()->startSlot();
            status_ = SLOT_GAME;
            messageCount_ = -1;
        }
        break;
    case menu::MenuItem::MENUITEM_RESULT_UP:
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        if (betCoin_ == MAX_BETCOIN) {
            casino::Casino_Slot::getSingleton()->startSlot();
            status_ = SLOT_GAME;
            messageCount_ = -1;
        } else {
            casino::Casino_Slot::getSingleton()->addCoin(haveCoin_);
            betCoin_ = casino::Casino_Slot::getSingleton()->betCoin_;
            redraw_ = 1;
        }
        break;
    case menu::MenuItem::MENUITEM_RESULT_DOWN:
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        casino::Casino_Slot::getSingleton()->subCoin(haveCoin_);
        betCoin_ = casino::Casino_Slot::getSingleton()->betCoin_;
        redraw_ = 1;
        break;
    }
}

THUMB void MaterielMenu_SLOT::showEffect()
{
    int oldCoin = haveCoin_;
    if (casino::Casino_Slot::getSingleton()->showEffect()) {
        casino::Casino_Slot::getSingleton()->cashAllCoin(haveCoin_);
        status::g_Party.setCasinoCoin(haveCoin_);
        casino::CasinoSlot::getSingleton()->setLampOff();
        resultCoin_ = 0;
        status_ = SLOT_RETRY;
        messageCount_ = -1;
    }
    if ((dss::g_Pad.edge() & 1) || (dss::g_Pad.edge() & 0x400)) {
        casino::Casino_Slot::getSingleton()->cashAllCoin(haveCoin_);
        status::g_Party.setCasinoCoin(haveCoin_);
        resultCoin_ = 0;
    }
    casino::Casino_Slot::getSingleton()->cashCoin(haveCoin_);
    if (oldCoin < haveCoin_) {
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_SLOT::startSlot()
{
    if (casino::Casino_Slot::getSingleton()->runningSlot()) {
        resultCoin_ = 0;
        resultCoin_ = casino::Casino_Slot::getSingleton()->getResultAllCoin();
        status_ = SLOT_RESULT;
        messageCount_ = -1;
    }
}

THUMB void MaterielMenu_SLOT::showMessage(int messageID)
{
    gTownMenu_MESSAGE.openMessageForMENU();
    gTownMenu_MESSAGE.addMessage(messageID);
}

THUMB void MaterielMenu_SLOT::closeMessage()
{
    if ((unsigned int)(gTownMenu_MESSAGE.stat_ - 1) <= 1) {
        gTownMenu_MESSAGE.close();
    }
}
