#include "wm_internal.h"

#pragma thumb on

typedef struct UnkWmParentParam {
    u16* userGameInfo;       // 0x00
    u16 userGameInfoLength;  // 0x04
    u8 unk_06[0xe];
    u16 KS_Flag;             // 0x14
    u8 unk_16[2];
    u16 beaconPeriod;        // 0x18
    u8 unk_1a[0x18];
    u16 channel;             // 0x32
    u16 parentMaxSize;       // 0x34
    u16 childMaxSize;        // 0x36
    u8 unk_38[8];
} UnkWmParentParam;

u32 func_0207a4b0(UnkWmCallbackFunc callback, UnkWmParentParam* param) {
    u32 result = func_02079df8(1, 2);

    if (result != 0) {
        return result;
    }
    if (param == NULL) {
        return 6;
    }
    if (param->userGameInfoLength != 0 && param->userGameInfo == NULL) {
        return 6;
    }
    if (param->parentMaxSize + (param->KS_Flag ? 42 : 0) > 512 ||
        param->childMaxSize + (param->KS_Flag ? 6 : 0) > 512) {
        return 6;
    }

    func_0207a540(param);
    func_02079c94(7, callback);
    DC_CleanRange(param, sizeof(UnkWmParentParam));
    if (param->userGameInfoLength != 0) {
        DC_CleanRange(param->userGameInfo, param->userGameInfoLength);
    }
    result = func_02079ce0(7, 1, param);
    if (result != 0) {
        return result;
    }
    return 2;
}

BOOL func_0207a540(void* param_) {
    UnkWmParentParam* param = (UnkWmParentParam*)param_;

    if (param->userGameInfoLength > 0x70) {
        return FALSE;
    }
    if (param->beaconPeriod < 10 || param->beaconPeriod > 1000) {
        return FALSE;
    }
    if (param->channel < 1 || param->channel > 14) {
        return FALSE;
    }
    return TRUE;
}

u32 func_0207a570(UnkWmCallbackFunc callback, BOOL powerSave) {
    UnkWmArm9Buf* p;
    u32 result = func_02079df8(1, 2);

    if (result != 0) {
        return result;
    }
    p = func_02079da8();
    p->myAid = 0;
    p->connectedAidBitmap = 0;
    func_02079c94(8, callback);
    result = func_02079ce0(8, 1, powerSave);
    if (result != 0) {
        return result;
    }
    return 2;
}

u32 func_0207a5ac(UnkWmCallbackFunc callback) {
    return func_0207a570(callback, TRUE);
}

u32 func_0207a5b8(UnkWmCallbackFunc callback) {
    u32 result = func_02079df8(1, 7);

    if (result != 0) {
        return result;
    }
    func_02079c94(9, callback);
    result = func_02079ce0(9, 0);
    if (result != 0) {
        return result;
    }
    return 2;
}
