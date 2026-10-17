#pragma ipa file
#include "ov006/mp/UnkMPExchange.hpp"
#include "main/debug/UnkDebugPrint.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "main/text/TextAPI.hpp"

ARM void UnkMPExchange::unkfunc_02129990()
{
    if (unkfunc_02121f50() == WH_SYSSTATE_IDLE) {
        unkfunc_02122998();
        unkfunc_0212a750(SYSMODE_FINISH_WAIT);
    }
}

ARM void UnkMPExchange::unkfunc_021299b8()
{
    if (unkfunc_02121f50() != WH_SYSSTATE_IDLE) {
        return;
    }
    if (unk_1c != 0) {
        unkfunc_0212a750(SYSMODE_FINISH_READY);
        return;
    }
    int role = role_.unkfunc_0212ae1c();
    if (role == 2) {
        unk_f8 = 0;
        unkfunc_0212ac28(0, 90);
    }
    if (role == 1) {
        unk_f8 = 1;
        unk_40 = 1;
        unkfunc_0212ac8c(1);
    }
}

ARM void UnkMPExchange::unkfunc_02129a30()
{
    unkfunc_0212a954(1);
    unkfunc_020434c8(2, 1, "BEACON CNT %d", unkfunc_021229f0());
    role_.unkfunc_0212afec();
    if (unkfunc_021229f0() > 1 && unk_1c != 0) {
        unkfunc_0212acc0();
        return;
    }
    if (unkfunc_021229f0() > 60) {
        SEND_PACKET->state_ = 0;
        unkfunc_02122888();
        unkfunc_0212a750(SYSMODE_SELECT_NEXT);
        return;
    }
    int count = 0;
    u16 bitmap = unkfunc_02121f40();
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
        unkfunc_0212a954(0);
        unkfunc_0212a750(SYSMODE_PARENT_EXEC);
    }
    if (role_.unkfunc_0212b0f0()) {
        SEND_PACKET->state_ = 0;
        unkfunc_02122888();
        unkfunc_0212a750(SYSMODE_SELECT_NEXT);
    }
}

ARM void UnkMPExchange::unkfunc_02129b64()
{
    if (counter_ > 60) {
        unkfunc_0212a750(SYSMODE_LIGHT_ERRORINIT);
    }
    if (unk_1c != 0) {
        unkfunc_0212acc0();
        return;
    }
    if (RECV_PACKET(0)->state_ == 1) {
        SEND_PACKET->state_ = 0;
        for (int i = 0; i < 2; i++) {
            UnkMPExchangePacket* packet = RECV_PACKET(i);
            packet->state_ = 0;
        }
        unkfunc_0212a750(SYSMODE_CHILD_EXEC);
    }
}

ARM void UnkMPExchange::unkfunc_02129bec()
{
    char buf[0x20];
    unkfunc_020434c8(2, 1, "CHANNEL %d", unk_40);
    role_.unkfunc_0212afec();
    if (unk_1c != 0) {
        if (unkfunc_02121f50() == WH_SYSSTATE_SCANNING) {
            unkfunc_021218f4();
        }
        unkfunc_0212acc0();
        return;
    }
    if (parentCount_ > 0) {
        dss::sprintf_s(buf, sizeof(buf), "%2d %08x", 0, bssDesc_[0].gameInfo.ggid);
        unkfunc_0204348c(1, 2, buf);
        if (unkfunc_02121f50() == WH_SYSSTATE_SCANNING) {
            unkfunc_021218f4();
        }
        unkfunc_0212a750(SYSMODE_CHILD_CONNECT);
        return;
    }
    if (role_.unkfunc_0212b0f0()) {
        if (unkfunc_02121f50() == WH_SYSSTATE_SCANNING) {
            unkfunc_021218f4();
        }
        unkfunc_0212a750(SYSMODE_SELECT_SCAN);
    }
}

ARM void UnkMPExchange::unkfunc_02129cec()
{
    unkfunc_020434c8(2, 1, "CHANNEL %d", unk_40);
    role_.unkfunc_0212afec();
    if (unkfunc_02121f50() != WH_SYSSTATE_IDLE) {
        return;
    }
    if (unk_1c != 0) {
        unkfunc_0212acc0();
        return;
    }
    role_.unkfunc_0212b0d8();
    switch (unk_40) {
    case 1:
        unk_40 = 7;
        unkfunc_0212ac8c(7);
        break;
    case 7:
        unk_40 = 13;
        unkfunc_0212ac8c(13);
        break;
    case 13:
        unkfunc_02122888();
        unkfunc_0212a750(SYSMODE_SELECT_NEXT);
        break;
    }
}

ARM void UnkMPExchange::unkfunc_02129d9c()
{
    if (unkfunc_02121f50() == WH_SYSSTATE_IDLE) {
        unkfunc_02122740(5, &bssDesc_[0]);
        unkfunc_0212a750(SYSMODE_CHILD_READY);
    }
}

ARM void UnkMPExchange::unkfunc_02129dd0()
{
    unkfunc_0212a1b4();
    dss::memcpy(&SEND_PACKET->data_, sendData_, 0xdc);
    if (unkfunc_02121f40() == 1) {
        unkfunc_0212acc0();
        return;
    }
    if (unk_3c == 4) {
        unkfunc_0212acc0();
        return;
    }
    if (unk_3c == 6) {
        unkfunc_0212acc0();
        return;
    }
    if (unk_1c != 0) {
        unkfunc_0212acc0();
        return;
    }
    if (RECV_PACKET(0)->state_ == 2) {
        unkfunc_0212acc0();
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

ARM void UnkMPExchange::unkfunc_02129ec4()
{
    unkfunc_0212a1b4();
    dss::memcpy(&SEND_PACKET->data_, sendData_, 0xdc);
    if (unk_3c == 5) {
        unkfunc_0212acc0();
        return;
    }
    if (unk_3c == 6) {
        if (unk_fc == 1) {
            unkfunc_0212acc0();
        }
        return;
    }
    if (unk_1c != 0) {
        unkfunc_0212acc0();
        return;
    }
    if (RECV_PACKET(0)->state_ == 2) {
        unkfunc_0212acc0();
    }
}

ARM void UnkMPExchange::unkfunc_02129f58()
{
    role_.unkfunc_0212afec();
    if (unkfunc_02121f50() == WH_SYSSTATE_IDLE) {
        unkfunc_0212a750(SYSMODE_SELECT_ROLE);
    }
}

ARM void UnkMPExchange::unkfunc_02129f84()
{
    if (unkfunc_02121f50() == WH_SYSSTATE_DATASHARING) {
        if (unkfunc_021227ec(sendBuffer_)) {
            int i;
            for (i = 0; i < 2; i++) {
                void* data = unkfunc_021227cc(i);
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

ARM void UnkMPExchange::unkfunc_0212a10c()
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
