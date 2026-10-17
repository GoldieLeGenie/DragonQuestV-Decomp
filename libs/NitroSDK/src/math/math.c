#include "math_internal.h"

typedef s32 (*UnkCompareFunc)(void *a, void *b);

// clang-format off
/* Number of leading zero bits */
asm u32 func_0208a8d4(register u32 x) {
    clz     r0, r0
    bx      lr
}
// clang-format on

/* Number of set bits */
u8 func_0208a8dc(u32 x) {
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0f0f0f0f;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return (u8)x;
}

/* MD5 digest of a buffer */
void func_0208a920(void* digest, const void* data, u32 len) {
    UnkMD5Context context;

    func_020720b0(&context);
    func_020720d8(&context, data, len);
    func_0207216c(digest, &context);
}

/* Non-recursive quicksort of num elements of the given size (explicit range stack; uses stackBuf or allocates
   it on the stack when NULL) */
// clang-format off
asm void func_0208a960(register void *head, register u32 num, register u32 size, register UnkCompareFunc compare, void *stackBuf) {
    stmdb   sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    cmp     r1, #1
    ble     @end
    ldr     r4, [sp, #0x24]
    mov     r11, r3
    mov     r8, r2
    cmp     r4, #0
    bne     @have_stack
    clz     r2, r1
    rsb     r2, r2, #0x20
    mov     r2, r2, lsl #3
    sub     sp, sp, r2
    mov     r4, sp
    str     r2, [sp, #-4]!
@have_stack:
    sub     r1, r1, #1
    mla     r1, r1, r8, r0
    mov     r5, r4
    str     r0, [r4], #4
    str     r1, [r4], #4
    clz     r2, r8
    rsb     r2, r2, #0x20
    str     r2, [sp, #-4]!
@pop_range:
    cmp     r4, r5
    beq     @done
    ldr     r7, [r4, #-4]
    ldr     r6, [r4, #-8]!
    sub     r2, r7, r6
    cmp     r2, r8
    bne     @partition
    mov     r0, r6
    mov     r1, r7
    blx     r11
    cmp     r0, #0
    ble     @pop_range
    mov     r0, r8
    tst     r0, #3
    beq     @swap2_words
@swap2_bytes:
    ldrb    r1, [r6]
    subs    r0, r0, #1
    swpb    r1, r1, [r7]
    add     r7, r7, #1
    strb    r1, [r6], #1
    bne     @swap2_bytes
    b       @pop_range
@swap2_words:
    ldr     r1, [r6]
    subs    r0, r0, #4
    swp     r1, r1, [r7]
    add     r7, r7, #4
    str     r1, [r6], #4
    bne     @swap2_words
    b       @pop_range
@partition:
    ldr     r3, [sp]
    sub     r2, r7, r6
    mov     r2, r2, lsr r3
    mla     r2, r2, r8, r6
    mov     r3, r6
    mov     r0, r8
    mov     r2, r2
    tst     r0, #3
    beq     @swapm_words
@swapm_bytes:
    ldrb    r1, [r2]
    subs    r0, r0, #1
    swpb    r1, r1, [r3]
    add     r3, r3, #1
    strb    r1, [r2], #1
    bne     @swapm_bytes
    b       @scan_init
@swapm_words:
    ldr     r1, [r2]
    subs    r0, r0, #4
    swp     r1, r1, [r3]
    add     r3, r3, #4
    str     r1, [r2], #4
    bne     @swapm_words
@scan_init:
    mov     r9, r6
    mov     r10, r7
    add     r9, r9, r8
@scan_left:
    cmp     r9, r7
    bge     @scan_right
    mov     r1, r6
    mov     r0, r9
    blx     r11
    cmp     r0, #0
    blt @x1a
    b @x1b
@x1a:
    add   r9, r9, r8
@x1b:
    blt     @scan_left
@scan_right:
    mov     r1, r6
    mov     r0, r10
    blx     r11
    cmp     r0, #0
    bgt @x2a
    b @x2b
@x2a:
    sub   r10, r10, r8
@x2b:
    bgt     @scan_right
    cmp     r9, r10
    bge     @place_pivot
    mov     r2, r9
    mov     r3, r10
    mov     r0, r8
    tst     r0, #3
    beq     @swaplr_words
@swaplr_bytes:
    ldrb    r1, [r2]
    subs    r0, r0, #1
    swpb    r1, r1, [r3]
    add     r3, r3, #1
    strb    r1, [r2], #1
    bne     @swaplr_bytes
    b       @next_scan
@swaplr_words:
    ldr     r1, [r2]
    subs    r0, r0, #4
    swp     r1, r1, [r3]
    add     r3, r3, #4
    str     r1, [r2], #4
    bne     @swaplr_words
@next_scan:
    add     r9, r9, r8
    sub     r10, r10, r8
    cmp     r9, r10
    ble     @scan_left
@place_pivot:
    mov     r2, r6
    mov     r3, r10
    mov     r0, r8
    tst     r0, #3
    beq     @swapp_words
@swapp_bytes:
    ldrb    r1, [r2]
    subs    r0, r0, #1
    swpb    r1, r1, [r3]
    add     r3, r3, #1
    strb    r1, [r2], #1
    bne     @swapp_bytes
    b       @push_ranges
@swapp_words:
    ldr     r1, [r2]
    subs    r0, r0, #4
    swp     r1, r1, [r3]
    add     r3, r3, #4
    str     r1, [r2], #4
    bne     @swapp_words
@push_ranges:
    sub     r2, r10, r6
    sub     r3, r7, r10
    cmp     r2, r3
    ble     @push_right_first
    sub     r2, r10, r8
    cmp     r6, r2
    blt @x3a
    b @x3b
@x3a:
    str   r6, [r4], #4
@x3b:
    blt @x4a
    b @x4b
@x4a:
    str   r2, [r4], #4
@x4b:
    add     r2, r10, r8
    cmp     r2, r7
    blt @x5a
    b @x5b
@x5a:
    str   r2, [r4], #4
@x5b:
    blt @x6a
    b @x6b
@x6a:
    str   r7, [r4], #4
@x6b:
    b       @pop_range
@push_right_first:
    add     r2, r10, r8
    cmp     r2, r7
    blt @x7a
    b @x7b
@x7a:
    str   r2, [r4], #4
@x7b:
    blt @x8a
    b @x8b
@x8a:
    str   r7, [r4], #4
@x8b:
    sub     r2, r10, r8
    cmp     r6, r2
    blt @x9a
    b @x9b
@x9a:
    str   r6, [r4], #4
@x9b:
    blt @x10a
    b @x10b
@x10a:
    str   r2, [r4], #4
@x10b:
    b       @pop_range
@done:
    add     sp, sp, #4
    sub     r4, r4, #4
    cmp     r4, sp
    beq @x11a
    b @x11b
@x11a:
    ldr   r0, [sp]
@x11b:
    beq @x12a
    b @x12b
@x12a:
    add   r0, r0, #4
@x12b:
    beq @x13a
    b @x13b
@x13a:
    add   sp, sp, r0
@x13b:
@end:
    ldmia   sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    bx      lr
}
// clang-format on
