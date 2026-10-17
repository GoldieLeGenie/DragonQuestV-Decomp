#include <nitro/types.h>

/* Byte-oriented decompressors (LZ77 / Huffman / run-length) that write through swp/swpb. */

// clang-format off
/* LZ77 decompression: src = compressed data with header, dest = output. */
asm void func_02070620(register const void* src, register void* dest) {
    stmdb   sp!, {r4, r5, r6, r7, lr}
    ldr     r5, [r0], #4
    mov     r2, r5, lsr #8
    mov     r7, #0
    tst     r5, #0xf
    bne     _0207063c
    b       _02070640
_0207063c:
    mov     r7, #1
_02070640:
    cmp     r2, #0
    ble     _02070718
    ldrb    lr, [r0], #1
    mov     r4, #8
_02070650:
    subs    r4, r4, #1
    blt     _02070640
    tst     lr, #0x80
    bne     _02070674
    ldrb    r6, [r0], #1
    swpb    r6, r6, [r1]
    add     r1, r1, #1
    sub     r2, r2, #1
    b       _02070700
_02070674:
    ldrb    r5, [r0]
    cmp     r7, #0
    beq     _02070684
    b       _02070688
_02070684:
    mov     r6, #3
_02070688:
    beq     _020706cc
    tst     r5, #0xe0
    bne     _02070698
    b       _0207069c
_02070698:
    mov     r6, #1
_0207069c:
    bne     _020706cc
    add     r0, r0, #1
    and     r6, r5, #0xf
    mov     r6, r6, lsl #4
    tst     r5, #0x10
    beq     _020706c4
    mov     r6, r6, lsl #8
    ldrb    r5, [r0], #1
    add     r6, r6, r5, lsl #4
    add     r6, r6, #0x100
_020706c4:
    add     r6, r6, #0x11
    ldrb    r5, [r0]
_020706cc:
    add     r3, r6, r5, asr #4
    add     r0, r0, #1
    and     r5, r5, #0xf
    mov     ip, r5, lsl #8
    ldrb    r6, [r0], #1
    orr     r5, r6, ip
    add     ip, r5, #1
    sub     r2, r2, r3
_020706ec:
    ldrb    r5, [r1, -ip]
    swpb    r5, r5, [r1]
    add     r1, r1, #1
    subs    r3, r3, #1
    bgt     _020706ec
_02070700:
    cmp     r2, #0
    bgt     _0207070c
    b       _02070710
_0207070c:
    mov     lr, lr, lsl #1
_02070710:
    bgt     _02070650
    b       _02070640
_02070718:
    ldmia   sp!, {r4, r5, r6, r7, lr}
    bx      lr
}

/* Huffman decompression. */
asm void func_02070720(register const void* src, register void* dest) {
    stmfd sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #4
    add r2, r0, #4
    add r7, r2, #1
    ldrb r10, [r0]
    and r4, r10, #0xf
    mov r3, #0
    mov lr, #0
    and r10, r4, #7
    add r11, r10, #4
    str r11, [sp]
    ldr r10, [r0]
    mov r12, r10, lsr #8
    ldrb r10, [r2]
    add r10, r10, #1
    add r0, r2, r10, lsl #1
    mov r2, r7
_2067c60:
    cmp r12, #0
    ble _2067ce8
    mov r8, #0x20
    ldr r5, [r0], #4
_2067c70:
    subs r8, r8, #1
    blt _2067c60
    mov r10, #1
    and r9, r10, r5, lsr #31
    ldrb r6, [r2]
    mov r6, r6, lsl r9
    mov r10, r2, lsr #1
    mov r10, r10, lsl #1
    ldrb r11, [r2]
    and r11, r11, #0x3f
    add r11, r11, #1
    add r10, r10, r11, lsl #1
    add r2, r10, r9
    tst r6, #0x80
    beq _2067cd8
    mov r3, r3, lsr r4
    ldrb r10, [r2]
    rsb r11, r4, #0x20
    orr r3, r3, r10, lsl r11
    mov r2, r7
    add lr, lr, #1
    ldr r11, [sp]
    cmp lr, r11
    beq @x2a
    b @x2b
@x2a:
    str r3, [r1], #4
@x2b:
    beq @x3a
    b @x3b
@x3a:
    sub r12, r12, #4
@x3b:
    beq @x4a
    b @x4b
@x4a:
    mov lr, #0
@x4b:
_2067cd8:
    cmp r12, #0
    bgt @x5a
    b @x5b
@x5a:
    mov r5, r5, lsl #1
@x5b:
    bgt _2067c70
    b _2067c60
_2067ce8:
    add sp, sp, #4
    ldmfd sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    bx lr
}

/* Run-length decompression. */
asm void func_02070818(register const void* src, register void* dest) {
    stmfd sp!, {r4, r5, r7}
    ldmia r0!, {r3}
    mov r7, r3, lsr #8
_2067d00:
    cmp r7, #0
    ble _2067d58
    ldrb r4, [r0], #1
    ands r2, r4, #0x7f
    tst r4, #0x80
    bne _2067d38
    add r2, r2, #1
    sub r7, r7, r2
_2067d20:
    ldrb r3, [r0], #1
    swpb r3, r3, [r1]
    add r1, r1, #1
    subs r2, r2, #1
    bgt _2067d20
    b _2067d00
_2067d38:
    add r2, r2, #3
    sub r7, r7, r2
    ldrb r5, [r0], #1
_2067d44:
    swpb r4, r5, [r1]
    add r1, r1, #1
    subs r2, r2, #1
    bgt _2067d44
    b _2067d00
_2067d58:
    ldmfd sp!, {r4, r5, r7}
    bx lr
}

// clang-format on
