#include "ctrdg_internal.h"

#pragma thumb on

#define REG_EXMEMCNT (*(vu16*)0x04000204)
#define REG_IME      (*(vu16*)0x04000208)
#define REG_POSTFLG  (*(vu16*)0x04000300)

#define CTRDG_AGB_ROM ((u8*)0x08000000)

/* definition order chosen for the .bss layout (the compiler sorts the objects by size) */
UnkCtrdgCommon2 data_0211da0c;
BOOL            data_0211da08; /* cartridge access enabled */

void func_02071b58(void) {
    u32 zero = 0;
    CpuSet(&zero, &data_0211da0c, 0x05000001);
    data_0211da0c.unk_02 = OS_GetLockID();
}

BOOL func_02071b80(void) {
    if (func_02071bac() && !func_02071b9c()) {
        return TRUE;
    }
    return FALSE;
}

BOOL func_02071b9c(void) {
    UnkCtrdgInfo* info = CTRDG_INFO;
    return info->unk_05_0;
}

/* Checks that the inserted cartridge is still the one detected at boot. */
BOOL func_02071bac(void) {
    BOOL           ret  = TRUE;
    UnkCtrdgInfo*  info = CTRDG_INFO;
    UnkCtrdgLock   lock;
    UnkCtrdgCycles cycles;

    if (info->unk_00 == 0xFFFF) {
        return FALSE;
    }
    if (info->unk_05_1 == 1) {
        return FALSE;
    }

    func_02071cb4(data_0211da0c.unk_02, &lock);
    func_02071c58(&cycles);
    {
        u8* rom = CTRDG_AGB_ROM;
        if ((rom[0xB2] == 0x96 && info->unk_00 != *(u16*)(rom + 0xBE)) ||
            (rom[0xB2] != 0x96 && info->unk_00 != *(u16*)0x0801FFFE) ||
            (info->unk_08 != *(u32*)(rom + 0xAC) && info->unk_05_0)) {
            ret            = FALSE;
            info->unk_05_1 = 1;
        }
    }
    func_02071c8c(&cycles);
    func_02071cf0(data_0211da0c.unk_02, &lock);
    return ret;
}

void func_02071c58(UnkCtrdgCycles* cycles) {
    cycles->unk_00 = (REG_EXMEMCNT & 0xC) >> 2;
    cycles->unk_04 = (REG_EXMEMCNT & 0x10) >> 4;
    REG_EXMEMCNT   = (u16)((REG_EXMEMCNT & ~0xC) | (3 << 2));
    REG_EXMEMCNT   = (u16)((REG_EXMEMCNT & ~0x10) | (0 << 4));
}

#pragma opt_propagation off
static inline void CTRDGi_SetRomCycle1st(u32 cycle) {
    REG_EXMEMCNT = (u16)((REG_EXMEMCNT & ~0xC) | (cycle << 2));
}

static inline void CTRDGi_SetRomCycle2nd(u32 cycle) {
    REG_EXMEMCNT = (u16)((REG_EXMEMCNT & ~0x10) | (cycle << 4));
}

void func_02071c8c(const UnkCtrdgCycles* cycles) {
    CTRDGi_SetRomCycle1st(cycles->unk_00);
    CTRDGi_SetRomCycle2nd(cycles->unk_04);
}
#pragma opt_propagation reset

/* Locks the cartridge bus unless the ARM7 holds it. */
void func_02071cb4(u16 lockId, UnkCtrdgLock* lock) {
    for (;;) {
        lock->unk_04 = OS_DisableIRQ();
        if ((lock->unk_00 = func_02087354((void*)0x027FFFE8) & 0x40) != 0) {
            return;
        }
        if (func_020872d0(lockId) == 0) {
            return;
        }
        OS_RestoreIRQ(lock->unk_04);
        WaitByLoop(1);
    }
}

void func_02071cf0(u16 lockId, UnkCtrdgLock* lock) {
    if (lock->unk_00 == 0) {
        func_020872c8(lockId);
    }
    OS_RestoreIRQ(lock->unk_04);
}

void func_02071d08(u32 data) {
    while (PXI_SendWordByFifo(13, data, FALSE) != 0) {
        WaitByLoop(1);
    }
}

void func_02071d38(BOOL enable) {
    ENTER_CRITICAL_SECTION();
    data_0211da08 = enable;
    if (!func_02071b80()) {
        func_02088320(0xF000, enable ? 0x1000 : 0x5000);
    }
    LEAVE_CRITICAL_SECTION();
}
