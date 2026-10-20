#pragma ipa file
#include "ov006/mp/MPExchange.hpp"
#include "main/debug/UnkDebugPrint.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "main/text/TextAPI.hpp"

ARM void MPExchange::updateFinishReady()
{
    if (getWhSysState() == WH_SYSSTATE_IDLE) {
        endWh();
        setMode(SYSMODE_FINISH_WAIT);
    }
}

ARM void MPExchange::updateSelectRole()
{
    if (getWhSysState() != WH_SYSSTATE_IDLE) {
        return;
    }
    if (unk_1c != 0) {
        setMode(SYSMODE_FINISH_READY);
        return;
    }
    int role = role_.getNextRole();
    if (role == 2) {
        unk_f8 = 0;
        startParent(0, 90);
    }
    if (role == 1) {
        unk_f8 = 1;
        unk_40 = 1;
        startScan(1);
    }
}

ARM void MPExchange::unkfunc_02129a30()
{
    updateGameInfo(1);
    debugConsolePrintfIfEnabled(2, 1, "BEACON CNT %d", unkfunc_021229f0());
    role_.printTable();
    if (unkfunc_021229f0() > 1 && unk_1c != 0) {
        finish();
        return;
    }
    if (unkfunc_021229f0() > 60) {
        SEND_PACKET->state_ = 0;
        finalizeWh();
        setMode(SYSMODE_SELECT_NEXT);
        return;
    }
    int count = 0;
    u16 bitmap = getWhConnectBitmap();
    for (int i = 0; i < 16; i++) {
        if (bitmap & (1 << i)) {
            count++;
        }
    }
    if (count == 2) {
        SEND_PACKET->state_ = 0;
        for (int i = 0; i < 2; i++) {
            UnkMPExchangePacket* packet = RECV_PACKET(i);
            packet->state_ = 0;
        }
        updateGameInfo(0);
        setMode(SYSMODE_PARENT_EXEC);
    }
    if (role_.isTimedOut()) {
        SEND_PACKET->state_ = 0;
        finalizeWh();
        setMode(SYSMODE_SELECT_NEXT);
    }
}

ARM void MPExchange::unkfunc_02129b64()
{
    if (counter_ > 60) {
        setMode(SYSMODE_LIGHT_ERRORINIT);
    }
    if (unk_1c != 0) {
        finish();
        return;
    }
    if (RECV_PACKET(0)->state_ == 1) {
        SEND_PACKET->state_ = 0;
        for (int i = 0; i < 2; i++) {
            UnkMPExchangePacket* packet = RECV_PACKET(i);
            packet->state_ = 0;
        }
        setMode(SYSMODE_CHILD_EXEC);
    }
}

ARM void MPExchange::updateChildScan()
{
    char buf[0x20];
    debugConsolePrintfIfEnabled(2, 1, "CHANNEL %d", unk_40);
    role_.printTable();
    if (unk_1c != 0) {
        if (getWhSysState() == WH_SYSSTATE_SCANNING) {
            endWhScan();
        }
        finish();
        return;
    }
    if (parentCount_ > 0) {
        dss::sprintf_s(buf, sizeof(buf), "%2d %08x", 0, bssDesc_[0].gameInfo.ggid);
        debugConsolePrint(1, 2, buf);
        if (getWhSysState() == WH_SYSSTATE_SCANNING) {
            endWhScan();
        }
        setMode(SYSMODE_CHILD_CONNECT);
        return;
    }
    if (role_.isTimedOut()) {
        if (getWhSysState() == WH_SYSSTATE_SCANNING) {
            endWhScan();
        }
        setMode(SYSMODE_SELECT_SCAN);
    }
}

ARM void MPExchange::updateSelectScan()
{
    debugConsolePrintfIfEnabled(2, 1, "CHANNEL %d", unk_40);
    role_.printTable();
    if (getWhSysState() != WH_SYSSTATE_IDLE) {
        return;
    }
    if (unk_1c != 0) {
        finish();
        return;
    }
    role_.restartTimer();
    switch (unk_40) {
    case 1:
        unk_40 = 7;
        startScan(7);
        break;
    case 7:
        unk_40 = 13;
        startScan(13);
        break;
    case 13:
        finalizeWh();
        setMode(SYSMODE_SELECT_NEXT);
        break;
    }
}

ARM void MPExchange::updateChildConnect()
{
    if (getWhSysState() == WH_SYSSTATE_IDLE) {
        connectWhChild(5, &bssDesc_[0]);
        setMode(SYSMODE_CHILD_READY);
    }
}

ARM void MPExchange::unkfunc_02129dd0()
{
    unkfunc_0212a1b4();
    dss::memcpy(&SEND_PACKET->data_, sendData_, 0xdc);
    if (getWhConnectBitmap() == 1) {
        finish();
        return;
    }
    if (unk_3c == 4) {
        finish();
        return;
    }
    if (unk_3c == 6) {
        finish();
        return;
    }
    if (unk_1c != 0) {
        finish();
        return;
    }
    if (RECV_PACKET(0)->state_ == 2) {
        finish();
        return;
    }
    for (int i = 0; i < 2; i++) {
        if (RECV_PACKET(i)->state_ == 2) {
            SEND_PACKET->state_ = 2;
            return;
        }
    }
    if (unk_fc == 4) {
        SEND_PACKET->state_ = 2;
        return;
    }
}

ARM void MPExchange::unkfunc_02129ec4()
{
    unkfunc_0212a1b4();
    dss::memcpy(&SEND_PACKET->data_, sendData_, 0xdc);
    if (unk_3c == 5) {
        finish();
        return;
    }
    if (unk_3c == 6) {
        if (unk_fc == 1) {
            finish();
        }
        return;
    }
    if (unk_1c != 0) {
        finish();
        return;
    }
    if (RECV_PACKET(0)->state_ == 2) {
        finish();
    }
}

ARM void MPExchange::updateSelectNext()
{
    role_.printTable();
    if (getWhSysState() == WH_SYSSTATE_IDLE) {
        setMode(SYSMODE_SELECT_ROLE);
    }
}

ARM void MPExchange::unkfunc_02129f84()
{
    if (getWhSysState() == WH_SYSSTATE_DATASHARING) {
        if (unkfunc_021227ec(sendBuffer_)) {
            int i;
            for (i = 0; i < 2; i++) {
                void* data = getWhSharedData(i);
                UnkMPExchangePacket* packet = RECV_PACKET(i);
                if (data != NULL) {
                    MI_CpuCopyU8(data, packet, 0xdc);
                    connected_[i] = 1;
                    if (unk_f8 == 0) {
                        if (i == 1) {
                            dss::memcpy(receiveData_, &packet->data_, 0xdc);
                            unk_fc++;
                            unkfunc_0204afa8(((status::TAISHI_DATA*)receiveData_)->taishiName_);
                            unkfunc_0204afa8(((status::TAISHI_DATA*)receiveData_)->message_);
                        }
                    } else if (i == 0) {
                        dss::memcpy(receiveData_, &packet->data_, 0xdc);
                        unk_fc++;
                        unkfunc_0204afa8(((status::TAISHI_DATA*)receiveData_)->taishiName_);
                        unkfunc_0204afa8(((status::TAISHI_DATA*)receiveData_)->message_);
                    }
                } else {
                    packet->linkLevel_ = 0;
                    connected_[i] = 0;
                }
            }
            for (; i < 16; i++) {
                connected_[i] = 0;
            }
            unk_34 = 0;
        } else {
            for (int i = 0; i < 16; i++) {
                connected_[i] = 0;
            }
            unk_34 = 1;
        }
    } else {
        for (int i = 0; i < 16; i++) {
            connected_[i] = 0;
        }
        unk_34 = 0;
    }
}

ARM void MPExchange::unkfunc_0212a10c()
{
    if (unk_34 != 0) {
        return;
    }
    UnkMPExchangePacket* packet = SEND_PACKET;
    if (packet->state_ != 2) {
        packet->state_ = mode_ == SYSMODE_PARENT_LOBBY ? 0 : 1;
    }
    packet->linkLevel_ = (u16)func_0207a2e4();
    packet->pad_ = dss::g_Pad.pad();
    packet->frame_ = (u16)frame_;
    if (unk_0212e0c4 != 0) {
        if (unk_0212e0c4 > 0) {
            unk_0212e0c4 = -unk_0212e0c4 + 1;
        } else {
            unk_0212e0c4 = -unk_0212e0c4 - 1;
        }
    }
    frame_++;
}
