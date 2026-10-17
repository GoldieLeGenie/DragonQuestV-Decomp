#include "os_internal.h"

#pragma thumb on

#define LOCK_INIT_BUF      ((UnkLockWord*)0x027ffff0)
#define LOCK_CARTRIDGE_BUF ((UnkLockWord*)0x027fffe8)
#define LOCK_CARD_BUF      ((UnkLockWord*)0x027fffe0)
#define LOCK_ID_FLAG       ((u32*)0x027fffb0)
#define LOCK_SHARED_AREA   ((void*)0x027fffc0)

#define LOCK_ID_INIT_ARM9 0x7e
#define LOCK_ID_INIT_ARM7 0x7f


// Initializes the lock system shared with the ARM7
void func_02087158(void) {
    static BOOL data_02127bcc;
    UnkLockWord* lockp = LOCK_INIT_BUF;

    if (data_02127bcc) {
        return;
    }
    data_02127bcc = TRUE;

    lockp->lockFlag = 0;
    func_02087204(LOCK_ID_INIT_ARM9, lockp, NULL);

    while (lockp->extension != 0) {
        WaitByLoop(0x400);
    }

    LOCK_ID_FLAG[0] = 0xffffffff;
    LOCK_ID_FLAG[1] = 0xffff0000;

    func_02070224(0, LOCK_SHARED_AREA, 0x28);

    REG_EXMEM_CNT |= 0x800;
    REG_EXMEM_CNT |= 0x80;

    func_02087258(LOCK_ID_INIT_ARM9, lockp, NULL);
    func_02087204(LOCK_ID_INIT_ARM7, lockp, NULL);
}

// Locks a lock word, spinning until it is free
s32 func_020871d8(u16 lockID, UnkLockWord* lockp, void (*ctrlFunc)(void), BOOL disableFiq) {
    s32 lastLockFlag;
    while ((lastLockFlag = func_02087264(lockID, lockp, ctrlFunc, disableFiq)) > 0) {
        WaitByLoop(0x400);
    }
    return lastLockFlag;
}

s32 func_02087204(u16 lockID, UnkLockWord* lockp, void (*ctrlFunc)(void)) {
    return func_020871d8(lockID, lockp, ctrlFunc, FALSE);
}

// Unlocks a lock word
s32 func_02087210(u16 lockID, UnkLockWord* lockp, void (*ctrlFunc)(void), BOOL disableFiq) {
    u32 prev;

    if (lockID != lockp->ownerID) {
        return -2;
    }

    if (disableFiq) {
        prev = OS_DisableFIQ();
    } else {
        prev = OS_DisableIRQ();
    }

    lockp->ownerID = 0;
    if (ctrlFunc) {
        ctrlFunc();
    }
    lockp->lockFlag = 0;

    if (disableFiq) {
        OS_RestoreFIQ(prev);
    } else {
        OS_RestoreIRQ(prev);
    }
    return 0;
}

s32 func_02087258(u16 lockID, UnkLockWord* lockp, void (*ctrlFunc)(void)) {
    return func_02087210(lockID, lockp, ctrlFunc, FALSE);
}

// Tries to lock a lock word once
s32 func_02087264(u16 lockID, UnkLockWord* lockp, void (*ctrlFunc)(void), BOOL disableFiq) {
    s32 lastLockFlag;
    u32 prev;

    if (disableFiq) {
        prev = OS_DisableFIQ();
    } else {
        prev = OS_DisableIRQ();
    }

    lastLockFlag = func_02070618(lockID, &lockp->lockFlag);
    if (lastLockFlag == 0) {
        if (ctrlFunc) {
            ctrlFunc();
        }
        lockp->ownerID = lockID;
    }

    if (disableFiq) {
        OS_RestoreFIQ(prev);
    } else {
        OS_RestoreIRQ(prev);
    }
    return lastLockFlag;
}

s32 func_020872b0(u16 lockID) {
    return func_02087210(lockID, LOCK_CARTRIDGE_BUF, func_020872f8, TRUE);
}

// clang-format off
asm s32 func_020872c8(u16 lockID) {
    ldr r1, =func_020872b0
    bx r1
}
// clang-format on

s32 func_020872d0(u16 lockID) {
    return func_02087264(lockID, LOCK_CARTRIDGE_BUF, func_020872e8, TRUE);
}

void func_020872e8(void) {
    REG_EXMEM_CNT = (u16)(REG_EXMEM_CNT & ~0x80);
}

void func_020872f8(void) {
    REG_EXMEM_CNT |= 0x80;
}

s32 func_02087308(u16 lockID) {
    return func_02087204(lockID, LOCK_CARD_BUF, func_02087330);
}

s32 func_0208731c(u16 lockID) {
    return func_02087258(lockID, LOCK_CARD_BUF, func_02087344);
}

void func_02087330(void) {
    REG_EXMEM_CNT &= ~0x800;
}

void func_02087344(void) {
    REG_EXMEM_CNT |= 0x800;
}

u16 func_02087354(UnkLockWord* lockp) {
    return lockp->ownerID;
}

#pragma thumb off

// Allocates a lock ID from the shared ID bit field
// clang-format off
asm s32 OS_GetLockID(void) {
    ldr r3, =0x027fffb0
    ldr r1, [r3]
    clz r2, r1
    cmp r2, #0x20
    bne @x1a
    b @x1b
@x1a:
    mov r0, #0x40
@x1b:
    bne _found
    add r3, r3, #4
    ldr r1, [r3]
    clz r2, r1
    cmp r2, #0x20
    ldr r0, =0xfffffffd
    beq @x2a
    b @x2b
@x2a:
    bx lr
@x2b:
    mov r0, #0x60
_found:
    add r0, r0, r2
    mov r1, #0x80000000
    mov r1, r1, lsr r2
    ldr r2, [r3]
    bic r2, r2, r1
    str r2, [r3]
    bx lr
}
// clang-format on
