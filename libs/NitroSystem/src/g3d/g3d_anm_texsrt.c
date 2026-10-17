#include "g3d_anm.h"

#pragma thumb on

/* texture SRT animation (nsbta) */
typedef struct {
    u32 scaleSInfo;                 /* 0x00 */
    u32 scaleSData;                 /* 0x04 */
    u32 scaleTInfo;                 /* 0x08 */
    u32 scaleTData;                 /* 0x0C */
    u32 rotInfo;                    /* 0x10 */
    u32 rotData;                    /* 0x14 */
    u32 transSInfo;                 /* 0x18 */
    u32 transSData;                 /* 0x1C */
    u32 transTInfo;                 /* 0x20 */
    u32 transTData;                 /* 0x24 */
} UnkTexSRTAnmData;

typedef struct {
    fx16 sin;
    fx16 cos;
} UnkRotData;

extern UnkAnmFunc data_0209c518;

/* scale/translation value of a texture SRT track */
fx32 func_02084624(const u8* p, u32 info, u32 data, u32 frame)
{
    u32 last;
    const u8* d;

    if (info & 0x20000000) {
        return (fx32)data;
    }

    d = p + data;
    if (info & 0xc0000000) {
        last = (u16)info;
        if (info & 0x40000000) {
            if (frame & 1) {
                if (frame > last) {
                    frame = (last >> 1) + 1;
                } else {
                    frame >>= 1;
                    goto avg2;
                }
            } else {
                frame >>= 1;
            }
        } else {
            u32 rem = frame & 3;
            if (rem != 0) {
                if (frame > last) {
                    frame = (last >> 2) + rem;
                } else if (frame & 1) {
                    u32 idx0;
                    fx32 v0, v1;

                    if (frame & 2) {
                        idx0 = frame >> 2;
                        frame = idx0 + 1;
                    } else {
                        frame = frame >> 2;
                        idx0 = frame + 1;
                    }
                    if (info & 0x10000000) {
                        v0 = ((const fx16*)d)[frame];
                        v1 = ((const fx16*)d)[idx0];
                    } else {
                        v0 = ((const fx32*)d)[frame];
                        v1 = ((const fx32*)d)[idx0];
                    }
                    return (v0 + v0 + v0 + v1) >> 2;
                } else {
                    frame >>= 2;
                    goto avg2;
                }
            } else {
                frame >>= 2;
            }
        }
    }

    if (info & 0x10000000) {
        return ((const fx16*)d)[frame];
    } else {
        return ((const fx32*)d)[frame];
    }

avg2:
    {
        fx32 v0, v1;
        if (info & 0x10000000) {
            v0 = ((const fx16*)d)[frame];
            v1 = ((const fx16*)d + frame)[1];
        } else {
            v0 = ((const fx32*)d)[frame];
            v1 = ((const fx32*)d + frame)[1];
        }
        return (v0 + v1) >> 1;
    }
}

/* rotation value (cos << 16 | sin) of a texture SRT track */
#pragma opt_propagation off
u32 func_020846f0(const u8* pData, u32 info, u32 data, u32 frame)
{
    const UnkRotData* p;
    u32 last;
    u32 idx0;
    u32 idx1;

    if (info & 0x20000000) {
        return data;
    }

    p = (const UnkRotData*)(pData + data);
    if (info & 0xc0000000) {
        last = (u16)info;
        if (info & 0x40000000) {
            if (frame & 1) {
                if (frame > last) {
                    frame = (last >> 1) + 1;
                } else {
                    idx0 = frame >> 1;
                    goto avg2;
                }
            } else {
                frame >>= 1;
            }
        } else {
            u32 rem = frame & 3;
            if (rem != 0) {
                if (frame > last) {
                    frame = (last >> 2) + rem;
                } else if (frame & 1) {
                    fx32 s0, c0;
                    fx32 s, c;

                    if (frame & 2) {
                        idx1 = frame >> 2;
                        idx0 = idx1 + 1;
                    } else {
                        idx0 = frame >> 2;
                        idx1 = idx0 + 1;
                    }
                    s0 = p[idx0].sin;
                    c0 = p[idx0].cos;
                    s = (s0 * 3 + p[idx1].sin) >> 2;
                    c = (c0 * 3 + p[idx1].cos) >> 2;
                    return (u16)s | (c << 16);
                } else {
                    idx0 = frame >> 2;
                    goto avg2;
                }
            } else {
                frame >>= 2;
            }
        }
    }
    return ((const u32*)p)[frame];

avg2:
    {
        const UnkRotData* q = p + idx0;
        return (u16)((q[0].sin + q[1].sin) >> 1) | (((q[0].cos + q[1].cos) >> 1) << 16);
    }
}
#pragma opt_propagation reset

void func_020847b4(const UnkResAnm* anm, u32 dataIdx, u32 frame, UnkMatAnmResult* result)
{
    const UnkTexSRTAnmData* data = UnkGetResDataByIdx_(&anm->dict, dataIdx);
    u32 flag = result->flag;
    fx32 s, t;
    u32 rot;

    s = func_02084624((const u8*)anm, data->transSInfo, data->transSData, frame);
    t = func_02084624((const u8*)anm, data->transTInfo, data->transTData, frame);
    if (s == 0 && t == 0) {
        flag |= 4;
    } else {
        flag &= ~4;
        result->transS = s;
        result->transT = t;
    }

    rot = func_020846f0((const u8*)anm, data->rotInfo, data->rotData, frame);
    if (rot == 0x10000000) {
        flag |= 2;
    } else {
        result->sinR = (fx16)rot;
        result->cosR = (fx16)(rot >> 16);
        flag &= ~2;
    }

    s = func_02084624((const u8*)anm, data->scaleSInfo, data->scaleSData, frame);
    t = func_02084624((const u8*)anm, data->scaleTInfo, data->scaleTData, frame);
    if (s == 0x1000 && t == 0x1000) {
        flag |= 1;
    } else {
        flag &= ~1;
        result->scaleS = s;
        result->scaleT = t;
    }

    result->flag = flag;
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

void func_02084870(UnkAnmObj* obj, const UnkResAnm* anm, const UnkResMdl* mdl)
{
    u32 i;
    const UnkResMat* mat = GetMat_(mdl);

    obj->funcAnm = data_0209c518;
    obj->numMapData = mdl->info.numMat;
    MI_CpuFillU16(0, obj->mapData, obj->numMapData * sizeof(u16));

    for (i = 0; i < anm->dict.numEntry; i++) {
        int idx = GetMatIdxByName_(mat, UnkGetResNameByIdx_(&anm->dict, i));
        if (idx >= 0) {
            obj->mapData[idx] = (u16)(i | 0x100);
        }
    }
}

void func_02084904(UnkMatAnmResult* result, const UnkAnmObj* obj, u32 dataIdx)
{
    func_020847b4(obj->resAnm, (u16)dataIdx, obj->frame >> 12, result);
    result->prmTexImage = (result->prmTexImage & ~0xc0000000) | 0x40000000;
    result->flag |= 8;
}
