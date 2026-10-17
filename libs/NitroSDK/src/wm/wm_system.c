#include "wm_internal.h"

#pragma thumb on

static u16 data_0211fde0;
static UnkWmArm9Buf* data_0211fde4;
static UnkMessageQueue data_0211fde8;
static void* data_0211fe08[10];
static UnkWmPortRecvCallback data_0211fe30;
static u16 data_0211fe80[10][0x80] __attribute__((aligned(32)));
static u32 data_0209c508 = 0x10000;

#define WM_FIFO_FLAG (*(u16*)0x027fff96)

u32 func_02079af8(void* buf, u16 dmaNo) {
    u32 result = func_02079b14(buf, dmaNo, 0xf00);

    if (result != 0) {
        return result;
    }
    data_0211fde4->unk_016 = 0;
    return result;
}

u32 func_02079b14(void* buf, u16 dmaNo, u32 size) {
    u32 enabled = OS_DisableIRQ();
    s32 i;

    if (data_0211fde0) {
        OS_RestoreIRQ(enabled);
        return 3;
    }
    if (buf == NULL) {
        OS_RestoreIRQ(enabled);
        return 6;
    }
    if (dmaNo > 3) {
        OS_RestoreIRQ(enabled);
        return 6;
    }
    if ((u32)buf & 0x1f) {
        OS_RestoreIRQ(enabled);
        return 6;
    }

    func_0207734c();
    if (!func_0207744c(10, 1)) {
        OS_RestoreIRQ(enabled);
        return 4;
    }

    DC_InvalidateRange(buf, size);
    func_0206fc90(dmaNo, buf, 0, size);

    data_0211fde4 = (UnkWmArm9Buf*)buf;
    data_0211fde4->unk_000 = (u8*)buf + 0x200;
    data_0211fde4->status = (UnkWmStatus*)((u8*)data_0211fde4->unk_000 + 0x300);
    data_0211fde4->unk_00c = (u8*)data_0211fde4->status + 0x800;
    data_0211fde4->unk_010 = (u8*)data_0211fde4->unk_00c + 0x100;

    func_0207a0d4();

    data_0211fde4->dmaNo = dmaNo;
    data_0211fde4->connectedAidBitmap = 0;
    data_0211fde4->myAid = 0;
    {
        s32 j;
        for (j = 0; j < 16; j++) {
            data_0211fde4->portCallbackTable[j] = NULL;
            data_0211fde4->portCallbackArgument[j] = NULL;
        }
    }

    func_02087aec(&data_0211fde8, data_0211fe08, 10);
    for (i = 0; i < 10; i++) {
        data_0211fe80[i][0] = 0x8000;
        DC_CleanRange(data_0211fe80[i], 2);
        func_02087b00(&data_0211fde8, data_0211fe80[i], 1);
    }

    func_02077400(10, (PxiCallback)func_02079e48);
    data_0211fde0 = TRUE;
    OS_RestoreIRQ(enabled);
    return 0;
}

u32 func_02079c4c(void) {
    u32 result;
    u32 enabled = OS_DisableIRQ();

    if (func_02079db4() != 0) {
        OS_RestoreIRQ(enabled);
        return 3;
    }
    result = func_02079df8(1, 0);
    if (result != 0) {
        return result;
    }

    func_0207a0d4();
    func_02077400(10, NULL);
    data_0211fde4 = NULL;
    data_0211fde0 = FALSE;
    OS_RestoreIRQ(enabled);
    return 0;
}

void func_02079c94(u32 id, UnkWmCallbackFunc callback) {
    data_0211fde4->callbackTable[id] = callback;
}

u32* func_02079ca4(void) {
    u32* buf;

    if (!func_02087b5c(&data_0211fde8, &buf, 0)) {
        return NULL;
    }
    DC_InvalidateRange(buf, 2);
    if (!(*(u16*)buf & 0x8000)) {
        func_02087bc4(&data_0211fde8, buf, 1);
        return NULL;
    }
    return buf;
}

u32 func_02079ce0(u16 id, u16 paramNum, ...) {
    va_list args;
    s32 i;
    s32 result;
    u32* buf = func_02079ca4();

    if (buf == NULL) {
        return 8;
    }
    *(u16*)buf = id;

    va_start(args, paramNum);
    for (i = 0; i < paramNum; i++) {
        buf[i + 1] = va_arg(args, u32);
    }
    va_end(args);

    DC_CleanRange(buf, 0x100);
    result = PXI_SendWordByFifo(10, (u32)buf, FALSE);
    func_02087b00(&data_0211fde8, buf, 1);
    if (result < 0) {
        return 8;
    }
    return 2;
}

u32 func_02079d5c(void* data, u32 length) {
    s32 result;
    u32* buf = func_02079ca4();

    if (buf == NULL) {
        return 8;
    }
    MI_CpuCopyU8(data, buf, length);
    DC_CleanRange(buf, length);
    result = PXI_SendWordByFifo(10, (u32)buf, FALSE);
    func_02087b00(&data_0211fde8, buf, 1);
    if (result < 0) {
        return 8;
    }
    return 2;
}

UnkWmArm9Buf* func_02079da8(void) {
    return data_0211fde4;
}

u32 func_02079db4(void) {
    if (data_0211fde0) {
        return 0;
    }
    return 3;
}

u32 func_02079dc8(void) {
    u32 result = func_02079db4();

    if (result != 0) {
        return result;
    }
    DC_InvalidateRange(&data_0211fde4->status->state, 2);
    if (data_0211fde4->status->state <= 1) {
        return 3;
    }
    return 0;
}

u32 func_02079df8(s32 paramNum, ...) {
    u32 result;
    u16 now;
    va_list args;

    result = func_02079db4();
    if (result != 0) {
        return result;
    }
    DC_InvalidateRange(&data_0211fde4->status->state, 2);
    now = data_0211fde4->status->state;

    result = 3;
    va_start(args, paramNum);
    for (; paramNum; paramNum--) {
        if (va_arg(args, u32) == now) {
            result = 0;
        }
    }
    va_end(args);
    return result;
}

void func_02079e48(u32 tag, u32 data, BOOL err) {
    UnkWmArm9Buf* p = data_0211fde4;
    UnkWmCallback* cb = (UnkWmCallback*)data;

    if (err) {
        return;
    }

    DC_InvalidateRange(p->unk_010, 0x100);
    if (p->unk_016 == 0) {
        DC_InvalidateRange(p->status, 0x800);
    }
    if ((void*)cb != p->unk_010) {
        DC_InvalidateRange(cb, 0x100);
    }

    if (cb->apiid >= 0x2c) {
        if (cb->apiid == 0x80) {
            if (cb->errcode == 0x13) {
                OS_Terminate();
            }
            if (p->indCallback) {
                p->indCallback(cb);
            }
        } else if (cb->apiid == 0x82) {
            UnkWmPortRecvCallback* cbPort = (UnkWmPortRecvCallback*)cb;
            if (p->portCallbackTable[cbPort->port]) {
                cbPort->arg = p->portCallbackArgument[cbPort->port];
                cbPort->connectedAidBitmap = (u16)p->connectedAidBitmap;
                DC_InvalidateRange(cbPort->recvBuf, p->status->unk_072);
                p->portCallbackTable[cbPort->port](cb);
            }
        } else if (cb->apiid == 0x81) {
            UnkWmUnknownCallback* cbUnknown = (UnkWmUnknownCallback*)cb;
            cb->apiid = 0xf;
            if (cbUnknown->callback) {
                cbUnknown->callback(cb);
            }
        }
    } else {
        if (cb->apiid == 0xe) {
            UnkWmStartMPCallback* cbStartMP = (UnkWmStartMPCallback*)cb;
            if ((cbStartMP->state == 11 || cbStartMP->state == 12) && cb->errcode == 0) {
                DC_InvalidateRange(cbStartMP->recvBuf, p->status->unk_072);
            }
        }

        if (cb->apiid == 2 && cb->errcode == 0) {
            UnkWmCallbackFunc callback = p->callbackTable[cb->apiid];
            func_02079c4c();
            if (callback) {
                callback(cb);
            }
            return;
        }

        if (p->callbackTable[cb->apiid]) {
            p->callbackTable[cb->apiid](cb);
            if (!data_0211fde0) {
                return;
            }
        }

        if (cb->apiid == 8 || cb->apiid == 0xc) {
            u16 state;
            u16 aid;
            u16 myAid;
            u16 reason;
            u8* macAddress;
            u8* ssid;
            u16 parentSize;
            u16 childSize;

            if (cb->apiid == 8) {
                UnkWmStartParentCallback* cbParent = (UnkWmStartParentCallback*)cb;
                state = cbParent->state;
                aid = cbParent->aid;
                myAid = 0;
                macAddress = cbParent->macAddress;
                ssid = cbParent->ssid;
                reason = cbParent->reason;
                parentSize = cbParent->parentSize;
                childSize = cbParent->childSize;
            } else if (cb->apiid == 0xc) {
                UnkWmStartConnectCallback* cbConnect = (UnkWmStartConnectCallback*)cb;
                state = cbConnect->state;
                aid = 0;
                macAddress = cbConnect->macAddress;
                ssid = NULL;
                myAid = cbConnect->aid;
                reason = cbConnect->reason;
                parentSize = cbConnect->parentSize;
                childSize = cbConnect->childSize;
            }

            if (state == 7 || state == 9 || state == 0x1a) {
                u16 i;

                if (state == 7) {
                    p->connectedAidBitmap |= (1 << aid);
                } else {
                    p->connectedAidBitmap &= ~(1 << aid);
                }
                p->myAid = myAid;

                MI_CpuSet(&data_0211fe30, 0, sizeof(UnkWmPortRecvCallback));
                data_0211fe30.apiid = 0x82;
                data_0211fe30.errcode = 0;
                data_0211fe30.state = state;
                data_0211fe30.recvBuf = NULL;
                data_0211fe30.data = NULL;
                data_0211fe30.length = 0;
                data_0211fe30.aid = aid;
                data_0211fe30.myAid = myAid;
                data_0211fe30.connectedAidBitmap = (u16)p->connectedAidBitmap;
                data_0211fe30.seqNo = 0xffff;
                data_0211fe30.reason = reason;
                MI_CpuCopyU8(macAddress, data_0211fe30.macAddress, 6);
                if (ssid) {
                    MI_CpuCopyU16(ssid, data_0211fe30.ssid, 24);
                } else {
                    MI_CpuFillU16(0, data_0211fe30.ssid, 24);
                }
                data_0211fe30.maxSendDataSize = (myAid == 0) ? parentSize : childSize;
                data_0211fe30.maxRecvDataSize = (myAid == 0) ? childSize : parentSize;

                for (i = 0; i < 16; i++) {
                    data_0211fe30.port = i;
                    if (p->portCallbackTable[i]) {
                        data_0211fe30.arg = p->portCallbackArgument[i];
                        p->portCallbackTable[i](&data_0211fe30);
                    }
                }
            }
        }
    }

    DC_InvalidateRange(p->unk_010, 0x100);
    func_0207a0d4();
    if ((void*)cb != p->unk_010) {
        cb->apiid |= 0x8000;
        DC_CleanRange(cb, 0x100);
    }
}

void func_0207a0d4(void) {
    u16* flag = &WM_FIFO_FLAG;

    if (*flag & 1) {
        *flag &= ~1;
    }
}

u16 func_0207a0ec(void) {
    u16 aid;
    u32 enabled = OS_DisableIRQ();

    if (data_0211fde4 != NULL) {
        aid = data_0211fde4->myAid;
    } else {
        aid = 0;
    }
    OS_RestoreIRQ(enabled);
    return aid;
}

u16 func_0207a110(void) {
    u32 bitmap;
    u32 enabled = OS_DisableIRQ();

    if (data_0211fde4 != NULL) {
        bitmap = data_0211fde4->connectedAidBitmap;
    } else {
        bitmap = 0;
    }
    OS_RestoreIRQ(enabled);
    return (u16)bitmap;
}

u32 func_0207a138(UnkWmCallbackFunc callback) {
    u32 result;
    u32 enabled = OS_DisableIRQ();

    result = func_02079db4();
    if (result != 0) {
        OS_RestoreIRQ(enabled);
        return result;
    }
    func_02079da8()->indCallback = callback;
    OS_RestoreIRQ(enabled);
    return 0;
}

u32 func_0207a168(u16 port, UnkWmCallbackFunc callback, void* arg) {
    u32 enabled;
    u32 result;
    UnkWmArm9Buf* p;
    UnkWmPortRecvCallback cbParam;

    if (callback) {
        MI_CpuSet(&cbParam, 0, sizeof(UnkWmPortRecvCallback));
        cbParam.apiid = 0x82;
        cbParam.errcode = 0;
        cbParam.state = 0x19;
        cbParam.port = port;
        cbParam.recvBuf = NULL;
        cbParam.data = NULL;
        cbParam.length = 0;
        cbParam.seqNo = 0xffff;
        cbParam.arg = arg;
        cbParam.aid = 0;
        func_020887b4(cbParam.macAddress);
    }

    enabled = OS_DisableIRQ();
    result = func_02079db4();
    if (result != 0) {
        OS_RestoreIRQ(enabled);
        return result;
    }
    p = func_02079da8();
    p->portCallbackTable[port] = callback;
    p->portCallbackArgument[port] = arg;
    if (callback) {
        cbParam.connectedAidBitmap = func_0207a110();
        cbParam.myAid = func_0207a0ec();
        callback(&cbParam);
    }
    OS_RestoreIRQ(enabled);
    return 0;
}

s32 func_0207a1fc(void) {
    UnkWmArm9Buf* p = func_02079da8();

    if (func_02079df8(2, 7, 8) != 0) {
        return 0;
    }
    DC_InvalidateRange(&p->status->unk_00c, 4);
    if (p->status->unk_00c == 1) {
        return 0;
    }
    DC_InvalidateRange(&p->status->unk_03c, 4);
    return (p->status->unk_03c + 0x1f) & ~0x1f;
}

s32 func_0207a240(void) {
    u32 maxSize;
    UnkWmArm9Buf* p = func_02079da8();
    BOOL isParent;

    if (func_02079df8(2, 7, 8) != 0) {
        return 0;
    }
    DC_InvalidateRange(&p->status->unk_00c, 4);
    if (p->status->unk_00c == 1) {
        return 0;
    }
    DC_InvalidateRange(&p->status->unk_188, 2);
    if (p->status->unk_188 == 0) {
        isParent = TRUE;
    } else {
        isParent = FALSE;
    }
    DC_InvalidateRange(&p->status->unk_03e, 2);
    maxSize = p->status->unk_03e;
    if (isParent == TRUE) {
        DC_InvalidateRange(&p->status->unk_0f8, 2);
        return (((maxSize + 0xc) * p->status->unk_0f8 + 0x29) & ~0x1f) << 1;
    }
    return ((maxSize + 0x51) & ~0x1f) << 1;
}

u16 func_0207a2c8(void) {
    if (func_02079db4() != 0) {
        return 0x8000;
    }
    return *(u16*)0x027ffcfa;
}

u16 func_0207a2e4(void) {
    UnkWmArm9Buf* p = func_02079da8();

    if (func_02079db4() != 0) {
        return 0;
    }
    DC_InvalidateRange(&p->status->state, 2);
    switch (p->status->state) {
    case 9:
        DC_InvalidateRange(&p->status->unk_182, 2);
        if (p->status->unk_182 == 0) {
            return 0;
        }
    case 10:
    case 11:
        DC_InvalidateRange(&p->status->unk_0bc, 2);
        return p->status->unk_0bc;
    }
    return 0;
}

u16 func_0207a344(void) {
    u8 mac[6];
    u16 sum;
    s32 i;

    func_020887b4(mac);
    for (i = 0, sum = 0; i < 6; i++) {
        sum += mac[i];
    }
    sum += *(vu32*)0x027ffc3c;
    sum *= 7;
    return (u16)(200 + (sum % 20));
}

u16 func_0207a38c(void) {
    u8 mac[6];
    u16 sum;
    s32 i;

    func_020887b4(mac);
    for (i = 0, sum = 0; i < 6; i++) {
        sum += mac[i];
    }
    sum += *(vu32*)0x027ffc3c;
    sum *= 13;
    return (u16)(30 + (sum % 10));
}

/* Next transfer group id, seeded once from the RTC clock */
u16 func_0207a3d4(void) {
    if (data_0209c508 == 0x10000) {
        UnkRtcTime time;

        func_020775a0();
        if (func_02077628(&time) == 0) {
            data_0209c508 = (u16)(time.second + (time.minute << 8));
        }
    }
    data_0209c508 = (u16)(data_0209c508 + 1);
    return (u16)data_0209c508;
}
