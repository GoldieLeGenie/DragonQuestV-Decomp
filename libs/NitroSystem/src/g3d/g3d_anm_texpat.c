#include "g3d_anm.h"

#pragma thumb on

/* texture pattern animation (nsbtp) */
typedef struct {
    u8 category0;                   /* 0x00 */
    u8 revision;                    /* 0x01 */
    u16 category1;                  /* 0x02 */
    u16 numFrame;                   /* 0x04 */
    u8 numTex;                      /* 0x06 */
    u8 numPltt;                     /* 0x07 */
    u16 ofsTexName;                 /* 0x08 */
    u16 ofsPlttName;                /* 0x0A */
    UnkResDict dict;                /* 0x0C */
} UnkResTexPatAnm;

typedef struct {
    u16 idxFrame;                   /* 0x00 */
    u8 idTex;                       /* 0x02 */
    u8 idPltt;                      /* 0x03 */
} UnkTexPatAnmFV;

typedef struct {
    u32 vramKey;                    /* 0x00 */
    u16 sizeTex;                    /* 0x04 */
    u16 ofsDict;                    /* 0x06 */
    u16 flag;                       /* 0x08 */
    u16 dummy_;                     /* 0x0A */
    u32 ofsTex;                     /* 0x0C */
} UnkResTexInfo;

typedef struct {
    u32 vramKey;                    /* 0x00 */
    u16 sizeTex;                    /* 0x04 */
    u16 ofsDict;                    /* 0x06 */
    u16 flag;                       /* 0x08 */
    u16 dummy_;                     /* 0x0A */
    u32 ofsTex;                     /* 0x0C */
    u32 ofsTexPlttIdx;              /* 0x10 */
} UnkResTex4x4Info;

typedef struct {
    u32 vramKey;                    /* 0x00 */
    u16 sizePltt;                   /* 0x04 */
    u16 flag;                       /* 0x06 */
    u16 ofsDict;                    /* 0x08 */
    u16 dummy_;                     /* 0x0A */
    u32 ofsPlttData;                /* 0x0C */
} UnkResPlttInfo;

typedef struct {
    u32 kind;                       /* 0x00 */
    u32 size;                       /* 0x04 */
    UnkResTexInfo texInfo;          /* 0x08 */
    UnkResTex4x4Info tex4x4Info;    /* 0x18 */
    UnkResPlttInfo plttInfo;        /* 0x2C */
    UnkResDict dict;                /* 0x3C */
} UnkResTex;

typedef struct {
    u32 texImageParam;              /* 0x00 */
    u32 extraParam;                 /* 0x04 */
} UnkResDictTexData;

typedef struct {
    u16 offset;                     /* 0x00 */
    u16 flag;                       /* 0x02 */
} UnkResDictPlttData;

extern UnkAnmFunc data_0209c51c;

const UnkTexPatAnmFV* func_02083304(const UnkResTexPatAnm* anm, u32 idx, u32 frame);
const UnkResName* func_020832d4(const UnkResTexPatAnm* anm, u32 idx);
const UnkResName* func_020832ec(const UnkResTexPatAnm* anm, u32 idx);

static inline u32 KeyAddr_(u32 key)
{
    return (u32)(u16)key << 3;
}

static inline const UnkResMat* GetMat_(const UnkResMdl* mdl)
{
    if (mdl != NULL && mdl->ofsMat != 0) {
        return (const UnkResMat*)((const u8*)mdl + mdl->ofsMat);
    }
    return NULL;
}

static inline int GetMatIdxByName_(const UnkResMat* mat, const UnkResName* name)
{
    if (mat != NULL) {
        return func_02083180(&mat->dict, name);
    }
    return -1;
}

static inline const UnkResDictTexData* GetTexDataByName_(const UnkResTex* tex, const UnkResName* name)
{
    if (tex != NULL) {
        return func_02083064(&tex->dict, name);
    }
    return NULL;
}

static inline const UnkResDictPlttData* GetPlttDataByName_(const UnkResTex* tex, const UnkResName* name)
{
    if (tex != NULL && tex->plttInfo.ofsDict != 0) {
        return func_02083064((const UnkResDict*)((const u8*)tex + tex->plttInfo.ofsDict), name);
    }
    return NULL;
}

void func_02084934(UnkAnmObj* obj, const UnkResTexPatAnm* anm, const UnkResMdl* mdl)
{
    u32 i;
    const UnkResMat* mat = GetMat_(mdl);

    obj->funcAnm = data_0209c51c;
    obj->numMapData = mdl->info.numMat;
    obj->resAnm = (void*)anm;
    MI_CpuFillU16(0, obj->mapData, obj->numMapData * sizeof(u16));

    for (i = 0; i < anm->dict.numEntry; i++) {
        int idx = GetMatIdxByName_(mat, UnkGetResNameByIdx_(&anm->dict, i));
        if (idx >= 0) {
            obj->mapData[idx] = (u16)(i | 0x100);
        }
    }
}

/* sets the texture of a texture pattern frame */
void func_020849cc(const UnkResTex* tex, const UnkResName* name, UnkMatAnmResult* result)
{
    const UnkResDictTexData* data = GetTexDataByName_(tex, name);
    u32 vramAddr;
    u32 w, h;

    if ((data->texImageParam & 0x1c000000) != 0x14000000) {
        vramAddr = KeyAddr_(tex->texInfo.vramKey) >> 3;
    } else {
        vramAddr = KeyAddr_(tex->tex4x4Info.vramKey) >> 3;
    }

    result->prmTexImage &= 0xc00f0000;
    result->prmTexImage |= data->texImageParam + vramAddr;
    result->origW = data->extraParam & 0x7ff;
    result->origH = (data->extraParam & (0x7ff << 11)) >> 11;

    w = data->extraParam & 0x7ff;
    h = (data->extraParam & (0x7ff << 11)) >> 11;
    result->magW = (w != result->origW) ? FX_Divide(w << 12, result->origW << 12) : 0x1000;
    result->magH = (h != result->origH) ? FX_Divide(h << 12, result->origH << 12) : 0x1000;
}

/* sets the palette of a texture pattern frame */
void func_02084a68(const UnkResTex* tex, const UnkResName* name, UnkMatAnmResult* result)
{
    const UnkResDictPlttData* data = GetPlttDataByName_(tex, name);
    u16 offset = data->offset;
    u16 base = (u16)(KeyAddr_(tex->plttInfo.vramKey) >> 3);

    if (!(data->flag & 1)) {
        offset = (u16)(offset >> 1);
        base = (u16)(base >> 1);
    }
    result->prmTexPltt = offset + base;
}

void func_02084aac(UnkMatAnmResult* result, const UnkAnmObj* obj, u32 dataIdx)
{
    const UnkResTexPatAnm* anm = obj->resAnm;
    const UnkTexPatAnmFV* fv = func_02083304(anm, (u16)dataIdx, (u16)(obj->frame >> 12));

    func_020849cc(obj->resTex, func_020832d4(anm, fv->idTex), result);
    if (fv->idPltt != 0xff) {
        func_02084a68(obj->resTex, func_020832ec(anm, fv->idPltt), result);
    }
}
