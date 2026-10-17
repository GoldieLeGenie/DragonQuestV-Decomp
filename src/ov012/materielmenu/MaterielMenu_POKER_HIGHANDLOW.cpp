#include "ov012/materielmenu/MaterielMenu_POKER_HIGHANDLOW.hpp"
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
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

inline void casino::PokerManager::setGetCoin(int coin)
{
    getCoin_ = coin;
}

inline dss::Fix32Vector3 casino::CasinoPokerDraw::getCardPosition(int cardIndex)
{
    return card[cardIndex].getPosition();
}

inline casino::PokerActionMove& casino::PokerAction::getActionMove()
{
    return pokerActionMove_;
}

inline void casino::PokerActionMove::setMoveDirection(char direction)
{
    direction_ = direction;
}

inline void casino::PokerActionMove::setEndPos(dss::Fix32Vector3 pos)
{
    endPos_ = pos;
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::menuSetup()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    casino::PokerManager::getSingleton()->startHighAndLow();
    m_mode = 0;
    m_doubleupCount = 0;
    m_getCoin = casino::PokerManager::getSingleton()->getCoin_;
    int bet = casino::PokerManager::getSingleton()->betCoin_;
    m_haveCoin = menu::MenuStatusInfo::getCoin() - bet;
    m_win = 0;
    m_isPlaySound = 0;
    m_pos = 1;
    casino::CasinoPokerDraw::getSingleton()->setHighLowPosition();
    casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_FADE);
    casino::PokerAction::getSingleton()->pokerActionTabulate_.doubleUp_ = true;
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_POKER_HI_AND_LOW(&menuItem_, menuItem_.active_);
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::menuDraw()
{
    if (m_isPlaySound != 0) {
        return;
    }
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    unkfunc_0217c07c(m_mode, m_haveCoin, m_getCoin, m_win);
    if (m_mode == 1) {
        menuItem_.drawActive();
    }
    switch (casino::PokerAction::getSingleton()->action_) {
    case casino::CARD_ACTION_TABULATE:
    case casino::CARD_ACTION_REVERSE:
        actionSwing();
        break;
    case casino::CARD_ACTION_MOVE:
        actionMove();
        break;
    case casino::CARD_ACTION_FADE:
        actionFade();
        break;
    }
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::menuUpdate()
{
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::PLAYER_MODE);
    if (cmn::g_cmnSoundManager.isPlaySound() == true) {
        cmn::g_cmnSoundManager.execSound();
        return;
    }
    m_isPlaySound = 0;
    if (!messageUpdate()) {
        statusUpdate();
    }
}

THUMB bool MaterielMenu_POKER_HIGHANDLOW::messageUpdate()
{
    if (casino::PokerAction::getSingleton()->action_ != casino::CARD_ACTION_MAX) {
        return true;
    }
    if (gTownMenu_MESSAGE.isOpen()) {
        if (m_mode == 8) {
            getCoinAction();
            return true;
        }
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            if (m_mode != 7) {
                gTownMenu_MESSAGE.close();
            }
            selectYes();
        } else if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            selectNo();
        }
        return true;
    }
    if (m_mode == 0) {
        showMessage(0xc92dd, 0);
        return true;
    }
    if (m_mode == 11) {
        m_doubleupCount++;
        m_getCoin = m_getCoin * 2;
        casino::PokerManager::getSingleton()->setGetCoin(m_getCoin);
        m_win = 1;
        if (m_haveCoin + m_getCoin > 9999999) {
            m_getCoin = 9999999 - m_haveCoin;
            TextAPI::setMACRO0(0x48, 0xf0000000, m_getCoin);
            showMessage(0xc92e0, 0xc92e3);
            gTownMenu_MESSAGE.setYesNo();
            m_mode = 6;
            m_pos = 2;
        } else {
            TextAPI::setMACRO0(0x48, 0xf0000000, m_getCoin);
            showMessage(0xc92e0, 0);
            m_mode = 3;
            dss::Fix32Vector3 pos = casino::CasinoPokerDraw::getSingleton()->getCardPosition(1);
            casino::PokerAction::getSingleton()->getActionMove().setMoveDirection(3);
            casino::PokerAction::getSingleton()->getActionMove().setEndPos(pos);
            m_pos = 1;
        }
        return true;
    }
    return false;
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::statusUpdate()
{
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    navigator_.setup(1, 2, 2);
    if (result != 0) {
        if (m_mode == 12) {
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            return;
        }
        if (result == 2) {
            m_mode = 2;
            casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_TABULATE);
            m_pos = 0;
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::selectYes()
{
    switch (m_mode) {
    case 0:
        m_mode = 1;
        break;
    case 3:
        casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_MOVE);
        break;
    case 4:
    case 5:
        casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_REVERSE);
        m_pos = 2;
        break;
    case 6: {
        m_mode = 3;
        dss::Fix32Vector3 pos = casino::CasinoPokerDraw::getSingleton()->getCardPosition(1);
        casino::PokerAction::getSingleton()->getActionMove().setMoveDirection(3);
        casino::PokerAction::getSingleton()->getActionMove().setEndPos(pos);
        casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_MOVE);
        break;
    }
    case 7:
        m_mode = 8;
        menu::MenuStatusInfo::getCoin();
        break;
    case 9:
        m_mode = 0;
        m_win = 0;
        break;
    case 10:
        casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_REVERSE);
        break;
    case 13:
        break;
    }
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::selectNo()
{
    switch (m_mode) {
    case 0:
        m_mode = 1;
        break;
    case 4:
        MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
        break;
    case 6:
    case 9:
        menuItem_.active_ = 0;
        TextAPI::setMACRO0(0x48, 0xf0000000, m_getCoin);
        showMessage(0xc92ec, 0);
        m_mode = 7;
        break;
    case 10:
        MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
        break;
    case 13:
        break;
    }
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::judgementHiAndLow()
{
    switch (casino::PokerManager::getSingleton()->getHighAndLowResult()) {
    case casino::DOUBLEUP_WIN:
        m_mode = 11;
        setSoundNo();
        break;
    case casino::DOUBLEUP_LOSE: {
        m_getCoin = 0;
        casino::PokerManager::getSingleton()->getCoin_ = 0;
        casino::PokerManager::getSingleton()->winningCombination_ = 0;
        int bet = casino::PokerManager::getSingleton()->betCoin_;
        menu::MenuStatusInfo::setCoin(menu::MenuStatusInfo::getCoin() - bet);
        m_doubleupCount = 0;
        m_win = 0;
        showMessage(0xc92f0, 0xc92f4);
        gTownMenu_MESSAGE.setYesNo();
        m_mode = 4;
        break;
    }
    case casino::DOUBLEUP_DRAW:
        m_doubleupCount++;
        showMessage(0xc92e9, 0);
        m_mode = 5;
        break;
    }
    menuItem_.active_ = 0;
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::showMessage(int messageID, int messageID2)
{
    gTownMenu_MESSAGE.openMessageForMENU();
    gTownMenu_MESSAGE.addMessage(messageID);
    if (messageID2 != 0) {
        gTownMenu_MESSAGE.addMessage(messageID2);
    }
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::getCoinAction()
{
    SoundManager::playSe(0x154, 0);
    if ((dss::g_Pad.edge() & 1) || (dss::g_Pad.edge() & 0x400)) {
        menu::MenuStatusInfo::setCoin(m_getCoin + menu::MenuStatusInfo::getCoin());
        m_getCoin = 0;
        m_haveCoin = menu::MenuStatusInfo::getCoin();
        redraw_ = 1;
        if (m_haveCoin == 9999999) {
            m_mode = 12;
        } else {
            showMessage(0xc92f4, 0);
            gTownMenu_MESSAGE.setYesNo();
            m_mode = 10;
        }
    } else if (m_getCoin > 0) {
        if (m_getCoin == 1) {
            m_haveCoin += 1;
            m_getCoin = 0;
        } else {
            m_haveCoin += 2;
            m_getCoin -= 2;
        }
        redraw_ = 1;
    } else if (m_haveCoin == 9999999) {
        MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
    } else {
        showMessage(0xc92f4, 0);
        gTownMenu_MESSAGE.setYesNo();
        m_mode = 10;
    }
    menu::MenuStatusInfo::setCoin(m_haveCoin);
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::actionFade()
{
    if (casino::PokerAction::getSingleton()->isEnd() == true) {
        casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_MAX);
        if (m_mode == 3) {
            if (m_haveCoin + m_getCoin * 2 > 9999999) {
                TextAPI::setMACRO0(0x45, 0xf0000000, 9999999 - m_haveCoin);
            } else {
                TextAPI::setMACRO0(0x45, 0xf0000000, m_getCoin * 2);
            }
            TextAPI::setMACRO0(0x2e, 0xf0000000, m_doubleupCount + 1);
            showMessage(0xc92d9, 0);
            gTownMenu_MESSAGE.setYesNo();
            m_mode = 9;
        } else if (m_mode == 4) {
            m_mode = 10;
            casino::CasinoPokerDraw::getSingleton()->setPoolPosition();
            for (int i = 0; i < 5; i++) {
                casino::CasinoPokerDraw::getSingleton()->setCardAngle(i, 0);
                casino::CasinoPokerDraw::getSingleton()->setAlpha(i, 0);
            }
            casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_FADE);
        } else if (m_mode == 10) {
            close();
            gMaterielMenu_POKER_BETCOIN.open();
        } else {
            casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_TABULATE);
            m_pos = 1;
        }
        return;
    }
    if (m_mode == 3) {
        casino::PokerAction::getSingleton()->setCardIndex(0);
        casino::PokerAction::getSingleton()->execute();
        return;
    }
    int count = 5;
    if (m_mode == 4) {
        count = 2;
    }
    for (int i = 0; i < count; i++) {
        casino::PokerAction::getSingleton()->setCardIndex(i);
        casino::PokerAction::getSingleton()->execute();
    }
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::actionSwing()
{
    if (casino::PokerAction::getSingleton()->isEnd() == true) {
        casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_MAX);
        if (m_mode == 0) {
            return;
        }
        if (m_mode == 2) {
            casino::PokerManager::getSingleton()->setAnswer(menuItem_.active_);
            judgementHiAndLow();
            return;
        }
        if (m_mode == 5) {
            m_mode = 0;
            casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_TABULATE);
            m_pos = 1;
            return;
        }
        if (m_mode == 4 || m_mode == 10) {
            casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_FADE);
            m_mode = 4;
        }
        return;
    }
    switch (m_pos) {
    case 0:
        casino::PokerAction::getSingleton()->setCardIndex(0);
        casino::PokerAction::getSingleton()->execute();
        break;
    case 1:
        casino::PokerAction::getSingleton()->setCardIndex(1);
        casino::PokerAction::getSingleton()->execute();
        break;
    case 2:
        casino::PokerAction::getSingleton()->setCardIndex(0);
        casino::PokerAction::getSingleton()->execute();
        casino::PokerAction::getSingleton()->setCardIndex(1);
        casino::PokerAction::getSingleton()->execute();
        break;
    }
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::actionMove()
{
    if (casino::PokerAction::getSingleton()->isEnd() == true) {
        casino::CasinoPokerDraw::getSingleton()->setAlpha(0, 0);
        casino::CasinoPokerDraw::getSingleton()->setHighLowPosition();
        casino::CasinoPokerDraw::getSingleton()->setCardAngle(1, 0);
        setCardTex(1, true);
        casino::CasinoPokerDraw::getSingleton()->setCardAngle(0, 0x8000);
        setCardTex(0, false);
        casino::PokerAction::getSingleton()->setCardAction(casino::CARD_ACTION_FADE);
        return;
    }
    casino::PokerAction::getSingleton()->setCardIndex(0);
    casino::PokerAction::getSingleton()->execute();
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::setCardTex(int card, bool base)
{
    int type = casino::PokerManager::getSingleton()->getHighAndLowCardType(base);
    int no = 0;
    if (type != casino::TYPE_JOKER) {
        no = casino::PokerManager::getSingleton()->getHighAndLowCardNo(base);
    }
    casino::CasinoPokerDraw::getSingleton()->setCardTexture(card, type, no);
}

THUMB void MaterielMenu_POKER_HIGHANDLOW::setSoundNo()
{
    m_isPlaySound = 1;
    int coin = m_getCoin * 2;
    int sound = 8;
    if (coin >= 10000) {
        sound = 10;
    } else if (coin >= 500) {
        sound = 9;
    }
    cmn::g_cmnSoundManager.setPlaySound(sound, false);
}
