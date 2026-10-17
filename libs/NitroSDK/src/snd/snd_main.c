#include "snd_internal.h"

#pragma thumb on

BOOL data_0211e1a8;
UnkMutex data_0211e1ac;

void SND_Init(void) {
    if (data_0211e1a8) {
        return;
    }
    data_0211e1a8 = TRUE;
    OS_InitMutex(&data_0211e1ac);
    func_02077d04();
    func_0207819c();
}

void func_02077ce4(void) {
    OS_LockMutex(&data_0211e1ac);
}

void func_02077cf4(void) {
    OS_UnlockMutex(&data_0211e1ac);
}
