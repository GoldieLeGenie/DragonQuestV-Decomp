// Card wait / result / lock helpers. A unit of its own: these functions address data_0211d1a0 through its own
// symbol, while card_common.c (which defines it) reaches it through its pooled .bss base.
#include "card_internal.h"

#pragma thumb on

/* This unit is built without loop rotation (while loops keep their test at the bottom, entered by a branch). */
#pragma opt_rotateloops off
#pragma opt_propagation off

BOOL func_02070c70(void) {
    UnkCardCommon* const p = &data_0211d1a0;
    ENTER_CRITICAL_SECTION();
    while (p->unk_114 & 4) {
        OS_PauseThread(&p->unk_10c);
    }
    LEAVE_CRITICAL_SECTION();
    return p->unk_000->unk_00 == 0;
}

BOOL func_02070cac(void) {
    UnkCardCommon* const p = &data_0211d1a0;
    return (p->unk_114 & 4) == 0;
}

u32 CARD_GetResultCode(void) {
    return data_0211d1a0.unk_000->unk_00;
}

void CARD_LockRom(u16 lockId) {
    func_02070ac8(lockId, 1);
    func_02087308(lockId);
}

void CARD_UnlockRom(u16 lockId) {
    func_0208731c(lockId);
    func_02070b24(lockId, 1);
}

void CARD_LockBackup(u16 lockId) {
    func_02070ac8(lockId, 2);
}

void CARD_UnlockBackup(u16 lockId) {
    if (!CARD_TryWaitBackupAsync()) {
        func_020712d0();
    }
    func_02070b24(lockId, 2);
}

