#include "../nns_internal.h"

#pragma thumb on

typedef struct {
    u32 unk_00;                     /* 0x00 */
    u32 allocatedBits;              /* 0x04 */
    u32 lockedChannels;             /* 0x08 */
} UnkSndResourceState;

UnkSndResourceState data_02122d00;

void SND_LockChannel(u32 chBitMask, u32 flags);
void func_02077b98(u32 chBitMask, u32 flags);

BOOL func_0207b3d8(u32 chBitMask)
{
    if (chBitMask == 0) {
        return TRUE;
    }
    if (chBitMask & data_02122d00.lockedChannels) {
        return FALSE;
    }
    SND_LockChannel(chBitMask, 0);
    data_02122d00.lockedChannels |= chBitMask;
    return TRUE;
}

void func_0207b404(u32 chBitMask)
{
    if (chBitMask == 0) {
        return;
    }
    func_02077b98(chBitMask, 0);
    data_02122d00.lockedChannels &= ~chBitMask;
}

void func_0207b420(u32 bitMask)
{
    data_02122d00.unk_00 &= ~bitMask;
}

int func_0207b430(void)
{
    int i;
    u32 bit = 1;

    for (i = 0; i < 8; i++) {
        if ((data_02122d00.allocatedBits & bit) == 0) {
            data_02122d00.allocatedBits |= bit;
            return i;
        }
        bit <<= 1;
    }
    return -1;
}

void func_0207b45c(int no)
{
    data_02122d00.allocatedBits &= ~(1 << no);
}

void func_0207b470(void)
{
    data_02122d00.lockedChannels = 0;
    data_02122d00.unk_00 = 0;
    data_02122d00.allocatedBits = 0;
}
