#include "snd_internal.h"

#pragma thumb on

UnkSndAlarm data_0211fcc0[8];

void func_0207819c(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        data_0211fcc0[i].func = NULL;
        data_0211fcc0[i].arg = NULL;
        data_0211fcc0[i].id = 0;
    }
}

void func_020781b8(s32 no) {
    UnkSndAlarm* alarm = &data_0211fcc0[no];
    alarm->id++;
}

u8 func_020781cc(s32 no, UnkSndAlarmHandler func, void* arg) {
    UnkSndAlarm* alarm = &data_0211fcc0[no];

    alarm->func = func;
    alarm->arg = arg;
    alarm->id++;
    return alarm->id;
}

void func_020781ec(s32 data) {
    s32 no = data & 0xff;
    u8 id = (u8)(data >> 8);
    UnkSndAlarm* alarm = &data_0211fcc0[no];

    if (id != alarm->id) {
        return;
    }
    if (alarm->func == NULL) {
        return;
    }
    alarm->func(alarm->arg);
}
