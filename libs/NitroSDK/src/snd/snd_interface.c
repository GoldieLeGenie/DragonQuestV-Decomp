#include "snd_internal.h"

#pragma thumb on

void func_02077a6c(u32 arg0) {
    func_02077c94(1, arg0, 0, 0, 0);
}

void func_02077a80(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    func_02077c94(2, arg0, arg1, arg2, arg3);
}

void func_02077a9c(u32 arg0) {
    func_02077c94(3, arg0, 0, 0, 0);
}

void func_02077ab0(u32 arg0, u32 arg1) {
    func_02077c94(4, arg0, arg1, 0, 0);
}

void func_02077ac8(u32 arg0, u32 arg1) {
    func_02077c78(arg0, 6, arg1, 2);
}

void func_02077ad8(u32 arg0, u32 arg1) {
    func_02077c78(arg0, 4, arg1, 1);
}

void func_02077ae8(u32 arg0, u32 arg1, u32 arg2) {
    func_02077c94(9, arg0, arg1, arg2, 0);
}

void func_02077b00(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    func_02077c94(12, arg0, arg1, arg2, arg3);
}

void func_02077b1c(u32 arg0, u32 arg1, u32 alarmMask, u32 arg3) {
    s32 i;
    u32 mask = alarmMask;

    for (i = 0; i < 8 && mask != 0; i++, mask >>= 1) {
        if (mask & 1) {
            func_020781b8(i);
        }
    }
    func_02077c94(13, arg0, arg1, alarmMask, arg3);
}

void SND_SetupAlarm(s32 alarmNo, u32 tick, u32 period, UnkSndAlarmHandler func, void* arg) {
    func_02077c94(18, alarmNo, tick, period, func_020781cc(alarmNo, func, arg));
}

void SND_LockChannel(u32 chMask, u32 flags) {
    func_02077c94(26, chMask, flags, 0, 0);
}

void func_02077b98(u32 chMask, u32 flags) {
    func_02077c94(27, chMask, flags, 0, 0);
}

void SND_SetChannelVolume(u32 chMask, s32 volume, s32 shift) {
    func_02077c94(20, chMask, volume, shift, 0);
}

void SND_SetChannelPan(u32 chMask, s32 pan) {
    func_02077c94(21, chMask, pan, 0, 0);
}

void SND_SetupChannelPcm(s32 chNo, s32 format, const void* dataAddr, s32 loop, s32 loopStart, s32 loopLen,
                         s32 volume, s32 shift, s32 timer, s32 pan) {
    func_02077c94(14, chNo | (timer << 16), (u32)dataAddr, loopLen | ((volume << 24) | (shift << 22)),
                  loopStart | ((loop << 26) | (format << 24) | (pan << 16)));
}

void func_02077c14(u32 arg0, u32 arg1) {
    func_02077c94(30, arg0, arg1, 0, 0);
}

void func_02077c2c(u32 arg0, u32 arg1) {
    func_02077c94(31, arg0, arg1, 0, 0);
}

void func_02077c44(u32 arg0, u32 arg1) {
    func_02077c94(32, arg0, arg1, 0, 0);
}

void func_02077c5c(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    func_02077c94(25, arg0, arg1, arg2, arg3);
}

void func_02077c78(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    func_02077c94(6, arg0, arg1, arg2, arg3);
}

void func_02077c94(s32 id, u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    UnkSndCommand* cmd = func_02077e34(1);
    if (cmd == NULL) {
        return;
    }
    cmd->id = id;
    cmd->arg[0] = arg0;
    cmd->arg[1] = arg1;
    cmd->arg[2] = arg2;
    cmd->arg[3] = arg3;
    func_02077e90(cmd);
}
