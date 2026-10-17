#include "../sdk_internal.h"

#pragma thumb on

/* this file is built without IR loop-invariant code motion: in func_02078fb0 the key argument of the
   sleep request is hoisted out of the retry loop by the back end, after the wake-up data */
#pragma opt_loop_invariants off

typedef void (*UnkPmCallback)(u32 result, void* arg);
typedef void (*UnkPmSleepCallback)(void* arg);

typedef struct UnkPmCallbackInfo {
    UnkPmSleepCallback func;
    void* arg;
    struct UnkPmCallbackInfo* next;
} UnkPmCallbackInfo;

typedef struct UnkPmRegisterRead {
    u16 done;
    u16 unk_02;
    u16* buffer;
} UnkPmRegisterRead;

/* PM state (definition order chosen for the .bss layout) */
u32                data_0211fd70;    // LCD off count
vu32               data_0211fd7c;    // lock
u32                data_0211fd74;    // amp state restored when the LCD is switched on
UnkPmCallbackInfo* data_0211fd78;    // post-sleep callback list
UnkPmCallbackInfo* data_0211fd6c;    // pre-sleep callback list
vu32               data_0211fd64;    // set by notification 0x60
UnkPmRegisterRead  data_0211fda4[5]; // register reads
vu32               data_0211fd68;    // set by notification 0x62
u16                data_0211fd60;    // initialized
UnkPmCallback      data_0211fd80;    // callback
void*              data_0211fd84;    // callback argument
u32*               data_0211fd88;    // set by notification 0x67
UnkMutex           data_0211fd8c;    // mutex

#define VBLANK_COUNT (*(vu32*)0x027ffc3c)
#define REG_POWCNT   (*(vu16*)0x04000304)
#define REG_IME_     (*(vu16*)0x04000208)

void func_02078c0c(u32 tag, u32 data, BOOL err);
u32 func_02078f58(BOOL* top, BOOL* bottom);
void func_02078f98(u32 data);
BOOL func_0207914c(u32 sw, u32 backLight, BOOL skipWait, BOOL isSync);
BOOL func_020791e0(u32 sw);
u32 func_020791f4(void);
void func_02079268(UnkPmCallbackInfo* info);

BOOL func_02078b30(void) {
    u32 enabled = OS_DisableIRQ();

    if (data_0211fd7c) {
        OS_RestoreIRQ(enabled);
        return FALSE;
    }
    data_0211fd7c = TRUE;
    OS_RestoreIRQ(enabled);
    return TRUE;
}

void func_02078b58(void) {
    vu32* lock = &data_0211fd7c;

    if (data_0211fd7c) {
        do {
            if (OS_GetIRQFlag() == 0x80) {
                PXIi_HandlerRecvFifoNotEmpty();
            }
        } while (*lock);
    }
}

void func_02078b80(u32 result, void* arg) {
    *(u32*)arg = result;
}

void func_02078b84(u32 result) {
    UnkPmCallback callback = data_0211fd80;
    void* arg = data_0211fd84;

    if (data_0211fd7c) {
        data_0211fd7c = FALSE;
    }
    if (callback) {
        data_0211fd80 = NULL;
        callback(result, arg);
    }
}

void func_02078ba8(void) {
    s32 i;

    if (data_0211fd60) {
        return;
    }
    data_0211fd60 = TRUE;
    data_0211fd7c = FALSE;
    data_0211fd80 = NULL;

    func_0207734c();
    while (!func_0207744c(8, 1)) {
    }
    func_02077400(8, func_02078c0c);

    for (i = 0; i < 5; i++) {
        data_0211fda4[i].done = 0;
    }
    OS_InitMutex(&data_0211fd8c);
    data_0211fd70 = VBLANK_COUNT;
}

void func_02078c0c(u32 tag, u32 data, BOOL err) {
    u16 command;
    u16 result;

    if (err) {
        func_02078b84(2);
        return;
    }

    command = (u16)((data & 0x7f00) >> 8);
    result = data & 0xff;
    if (command >= 0x70 && command <= 0x74) {
        u16 value = (u16)(result & 0xff);
        s32 index = command - 0x70;
        u16* buf = data_0211fda4[index].buffer;
        if (buf) {
            *buf = value;
        }
        data_0211fda4[index].done = TRUE;
        result = 0;
    } else if (command == 0x60) {
        data_0211fd64 = TRUE;
    } else if (command == 0x62) {
        data_0211fd68 = TRUE;
    } else if (command == 0x67) {
        if (data_0211fd88) {
            *data_0211fd88 = result;
        }
        result = 0;
    }
    func_02078b84(result);
}

u32 func_02078c90(u32 trigger, u32 keyPattern) {
    if (!func_02078b30()) {
        return 1;
    }

    data_0211fd64 = FALSE;
    func_02078f98(0x03006000);
    while (!data_0211fd64) {
    }
    data_0211fd64 = FALSE;
    data_0211fd68 = FALSE;

    func_0207914c(0, 2, FALSE, TRUE);
    func_02078f98(0x02006100 | (trigger & 0xff));
    func_02078f98(0x01010000 | (u16)keyPattern);
    return 0;
}

u32 func_02078cf4(u32 data, UnkPmCallback callback, void* arg) {
    if (!func_02078b30()) {
        return 1;
    }
    data_0211fd80 = callback;
    data_0211fd84 = arg;
    func_02078f98(0x02006300 | ((data >> 16) & 0xff));
    func_02078f98(0x01010000 | (u16)data);
    return 0;
}

u32 func_02078d38(u32 reg, u16* buffer, UnkPmCallback callback, void* arg) {
    if (!func_02078b30()) {
        return 1;
    }
    data_0211fd80 = callback;
    data_0211fd84 = arg;
    data_0211fda4[reg].done = FALSE;
    data_0211fda4[reg].buffer = buffer;
    func_02078f98(0x03006500 | (reg & 0xff));
    return 0;
}

u32 func_02078d80(u32 reg, u16* buffer) {
    u32 syncResult;
    u32 result = func_02078d38(reg, buffer, func_02078b80, &syncResult);

    if (result != 0) {
        return result;
    }
    func_02078b58();
    return syncResult;
}

u32 func_02078d9c(u32 reg, u32 data, UnkPmCallback callback, void* arg) {
    if (!func_02078b30()) {
        return 1;
    }
    data_0211fd80 = callback;
    data_0211fd84 = arg;
    func_02078f98(0x02006400 | (reg & 0xff));
    func_02078f98(0x01010000 | (u16)data);
    return 0;
}

u32 func_02078de0(u32 reg, u32 data) {
    u32 syncResult;
    u32 result = func_02078d9c(reg, data, func_02078b80, &syncResult);

    if (result != 0) {
        return result;
    }
    func_02078b58();
    return syncResult;
}

u32 func_02078dfc(u32 type, UnkPmCallback callback, void* arg) {
    u32 command;

    switch (type) {
    case 1:
        command = 1;
        break;
    case 3:
        command = 2;
        break;
    case 2:
        command = 3;
        break;
    default:
        command = 0;
        break;
    }
    if (command != 0) {
        return func_02078cf4(command, callback, arg);
    }
    return 0xffff;
}

u32 func_02078e2c(u32 type) {
    u32 syncResult;
    u32 result = func_02078dfc(type, func_02078b80, &syncResult);

    if (result != 0) {
        return result;
    }
    func_02078b58();
    return syncResult;
}

u32 func_02078e48(u32 target, u32 on, UnkPmCallback callback, void* arg) {
    u32 command = 0;

    if (target == 0) {
        if (on == 1) {
            command = 6;
        }
        if (on == 0) {
            command = 7;
        }
    } else if (target == 1) {
        if (on == 1) {
            command = 4;
        }
        if (on == 0) {
            command = 5;
        }
    } else if (target == 2) {
        if (on == 1) {
            command = 8;
        }
        if (on == 0) {
            command = 9;
        }
    }
    if (command != 0) {
        return func_02078cf4(command, callback, arg);
    }
    return 0xffff;
}

u32 func_02078e98(u32 target, u32 on) {
    u32 syncResult;
    u32 result = func_02078e48(target, on, func_02078b80, &syncResult);

    if (result != 0) {
        return result;
    }
    func_02078b58();
    return syncResult;
}

u32 func_02078eb4(UnkPmCallback callback, void* arg) {
    BOOL top;
    BOOL bottom;

    OS_Delay(0x996a00);
    if (func_020791f4() != 1) {
        func_02078f58(&top, &bottom);
        if (top) {
            func_02078e98(0, 0);
        }
        if (bottom) {
            func_02078e98(1, 0);
        }
        while (!func_020791e0(1)) {
            OS_Delay(0x996a00);
        }
    }
    return func_02078cf4(14, callback, arg);
}

u32 func_02078f20(void) {
    u32 syncResult;
    u32 result = func_02078eb4(func_02078b80, &syncResult);

    if (result != 0) {
        return result;
    }
    func_02078b58();
    return syncResult;
}

u32 func_02078f3c(u32 amp) {
    if (func_020791f4()) {
        return func_02078de0(2, (u16)amp);
    }
    return 0;
}

u32 func_02078f58(BOOL* top, BOOL* bottom) {
    u16 status;
    u32 result = func_02078d80(0, &status);

    if (result != 0) {
        return result;
    }
    if (top) {
        *top = (status & 8) ? TRUE : FALSE;
    }
    if (bottom) {
        *bottom = (status & 4) ? TRUE : FALSE;
    }
    return result;
}

void func_02078f98(u32 data) {
    while (PXI_SendWordByFifo(8, data, FALSE) != 0) {
    }
}

static inline u16 PmDisableInterrupts(void) {
    u16 prev = REG_IME_;
    REG_IME_ = 0;
    return prev;
}

static inline u16 PmEnableInterrupts(void) {
    u16 prev = REG_IME_;
    REG_IME_ = 1;
    return prev;
}

static inline u16 PmRestoreInterrupts(u16 ime) {
    u16 prev = REG_IME_;
    REG_IME_ = ime;
    return prev;
}

static inline u32 GetVBlankCount(void) {
    return VBLANK_COUNT;
}

void func_02078fb0(u32 trigger, u16 logic, u16 keyPattern) {
    BOOL top;
    BOOL bottom;
    vu32 vcount;
    u32 prevIntr;
    u32 prevIrqMask;
    BOOL powerOff = FALSE;
    u32 dispCnt;
    u32 dbDispCnt;
    u32 lcdPower;
    u16 prevIme;
    u16 data;

    func_02079268(data_0211fd6c);

    prevIme = PmDisableInterrupts();
    prevIntr = OS_DisableIRQ();
    prevIrqMask = func_020870e8(0x3fffff);
    func_020870a4(0x40000 | (func_02088594() ? 8 : 0));
    OS_RestoreIRQ(prevIntr);
    PmEnableInterrupts();

    if (trigger & 8) {
        if (*(vu16*)0x027ffc40 == 2) {
            trigger &= ~8;
        }
    }
    if (trigger & 0x10) {
        if (!func_02071bac()) {
            trigger &= ~0x10;
        }
    }

    dispCnt = *(vu32*)0x04000000;
    dbDispCnt = *(vu32*)0x04001000;
    lcdPower = func_020791f4();
    func_02078f58(&top, &bottom);
    func_02078e98(2, 0);

    vcount = GetVBlankCount();
    while (vcount == GetVBlankCount()) {
    }
    vcount = GetVBlankCount();
    *(vu32*)0x04000000 &= ~0x30000;
    *(vu32*)0x04001000 &= ~0x10000;
    while (vcount == GetVBlankCount()) {
    }
    vcount = GetVBlankCount();
    while (vcount == GetVBlankCount()) {
    }

    data = (u16)(trigger | (top << 5) | (bottom << 6));
    while (func_02078c90(data, (u16)(logic | keyPattern)) != 0) {
    }

    func_0208894c();

    if (trigger & 8) {
        if (*(vu32*)0x04000214 & 0x100000) {
            powerOff = TRUE;
        }
    }

    if (!powerOff) {
        if (lcdPower == 1) {
            func_0207914c(1, 1, 1, 1);
        } else {
            func_02078e2c(1);
        }
        *(vu32*)0x04000000 = dispCnt;
        *(vu32*)0x04001000 = dbDispCnt;
    }

    OS_Delay(0x708100);
    OS_DisableIRQ();
    func_020870a4(prevIrqMask);
    OS_RestoreIRQ(prevIntr);
    PmRestoreInterrupts(prevIme);

    if (powerOff) {
        func_02078f20();
    }
    func_02079268(data_0211fd78);
}

BOOL func_0207914c(u32 sw, u32 backLight, BOOL skipWait, BOOL isSync) {
    switch (sw) {
    case 1:
        if (!skipWait) {
            if ((u32)(VBLANK_COUNT - data_0211fd70) <= 7) {
                return FALSE;
            }
        }
        if (backLight) {
            if (isSync) {
                func_02078e2c(backLight);
            } else {
                func_02078dfc(backLight, NULL, NULL);
            }
        }
        REG_POWCNT |= 1;
        func_02078f3c(data_0211fd74);
        break;
    case 0:
        func_02078f3c(0);
        REG_POWCNT &= ~1;
        data_0211fd70 = VBLANK_COUNT;
        if (backLight) {
            if (isSync) {
                func_02078e2c(backLight);
            } else {
                func_02078dfc(backLight, NULL, NULL);
            }
        }
        break;
    }
    return TRUE;
}

BOOL func_020791e0(u32 sw) {
    if (sw != 1) {
        sw = 0;
    }
    return func_0207914c(sw, 0, FALSE, TRUE);
}

u32 func_020791f4(void) {
    return (REG_POWCNT & 1) ? 1 : 0;
}

void func_02079208(UnkPmCallbackInfo** list, UnkPmCallbackInfo* info) {
    if (list) {
        info->next = *list;
        *list = info;
    }
}

void func_02079214(UnkPmCallbackInfo** list, UnkPmCallbackInfo* info) {
    UnkPmCallbackInfo* p;

    if (!list) {
        return;
    }
    p = *list;
    if (p == NULL) {
        info->next = NULL;
        *list = info;
        return;
    }
    while (p->next) {
        p = p->next;
    }
    info->next = p->next;
    p->next = info;
}

void func_0207923c(UnkPmCallbackInfo** list, UnkPmCallbackInfo* info) {
    UnkPmCallbackInfo* p;
    UnkPmCallbackInfo* prev;

    if (!list) {
        return;
    }
    prev = p = *list;
    while (p) {
        if (p == info) {
            if (p == prev) {
                *list = p->next;
            } else {
                prev->next = p->next;
            }
            return;
        }
        prev = p;
        p = p->next;
    }
}

void func_02079268(UnkPmCallbackInfo* info) {
    while (info) {
        info->func(info->arg);
        info = info->next;
    }
}

void func_0207927c(UnkPmCallbackInfo* info) {
    func_02079214(&data_0211fd6c, info);
}

void func_0207928c(UnkPmCallbackInfo* info) {
    func_02079208(&data_0211fd6c, info);
}

void func_0207929c(UnkPmCallbackInfo* info) {
    func_02079214(&data_0211fd78, info);
}

void func_020792ac(UnkPmCallbackInfo* info) {
    func_0207923c(&data_0211fd6c, info);
}

void func_020792bc(UnkPmCallbackInfo* info) {
    func_0207923c(&data_0211fd78, info);
}
