#ifndef H_OS_H_H
#define H_OS_H_H

#include <nitro/types.h>
#include <nitro/reg.h>
#include <nitro/os/cpustat.h>
#include <stdarg.h>

// ---------------------------------------------------------------- externals
void WaitByLoop(s32 count);                                  // 0x02000074 (thumb, svc)
void func_02070224(u32 data, void* dst, u32 size);           // 32-bit fill
s32  func_02067b80(u32 value, void* dst);                    // atomic word swap
void CP_SaveContext(void* context);                          // 0x0205e8c0
void CPi_RestoreContext(void* context);                      // 0x0205e900
void OS_Terminate(void);                                     // 0x0207a058
void func_0208894c(void);                                    // halt

// ---------------------------------------------------------------- interrupts
typedef void (*UnkIrqFunction)(void);

typedef struct UnkIrqCallbackInfo {
    /* 0x00 */ void (*func)(void*);
    /* 0x04 */ u32   enable;
    /* 0x08 */ void* arg;
} UnkIrqCallbackInfo; // size 0xc

typedef struct UnkThreadQueue UnkThreadQueue;
struct UnkThreadQueue {
    void* head;
    void* tail;
};

extern UnkIrqFunction     data_027e0000[22];  // DTCM IRQ handler table
extern UnkThreadQueue     data_027e0060;      // IRQ thread queue (DTCM)
extern UnkIrqCallbackInfo data_02127b6c[8];   // DMA (0..3) + timer (4..7) callbacks

void OS_InitIRQQueue(void);
void func_02086f88(u32 mask, UnkIrqFunction func);
UnkIrqFunction func_02086fe4(u32 mask);
void func_02087040(u32 dmaNo, void (*func)(void*), void* arg);
void func_02087074(u32 timerNo, void (*func)(void*), void* arg);
u32  func_020870a4(u32 mask);
u32  func_020870c4(u32 mask);
u32  func_020870e8(u32 mask);
u32  func_0208710c(u32 mask);
void func_0208712c(void);

// ---------------------------------------------------------------- spin locks
typedef struct UnkLockWord {
    /* 0x00 */ u32 lockFlag;
    /* 0x04 */ u16 ownerID;
    /* 0x06 */ u16 extension;
} UnkLockWord;

void func_02087158(void);
s32  func_020871d8(u16 lockID, UnkLockWord* lockp, void (*ctrlFunc)(void), BOOL disableFiq);
s32  func_02087204(u16 lockID, UnkLockWord* lockp, void (*ctrlFunc)(void));
s32  func_02087210(u16 lockID, UnkLockWord* lockp, void (*ctrlFunc)(void), BOOL disableFiq);
s32  func_02087258(u16 lockID, UnkLockWord* lockp, void (*ctrlFunc)(void));
s32  func_02087264(u16 lockID, UnkLockWord* lockp, void (*ctrlFunc)(void), BOOL disableFiq);
s32  func_020872b0(u16 lockID);
s32  func_020872c8(u16 lockID);
s32  func_020872d0(u16 lockID);
void func_020872e8(void);
void func_020872f8(void);
s32  func_02087308(u16 lockID);
s32  func_0208731c(u16 lockID);
void func_02087330(void);
void func_02087344(void);
u16  func_02087354(UnkLockWord* lockp);
s32  OS_GetLockID(void);

// ---------------------------------------------------------------- printf
int func_02079420(char* dst, u32 len, const char* fmt, va_list vlist); // formatter (std)
int func_020873c0(char* dst, u32 len, const char* fmt, ...);
int func_020873dc(char* dst, u32 len, const char* fmt, va_list vlist);

#endif
