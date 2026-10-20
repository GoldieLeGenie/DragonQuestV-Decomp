#include "ov037/materielmenu/casino/MaterielMenu_FIGHT_STADIUM.hpp"
#include "ov037/materielmenu/casino/FightStadiumManager.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/dss/Pad.hpp"
#include "main/menu/StadiumData.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/menu/UnkMenuCasinoDraw.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "main/text/TextAPI.hpp"

inline FightStadiumManager& FightStadiumManager::getSingleton()
{
    return m_singleton;
}

inline int FightStadiumManager::getMonsterCount()
{
    return cardCount_;
}

inline void MaterielMenu_FIGHT_STADIUM::setMenuStatus(int status)
{
    status_ = status;
    messageCount_ = -1;
}

inline unsigned int status::BasePartyStatus::getCasinoCoin()
{
    return casinoCoin_;
}

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

inline unsigned char StadiumData::getBetArray()
{
    return monsterArray_;
}

inline void StadiumData::setBetArray(unsigned char betArray)
{
    monsterArray_ = betArray;
}

inline void StadiumData::setBetID(unsigned char id)
{
    monsterID_ = id;
}

inline void StadiumData::setBetNumber(char number)
{
    monsterNumber_ = number;
}

inline void menu::MenuItem::resetResult()
{
    result_ = 0;
    lastresult_ = 0;
}

inline void status::StageInfo::setOverviewPosition(dss::Fix32Vector3& pos)
{
    overviewPosition_ = pos;
    overviewTempPosition_ = pos;
}

THUMB void MaterielMenu_FIGHT_STADIUM::menuSetup()
{
    status::g_Party.setPlayerMode();
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_UP);
    monsterItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 1;
    setMenuStatus(FIGHT_STADIUM_START);
    haveCoin_ = status::g_Party.getCasinoCoin();
    int result = g_StadiumData.result_;
    if (result != RESULT_NONE) {
        status::g_Menu.bookingFlag_ = 0;
        playBackMenu(result);
        g_StadiumData.result_ = RESULT_NONE;
        g_StadiumData.stadiumFlag_ = 0;
    }
    unk_104 = 0;
    m_bDispCoin = 0;
    blink_ = 0;
    blinkCount_ = 0;
    ui_MsgSndSet(0x32);
}

THUMB void MaterielMenu_FIGHT_STADIUM::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_MONSTER_LIST(&monsterItem_, monsterItem_.active_, FightStadiumManager::getSingleton().getMonsterCount());
    menu::MenuTemplate_materiel::MATERIEL_BET_COIN(&menuItem_, menuItem_.active_, 2, 0xf0, 0x2e);
}

THUMB void MaterielMenu_FIGHT_STADIUM::menuDraw()
{
    int show = 0;
    unkfunc_0202a0d0(haveCoin_, show, show, show);
    if (m_bDispCoin != 0
        || (status_ == FIGHT_STADIUM_RESULT && result_ < RESULT_DRAW)
        || (status_ == FIGHT_STADIUM_RETRY && messageCount_ != 0)
        || (unk_104 != 0 && g_StadiumData.doubleUp_ != 0)) {
        show = 1;
        unkfunc_0202a0d0(g_StadiumData.betCoin_, 0, 0x18, show);
        unkfunc_02029fc8(status_ == FIGHT_STADIUM_BET || unk_104 != 0);
        if (m_bDispCoin != 0) {
            if (blink_ != 0) {
                if (blinkCount_ > 15) {
                    menuItem_.drawActive();
                }
                if (blinkCount_ == 0 || blinkCount_ == 16) {
                    redraw_ = 1;
                }
                blinkCount_++;
                if (blinkCount_ > 30) {
                    blinkCount_ = 0;
                }
            }
            else {
                menuItem_.drawActive();
            }
        }
        if (m_bDispCoin != 0) {
            drawMenuFrame(0xb8, 0, 0x48, 0x48, -1);
        }
        else {
            drawMenuFrame(0xb8, 0, 0x48, 0x40, -1);
        }
    }
    else {
        drawMenuFrame(0xb8, 0, 0x48, 0x28, -1);
    }
    if (unk_104 != 0) {
        int count = FightStadiumManager::getSingleton().getMonsterCount();
        monsterItem_.drawActive();
        for (int i = 0; i < count; i++) {
            unkfunc_0202a034(FightStadiumManager::getSingleton().getMonsterID(i), FightStadiumManager::getSingleton().getDiameter(i), i, FightStadiumManager::getSingleton().getOrderCount(i));
        }
        drawMenuFrame(0, 0, 0xb8, count * 16 + 0x30, -1);
        unkfunc_02029fa4(show);
    }
    if (status_ == FIGHT_STADIUM_BET) {
        drawFightStadiumCursor(g_StadiumData.monsterArray_);
    }
}

THUMB void MaterielMenu_FIGHT_STADIUM::menuUpdate()
{
    if (cmn::g_cmnSoundManager.isPlaySound()) {
        cmn::g_cmnSoundManager.execSound();
        return;
    }
    if (!messageUpdate()) {
        statusUpdate();
    }
}

THUMB bool MaterielMenu_FIGHT_STADIUM::messageUpdate()
{
    if (!gTownMenu_MESSAGE.isOpen()) {
        return false;
    }
    int stat = gTownMenu_MESSAGE.stat_;
    switch (status_) {
        case FIGHT_STADIUM_START:
        case FIGHT_STADIUM_BATTLE:
        case FIGHT_STADIUM_END:
            closeMessage();
            break;
        case FIGHT_STADIUM_CHOICE:
        case FIGHT_STADIUM_BET:
            if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                gTownMenu_MESSAGE.setMessageLastCursor(false);
            }
            return false;
        case FIGHT_STADIUM_CHECK:
            if (stat == MENUBASE_STAT_OK) {
                setMenuStatus(FIGHT_STADIUM_BET);
                messageCount_++;
                gTownMenu_MESSAGE.close();
                showMessage(0xc8ee6);
                gTownMenu_MESSAGE.addMessageWAITKEY();
                gTownMenu_MESSAGE.setMessageLastCursor(true);
                menuItem_.active_ = 1;
            }
            else if (stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                setMenuStatus(FIGHT_STADIUM_START);
                messageCount_ = 0;
                redraw_ = 1;
                return true;
            }
            break;
        case FIGHT_STADIUM_RESULT:
            if (messageCount_ == 1) {
                if (stat == MENUBASE_STAT_OK) {
                    g_StadiumData.doubleUp_ = 1;
                    setMenuStatus(FIGHT_STADIUM_START);
                    messageCount_++;
                }
                else if (stat == MENUBASE_STAT_CANCEL) {
                    g_StadiumData.doubleUp_ = 0;
                    setMenuStatus(FIGHT_STADIUM_RETRY);
                    return true;
                }
            }
            else {
                closeMessage();
            }
            break;
        case FIGHT_STADIUM_RETRY:
            if (messageCount_ != 0) {
                if (g_StadiumData.betCoin_ != 0) {
                    if ((dss::g_Pad.edge() & 1) || (dss::g_Pad.edge() & 0x400)) {
                        SoundManager::playSe(0x154, 0);
                        haveCoin_ += g_StadiumData.betCoin_;
                        g_StadiumData.betCoin_ = 0;
                    }
                    else {
                        SoundManager::playSe(0x154, 0);
                        haveCoin_++;
                        g_StadiumData.betCoin_--;
                    }
                    if (haveCoin_ > 9999999) {
                        haveCoin_ = 9999999;
                    }
                    status::g_Party.setCasinoCoin(haveCoin_);
                    redraw_ = 1;
                }
                else {
                    gTownMenu_MESSAGE.clearMessageWAITPROG();
                    closeMessage();
                    redraw_ = 1;
                }
            }
            else if (stat == MENUBASE_STAT_OK) {
                gTownMenu_MESSAGE.close();
                setMenuStatus(FIGHT_STADIUM_START);
                messageCount_++;
            }
            else if (stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                showMessage(0xc8f0e);
                setMenuStatus(FIGHT_STADIUM_END);
                return true;
            }
            break;
    }
    return true;
}

THUMB void MaterielMenu_FIGHT_STADIUM::statusUpdate()
{
    switch (status_) {
        case FIGHT_STADIUM_START:
            if (messageCount_ == -1) {
                FightStadiumManager::getSingleton().setup();
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(0xc8eda);
                gTownMenu_MESSAGE.addMessage(0xc8edb);
                messageCount_++;
                g_StadiumData.setBetArray(0);
                g_StadiumData.betCoin_ = 0;
                result_ = RESULT_NONE;
            }
            else {
                g_StadiumData.cleanUp();
                showMessage(0xc8edd);
                gTownMenu_MESSAGE.addMessageWAITKEY();
                monsterItem_.active_ = 0;
                monsterItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_INACTIVE);
                setMenuStatus(FIGHT_STADIUM_CHOICE);
            }
            break;
        case FIGHT_STADIUM_CHOICE:
            monsterListUpdate();
            break;
        case FIGHT_STADIUM_CHECK:
            break;
        case FIGHT_STADIUM_BET:
            coinUpdate();
            break;
        case FIGHT_STADIUM_BATTLE:
            battleStart();
            break;
        case FIGHT_STADIUM_RESULT:
            resultUpdate();
            break;
        case FIGHT_STADIUM_RETRY:
            if (status::g_Party.getCasinoCoin() == 9999999) {
                showMessage(0xc8ef0);
            }
            else {
                showMessage(0xc8ef3);
            }
            gTownMenu_MESSAGE.setYesNo();
            messageCount_++;
            break;
        case FIGHT_STADIUM_END: {
            status::g_Menu.bookingFlag_ = 0;
            close();
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            dss::Fix32Vector3 pos;
            static float x = -3.0f;
            static float z = 4.35f;
            static float y = 0.375f;
            pos.vx = dss::Fix32(x);
            pos.vy = dss::Fix32(y);
            pos.vz = dss::Fix32(z);
            status::g_StageInfo.setOverviewPosition(pos);
            break;
        }
    }
}

THUMB void MaterielMenu_FIGHT_STADIUM::monsterListUpdate()
{
    if (!gTownMenu_MESSAGE.isOpen()) {
        return;
    }
    int prev = waitProg_;
    waitProg_ = gTownMenu_MESSAGE.isMessageWAITPROG();
    if (waitProg_ == 0) {
        return;
    }
    if (prev == 0 && waitProg_ != 0) {
        int active = monsterItem_.active_;
        monsterItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
        monsterItem_.active_ = active;
        unk_104 = 1;
        redraw_ = 1;
    }
    monsterItem_.execInput();
    switch (monsterItem_.result_) {
        case menu::MenuItem::MENUITEM_RESULT_CANCEL:
        case menu::MenuItem::MENUITEM_RESULT_SUPERCANCEL:
            gTownMenu_MESSAGE.close();
            monsterItem_.resetResult();
            unk_104 = 0;
            if (g_StadiumData.doubleUp_) {
                showMessage(0xc8f13);
                gTownMenu_MESSAGE.addMessageWAITKEY();
            }
            else {
                showMessage(0xc8f0e);
                setMenuStatus(FIGHT_STADIUM_END);
            }
            redraw_ = 1;
            break;
        case menu::MenuItem::MENUITEM_RESULT_OK: {
            monsterItem_.resetResult();
            g_StadiumData.setBetArray(monsterItem_.active_);
            g_StadiumData.setBetID(FightStadiumManager::getSingleton().getMonsterID(g_StadiumData.getBetArray()));
            g_StadiumData.setBetNumber(FightStadiumManager::getSingleton().getOrderCount(g_StadiumData.getBetArray()));
            monsterItem_.active_ = -1;
            setMenuStatus(FIGHT_STADIUM_CHECK);
            if (g_StadiumData.doubleUp_) {
                FightStadiumManager::getSingleton().setBetOnMacro();
                TextAPI::setMACRO0(0x47, 0xf0000000, g_StadiumData.betCoin_);
                showMessage(0xc8ee9);
                setMenuStatus(FIGHT_STADIUM_BATTLE);
                return;
            }
            if (status::g_Party.getCasinoCoin() == 0) {
                showMessage(0xc8ee0);
                setMenuStatus(FIGHT_STADIUM_END);
            }
            else {
                FightStadiumManager::getSingleton().setBetOnMacro();
                showMessage(0xc8ee3);
                gTownMenu_MESSAGE.setYesNo();
                messageCount_++;
            }
            redraw_ = 1;
            break;
        }
        case menu::MenuItem::MENUITEM_RESULT_UP: {
            int count = FightStadiumManager::getSingleton().getMonsterCount();
            monsterItem_.resetResult();
            monsterItem_.active_ = count - 1;
            break;
        }
        case menu::MenuItem::MENUITEM_RESULT_DOWN:
            monsterItem_.resetResult();
            monsterItem_.active_ = 0;
            break;
    }
}

THUMB void MaterielMenu_FIGHT_STADIUM::coinUpdate()
{
    int coin = g_StadiumData.betCoin_;
    int difCoin = coin;
    if (!gTownMenu_MESSAGE.isOpen()) {
        return;
    }
    int prev = waitProg_;
    waitProg_ = gTownMenu_MESSAGE.isMessageWAITPROG();
    if (waitProg_ == 0) {
        return;
    }
    if (prev == 0 && waitProg_ != 0) {
        blink_ = 1;
        m_bDispCoin = 1;
        redraw_ = 1;
    }
    menuItem_.execInput();
    int result = menuItem_.result_;
    if (result != 0) {
        blink_ = 0;
    }
    switch (result) {
        case menu::MenuItem::MENUITEM_RESULT_CANCEL:
        case menu::MenuItem::MENUITEM_RESULT_SUPERCANCEL:
            g_StadiumData.betCoin_ = 0;
            haveCoin_ = status::g_Party.getCasinoCoin();
            gTownMenu_MESSAGE.close();
            menuItem_.resetResult();
            setMenuStatus(FIGHT_STADIUM_START);
            messageCount_ = 0;
            m_bDispCoin = 0;
            unk_104 = 0;
            redraw_ = 1;
            return;
        case menu::MenuItem::MENUITEM_RESULT_OK:
            menuItem_.resetResult();
            menuItem_.active_ = 1;
            setMenuStatus(FIGHT_STADIUM_BET);
            if (g_StadiumData.betCoin_ == 0) {
                gTownMenu_MESSAGE.close();
                menuItem_.resetResult();
                setMenuStatus(FIGHT_STADIUM_START);
                messageCount_ = 0;
                m_bDispCoin = 0;
                unk_104 = 0;
                redraw_ = 1;
            }
            else {
                FightStadiumManager::getSingleton().setBetOnMacro();
                TextAPI::setMACRO0(0x47, 0xf0000000, g_StadiumData.betCoin_);
                showMessage(0xc8ee9);
                setMenuStatus(FIGHT_STADIUM_BATTLE);
                unk_104 = 0;
                m_bDispCoin = 0;
                status::g_Party.setCasinoCoin(haveCoin_);
            }
            redraw_ = 1;
            return;
        case menu::MenuItem::MENUITEM_RESULT_RIGHT:
            menuItem_.resetResult();
            menuItem_.active_ = 1;
            redraw_ = 1;
            break;
        case menu::MenuItem::MENUITEM_RESULT_LEFT:
            menuItem_.resetResult();
            menuItem_.active_ = 0;
            redraw_ = 1;
            break;
        case menu::MenuItem::MENUITEM_RESULT_UP:
            menuItem_.resetResult();
            if (menuItem_.active_ != 0) {
                difCoin++;
                if (difCoin > 50) {
                    difCoin = 0;
                }
            }
            else if (coin == 50) {
                difCoin = 0;
            }
            else {
                difCoin += 10;
                if (difCoin > 50) {
                    difCoin = 50;
                }
            }
            redraw_ = 1;
            break;
        case menu::MenuItem::MENUITEM_RESULT_DOWN:
            menuItem_.resetResult();
            if (menuItem_.active_ != 0) {
                if (--difCoin < 0) {
                    difCoin = 50;
                }
            }
            else if (coin == 0) {
                difCoin = 50;
            }
            else {
                if ((difCoin -= 10) < 0) {
                    difCoin = 0;
                }
            }
            redraw_ = 1;
            break;
    }
    g_StadiumData.betCoin_ = (unsigned char)difCoin;
    if (g_StadiumData.betCoin_ > 50) {
        g_StadiumData.betCoin_ = 50;
    }
    if (g_StadiumData.betCoin_ > status::g_Party.getCasinoCoin()) {
        g_StadiumData.betCoin_ = (unsigned char)status::g_Party.getCasinoCoin();
    }
    haveCoin_ += coin - g_StadiumData.betCoin_;
}

THUMB void MaterielMenu_FIGHT_STADIUM::resultUpdate()
{
    FightStadiumManager::getSingleton().setup();
    g_StadiumData.doubleUp_ = 0;
    if (result_ == RESULT_WIN) {
        gTownMenu_MESSAGE.openMessageForTALK();
        if (messageCount_ == -1) {
            TextAPI::setMACRO0(0x48, 0xf0000000, g_StadiumData.betCoin_);
            gTownMenu_MESSAGE.addMessage(0xc8eed);
            playFanfare();
            messageCount_++;
            return;
        }
        if (g_StadiumData.betCoin_ > 10000) {
            setMenuStatus(FIGHT_STADIUM_RETRY);
            gTownMenu_MESSAGE.addMessage(0xc8f15);
            return;
        }
        messageCount_++;
        gTownMenu_MESSAGE.addMessage(0xc8f17);
        gTownMenu_MESSAGE.setYesNo();
    }
    else if (result_ == RESULT_LOSE) {
        showMessage(0xc8ef7);
        setMenuStatus(FIGHT_STADIUM_RETRY);
    }
    else if (result_ == RESULT_DRAW) {
        haveCoin_ += g_StadiumData.betCoin_;
        if (haveCoin_ > 9999999) {
            haveCoin_ = 9999999;
        }
        status::g_Party.setCasinoCoin(haveCoin_);
        g_StadiumData.betCoin_ = 0;
        setMenuStatus(FIGHT_STADIUM_RETRY);
    }
    else if (result_ == RESULT_RETIRE) {
        showMessage(0xc8f05);
        setMenuStatus(FIGHT_STADIUM_END);
    }
}

THUMB void MaterielMenu_FIGHT_STADIUM::battleStart()
{
    g_StadiumData.odds_ = FightStadiumManager::getSingleton().getDiameter(g_StadiumData.monsterArray_);
    FightStadiumManager::getSingleton().battleStart();
    status::g_Menu.bookingFlag_ = menu::BOOKING_STADIUM;
    close();
    MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
}

THUMB void MaterielMenu_FIGHT_STADIUM::playBackMenu(int result)
{
    setMenuStatus(FIGHT_STADIUM_RESULT);
    result_ = result;
    if (result_ == RESULT_WIN) {
        unsigned int coin = g_StadiumData.odds_ * g_StadiumData.betCoin_;
        if (coin % 10 > 4) {
            coin += 10;
        }
        g_StadiumData.betCoin_ = coin / 10;
    }
    else if (result_ == RESULT_LOSE) {
        g_StadiumData.betCoin_ = 0;
    }
}

THUMB void MaterielMenu_FIGHT_STADIUM::playFanfare()
{
    int coin = g_StadiumData.betCoin_;
    if (coin >= 5000) {
        cmn::g_cmnSoundManager.setPlaySound(10, false);
    }
    else if (coin >= 500) {
        cmn::g_cmnSoundManager.setPlaySound(9, false);
    }
    else {
        cmn::g_cmnSoundManager.setPlaySound(8, false);
    }
}

THUMB void MaterielMenu_FIGHT_STADIUM::showMessage(int mes)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(mes);
}

THUMB void MaterielMenu_FIGHT_STADIUM::closeMessage()
{
    int stat = gTownMenu_MESSAGE.stat_;
    if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
        gTownMenu_MESSAGE.close();
    }
}
