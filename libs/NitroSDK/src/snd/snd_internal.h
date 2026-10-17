#ifndef SND_INTERNAL_H
#define SND_INTERNAL_H

#include "../sdk_internal.h"

typedef struct UnkSndCommand {
    struct UnkSndCommand* next;
    s32 id;
    u32 arg[4];
} UnkSndCommand;

typedef struct UnkSndPlayerWork {
    s16 variable[16];
    u32 tickCounter;
} UnkSndPlayerWork;

typedef struct UnkSndSharedWork {
    vu32 finishCommandTag;          // 0x00
    vu32 playerStatus;              // 0x04
    vu16 channelStatus;             // 0x08
    vu16 captureStatus;             // 0x0a
    vu32 unk_0c[5];                 // 0x0c
    UnkSndPlayerWork player[16];    // 0x20
    vs16 globalVariable[16];        // 0x260
} UnkSndSharedWork;

typedef void (*UnkSndAlarmHandler)(void* arg);

typedef struct UnkSndAlarm {
    UnkSndAlarmHandler func;
    void* arg;
    u8 id;
} UnkSndAlarm;

UnkSndCommand* func_02077e34(u32 flags);
void func_02077e90(UnkSndCommand* cmd);
BOOL func_02077eb8(u32 flags);
UnkSndCommand* func_02077d8c(u32 flags);
BOOL func_02078030(u32 tag);
s32 func_02078070(void);
s32 func_02078094(void);
s32 func_020780b8(void);
void func_020780d0(u32 tag, u32 data, BOOL err);
void func_020780e8(void);
void func_02078124(void);
UnkSndCommand* func_0207813c(void);
BOOL func_0207816c(void);
void func_02077d04(void);
void func_02077ce4(void);
void func_02077cf4(void);
void func_02077c94(s32 id, u32 arg0, u32 arg1, u32 arg2, u32 arg3);
void func_02077c78(u32 arg0, u32 arg1, u32 arg2, u32 arg3);

void func_0207819c(void);
void func_020781b8(s32 no);
u8 func_020781cc(s32 no, UnkSndAlarmHandler func, void* arg);
void func_020781ec(s32 data);

u32 func_02078258(void);
void func_02078270(UnkSndSharedWork* work);

#endif
