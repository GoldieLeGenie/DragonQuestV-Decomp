#include "../sdk_internal.h"

u32 data_02127f50;    // locked bank mask
u16 data_02127f54[9]; // lock id per bank

// clang-format off
asm u32 func_02088820(register u32 value) {
    clz r0, r0
    bx lr
}
// clang-format on

#pragma thumb on

void func_02088828(void) {
    s32 i;

    data_02127f50 = 0;
    for (i = 0; i < 9; i++) {
        data_02127f54[i] = 0;
    }
}

/* Releases every bank of `bank` held by `lockID`. */
void func_02088848(u32 bank, u16 lockID) {
    u32 mask;
    u32 enabled = OS_DisableIRQ();

    mask = bank & data_02127f50 & 0x1ff;

    while (TRUE) {
        s32 i = 31 - func_02088820(mask);
        if (i < 0) {
            break;
        }
        mask &= ~(1 << i);
        if (data_02127f54[i] == lockID) {
            data_02127f54[i] = 0;
            data_02127f50 &= ~(1 << i);
        }
    }
    OS_RestoreIRQ(enabled);
}

#pragma thumb off
