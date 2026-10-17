#include "os_internal.h"
#include <nitro/os/interrupt.h>
#include <nitro/os/thread.h>

// IRQ dispatch and thread switch after an interrupt, linked into the ITCM

void CP_SaveContext(void* context);
void CPi_RestoreContext(void* context);
void func_01ff811c(void);

// clang-format off
asm void func_01ff80b4(void) {
    stmfd   sp!, {lr}
    mov     r12, 0x4000000
    add     r12, r12, 0x210
    ldr     r1, [r12, -8]
    cmp     r1, 0
    beq     @0a
    b       @0b
@0a:
    ldmfd   sp!, {pc}
@0b:
    ldmia   r12, {r1, r2}
    ands    r1, r1, r2
    beq     @0c
    b       @0d
@0c:
    ldmfd   sp!, {pc}
@0d:
    mov     r3, 0x80000000
@1:
    clz     r0, r1
    bics    r1, r1, r3, lsr r0
    bne     @1
    mov     r1, r3, lsr r0
    str     r1, [r12, 4]
    rsbs    r0, r0, 31
    ldr     r1, =data_027e0000
    ldr     r0, [r1, r0, lsl 2]
    ldr     lr, =func_01ff811c
    bx      r0
}

asm void func_01ff811c(void) {
    ldr     r12, =data_027e0060
    mov     r3, 0
    ldr     r12, [r12]
    mov     r2, 1
    cmp     r12, 0
    beq     @3
@1:
    str     r2, [r12, 0x64]
    str     r3, [r12, 0x78]
    str     r3, [r12, 0x7c]
    ldr     r0, [r12, 0x80]
    str     r3, [r12, 0x80]
    mov     r12, r0
    cmp     r12, 0
    bne     @1
    ldr     r12, =data_027e0060
    str     r3, [r12]
    str     r3, [r12, 4]
    ldr     r12, =ThreadInfo
    mov     r1, 1
    strh    r1, [r12]
@3:
    ldr     r12, =ThreadInfo
    ldrh    r1, [r12]
    cmp     r1, 0
    beq     @3a
    b       @3b
@3a:
    ldr     pc, [sp], 4
@3b:
    mov     r1, 0
    strh    r1, [r12]
    mov     r3, 0xd2
    msr     cpsr_c, r3
    add     r2, r12, 8
    ldr     r1, [r2]
@4:
    cmp     r1, 0
    bne     @4a
    b       @4b
@4a:
    ldrh    r0, [r1, 0x64]
@4b:
    bne     @4c
    b       @4d
@4c:
    cmp     r0, 1
@4d:
    bne     @4e
    b       @4f
@4e:
    ldr     r1, [r1, 0x68]
@4f:
    bne     @4
    cmp     r1, 0
    bne     @5
@6:
    mov     r3, 0x92
    msr     cpsr_c, r3
    ldr     pc, [sp], 4
@5:
    ldr     r0, [r12, 4]
    cmp     r1, r0
    beq     @6
    ldr     r3, [r12, 0xc]
    cmp     r3, 0
    beq     @7
    stmfd   sp!, {r0, r1, r12}
    mov     lr, pc
    bx      r3
    ldmfd   sp!, {r0, r1, r12}
@7:
    str     r1, [r12, 4]
    mrs     r2, spsr
    str     r2, [r0, 0]!
    stmfd   sp!, {r0, r1}
    add     r0, r0, 0
    add     r0, r0, 0x48
    ldr     r1, =CP_SaveContext
    blx     r1
    ldmfd   sp!, {r0, r1}
    ldmib   sp!, {r2, r3}
    stmib   r0!, {r2, r3}
    ldmib   sp!, {r2, r3, r12, lr}
    stmib   r0!, {r2-r14}^
    stmib   r0!, {lr}
    mov     r3, 0xd3
    msr     cpsr_c, r3
    stmib   r0!, {sp}
    stmfd   sp!, {r1}
    add     r0, r1, 0
    add     r0, r0, 0x48
    ldr     r1, =CPi_RestoreContext
    blx     r1
    ldmfd   sp!, {r1}
    ldr     sp, [r1, 0x44]
    mov     r3, 0xd2
    msr     cpsr_c, r3
    ldr     r2, [r1, 0]!
    msr     spsr_fc, r2
    ldr     lr, [r1, 0x40]
    ldmib   r1, {r0-r14}^
    nop
    stmda   sp!, {r0-r3, r12, lr}
    ldmfd   sp!, {pc}
}
// clang-format on
