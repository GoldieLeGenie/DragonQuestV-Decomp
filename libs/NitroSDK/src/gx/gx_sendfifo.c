#include <nitro/types.h>

/* Write 48 bytes to a FIFO register (destination address not incremented) */
// clang-format off
asm void func_0207730c(register const void *src, register volatile void *fifo) {
    ldmia   r0!, {r2, r3, r12}
    stmia   r1, {r2, r3, r12}
    ldmia   r0!, {r2, r3, r12}
    stmia   r1, {r2, r3, r12}
    ldmia   r0!, {r2, r3, r12}
    stmia   r1, {r2, r3, r12}
    ldmia   r0!, {r2, r3, r12}
    stmia   r1, {r2, r3, r12}
    bx      lr
}

/* Write 64 bytes to a FIFO register (destination address not incremented) */
asm void func_02077330(register const void *src, register volatile void *fifo) {
    stmdb   sp!, {r4, r5, r6, r7, r8}
    ldmia   r0!, {r2, r3, r4, r5, r6, r7, r8, r12}
    stmia   r1, {r2, r3, r4, r5, r6, r7, r8, r12}
    ldmia   r0!, {r2, r3, r4, r5, r6, r7, r8, r12}
    stmia   r1, {r2, r3, r4, r5, r6, r7, r8, r12}
    ldmia   sp!, {r4, r5, r6, r7, r8}
    bx      lr
}
// clang-format on
