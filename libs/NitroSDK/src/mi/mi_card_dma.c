#include <nitro/types.h>

#pragma thumb on

extern void func_0206ff00(u32 dmaNo, u32 dmaType);
extern void func_0206ff88(u32 dmaNo, u32 src, u32 size, u32 dir);
extern void func_01ff8000(u32 dmaNo, const void* src, void* dest, u32 ctrl);

/* Starts a 32-bit DMA transfer triggered by the DS card (timing 5). */
void func_02070884(u32 dmaNo, const void* src, void* dest, u32 size) {
    vu32* reg;

    func_0206ff00(dmaNo, -1);
    func_0206ff88(dmaNo, (u32)src, size, 0x1000000);
    if (size == 0) {
        return;
    }
    reg = (vu32*)0x040000b0 + (dmaNo * 3 + 2);
    while (*reg & 0x80000000) {
    }
    func_01ff8000(dmaNo, src, dest, 0xaf000001);
}
