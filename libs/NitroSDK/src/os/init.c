#include <nitro/reg.h>
#include <nitro/card.h>

// clang-format off
static asm void func_02087e8c(void) {
    mov     r12, #0x4000000
    ldr     r1, [r12, #0x208]
    str     r12, [r12, #0x208]
loop:
    ldrh    r0, [r12, #0x6]
    cmp     r0, #0x0
    bne     loop
    str     r1, [r12, #0x208]
    bx      lr
}
// clang-format on

#pragma thumb on

void OS_InitAllSystems(void) {
    OS_RegionsInit();
    func_0207734c();
    func_02087158();
    OS_ExtendedRegionInit();
    OS_InitIRQQueue();
    func_0208712c();
    func_02088344();
    func_02070a80();
    OS_VAlarmSystemInit();
    func_02088828();
    OS_InitThread();
    func_0208872c();
    func_02071d70();
    CARD_Init();
    func_02078ba8();
    func_02087e8c();
}

#pragma thumb off
