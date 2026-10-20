#pragma ipa file
#include "main/part/MPExchangePart.hpp"
#include "main/cmn/PlayerManager.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/UnkOverlaySlot.hpp"
#include "main/dss/UnkSleep.hpp"
#include "main/dss/UnkTextConvert.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/global/Global.hpp"
#include "main/global/StageLink.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/sound/Sound.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "nitro/pad.h"
#include "nitro/pm.hpp"

MPExchangePart g_MPExchangePart;

THUMB MPExchangePart::MPExchangePart()
{
}

THUMB void MPExchangePart::initialize()
{
    loadOverlay((int)&OVERLAY_6_ID);
    ov006_entry();
    data_020f4f74.initVramManagers(0x40000, 0x4000);
    changeDisplayPlugin(&dss::g_DISPLAYPLUGIN_SINGLE3D);
    lcdCounter_ = 0;
    g_Global.fadeIn(30);
    switch (data_0211b27c.state_) {
        case FadeEffector::FADE_NONE:
            data_0211b27c.state_ = FadeEffector::FADE_OUT_BLACK;
            break;
        case FadeEffector::FADE_IN_BLACK:
            data_0211b27c.state_ = FadeEffector::FADE_OUT_WHITE;
            break;
        default:
            data_0211b27c.state_ = FadeEffector::FADE_OUT_BLACK;
            break;
    }
    data_0211b27c.count_ = 0;
    data_0211b27c.frames_ = 30;
    data_02101d14.unkfunc_020519a8(&data_0211b27c);
    setSleepEnabled(0);
    setState(0);
}

THUMB void MPExchangePart::terminate()
{
    setSleepEnabled(1);
    data_020f4f74.onPartTerminate();
    unloadOverlay((int)&OVERLAY_6_ID);
}

THUMB void MPExchangePart::onExecutePart()
{
    status::TAISHI_DATA* data;
    switch (state_) {
        case 0:
            if (counter_ > 30) {
                setState(1);
            }
            break;
        case 1:
            if (counter_ == 0) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(0xcc605);
                gTownMenu_MESSAGE.suspendInput_ = 1;
                message_ = 0;
            }
            if (counter_ > 120) {
                setState(4);
            }
            break;
        case 4: {
            exchange_.unkfunc_0212a310();
            status::TaishiBase taishi = status::g_MuseumStatus.playerTaishi_;
            data = (status::TAISHI_DATA*)&taishi;
            convertUtf8ToSjisWork(data->taishiName_);
            convertUtf8ToSjisWork(data->producer_);
            convertUtf8ToSjisWork(data->message_);
            exchange_.unkfunc_0212a2b8(data);
            setState(2);
            break;
        }
        case 2:
            if (exchange_.mode_ == SYSMODE_FATAL_ERROR) {
                setState(8);
            } else if (exchange_.mode_ == SYSMODE_READY) {
                exchange_.startRoleSelection();
                setState(3);
            }
            break;
        case 3:
            if (message_ == 0) {
                if (counter_ == 0) {
                    gTownMenu_MESSAGE.openMessageForTALK();
                    gTownMenu_MESSAGE.addMessage(0xcc607);
                    message_ = 1;
                }
                if (counter_ == 30) {
                    setState(5);
                }
            } else {
                setState(5);
            }
            break;
        case 5:
            updateLcdPower();
            playWaitSe();
            if (exchange_.mode_ == SYSMODE_FATAL_ERROR) {
                setState(6);
            } else if (exchange_.mode_ == SYSMODE_LIGHT_ERROR) {
                setState(7);
            } else if (exchange_.mode_ == SYSMODE_FINISH_WAIT) {
                setState(9);
            } else if (PAD_DetectFold() == FALSE && (dss::g_Pad.edge() & PAD_BUTTON_A)) {
                setState(10);
            }
            break;
        case 6:
            if (counter_ == 0) {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xcc620);
                message_ = 0;
                exchange_.unkfunc_0212acdc();
            }
            if (counter_ > 60 && gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_OK) {
                setState(13);
            }
            break;
        case 7:
            setState(4);
            break;
        case 8:
            restoreLcdAndSleep();
            if (counter_ == 0) {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xcc620);
                message_ = 0;
                exchange_.unkfunc_0212acdc();
            }
            if (counter_ > 60 && gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_OK) {
                setState(13);
            }
            break;
        case 9: {
            data = exchange_.unkfunc_0212a2fc();
            if (exchange_.receiveCount_ <= 4) {
                setState(7);
                break;
            }
            if (PAD_DetectFold() == FALSE) {
                Sound::sePlay(0x146);
            }
            if (status::g_MuseumStatus.findExistTaishi(data->uniqueId_) == -1) {
                known_ = FALSE;
            } else {
                known_ = TRUE;
            }
            status::g_MuseumStatus.setSuccessTaishi(data, true);
            convertUtf8ToSjisWork(data->taishiName_);
            convertUtf8ToSjisWork(data->producer_);
            convertUtf8ToSjisWork(data->message_);
            setState(12);
            break;
        }
        case 10:
            status::g_MuseumStatus.setSuccessTaishi(NULL, false);
            setState(11);
            break;
        case 11:
            restoreLcdAndSleep();
            if (counter_ == 0) {
                gTownMenu_MESSAGE.close();
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(0xcc60a);
                gTownMenu_MESSAGE.setYesNo(1);
                message_ = 0;
                exchange_.cancelRequest_ = 1;
            }
            if (counter_ > 60) {
                if (gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_CANCEL) {
                    gTownMenu_MESSAGE.close();
                    setState(13);
                }
                if (gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_OK) {
                    gTownMenu_MESSAGE.close();
                    setSleepEnabled(0);
                    setState(4);
                }
            }
            break;
        case 12:
            restoreLcdAndSleep();
            if (counter_ == 0) {
                int message;
                if (known_ != 0) {
                    message = 0xcc616;
                } else if (status::g_MuseumStatus.getTaishiCount() == 1) {
                    message = 0xcc613;
                } else {
                    message = 0xcc617;
                }
                gTownMenu_MESSAGE.close();
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(message);
                message_ = 0;
            }
            if (counter_ > 60 && gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_OK) {
                setState(13);
            }
            break;
        case 13:
            restoreLcdAndSleep();
            if (counter_ == 0) {
                gTownMenu_MESSAGE.close();
                exchange_.cancelRequest_ = 1;
                g_Global.fadeOutBlack(30, true);
            }
            if (counter_ > 30 && exchange_.mode_ == SYSMODE_FINISH_WAIT) {
                cmn::PlayerManager::setLock(true);
                util::StageLink::resetTownExitIndex();
                g_Global.startTown("xdb1b");
                status::g_StageInfo.flagMapChange_ = 1;
                status::g_MuseumStatus.updateMuseum();
                setState(14);
            }
            break;
    }
    exchange_.unkfunc_0212a424();
    updateState();
}

THUMB void MPExchangePart::onDebugPart()
{
    exchange_.updateDataSharing();
}

THUMB void MPExchangePart::setState(int state)
{
    nextState_ = state;
}

/* not original: without it nextState_ is loaded before state_ */
#pragma push
#pragma opt_common_subs off
THUMB void MPExchangePart::updateState()
{
    if (state_ != nextState_) {
        state_ = nextState_;
        counter_ = 0;
    } else {
        counter_++;
    }
}
#pragma pop

THUMB void MPExchangePart::updateLcdPower()
{
    if (PAD_DetectFold()) {
        if (func_020791f4() == TRUE) {
            func_020791e0(FALSE);
            lcdCounter_ = 0;
        }
    }
    if (PAD_DetectFold() == FALSE && lcdCounter_ > 10 && func_020791f4() == FALSE) {
        func_020791e0(TRUE);
        lcdCounter_ = 0;
    }
    lcdCounter_++;
}

THUMB void MPExchangePart::playWaitSe()
{
    if (counter_ % 60 == 0) {
        Sound::sePlay(0x12f);
    }
}

THUMB void MPExchangePart::restoreLcdAndSleep()
{
    if (func_020791f4() == FALSE) {
        func_020791e0(TRUE);
    }
    setSleepEnabled(1);
}

THUMB void MPExchangePart::onWindowPart()
{
}

THUMB void MPExchangePart::onDrawPart()
{
}
