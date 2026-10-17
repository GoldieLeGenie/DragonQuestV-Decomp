#include "g3d_types.h"

/* Default blend functions for material / joint / visibility animation results. */

typedef struct UnkVecFx32 {
    s32 unk_00;                 // 0x00 x
    s32 unk_04;                 // 0x04 y
    s32 unk_08;                 // 0x08 z
} UnkVecFx32;

/* Joint animation result (0x58 bytes). */
typedef struct UnkJntAnmResult {
    u32 unk_00;                 // 0x00 flags: 1 scale one, 2 rotation zero, 4 translation zero, 8/0x10 extra scales one
    UnkVecFx32 unk_04;          // 0x04 scale
    UnkVecFx32 unk_10;          // 0x10 extra scale 0
    UnkVecFx32 unk_1c;          // 0x1C extra scale 1
    UnkVecFx32 unk_28;          // 0x28 rotation row 0
    UnkVecFx32 unk_34;          // 0x34 rotation row 1
    UnkVecFx32 unk_40;          // 0x40 rotation row 2
    UnkVecFx32 unk_4c;          // 0x4C translation
} UnkJntAnmResult;

extern void MI_CpuFill(u32 value, void* dest, u32 size);
extern void MI_CpuCopyU32(const void* src, void* dest, u32 size);
extern s32 FX_Divide(s32 numer, s32 denom);
extern void func_0208a24c(const UnkVecFx32* a, const UnkVecFx32* b, UnkVecFx32* axb);
extern void func_0208a330(const UnkVecFx32* src, UnkVecFx32* dst);

#pragma thumb on

BOOL func_020806e4(void* result, UnkAnmObj* anm, u32 matID) {
    BOOL ret = FALSE;

    while (anm != NULL) {
        if (matID < anm->unk_19) {
            u16 data = anm->unk_1a[matID];

            if ((data & 0x300) == 0x100 && anm->unk_0c != NULL) {
                anm->unk_0c(result, anm, data & 0xff);
                ret = TRUE;
            }
        }
        anm = anm->unk_10;
    }
    return ret;
}

#pragma thumb off

/* Adds src * ratio to dst (or ratio * 1.0 when isOne is set). */
void func_02080728(UnkVecFx32* dst, const UnkVecFx32* src, s32 ratio, u32 isOne) {
    if (isOne) {
        dst->unk_00 += ratio;
        dst->unk_04 += ratio;
        dst->unk_08 += ratio;
    } else {
        dst->unk_00 += (ratio * src->unk_00) >> 12;
        dst->unk_04 += (ratio * src->unk_04) >> 12;
        dst->unk_08 += (ratio * src->unk_08) >> 12;
    }
}

BOOL func_02080798(UnkJntAnmResult* result, UnkAnmObj* anm, u32 jntID) {
    s32 sumRatio;
    UnkAnmObj* p;
    int num;
    UnkAnmObj* last;
    int count;
    UnkVecFx32 defRow0;
    UnkVecFx32 defRow2;

    if (anm == NULL) {
        return FALSE;
    }

    if (anm->unk_10 == NULL) {
        if (jntID < anm->unk_19) {
            u16 data = anm->unk_1a[jntID];

            if ((data & 0x300) == 0x100) {
                if (anm->unk_0c == NULL) {
                    return FALSE;
                }
                anm->unk_0c(result, anm, data & 0xff);
                return TRUE;
            }
            return FALSE;
        }
        return FALSE;
    }

    sumRatio = 0;
    num = 0;
    count = 0;
    p = anm;
    do {
        if (jntID < p->unk_19 && (p->unk_1a[jntID] & 0x300) == 0x100) {
            s32 ratio = p->unk_04;

            if (ratio > 0x1000) {
                sumRatio += 0x1000;
            } else if (ratio > 0) {
                sumRatio += ratio;
            }
            last = p;
            num++;
        }
        p = p->unk_10;
    } while (p != NULL);

    if (sumRatio == 0) {
        return FALSE;
    }
    if (num == 1) {
        u16 data = last->unk_1a[jntID];

        if (last->unk_0c == NULL) {
            return FALSE;
        }
        last->unk_0c(result, last, data & 0xff);
        return TRUE;
    }

    MI_CpuFill(0, result, sizeof(UnkJntAnmResult));
    result->unk_00 = 0xffffffff;
    do {
        UnkJntAnmResult r;

        if (jntID < anm->unk_19) {
            u16 data = anm->unk_1a[jntID];

            if ((data & 0x300) == 0x100 && anm->unk_04 > 0 && anm->unk_0c != NULL) {
                s32 ratio;

                anm->unk_0c(&r, anm, data & 0xff);
                if (count == 0) {
                    MI_CpuCopyU32(&r.unk_28, &defRow0, sizeof(UnkVecFx32));
                    MI_CpuCopyU32(&r.unk_40, &defRow2, sizeof(UnkVecFx32));
                }
                if (sumRatio == 0x1000) {
                    ratio = anm->unk_04;
                } else {
                    ratio = FX_Divide(anm->unk_04, sumRatio);
                }
                func_02080728(&result->unk_04, &r.unk_04, ratio, r.unk_00 & 1);
                func_02080728(&result->unk_10, &r.unk_10, ratio, r.unk_00 & 8);
                func_02080728(&result->unk_1c, &r.unk_1c, ratio, r.unk_00 & 0x10);
                if (!(r.unk_00 & 4)) {
                    result->unk_4c.unk_00 += (s32)(((s64)ratio * r.unk_4c.unk_00) >> 12);
                    result->unk_4c.unk_04 += (s32)(((s64)ratio * r.unk_4c.unk_04) >> 12);
                    result->unk_4c.unk_08 += (s32)(((s64)ratio * r.unk_4c.unk_08) >> 12);
                }
                if (!(r.unk_00 & 2)) {
                    result->unk_28.unk_00 += (ratio * r.unk_28.unk_00) >> 12;
                    result->unk_28.unk_04 += (ratio * r.unk_28.unk_04) >> 12;
                    result->unk_28.unk_08 += (ratio * r.unk_28.unk_08) >> 12;
                    result->unk_34.unk_00 += (ratio * r.unk_34.unk_00) >> 12;
                    result->unk_34.unk_04 += (ratio * r.unk_34.unk_04) >> 12;
                    result->unk_34.unk_08 += (ratio * r.unk_34.unk_08) >> 12;
                } else {
                    result->unk_28.unk_00 += ratio;
                    result->unk_34.unk_04 += ratio;
                }
                result->unk_00 &= r.unk_00;
            }
        }
        anm = anm->unk_10;
        count++;
    } while (anm != NULL);

    func_0208a24c(&result->unk_28, &result->unk_34, &result->unk_40);
    if (result->unk_28.unk_00 == 0 && result->unk_28.unk_04 == 0 && result->unk_28.unk_08 == 0) {
        MI_CpuCopyU32(&defRow0, &result->unk_28, sizeof(UnkVecFx32));
    } else {
        func_0208a330(&result->unk_28, &result->unk_28);
    }
    if (result->unk_40.unk_00 == 0 && result->unk_40.unk_04 == 0 && result->unk_40.unk_08 == 0) {
        MI_CpuCopyU32(&defRow2, &result->unk_40, sizeof(UnkVecFx32));
    } else {
        func_0208a330(&result->unk_40, &result->unk_40);
    }
    func_0208a24c(&result->unk_40, &result->unk_28, &result->unk_34);
    return TRUE;
}

#pragma thumb on

BOOL func_02080b84(u32* result, UnkAnmObj* anm, u32 nodeID) {
    BOOL ret;

    *result = 0;
    ret = FALSE;
    do {
        if (nodeID < anm->unk_19) {
            u16 data = anm->unk_1a[nodeID];

            if ((data & 0x300) == 0x100 && anm->unk_0c != NULL) {
                u32 r;

                anm->unk_0c(&r, anm, data & 0xff);
                *result |= r;
                ret = TRUE;
            }
        }
        anm = anm->unk_10;
    } while (anm != NULL);
    return ret;
}

/* default animation functions */
void func_02084574(void* result, UnkAnmObj* anm, u32 dataIdx); // material (g3d_anm_mat.c)
void func_02084aac(void* result, UnkAnmObj* anm, u32 dataIdx); // texture pattern (g3d_anm_texpat.c)
void func_02084904(void* result, UnkAnmObj* anm, u32 dataIdx); // texture SRT (g3d_anm_texsrt.c)
void func_020833bc(void* result, UnkAnmObj* anm, u32 dataIdx); // joint (g3d_anm_jnt.c)
void func_02084b24(void* result, UnkAnmObj* anm, u32 dataIdx); // visibility (g3d_anm_vis.c)
/* animation object init functions */
void func_020844e0(UnkAnmObj* anm, void* resAnm, const UnkResMdlInfo* resMdl); // material color (g3d_anm_mat.c)
void func_02084934(UnkAnmObj* anm, void* resAnm, const UnkResMdlInfo* resMdl); // texture pattern (g3d_anm_texpat.c)
void func_02084870(UnkAnmObj* anm, void* resAnm, const UnkResMdlInfo* resMdl); // texture SRT (g3d_anm_texsrt.c)
void func_02084af0(UnkAnmObj* anm, void* resAnm, const UnkResMdlInfo* resMdl); // visibility (g3d_anm_vis.c)
void func_02083370(UnkAnmObj* anm, void* resAnm, const UnkResMdlInfo* resMdl); // joint (g3d_anm_jnt.c)

/* default blend functions (set into render objects by g3d_kernel.c) */
UnkBlendFunc data_0209c52c = (UnkBlendFunc)func_020806e4; // material
UnkBlendFunc data_0209c528 = (UnkBlendFunc)func_02080798; // joint
UnkBlendFunc data_0209c524 = (UnkBlendFunc)func_02080b84; // visibility

/* default animation functions (set into animation objects by their init functions) */
UnkAnmFunc data_0209c520 = func_02084574; // material
UnkAnmFunc data_0209c51c = func_02084aac; // texture pattern
UnkAnmFunc data_0209c518 = func_02084904; // texture SRT
UnkAnmFunc data_0209c514 = func_020833bc; // joint
UnkAnmFunc data_0209c510 = func_02084b24; // visibility

/* number of used entries in data_0209c530 */
u32 data_0209c50c = 5;

/* animation object init functions per resource category ('M' / 'J' / 'V') and sub category */
UnkAnmInitEntry data_0209c530[10] = {
    {'M', 0x4d41, func_020844e0},
    {'M', 0x5450, func_02084934},
    {'M', 0x5441, func_02084870},
    {'V', 0x5641, func_02084af0},
    {'J', 0x4341, func_02083370},
};
