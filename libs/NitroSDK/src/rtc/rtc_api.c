#include "../sdk_internal.h"
#include "rtc_internal.h"

#pragma thumb on

typedef void (*UnkRtcCallback)(s32 result, void* arg);
typedef void (*UnkRtcInterruptCallback)(void);

/* raw RTC data the ARM7 leaves in the shared work area (0x027FFDE8) */
typedef union UnkRtcRawData {
    struct {
        struct {
            u32 year : 8;
            u32 month : 5;
            u32 : 3;
            u32 day : 6;
            u32 : 10;
        } date;
        struct {
            u32 hour : 6;
            u32 : 2;
            u32 minute : 7;
            u32 : 1;
            u32 second : 7;
            u32 : 9;
        } time;
    } t;
    struct {
        u16 unk_00;
        struct {
            u16 intrMode : 4;
            u16 : 2;
            u16 intr2 : 1;
            u16 : 9;
        } status2;
        struct {
            u32 week : 3;
            u32 : 4;
            u32 weekEnable : 1;
            u32 hour : 6;
            u32 : 1;
            u32 hourEnable : 1;
            u32 minute : 7;
            u32 minuteEnable : 1;
            u32 : 8;
        } alarm;
    } a;
} UnkRtcRawData;

#define RTC_RAW (*(UnkRtcRawData*)0x027FFDE8)

typedef struct UnkRtcAlarmParam {
    u32 week;
    u32 hour;
    u32 minute;
    u32 enable;
} UnkRtcAlarmParam;

typedef struct UnkRtcWork {
    /* 0x00 */ u32                     unk_00[2]; /* not used by this code */
    /* 0x08 */ vu32                    lock;
    /* 0x0C */ UnkRtcCallback          callback;
    /* 0x10 */ void*                   buffer[2];
    /* 0x18 */ void*                   callbackArg;
    /* 0x1C */ u32                     sequence;
    /* 0x20 */ u32                     index;
    /* 0x24 */ UnkRtcInterruptCallback interrupt;
    /* 0x28 */ s32                     commonResult;
} UnkRtcWork;

static u16        data_0211e178;
static UnkRtcWork data_0211e17c;

static void func_0207764c(u32 tag, u32 data, BOOL err);
static u32  func_02077968(u32 bcd);
static void func_020779b0(s32 result, void* arg);
static void func_020779bc(void);

void func_020775a0(void) {
    if (data_0211e178) {
        return;
    }
    data_0211e178 = 1;
    data_0211e17c.lock      = 0;
    data_0211e17c.callback  = NULL;
    data_0211e17c.interrupt = NULL;
    data_0211e17c.buffer[0] = NULL;
    data_0211e17c.buffer[1] = NULL;
    func_0207734c();
    while (!func_0207744c(5, 1)) {
    }
    func_02077400(5, func_0207764c);
}

s32 func_020775e0(RTCTime* time, UnkRtcCallback callback, void* arg) {
    u32 enabled = OS_DisableIRQ();

    if (data_0211e17c.lock != 0) {
        OS_RestoreIRQ(enabled);
        return 1;
    }
    data_0211e17c.lock = 1;
    OS_RestoreIRQ(enabled);

    data_0211e17c.sequence    = 1;
    data_0211e17c.index       = 0;
    data_0211e17c.buffer[0]   = time;
    data_0211e17c.callback    = callback;
    data_0211e17c.callbackArg = arg;
    if (func_020779d4()) {
        return 0;
    }
    return 3;
}

s32 func_02077628(RTCTime* time) {
    data_0211e17c.commonResult = func_020775e0(time, func_020779b0, NULL);
    if (data_0211e17c.commonResult == 0) {
        func_020779bc();
    }
    return data_0211e17c.commonResult;
}

static void func_0207764c(u32 tag, u32 data, BOOL err) {
#pragma unused(tag)
    s32 result;
    u8  status;
    u8  command;

    if (err) {
        if (data_0211e17c.index != 0) {
            data_0211e17c.index = 0;
        }
        if (data_0211e17c.lock != 0) {
            data_0211e17c.lock = 0;
        }
        if (data_0211e17c.callback != NULL) {
            UnkRtcCallback callback = data_0211e17c.callback;
            data_0211e17c.callback  = NULL;
            callback(6, data_0211e17c.callbackArg);
        }
        return;
    }

    status  = (u8)data;
    command = (u8)((data & 0x7F00) >> 8);
    if (command == 0x30) {
        if (data_0211e17c.interrupt != NULL) {
            data_0211e17c.interrupt();
        }
        return;
    }

    if (status == 0) {
        result = 0;
        switch (data_0211e17c.sequence) {
        case 0: {
            RTCDate* date = (RTCDate*)data_0211e17c.buffer[0];
            date->year    = func_02077968(RTC_RAW.t.date.year);
            date->month   = func_02077968(RTC_RAW.t.date.month);
            date->day     = func_02077968(RTC_RAW.t.date.day);
            date->unk     = func_02077a0c(date);
        } break;
        case 1: {
            RTCTime* time = (RTCTime*)data_0211e17c.buffer[0];
            time->hour    = func_02077968(RTC_RAW.t.time.hour);
            time->minute  = func_02077968(RTC_RAW.t.time.minute);
            time->second  = func_02077968(RTC_RAW.t.time.second);
        } break;
        case 2: {
            RTCDate* date = (RTCDate*)data_0211e17c.buffer[0];
            RTCTime* time;
            date->year   = func_02077968(RTC_RAW.t.date.year);
            date->month  = func_02077968(RTC_RAW.t.date.month);
            date->day    = func_02077968(RTC_RAW.t.date.day);
            date->unk    = func_02077a0c(date);
            time         = (RTCTime*)data_0211e17c.buffer[1];
            time->hour   = func_02077968(RTC_RAW.t.time.hour);
            time->minute = func_02077968(RTC_RAW.t.time.minute);
            time->second = func_02077968(RTC_RAW.t.time.second);
        } break;
        case 3:
        case 4:
        case 5:
            break;
        case 6:
        {
            u32* enable = (u32*)data_0211e17c.buffer[0];
            if (RTC_RAW.a.status2.intrMode == 4) {
                *enable = 1;
            } else {
                *enable = 0;
            }
        } break;
        case 7:
        {
            u32* enable = (u32*)data_0211e17c.buffer[0];
            if (RTC_RAW.a.status2.intr2) {
                *enable = 1;
            } else {
                *enable = 0;
            }
        } break;
        case 8: {
            UnkRtcAlarmParam* param = (UnkRtcAlarmParam*)data_0211e17c.buffer[0];
            param->week   = RTC_RAW.a.alarm.week;
            param->hour   = func_02077968(RTC_RAW.a.alarm.hour);
            param->minute = func_02077968(RTC_RAW.a.alarm.minute);
            param->enable = 0;
            if (RTC_RAW.a.alarm.weekEnable) {
                param->enable += 1;
            }
            if (RTC_RAW.a.alarm.hourEnable) {
                param->enable += 2;
            }
            if (RTC_RAW.a.alarm.minuteEnable) {
                param->enable += 4;
            }
        } break;
        case 9:
            if (data_0211e17c.index == 0) {
                if (*(u32*)data_0211e17c.buffer[0] == 1) {
                    if (RTC_RAW.a.status2.intrMode != 4) {
                        data_0211e17c.index++;
                        RTC_RAW.a.status2.intrMode = 4;
                        if (!func_020779e0()) {
                            data_0211e17c.index = 0;
                            result              = 3;
                        }
                    }
                } else {
                    if (RTC_RAW.a.status2.intrMode != 0) {
                        data_0211e17c.index++;
                        RTC_RAW.a.status2.intrMode = 0;
                        if (!func_020779e0()) {
                            data_0211e17c.index = 0;
                            result              = 3;
                        }
                    }
                }
            } else {
                data_0211e17c.index = 0;
            }
            break;
        case 10:
            if (data_0211e17c.index == 0) {
                if (*(u32*)data_0211e17c.buffer[0] == 1) {
                    if (!RTC_RAW.a.status2.intr2) {
                        data_0211e17c.index++;
                        RTC_RAW.a.status2.intr2 = 1;
                        if (!func_020779e0()) {
                            data_0211e17c.index = 0;
                            result              = 3;
                        }
                    }
                } else {
                    if (RTC_RAW.a.status2.intr2) {
                        data_0211e17c.index++;
                        RTC_RAW.a.status2.intr2 = 0;
                        if (!func_020779e0()) {
                            data_0211e17c.index = 0;
                            result              = 3;
                        }
                    }
                }
            } else {
                data_0211e17c.index = 0;
            }
            break;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            break;
        default:
            result              = 4;
            data_0211e17c.index = 0;
            break;
        }
    } else {
        data_0211e17c.index = 0;
        switch (status) {
        case 1:
            result = 4;
            break;
        case 2:
            result = 5;
            break;
        case 3:
            result = 1;
            break;
        case 4:
        default:
            result = 6;
            break;
        }
    }

    if (data_0211e17c.index == 0) {
        if (data_0211e17c.lock != 0) {
            data_0211e17c.lock = 0;
        }
        if (data_0211e17c.callback != NULL) {
            UnkRtcCallback callback = data_0211e17c.callback;
            data_0211e17c.callback  = NULL;
            callback(result, data_0211e17c.callbackArg);
        }
    }
}

static u32 func_02077968(u32 bcd) {
    u32 hex = 0;
    s32 i;
    u32 mul;

    for (i = 0; i < 8; i++) {
        if (((bcd >> (i * 4)) & 0xF) >= 10) {
            return 0;
        }
    }
    for (i = 0, mul = 1; i < 8; i++, mul *= 10) {
        hex += ((bcd >> (i * 4)) & 0xF) * mul;
    }
    return hex;
}

static void func_020779b0(s32 result, void* arg) {
#pragma unused(arg)
    data_0211e17c.commonResult = result;
}

/* hand-written: spins on the lock word through r12 */
#pragma thumb off
// clang-format off
static asm void func_020779bc(void) {
    ldr r12, =data_0211e17c.lock
@loop:
    ldr r0, [r12]
    cmp r0, #1
    beq @loop
    bx lr
}
// clang-format on
