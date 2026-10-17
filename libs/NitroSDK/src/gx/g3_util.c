#include "gx_internal.h"

#define REG_MTX_MODE       (*(vu32 *)0x04000440)
#define REG_MTX_MULT_3x3   (*(vu32 *)0x04000468)

typedef struct {
    s32 x, y, z;
} UnkVec32;

typedef struct {
    s32 _00, _01, _02, _03;
    s32 _10, _11, _12, _13;
    s32 _20, _21, _22, _23;
    s32 _30, _31, _32, _33;
} UnkMtx44;

typedef struct {
    s32 _00, _01, _02;
    s32 _10, _11, _12;
    s32 _20, _21, _22;
    s32 _30, _31, _32;
} UnkMtx43;

void func_02075ac8(const UnkMtx44 *mtx);
void func_02075ae4(const UnkMtx43 *mtx);
void func_02089e40(s32 t, s32 b, s32 l, s32 r, s32 n, s32 f, s32 scaleW, UnkMtx44 *mtx);
void func_02089528(const UnkVec32 *camPos, const UnkVec32 *camUp, const UnkVec32 *target, UnkMtx43 *mtx);

/* Orthographic projection matrix (sent to the geometry engine and/or stored) */
void func_020760b4(s32 t, s32 b, s32 l, s32 r, s32 n, s32 f, s32 scaleW, BOOL draw, UnkMtx44 *mtx) {
    UnkMtx44 tmp;

    if (mtx == NULL) {
        mtx = &tmp;
    }
    func_02089e40(t, b, l, r, n, f, scaleW, mtx);
    if (draw) {
        REG_MTX_MODE = 0;
        func_02075ac8(mtx);
    }
}

/* Look-at camera matrix (sent to the geometry engine and/or stored) */
void func_02076118(const UnkVec32 *camPos, const UnkVec32 *camUp, const UnkVec32 *target, BOOL draw, UnkMtx43 *mtx) {
    UnkMtx43 tmp;

    if (mtx == NULL) {
        mtx = &tmp;
    }
    func_02089528(camPos, camUp, target, mtx);
    if (draw) {
        REG_MTX_MODE = 2;
        func_02075ae4(mtx);
    }
}

/* Multiply the current matrix by a rotation around X */
void func_02076164(s32 s, s32 c) {
    REG_MTX_MULT_3x3 = 0x1000;
    REG_MTX_MULT_3x3 = 0;
    REG_MTX_MULT_3x3 = 0;
    REG_MTX_MULT_3x3 = 0;
    REG_MTX_MULT_3x3 = c;
    REG_MTX_MULT_3x3 = s;
    REG_MTX_MULT_3x3 = 0;
    REG_MTX_MULT_3x3 = -s;
    REG_MTX_MULT_3x3 = c;
}

/* Multiply the current matrix by a rotation around Y */
void func_020761a0(s32 s, s32 c) {
    REG_MTX_MULT_3x3 = c;
    REG_MTX_MULT_3x3 = 0;
    REG_MTX_MULT_3x3 = -s;
    REG_MTX_MULT_3x3 = 0;
    REG_MTX_MULT_3x3 = 0x1000;
    REG_MTX_MULT_3x3 = 0;
    REG_MTX_MULT_3x3 = s;
    REG_MTX_MULT_3x3 = 0;
    REG_MTX_MULT_3x3 = c;
}

/* Multiply the current matrix by a rotation around Z */
void func_020761dc(s32 s, s32 c) {
    REG_MTX_MULT_3x3 = c;
    REG_MTX_MULT_3x3 = s;
    REG_MTX_MULT_3x3 = 0;
    REG_MTX_MULT_3x3 = -s;
    REG_MTX_MULT_3x3 = c;
    REG_MTX_MULT_3x3 = 0;
    REG_MTX_MULT_3x3 = 0;
    REG_MTX_MULT_3x3 = 0;
    REG_MTX_MULT_3x3 = 0x1000;
}
