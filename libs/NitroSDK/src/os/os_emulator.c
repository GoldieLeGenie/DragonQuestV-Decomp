#include "os_internal.h"

#pragma thumb on

u32 data_0209c7ac = 0xffffffff; // console type cache

// Returns whether running on an emulator
BOOL func_02087ad8(void) {
    return FALSE;
}

// Returns the console type
u32 func_02087adc(void) {
    data_0209c7ac = 0x82000001;
    return data_0209c7ac;
}
