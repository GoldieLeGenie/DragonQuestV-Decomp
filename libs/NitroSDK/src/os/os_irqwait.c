// IRQ wait helper and the DMA/timer interrupt callback dispatchers.
#include <nitro/types.h>
#include <nitro/os/cpustat.h>
#include <nitro/os/thread.h>

typedef struct UnkIrqCallbackInfo {
    /* 0x00 */ void (*func)(void*);
    /* 0x04 */ u32 enable;
    /* 0x08 */ void* arg;
} UnkIrqCallbackInfo;

extern u8 data_027e0000[];                  // DTCM start (interrupt check flag at +0x3FF8)
extern OSThreadQueue data_027e0060;         // threads waiting for an interrupt
extern UnkIrqCallbackInfo data_02127b6c[8]; // DMA 0-3 / timer 0-3 callbacks
u16 data_0209c79c[8] = {8, 9, 10, 11, 3, 4, 5, 6}; // interrupt bit of each callback slot

#define UNK_IRQ_CHECK (*(vu32*)((u32)data_027e0000 + 0x3FF8))

u32 func_020870e8(u32 mask);

void func_02086e48(BOOL clear, u32 irqFlags) {
    u32 irq = OS_DisableIRQ();
    if (clear) {
        UNK_IRQ_CHECK &= ~irqFlags;
    }
    OS_RestoreIRQ(irq);

    if (irqFlags & UNK_IRQ_CHECK) {
        return;
    }

    do {
        OS_PauseThread(&data_027e0060);
    } while (!(irqFlags & UNK_IRQ_CHECK));
}

#pragma thumb on

void func_02086ebc(void) {
}

void func_02086ec0(int index) {
    u32 mask = 1 << data_0209c79c[index];
    void (*func)(void*) = data_02127b6c[index].func;

    data_02127b6c[index].func = NULL;
    if (func != NULL) {
        func(data_02127b6c[index].arg);
    }

    UNK_IRQ_CHECK |= mask;

    if (!data_02127b6c[index].enable) {
        func_020870e8(mask);
    }
}

void func_02086f18(void) {
    func_02086ec0(0);
}

void func_02086f24(void) {
    func_02086ec0(1);
}

void func_02086f30(void) {
    func_02086ec0(2);
}

void func_02086f3c(void) {
    func_02086ec0(3);
}

void func_02086f48(void) {
    func_02086ec0(4);
}

void func_02086f54(void) {
    func_02086ec0(5);
}

void func_02086f60(void) {
    func_02086ec0(6);
}

void func_02086f6c(void) {
    func_02086ec0(7);
}

#pragma thumb off
