#include "wm_internal.h"

#pragma thumb on

typedef struct UnkWmMPTmpParam {
    u32 mask;          // 0x00
    u16 minFrequency;  // 0x04
    u16 frequency;     // 0x06
    u8 unk_08[8];
} UnkWmMPTmpParam;

typedef struct UnkWmStartMPReq {
    u16 apiid;              // 0x00
    u16 unk_02;
    u16* recvBuf;           // 0x04
    u32 recvBufSize;        // 0x08
    u16* sendBuf;           // 0x0c
    u32 sendBufSize;        // 0x10
    u8 unk_14[0x1c];        // 0x14
    UnkWmMPTmpParam param;  // 0x30
} UnkWmStartMPReq;

u32 func_0207a79c(UnkWmCallbackFunc callback, u16* recvBuf, s32 recvBufSize, u16* sendBuf, u16 sendBufSize,
                  void* tmpParam) {
    UnkWmStartMPReq req;
    UnkWmStatus* status = func_02079da8()->status;
    u32 result = func_02079df8(2, 7, 8);

    if (result != 0) {
        return result;
    }

    DC_InvalidateRange(&status->unk_188, 2);
    DC_InvalidateRange(&status->unk_0c6, 2);
    if (status->unk_188 != 0 && status->unk_0c6 != 1) {
        return 3;
    }
    DC_InvalidateRange(&status->unk_00c, 4);
    if (status->unk_00c == 1) {
        return 3;
    }
    if (recvBufSize & 0x3f) {
        return 6;
    }
    if (sendBufSize & 0x1f) {
        return 6;
    }
    DC_InvalidateRange(&status->unk_09c, 2);
    if (status->unk_09c == 0) {
        if (recvBufSize < func_0207a240()) {
            return 6;
        }
        if (sendBufSize < func_0207a1fc()) {
            return 6;
        }
    }

    func_02079c94(14, callback);
    func_02070224(0, &req, sizeof(UnkWmStartMPReq));
    req.apiid = 14;
    req.recvBuf = recvBuf;
    req.recvBufSize = (u32)recvBufSize >> 1;
    req.sendBuf = sendBuf;
    req.sendBufSize = sendBufSize;
    func_02070224(0, req.unk_14, sizeof(req.unk_14));
    MI_CpuCopyU32(tmpParam, &req.param, sizeof(UnkWmMPTmpParam));
    result = func_02079d5c(&req, sizeof(UnkWmStartMPReq));
    if (result != 0) {
        return result;
    }
    return 2;
}

u32 func_0207a89c(UnkWmCallbackFunc callback, u16* recvBuf, s32 recvBufSize, u16* sendBuf, u16 sendBufSize,
                  u16 mpFreq) {
    UnkWmMPTmpParam tmpParam;

    func_02070224(0, &tmpParam, sizeof(UnkWmMPTmpParam));
    tmpParam.mask = 3;
    tmpParam.minFrequency = mpFreq;
    tmpParam.frequency = mpFreq;
    return func_0207a79c(callback, recvBuf, recvBufSize, sendBuf, sendBufSize, &tmpParam);
}

u32 func_0207a8d8(UnkWmCallbackFunc callback, void* arg, const u16* sendData, u16 sendDataSize, u16 destBitmap,
                  u16 port, u16 prio) {
    u16 childBitmap = 1;
    UnkWmStatus* status = func_02079da8()->status;
    u32 result = func_02079df8(2, 9, 10);

    if (result != 0) {
        return result;
    }

    DC_InvalidateRange(&status->unk_188, 2);
    if (status->unk_188 == 0) {
        DC_InvalidateRange(&status->unk_182, 2);
        childBitmap = status->unk_182;
        DC_InvalidateRange(&status->unk_086, 2);
    }

    if (sendData == NULL) {
        return 6;
    }
    if (childBitmap == 0) {
        return 7;
    }
    DC_InvalidateRange(&status->unk_07c, 2);
    if ((u32)sendData == status->unk_07c) {
        return 6;
    }
    if (sendDataSize > 512) {
        return 6;
    }
    if (sendDataSize == 0) {
        return 6;
    }

    DC_CleanRange((void*)sendData, sendDataSize);
    result = func_02079ce0(15, 7, sendData, sendDataSize, destBitmap, port, prio, callback, arg);
    if (result != 0) {
        return result;
    }
    return 2;
}

u32 func_0207a9a4(UnkWmCallbackFunc callback) {
    UnkWmArm9Buf* p = func_02079da8();
    u32 result = func_02079df8(2, 9, 10);

    if (result != 0) {
        return result;
    }
    DC_InvalidateRange(&p->status->unk_00c, 4);
    if (p->status->unk_00c == 0) {
        return 3;
    }
    func_02079c94(16, callback);
    result = func_02079ce0(16, 0);
    if (result != 0) {
        return result;
    }
    return 2;
}
