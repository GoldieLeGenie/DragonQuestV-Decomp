#pragma once

typedef int fx32;
typedef short fx16;
typedef long long fx64;

#define FX32_SHIFT 12
#define FX32_ONE ((fx32)(1 << FX32_SHIFT))

inline fx32 FX_Mul(fx32 v1, fx32 v2)
{
    return (fx32)(((fx64)v1 * v2 + 0x800) >> FX32_SHIFT);
}

struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
};

struct VecFx16 {
    fx16 x;
    fx16 y;
    fx16 z;
};

extern "C" void func_0208a330(const VecFx32* src, VecFx32* dst);   // VEC_Normalize
extern "C" void func_0208a1dc(const VecFx32* a, const VecFx32* b, VecFx32* ab);   // VEC_Subtract
extern "C" fx32 func_0208a5d0(const VecFx32* a, const VecFx32* b);   // VEC_Distance
extern "C" void func_0208a448(const VecFx16* src, VecFx16* dst);   // VEC_Fx16Normalize

struct MtxFx43 {
    fx32 m[4][3];
};

struct MtxFx22 {
    fx32 m[2][2];
};

extern "C" void func_02088958(MtxFx22* m);   // MTX_Identity22_

struct MtxFx33 {
    fx32 m[3][3];
};

extern "C" void func_02088970(MtxFx33* m);   // MTX_Identity33_
extern "C" {
    void func_02088994(const MtxFx33* src, MtxFx33* dst, fx32 x, fx32 y, fx32 z);     // MTX_ScaleApply33
    void func_02088a54(MtxFx33* m, fx32 sinVal, fx32 cosVal);                          // MTX_RotX33_
    void func_02088a70(MtxFx33* m, fx32 sinVal, fx32 cosVal);                          // MTX_RotY33_
    void func_02088a8c(MtxFx33* m, fx32 sinVal, fx32 cosVal);                          // MTX_RotZ33_
    void MTX_Concat33(const MtxFx33* a, const MtxFx33* b, MtxFx33* ab);
    void func_02088cc4(const VecFx32* vec, const MtxFx33* m, VecFx32* dst);            // MTX_MultVec33
    void func_0208a1a8(const VecFx32* a, const VecFx32* b, VecFx32* ab);               // VEC_Add
    fx32 func_0208a210(const VecFx32* a, const VecFx32* b);                            // VEC_DotProduct
    fx32 func_0208a2d0(const VecFx32* v);                                              // VEC_Mag
    void func_0208a24c(const VecFx32* a, const VecFx32* b, VecFx32* axb);              // VEC_CrossProduct
    void func_0208a574(fx32 a, const VecFx32* v1, const VecFx32* v2, VecFx32* dst);    // VEC_MultAdd
}

struct MtxFx44 {
    fx32 m[4][4];
};

extern "C" void func_02088d9c(const MtxFx43* src, MtxFx43* dst, fx32 x, fx32 y, fx32 z);   // MTX_ScaleApply43
extern "C" {
    void func_02088d40(MtxFx43* m);                                                     // MTX_Identity43_
    void func_02088dd0(MtxFx43* m, fx32 sinVal, fx32 cosVal);                          // MTX_RotX43_
    void func_02088df0(MtxFx43* m, fx32 sinVal, fx32 cosVal);                          // MTX_RotY43_
    void func_02088e0c(MtxFx43* m, fx32 sinVal, fx32 cosVal);                          // MTX_RotZ43_
    void func_020891b4(const MtxFx43* a, const MtxFx43* b, MtxFx43* ab);               // MTX_Concat43
    void func_02089488(const VecFx32* vec, const MtxFx43* m, VecFx32* dst);            // MTX_MultVec43
    void func_02089528(const VecFx32* camPos, const VecFx32* camUp, const VecFx32* target, MtxFx43* mtx);   // MTX_LookAt
    void func_02089cf4(unsigned int fovySin, unsigned int fovyCos, fx32 aspect, fx32 n, fx32 f, fx32 scaleW, MtxFx44* mtx);   // MTX_PerspectiveW
    void func_02089e40(fx32 t, fx32 b, fx32 l, fx32 r, fx32 n, fx32 f, fx32 scaleW, MtxFx44* mtx);  // MTX_OrthoW
}
