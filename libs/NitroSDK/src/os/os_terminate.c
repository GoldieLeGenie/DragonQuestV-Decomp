#include "../sdk_internal.h"

#pragma thumb on

void OS_Terminate(void) {
    while (TRUE) {
        OS_DisableIRQ();
        func_0208894c();
    }
}

#pragma thumb off

// clang-format off
asm void func_0208894c(void) {
    mov r0, #0
    mcr p15, 0, r0, c7, c0, 4
    bx lr
}
// clang-format on
