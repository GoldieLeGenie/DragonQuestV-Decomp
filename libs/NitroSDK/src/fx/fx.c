#include "fx_internal.h"

// Initializes the fixed-point library (nothing to do)
void func_0208a8b0(void) {
}

// v32 * v64c (v64c: 32.32 fixed point), rounded
s32 func_0208a8b4(s32 v32, s64 v64c) {
    return (s32)((v64c * v32 + 0x80000000LL) >> 32);
}
