#include "ov012/materielmenu/MaterielMenuPokerChangecard.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/dss/Pad.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/text/TextAPI.hpp"
#include "ov012/casino/CasinoPokerDraw.hpp"
#include "ov012/casino/PokerAction.hpp"
#include "ov012/casino/PokerManager.hpp"
#include "ov012/materielmenu/MaterielMenuPokerBetcoin.hpp"
#include "ov012/materielmenu/MaterielMenu_POKER_HIGHANDLOW.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuDrawParts.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

inline void casino::PokerManager::setCardPosition(int position)
{
    cardPosition_ = position;
}

inline void casino::PokerManager::setGetCoin(int coin)
{
    getCoin_ = coin;
}

THUMB void MaterielMenuPokerChangecard::menuSetup()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    dealItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_NONE);
    menuItem_.active_ = 0;
    dealItem_.active_ = 0;
    navigator_128.setupBase();
    navigator_134.setupBase();
    gameMode_ = 0;
    animation_ = 1;
    combination_ = -1;
    unk_20 = 0;
    isPlaySound_ = 0;
    reverse_ = 0;
    betCoin_ = casino::PokerManager::getSingleton()->betCoin_;
    getCoin_ = 0;
    haveCoin_ = menu::MenuStatusInfo::getCoin() - betCoin_;
    ang_ = 0x8000;
    gyre_ = 0;
    index_ = 0;
    distance_ = casino::CasinoPokerDraw::getSingleton()->getDistance();
    casino::PokerAction::getSingleton()->initialize();
    casino::PokerAction::getSingleton()->setCardIndex(index_);
    casino::PokerAction::getSingleton()->pokerActionTabulate_.doubleUp_ = false;
    casino::PokerManager::getSingleton()->dealCard(-1);
    for (int i = 0; i < 5; i++) {
        change_[i] = 0;
    }
}

THUMB void MaterielMenuPokerChangecard::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_POKER_SELECT_CARD(&menuItem_, menuItem_.active_);
    menu::MenuTemplate_materiel::MATERIEL_POKER_SELECT_DEAL(&dealItem_, dealItem_.active_);
}

THUMB void MaterielMenuPokerChangecard::menuDraw()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    int draw = 0;
    if (isPlaySound_ == 0) {
        switch (animation_) {
        case 0:
            if (gameMode_ != 3 || gameMode_ != 4) {
                draw = 1;
                menuItem_.drawActive();
                dealItem_.drawActive();
            }
            break;
        case 1:
            pokerDealCard();
            break;
        case 2:
            pokerChangeCard();
            break;
        case 4:
            pokerReverseCard(false);
            break;
        case 5:
            pokerReverseCard(true);
            break;
        case 6:
            pokerFadeAnimation();
            break;
        }
    }
    int coin = betCoin_;
    if (unk_20 == 1) {
        coin = getCoin_;
    }
    unkfunc_0217c058(draw, haveCoin_, coin, change_, unk_20);
}

THUMB void MaterielMenuPokerChangecard::menuUpdate()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    if (cmn::g_cmnSoundManager.isPlaySound() == true) {
        cmn::g_cmnSoundManager.execSound();
        return;
    }
    isPlaySound_ = 0;
    if (unk_20 == 1 && animation_ == 0) {
        unkfunc_0212bab0();
    }
    if (animation_ == 1 || animation_ == 2) {
        return;
    }
    if (!messageUpdata()) {
        menuUpdata();
    }
}

THUMB bool MaterielMenuPokerChangecard::messageUpdata()
{
    if (gTownMenu_MESSAGE.isOpen()) {
        if (gameMode_ == 6) {
            unkfunc_0212baf0();
            return true;
        }
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            unkfunc_0212bb74();
        } else if (stat == MENUBASE_STAT_CANCEL) {
            unkfunc_0212bc70();
        }
        return true;
    }
    if (gameMode_ == 0) {
        showMessage(0xc92d1, -1);
        gameMode_ = 1;
    }
    if ((gameMode_ == 2 && animation_ == 2) || animation_ == 4) {
        return true;
    }
    if (gameMode_ == 2 && animation_ == 3) {
        combination_ = casino::PokerManager::getSingleton()->judgementCombination();
        if (combination_ == 0) {
            combination_ = -1;
            unk_20 = 0;
            showMessage(0xc92f0, 0xc92f4);
            gTownMenu_MESSAGE.setYesNo();
            gameMode_ = 4;
            menu::MenuStatusInfo::setCoin(haveCoin_);
            casino::PokerManager::getSingleton()->setBetCoin(betCoin_);
            getCoin_ = 0;
        } else {
            unk_20 = 1;
            getCoin_ = casino::PokerManager::getSingleton()->getMultiple() * betCoin_;
            if (haveCoin_ + getCoin_ > 9999999) {
                getCoin_ = 9999999 - haveCoin_;
            }
            if (haveCoin_ + getCoin_ * 2 > 9999999) {
                TextAPI::setMACRO0(0x45, 0xf0000000, 9999999 - haveCoin_);
            } else {
                TextAPI::setMACRO0(0x45, 0xf0000000, getCoin_ * 2);
            }
            TextAPI::setMACRO0(0x84, 0xe0000000, unkfunc_02178f7c(combination_) + 0x20000000);
            TextAPI::setMACRO0(0x48, 0xf0000000, getCoin_);
            TextAPI::setMACRO0(0x2e, 0xf0000000, 1);
            showMessage(0xc92d7, 0xc92d9);
            gTownMenu_MESSAGE.setYesNo();
            gameMode_ = 3;
            casino::PokerManager::getSingleton()->setGetCoin(getCoin_);
        }
        animation_ = 0;
    }
    return false;
}

THUMB void MaterielMenuPokerChangecard::menuUpdata()
{
    navigator_128.setup(5, 1, 5);
    if (gameMode_ == 1) {
        int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_128);
        if (result != 0) {
            if (result == 4 || result == 5) {
                casino::PokerManager::getSingleton()->setCardPosition(menuItem_.active_);
                menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_NONE);
                dealItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
                dealItem_.result_ = 0;
                dealItem_.lastresult_ = 0;
                gameMode_ = 2;
            } else if (result == 2) {
                change_[menuItem_.active_] = change_[menuItem_.active_] == 0 ? 1 : 0;
            }
            redraw_ = 1;
            return;
        }
    }
    navigator_134.setup(1, 1, 1);
    if (gameMode_ == 2) {
        int result = MenuUpdate_Assist::menuSelect(dealItem_, navigator_134);
        if (result != 0) {
            if (result == 4 || result == 5) {
                menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
                dealItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_NONE);
                menuItem_.active_ = casino::PokerManager::getSingleton()->cardPosition_;
                menuItem_.result_ = 0;
                menuItem_.lastresult_ = 0;
                gameMode_ = 1;
            } else if (result == 2) {
                dealItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_NONE);
                changeCard();
            }
            redraw_ = 1;
        }
    }
}

THUMB void MaterielMenuPokerChangecard::changeCard()
{
    for (int i = 0; i < 5; i++) {
        if (change_[i] == 0) {
            casino::PokerManager::getSingleton()->dealCard(i);
        }
    }
    casino::PokerManager::getSingleton()->clearDebugCard(-1);
    animation_ = 2;
    casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_REVERSE);
}

THUMB void MaterielMenuPokerChangecard::showMessage(int messageID, int messageID2)
{
    gTownMenu_MESSAGE.openMessageForMENU();
    gTownMenu_MESSAGE.addMessage(messageID);
    if (messageID2 != -1) {
        gTownMenu_MESSAGE.addMessage(messageID2);
    }
}

THUMB void MaterielMenuPokerChangecard::pokerDealCard()
{
    casino::PokerAction::getSingleton()->execute();
    if (casino::PokerAction::getSingleton()->isEnd() == true) {
        index_++;
        casino::PokerAction::getSingleton()->setCardIndex(index_);
        if (index_ > 4) {
            index_ = 0;
            animation_ = 0;
            combination_ = casino::PokerManager::getSingleton()->judgementCombination();
            if (combination_ != 0) {
                getCoin_ = casino::PokerManager::getSingleton()->getMultiple() * betCoin_;
                cmn::g_cmnSoundManager.setPlaySound(8, false);
                isPlaySound_ = 1;
                unk_20 = 1;
            }
        }
    }
}

THUMB void MaterielMenuPokerChangecard::pokerChangeCard()
{
    while (change_[index_] != 0) {
        index_++;
        if (index_ > 4) {
            index_ = 0;
            if (reverse_ == 1) {
                reverse_ = 0;
                animation_ = 3;
                if (casino::PokerManager::getSingleton()->judgementCombination() != 0) {
                    setSoundNo();
                }
                casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_REVERSE);
            } else {
                reverse_ = 1;
                casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_TABULATE);
            }
            return;
        }
    }
    casino::PokerAction::getSingleton()->setCardIndex(index_);
    casino::PokerAction::getSingleton()->execute();
    if (reverse_ == 1) {
        if (casino::PokerAction::getSingleton()->isEnd() == true) {
            if (++index_ > 4) {
                index_ = 0;
                reverse_ = 0;
                animation_ = 3;
                if (casino::PokerManager::getSingleton()->judgementCombination() != 0) {
                    setSoundNo();
                }
                casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_REVERSE);
            }
        }
    } else if (casino::PokerAction::getSingleton()->isEnd() == true) {
        if (++index_ > 4) {
            index_ = 0;
            reverse_ = 1;
            casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_TABULATE);
        }
    }
}

THUMB void MaterielMenuPokerChangecard::pokerReverseCard(bool flag)
{
    casino::PokerAction::getSingleton()->setCardIndex(index_);
    casino::PokerAction::getSingleton()->execute();
    if (casino::PokerAction::getSingleton()->isEnd() == true) {
        if (++index_ > 4) {
            if (flag) {
                animation_ = 6;
                casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_FADE);
            } else {
                close();
                gMaterielMenu_POKER_BETCOIN.open();
            }
        }
    }
}

THUMB void MaterielMenuPokerChangecard::pokerFadeAnimation()
{
    if (casino::PokerAction::getSingleton()->isEnd() == true) {
        close();
        gMaterielMenu_POKER_HIGHANDLOW.open();
        return;
    }
    for (int i = 0; i < 5; i++) {
        casino::PokerAction::getSingleton()->setCardIndex(i);
        casino::PokerAction::getSingleton()->execute();
    }
}

THUMB void MaterielMenuPokerChangecard::setSoundNo()
{
    isPlaySound_ = 1;
    int coin = betCoin_ * casino::PokerManager::getSingleton()->getMultiple();
    int sound = 8;
    if (coin >= 10000) {
        sound = 10;
    } else if (coin >= 500) {
        sound = 9;
    }
    cmn::g_cmnSoundManager.setPlaySound(sound, false);
}

THUMB void MaterielMenuPokerChangecard::unkfunc_0212bab0()
{
    if (effectCount_ > 90) {
        for (int i = 0; i < 5; i++) {
            if (casino::PokerManager::getSingleton()->combinationCard_[i] == 1) {
                casino::CasinoPokerDraw::getSingleton()->setEffect(i);
            }
        }
        effectCount_ = 0;
    } else {
        effectCount_++;
    }
}

THUMB void MaterielMenuPokerChangecard::unkfunc_0212baf0()
{
    SoundManager::playSe(0x154, 0);
    if ((dss::g_Pad.edge() & 1) || (dss::g_Pad.edge() & 0x400)) {
        menu::MenuStatusInfo::setCoin(getCoin_ + menu::MenuStatusInfo::getCoin());
        getCoin_ = 0;
        haveCoin_ = menu::MenuStatusInfo::getCoin();
        gameMode_ = 8;
        redraw_ = 1;
    } else if (getCoin_ > 0) {
        if (getCoin_ == 1) {
            haveCoin_ += 1;
            getCoin_ = 0;
        } else {
            haveCoin_ += 2;
            getCoin_ -= 2;
        }
        redraw_ = 1;
    } else {
        gameMode_ = 8;
    }
    menu::MenuStatusInfo::setCoin(haveCoin_);
}

THUMB void MaterielMenuPokerChangecard::unkfunc_0212bb74()
{
    switch (gameMode_) {
    case 5:
        gameMode_ = 6;
        return;
    case 3:
        gTownMenu_MESSAGE.close();
        animation_ = 5;
        return;
    case 4:
        gTownMenu_MESSAGE.close();
        animation_ = 4;
        redraw_ = 1;
        return;
    case 8:
        gTownMenu_MESSAGE.close();
        showMessage(0xc92f4, -1);
        gTownMenu_MESSAGE.setYesNo();
        betCoin_ = 0;
        getCoin_ = 0;
        unk_20 = 0;
        casino::PokerManager::getSingleton()->winningCombination_ = 0;
        gameMode_ = 4;
        redraw_ = 1;
        return;
    case 7:
        gTownMenu_MESSAGE.close();
        gameMode_ = 3;
        if (getCoin_ + menu::MenuStatusInfo::getCoin() - betCoin_ > 9999999) {
            getCoin_ = 9999999 - menu::MenuStatusInfo::getCoin();
        }
        casino::PokerManager::getSingleton()->setGetCoin(getCoin_);
        TextAPI::setMACRO0(0x45, 0xf0000000, getCoin_ * 2);
        TextAPI::setMACRO0(0x2e, 0xf0000000, 1);
        showMessage(0xc92d9, -1);
        gTownMenu_MESSAGE.setYesNo();
        return;
    default:
        gTownMenu_MESSAGE.close();
        return;
    }
}

THUMB void MaterielMenuPokerChangecard::unkfunc_0212bc70()
{
    gTownMenu_MESSAGE.close();
    if (gameMode_ == 3 || gameMode_ == 7) {
        TextAPI::setMACRO0(0x48, 0xf0000000, getCoin_);
        showMessage(0xc92ec, -1);
        gameMode_ = 5;
        if (haveCoin_ + getCoin_ >= 9999999) {
            betCoin_ = 0;
        }
    } else if (gameMode_ == 4) {
        MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
    }
}
