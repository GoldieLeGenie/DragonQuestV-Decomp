#include "fx_internal.h"

#define REG_DIV_NUMER_ADDR 0x04000290
#define REG_DIV_DENOM_ADDR 0x04000298

/* plain (non-volatile) accesses: lets the stores be merged as in the original */
static inline void SetDivNumer64Denom32(u64 numer, u32 denom) {
    *(u64*)REG_DIV_NUMER_ADDR = numer;
    *(u64*)REG_DIV_DENOM_ADDR = denom;
}

static inline s32 FxMul(s32 a, s32 b) {
    return (s32)(((s64)a * b + 0x800) >> 12);
}

static inline s32 FxMul32x64c(s32 a, s64 b) {
    return (s32)((b * a + 0x80000000LL) >> 32);
}

/* Sets a 4x4 matrix to identity. */
asm void func_02089630(register Mtx44* m) {
    mov     r2, #0x1000
    mov     r3, #0
    stmia   r0!, {r2, r3}
    mov     r1, #0
    stmia   r0!, {r1, r3}
    stmia   r0!, {r1, r2, r3}
    stmia   r0!, {r1, r3}
    stmia   r0!, {r1, r2, r3}
    stmia   r0!, {r1, r3}
    stmia   r0!, {r1, r2}
    bx      lr
}

/* Copies a 4x4 matrix into a 4x3 matrix (drops the last column). */
asm void func_0208965c(register const Mtx44* src, register Mtx43* dst) {
    ldmia   r0!, {r2-r3, r12}
    add     r0, r0, #4
    stmia   r1!, {r2-r3, r12}
    ldmia   r0!, {r2-r3, r12}
    add     r0, r0, #4
    stmia   r1!, {r2-r3, r12}
    ldmia   r0!, {r2-r3, r12}
    add     r0, r0, #4
    stmia   r1!, {r2-r3, r12}
    ldmia   r0!, {r2-r3, r12}
    add     r0, r0, #4
    stmia   r1!, {r2-r3, r12}
    bx      lr
}

void func_02089690(const Mtx44* a, const Mtx44* b, Mtx44* ab) {
    Mtx44  tmp;
    Mtx44* m;
    s32    xa, ya, za, wa;
    s32    xb, yb, zb, wb;

    if (ab == b) {
        m = &tmp;
    } else {
        m = ab;
    }

    xa = a->_00;
    ya = a->_01;
    za = a->_02;
    wa = a->_03;

    m->_00 = (s32)(((s64)xa * b->_00 + (s64)ya * b->_10 + (s64)za * b->_20 + (s64)wa * b->_30) >> 12);
    m->_01 = (s32)(((s64)xa * b->_01 + (s64)ya * b->_11 + (s64)za * b->_21 + (s64)wa * b->_31) >> 12);
    m->_03 = (s32)(((s64)xa * b->_03 + (s64)ya * b->_13 + (s64)za * b->_23 + (s64)wa * b->_33) >> 12);

    xb = b->_02;
    yb = b->_12;
    zb = b->_22;
    wb = b->_32;

    m->_02 = (s32)(((s64)xa * xb + (s64)ya * yb + (s64)za * zb + (s64)wa * wb) >> 12);

    xa = a->_10;
    ya = a->_11;
    za = a->_12;
    wa = a->_13;

    m->_12 = (s32)(((s64)xa * xb + (s64)ya * yb + (s64)za * zb + (s64)wa * wb) >> 12);
    m->_11 = (s32)(((s64)xa * b->_01 + (s64)ya * b->_11 + (s64)za * b->_21 + (s64)wa * b->_31) >> 12);
    m->_13 = (s32)(((s64)xa * b->_03 + (s64)ya * b->_13 + (s64)za * b->_23 + (s64)wa * b->_33) >> 12);

    xb = b->_00;
    yb = b->_10;
    zb = b->_20;
    wb = b->_30;

    m->_10 = (s32)(((s64)xa * xb + (s64)ya * yb + (s64)za * zb + (s64)wa * wb) >> 12);

    xa = a->_20;
    ya = a->_21;
    za = a->_22;
    wa = a->_23;

    m->_20 = (s32)(((s64)xa * xb + (s64)ya * yb + (s64)za * zb + (s64)wa * wb) >> 12);
    m->_21 = (s32)(((s64)xa * b->_01 + (s64)ya * b->_11 + (s64)za * b->_21 + (s64)wa * b->_31) >> 12);
    m->_23 = (s32)(((s64)xa * b->_03 + (s64)ya * b->_13 + (s64)za * b->_23 + (s64)wa * b->_33) >> 12);

    xb = b->_02;
    yb = b->_12;
    zb = b->_22;
    wb = b->_32;

    m->_22 = (s32)(((s64)xa * xb + (s64)ya * yb + (s64)za * zb + (s64)wa * wb) >> 12);

    xa = a->_30;
    ya = a->_31;
    za = a->_32;
    wa = a->_33;

    m->_32 = (s32)(((s64)xa * xb + (s64)ya * yb + (s64)za * zb + (s64)wa * wb) >> 12);
    m->_31 = (s32)(((s64)xa * b->_01 + (s64)ya * b->_11 + (s64)za * b->_21 + (s64)wa * b->_31) >> 12);
    m->_30 = (s32)(((s64)xa * b->_00 + (s64)ya * b->_10 + (s64)za * b->_20 + (s64)wa * b->_30) >> 12);
    m->_33 = (s32)(((s64)xa * b->_03 + (s64)ya * b->_13 + (s64)za * b->_23 + (s64)wa * b->_33) >> 12);

    if (m == &tmp) {
        *ab = tmp;
    }
}

/* Perspective projection matrix with a w scale */
void func_02089cf4(s32 fovySin, s32 fovyCos, s32 aspect, s32 n, s32 f, s32 scaleW, Mtx44* mtx) {
    s32 cot;
    s64 nf;

    cot = FX_Divide(fovyCos, fovySin);
    SetDivNumer64Denom32(0x1000LL << 32, (u32)(n - f));
    if (scaleW != 0x1000) {
        cot = cot * scaleW / 0x1000;
    }
    mtx->_01 = 0;
    mtx->_02 = 0;
    mtx->_03 = 0;
    mtx->_10 = 0;
    mtx->_11 = cot;
    mtx->_12 = 0;
    mtx->_13 = 0;
    mtx->_20 = 0;
    mtx->_21 = 0;
    mtx->_23 = -scaleW;
    mtx->_30 = 0;
    mtx->_31 = 0;
    mtx->_33 = 0;

    nf = FX_GetDivResultFx64c();
    SetDivNumer64Denom32((u64)(u32)cot << 32, (u32)aspect);
    if (scaleW != 0x1000) {
        nf = nf * scaleW / 0x1000;
    }
    mtx->_22 = FxMul32x64c(f + n, nf);
    mtx->_32 = FxMul32x64c(FxMul(n * 2, f), nf);
    mtx->_00 = FX_GetDivResult();
}

/* Orthographic projection matrix with a w scale */
void func_02089e40(s32 t, s32 b, s32 l, s32 r, s32 n, s32 f, s32 scaleW, Mtx44* mtx) {
    s64 lr;
    s64 tb;
    s64 nf;

    FX_InvAsync(r - l);
    mtx->_01 = 0;
    mtx->_02 = 0;
    mtx->_03 = 0;
    mtx->_10 = 0;
    mtx->_12 = 0;
    mtx->_13 = 0;
    mtx->_20 = 0;
    mtx->_21 = 0;
    mtx->_23 = 0;
    mtx->_33 = scaleW;

    lr = FX_GetDivResultFx64c();
    SetDivNumer64Denom32(0x1000LL << 32, (u32)(t - b));
    if (scaleW != 0x1000) {
        lr = lr * scaleW / 0x1000;
    }
    mtx->_00 = FxMul32x64c(0x1000 * 2, lr);

    tb = FX_GetDivResultFx64c();
    SetDivNumer64Denom32(0x1000LL << 32, (u32)(n - f));
    if (scaleW != 0x1000) {
        tb = tb * scaleW / 0x1000;
    }
    mtx->_11 = FxMul32x64c(0x1000 * 2, tb);

    nf = FX_GetDivResultFx64c();
    if (scaleW != 0x1000) {
        nf = nf * scaleW / 0x1000;
    }
    mtx->_22 = FxMul32x64c(0x1000 * 2, nf);
    mtx->_30 = FxMul32x64c(-r - l, lr);
    mtx->_31 = FxMul32x64c(-t - b, tb);
    mtx->_32 = FxMul32x64c(f + n, nf);
}
