#pragma thumb on
#include "../gx/gx_internal.h"

#define REG_GXSTAT_V (*(vu32 *)0x04000600)
#define UNK_GXFIFO   ((void *)0x04000400)
#define UNK_IE_GXFIFO 0x200000

typedef void (*UnkDmaCallback)(void *arg);
typedef void (*UnkIrqHandler)(void);

/* data_0211d0e4 (0x20 bytes): geometry command DMA transfer state */
typedef struct {
    /* 0x00 */ volatile BOOL isBusy;
    /* 0x04 */ u32 dmaNo;
    /* 0x08 */ u32 src;
    /* 0x0c */ u32 size;
    /* 0x10 */ UnkDmaCallback callback;
    /* 0x14 */ void *arg;
    /* 0x18 */ volatile u32 fifoCond;
    /* 0x1c */ UnkIrqHandler fifoIntrHandler;
} UnkGxCmdDmaState;
UnkGxCmdDmaState data_0211d0e4;

void func_01ff8000(u32 dmaNo, const void *src, void *dest, u32 ctrl);
void func_02087040(u32 dmaNo, UnkDmaCallback callback, void *arg);
void func_02086f88(u32 mask, UnkIrqHandler handler);
UnkIrqHandler func_02086fe4(u32 mask);
void func_020870c4(u32 mask);
void func_020870e8(u32 mask);
void func_0208710c(u32 mask);
void func_0206ff00(u32 dmaNo, u32 dmaType);
void func_0206ff88(u32 dmaNo, u32 src, u32 size, u32 dir);
void func_02070080(void);
void func_020700f8(void *arg);
void func_020701b0(void *arg);

static inline u32 UnkGetFifoStat(void) {
    return (REG_GXSTAT_V & 0x7000000) >> 24;
}

static inline void UnkSetFifoIntrCond(s32 cond) {
    REG_GXSTAT_V = (REG_GXSTAT_V & ~0xc0000000) | (cond << 30);
}

static inline void UnkCallCallback(UnkDmaCallback callback, void *arg) {
    if (callback) {
        callback(arg);
    }
}

/* Send geometry commands to the FIFO with DMA, refilled from the FIFO interrupt */
void func_0206ffd0(u32 dmaNo, const void *src, u32 size, UnkDmaCallback callback, void *arg) {
    u32 e;

    if (size == 0) {
        UnkCallCallback(callback, arg);
        return;
    }
    while (data_0211d0e4.isBusy) {
    }
    while (!(UnkGetFifoStat() & 2)) {
    }
    data_0211d0e4.isBusy   = TRUE;
    data_0211d0e4.dmaNo    = dmaNo;
    data_0211d0e4.src      = (u32)src;
    data_0211d0e4.size     = size;
    data_0211d0e4.callback = callback;
    data_0211d0e4.arg      = arg;
    func_0206ff88(dmaNo, (u32)src, size, 0);
    func_0206fe6c(dmaNo);

    e = OS_DisableIRQ();
    data_0211d0e4.fifoCond        = (REG_GXSTAT_V & 0xc0000000) >> 30;
    data_0211d0e4.fifoIntrHandler = func_02086fe4(UNK_IE_GXFIFO);
    REG_GXSTAT_V = (REG_GXSTAT_V & ~0xc0000000) | 0x40000000;
    func_02086f88(UNK_IE_GXFIFO, func_02070080);
    func_020870c4(UNK_IE_GXFIFO);
    func_02070080();
    OS_RestoreIRQ(e);
}

void func_02070080(void) {
    u32 src;
    u32 size;

    if (data_0211d0e4.size == 0) {
        return;
    }
    size = data_0211d0e4.size;
    if (size >= 0x1d8) {
        size = 0x1d8;
    }
    src = data_0211d0e4.src;
    data_0211d0e4.size -= size;
    data_0211d0e4.src += size;
    if (data_0211d0e4.size == 0) {
        func_02087040(data_0211d0e4.dmaNo, func_020700f8, NULL);
        func_01ff8000(data_0211d0e4.dmaNo, (const void *)src, UNK_GXFIFO, 0xc4400000 | (size >> 2));
        func_0208710c(UNK_IE_GXFIFO);
    } else {
        func_01ff8000(data_0211d0e4.dmaNo, (const void *)src, UNK_GXFIFO, 0x84400000 | (size >> 2));
        func_0208710c(UNK_IE_GXFIFO);
    }
}

void func_020700f8(void *arg) {
    func_020870e8(UNK_IE_GXFIFO);
    UnkSetFifoIntrCond(data_0211d0e4.fifoCond);
    func_02086f88(UNK_IE_GXFIFO, data_0211d0e4.fifoIntrHandler);
    data_0211d0e4.isBusy = FALSE;
    UnkCallCallback(data_0211d0e4.callback, data_0211d0e4.arg);
}

/* Send geometry commands to the FIFO with a geometry-FIFO-timed DMA */
void func_0207013c(u32 dmaNo, const void *src, u32 size, UnkDmaCallback callback, void *arg) {
    if (size == 0) {
        UnkCallCallback(callback, arg);
        return;
    }
    while (data_0211d0e4.isBusy) {
    }
    data_0211d0e4.isBusy   = TRUE;
    data_0211d0e4.dmaNo    = dmaNo;
    data_0211d0e4.callback = callback;
    data_0211d0e4.arg      = arg;
    func_0206ff00(dmaNo, 0x38000000);
    func_0206ff88(dmaNo, (u32)src, size, 0);
    func_0206fe6c(dmaNo);
    func_02087040(dmaNo, func_020701b0, NULL);
    func_01ff8000(dmaNo, src, UNK_GXFIFO, 0xfc400000 | (size >> 2));
}

void func_020701b0(void *arg) {
    data_0211d0e4.isBusy = FALSE;
    UnkCallCallback(data_0211d0e4.callback, data_0211d0e4.arg);
}
