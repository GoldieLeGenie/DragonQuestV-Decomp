// Keep the complete exception state, including the storage the ROM code does not refer to.
#pragma define_section sdk_state ".data" ".bss.keep" ".rodata" RW
#include "os_internal.h"

#define EXCEPTION_VECTOR_MAIN (*(u32*)0x027ffd9c)

// DTCM area above the IRQ stack (0x027e3f80)
typedef struct UnkDtcmStackEnd {
    u8  unk_00[0x5c];
    u32 excpVectorBuf; // 0x5C exception vector buffer (DTCM + 0x3fdc)
} UnkDtcmStackEnd;

extern UnkDtcmStackEnd unk_DtcmStackEnd;

#define EXCEPTION_VECTOR_BUF  (unk_DtcmStackEnd.excpVectorBuf)

typedef void (*UnkExceptionHandler)(void* context, void* arg);

typedef struct UnkExceptionInfo {
    /* 0x00 */ u32                 debuggerHandler; // debugger exception handler
    /* 0x04 */ void*               userArg;         // user exception handler argument
    /* 0x08 */ UnkExceptionHandler userHandler;     // user exception handler
} UnkExceptionInfo;

/* definition order chosen for the .bss layout (the compiler sorts the objects by size) */
__declspec(sdk_state) UnkExceptionInfo data_02127e78;
__declspec(sdk_state) u8               data_02127e84[0x20]; // not referenced by the code linked into the ROM
__declspec(sdk_state) u8               data_02127ea4[0x80]; // exception context

void func_02088390(void);
void func_02088414(void);
void func_02088428(void);
void func_020884b8(void);
void OS_EnableProtectionUnit(void);
void OS_DisableProtectionUnit(void);

#pragma thumb on

// Installs the exception handler (unless a debugger already has one)
void func_02088344(void) {
    if (0x02600000 <= EXCEPTION_VECTOR_MAIN && EXCEPTION_VECTOR_MAIN < 0x02800000) {
        data_02127e78.debuggerHandler = EXCEPTION_VECTOR_MAIN;
    } else {
        data_02127e78.debuggerHandler = 0;
    }

    if (data_02127e78.debuggerHandler == 0) {
        EXCEPTION_VECTOR_MAIN = (u32)func_02088390;
        EXCEPTION_VECTOR_BUF  = (u32)func_02088390;
    }

    data_02127e78.userHandler = NULL;
}

#pragma thumb off

// clang-format off

// Exception vector entry
asm void func_02088390(void) {
    ldr     r12, =data_02127e78
    ldr     r12, [r12]
    cmp     r12, #0
    bne @x1a
    b @x1b
@x1a:
    mov   lr, pc
@x1b:
    bne @x2a
    b @x2b
@x2a:
    bx    r12
@x2b:

    ldr     r12, =0x02000000
    stmdb   r12!, {r0-r3, sp, lr}
    and     r0, sp, #1
    mov     sp, r12

    mrs     r1, cpsr
    and     r1, r1, #0x1f
    teq     r1, #0x17
    bne     _not_abort
    bl      func_02088414
    b       _done
_not_abort:
    teq     r1, #0x1b
    bne     _done
    bl      func_02088414
_done:
    ldr     r12, =data_02127e78
    ldr     r12, [r12]
    cmp     r12, #0
_stop:
    beq     _stop
_loop:
    mov     r0, r0
    b       _loop

    ldmia   sp!, {r0-r3, r12, lr}
    mov     sp, r12
    bx      lr
}

asm void func_02088414(void) {
    stmfd   sp!, {r0, lr}
    bl      func_02088428
    bl      func_020884b8
    ldmfd   sp!, {r0, lr}
    bx      lr
}

// Saves the exception context
asm void func_02088428(void) {
    ldr     r1, =data_02127ea4
    mrs     r2, cpsr
    str     r2, [r1, #0x74]
    str     r0, [r1, #0x6c]
    ldr     r0, [r12]
    str     r0, [r1, #4]
    ldr     r0, [r12, #4]
    str     r0, [r1, #8]
    ldr     r0, [r12, #8]
    str     r0, [r1, #0xc]
    ldr     r0, [r12, #0xc]
    str     r0, [r1, #0x10]
    ldr     r2, [r12, #0x10]
    bic     r2, r2, #1
    add     r0, r1, #0x14
    stmia   r0, {r4-r11}
    str     r12, [r1, #0x70]
    ldr     r0, [r2]
    str     r0, [r1, #0x64]
    ldr     r3, [r2, #4]
    str     r3, [r1]
    ldr     r0, [r2, #8]
    str     r0, [r1, #0x34]
    ldr     r0, [r2, #0xc]
    str     r0, [r1, #0x40]
    mrs     r0, cpsr
    orr     r3, r3, #0x80
    bic     r3, r3, #0x20
    msr     cpsr_fsxc, r3
    str     sp, [r1, #0x38]
    str     lr, [r1, #0x3c]
    mrs     r2, spsr
    str     r2, [r1, #0x7c]
    msr     cpsr_fsxc, r0
    bx      lr
}

// Calls the user exception handler in system mode
asm void func_020884b8(void) {
    stmfd   sp!, {r3, lr}
    ldr     r0, =data_02127e78
    ldr     r0, [r0, #8]
    cmp     r0, #0
    ldmeqfd sp!, {r3, pc}
    mrs     r2, cpsr
    mov     r0, sp
    ldr     r1, =0x9f
    msr     cpsr_fsxc, r1
    mov     r1, sp
    mov     sp, r0
    stmfd   sp!, {r1, r2}
    bl      OS_EnableProtectionUnit
    ldr     r0, =data_02127ea4
    ldr     r1, =data_02127e78+4
    ldr     r1, [r1]
    ldr     r12, =data_02127e78+8
    ldr     r12, [r12]
    ldr     lr, =@ret
    bx      r12
@ret:
    bl      OS_DisableProtectionUnit
    ldmfd   sp!, {r1, r2}
    mov     sp, r1
    msr     cpsr_fsxc, r2
    ldmfd   sp!, {r3, pc}
}

// clang-format on
