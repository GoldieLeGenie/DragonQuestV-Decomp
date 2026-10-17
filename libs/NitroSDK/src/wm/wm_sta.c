#include "wm_internal.h"
#include "wm_bssdesc.h"

#pragma thumb on

typedef struct UnkWmScanParam {
    void* scanBuf;       // 0x00
    u16 channel;         // 0x04
    u16 maxChannelTime;  // 0x06
    u8 bssid[6];         // 0x08
} UnkWmScanParam;

typedef struct UnkWmStartScanReq {
    u16 apiid;
    u16 channel;
    void* scanBuf;
    u16 maxChannelTime;
    u8 bssid[6];
} UnkWmStartScanReq;

typedef struct UnkWmStartConnectReq {
    u16 apiid;            // 0x00
    u16 unk_02;
    UnkWmBssDesc* pInfo;  // 0x04
    u8 ssid[24];          // 0x08
    BOOL powerSave;       // 0x20
    u16 unk_24;
    u16 authMode;         // 0x26
} UnkWmStartConnectReq;

u32 func_0207a5e0(UnkWmCallbackFunc callback, UnkWmScanParam* param) {
    UnkWmStartScanReq req;
    u32 result = func_02079df8(3, 2, 3, 5);

    if (result != 0) {
        return result;
    }
    if (param == NULL) {
        return 6;
    }
    if (param->scanBuf == NULL) {
        return 6;
    }
    if (param->channel < 1 || param->channel > 14) {
        return 6;
    }

    func_02079c94(10, callback);
    req.apiid = 10;
    req.channel = param->channel;
    req.scanBuf = param->scanBuf;
    req.maxChannelTime = param->maxChannelTime;
    req.bssid[0] = param->bssid[0];
    req.bssid[1] = param->bssid[1];
    req.bssid[2] = param->bssid[2];
    req.bssid[3] = param->bssid[3];
    req.bssid[4] = param->bssid[4];
    req.bssid[5] = param->bssid[5];
    result = func_02079d5c(&req, sizeof(UnkWmStartScanReq));
    if (result != 0) {
        return result;
    }
    return 2;
}

u32 func_0207a664(UnkWmCallbackFunc callback) {
    u32 result = func_02079df8(1, 5);

    if (result != 0) {
        return result;
    }
    func_02079c94(11, callback);
    result = func_02079ce0(11, 0);
    if (result != 0) {
        return result;
    }
    return 2;
}

u32 func_0207a68c(UnkWmCallbackFunc callback, UnkWmBssDesc* pInfo, const u8* ssid, BOOL powerSave, u16 authMode) {
    UnkWmStartConnectReq req;
    UnkWmArm9Buf* p;
    u32 result = func_02079df8(1, 2);

    if (result != 0) {
        return result;
    }
    if (pInfo == NULL) {
        return 6;
    }
    DC_CleanRange(pInfo, pInfo->length * 2);

    p = func_02079da8();
    p->myAid = 0;
    p->connectedAidBitmap = 0;
    func_02079c94(12, callback);

    req.apiid = 12;
    req.pInfo = pInfo;
    if (ssid != NULL) {
        MI_CpuCopyU8(ssid, req.ssid, 24);
    } else {
        MI_CpuSet(req.ssid, 0, 24);
    }
    req.powerSave = powerSave;
    req.authMode = authMode;
    result = func_02079d5c(&req, sizeof(UnkWmStartConnectReq));
    if (result != 0) {
        return result;
    }
    return 2;
}

u32 func_0207a710(UnkWmCallbackFunc callback, u16 aid) {
    UnkWmArm9Buf* p = func_02079da8();
    u32 result = func_02079df8(5, 7, 9, 8, 10, 11);

    if (result != 0) {
        return result;
    }
    if (p->status->state == 7 || p->status->state == 9) {
        if (aid < 1 || aid > 15) {
            return 6;
        }
        DC_InvalidateRange(&p->status->unk_182, 2);
        if (!(p->status->unk_182 & (1 << aid))) {
            return 7;
        }
    } else {
        if (aid != 0) {
            return 6;
        }
    }

    func_02079c94(13, callback);
    result = func_02079ce0(13, 1, 1 << aid);
    if (result != 0) {
        return result;
    }
    return 2;
}
