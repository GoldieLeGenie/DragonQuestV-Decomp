#include "../sdk_internal.h"
#include "rtc_internal.h"

#pragma thumb on

static BOOL func_020779ec(u32 command);

BOOL func_020779d4(void) {
    return func_020779ec(0x12);
}

BOOL func_020779e0(void) {
    return func_020779ec(0x27);
}

static BOOL func_020779ec(u32 command) {
    if (PXI_SendWordByFifo(5, (command << 8) & 0x7F00, FALSE) < 0) {
        return FALSE;
    }
    return TRUE;
}
