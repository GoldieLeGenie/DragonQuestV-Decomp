// Capture effect: worker thread, volume fade and stop/sleep handling.
#include "snd_internal.h"

#pragma thumb on

typedef struct UnkSndFader {
    /* 0x00 */ s32 origin;
    /* 0x04 */ s32 target;
    /* 0x08 */ s32 counter;
    /* 0x0C */ s32 frames;
} UnkSndFader;

typedef void (*UnkCaptureCallback)(void* buf0, void* buf1, u32 size, int format, void* arg);

typedef struct UnkSndCapture {
    /* 0x00 */ BOOL active;
    /* 0x04 */ int type;
    /* 0x08 */ int format;
    /* 0x0C */ void* buf0;
    /* 0x10 */ void* buf1;
    /* 0x14 */ u32 bufSize;
    /* 0x18 */ u32 unk_18;
    /* 0x1C */ u32 unk_1c;
    /* 0x20 */ u32 lockedChBitMask;
    /* 0x24 */ u32 chBitMask;
    /* 0x28 */ u32 capBitMask;
    /* 0x2C */ int alarmNo;
    /* 0x30 */ u32 unk_30;
    /* 0x34 */ UnkCaptureCallback callback;
    /* 0x38 */ void* arg;
    /* 0x3C */ UnkSndFader fader;
    /* 0x4C */ BOOL stopAfterFade;
    /* 0x50 */ int volume;
} UnkSndCapture;

typedef struct UnkSndCaptureMsg {
    /* 0x00 */ UnkSndCapture* capture;
    /* 0x04 */ u32 size;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ void* buf0;
    /* 0x10 */ void* buf1;
} UnkSndCaptureMsg;

typedef struct UnkMessageQueue {
    /* 0x00 */ u8 unk_00[0x20];
} UnkMessageQueue;

typedef struct UnkSndCaptureUnk {
    /* 0x00 */ u32 unk_00[0x28];
} UnkSndCaptureUnk;

BOOL             data_021236b4;        // capture thread created
u32              data_021236b8;
UnkMessageQueue  data_021236bc;        // capture message queue
void*            data_021236dc[8];     // capture messages
UnkSndCapture    data_021236fc;        // capture state
UnkSndCaptureUnk data_02123750;        // used only by code that is not linked into the ROM
OSThread         data_021237f0;        // capture thread
u8               data_021238b0[0x400]; // capture thread stack

// Uses data_02123750 like the library code that is not linked into the ROM (keeps it in the pooled .bss,
// between the capture state and the capture thread).
static void unkfunc_unused_25(void) {
    data_02123750.unk_00[0] = 0;
}

void OS_WakeupThreadDirect(void* thread);
s32  func_0207e250(UnkSndFader* fader);
void func_0207e270(UnkSndFader* fader);
BOOL func_0207e280(UnkSndFader* fader);

void func_0207bf4c(void);
void func_0207c084(void* arg);

void func_0207be8c(u32 prio) {
    if (data_021236b4) {
        return;
    }

    data_021236b8 = 0;
    func_02087aec(&data_021236bc, data_021236dc, 8);
    func_02087688(&data_021237f0, func_0207c084, NULL, data_021238b0 + sizeof(data_021238b0), sizeof(data_021238b0), prio);
    data_021236b4 = TRUE;
    OS_WakeupThreadDirect(&data_021237f0);
}

void func_0207bee4(void) {
    data_021236b4 = FALSE;
    data_021236fc.active = FALSE;
}

void func_0207bef4(void) {
    UnkSndCapture* capture = &data_021236fc;
    UnkSndFader* fader;
    int volume;

    if (!data_021236fc.active) {
        return;
    }
    if (capture->type != 0) {
        return;
    }

    fader = &capture->fader;
    func_0207e270(fader);

    if (capture->stopAfterFade && func_0207e280(fader)) {
        func_0207bf4c();
        return;
    }

    volume = func_0207e250(fader) >> 8;
    if (volume == capture->volume) {
        return;
    }

    SND_SetChannelVolume(capture->chBitMask, volume, 0);
    capture->volume = volume;
}

void func_0207bf4c(void) {
    UnkSndCapture* capture = &data_021236fc;
    BOOL hasAlarm;

    if (!data_021236fc.active) {
        return;
    }

    hasAlarm = capture->alarmNo >= 0;
    func_02077b1c(capture->chBitMask, capture->capBitMask, hasAlarm ? 1 << capture->alarmNo : 0, 0);

    if (hasAlarm) {
        u32 tag = func_02078010();
        func_02077eb8(1);
        func_02077fcc(tag);

        while (func_02087b5c(&data_021236bc, NULL, 0)) {
        }
    }

    if (capture->capBitMask != 0) {
        func_0207b420(capture->capBitMask);
    }
    if (capture->lockedChBitMask != 0) {
        func_0207b404(capture->lockedChBitMask);
    }
    if (hasAlarm) {
        func_0207b45c(capture->alarmNo);
    }
    if (capture->type == 1) {
        func_02077c5c(0, 0, 0, 0);
    }

    capture->active = FALSE;
}

void func_0207bfe8(void) {
    UnkSndCapture* capture = &data_021236fc;
    u32 tag;

    if (!data_021236fc.active) {
        return;
    }

    func_02077b1c(capture->chBitMask, capture->capBitMask, capture->alarmNo >= 0 ? 1 << capture->alarmNo : 0, 0);

    tag = func_02078010();
    func_02077eb8(1);
    func_02077fcc(tag);
}

void func_0207c02c(void) {
    UnkSndCapture* capture = &data_021236fc;

    if (!data_021236fc.active) {
        return;
    }

    capture->unk_1c = 0;
    func_02070224(0, capture->buf0, capture->bufSize);
    func_02070224(0, capture->buf1, capture->bufSize);
    DC_PurgeRange(capture->buf0, capture->bufSize);
    DC_PurgeRange(capture->buf1, capture->bufSize);

    func_02077b00(capture->chBitMask, capture->capBitMask, capture->alarmNo >= 0 ? 1 << capture->alarmNo : 0, 0);
}

void func_0207c084(void* arg) {
    void* msg;

    while (TRUE) {
        UnkSndCaptureMsg* info;
        UnkSndCapture* capture;

        func_02087b5c(&data_021236bc, &msg, 1);
        info = msg;
        if (info == NULL) {
            break;
        }

        DC_InvalidateRange(info->buf0, info->size);
        DC_InvalidateRange(info->buf1, info->size);

        capture = info->capture;
        capture->callback(info->buf0, info->buf1, info->size, capture->format, capture->arg);
    }
}
