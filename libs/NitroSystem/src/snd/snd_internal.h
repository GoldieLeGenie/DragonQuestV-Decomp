#ifndef SND_INTERNAL_H
#define SND_INTERNAL_H

// Placeholder declarations shared by the sound system files of this range.

#include <nitro/types.h>
#include <nitro/os/cpustat.h>
#include <nitro/os/thread.h>
#include <nitro/os/mutex.h>
#include <nitro/fs/file.h>

// ---- intrusive list (link at a fixed offset inside each object) ----
typedef struct UnkList {
    /* 0x00 */ void* head;
    /* 0x04 */ void* tail;
    /* 0x08 */ u16 numObjects;
    /* 0x0A */ u16 offset;
} UnkList; // size 0xC

typedef struct UnkLink {
    /* 0x00 */ void* prev;
    /* 0x04 */ void* next;
} UnkLink;

void  func_0207e290(UnkList* list, u16 offset);                 // init list
void  func_0207e2b8(UnkList* list, void* obj);                  // append
void  func_0207e310(UnkList* list, void* target, void* obj);    // insert before target
void  func_0207e348(UnkList* list, void* obj);                  // remove
void* func_0207e384(UnkList* list, void* obj);                  // next
void* func_0207e394(UnkList* list, void* obj);                  // prev

// ---- frame heap ----
void* func_0207ea48(void* start, u32 size, u16 opt);            // create
void  func_0207ea68(void* heap);                                // destroy
void* func_0207ea70(void* heap, u32 size, int align);           // alloc
void  func_0207ea94(void* heap, int mode);                      // free
BOOL  func_0207eab4(void* heap, u32 tagName);                   // record state
BOOL  func_0207eae4(void* heap, u32 tagName);                   // free by state

// ---- file system ----
BOOL func_0207399c(FS_FileIdentifier* id, const char* path);
void func_02073868(FS_File* file);
BOOL func_020739f4(FS_File* file, FS_FileIdentifier id);
BOOL func_02073a68(FS_File* file);
BOOL func_02073b28(FS_File* file);
s32  func_02073b58(FS_File* file, void* dst, s32 len);
BOOL func_02073b64(FS_File* file, s32 offset, int origin);

// ---- memory / cache ----
void MI_CpuCopyU8(const void* src, void* dest, u32 count);
void MI_CpuSet(void* dest, u8 value, u32 count);
void func_02070224(u32 data, void* dest, u32 size);
void DC_PurgeRange(void* ptr, u32 size);
void DC_CleanRange(void* ptr, u32 size);
void DC_InvalidateRange(void* ptr, u32 size);

// ---- os ----
void func_02087688(OSThread* thread, void (*func)(void*), void* arg, void* stack, u32 stackSize, u32 prio);
void func_02087aec(void* queue, void* msgs, s32 count);
BOOL func_02087b5c(void* queue, void* msg, s32 flags);

// ---- runtime ----
u32 _u32_div_f(u32 a, u32 b);
s32 _s32_div_f(s32 a, s32 b);
u64 func_02005fe4(u32 lo, u32 hi, u32 dlo, u32 dhi);

// ---- low level sound ----
void SND_SetupChannelPcm(int ch, int format, const void* data, int loop, int loopStart, int loopLen, int volume, int shift, int timer, int pan);
void SND_SetupAlarm(int alarm, u32 tick, u32 period, void (*callback)(void*), void* arg);
void SND_SetChannelVolume(u32 chBitMask, int volume, int shift);
void SND_SetChannelPan(u32 chBitMask, int pan);
void func_02077a6c(int playerNo);
void func_02077a80(int playerNo, const void* seq, u32 offset, const void* bank);
void func_02077ac8(int playerNo, int volume);
void func_02077ab0(int playerNo, BOOL flag);
void func_02077ae8(int playerNo, u32 trackBitMask, u32 chBitMask);
void func_02077b00(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);
void func_02077b1c(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);
void func_02077c14(const void* start, const void* end);
void func_02077c2c(const void* start, const void* end);
void func_02077c44(const void* start, const void* end);
void func_02077c5c(int a, int b, int c, int d);
void func_02077eb8(int flag);
void func_02077fcc(u32 tag);
u32  func_02078010(void);
s32  func_020782b8(int volume);
void func_0207830c(void* bank, int index, void* waveArc);
void func_0207838c(void* bank);
void func_020783e0(void* waveArc);


u32  func_02078514(void* waveArc);
void* func_02078538(void* waveArc, u32 index);
void func_02078518(void* waveArc, u32 index, void* wave);
void func_0207b420(u32 capBitMask);
BOOL func_0207b404(u32 chBitMask);
BOOL func_02073258(u32 chBitMask);
int  func_0207b430(void);
void func_0207b45c(int alarm);

#endif
