#include "os_internal.h"

#pragma thumb on

typedef struct UnkVAlarmState {
    /* 0x00 */ u16   active;
    /* 0x04 */ s32   unk_04;
    /* 0x08 */ s32   unk_08;
    /* 0x0c */ void* head;
    /* 0x10 */ void* tail;
} UnkVAlarmState;

UnkVAlarmState data_02127f38;

#define IRQ_VCOUNT (1 << 2)

void OS_VAlarmSystemInit(void) {
    if (data_02127f38.active == FALSE) {
        data_02127f38.active = TRUE;

        data_02127f38.head = NULL;
        data_02127f38.tail = NULL;

        func_020870e8(IRQ_VCOUNT);

        data_02127f38.unk_08 = 0;
        data_02127f38.unk_04 = 0;
    }
}
