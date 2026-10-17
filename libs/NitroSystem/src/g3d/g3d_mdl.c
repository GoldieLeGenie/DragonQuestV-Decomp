#include "g3d_internal.h"

#pragma thumb on

static inline NNSG3dResMat* GetMat(const NNSG3dResMdl* mdl) {
    if (mdl != NULL && mdl->ofsMat != 0) {
        return (NNSG3dResMat*)((u8*)mdl + mdl->ofsMat);
    }
    return NULL;
}

// Sets or clears flag bits of all the materials of a model
void func_02082db0(NNSG3dResMdl* mdl, BOOL enable, u32 flag) {
    u32 numMat;
    u32 i;
    NNSG3dResMat* mat;

    numMat = mdl->info.numMat;
    mat = GetMat(mdl);

    for (i = 0; i < numMat; i++) {
        NNSG3dResMatData* data = GetMatDataByIdx(mat, i);
        if (enable) {
            data->flag |= flag;
        } else {
            data->flag &= ~flag;
        }
    }
}

// Sets or clears polygon attribute mask bits of all the materials of a model
void func_02082e1c(NNSG3dResMdl* mdl, BOOL enable, u32 flag) {
    u32 numMat;
    u32 i;
    NNSG3dResMat* mat;

    numMat = mdl->info.numMat;
    mat = GetMat(mdl);

    for (i = 0; i < numMat; i++) {
        NNSG3dResMatData* data = GetMatDataByIdx(mat, i);
        if (enable) {
            data->polyAttrMask |= flag;
        } else {
            data->polyAttrMask &= ~flag;
        }
    }
}

// Sets the diffuse color of a material
void func_02082e88(NNSG3dResMdl* mdl, u32 matID, u16 col) {
    NNSG3dResMatData* data = GetMatDataByIdx(GetMat(mdl), matID);
    data->diffAmb = (data->diffAmb & ~0x7fff) | col;
}

// Sets the ambient color of a material
void func_02082ed8(NNSG3dResMdl* mdl, u32 matID, u16 col) {
    NNSG3dResMatData* data = GetMatDataByIdx(GetMat(mdl), matID);
    data->diffAmb = (data->diffAmb & ~0x7fff0000) | (col << 16);
}

// Sets the specular color of a material
void func_02082f28(NNSG3dResMdl* mdl, u32 matID, u16 col) {
    NNSG3dResMatData* data = GetMatDataByIdx(GetMat(mdl), matID);
    data->specEmi = (data->specEmi & ~0x7fff) | col;
}

// Sets the emission color of a material
void func_02082f78(NNSG3dResMdl* mdl, u32 matID, u16 col) {
    NNSG3dResMatData* data = GetMatDataByIdx(GetMat(mdl), matID);
    data->specEmi = (data->specEmi & ~0x7fff0000) | (col << 16);
}

// Sets the alpha of a material
void func_02082fc8(NNSG3dResMdl* mdl, u32 matID, u32 alpha) {
    NNSG3dResMatData* data = GetMatDataByIdx(GetMat(mdl), matID);
    data->polyAttr = (data->polyAttr & ~0x1f0000) | (alpha << 16);
}

// Gets the alpha of a material
u32 func_02083018(const NNSG3dResMdl* mdl, u32 matID) {
    NNSG3dResMatData* data = GetMatDataByIdx(GetMat(mdl), matID);
    return (data->polyAttr & 0x1f0000) >> 16;
}
