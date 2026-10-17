#include "card_internal.h"

#pragma thumb on

/* This unit is built without loop rotation (while loops keep their test at the bottom, entered by a branch). */
#pragma opt_rotateloops off

BOOL          data_0211d120;                            /* card access enabled */
UnkCardCmd    data_0211d140 ATTRIBUTE_ALIGN(32);        /* command block shared with the ARM7 */
UnkCardCommon data_0211d1a0;                            /* card library state */
static u8     data_0211d3c0[0x400] ATTRIBUTE_ALIGN(32); /* card thread stack */


static inline BOOL CARDi_IsBootTypeMultiboot(void) {
    return *(vu16*)0x027FFC40 == 2;
}

/* Hands a task to the card thread and wakes it up. */
void func_02070a90(UnkCardTask task) {
    UnkCardCommon* const p = &data_0211d1a0;

    func_020878e4(&p->unk_044, p->unk_108);
    p->unk_104 = &p->unk_044;
    p->unk_040 = task;
    p->unk_114 |= 8;
    OS_WakeupThreadDirect(&p->unk_044);
}

/* Acquires the card bus for one target (1 = rom, 2 = backup). */
void func_02070ac8(u16 lockId, u32 target) {
    UnkCardCommon* const p = &data_0211d1a0;
    ENTER_CRITICAL_SECTION();

    if (p->unk_008 == lockId) {
        if (p->unk_018 != target) {
            OS_Terminate();
        }
    } else {
        while (p->unk_008 != -3) {
            OS_PauseThread(&p->unk_010);
        }
        p->unk_008 = lockId;
        p->unk_018 = target;
    }
    ++p->unk_00c;
    p->unk_000->unk_00 = 0;
    LEAVE_CRITICAL_SECTION();
}

/* Releases the card bus. */
void func_02070b24(u16 lockId, u32 target) {
    UnkCardCommon* const p = &data_0211d1a0;
    ENTER_CRITICAL_SECTION();

    if (p->unk_008 != lockId || p->unk_00c == 0) {
        OS_Terminate();
    } else {
        s32 ref;
        if (p->unk_018 != target) {
            OS_Terminate();
        }
        ref = p->unk_00c - 1;
        p->unk_00c = ref;
        if (ref == 0) {
            p->unk_008 = -3;
            p->unk_018 = 0;
            OS_UnpauseThread(&p->unk_010);
        }
    }
    p->unk_000->unk_00 = 0;
    LEAVE_CRITICAL_SECTION();
}

void func_02070b7c(void) {
    UnkCardCommon* const p = &data_0211d1a0;

    p->unk_008 = -3;
    p->unk_00c = 0;
    p->unk_018 = 0;
    p->unk_000 = &data_0211d140;
    MI_CpuFill(0, p->unk_000, sizeof(UnkCardCmd));
    DC_PurgeRange(&data_0211d140, sizeof(UnkCardCmd));
    p->unk_118[0] = -1;
    p->unk_118[1] = -1;

    if (!CARDi_IsBootTypeMultiboot()) {
        MI_CpuCopyU8((void*)0x027FFE00, (void*)0x027FFA80, 0x160);
    }

    p->unk_010.tail   = NULL;
    p->unk_010.head   = NULL;
    p->unk_10c.tail   = NULL;
    p->unk_10c.head   = NULL;
    p->unk_108        = 4;
    func_02087688(&p->unk_044, func_02071830, NULL, data_0211d3c0 + sizeof(data_0211d3c0), sizeof(data_0211d3c0), p->unk_108);
    OS_WakeupThreadDirect(&p->unk_044);
    func_02077400(11, func_02071808);

    if (CARDi_IsBootTypeMultiboot()) {
        return;
    }
    func_02070c64(TRUE);
}

BOOL func_02070c48(void) {
    return data_0211d120;
}

void func_02070c54(void) {
    if (!func_02070c48()) {
        OS_Terminate();
    }
}

void func_02070c64(BOOL enable) {
    data_0211d120 = enable;
}
