#include "ov034/materielmenu/casino/MaterielMenu_RaceResult.hpp"
#include "ov034/materielmenu/casino/MaterielMenu_ChoiceSlime.hpp"
#include "ov034/materielmenu/casino/MaterielMenu_RaceEntrance.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/RaceData.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline unsigned int status::BasePartyStatus::getCasinoCoin()
{
    return casinoCoin_;
}

inline unsigned int status::BasePartyStatus::getGold()
{
    return gold_;
}

inline void status::MenuStatus::clearBooking()
{
    bookingFlag_ = 0;
}

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

inline unsigned char RaceData::getPaddock()
{
    return slimeNum_;
}

inline bool RaceData::isLookOnly()
{
    return look_;
}

inline unsigned int RaceData::getBetCoin()
{
    return betCoin_;
}

inline unsigned char RaceData::getResult()
{
    return result_;
}

inline unsigned short RaceData::getOdds()
{
    return odds_;
}

inline bool RaceData::isSlimeWin()
{
    return slimeResult_ == 1 || slimeResult_ == 2;
}

inline int RaceData::getSlimeNumber()
{
    return monsterNumber_;
}

THUMB void MaterielMenu_RaceResult::menuSetup()
{
    mode_ = MODE_RESULT;
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    yesno_ = 0;
    slime_ = 0;
    coin_ = 0;
    gold_ = 0;
    status::g_Menu.clearBooking();
    ui_MsgSndSet(0x32);
}

THUMB void MaterielMenu_RaceResult::menuExecute()
{
}

THUMB void MaterielMenu_RaceResult::menuDraw()
{
    unkfunc_0217c0e8(status::g_Party.getCasinoCoin(), status::g_Party.getGold());
}

THUMB void MaterielMenu_RaceResult::menuUpdate()
{
    if (fadeEffector.isEnd()) {
        if (cmn::g_cmnSoundManager.isPlaySound()) {
            cmn::g_cmnSoundManager.execSound();
        } else if (messageUpdate()) {
            commandUpdate();
        }
    }
}

THUMB bool MaterielMenu_RaceResult::messageUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int openFlag = gTownMenu_MESSAGE.isOpen();
    int stat = gTownMenu_MESSAGE.stat_;
    if (openFlag && !gTownMenu_MESSAGE.isMessageWAITPROG() && !yesno_) {
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
        }
        return false;
    }
    int index = g_RaceData.getSlimeNumber();
    TextAPI::setMACRO0(0x12, 0x50000000, index);
    TextAPI::setMACRO0(0x48, 0xf0000000, coin_);
    TextAPI::setMACRO0(0x6e, 0xf0000000, gold_);
    TextAPI::setMACRO0(0x6d, 0xf0000000, ranking_);
    TextAPI::setMACRO0(0x6f, 0xf0000000, ranking_);
    switch (mode_) {
        case MODE_FANFARE:
            return true;
        case MODE_RESULT:
            return true;
        case MODE_BET_HIT:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xc9a9f);
            yesno_ = 1;
            mode_ = MODE_FANFARE;
            break;
        case MODE_LOSE:
            setMessage(0xc9aac, -1);
            return true;
        case MODE_SLIME_WIN:
            gTownMenu_MESSAGE.openMessageForTALK();
            if (g_RaceData.isLookOnly()) {
                gTownMenu_MESSAGE.addMessage(0xc9adb);
            } else if (g_RaceData.getResult() == 1) {
                gTownMenu_MESSAGE.addMessage(0xc9aa2);
            } else if (g_RaceData.getResult() == 0) {
                gTownMenu_MESSAGE.addMessage(0xc9aaf);
            }
            yesno_ = 1;
            mode_ = MODE_TAKE_GOLD;
            break;
        case MODE_SLIME_LOSE:
            gTownMenu_MESSAGE.openMessageForTALK();
            if (g_RaceData.isLookOnly()) {
                gTownMenu_MESSAGE.addMessage(0xc9adf);
            } else if (g_RaceData.getResult() == 1) {
                gTownMenu_MESSAGE.addMessage(0xc9aa6);
            } else if (g_RaceData.getResult() == 0) {
                gTownMenu_MESSAGE.addMessage(0xc9ab2);
            }
            yesno_ = 1;
            mode_ = MODE_PAYOUT;
            break;
        case MODE_TAKE_GOLD:
        case MODE_PAYOUT:
        case MODE_TAKE_COIN:
            return true;
        case MODE_IS_NEXT:
            if (!openFlag) {
                setYesNoMessage(0xc9aa9, -1);
                break;
            }
            if (stat == MENUBASE_STAT_OK) {
                gTownMenu_MESSAGE.close();
                yesno_ = 0;
                return true;
            }
            if (stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                yesno_ = 0;
                if (slime_) {
                    close();
                    gMaterielMenu_ChoiceSlime.open();
                    gMaterielMenu_ChoiceSlime.mode_ = MaterielMenu_ChoiceSlime::MODE_LOOK_ONLY;
                } else {
                    mode_ = MODE_CANCEL;
                }
            }
            break;
        case MODE_IS_NEXTSLIME:
            if (!openFlag) {
                setYesNoMessage(0xc9aa3, -1);
                break;
            }
            if (stat == MENUBASE_STAT_OK) {
                gTownMenu_MESSAGE.close();
                yesno_ = 0;
                return true;
            }
            if (stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                yesno_ = 0;
                if (status::g_Party.getCasinoCoin() == 0) {
                    mode_ = MODE_CANCEL;
                } else {
                    mode_ = MODE_IS_NEXT;
                }
            }
            break;
        case MODE_IS_LOOK:
            if (!openFlag) {
                setYesNoMessage(0xc9adc, -1);
                break;
            }
            if (stat == MENUBASE_STAT_OK) {
                gTownMenu_MESSAGE.close();
                yesno_ = 0;
                return true;
            }
            if (stat == MENUBASE_STAT_CANCEL) {
                gTownMenu_MESSAGE.close();
                yesno_ = 0;
                mode_ = MODE_CANCEL;
            }
            break;
        case MODE_RACE:
            return true;
        case MODE_CANCEL:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(0xc9af1);
            mode_ = MODE_END;
            break;
        case MODE_END:
            return true;
    }
    return false;
}

THUMB void MaterielMenu_RaceResult::commandUpdate()
{
    switch (mode_) {
        case MODE_FANFARE:
            if (coin_ < 500) {
                cmn::g_cmnSoundManager.setPlaySound(8, false);
            } else if (coin_ < 5000) {
                cmn::g_cmnSoundManager.setPlaySound(9, false);
            } else {
                cmn::g_cmnSoundManager.setPlaySound(10, false);
            }
            mode_ = MODE_TAKE_COIN;
            break;
        case MODE_RESULT:
            checkResult();
            break;
        case MODE_LOSE:
        case MODE_BET_HIT:
            if (g_RaceData.getPaddock() == 5) {
                if (status::g_Party.getCasinoCoin() == 0) {
                    mode_ = MODE_CANCEL;
                } else {
                    mode_ = MODE_IS_NEXT;
                }
            } else {
                checkSlimeResult();
            }
            break;
        case MODE_TAKE_GOLD:
            if (gold_ > 0) {
                unsigned int playerGold = status::g_Party.getGold();
                execCoinAnim(playerGold, gold_, true);
                status::g_Party.setGold(playerGold);
                redraw_ = 1;
            } else {
                yesno_ = 0;
                if (g_RaceData.isLookOnly()) {
                    mode_ = MODE_IS_LOOK;
                } else {
                    mode_ = MODE_IS_NEXTSLIME;
                }
            }
            break;
        case MODE_TAKE_COIN:
            if (coin_ > 0) {
                unsigned int playerCoin = status::g_Party.getCasinoCoin();
                execCoinAnim(playerCoin, coin_, true);
                status::g_Party.setCasinoCoin(playerCoin);
                redraw_ = 1;
            } else {
                yesno_ = 0;
                if (g_RaceData.getPaddock() == 6) {
                    checkSlimeResult();
                } else {
                    mode_ = MODE_IS_NEXT;
                }
            }
            break;
        case MODE_PAYOUT:
            if (gold_ > 0) {
                unsigned int playerGold = status::g_Party.getGold();
                execCoinAnim(playerGold, gold_, false);
                status::g_Party.setGold(playerGold);
                redraw_ = 1;
            } else {
                yesno_ = 0;
                checkNext();
            }
            break;
        case MODE_IS_NEXT:
            close();
            if (slime_) {
                g_RaceData.setDoubleBetMode();
                gMaterielMenu_ChoiceSlime.open();
                gMaterielMenu_ChoiceSlime.mode_ = MaterielMenu_ChoiceSlime::MODE_IN_RACE;
            } else {
                g_RaceData.setBetMode();
                gMaterielMenu_RaceEntrance.open();
                gMaterielMenu_RaceEntrance.mode_ = MaterielMenu_RaceEntrance::MODE_IN_RACE;
            }
            break;
        case MODE_IS_NEXTSLIME:
            g_RaceData.setSlimeMode();
            if (status::g_Party.getCasinoCoin() == 0) {
                close();
                gMaterielMenu_ChoiceSlime.open();
                gMaterielMenu_ChoiceSlime.mode_ = MaterielMenu_ChoiceSlime::MODE_LOOK_ONLY;
            } else {
                slime_ = 1;
                mode_ = MODE_IS_NEXT;
            }
            break;
        case MODE_IS_LOOK:
            g_RaceData.setSlimeMode();
            gMaterielMenu_ChoiceSlime.open();
            close();
            gMaterielMenu_ChoiceSlime.mode_ = MaterielMenu_ChoiceSlime::MODE_IN_RACE;
            break;
        case MODE_END:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_RaceResult::checkResult()
{
    if (g_RaceData.isLookOnly()) {
        checkSlimeResult();
        return;
    }
    if (g_RaceData.getResult() == 1) {
        mode_ = MODE_BET_HIT;
        coin_ = g_RaceData.getBetCoin() * g_RaceData.getOdds() / 10;
        return;
    }
    mode_ = MODE_LOSE;
}

THUMB void MaterielMenu_RaceResult::checkSlimeResult()
{
    if (g_RaceData.isSlimeWin()) {
        mode_ = MODE_SLIME_WIN;
        gold_ = 400;
        ranking_ = 1;
        if (g_RaceData.slimeResult_ == 2) {
            gold_ = 150;
            ranking_ = 2;
        }
        return;
    }
    mode_ = MODE_SLIME_LOSE;
    gold_ = 50;
}

THUMB void MaterielMenu_RaceResult::checkNext()
{
    if (status::g_Party.getGold() >= 50) {
        mode_ = MODE_IS_NEXTSLIME;
    } else if (g_RaceData.isLookOnly() || status::g_Party.getCasinoCoin() == 0) {
        mode_ = MODE_CANCEL;
    } else {
        mode_ = MODE_IS_NEXT;
    }
}

THUMB void MaterielMenu_RaceResult::setMessage(int mes1, int mes2)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    if (mes2 == -1) {
        gTownMenu_MESSAGE.addMessage(mes1);
    } else {
        gTownMenu_MESSAGE.addMessage(mes1, mes2);
    }
}

THUMB void MaterielMenu_RaceResult::setYesNoMessage(int mes1, int mes2)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    if (mes2 == -1) {
        gTownMenu_MESSAGE.addMessage(mes1);
    } else {
        gTownMenu_MESSAGE.addMessage(mes1, mes2);
    }
    gTownMenu_MESSAGE.setYesNo();
    yesno_ = 1;
}

THUMB void MaterielMenu_RaceResult::execCoinAnim(unsigned int& coin, int& anim, bool plus)
{
    SoundManager::playSe(0x154, 0);
    if ((dss::g_Pad.edge() & 1) || (dss::g_Pad.edge() & 0x400)) {
        coin = plus ? coin + anim : coin - anim;
        anim = 0;
    } else {
        coin = plus ? coin + 1 : coin - 1;
        anim--;
    }
}
