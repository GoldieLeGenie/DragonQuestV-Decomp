#include "os_internal.h"

#pragma thumb on

u16 data_02127f24; // reserved timer flags

// Marks a hardware timer as reserved by the system
void func_02088534(u32 timerNo) {
    data_02127f24 |= 1 << timerNo;
}
