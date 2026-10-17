#include <nitro/types.h>

#pragma thumb on

extern void func_0206fc84(u32 cnt);
extern void func_0206feb0(u32 dmaNo);

/* MI module init: gives all shared WRAM to ARM7 and stops DMA 0. */
void func_02070a80(void) {
    func_0206fc84(3);
    func_0206feb0(0);
}
