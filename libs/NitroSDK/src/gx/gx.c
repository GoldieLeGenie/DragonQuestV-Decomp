#include "gx_internal.h"

u16 data_0209c500 = TRUE;
u32 data_0209c504 = 3;

u16 data_0211e09a; /* GX lock id */
u16 data_0211e098; /* saved display mode */

void GX_Init(void) {
    REG_POWER_CNT |= 0x8000;
    REG_POWER_CNT = (REG_POWER_CNT & ~0x20e) | 0x20e;
    REG_POWER_CNT |= 1;
    func_020743f4();

    while (data_0211e09a == 0) {
        s32 lockId = OS_GetLockID();
        if (lockId == -3) {
            OS_Terminate();
        }
        data_0211e09a = lockId;
    }

    REG_DISPSTAT = 0;
    REG_DISPCNT  = 0;

    if (data_0209c504 != -1) {
        func_0206fc90(data_0209c504, (void *)&REG_BG0CNT, 0, 0x60);
        REG_MASTER_BRIGHT = 0;
        func_0206fc90(data_0209c504, (void *)&REG_DISPCNT_SUB, 0, 0x70);
    } else {
        func_02070224(0, (void *)&REG_BG0CNT, 0x60);
        REG_MASTER_BRIGHT = 0;
        func_02070224(0, (void *)&REG_DISPCNT_SUB, 0x70);
    }

    REG_BG2PA     = 0x100;
    REG_BG2PD     = 0x100;
    REG_BG3PA     = 0x100;
    REG_BG3PD     = 0x100;
    REG_BG2PA_SUB = 0x100;
    REG_BG2PD_SUB = 0x100;
    REG_BG3PA_SUB = 0x100;
    REG_BG3PD_SUB = 0x100;
}

s32 GX_VBlankIntr(BOOL enable) {
    s32 prev = REG_DISPSTAT & 8;
    if (enable) {
        REG_DISPSTAT |= 8;
    } else {
        REG_DISPSTAT &= ~8;
    }
    return prev;
}

void GX_DispOff(void) {
    u32 cnt = REG_DISPCNT;
    data_0209c500 = FALSE;
    data_0211e098 = (cnt & 0x30000) >> 16;
    REG_DISPCNT = cnt & ~0x30000;
}

void GX_DispOn(void) {
    data_0209c500 = TRUE;
    if (data_0211e098 != 0) {
        REG_DISPCNT = (REG_DISPCNT & ~0x30000) | (data_0211e098 << 16);
    } else {
        REG_DISPCNT |= 0x10000;
    }
}

void GX_SetGraphicsMode(u32 dispMode, u32 bgMode, u32 bg0_2d3d) {
    u32 cnt = REG_DISPCNT;

    data_0211e098 = dispMode;
    if (!data_0209c500) {
        dispMode = 0;
    }
    REG_DISPCNT = (cnt & ~0xf000f) | (dispMode << 16) | bgMode | (bg0_2d3d << 3);
    if (data_0211e098 == 0) {
        data_0209c500 = FALSE;
    }
}

void GXS_SetGraphicsMode(u32 bgMode) {
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~7) | bgMode;
}

void func_0207438c(vu16 *reg, s32 brightness) {
    if (brightness == 0) {
        *reg = 0;
    } else if (brightness > 0) {
        *reg = brightness | 0x4000;
    } else {
        *reg = -brightness | 0x8000;
    }
}

u32 func_020743b4(u32 dmaNo) {
    u32 prev = data_0209c504;
    u32 e;
    if (prev != -1) {
        func_0206fe6c(prev);
    }
    e = OS_DisableIRQ();
    data_0209c504 = dmaNo;
    OS_RestoreIRQ(e);
    return prev;
}
