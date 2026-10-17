#include "wm_internal.h"

#pragma thumb on

u32 func_0207a41c(void* buf, UnkWmCallbackFunc callback, u16 dmaNo) {
    return func_0207a428(buf, callback, dmaNo, 0);
}

u32 func_0207a428(void* buf, UnkWmCallbackFunc callback, u16 dmaNo, u32 flags) {
    UnkWmArm9Buf* p;
    u32 result = func_02079af8(buf, dmaNo);

    if (result != 0) {
        return result;
    }
    func_02079c94(0, callback);
    p = func_02079da8();
    result = func_02079ce0(0, 4, p->unk_000, p->status, p->unk_010, flags);
    if (result != 0) {
        return result;
    }
    return 2;
}

u32 func_0207a464(UnkWmCallbackFunc callback) {
    u32 result = func_02079dc8();

    if (result != 0) {
        return result;
    }
    func_02079c94(1, callback);
    result = func_02079ce0(1, 0);
    if (result != 0) {
        return result;
    }
    return 2;
}

u32 func_0207a488(UnkWmCallbackFunc callback) {
    u32 result = func_02079df8(1, 2);

    if (result != 0) {
        return result;
    }
    func_02079c94(2, callback);
    result = func_02079ce0(2, 0);
    if (result != 0) {
        return result;
    }
    return 2;
}
