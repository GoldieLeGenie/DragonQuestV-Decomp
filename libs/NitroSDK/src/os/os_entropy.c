#include "../sdk_internal.h"

#pragma thumb on

typedef struct UnkUserRtcInfo {
    u32 unk_00; // 0x00
    u16 unk_04; // 0x04
} UnkUserRtcInfo;

typedef struct UnkUserConfig {
    u8 unk_00[0x74];
    UnkUserRtcInfo unk_74; // 0x74
} UnkUserConfig;

typedef struct UnkSystemWork {
    u8 unk_000[0x3c];
    u32 unk_03c;
    u8 unk_040[0x80 - 0x40];
    UnkUserConfig user; // 0x080
    u8 unk_0fc[0x1e8 - 0xfc];
    u32 unk_1e8;
    u32 unk_1ec;
    u8 unk_1f0[0x390 - 0x1f0];
    u32 unk_390;
    u16 unk_394;
    u16 unk_396;
    u16 unk_398;
    u8 unk_39a[0x3a8 - 0x39a];
    u16 unk_3a8;
    u16 unk_3aa;
    u16 unk_3ac;
} UnkSystemWork;

extern vu64 data_02127f30; // tick counter

static inline UnkSystemWork* GetSystemWork(void) {
    return (UnkSystemWork*)0x027ffc00;
}

/* Collects 32 bytes of weakly random data from hardware/system state. */
#pragma opt_propagation off
void OS_GetLowEntropyData(u32* buffer) {
    u16 vcount = *(vu16*)0x04000006;
    UnkUserConfig* user = &GetSystemWork()->user;
    UnkUserRtcInfo* rtc = &user->unk_74;
    UnkSystemWork* sys;

    buffer[0] = func_02088654() | (vcount << 16);
    buffer[1] = (u32)((rtc->unk_04 << 16) ^ data_02127f30);
    sys = GetSystemWork();
    buffer[2] = sys->unk_03c ^ (u32)((data_02127f30 >> 32) ^ user->unk_74.unk_00);
    buffer[2] ^= *(vu32*)0x04000600;
    buffer[3] = sys->unk_1e8;
    buffer[4] = sys->unk_1ec;
    buffer[5] = (sys->unk_394 << 16) ^ sys->unk_390;
    buffer[6] = (sys->unk_3aa << 16) | sys->unk_3ac;
    buffer[7] = (*(vu16*)0x04000130 | *(u16*)0x027fffa8) | (sys->unk_398 << 16);
}
#pragma opt_propagation reset
