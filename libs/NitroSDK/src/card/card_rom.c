#include "card_internal.h"

#pragma thumb on

/* This unit is built without loop rotation and copy propagation (see REPORT.md). */
#pragma opt_rotateloops off
#pragma opt_propagation off

u32        data_0211d7c0;                     /* ROM base offset */
UnkCardRom data_0211d7e0 ATTRIBUTE_ALIGN(32); /* ROM read state */

#define REG_CARD_CNT_ADDR  0x040001A4
#define REG_CARD_DATA_ADDR 0x04100010

/* pointer to the card ROM header copy */
u8* data_0209c20c = (u8*)0x027FFE00;

static inline u32 CARDi_GetRomControl(void) {
    return *(u32*)(data_0209c20c + 0x60);
}

static inline BOOL CARDi_NextPage(void) {
    UnkCardCommon* const p = &data_0211d1a0;
    p->unk_01c += 0x200;
    p->unk_020 += 0x200;
    return (p->unk_024 -= 0x200) != 0;
}

static inline void CARDi_ReadRomDone(void) {
    UnkCardCommon* const p = &data_0211d1a0;
    func_02071a08(func_02071644());
    p->unk_000->unk_00 = 0;
    CARDi_EndTask(p);
}

static inline u32 CARDi_GetSrcPage(void) {
    return data_0211d1a0.unk_01c & ~0x1FF;
}

/* Copies what can be served from the page cache; returns TRUE if data remains. */
BOOL func_020712e0(UnkCardRom* rom) {
    UnkCardCommon* const p    = &data_0211d1a0;
    const u32            page = CARDi_GetSrcPage();

    if (page == rom->unk_008) {
        const u32 offset = p->unk_01c - page;
        u32       len    = 0x200 - offset;
        if (len > p->unk_024) {
            len = p->unk_024;
        }
        MI_CpuCopyU8((u8*)rom->unk_020 + offset, (void*)p->unk_020, len);
        p->unk_01c += len;
        p->unk_020 += len;
        p->unk_024 -= len;
    }
    return p->unk_024 != 0;
}

/* Writes an 8-byte card command. */
void func_02071338(u32 hi, u32 lo) {
    while (*(vu32*)REG_CARD_CNT_ADDR & 0x80000000) {
    }
    *(vu8*)0x040001A1 = 0xC0;
    *(vu8*)0x040001A8 = (u8)(hi >> 24);
    *(vu8*)0x040001A9 = (u8)(hi >> 16);
    *(vu8*)0x040001AA = (u8)(hi >> 8);
    *(vu8*)0x040001AB = (u8)(hi >> 0);
    *(vu8*)0x040001AC = (u8)(lo >> 24);
    *(vu8*)0x040001AD = (u8)(lo >> 16);
    *(vu8*)0x040001AE = (u8)(lo >> 8);
    *(vu8*)0x040001AF = (u8)(lo >> 0);
}

/* Starts the DMA read of one page. */
void func_02071374(void) {
    UnkCardCommon* const p   = &data_0211d1a0;
    UnkCardRom* const    rom = &data_0211d7e0;

    func_02070884(p->unk_028, (void*)REG_CARD_DATA_ADDR, (void*)p->unk_020, 0x200);
    {
        const u32 src = p->unk_01c;
        func_02071338(0xB7000000 | (src >> 8), src << 24);
    }
    *(vu32*)REG_CARD_CNT_ADDR = rom->unk_004;
}

/* Card DMA interrupt handler. */
void func_020713b0(void) {
    func_0206feb0(data_0211d1a0.unk_028);
    if (!CARDi_NextPage()) {
        func_020870e8(0x80000);
        func_0208710c(0x80000);
        CARDi_ReadRomDone();
    } else {
        func_02071374();
    }
}

/* Starts a DMA transfer if the request allows it. */
BOOL func_0207144c(UnkCardRom* rom) {
    u32                  dtcm;
    u32                  len;
    BOOL                 ret;
    BOOL                 aligned_ok;
    BOOL                 dma_ok;
    u32                  dst;
    UnkCardCommon* const p = &data_0211d1a0;
    BOOL                 usable;
    u32                  mis;
    BOOL                 overlap;
    BOOL                 itcm;
    u32                  end;

    dst        = p->unk_020;
    len        = p->unk_024;
    ret        = FALSE;
    aligned_ok = FALSE;
    dma_ok     = FALSE;
    usable     = FALSE;
    mis        = dst & 0x1F;

    if (mis == 0 && p->unk_028 <= 3) {
        usable = TRUE;
    }
    if (usable) {
        dtcm = func_020882ec();
        end  = dst + len;
        overlap = TRUE;
        itcm    = FALSE;
        if (end > 0x01FF8000 && dst < 0x02000000) {
            itcm = overlap;
        }
        if (!itcm && !(dtcm < end && dtcm + 0x4000 > dst)) {
            overlap = FALSE;
        }
        if (!overlap) {
            dma_ok = TRUE;
        }
    }
    if (dma_ok) {
        if (((p->unk_01c | len) & 0x1FF) == 0) {
            aligned_ok = TRUE;
        }
    }
    if (aligned_ok && len != 0) {
        ret = TRUE;
    }
    rom->unk_004 = (CARDi_GetRomControl() & ~0x07000000) | 0xA1000000;

    if (ret) {
        ENTER_CRITICAL_SECTION();
        if (len < p->unk_118[0]) {
            IC_InvalidateRange((void*)dst, len);
        } else {
            IC_InvalidateAll();
        }
        if (len < p->unk_118[1]) {
            if (mis != 0) {
                dst -= mis;
                DC_CleanRange((void*)dst, 0x20);
                DC_CleanRange((void*)(dst + len), 0x20);
                len += 0x20;
            }
            DC_InvalidateRange((void*)dst, len);
            DC_DrainWriteBuffer();
        } else {
            DC_PurgeAll();
        }
        func_02086f88(0x80000, func_020713b0);
        func_0208710c(0x80000);
        func_020870c4(0x80000);
        LEAVE_CRITICAL_SECTION();
        func_02071374();
    }
    return ret;
}

/* Reads the request with the CPU, page by page. */
#pragma opt_propagation on
void func_02071588(UnkCardRom* rom) {
    UnkCardCommon* const p = &data_0211d1a0;
    u32* const cache = rom->unk_020;

    for (;;) {
        const u32 page = p->unk_01c & ~0x1FF;
        u32*      dst;

        if (page != p->unk_01c || ((u32)(dst = (u32*)p->unk_020) & 3) != 0 || p->unk_024 < 0x200) {
            rom->unk_008 = page;
            dst          = cache;
        }
        func_02071338(0xB7000000 | (page >> 8), page << 24);
        *(vu32*)REG_CARD_CNT_ADDR = rom->unk_004;
        {
            u32 i = 0;
            u32 ctrl;
            do {
                ctrl = *(vu32*)REG_CARD_CNT_ADDR;
                if (ctrl & 0x800000) {
                    const u32 data = *(vu32*)REG_CARD_DATA_ADDR;
                    if (i * 4 < 0x200) {
                        dst[i++] = data;
                    }
                }
            } while (ctrl & 0x80000000);
        }
        if (dst == (u32*)p->unk_020) {
            data_0211d1a0.unk_01c += 0x200;
            data_0211d1a0.unk_020 += 0x200;
            if ((data_0211d1a0.unk_024 -= 0x200) == 0) {
                break;
            }
        } else if (!func_020712e0(rom)) {
            break;
        }
    }
}

#pragma opt_propagation off
/* Reads the card ID. */
u32 func_02071644(void) {
    func_02071338(0xB8000000, 0);
    *(vu32*)REG_CARD_CNT_ADDR = ((CARDi_GetRomControl() & ~0x07000000) | 0xA7000000) & ~0x1FFF;
    while (!(*(vu32*)REG_CARD_CNT_ADDR & 0x800000)) {
    }
    return *(vu32*)REG_CARD_DATA_ADDR;
}

/* Card thread task for CPU reads. */
void func_0207168c(UnkCardCommon* common) {
    UnkCardRom* const rom = &data_0211d7e0;
    if (func_020712e0(rom)) {
        rom->unk_000(rom);
    }
    CARDi_ReadRomDone();
}

void CARDi_ReadRom(u32 dma, const void* src, void* dst, u32 len, UnkCardCallback callback, void* arg, BOOL async) {
    UnkCardRom* const    rom = &data_0211d7e0;
    UnkCardCommon* const p   = &data_0211d1a0;

    func_02070c54();
    CARDi_WaitAndLock(p, callback, arg);
    p->unk_028 = dma;
    p->unk_01c = (u32)src + data_0211d7c0;
    p->unk_020 = (u32)dst;
    p->unk_024 = len;
    if (dma <= 3) {
        func_0206feb0(dma);
    }
    if (func_0207144c(rom)) {
        if (!async) {
            func_020717f8();
        }
    } else if (async) {
        func_02070a90(func_0207168c);
    } else {
        p->unk_104 = OS_GetCurrentThread();
        func_0207168c(p);
    }
}

void CARD_Init(void) {
    UnkCardCommon* const p = &data_0211d1a0;

    if (p->unk_114 == 0) {
        p->unk_114           = 1;
        p->unk_024           = 0;
        p->unk_020           = 0;
        p->unk_01c           = 0;
        p->unk_028           = (u32)-1;
        p->unk_038           = NULL;
        p->unk_03c           = NULL;
        data_0211d7c0 = 0;
        func_02070b7c();
        data_0211d7e0.unk_000 = (void (*)(UnkCardRom*))func_02071800();
        func_02071948();
    }
}

BOOL func_020717f8(void) {
    return func_02070c70();
}

void* func_02071800(void) {
    return (void*)func_02071588;
}
