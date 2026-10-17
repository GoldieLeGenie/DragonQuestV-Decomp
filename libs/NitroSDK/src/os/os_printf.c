#include "os_internal.h"

#pragma thumb on

// Formats into a buffer of `len` bytes
int func_020873c0(char* dst, u32 len, const char* fmt, ...) {
    int ret;
    va_list vlist;

    va_start(vlist, fmt);
    ret = func_020873dc(dst, len, fmt, vlist);
    va_end(vlist);
    return ret;
}

// Formats into a buffer of `len` bytes
int func_020873dc(char* dst, u32 len, const char* fmt, va_list vlist) {
    return func_02079420(dst, len, fmt, vlist);
}
