#include <nitro/types.h>
#include "../sdk_internal.h"

#pragma thumb on

/* Starts a streaming LZ77 decompression into dest; header = the compressed data's first word. */
void func_020708d4(UnkUncompContextLZ* context, u8* dest, const UnkCompressionHeader* header) {
    context->dest = dest;
    context->destCount = header->destSize;
    context->flags = 0;
    context->flagIndex = 0;
    context->length = 0;
    context->lengthFlg = 3;
    context->unk_0c = 0;
    context->unk_0e = 0;
    context->exFormat = header->compParam ? 1 : 0;
}

#pragma thumb off

// clang-format off
/* Decompresses the next len bytes of data; returns the bytes still to write. */
asm s32 func_020708fc(register UnkUncompContextLZ* context, register const u8* data, register u32 len) {
    stmdb   sp!, {r4, r5, r6, r7, r8, r9, r10, r11}
    ldr     r3, [r0]
    ldr     r4, [r0, #4]
    ldrb    r5, [r0, #0xf]
    ldrb    r6, [r0, #0x10]
    ldr     r7, [r0, #8]
    ldrb    r8, [r0, #0x11]
    ldrb    r11, [r0, #0x12]
_0207091c:
    cmp     r4, #0
    ble     _02070a58
    cmp     r6, #0
    beq     _02070a40
_0207092c:
    cmp     r2, #0
    beq     _02070a58
    tst     r5, #0x80
    bne     _02070954
    ldrb    r9, [r1], #1
    sub     r4, r4, #1
    sub     r2, r2, #1
    swpb    r9, r9, [r3]
    add     r3, r3, #1
    b       _02070a2c
_02070954:
    cmp     r8, #0
    beq     _020709f0
    cmp     r11, #1
    bne     _020709dc
    subs    r8, r8, #1
    beq     _020709c4
    cmp     r8, #1
    beq     _020709b8
    ldrb    r7, [r1], #1
    tst     r7, #0xe0
    beq     _0207098c
    add     r7, r7, #0x10
    mov     r8, #0
    b       _020709e8
_0207098c:
    mov     r10, #0x110
    tst     r7, #0x10
    beq     _020709a8
    and     r7, r7, #0xf
    add     r10, r10, #0x1000
    add     r7, r10, r7, lsl #16
    b       _020709d0
_020709a8:
    and     r7, r7, #0xf
    add     r7, r10, r7, lsl #8
    mov     r8, #1
    b       _020709d0
_020709b8:
    ldrb    r10, [r1], #1
    add     r7, r7, r10, lsl #8
    b       _020709d0
_020709c4:
    ldrb    r10, [r1], #1
    add     r7, r7, r10
    b       _020709e8
_020709d0:
    subs    r2, r2, #1
    beq     _02070a58
    b       _02070954
_020709dc:
    ldrb    r7, [r1], #1
    add     r7, r7, #0x30
    mov     r8, #0
_020709e8:
    subs    r2, r2, #1
    beq     _02070a58
_020709f0:
    and     r9, r7, #0xf
    mov     r10, r9, lsl #8
    ldrb    r9, [r1], #1
    mov     r8, #3
    sub     r2, r2, #1
    orr     r9, r9, r10
    add     r9, r9, #1
    movs    r7, r7, asr #4
    beq     _02070a2c
_02070a14:
    ldrb    r10, [r3, -r9]
    sub     r4, r4, #1
    swpb    r10, r10, [r3]
    add     r3, r3, #1
    subs    r7, r7, #1
    bgt     _02070a14
_02070a2c:
    cmp     r4, #0
    beq     _02070a58
    mov     r5, r5, lsl #1
    subs    r6, r6, #1
    bne     _0207092c
_02070a40:
    cmp     r2, #0
    beq     _02070a58
    ldrb    r5, [r1], #1
    mov     r6, #8
    sub     r2, r2, #1
    b       _0207091c
_02070a58:
    str     r3, [r0]
    str     r4, [r0, #4]
    strb    r5, [r0, #0xf]
    strb    r6, [r0, #0x10]
    str     r7, [r0, #8]
    strb    r8, [r0, #0x11]
    strb    r11, [r0, #0x12]
    mov     r0, r4
    ldmia   sp!, {r4, r5, r6, r7, r8, r9, r10, r11}
    bx      lr
}
// clang-format on
