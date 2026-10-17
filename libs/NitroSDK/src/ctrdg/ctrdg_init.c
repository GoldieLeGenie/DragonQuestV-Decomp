// Cartridge initialization (AGB header read, pull-out handling). A unit of its own: its .bss starts at the
// 32-byte aligned data_0211da20 (the function-local static of func_02071de8) and it reaches data_0211da0c
// through its own symbol, unlike ctrdg_common.c.
#include "ctrdg_internal.h"

#pragma thumb on

#define REG_EXMEMCNT (*(vu16*)0x04000204)
#define REG_IME      (*(vu16*)0x04000208)
#define REG_POSTFLG  (*(vu16*)0x04000300)

#define CTRDG_AGB_ROM ((u8*)0x08000000)

UnkCtrdgState     data_0211da24;
UnkCtrdgAgbHeader data_0211da40 ATTRIBUTE_ALIGN(32); /* copy of the AGB cartridge header */
UnkCtrdgThread    data_0211db00;                     /* cartridge task thread */

void func_02071d70(void) {
    if (data_0211da24.unk_04) {
        return;
    }
    data_0211da24.unk_04 = TRUE;

    func_02071b58();
    data_0211da24.unk_08 = FALSE;
    func_0207734c();
    while (!func_0207744c(13, TRUE)) {
    }
    func_02077400(13, func_02071f38);
    func_02071de8();
    func_02077400(13, NULL);
    func_02077400(13, func_02071f54);
    data_0211da24.unk_14 = NULL;
    func_02071fa8(&data_0211db00);
    func_02077400(17, func_02071f9c);
    func_02071d38(FALSE);
}

/* Reads the AGB cartridge header and hands it to the ARM7. */
void func_02071de8(void) {
    static BOOL data_0211da20; /* module info initialized */

    if (data_0211da20) {
        return;
    }
    data_0211da20 = TRUE;
    if (!(REG_POSTFLG & 1)) {
        return;
    }

    {
        const u32      irq = func_020870a4(0x40000);
        const u16      ime = REG_IME;
        UnkCtrdgLock   lock;
        UnkCtrdgCycles cycles;
        s32            phi;

        REG_IME = 1;
        func_02071cb4(data_0211da0c.unk_02, &lock);
        phi = (REG_EXMEMCNT & 0x8000) >> 15;
        func_02071c58(&cycles);
        REG_EXMEMCNT &= ~0x8000;
        DC_InvalidateRange((u8*)&data_0211da40 + 0x80, 0x40);
        func_0206fd40(1, CTRDG_AGB_ROM + 0x80, (u8*)&data_0211da40 + 0x80, 0x40);
        REG_EXMEMCNT = (u16)((REG_EXMEMCNT & ~0x8000) | (phi << 15));
        func_02071c8c(&cycles);
        func_02071cf0(data_0211da0c.unk_02, &lock);

        if (*(u8*)0x027FFF9B != 0 || *(u8*)0x027FFF9A == 0) {
            int                i;
            UnkCtrdgAgbHeader* hdr  = &data_0211da40;
            UnkCtrdgInfo*      info = CTRDG_INFO;

            info->unk_00 = hdr->unk_be;
            for (i = 0; i < 3; i++) {
                info->unk_02[i] = hdr->unk_b5[i];
            }
            info->unk_06 = hdr->unk_b0;
            info->unk_08 = hdr->unk_ac;

            *(u8*)0x027FFF9B = func_02071bac() ? 1 : 0;
            *(u8*)0x027FFF9A = 1;
        }

        MI_CpuCopyU32((const u32*)0xFFFF0020, (u32*)data_0211da40.unk_04, 0x9C);
        DC_PurgeAll();
        func_02071d08(((((u32)&data_0211da40 - 0x02000000) >> 5) << 6) | 1);
        while (data_0211da0c.unk_00 != 1) {
            WaitByLoop(1);
        }
        {
            u16 dummy = REG_IME;
            REG_IME   = ime;
        }
        func_020870a4(irq);
    }
}

void func_02071f38(u32 tag, u32 data, BOOL err) {
    if ((data & 0x3F) == 1) {
        data_0211da0c.unk_00 = 1;
    } else {
        OS_Terminate();
    }
}

void func_02071f54(u32 tag, u32 data, BOOL err) {
    if ((data & 0x3F) == 17) {
        if (!data_0211da24.unk_08) {
            BOOL terminate = FALSE;
            if (data_0211da24.unk_14 != NULL) {
                terminate = data_0211da24.unk_14();
            }
            if (terminate) {
                func_02071f8c();
            }
            data_0211da24.unk_08 = TRUE;
        }
    } else {
        OS_Terminate();
    }
}

void func_02071f8c(void) {
    func_02071d08(2);
    OS_Terminate();
}

void func_02071f9c(u32 tag, u32 data, BOOL err) {
    data_0211da24.unk_00 = 0;
}
