#ifndef FX_INTERNAL_H
#define FX_INTERNAL_H

#include <nitro/types.h>
#include <nitro/reg.h>
#include <nitro/fx/fx_matrix.h>

typedef struct {
    s32 _00, _01;
    s32 _10, _11;
} UnkMtx22;

typedef struct {
    s16 x, y, z;
} UnkVecFx16;

/* fx_division */
s32  FX_Divide(s32 numer, s32 denom);
s32  FX_Inverse(s32 denom);
s64  FX_Divide64(s32 denom);
s32  FX_Sqrt(s32 value);
s64  FX_GetDivResultFx64c(void);
s32  FX_GetDivResult(void);
void FX_InvAsync(s32 denom);
s32  FX_GetSqrtResult(void);
void FX_DivAsync(s32 numer, s32 denom);

/* matrix */
void func_02088958(UnkMtx22* m);
void func_02088970(Mtx33* m);
void func_02088994(const Mtx33* src, Mtx33* dst, s32 x, s32 y, s32 z);
void func_02088a54(Mtx33* m, s32 sinVal, s32 cosVal);
void func_02088a70(Mtx33* m, s32 sinVal, s32 cosVal);
void func_02088a8c(Mtx33* m, s32 sinVal, s32 cosVal);
void MTX_Concat33(const Mtx33* a, const Mtx33* b, Mtx33* ab);
void func_02088cc4(const Vec* vec, const Mtx33* m, Vec* dst);
void func_02088d40(Mtx43* m);
void func_02088d68(const Mtx43* src, Mtx44* dst);
void func_02088d9c(const Mtx43* src, Mtx43* dst, s32 x, s32 y, s32 z);
void func_02088dd0(Mtx43* m, s32 sinVal, s32 cosVal);
void func_02088df0(Mtx43* m, s32 sinVal, s32 cosVal);
void func_02088e0c(Mtx43* m, s32 sinVal, s32 cosVal);
s32  func_02088e28(const Mtx43* src, Mtx43* dst);
void func_020891b4(const Mtx43* a, const Mtx43* b, Mtx43* ab);
void func_02089488(const Vec* vec, const Mtx43* m, Vec* dst);
void func_02089630(Mtx44* m);
void func_0208965c(const Mtx44* src, Mtx43* dst);
void func_02089690(const Mtx44* a, const Mtx44* b, Mtx44* ab);
void func_02089cf4(s32 fovySin, s32 fovyCos, s32 aspect, s32 n, s32 f, s32 scaleW, Mtx44* mtx);
void func_02089e40(s32 t, s32 b, s32 l, s32 r, s32 n, s32 f, s32 scaleW, Mtx44* mtx);

/* vector */
void func_0208a1a8(const Vec* a, const Vec* b, Vec* ab);
void func_0208a1dc(const Vec* a, const Vec* b, Vec* ab);
s32  func_0208a210(const Vec* a, const Vec* b);
void func_0208a24c(const Vec* a, const Vec* b, Vec* axb);
s32  func_0208a2d0(const Vec* v);
void func_0208a330(const Vec* src, Vec* dst);
void func_0208a448(const UnkVecFx16* src, UnkVecFx16* dst);
void func_0208a574(s32 a, const Vec* v1, const Vec* v2, Vec* dst);
s32  func_0208a5d0(const Vec* a, const Vec* b);

void MI_CpuCopy48(const void* src, void* dest);

#endif
