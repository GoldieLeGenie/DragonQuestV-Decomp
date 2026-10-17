#include "snd_internal.h"

#pragma thumb on

UnkSndSharedWork* data_0211fd20;

u32 func_02078218(void) {
    DC_InvalidateRange((void*)&data_0211fd20->playerStatus, 4);
    return data_0211fd20->playerStatus;
}

u32 func_02078234(s32 playerNo) {
    DC_InvalidateRange((void*)&data_0211fd20->player[playerNo].tickCounter, 4);
    return data_0211fd20->player[playerNo].tickCounter;
}

u32 func_02078258(void) {
    DC_InvalidateRange((void*)&data_0211fd20->finishCommandTag, 4);
    return data_0211fd20->finishCommandTag;
}

void func_02078270(UnkSndSharedWork* work) {
    s32 i;
    s32 j;

    work->playerStatus = 0;
    work->channelStatus = 0;
    work->captureStatus = 0;
    work->finishCommandTag = 0;
    for (i = 0; i < 16; i++) {
        work->player[i].tickCounter = 0;
        for (j = 0; j < 16; j++) {
            work->player[i].variable[j] = -1;
        }
    }
    for (i = 0; i < 16; i++) {
        work->globalVariable[i] = -1;
    }
    DC_PurgeRange(work, sizeof(UnkSndSharedWork));
}
