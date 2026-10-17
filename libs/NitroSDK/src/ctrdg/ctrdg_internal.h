#ifndef CTRDG_INTERNAL_H
#define CTRDG_INTERNAL_H

#include <nitro/types.h>
#include <nitro/os/thread.h>
#include <nitro/os/cpustat.h>
#include <nitro/os/cache.h>
#include <nitro/mi/cpumem.h>

/* Cartridge information kept in the shared work area (0x027FFC30). */
typedef struct UnkCtrdgInfo {
    /* 0x00 */ u16 unk_00; /* game ID (0xFFFF = none) */
    /* 0x02 */ u8  unk_02[3];
    /* 0x05 */ u8  unk_05_0 : 1; /* AGB cartridge */
    /* 0x05 */ u8  unk_05_1 : 1; /* cartridge was pulled out */
    /* 0x05 */ u8  unk_05_2 : 6;
    /* 0x06 */ u16 unk_06; /* maker code */
    /* 0x08 */ u32 unk_08; /* game code */
} UnkCtrdgInfo;

#define CTRDG_INFO ((UnkCtrdgInfo*)0x027FFC30)

/* data_0211da0c */
typedef struct UnkCtrdgCommon2 {
    /* 0x00 */ vu16 unk_00; /* ARM7 finished reading the header */
    /* 0x02 */ u16  unk_02; /* cartridge lock ID */
} UnkCtrdgCommon2;

/* data_0211da24 */
typedef BOOL (*UnkCtrdgPulledOutCallback)(void);
typedef struct UnkCtrdgState {
    /* 0x00 */ u32                       unk_00;
    /* 0x04 */ BOOL                      unk_04; /* CTRDG initialized */
    /* 0x08 */ BOOL                      unk_08; /* pull-out handled */
    /* 0x0C */ u32                       unk_0c[2];
    /* 0x14 */ UnkCtrdgPulledOutCallback unk_14;
} UnkCtrdgState;

/* Saved cartridge lock state. */
typedef struct UnkCtrdgLock {
    /* 0x00 */ u32 unk_00; /* locked by the ARM7 */
    /* 0x04 */ u32 unk_04; /* saved IRQ state */
} UnkCtrdgLock;

/* Saved cartridge access cycles. */
typedef struct UnkCtrdgCycles {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} UnkCtrdgCycles;

/* Cartridge task (0x24 bytes). */
struct UnkCtrdgTask;
typedef u32 (*UnkCtrdgTaskFunc)(struct UnkCtrdgTask* task);
typedef void (*UnkCtrdgTaskCallback)(struct UnkCtrdgTask* task);
typedef struct UnkCtrdgTask {
    /* 0x00 */ UnkCtrdgTaskFunc     unk_00;
    /* 0x04 */ UnkCtrdgTaskCallback unk_04;
    /* 0x08 */ u32                  unk_08; /* result */
    /* 0x0C */ u32                  unk_0c[5];
    /* 0x20 */ u16                  unk_20;
    /* 0x22 */ u8                   unk_22; /* busy */
    /* 0x23 */ u8                   unk_23;
} UnkCtrdgTask;

/* Cartridge task thread (data_0211db00, 0xE8 bytes). */
typedef struct UnkCtrdgThread {
    /* 0x00 */ OSThread      unk_00;
    /* 0xC0 */ UnkCtrdgTask* volatile unk_c0; /* current task */
    /* 0xC4 */ UnkCtrdgTask  unk_c4;
} UnkCtrdgThread;

extern BOOL              data_0211da08; /* cartridge access enabled */
extern UnkCtrdgCommon2   data_0211da0c;
extern UnkCtrdgState     data_0211da24;
/* Copy of the AGB cartridge header (data_0211da40, 0xC0 bytes). */
typedef struct UnkCtrdgAgbHeader {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u8  unk_04[0x9C]; /* logo */
    /* 0xA0 */ u8  unk_a0[0x0C]; /* title */
    /* 0xAC */ u32 unk_ac;       /* game code */
    /* 0xB0 */ u16 unk_b0;       /* maker code */
    /* 0xB2 */ u8  unk_b2;       /* fixed 0x96 */
    /* 0xB3 */ u8  unk_b3[2];
    /* 0xB5 */ u8  unk_b5[3];
    /* 0xB8 */ u8  unk_b8[6];
    /* 0xBE */ u16 unk_be;
} UnkCtrdgAgbHeader;

extern UnkCtrdgAgbHeader data_0211da40;
extern UnkCtrdgThread    data_0211db00;
extern UnkCtrdgThread*   data_0211dbe8; /* task thread */
extern UnkCtrdgTask      data_0211dbec;

/* external */
void OS_Terminate(void);
u32  OS_GetLockID(void);
void CpuSet(const void* src, void* dst, u32 control);
void WaitByLoop(s32 count);
s32  PXI_SendWordByFifo(u32 tag, u32 data, BOOL err);
void func_0207734c(void);
void func_02077400(u32 tag, void (*callback)(u32 tag, u32 data, BOOL err));
BOOL func_0207744c(u32 tag, BOOL arm7);
u32  func_02087354(void* lockWord);
s32  func_020872d0(u16 lockId);
void func_020872c8(u16 lockId);
void func_02088320(u32 mask, u32 flags);
u32  func_020870a4(u32 mask);
void func_0206fd40(u32 dma, const void* src, void* dst, u32 size);
void func_02087688(OSThread* thread, void (*func)(void*), void* arg, void* stack, u32 stackSize, u32 prio);
void func_02087760(void);

/* ctrdg_common.c */
void func_02071b58(void);
BOOL func_02071b80(void);
BOOL func_02071b9c(void);
BOOL func_02071bac(void);
void func_02071c58(UnkCtrdgCycles* cycles);
void func_02071c8c(const UnkCtrdgCycles* cycles);
void func_02071cb4(u16 lockId, UnkCtrdgLock* lock);
void func_02071cf0(u16 lockId, UnkCtrdgLock* lock);
void func_02071d08(u32 data);
void func_02071d38(BOOL enable);
void func_02071d70(void);
void func_02071de8(void);
void func_02071f38(u32 tag, u32 data, BOOL err);
void func_02071f54(u32 tag, u32 data, BOOL err);
void func_02071f8c(void);
void func_02071f9c(u32 tag, u32 data, BOOL err);

/* ctrdg_task.c */
void func_02071fa8(UnkCtrdgThread* thread);
void func_0207200c(UnkCtrdgTask* task);
void func_02072018(void* arg);

#endif
