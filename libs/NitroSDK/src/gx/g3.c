#include "gx_internal.h"

#define REG_GXFIFO (*(vu32 *)0x04000400)

void func_0207730c(const void *src, volatile void *dest);
void func_02077330(const void *src, volatile void *dest);
void func_02070360(const void *src, volatile void *dest);

/* Matrix load/multiply commands sent through the geometry FIFO */
void func_02075ac8(const void *mtx) {
    REG_GXFIFO = 0x16;
    func_02077330(mtx, &REG_GXFIFO);
}

void func_02075ae4(const void *mtx) {
    REG_GXFIFO = 0x17;
    func_0207730c(mtx, &REG_GXFIFO);
}

void func_02075b00(const void *mtx) {
    REG_GXFIFO = 0x19;
    func_0207730c(mtx, &REG_GXFIFO);
}

void func_02075b1c(const void *mtx) {
    REG_GXFIFO = 0x1a;
    func_02070360(mtx, &REG_GXFIFO);
}
