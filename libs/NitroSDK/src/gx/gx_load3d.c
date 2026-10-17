#include "gx_internal.h"

/* data_0211e0d4 (0x20 bytes): texture / texture palette / clear image load state */
typedef struct {
    /* 0x00 */ s32 clearImageBank;
    /* 0x04 */ u32 texStartAddr;
    /* 0x08 */ u32 texPlttStartAddr;
    /* 0x0c */ s32 texPlttBank;
    /* 0x10 */ u32 clearImageAddr;
    /* 0x14 */ s32 texBank;
    /* 0x18 */ u32 texStartAddr2;
    /* 0x1c */ u32 texSize1;
} UnkGxLoad3dState;
UnkGxLoad3dState data_0211e0d4;

/* texture palette start address per bank combination (in 4KB units) */
const u16 data_0208df30[8] = {0x0000, 0x6880, 0x6890, 0x6880, 0x6894, 0x0000, 0x6890, 0x6880};

/* per texture bank combination: start address, second block address and first block size (in 4KB units) */
const u16 data_0208df40[16][3] = {
    {0x0000, 0x0000, 0x00}, {0x6800, 0x0000, 0x00}, {0x6820, 0x0000, 0x00}, {0x6800, 0x0000, 0x00},
    {0x6840, 0x0000, 0x00}, {0x6800, 0x6840, 0x20}, {0x6820, 0x0000, 0x00}, {0x6800, 0x0000, 0x00},
    {0x6860, 0x0000, 0x00}, {0x6800, 0x6860, 0x20}, {0x6820, 0x6860, 0x20}, {0x6800, 0x6860, 0x40},
    {0x6840, 0x0000, 0x00}, {0x6800, 0x6840, 0x20}, {0x6820, 0x0000, 0x00}, {0x6800, 0x0000, 0x00},
};

void MI_CpuCopyU32(const void *src, void *dest, u32 size);
void func_0206fcf0(u32 dmaNo, const void *src, void *dest, u32 size);
void func_0206fe0c(u32 dmaNo, const void *src, void *dest, u32 size, void (*callback)(void *), void *arg);

s32 GX_ResetBankForTex(void);
s32 func_020753d0(void);
s32 func_020753e4(void);
void GX_SetBankForTex(s32 tex);
void GX_SetBankForTexPltt(s32 texPltt);
void GX_SetBankForClearImage(s32 clearImage);

static inline void UnkGxCopy32(u32 dmaNo, const void *src, void *dest, u32 size) {
    if (dmaNo != -1 && size > 0x30) {
        func_0206fcf0(dmaNo, src, dest, size);
    } else {
        MI_CpuCopyU32(src, dest, size);
    }
}

static inline void UnkGxCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size) {
    if (dmaNo != -1) {
        func_0206fe0c(dmaNo, src, dest, size, NULL, NULL);
    } else {
        MI_CpuCopyU32(src, dest, size);
    }
}

static inline void UnkGxWaitDma(u32 dmaNo) {
    if (dmaNo != -1) {
        func_0206fe6c(dmaNo);
    }
}

void func_02076e98(void) {
    s32 bank = GX_ResetBankForTex();
    data_0211e0d4.texBank       = bank;
    data_0211e0d4.texStartAddr  = data_0208df40[bank][0] << 12;
    data_0211e0d4.texStartAddr2 = data_0208df40[bank][1] << 12;
    data_0211e0d4.texSize1      = data_0208df40[bank][2] << 12;
}

void func_02076ef4(const void *src, u32 destSlotAddr, u32 size) {
    void *dest;

    if (data_0211e0d4.texStartAddr2 == 0) {
        dest = (void *)(data_0211e0d4.texStartAddr + destSlotAddr);
    } else if (destSlotAddr + size < data_0211e0d4.texSize1) {
        dest = (void *)(data_0211e0d4.texStartAddr + destSlotAddr);
    } else if (destSlotAddr >= data_0211e0d4.texSize1) {
        dest = (void *)(data_0211e0d4.texStartAddr2 + destSlotAddr - data_0211e0d4.texSize1);
    } else {
        void *dest2 = (void *)data_0211e0d4.texStartAddr2;
        u32 size1   = data_0211e0d4.texSize1 - destSlotAddr;
        UnkGxCopy32(data_0209c504, src, (void *)(data_0211e0d4.texStartAddr + destSlotAddr), size1);
        UnkGxCopy32Async(data_0209c504, (u8 *)src + size1, dest2, size - size1);
        return;
    }
    UnkGxCopy32Async(data_0209c504, src, dest, size);
}

void func_02077034(void) {
    UnkGxWaitDma(data_0209c504);
    GX_SetBankForTex(data_0211e0d4.texBank);
    data_0211e0d4.texSize1      = 0;
    data_0211e0d4.texStartAddr2 = 0;
    data_0211e0d4.texStartAddr  = 0;
    data_0211e0d4.texBank       = 0;
}

void func_02077080(void) {
    s32 bank = func_020753d0();
    data_0211e0d4.texPlttBank      = bank;
    data_0211e0d4.texPlttStartAddr = data_0208df30[bank >> 4] << 12;
}

void func_020770b4(const void *src, u32 destSlotAddr, u32 size) {
    UnkGxCopy32Async(data_0209c504, src, (void *)(data_0211e0d4.texPlttStartAddr + destSlotAddr), size);
}

void func_02077120(void) {
    UnkGxWaitDma(data_0209c504);
    GX_SetBankForTexPltt(data_0211e0d4.texPlttBank);
    data_0211e0d4.texPlttBank      = 0;
    data_0211e0d4.texPlttStartAddr = 0;
}

void func_02077164(void) {
    data_0211e0d4.clearImageBank = func_020753e4();

    switch (data_0211e0d4.clearImageBank) {
    case 0x02:
    case 0x03:
        data_0211e0d4.clearImageAddr = 0x6800000;
        break;
    case 0x08:
    case 0x0c:
        data_0211e0d4.clearImageAddr = 0x6840000;
        break;
    case 0x01:
        data_0211e0d4.clearImageAddr = 0x67e0000;
        break;
    case 0x04:
        data_0211e0d4.clearImageAddr = 0x6820000;
        break;
    default:
        break;
    }
}

void func_020771f4(const void *src, u32 size) {
    UnkGxCopy32Async(data_0209c504, src, (void *)data_0211e0d4.clearImageAddr, size);
}

void func_0207725c(const void *src, u32 size) {
    UnkGxCopy32Async(data_0209c504, src, (void *)(data_0211e0d4.clearImageAddr + 0x20000), size);
}

void func_020772c8(void) {
    UnkGxWaitDma(data_0209c504);
    GX_SetBankForClearImage(data_0211e0d4.clearImageBank);
    data_0211e0d4.clearImageBank = 0;
    data_0211e0d4.clearImageAddr = 0;
}
