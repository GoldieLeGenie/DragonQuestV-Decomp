#include "g3d_internal.h"

#pragma thumb on

/* Global 3D state: camera / projection matrices, lights, material colors, base transform and cached inverses. */

NNSG3dGlb data_02124bb4;

// Resets the global 3D state to its defaults
void func_020801e8(void) {
    data_02124bb4.unk_000[0] = 0x17101610;
    data_02124bb4.unk_000[1] = 0;
    data_02124bb4.unk_048 = 2;
    data_02124bb4.unk_07c = 0x32323232;
    data_02124bb4.unk_090 = 0x60293130;
    data_02124bb4.unk_0a4 = 0x33333333;
    data_02124bb4.unk_0b8 = 0x2a1b19;
    func_02088d40(&data_02124bb4.cameraMtx);
    func_02089630(&data_02124bb4.projMtx);
    data_02124bb4.unk_080[0] = 0x2d8b62d8;
    data_02124bb4.unk_080[1] = 0x40000200;
    data_02124bb4.unk_080[2] = 0x800001ff;
    data_02124bb4.unk_080[3] = 0xc0080000;
    data_02124bb4.prmMatColor0 = 0x4210c210;
    data_02124bb4.prmMatColor1 = 0x4210c210;
    data_02124bb4.prmPolygonAttr = 0x1f008f;
    data_02124bb4.unk_0a0 = 0xbfff0000;
    data_02124bb4.unk_0a8[0] = 0x7fff;
    data_02124bb4.unk_0a8[1] = 0x4000001f;
    data_02124bb4.unk_0a8[2] = 0x800003e0;
    data_02124bb4.unk_0a8[3] = 0xc0007c00;
    data_02124bb4.unk_0e0.x = 0;
    data_02124bb4.unk_0e0.y = 0;
    data_02124bb4.unk_0e0.z = 0;
    func_02088970(&data_02124bb4.prmBaseRot);
    data_02124bb4.unk_0ec.x = FX32_ONE;
    data_02124bb4.unk_0ec.y = FX32_ONE;
    data_02124bb4.unk_0ec.z = FX32_ONE;
    data_02124bb4.unk_0f8 = 0;
    data_02124bb4.flag = 0;
    data_02124bb4.camPos.z = 0;
    data_02124bb4.camPos.y = 0;
    data_02124bb4.camPos.x = 0;
    data_02124bb4.camUp.z = 0;
    data_02124bb4.camUp.x = 0;
    data_02124bb4.camUp.y = FX32_ONE;
    data_02124bb4.camTarget.y = 0;
    data_02124bb4.camTarget.x = 0;
    data_02124bb4.camTarget.z = -FX32_ONE;
}

// Sends the projection / camera state to the geometry engine
void func_020802dc(void) {
    func_020826d0(data_02124bb4.unk_000[0], (u32*)&data_02124bb4 + 1, 0x3e);
    data_02124bb4.flag &= ~1;
    data_02124bb4.flag &= ~2;
}

// Sets the base translation
void func_02080308(const VecFx32* trans) {
    if (trans != NULL) {
        data_02124bb4.unk_0e0 = *trans;
        data_02124bb4.flag &= ~0xa4;
    }
}

// Sets the base scale
void func_0208032c(const VecFx32* scale) {
    if (scale != NULL) {
        data_02124bb4.unk_0ec = *scale;
        data_02124bb4.flag &= ~0xa4;
    }
}

// Sets a light vector
void func_02080350(int lightID, fx16 x, fx16 y, fx16 z) {
    data_02124bb4.unk_080[lightID] =
        ((x >> 3) & 0x3ff) | (((y >> 3) & 0x3ff) << 10) | (((z >> 3) & 0x3ff) << 20) | (lightID << 30);
}

// Sets a light color
void func_02080380(int lightID, u16 rgb) {
    data_02124bb4.unk_0a8[lightID] = rgb | (lightID << 30);
}

// Sets the diffuse / ambient material colors
void func_02080390(u16 diffuse, u16 ambient, BOOL isSetVtxColor) {
    u32 flag = isSetVtxColor ? 1 : 0;

    data_02124bb4.prmMatColor0 = diffuse | (ambient << 16) | (flag << 15);
}

// Sets the specular / emission material colors
void func_020803b0(u16 specular, u16 emission, BOOL isShininess) {
    u32 flag = isShininess ? 1 : 0;

    data_02124bb4.prmMatColor1 = specular | (emission << 16) | (flag << 15);
}

// Sets the polygon attributes
void func_020803d0(int light, int polyMode, int cullMode, int polygonID, int alpha, int misc) {
    data_02124bb4.prmPolygonAttr = (light | (polyMode << 4) | (cullMode << 6)) | misc | (polygonID << 24) | (alpha << 16);
}

// Returns the inverse camera matrix (computed on demand)
const MtxFx43* func_020803f8(void) {
    if (!(data_02124bb4.flag & 8)) {
        func_02088e28(&data_02124bb4.cameraMtx, &data_02124bb4.unk_100);
        data_02124bb4.flag |= 8;
    }
    return &data_02124bb4.unk_100;
}

// Inverts a 4x4 matrix by Gauss-Jordan elimination; returns -1 when it is singular
int func_02080428(const MtxFx44* src, MtxFx44* dst) {
    fx32 tmp[4][4];
    fx32 (*d)[4] = (fx32 (*)[4])dst;
    int i;
    int j;
    int k;

    MI_CpuCopy64((const u32*)src, (u32*)tmp);
    func_02089630(dst);

    for (i = 0; i < 4; i++) {
        fx32 max = 0;
        int maxRow = i;
        fx64 inv;
        fx32 v;

        for (j = i; j < 4; j++) {
            v = (tmp[j][i] < 0) ? -tmp[j][i] : tmp[j][i];

            if (v > max) {
                max = v;
                maxRow = j;
            }
        }
        if (max == 0) {
            return -1;
        }

        if (maxRow != i) {
            fx32 t;

            for (j = 0; j < 4; j++) {
                t = tmp[i][j];
                tmp[i][j] = tmp[maxRow][j];
                tmp[maxRow][j] = t;

                t = d[i][j];
                d[i][j] = d[maxRow][j];
                d[maxRow][j] = t;
            }
        }

        inv = FX_Divide64(tmp[i][i]);
        for (k = 0; k < 4; k++) {
            tmp[i][k] = func_0208a8b4(tmp[i][k], inv);
            d[i][k] = func_0208a8b4(d[i][k], inv);
        }

        for (j = 0; j < 4; j++) {
            if (j != i) {
                fx32 f = tmp[j][i];

                for (k = 0; k < 4; k++) {
                    tmp[j][k] = tmp[j][k] - (fx32)(((fx64)f * tmp[i][k]) >> 12);
                    d[j][k] = d[j][k] - (fx32)(((fx64)f * d[i][k]) >> 12);
                }
            }
        }
    }
    return 0;
}

// Returns the inverse projection matrix (computed on demand)
const MtxFx44* func_0208059c(void) {
    if (!(data_02124bb4.flag & 0x10)) {
        func_02080428(&data_02124bb4.projMtx, &data_02124bb4.unk_1c0);
        data_02124bb4.flag |= 0x10;
    }
    return &data_02124bb4.unk_1c0;
}

// Computes base * camera (scaled) and its inverse
void func_020805cc(void) {
    func_020891b4((const MtxFx43*)&data_02124bb4.prmBaseRot, &data_02124bb4.cameraMtx, &data_02124bb4.unk_130);
    func_02088d9c(&data_02124bb4.unk_130, &data_02124bb4.unk_130, data_02124bb4.unk_0ec.x, data_02124bb4.unk_0ec.y,
                  data_02124bb4.unk_0ec.z);
    func_02088e28(&data_02124bb4.unk_130, &data_02124bb4.unk_160);
}

// Returns base * camera (computed on demand)
const MtxFx43* func_02080608(void) {
    if (!(data_02124bb4.flag & 0x80)) {
        func_020805cc();
        data_02124bb4.flag |= 0x80;
    }
    return &data_02124bb4.unk_130;
}

// Returns the inverse of base * camera (computed on demand)
const MtxFx43* func_02080630(void) {
    if (!(data_02124bb4.flag & 0x80)) {
        func_020805cc();
        data_02124bb4.flag |= 0x80;
    }
    return &data_02124bb4.unk_160;
}

// Returns the inverse of projection * camera (computed on demand)
const MtxFx44* func_02080658(void) {
    if (!(data_02124bb4.flag & 0x40)) {
        const MtxFx43* invCamera = func_020803f8();
        const MtxFx44* invProj = func_0208059c();
        MtxFx44 tmp;

        func_02088d68(invCamera, &tmp);
        func_02089690(invProj, &tmp, &data_02124bb4.unk_200);
        data_02124bb4.flag |= 0x40;
    }
    return &data_02124bb4.unk_200;
}

// Returns the viewport
void func_0208069c(int* x1, int* y1, int* x2, int* y2) {
    if (x1 != NULL) {
        *x1 = data_02124bb4.unk_0a0 & 0xff;
    }
    if (y1 != NULL) {
        *y1 = (data_02124bb4.unk_0a0 >> 8) & 0xff;
    }
    if (x2 != NULL) {
        *x2 = (data_02124bb4.unk_0a0 >> 16) & 0xff;
    }
    if (y2 != NULL) {
        *y2 = (data_02124bb4.unk_0a0 >> 24) & 0xff;
    }
}
