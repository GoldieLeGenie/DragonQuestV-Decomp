#include "g3d_internal.h"

#pragma thumb on

// Joint animation resource
typedef struct UnkResJntAnm {
    u8 anmHeader[4]; // 0x00
    u16 numFrame;    // 0x04
    u16 numNode;     // 0x06
    u32 flag;        // 0x08
    u32 ofsRot3;     // 0x0C
    u32 ofsRot5;     // 0x10
    u16 ofsTag[1];   // 0x14
} UnkResJntAnm;

typedef struct UnkScale32 {
    fx32 s;
    fx32 inv;
} UnkScale32;

typedef struct UnkScale16 {
    fx16 s;
    fx16 inv;
} UnkScale16;

extern UnkAnmFunc data_0209c514;   // default joint animation function
/* for each pivot index the 4 other matrix elements set by a pivot-compressed rotation (also used by g3d_anm_jnt_rot.c) */
const u8 data_0208ec3c[9][4] = {{4, 5, 7, 8}, {3, 5, 6, 8}, {3, 4, 6, 7}, {1, 2, 7, 8}, {0, 2, 6, 8},
                                {0, 1, 6, 7}, {1, 2, 4, 5}, {0, 2, 3, 5}, {0, 1, 3, 4}};

void func_020835bc(const UnkResJntAnm* res, u32 idx, fx32 frame, NNSG3dJntAnmResult* r);
void func_0208386c(fx32* out, fx32 frame, const u32* p, const UnkResJntAnm* res);
void func_0208395c(fx32* out, fx32 frame, const u32* p, const UnkResJntAnm* res);
void func_02083a74(fx32* out, fx32 frame, const u32* p, const UnkResJntAnm* res);
void func_02083bbc(fx32* out, fx32 frame, const u32* p, const UnkResJntAnm* res);
void func_02083ce8(MtxFx33* out, fx32 frame, const u32* p, const UnkResJntAnm* res);
void func_02083f9c(MtxFx33* out, fx32 frame, const u32* p, const UnkResJntAnm* res);
BOOL func_0208420c(MtxFx33* out, const void* rot3, const void* rot5, u32 info);

// Initializes an animation object for a joint animation
void func_02083370(NNSG3dAnmObj* obj, const UnkResJntAnm* res, const NNSG3dResMdl* mdl) {
    u32 i;

    obj->resAnm = (void*)res;
    obj->funcAnm = data_0209c514;
    MI_CpuFillU16(0, obj->mapData, (obj->numMapData = mdl->info.numNode) * 2);

    {
        const u16* ofsTag = res->ofsTag;
        for (i = 0; i < res->numNode; i++) {
            obj->mapData[i] = (*(const u32*)((u8*)res + ofsTag[i]) >> 24) | 0x100;
        }
    }
}

// Default joint animation function
void func_020833bc(NNSG3dJntAnmResult* r, const NNSG3dAnmObj* obj, u32 idx) {
    const UnkResJntAnm* res = (const UnkResJntAnm*)obj->resAnm;
    fx32 frame;

    if (obj->frame >= (res->numFrame << 12)) {
        frame = (res->numFrame << 12) - 1;
    } else if (obj->frame < 0) {
        frame = 0;
    } else {
        frame = obj->frame;
    }
    func_020835bc(res, idx, frame, r);
}

// Gets the translation of the current node from the model
void func_020833e0(NNSG3dJntAnmResult* r) {
    const UnkResNodeData* nd = GetNodeDataByIdx(data_02124e18->pResNodeInfo, data_02124e18->c[1]);
    const fx32* p = (const fx32*)(nd + 1);

    if (nd->flag & 1) {
        r->flag |= 4;
    } else {
        r->trans.x = p[0];
        r->trans.y = p[1];
        r->trans.z = p[2];
    }
}

// Gets the scale of the current node from the model
void func_02083440(NNSG3dJntAnmResult* r) {
    NNSG3dRS* rs = data_02124e18;
    const u8* c = rs->c;
    const UnkResNodeData* nd = GetNodeDataByIdx(rs->pResNodeInfo, c[1]);
    const u8* p = (const u8*)(nd + 1);

    if (!(nd->flag & 1)) {
        p += 0xc;
    }
    if (!(nd->flag & 2)) {
        if (nd->flag & 8) {
            p += 4;
        } else {
            p += 0x10;
        }
    }
    rs->funcJntScale(r, p, c, nd->flag);
}

// Gets the rotation of the current node from the model
void func_020834a4(NNSG3dJntAnmResult* r) {
    long idxPivot;
    const UnkResNodeData* nd = GetNodeDataByIdx(data_02124e18->pResNodeInfo, data_02124e18->c[1]);
    const fx16* p = (const fx16*)(nd + 1);

    if (!(nd->flag & 1)) {
        p += 6;
    }

    if (!(nd->flag & 2)) {
        if (nd->flag & 8) {
            fx32 A;
            fx32 B;

            A = p[0];
            B = p[1];
            idxPivot = (nd->flag & 0xf0) >> 4;

            MI_CpuClear24(&r->rot);
            ((fx32*)&r->rot)[idxPivot] = (nd->flag & 0x100) ? -FX32_ONE : FX32_ONE;
            ((fx32*)&r->rot)[data_0208ec3c[idxPivot][0]] = A;
            ((fx32*)&r->rot)[data_0208ec3c[idxPivot][1]] = B;
            ((fx32*)&r->rot)[data_0208ec3c[idxPivot][2]] = (nd->flag & 0x200) ? -B : B;
            ((fx32*)&r->rot)[data_0208ec3c[idxPivot][3]] = (nd->flag & 0x400) ? -A : A;
        } else {
            r->rot._00 = nd->_00;
            r->rot._01 = p[0];
            r->rot._02 = p[1];
            r->rot._10 = p[2];
            r->rot._11 = p[3];
            r->rot._12 = p[4];
            r->rot._20 = p[5];
            r->rot._21 = p[6];
            r->rot._22 = p[7];
        }
    } else {
        r->flag |= 2;
    }
}

// Gets one scale component (scale and inverse scale), constant or animated
static inline void GetScaleComp(fx32* s, fx32* inv, u32 isConst, BOOL interp, fx32 frame, const u32* data,
                                const UnkResJntAnm* res) {
    if (!isConst) {
        fx32 tmp[2];
        if (interp) {
            func_02083bbc(tmp, frame, data, res);
        } else {
            func_02083a74(tmp, frame, data, res);
        }
        *s = tmp[0];
        *inv = tmp[1];
    } else {
        const u32* q = data;
        *s = q[0];
        *inv = q[1];
    }
}

// Calculates the joint animation result of a node
void func_020835bc(const UnkResJntAnm* res, u32 idx, fx32 frame, NNSG3dJntAnmResult* r) {
    u32 flag;
    BOOL interp;
    const u32* p;
    const u32* tag = (const u32*)((u8*)res + res->ofsTag[idx]);
    struct {
        VecFx32 s;
        VecFx32 inv;
    } scale;

    flag = *tag;

    if (flag & 1) {
        r->flag = 7;
    } else {
        p = tag + 1;
        interp = ((frame & 0xfff) && (res->flag & 1)) ? TRUE : FALSE;
        r->flag = 0;

        if (!(flag & 6)) {
            if (!(flag & 8)) {
                if (interp) {
                    func_0208395c(&r->trans.x, frame, p, res);
                } else {
                    func_0208386c(&r->trans.x, frame, p, res);
                }
                p += 2;
            } else {
                r->trans.x = (fx32)*p;
                p++;
            }

            if (!(flag & 0x10)) {
                if (interp) {
                    func_0208395c(&r->trans.y, frame, p, res);
                } else {
                    func_0208386c(&r->trans.y, frame, p, res);
                }
                p += 2;
            } else {
                r->trans.y = (fx32)*p++;
            }

            if (!(flag & 0x20)) {
                if (interp) {
                    func_0208395c(&r->trans.z, frame, p, res);
                } else {
                    func_0208386c(&r->trans.z, frame, p, res);
                }
                p += 2;
            } else {
                r->trans.z = (fx32)*p++;
            }
        } else if (flag & 2) {
            r->flag |= 4;
        } else {
            func_020833e0(r);
        }

        if (!(flag & 0xc0)) {
            if (!(flag & 0x100)) {
                if (interp) {
                    func_02083f9c(&r->rot, frame, p, res);
                } else {
                    func_02083ce8(&r->rot, frame, p, res);
                }
                p += 2;
            } else {
                if (func_0208420c(&r->rot, (u8*)res + res->ofsRot3, (u8*)res + res->ofsRot5, *p)) {
                    fx32 x = (r->rot._01 * r->rot._12 - r->rot._02 * r->rot._11) >> 12;
                    fx32 y = (r->rot._02 * r->rot._10 - r->rot._00 * r->rot._12) >> 12;
                    fx32 z = (r->rot._00 * r->rot._11 - r->rot._01 * r->rot._10) >> 12;
                    r->rot._20 = x;
                    r->rot._21 = y;
                    r->rot._22 = z;
                }
                p++;
            }
        } else if (flag & 0x40) {
            r->flag |= 2;
        } else {
            func_020834a4(r);
        }

        if (!(flag & 0x600)) {
            GetScaleComp(&scale.s.x, &scale.inv.x, flag & 0x800, interp, frame, p, res);
            GetScaleComp(&scale.s.y, &scale.inv.y, flag & 0x1000, interp, frame, p + 2, res);
            GetScaleComp(&scale.s.z, &scale.inv.z, flag & 0x2000, interp, frame, p + 4, res);
        } else if (flag & 0x200) {
            r->flag |= 1;
        } else {
            func_02083440(r);
            return;
        }
    }

    data_02124e18->funcJntScale(r, &scale, data_02124e18->c, (r->flag & 1) ? 4 : 0);
}
// Gets a translation value of a frame (no interpolation between frames)
void func_0208386c(fx32* out, fx32 frame, const u32* p, const UnkResJntAnm* res) {
    u32 b;
    u32 a;
    u32 lastInterp;
    u32 info;
    u32 idx;
    u32 f;
    const void* data;

    f = (u32)(frame >> 12);
    data = (u8*)res + p[1];
    info = p[0];

    if (info & 0xc0000000) {
        lastInterp = (info & 0x1fff0000) >> 16;

        if (info & 0x40000000) {
            if (f & 1) {
                if (f > lastInterp) {
                    f = (lastInterp >> 1) + 1;
                    goto direct;
                } else {
                    idx = f >> 1;
                    goto half;
                }
            } else {
                f >>= 1;
                goto direct;
            }
        } else {
            if (f & 3) {
                if (f > lastInterp) {
                    f = (lastInterp >> 2) + (f & 3);
                    goto direct;
                }
                if (f & 1) {
                    if (f & 2) {
                        b = f >> 2;
                        a = b + 1;
                    } else {
                        a = f >> 2;
                        b = a + 1;
                    }
                    if (info & 0x20000000) {
                        const fx16* d = (const fx16*)data;
                        fx32 t = d[a] * 3;
                        *out = (t + d[b]) >> 2;
                    } else {
                        const fx32* d = (const fx32*)data;
                        fx64 t = (fx64)d[a] * 3;
                        *out = (fx32)((t + d[b]) >> 2);
                    }
                    return;
                } else {
                    idx = f >> 2;
                    goto half;
                }
            } else {
                f >>= 2;
                goto direct;
            }
        }

    half:
        if (info & 0x20000000) {
            *out = (((const fx16*)data)[idx] + *((const fx16*)data + idx + 1)) >> 1;
        } else {
            *out = (((const fx32*)data)[idx] >> 1) + (*((const fx32*)data + idx + 1) >> 1);
        }
        return;
    }

direct:
    if (info & 0x20000000) {
        *out = ((const fx16*)data)[f];
    } else {
        *out = ((const fx32*)data)[f];
    }
}

// Gets a translation value of a frame (interpolated)
void func_0208395c(fx32* out, fx32 frame, const u32* p, const UnkResJntAnm* res) {
    const void* data;
    u32 f;
    u32 info;

    f = (u32)(frame >> 12);
    data = (u8*)res + p[1];
    info = p[0];

    if (f == res->numFrame - 1) {
        if (info & 0xc0000000) {
            if (info & 0x40000000) {
                f = (f >> 1) + (f & 1);
            } else {
                f = (f >> 2) + (f & 3);
            }
        }

        if (res->flag & 2) {
            fx32 frac = frame & 0xfff;
            fx32 v0, v1;
            if (info & 0x20000000) {
                v0 = ((const fx16*)data)[f];
                v1 = ((const fx16*)data)[0];
            } else {
                v0 = ((const fx32*)data)[f];
                v1 = ((const fx32*)data)[0];
            }
            *out = v0 + (((v1 - v0) * frac) >> 12);
        } else {
            if (info & 0x20000000) {
                *out = ((const fx16*)data)[f];
            } else {
                *out = ((const fx32*)data)[f];
            }
        }
    } else {
        fx32 mul;
        int shift;
        fx32 frac;
        fx32 v0, v1;

        if (info & 0xc0000000) {
            u32 lastInterp = (info & 0x1fff0000) >> 16;
            if (info & 0x40000000) {
                if (f >= lastInterp) {
                    f = lastInterp >> 1;
                    goto step1;
                }
                frac = frame & 0x1fff;
                f >>= 1;
                mul = 2;
                shift = 1;
            } else {
                if (f >= lastInterp) {
                    f = (f >> 2) + (f & 3);
                    goto step1;
                }
                frac = frame & 0x3fff;
                f >>= 2;
                mul = 4;
                shift = 2;
            }
        } else {
        step1:
            frac = frame & 0xfff;
            mul = 1;
            shift = 0;
        }

        if (info & 0x20000000) {
            v0 = ((const fx16*)data)[f];
            v1 = *((const fx16*)data + f + 1);
        } else {
            v0 = ((const fx32*)data)[f];
            v1 = *((const fx32*)data + f + 1);
        }
        *out = (fx32)(v0 * mul + (((v1 - v0) * frac) >> 12)) >> shift;
    }
}

// Gets a scale value pair of a frame (no interpolation between frames)
#pragma opt_dead_assignments off
void func_02083a74(fx32* out, fx32 frame, const u32* p, const UnkResJntAnm* res) {
    u32 idx;
    u32 lastInterp;
    const void* data;
    u32 a;
    u32 info;
    u32 b;
    u32 f;

    f = (u32)(frame >> 12);
    data = (u8*)res + p[1];
    info = p[0];

    if (info & 0xc0000000) {
        lastInterp = (info & 0x1fff0000) >> 16;

        if (info & 0x40000000) {
            if (f & 1) {
                if (f > lastInterp) {
                    f = (lastInterp >> 1) + 1;
                    goto direct;
                } else {
                    idx = f >> 1;
                    goto half;
                }
            } else {
                f >>= 1;
                goto direct;
            }
        } else {
            u32 rem = f & 3;
            if (rem) {
                if (f > lastInterp) {
                    f = (lastInterp >> 2) + rem;
                    goto direct;
                }
                if (f & 1) {
                    if (f & 2) {
                        b = f >> 2;
                        a = b + 1;
                    } else {
                        a = f >> 2;
                        b = a + 1;
                    }
                    if (info & 0x20000000) {
                        const UnkScale16* d = (const UnkScale16*)data;
                        fx32 x;
                        x = d[a].s;
                        out[0] = (d[b].s + (x + x * 2)) >> 2;
                        x = d[a].inv;
                        out[1] = (d[b].inv + (x + x * 2)) >> 2;
                    } else {
                        const UnkScale32* d = (const UnkScale32*)data;
                        fx32 x;
                        fx32 y;
                        x = d[a].s;
                        y = d[b].s;
                        out[0] = (fx32)(((fx64)x * 3 - -(fx64)y) >> 2);
                        out[1] = (fx32)(((fx64)d[a].inv * 3 - -(fx64)d[b].inv) >> 2);
                    }
                    return;
                } else {
                    idx = f >> 2;
                    goto half;
                }
            } else {
                f >>= 2;
                goto direct;
            }
        }

    }

direct:
    if (info & 0x20000000) {
        const UnkScale16* d = (const UnkScale16*)data;
        out[0] = d[f].s;
        out[1] = d[f].inv;
    } else {
        const UnkScale32* d = (const UnkScale32*)data;
        out[0] = d[f].s;
        out[1] = d[f].inv;
    }
    return;

half:
    if (info & 0x20000000) {
        const UnkScale16* d = (const UnkScale16*)data;
        out[0] = (d[idx].s + (d + idx + 1)->s) >> 1;
        out[1] = ((d + idx)->inv + (d + idx + 1)->inv) >> 1;
    } else {
        const UnkScale32* d = (const UnkScale32*)data;
        out[0] = (d[idx].s + (d + idx + 1)->s) >> 1;
        out[1] = ((d + idx)->inv + (d + idx + 1)->inv) >> 1;
    }
}

#pragma opt_dead_assignments reset

// Gets a scale value pair of a frame (interpolated)
void func_02083bbc(fx32* out, fx32 frame, const u32* p, const UnkResJntAnm* res) {
    u32 info = p[0];
    const void* data = (u8*)res + p[1];
    u32 f = (u32)(frame >> 12);
    u32 next;
    fx32 frac;
    fx32 mul;
    int shift;
    fx32 s0, inv0, s1, inv1;

    if (f == res->numFrame - 1) {
        if (info & 0xc0000000) {
            if (info & 0x40000000) {
                f = (f >> 1) + (f & 1);
            } else {
                f = (f >> 2) + (f & 3);
            }
        }

        if (res->flag & 2) {
            next = 0;
            goto step1;
        }

        if (info & 0x20000000) {
            const UnkScale16* d = (const UnkScale16*)data;
            out[0] = d[f].s;
            out[1] = d[f].inv;
        } else {
            const UnkScale32* d = (const UnkScale32*)data;
            out[0] = d[f].s;
            out[1] = d[f].inv;
        }
        return;
    }

    if (info & 0xc0000000) {
        u32 lastInterp = (info & 0x1fff0000) >> 16;
        if (info & 0x40000000) {
            if (f >= lastInterp) {
                f = lastInterp >> 1;
                next = f + 1;
                goto step1;
            }
            f >>= 1;
            next = f + 1;
            frac = frame & 0x1fff;
            mul = 2;
            shift = 1;
        } else {
            if (f >= lastInterp) {
                f = (f >> 2) + (f & 3);
                next = f + 1;
                goto step1;
            }
            f >>= 2;
            next = f + 1;
            frac = frame & 0x3fff;
            mul = 4;
            shift = 2;
        }
    } else {
        next = f + 1;
    step1:
        frac = frame & 0xfff;
        mul = 1;
        shift = 0;
    }

    if (info & 0x20000000) {
        const UnkScale16* d = (const UnkScale16*)data;
        s0 = d[f].s;
        inv0 = d[f].inv;
        s1 = d[next].s;
        inv1 = d[next].inv;
    } else {
        const UnkScale32* d = (const UnkScale32*)data;
        s0 = d[f].s;
        inv0 = d[f].inv;
        s1 = d[next].s;
        inv1 = d[next].inv;
    }
    out[0] = (fx32)(s0 * mul + (((s1 - s0) * frac) >> 12)) >> shift;
    out[1] = (fx32)(inv0 * mul + (((inv1 - inv0) * frac) >> 12)) >> shift;
}
