#include "gx_internal.h"

/* data_0211e0b8 (0x1c bytes): extended palette load state */
typedef struct {
    /* 0x00 */ s32 subBgExtPltt;
    /* 0x04 */ u32 objExtPlttAddr;
    /* 0x08 */ s32 objExtPltt;
    /* 0x0c */ u32 bgExtPlttOffset;
    /* 0x10 */ u32 bgExtPlttAddr;
    /* 0x14 */ s32 bgExtPltt;
    /* 0x18 */ s32 subObjExtPltt;
} UnkGxExtPlttState;
UnkGxExtPlttState data_0211e0b8;

void MI_CpuCopyU16(const void *src, void *dest, u32 size);
void MI_CpuCopyU32(const void *src, void *dest, u32 size);
void func_0206fcf0(u32 dmaNo, const void *src, void *dest, u32 size);
void func_0206fd40(u32 dmaNo, const void *src, void *dest, u32 size);
void func_0206fe0c(u32 dmaNo, const void *src, void *dest, u32 size, void (*callback)(void *), void *arg);

s32 GX_ResetBankForBgExtPltt(void);
s32 GX_ResetBankForOBJExtPltt(void);
s32 GX_ResetBankForSubBgExtPltt(void);
s32 GX_ResetBankForSubObjExtPltt(void);
void GX_SetBankForBgExtPltt(s32 bgExtPltt);
void GX_SetBankForObjExtPltt(s32 objExtPltt);
void GX_SetBankForSubBgExtPltt(s32 subBgExtPltt);
void GX_SetBankForSubObjExtPltt(s32 subObjExtPltt);

void *func_02075564(void);
void *func_02075598(void);
void *func_020755b8(void);
void *func_020755ec(void);
void *func_0207560c(void);
void *func_02075690(void);
void *func_02075704(void);
void *func_02075788(void);
void *func_020757fc(void);
void *func_02075830(void);
void *func_02075850(void);
void *func_02075884(void);
void *func_020758a4(void);
void *func_020758f4(void);
void *func_02075934(void);
void *func_0207598c(void);

/* Copy with DMA when a DMA channel is set and the size is large enough, else with the CPU */
static inline void UnkGxCopy16(u32 dmaNo, const void *src, void *dest, u32 size) {
    if (dmaNo != -1 && size > 0x1c) {
        func_0206fd40(dmaNo, src, dest, size);
    } else {
        MI_CpuCopyU16(src, dest, size);
    }
}

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

static inline void *UnkGetObjCharPtr(void) {
    return (void *)0x6400000;
}

static inline void *UnkGetSubObjCharPtr(void) {
    return (void *)0x6600000;
}

void GX_LoadBGPltt(const void *src, u32 offset, u32 size) {
    UnkGxCopy16(data_0209c504, src, (void *)(0x5000000 + offset), size);
}

void GXS_LoadBGPltt(const void *src, u32 offset, u32 size) {
    UnkGxCopy16(data_0209c504, src, (void *)(0x5000400 + offset), size);
}

void GX_LoadOBJPltt(const void *src, u32 offset, u32 size) {
    UnkGxCopy16(data_0209c504, src, (void *)(0x5000200 + offset), size);
}

void GXS_LoadOBJPltt(const void *src, u32 offset, u32 size) {
    UnkGxCopy16(data_0209c504, src, (void *)(0x5000600 + offset), size);
}

void GX_LoadOAM(const void *src, u32 offset, u32 size) {
    UnkGxCopy32(data_0209c504, src, (void *)(0x7000000 + offset), size);
}

void GXS_LoadOAM(const void *src, u32 offset, u32 size) {
    UnkGxCopy32(data_0209c504, src, (void *)(0x7000400 + offset), size);
}

/* OBJ character data */
void func_02076420(const void *src, u32 offset, u32 size) {
    u8 *base = (u8 *)UnkGetObjCharPtr();
    UnkGxCopy32(data_0209c504, src, base + offset, size);
}

void func_02076478(const void *src, u32 offset, u32 size) {
    u8 *base = (u8 *)UnkGetSubObjCharPtr();
    UnkGxCopy32(data_0209c504, src, base + offset, size);
}

/* BG screen data */
void func_020764d0(const void *src, u32 offset, u32 size) {
    void *dest = func_02075564();
    UnkGxCopy16(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_02076530(const void *src, u32 offset, u32 size) {
    void *dest = func_02075598();
    UnkGxCopy16(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_02076590(const void *src, u32 offset, u32 size) {
    void *dest = func_020755b8();
    UnkGxCopy16(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_020765f0(const void *src, u32 offset, u32 size) {
    void *dest = func_020755ec();
    UnkGxCopy16(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_02076650(const void *src, u32 offset, u32 size) {
    void *dest = func_0207560c();
    UnkGxCopy16(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_020766b0(const void *src, u32 offset, u32 size) {
    void *dest = func_02075690();
    UnkGxCopy16(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_02076710(const void *src, u32 offset, u32 size) {
    void *dest = func_02075704();
    UnkGxCopy16(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_02076770(const void *src, u32 offset, u32 size) {
    void *dest = func_02075788();
    UnkGxCopy16(data_0209c504, src, (u8 *)dest + offset, size);
}

/* BG character data */
void func_020767d0(const void *src, u32 offset, u32 size) {
    void *dest = func_020757fc();
    UnkGxCopy32(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_02076830(const void *src, u32 offset, u32 size) {
    void *dest = func_02075830();
    UnkGxCopy32(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_02076890(const void *src, u32 offset, u32 size) {
    void *dest = func_02075850();
    UnkGxCopy32(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_020768f0(const void *src, u32 offset, u32 size) {
    void *dest = func_02075884();
    UnkGxCopy32(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_02076950(const void *src, u32 offset, u32 size) {
    void *dest = func_020758a4();
    UnkGxCopy32(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_020769b0(const void *src, u32 offset, u32 size) {
    void *dest = func_020758f4();
    UnkGxCopy32(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_02076a10(const void *src, u32 offset, u32 size) {
    void *dest = func_02075934();
    UnkGxCopy32(data_0209c504, src, (u8 *)dest + offset, size);
}

void func_02076a70(const void *src, u32 offset, u32 size) {
    void *dest = func_0207598c();
    UnkGxCopy32(data_0209c504, src, (u8 *)dest + offset, size);
}

void GX_BeginLoadBGExtPltt(void) {
    data_0211e0b8.bgExtPltt = GX_ResetBankForBgExtPltt();

    switch (data_0211e0b8.bgExtPltt) {
    case 0x00:
        break;
    case 0x10:
        data_0211e0b8.bgExtPlttAddr   = 0x6880000;
        data_0211e0b8.bgExtPlttOffset = 0;
        break;
    case 0x40:
        data_0211e0b8.bgExtPlttAddr   = 0x6894000;
        data_0211e0b8.bgExtPlttOffset = 0x4000;
        break;
    case 0x20:
    case 0x60:
        data_0211e0b8.bgExtPlttAddr   = 0x6890000;
        data_0211e0b8.bgExtPlttOffset = 0;
        break;
    default:
        break;
    }
}

void GX_LoadBGExtPltt(const void *src, u32 destSlotAddr, u32 size) {
    UnkGxCopy32Async(data_0209c504, src,
                     (void *)(data_0211e0b8.bgExtPlttAddr + destSlotAddr - data_0211e0b8.bgExtPlttOffset), size);
}

void GX_EndLoadBGExtPltt(void) {
    if (data_0209c504 != -1) {
        func_0206fe6c(data_0209c504);
    }
    GX_SetBankForBgExtPltt(data_0211e0b8.bgExtPltt);
    data_0211e0b8.bgExtPltt       = 0;
    data_0211e0b8.bgExtPlttAddr   = 0;
    data_0211e0b8.bgExtPlttOffset = 0;
}

void GX_BeginLoadOBJExtPltt(void) {
    data_0211e0b8.objExtPltt = GX_ResetBankForOBJExtPltt();

    switch (data_0211e0b8.objExtPltt) {
    case 0x00:
        break;
    case 0x40:
        data_0211e0b8.objExtPlttAddr = 0x6894000;
        break;
    case 0x20:
        data_0211e0b8.objExtPlttAddr = 0x6890000;
        break;
    }
}

void GX_LoadOBJExtPltt(const void *src, u32 destSlotAddr, u32 size) {
    UnkGxCopy32Async(data_0209c504, src, (void *)(data_0211e0b8.objExtPlttAddr + destSlotAddr), size);
}

void GX_EndLoadOBJExtPltt(void) {
    if (data_0209c504 != -1) {
        func_0206fe6c(data_0209c504);
    }
    GX_SetBankForObjExtPltt(data_0211e0b8.objExtPltt);
    data_0211e0b8.objExtPltt     = 0;
    data_0211e0b8.objExtPlttAddr = 0;
}

void GXS_BeginLoadBGExtPltt(void) {
    data_0211e0b8.subBgExtPltt = GX_ResetBankForSubBgExtPltt();
}

void GXS_LoadBGExtPltt(const void *src, u32 destSlotAddr, u32 size) {
    UnkGxCopy32Async(data_0209c504, src, (void *)(0x6898000 + destSlotAddr), size);
}

void GXS_EndLoadBGExtPltt(void) {
    if (data_0209c504 != -1) {
        func_0206fe6c(data_0209c504);
    }
    GX_SetBankForSubBgExtPltt(data_0211e0b8.subBgExtPltt);
    data_0211e0b8.subBgExtPltt = 0;
}

void GXS_BeginLoadOBJExtPltt(void) {
    data_0211e0b8.subObjExtPltt = GX_ResetBankForSubObjExtPltt();
}

void GXS_LoadOBJExtPltt(const void *src, u32 destSlotAddr, u32 size) {
    UnkGxCopy32Async(data_0209c504, src, (void *)(0x68a0000 + destSlotAddr), size);
}

void GXS_EndLoadOBJExtPltt(void) {
    if (data_0209c504 != -1) {
        func_0206fe6c(data_0209c504);
    }
    GX_SetBankForSubObjExtPltt(data_0211e0b8.subObjExtPltt);
    data_0211e0b8.subObjExtPltt = 0;
}
