#include "g3d_internal.h"

#pragma thumb on

NNSG3dRS*     data_02124e18; // current render state
UnkG3dRSOnGlb data_02124e1c; // render state buffers

/* joint matrix / joint scale functions of the scaling rules (basic, Maya, SI3D) */
void func_02084b4c(const NNSG3dJntAnmResult* r);
void func_02084bc8(const NNSG3dJntAnmResult* r);
void func_02085320(const NNSG3dJntAnmResult* r);
void func_02084ba0(NNSG3dJntAnmResult* r, const void* p, const u8* cmd, u32 flag);
void func_02084c50(NNSG3dJntAnmResult* r, const void* p, const u8* cmd, u32 flag);
void func_0208544c(NNSG3dJntAnmResult* r, const void* p, const u8* cmd, u32 flag);
/* texture matrix functions of the texture matrix modes (Maya, SI3D, 3dsMax, XSI) */
void func_020851d8(NNSG3dMatAnmResult* r);
void func_02085668(NNSG3dMatAnmResult* r);
void func_02085d30(NNSG3dMatAnmResult* r);
void func_02086358(NNSG3dMatAnmResult* r);

UnkJntMtxFunc data_0209c580[3] = {func_02084b4c, func_02084bc8, func_02085320};   // indexed by scalingRule
UnkJntScaleFunc data_0209c58c[3] = {func_02084ba0, func_02084c50, func_0208544c}; // indexed by scalingRule
UnkTexMtxFunc data_0209c598[4] = {func_020851d8, func_02085668, func_02085d30, func_02086358}; // indexed by texMtxMode

// Executes SBC commands until the end flag is set
void G3d_RenderSBCCommands(NNSG3dRS* rs) {
    do {
        rs->flag &= ~0x40;
        data_0209c6a8[*rs->c & 0x1f](rs, *rs->c & 0xe0);
    } while (!(rs->flag & 0x20));
}

// Sets up a render state for a render object and runs its SBC
static inline NNSG3dResDict* GetNodeInfo(NNSG3dResMdl* mdl) {
    return mdl != NULL ? &mdl->nodeInfo : NULL;
}

static inline NNSG3dResMat* GetMat(NNSG3dResMdl* mdl) {
    if (mdl != NULL && mdl->ofsMat != 0) {
        return (NNSG3dResMat*)((u8*)mdl + mdl->ofsMat);
    }
    return NULL;
}

static inline NNSG3dResShp* GetShp(NNSG3dResMdl* mdl) {
    if (mdl != NULL && mdl->ofsShp != 0) {
        return (NNSG3dResShp*)((u8*)mdl + mdl->ofsShp);
    }
    return NULL;
}

void func_02080c04(NNSG3dRS* rs, NNSG3dRenderObj* obj) {
    MI_CpuFill(0, rs, sizeof(NNSG3dRS));
    rs->isMatCached[2] = 1;
    rs->flag = 1;

    if (obj->ptrUserSbc) {
        rs->c = obj->ptrUserSbc;
    } else {
        rs->c = (u8*)obj->resMdl + obj->resMdl->ofsSbc;
    }
    rs->pRenderObj = obj;
    rs->pResNodeInfo = GetNodeInfo(obj->resMdl);
    rs->pResMat = GetMat(obj->resMdl);
    rs->pResShp = GetShp(obj->resMdl);
    rs->funcJntScale = data_0209c58c[obj->resMdl->info.scalingRule];
    rs->funcJntMtx = data_0209c580[obj->resMdl->info.scalingRule];
    rs->funcTexMtx = data_0209c598[obj->resMdl->info.texMtxMode];
    rs->posScale = obj->resMdl->info.posScale;
    rs->invPosScale = obj->resMdl->info.invPosScale;

    if (obj->cbFunc && obj->cbCmd < 32) {
        rs->cbVecFunc[obj->cbCmd] = obj->cbFunc;
        rs->cbVecTiming[obj->cbCmd] = obj->cbTiming;
    }

    if (obj->flag & 1) {
        rs->flag |= 0x80;
    }
    if (obj->flag & 2) {
        rs->flag |= 0x100;
    }
    if (obj->flag & 4) {
        rs->flag |= 0x200;
    }
    if (obj->flag & 8) {
        rs->flag |= 0x400;
    }

    if (obj->cbInitFunc) {
        obj->cbInitFunc(rs);
    }

    G3d_RenderSBCCommands(rs);
    obj->flag &= ~1;
}

// Sets the hint bits of all the nodes/materials animated by an animation list
void func_02080d48(u32* hint, const NNSG3dAnmObj* anm) {
    while (anm) {
        int i;
        for (i = 0; i < anm->numMapData; i++) {
            if (anm->mapData[i] & 0x100) {
                hint[i >> 5] |= 1 << (i & 0x1f);
            }
        }
        anm = anm->next;
    }
}

void G3d_Render(NNSG3dRenderObj* obj) {
    NNSG3dRS rs;

    if ((obj->flag & 0x10) == 0x10) {
        func_02070224(0, obj->hintMatAnmExist, sizeof(obj->hintMatAnmExist));
        func_02070224(0, obj->hintJntAnmExist, sizeof(obj->hintJntAnmExist));
        func_02070224(0, obj->hintVisAnmExist, sizeof(obj->hintVisAnmExist));
        if (obj->anmMat) {
            func_02080d48(obj->hintMatAnmExist, obj->anmMat);
        }
        if (obj->anmJnt) {
            func_02080d48(obj->hintJntAnmExist, obj->anmJnt);
        }
        if (obj->anmVis) {
            func_02080d48(obj->hintVisAnmExist, obj->anmVis);
        }
        obj->flag &= ~0x10;
    }

    if (data_02124e18) {
        func_02080c04(data_02124e18, obj);
    } else {
        data_02124e18 = &rs;
        func_02080c04(&rs, obj);
        data_02124e18 = NULL;
    }
}
