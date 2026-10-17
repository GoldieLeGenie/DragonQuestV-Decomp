#include "g3d_internal.h"

#pragma thumb on

// Initializes the 3D engine and the G3D global state
void func_020827ac(void) {
    func_02075b38();
    func_020801e8();
    *(vu32*)0x04000600 = (*(vu32*)0x04000600 & ~0xc0000000) | 0x80000000;
}

// Sets up the textures/palettes of a resource file in VRAM and binds them to its models
BOOL func_020827d0(void* pResData) {
    switch (*(u32*)pResData) {
    case 0x30444d42: // BMD0
    case 0x30585442: // BTX0
    {
        NNSG3dResTex* tex;
        u32 szTex;
        u32 szTex4x4;
        u32 szPltt;
        BOOL sucTex = TRUE;
        BOOL sucTex4x4 = TRUE;
        BOOL sucPltt = TRUE;
        u32 keyTex;
        u32 keyTex4x4;
        u32 keyPltt;

        tex = func_02083270((UnkBinFileHeader*)pResData);
        if (tex) {
            szTex = func_0207fc2c(tex);
            szTex4x4 = func_0207fc3c(tex);
            szPltt = func_0207fd08(tex);

            if (szTex) {
                keyTex = data_0209c788(szTex, FALSE, 0);
                if (keyTex == 0) {
                    sucTex = FALSE;
                }
            } else {
                keyTex = 0;
            }

            if (szTex4x4) {
                keyTex4x4 = data_0209c788(szTex4x4, TRUE, 0);
                if (keyTex4x4 == 0) {
                    sucTex4x4 = FALSE;
                }
            } else {
                keyTex4x4 = 0;
            }

            if (szPltt) {
                keyPltt = data_0209c790(szPltt, tex->tex4x4Info.flag & 0x8000, 0);
                if (keyPltt == 0) {
                    sucPltt = FALSE;
                }
            } else {
                keyPltt = 0;
            }

            if (!sucTex || !sucTex4x4 || !sucPltt) {
                if (sucPltt) {
                    data_0209c794(keyPltt);
                }
                if (sucTex4x4) {
                    data_0209c78c(keyTex4x4);
                }
                if (sucTex) {
                    data_0209c78c(keyTex);
                }
                return FALSE;
            }

            func_0207fc4c(tex, keyTex, keyTex4x4);
            func_0207fd18(tex, keyPltt);
            func_0207fc5c(tex, TRUE);
            func_0207fd1c(tex, TRUE);
        }

        if (*(u32*)pResData == 0x30444d42) {
            NNSG3dResMdlSet* mdlSet = func_02083268((UnkBinFileHeader*)pResData);
            if (tex) {
                func_0208012c(mdlSet, tex);
            }
        }
        return TRUE;
    }
    case 0x30414342: // BCA0
    case 0x30415642: // BVA0
    case 0x30414d42: // BMA0
    case 0x30505442: // BTP0
    case 0x30415442: // BTA0
        return TRUE;
    default:
        return FALSE;
    }
}

// Releases the VRAM of a resource file set up by func_020827d0
void func_0208294c(void* pResData) {
    switch (*(u32*)pResData) {
    case 0x30444d42: // BMD0
    {
        NNSG3dResMdlSet* mdlSet = func_02083268((UnkBinFileHeader*)pResData);
        if (func_02083270((UnkBinFileHeader*)pResData)) {
            func_02080194(mdlSet);
        }
    }
    // fall through
    case 0x30585442: // BTX0
    {
        NNSG3dResTex* tex = func_02083270((UnkBinFileHeader*)pResData);
        if (tex) {
            u32 keyTex;
            u32 keyTex4x4;
            u32 keyPltt = func_0207fd4c(tex);

            func_0207fcd8(tex, &keyTex, &keyTex4x4);
            if (keyPltt) {
                data_0209c794(keyPltt);
            }
            if (keyTex4x4) {
                data_0209c78c(keyTex4x4);
            }
            if (keyTex) {
                data_0209c78c(keyTex);
            }
        }
        break;
    }
    case 0x30414342: // BCA0
    case 0x30415642: // BVA0
    case 0x30414d42: // BMA0
    case 0x30505442: // BTP0
    case 0x30415442: // BTA0
        break;
    }
}

// Converts a world position to a screen position, returns -1 when outside of the view volume
int func_02082a0c(const VecFx32* world, int* px, int* py) {
    int ret;
    int x1;
    int dx;
    int y1;
    fx32 w;
    fx32 x;
    const MtxFx44* proj;
    VecFx32 vec;
    int dy;
    int x2;
    fx64 inv;
    int y2;
    fx32 y;

    proj = &data_02124bb4.projMtx;
    func_02089488(world, &data_02124bb4.cameraMtx, &vec);
    {
        fx64 tw = (fx64)vec.x * proj->_03 + (fx64)vec.y * proj->_13 + (fx64)vec.z * proj->_23;
        w = (fx32)(tw >> 12) + proj->_33;
    }
    FX_InvAsync(w);
    {
        fx64 tx = (fx64)vec.x * proj->_00 + (fx64)vec.y * proj->_10 + (fx64)vec.z * proj->_20;
        fx64 ty = (fx64)vec.x * proj->_01 + (fx64)vec.y * proj->_11 + (fx64)vec.z * proj->_21;
        x = (fx32)(tx >> 12) + proj->_30;
        y = (fx32)(ty >> 12) + proj->_31;
    }
    inv = FX_GetDivResultFx64c();
    x = (func_0208a8b4(x, inv) + FX32_ONE) / 2;
    y = (func_0208a8b4(y, inv) + FX32_ONE) / 2;

    if (x < 0 || y < 0 || x > FX32_ONE || y > FX32_ONE) {
        ret = -1;
    } else {
        ret = 0;
    }

    func_0208069c(&x1, &y1, &x2, &y2);
    dx = x2 - x1;
    dy = y2 - y1;
    *px = x1 + ((x * dx + 0x800) >> 12);
    *py = 191 - y1 - ((y * dy + 0x800) >> 12);
    return ret;
}

// Converts a screen position to a line in world space
int func_02082b90(int px, int py, VecFx32* pNear, VecFx32* pFar) {
    int x1, y1, x2, y2;
    fx32 x, y;
    int ret;
    const MtxFx44* m;
    fx32 t;
    fx32 fw;
    fx64 inv;
    fx32 nx, ny, nz;
    fx32 fx, fy, fz;
    int h;

    func_0208069c(&x1, &y1, &x2, &y2);
    h = y2 - y1;
    x = FX_Divide((px - x1) << 12, (x2 - x1) << 12);
    y = FX_Divide((py + y1 - 191) << 12, -h << 12);

    if (x < 0 || y < 0 || x > FX32_ONE || y > FX32_ONE) {
        ret = -1;
    } else {
        ret = 0;
    }

    x = (x - 0x800) * 2;
    y = (y - 0x800) * 2;

    m = func_02080658();
    t = (fx32)(((fx64)x * m->_03 + (fx64)y * m->_13) >> 12) + m->_33;
    FX_InvAsync(t - m->_23);
    nx = (fx32)(((fx64)x * m->_00 + (fx64)y * m->_10) >> 12) + m->_30;
    ny = (fx32)(((fx64)x * m->_01 + (fx64)y * m->_11) >> 12) + m->_31;
    nz = (fx32)(((fx64)x * m->_02 + (fx64)y * m->_12) >> 12) + m->_32;

    if (pFar) {
        fx = nx + m->_20;
        fy = ny + m->_21;
        fz = nz + m->_22;
        fw = t + m->_23;
    }
    nx -= m->_20;
    ny -= m->_21;
    nz -= m->_22;

    inv = FX_GetDivResultFx64c();
    if (pFar) {
        FX_InvAsync(fw);
    }
    pNear->x = func_0208a8b4(nx, inv);
    pNear->y = func_0208a8b4(ny, inv);
    pNear->z = func_0208a8b4(nz, inv);

    if (pFar) {
        inv = FX_GetDivResultFx64c();
        pFar->x = func_0208a8b4(fx, inv);
        pFar->y = func_0208a8b4(fy, inv);
        pFar->z = func_0208a8b4(fz, inv);
    }
    return ret;
}

void* func_02082d7c(void* allocator) {
    return func_0207ebcc(allocator, sizeof(NNSG3dRenderObj));
}

void func_02082d88(void* allocator, NNSG3dRenderObj* obj) {
    func_0207ebd8(allocator, obj);
}

void* func_02082d90(void* allocator, const void* anm, const NNSG3dResMdl* mdl) {
    return func_0207ebcc(allocator, func_0207f9dc(anm, mdl));
}

void func_02082da8(void* allocator, NNSG3dAnmObj* obj) {
    func_0207ebd8(allocator, obj);
}
