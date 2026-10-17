// Low level PCM stream channels driven by an alarm.
#include "snd_internal.h"

#pragma thumb on

typedef struct UnkSleepCallbackInfo {
    /* 0x00 */ void (*func)(void*);
    /* 0x04 */ void* arg;
    /* 0x08 */ struct UnkSleepCallbackInfo* next;
} UnkSleepCallbackInfo;

typedef void (*UnkStrmCallback)(int status, int chNum, void** buffer, u32 len, int format, void* arg);

typedef struct UnkSndStrm {
    /* 0x00 */ UnkLink link;
    /* 0x08 */ UnkSleepCallbackInfo preSleepInfo;
    /* 0x14 */ UnkSleepCallbackInfo postSleepInfo;
    /* 0x20 */ int format;
    /* 0x24 */ BOOL active : 1;
    /* 0x24 */ BOOL started : 1;
    /* 0x28 */ u32 bufSize;
    /* 0x2C */ int interval;
    /* 0x30 */ UnkStrmCallback callback;
    /* 0x34 */ void* arg;
    /* 0x38 */ int curBlock;
    /* 0x3C */ int volume;
    /* 0x40 */ int alarmNo;
    /* 0x44 */ u32 chBitMask;
    /* 0x48 */ int chNum;
    /* 0x4C */ u8 chNo[16];
} UnkSndStrm;

typedef struct UnkSndStrmChannel {
    /* 0x00 */ u8* bufAddr;
    /* 0x04 */ int volume;
} UnkSndStrmChannel;

BOOL data_021235e4;                  // list initialized
UnkList data_021235e8;               // active streams
void* data_021235f4[16];             // buffer pointers passed to callbacks
UnkSndStrmChannel data_02123634[16]; // per hardware channel

void func_0207928c(UnkSleepCallbackInfo* info);
void func_0207929c(UnkSleepCallbackInfo* info);
void func_020792ac(UnkSleepCallbackInfo* info);
void func_020792bc(UnkSleepCallbackInfo* info);

void func_0207bcc4(UnkSndStrm* strm);
void func_0207bd38(UnkSndStrm* strm);
void func_0207bd88(UnkSndStrm* strm);
void func_0207bda8(void* arg);
void func_0207bdb4(UnkSndStrm* strm, int status);
void func_0207be1c(void* arg);
void func_0207be4c(void* arg);

void func_0207bad4(UnkSndStrm* strm) {
    if (!data_021235e4) {
        func_0207e290(&data_021235e8, 0);
        data_021235e4 = TRUE;
    }

    strm->preSleepInfo.func = func_0207be1c;
    strm->preSleepInfo.arg = strm;
    strm->postSleepInfo.func = func_0207be4c;
    strm->postSleepInfo.arg = strm;
    strm->chBitMask = 0;
    strm->chNum = 0;
    strm->active = FALSE;
    strm->started = FALSE;
}

BOOL func_0207bb20(UnkSndStrm* strm, int chNum, const u8* chNoList) {
    u32 chBitMask = 0;
    int i;

    for (i = 0; i < chNum; i++) {
        strm->chNo[i] = chNoList[i];
        chBitMask |= 1 << chNoList[i];
    }

    if (!func_0207b3d8(chBitMask)) {
        return FALSE;
    }

    strm->chNum = chNum;
    strm->chBitMask = chBitMask;
    return TRUE;
}

void func_0207bb60(UnkSndStrm* strm) {
    if (strm->chBitMask == 0) {
        return;
    }

    func_0207b404(strm->chBitMask);
    strm->chBitMask = 0;
    strm->chNum = 0;
}

BOOL func_0207bb78(UnkSndStrm* strm, int format, u8* buffer, u32 bufSize, int timer, int interval, UnkStrmCallback callback, void* arg) {
    u32 len;
    u32 period;
    int i;
    int irq;

    if (strm->active) {
        func_0207bcc4(strm);
    }

    bufSize = bufSize / (strm->chNum * (interval * 32));
    strm->bufSize = bufSize * interval * 32;

    len = strm->bufSize;
    if (format == 1) {
        len >>= 1;
    }
    period = timer * len / interval;

    strm->alarmNo = func_0207b430();
    if (strm->alarmNo < 0) {
        return FALSE;
    }

    for (i = 0; i < strm->chNum; i++) {
        int chNo = strm->chNo[i];
        UnkSndStrmChannel* ch = &data_02123634[chNo];

        ch->bufAddr = buffer + strm->bufSize * i;
        ch->volume = 0;
        SND_SetupChannelPcm(chNo, format, ch->bufAddr, 1, 0, strm->bufSize >> 2, 0x7F, 0, timer * 32, 0x40);
    }

    SND_SetupAlarm(strm->alarmNo, period, period, func_0207bda8, strm);
    func_0207e2b8(&data_021235e8, strm);

    strm->format = format;
    strm->interval = interval;
    strm->callback = callback;
    strm->arg = arg;
    strm->curBlock = 0;
    strm->volume = 0;
    strm->active = TRUE;

    irq = OS_DisableIRQ();
    strm->interval = 1;
    func_0207bdb4(strm, 0);
    strm->interval = interval;
    OS_RestoreIRQ(irq);

    return TRUE;
}

void func_0207bc8c(UnkSndStrm* strm) {
    func_02077b00(strm->chBitMask, 0, 1 << strm->alarmNo, 0);

    if (strm->started) {
        return;
    }

    func_0207928c(&strm->preSleepInfo);
    func_0207929c(&strm->postSleepInfo);
    strm->started = TRUE;
}

void func_0207bcc4(UnkSndStrm* strm) {
    if (!strm->active) {
        return;
    }
    func_0207bd38(strm);
}

void func_0207bcd4(UnkSndStrm* strm, int volume) {
    int chNo;
    int i;

    strm->volume = volume;

    for (i = 0; i < strm->chNum; i++) {
        s32 vol;
        chNo = strm->chNo[i];
        vol = func_020782b8(strm->volume + data_02123634[chNo].volume);

        SND_SetChannelVolume(1 << chNo, vol & 0xFF, vol >> 8);
    }
}

void func_0207bd18(UnkSndStrm* strm, int index, int pan) {
    if (index > strm->chNum - 1) {
        return;
    }
    SND_SetChannelPan(1 << strm->chNo[index], pan);
}

void func_0207bd38(UnkSndStrm* strm) {
    if (strm->started) {
        u32 tag;

        func_02077b1c(strm->chBitMask, 0, 1 << strm->alarmNo, 0);
        func_020792ac(&strm->preSleepInfo);
        func_020792bc(&strm->postSleepInfo);
        strm->started = FALSE;

        tag = func_02078010();
        func_02077eb8(1);
        func_02077fcc(tag);
    }

    func_0207bd88(strm);
}

void func_0207bd88(UnkSndStrm* strm) {
    func_0207b45c(strm->alarmNo);
    func_0207e348(&data_021235e8, strm);
    strm->active = FALSE;
}

void func_0207bda8(void* arg) {
    func_0207bdb4(arg, 1);
}

void func_0207bdb4(UnkSndStrm* strm, int status) {
    u32 len = strm->bufSize / strm->interval;
    unsigned long offset = len * strm->curBlock;
    int i;

    for (i = 0; i < strm->chNum; i++) {
        data_021235f4[i] = data_02123634[strm->chNo[i]].bufAddr + offset;
    }

    strm->callback(status, strm->chNum, data_021235f4, len, strm->format, strm->arg);

    if (++strm->curBlock >= strm->interval) {
        strm->curBlock = 0;
    }
}

void func_0207be1c(void* arg) {
    UnkSndStrm* strm = arg;
    u32 tag;

    if (!strm->started) {
        return;
    }

    func_02077b1c(strm->chBitMask, 0, 1 << strm->alarmNo, 0);

    tag = func_02078010();
    func_02077eb8(1);
    func_02077fcc(tag);
}

void func_0207be4c(void* arg) {
    UnkSndStrm* strm = arg;

    if (!strm->started) {
        return;
    }

    while (strm->curBlock != 0) {
        int irq = OS_DisableIRQ();
        func_0207bdb4(strm, 1);
        OS_RestoreIRQ(irq);
    }

    func_02077b00(strm->chBitMask, 0, 1 << strm->alarmNo, 0);
}
