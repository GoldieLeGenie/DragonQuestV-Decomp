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
    unkfunc_0204b5d4((int)&OVERLAY_6_ID);
    ov006_entry();
    data_020f4f74.unkfunc_0204a53c(0x40000, 0x4000);
    unkfunc_0204c9d8(&dss::g_DISPLAYPLUGIN_SINGLE3D);
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
    unkfunc_0204c08c(0);
    unkfunc_02043370(0);
}

THUMB void MPExchangePart::terminate()
{
    unkfunc_0204c08c(1);
    data_020f4f74.unkfunc_0204a5f0();
    unkfunc_0204b5e8((int)&OVERLAY_6_ID);
}

THUMB void MPExchangePart::onExecutePart()
{
    status::TAISHI_DATA* data;
    switch (state_) {
        case 0:
            if (counter_ > 30) {
                unkfunc_02043370(1);
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
                unkfunc_02043370(4);
            }
            break;
        case 4: {
            exchange_.unkfunc_0212a310();
            status::TaishiBase taishi = status::g_MuseumStatus.playerTaishi_;
            data = (status::TAISHI_DATA*)&taishi;
            unkfunc_0204afa8(data->taishiName_);
            unkfunc_0204afa8(data->producer_);
            unkfunc_0204afa8(data->message_);
            exchange_.unkfunc_0212a2b8(data);
            unkfunc_02043370(2);
            break;
        }
        case 2:
            if (exchange_.mode_ == SYSMODE_FATAL_ERROR) {
                unkfunc_02043370(8);
            } else if (exchange_.mode_ == SYSMODE_READY) {
                exchange_.startRoleSelection();
                unkfunc_02043370(3);
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
                    unkfunc_02043370(5);
                }
            } else {
                unkfunc_02043370(5);
            }
            break;
        case 5:
            unkfunc_0204338c();
            unkfunc_020433f4();
            if (exchange_.mode_ == SYSMODE_FATAL_ERROR) {
                unkfunc_02043370(6);
            } else if (exchange_.mode_ == SYSMODE_LIGHT_ERROR) {
                unkfunc_02043370(7);
            } else if (exchange_.mode_ == SYSMODE_FINISH_WAIT) {
                unkfunc_02043370(9);
            } else if (PAD_DetectFold() == FALSE && (dss::g_Pad.edge() & PAD_BUTTON_A)) {
                unkfunc_02043370(10);
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
                unkfunc_02043370(13);
            }
            break;
        case 7:
            unkfunc_02043370(4);
            break;
        case 8:
            unkfunc_02043410();
            if (counter_ == 0) {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xcc620);
                message_ = 0;
                exchange_.unkfunc_0212acdc();
            }
            if (counter_ > 60 && gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_OK) {
                unkfunc_02043370(13);
            }
            break;
        case 9: {
            data = exchange_.unkfunc_0212a2fc();
            if (exchange_.receiveCount_ <= 4) {
                unkfunc_02043370(7);
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
            unkfunc_0204afa8(data->taishiName_);
            unkfunc_0204afa8(data->producer_);
            unkfunc_0204afa8(data->message_);
            unkfunc_02043370(12);
            break;
        }
        case 10:
            status::g_MuseumStatus.setSuccessTaishi(NULL, false);
            unkfunc_02043370(11);
            break;
        case 11:
            unkfunc_02043410();
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
                    unkfunc_02043370(13);
                }
                if (gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_OK) {
                    gTownMenu_MESSAGE.close();
                    unkfunc_0204c08c(0);
                    unkfunc_02043370(4);
                }
            }
            break;
        case 12:
            unkfunc_02043410();
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
                unkfunc_02043370(13);
            }
            break;
        case 13:
            unkfunc_02043410();
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
                unkfunc_02043370(14);
            }
            break;
    }
    exchange_.unkfunc_0212a424();
    unkfunc_02043374();
}

THUMB void MPExchangePart::onDebugPart()
{
    exchange_.updateDataSharing();
}

THUMB void MPExchangePart::unkfunc_02043370(int state)
{
    nextState_ = state;
}

/* not original: without it nextState_ is loaded before state_ */
#pragma push
#pragma opt_common_subs off
THUMB void MPExchangePart::unkfunc_02043374()
{
    if (state_ != nextState_) {
        state_ = nextState_;
        counter_ = 0;
    } else {
        counter_++;
    }
}
#pragma pop

THUMB void MPExchangePart::unkfunc_0204338c()
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

THUMB void MPExchangePart::unkfunc_020433f4()
{
    if (counter_ % 60 == 0) {
        Sound::sePlay(0x12f);
    }
}

THUMB void MPExchangePart::unkfunc_02043410()
{
    if (func_020791f4() == FALSE) {
        func_020791e0(TRUE);
    }
    unkfunc_0204c08c(1);
}

THUMB void MPExchangePart::onWindowPart()
{
}

THUMB void MPExchangePart::onDrawPart()
{
}
