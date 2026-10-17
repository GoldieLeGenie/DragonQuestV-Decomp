#include <nitro/types.h>

// clang-format off
asm void MI_CpuFillU16(register u16 value, register u16* dest, register u32 count) {
    mov     r3, #0x0
@1:
    cmp     r3, r2
    blt @x1a
    b @x1b
@x1a:
    strh    r0, [r1, r3]
@x1b:
    blt @x2a
    b @x2b
@x2a:
    add     r3, r3, #0x2
@x2b:
    blt       @1
    bx      lr
}

asm void MI_CpuCopyU16(register const u16* src, register u16* dest, register u32 count) {
    mov     ip, #0x0
@1:
    cmp     ip, r2
    blt @x3a
    b @x3b
@x3a:
    ldrh    r3, [r0, ip]
@x3b:
    blt @x4a
    b @x4b
@x4a:
    strh    r3, [r1, ip]
@x4b:
    blt @x5a
    b @x5b
@x5a:
    add     ip, ip, #0x2
@x5b:
    blt       @1
    bx      lr
}

asm void func_02070224(register u32 value, register u32* dest, register u32 count) {
    add     ip, r1, r2
@1:
    cmp     r1, ip
    blt @x6a
    b @x6b
@x6a:
    stmia     r1!, {r0}
@x6b:
    blt       @1
    bx      lr
}

asm void MI_CpuCopyU32(register const u32* src, register u32* dest, register u32 count) {
    add     ip, r1, r2
@1:
    cmp     r1, ip
    blt @x7a
    b @x7b
@x7a:
    ldmia     r0!, {r2}
@x7b:
    blt @x8a
    b @x8b
@x8a:
    stmia     r1!, {r2}
@x8b:
    blt       @1
    bx      lr
}

asm void MI_CpuFillFromSrc(register const u32* src, register u32* dest, register u32 count) {
    add     ip, r0, r2
@1:
    cmp     r0, ip
    blt @x9a
    b @x9b
@x9a:
    ldmia     r0!, {r2}
@x9b:
    blt @x10a
    b @x10b
@x10a:
    str     r2, [r1, 0x0]
@x10b:
    blt       @1
    bx      lr
}

asm void MI_CpuFill(register u32 value, register void* dest, register u32 count) {
    stmdb   sp!, {r4, r5, r6, r7, r8, r9}
    add     r9, r1, r2
    mov     ip, r2, lsr #0x5
    add     ip, r1, ip, lsl #0x5
    mov     r2, r0
    mov     r3, r2
    mov     r4, r2
    mov     r5, r2
    mov     r6, r2
    mov     r7, r2
    mov     r8, r2
@1:
    cmp     r1, ip
    blt @x11a
    b @x11b
@x11a:
    stmia     r1!, {r0, r2, r3, r4, r5, r6, r7, r8}
@x11b:
    blt       @1
@2:
    cmp     r1, r9
    blt @x12a
    b @x12b
@x12a:
    stmia     r1!, {r0}
@x12b:
    blt       @2
    ldmia   sp!, {r4, r5, r6, r7, r8, r9}
    bx      lr
}

asm void MI_CpuCopy(register const u32* src, register u32* dest, register u32 count) {
    stmdb   sp!, {r4, r5, r6, r7, r8, r9, r10}
    add     r10, r1, r2
    mov     ip, r2, lsr #0x5
    add     ip, r1, ip, lsl #0x5
@1:
    cmp     r1, ip
    blt @x13a
    b @x13b
@x13a:
    ldmia     r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
@x13b:
    blt @x14a
    b @x14b
@x14a:
    stmia     r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
@x14b:
    blt       @1
@2:
    cmp     r1, r10
    blt @x15a
    b @x15b
@x15a:
    ldmia     r0!, {r2}
@x15b:
    blt @x16a
    b @x16b
@x16a:
    stmia     r1!, {r2}
@x16b:
    blt       @2
    ldmia   sp!, {r4, r5, r6, r7, r8, r9, r10}
    bx      lr
}

/* Copy 32 bytes */
asm void func_02070344(register const u32* src, register u32* dest) {
    ldmia     r0!, {r2, r3, ip}
    stmia     r1!, {r2, r3, ip}
    ldmia     r0!, {r2, r3, ip}
    stmia     r1!, {r2, r3, ip}
    ldmia     r0!, {r2, r3}
    stmia     r1!, {r2, r3}
    bx      lr
}

/* Copy 36 bytes */
asm void func_02070360(register const u32* src, register u32* dest) {
    ldmia     r0!, {r2, r3, ip}
    stmia     r1!, {r2, r3, ip}
    ldmia     r0!, {r2, r3, ip}
    stmia     r1!, {r2, r3, ip}
    ldmia     r0!, {r2, r3, ip}
    stmia     r1!, {r2, r3, ip}
    bx      lr
}

asm void MI_CpuCopy48(register const u32* src, register u32* dest) {
    ldmia     r0!, {r2, r3, ip}
    stmia     r1!, {r2, r3, ip}
    ldmia     r0!, {r2, r3, ip}
    stmia     r1!, {r2, r3, ip}
    ldmia     r0!, {r2, r3, ip}
    stmia     r1!, {r2, r3, ip}
    ldmia     r0!, {r2, r3, ip}
    stmia     r1!, {r2, r3, ip}
    bx      lr
}

asm void MI_CpuCopy64(register const u32* src, register u32* dest) {
    ldmia     r0!, {r2, r3, ip}
    stmia     r1!, {r2, r3, ip}
    ldmia     r0!, {r2, r3, ip}
    stmia     r1!, {r2, r3, ip}
    ldmia     r0!, {r2, r3, ip}
    stmia     r1!, {r2, r3, ip}
    ldmia     r0!, {r2, r3, ip}
    stmia     r1!, {r2, r3, ip}
    ldmia     r0, {r0, r2, r3, ip}
    stmia     r1!, {r0, r2, r3, ip}
    bx      lr
}

asm void MI_CpuSet(register void* dest, register u8 value, register u32 count) {
    cmp     r2, #0x0
    beq @x17a
    b @x17b
@x17a:
    bx    lr
@x17b:
    tst     r0, #0x1
    beq     aligned
    ldrh    ip, [r0, #-0x1]
    and     ip, ip, #0xff
    orr     r3, ip, r1, lsl #0x8
    strh    r3, [r0, #-0x1]
    add     r0, r0, #0x1
    subs    r2, r2, #0x1
    beq @x18a
    b @x18b
@x18a:
    bx    lr
@x18b:
aligned:
    cmp     r2, #0x2
    blo     final
    orr     r1, r1, r1, lsl #0x8
    tst     r0, #0x2
    beq     word_aligned
    strh    r1, [r0], #0x2
    subs    r2, r2, #0x2
    beq @x19a
    b @x19b
@x19a:
    bx    lr
@x19b:
word_aligned:
    orr     r1, r1, r1, lsl #0x10
    bics    r3, r2, #0x3
    beq     check_half
    sub     r2, r2, r3
    add     ip, r3, r0
loop:
    str     r1, [r0], #0x4
    cmp     r0, ip
    blo     loop
check_half:
    tst     r2, #0x2
    bne @x20a
    b @x20b
@x20a:
    strh    r1, [r0], #0x2
@x20b:
final:
    tst     r2, #0x1
    beq @x21a
    b @x21b
@x21a:
    bx    lr
@x21b:
    ldrh    r3, [r0, #0x0]
    and     r3, r3, #0xff00
    and     r1, r1, #0xff
    orr     r1, r1, r3
    strh    r1, [r0, #0x0]
    bx      lr
}

asm void MI_CpuCopyU8(register const void* src, register void* dest, register u32 count) {
    cmp     r2, #0x0
    beq @x22a
    b @x22b
@x22a:
    bx    lr
@x22b:
    tst     r1, #0x1
    beq     aligned
    ldrh    ip, [r1, #-0x1]
    and     ip, ip, #0xff
    tst     r0, #0x1
    bne @x23a
    b @x23b
@x23a:
    ldrh    r3, [r0, #-0x1]
@x23b:
    bne @x24a
    b @x24b
@x24a:
    mov     r3, r3, lsr #0x8
@x24b:
    beq @x25a
    b @x25b
@x25a:
    ldrh    r3, [r0, #0x0]
@x25b:
    orr     r3, ip, r3, lsl #0x8
    strh    r3, [r1, #-0x1]
    add     r0, r0, #0x1
    add     r1, r1, #0x1
    subs    r2, r2, #0x1
    beq @x26a
    b @x26b
@x26a:
    bx    lr
@x26b:
aligned:
    eor     ip, r1, r0
    tst     ip, #0x1
    beq     check_half_align
    bic     r0, r0, #0x1
    ldrh    ip, [r0], #0x2
    mov     r3, ip, lsr #0x8
    subs    r2, r2, #0x2
    blo     final_byte
loop1:
    ldrh    ip, [r0], #0x2
    orr     ip, r3, ip, lsl #0x8
    strh    ip, [r1], #0x2
    mov     r3, ip, lsr #0x10
    subs    r2, r2, #0x2
    bhs     loop1
final_byte:
    tst     r2, #0x1
    beq @x27a
    b @x27b
@x27a:
    bx    lr
@x27b:
    ldrh    ip, [r1, #0x0]
    and     ip, ip, #0xff00
    orr     ip, ip, r3
    strh    ip, [r1, #0x0]
    bx      lr
check_half_align:
    tst     ip, #0x2
    beq     check_word_align
    bics    r3, r2, #0x1
    beq     final
    sub     r2, r2, r3
    add     ip, r3, r1
loop2:
    ldrh    r3, [r0], #0x2
    strh    r3, [r1], #0x2
    cmp     r1, ip
    blo     loop2
    b       final
check_word_align:
    cmp     r2, #0x2
    blo     final
    tst     r1, #0x2
    beq     word_aligned
    ldrh    r3, [r0], #0x2
    strh    r3, [r1], #0x2
    subs    r2, r2, #0x2
    beq @x28a
    b @x28b
@x28a:
    bx    lr
@x28b:
word_aligned:
    bics    r3, r2, #0x3
    beq     check_half
    sub     r2, r2, r3
    add     ip, r3, r1
loop3:
    ldr     r3, [r0], #0x4
    str     r3, [r1], #0x4
    cmp     r1, ip
    blo     loop3
check_half:
    tst     r2, #0x2
    bne @x29a
    b @x29b
@x29a:
    ldrh    r3, [r0], #0x2
@x29b:
    bne @x30a
    b @x30b
@x30a:
    strh    r3, [r1], #0x2
@x30b:
final:
    tst     r2, #0x1
    beq @x31a
    b @x31b
@x31a:
    bx    lr
@x31b:
    ldrh    r2, [r1, #0x0]
    ldrh    r0, [r0, #0x0]
    and     r2, r2, #0xff00
    and     r0, r0, #0xff
    orr     r0, r2, r0
    strh    r0, [r1, #0x0]
    bx      lr
}
// clang-format on

// clang-format off
#pragma thumb on
asm void MI_CpuClear24(register u32* dest) {
    mov    r1, #0x0
    mov    r2, #0x0
    mov    r3, #0x0
    stmia  r0!, {r1, r2, r3}
    stmia  r0!, {r1, r2, r3}
    stmia  r0!, {r1, r2, r3}
    bx     lr
}
#pragma thumb off

/* Atomically swaps value with *addr (swp), returns the old value. */
asm u32 func_02070618(register u32 value, register u32* addr) {
    swp     r0, r0, [r1]
    bx      lr
}
// clang-format on
