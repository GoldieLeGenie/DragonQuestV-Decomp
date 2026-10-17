#include "os_internal.h"

#pragma thumb on

#define REG_TM0CNT_L (*(vu16*)0x04000100)
#define REG_TM0CNT_H (*(vu16*)0x04000102)

#define IRQ_TIMER0 (1 << 3)

u16  data_02127f28; // initialized
BOOL data_02127f2c; // timer needs a reset
vu64 data_02127f30; // tick counter

void func_02088534(u32 timerNo);
void func_020885a0(void);

// Starts the system tick counter on timer 0
void func_02088548(void) {
    if (data_02127f28) {
        return;
    }
    data_02127f28 = TRUE;

    func_02088534(0);

    data_02127f30 = 0;

    REG_TM0CNT_H = 0;
    REG_TM0CNT_L = 0;
    REG_TM0CNT_H = 0xc1;

    func_02086f88(IRQ_TIMER0, func_020885a0);
    func_020870c4(IRQ_TIMER0);

    data_02127f2c = FALSE;
}

// Returns whether the tick counter has been started
u16 func_02088594(void) {
    return data_02127f28;
}

// Timer 0 interrupt handler
void func_020885a0(void) {
    data_02127f30++;

    if (data_02127f2c) {
        REG_TM0CNT_H = 0;
        REG_TM0CNT_L = 0;
        REG_TM0CNT_H = 0xc1;
        data_02127f2c = FALSE;
    }

    func_02087074(0, (void (*)(void*))func_020885a0, NULL);
}

// Returns the system tick
u64 func_020885e0(void) {
    vu16 countL;
    vu64 countH;
    u32  prev = OS_DisableIRQ();

    countL = REG_TM0CNT_L;
    countH = data_02127f30 & 0x0000ffffffffffffULL;

    if ((REG_IF & IRQ_TIMER0) && !(countL & 0x8000)) {
        countH++;
    }

    OS_RestoreIRQ(prev);
    return (countH << 16) | countL;
}

// Returns the low 16 bits of the system tick
u16 func_02088654(void) {
    return REG_TM0CNT_L;
}
