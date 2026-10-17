#include "wm_internal.h"

#pragma thumb on

u32 func_0207b228(UnkWmCallbackFunc callback, u16 wepMode, const u16* wepKey) {
    u32 result = func_02079dc8();

    if (result != 0) {
        return result;
    }
    if (wepMode > 3) {
        return 6;
    }
    if (wepMode != 0) {
        if (wepKey == NULL) {
            return 6;
        }
        DC_CleanRange((void*)wepKey, 0x50);
    }
    func_02079c94(20, callback);
    result = func_02079ce0(20, 2, wepMode, wepKey);
    if (result != 0) {
        return result;
    }
    return 2;
}
