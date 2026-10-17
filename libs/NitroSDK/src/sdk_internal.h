#ifndef SDK_INTERNAL_H
#define SDK_INTERNAL_H

#include <nitro/types.h>

/* ---- external functions (names from config/eur/arm9/symbols.txt) ---- */
u32 OS_DisableIRQ(void);
u32 OS_RestoreIRQ(u32 state);
u32 OS_GetIRQFlag(void);
void OS_Delay(u32 count);
void OS_Terminate(void);
void func_0208894c(void);
u32 func_02088654(void);

typedef struct UnkMutex {
    u32 unk_00[6];
} UnkMutex;
void OS_InitMutex(UnkMutex* mutex);
void OS_LockMutex(UnkMutex* mutex);
void OS_UnlockMutex(UnkMutex* mutex);

typedef struct UnkMessageQueue {
    u32 unk_00[8];
} UnkMessageQueue;
void func_02087aec(UnkMessageQueue* queue, void* buf, s32 count);
BOOL func_02087b00(UnkMessageQueue* queue, void* msg, s32 flags);
BOOL func_02087b5c(UnkMessageQueue* queue, void* msg, s32 flags);
BOOL func_02087bc4(UnkMessageQueue* queue, void* msg, s32 flags);
BOOL func_02087ad8(void);

void func_0208710c(u32 mask);
void func_02086f88(u32 mask, void* handler);
u32 func_020870c4(u32 mask);
u32 func_020870e8(u32 mask);
u32 func_020870a4(u32 mask);

void DC_InvalidateRange(void* ptr, u32 size);
void DC_CleanRange(void* ptr, u32 size);
void DC_PurgeRange(void* ptr, u32 size);

void MI_CpuCopyU8(const void* src, void* dest, u32 size);
void MI_CpuCopyU16(const void* src, void* dest, u32 size);
void MI_CpuCopyU32(const void* src, void* dest, u32 size);
void MI_CpuSet(void* dest, u8 value, u32 size);
void MI_CpuFillU16(u16 value, void* dest, u32 size);
void func_02070224(u32 value, void* dest, u32 size);
void MI_CpuFill(u32 value, void* dest, u32 size);
void func_0206fc90(u32 dmaNo, void* dest, u32 value, u32 size);
u8 func_0208a8dc(u32 value);
u16 func_02088594(void);
BOOL func_02071bac(void);

/* ---- MI streaming decompression ---- */
typedef struct UnkCompressionHeader {
    u32 compParam : 4;
    u32 compType : 4;
    u32 destSize : 24;
} UnkCompressionHeader;

typedef struct UnkUncompContextLZ {
    u8* dest;      // 0x00
    s32 destCount; // 0x04
    s32 length;    // 0x08
    u16 unk_0c;    // 0x0c
    u8 unk_0e;     // 0x0e
    u8 flags;      // 0x0f
    u8 flagIndex;  // 0x10
    u8 lengthFlg;  // 0x11
    u8 exFormat;   // 0x12
} UnkUncompContextLZ;

/* ---- PXI ---- */
typedef void (*PxiCallback)(u32 tag, u32 data, BOOL err);
void func_0207734c(void);
void func_02077354(void);
void func_02077400(u32 tag, PxiCallback callback);
BOOL func_0207744c(u32 tag, u32 proc);
s32 PXI_SendWordByFifo(u32 tag, u32 data, BOOL err);
void PXIi_HandlerRecvFifoNotEmpty(void);

#endif
