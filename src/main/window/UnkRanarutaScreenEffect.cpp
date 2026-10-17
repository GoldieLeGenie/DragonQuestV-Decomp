#pragma ipa file
#include "main/window/ScreenEffectManager.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/object/DSSAObject.hpp"
#include "nitro/g3.hpp"

inline bool window::UnkScreenEffect::isActive()
{
    return (flag_ & FLAG_ACTIVE) ? true : false;
}

THUMB window::UnkScreenEffectCamera::UnkScreenEffectCamera()
{
}

THUMB window::UnkScreenEffectCamera::~UnkScreenEffectCamera()
{
}

THUMB window::UnkScreenEffectCamera* window::UnkScreenEffectCamera::unkfunc_02028cc4()
{
    static UnkScreenEffectCamera camera;
    return &camera;
}

static const dss::Fix32Vector3 s_target(0, 0, 0);
static dss::Vector3<short> s_angle(0, 0, 0);
static const float s_distanceValue = 34.2901f;
static dss::Fix32 s_distance(s_distanceValue);
static dss::Fix32 s_unk(2L);
static short s_fov = 10;
VecFx32 unusedScreenEffectPosition;     // not linked: unreferenced, only takes part in the data layout

THUMB void window::UnkScreenEffectCamera::unkfunc_02028d00()
{
    camera_.setup();
    camera_.setTarget(s_target);
    camera_.setDistance(s_distance);
    camera_.setAngle(s_angle);
    camera_.setFOV2(s_fov);
}

THUMB void window::UnkScreenEffectCamera::unkfunc_02028d40()
{
}

THUMB void window::UnkScreenEffectCamera::unkfunc_02028d44()
{
    camera_.applyCamera();
}

THUMB void window::UnkRanarutaScreenEffect::setup()
{
    unk_0c = 32;
    unk_10 = 24;
    alpha_ = 31;
    unk_08 = dss::Fix32(0x8000);
    for (int i = 0; i < 10; i++) {
        wavePanel_[i] = i * 2 + 0x180;
    }
    counter_ = 0;
    unk_20 = 0;
    waveSpeed_ = -250;
    UnkScreenEffect::setup();
}

THUMB void window::UnkRanarutaScreenEffect::draw()
{
    if (isActive() == false) {
        return;
    }
    dss::g_DISPLAYPLUGIN_DOUBLE3D.SetBlur(2, 14);
    UnkScreenEffectCamera::unkfunc_02028cc4()->unkfunc_02028d44();
    {
        VecFx32 scale = {FX32_ONE, FX32_ONE, FX32_ONE};
        VecFx32 trans = {0, 0, 0};
        MtxFx33 baseRot;
        func_02088970(&baseRot);
        func_0208032c(&scale);
        func_02070360(&baseRot, &data_02124bb4.prmBaseRot);
        data_02124bb4.flag &= ~0xa4;
        func_02080308((dss::Fix32Vector3*)&trans);
        func_020802dc();
        func_02082604();
    }
    for (int y = 1; y < 23; y++) {
        for (int x = 1; x < 31; x++) {
            int index = x + y * 32;
            for (int k = 0; k < 4; k++) {
                short z = data_020c32a0[index].vertex[k][2];
                short average = (data_020c32a0[index - 1].vertex[k][2] + data_020c32a0[index + 1].vertex[k][2] + data_020c32a0[index - 24].vertex[k][2] + data_020c32a0[index + 24].vertex[k][2]) >> 2;
                z += (short)(average - z) >> 2;
                unkfunc_020290c8(index, k, z);
            }
        }
    }
    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 24; y++) {
            int index = y + x * 24;
            G3_PushMtx();
            G3_Scale(0x8000, 0x8000, 0x8000);
            data_020c32a0[index].z += 80;
            if (unkfunc_0204ccd0() & 1) {
                G3_Translate(data_020c32a0[index].x, data_020c32a0[index].y + counter_, data_020c32a0[index].z);
            } else {
                G3_Translate(data_020c32a0[index].x, data_020c32a0[index].y - counter_, data_020c32a0[index].z);
            }
            unkfunc_020287e8(24);
            G3_Begin(1);
            for (int k = 0; k < 4; k++) {
                data_020c32a0[index].vertex[k][2] -= 40;
                int color = dss::clamp<int>(data_020c32a0[index].vertex[k][2] / 100 + 31, 0, 31);
                if (morningFlag_) {
                    G3_Color(GX_RGB(31, 31, color));
                } else {
                    G3_Color(GX_RGB(color, color, 31));
                }
                G3_TexCoord(data_020c32a0[index].texCoord[k][0], data_020c32a0[index].texCoord[k][1]);
                G3_Vtx(data_020c32a0[index].vertex[k][0], data_020c32a0[index].vertex[k][1], data_020c32a0[index].vertex[k][2]);
            }
            G3_PopMtx(1);
        }
    }
    unk_20++;
    counter_++;
    for (int i = 0; i < 10; i++) {
        unkfunc_020290c8(wavePanel_[i], 0, waveHeight_);
        unkfunc_020290c8(wavePanel_[i], 1, waveHeight_);
        unkfunc_020290c8(wavePanel_[i], 2, waveHeight_);
        unkfunc_020290c8(wavePanel_[i], 3, waveHeight_);
    }
    waveHeight_ += waveSpeed_;
    if (waveHeight_ < -10000 || (waveHeight_ >= -2000 && waveSpeed_ > 0)) {
        waveSpeed_ = -waveSpeed_;
    }
}

THUMB bool window::UnkRanarutaScreenEffect::isEnd()
{
    return counter_ > 60;
}

THUMB void window::UnkRanarutaScreenEffect::unkfunc_020290c8(int index, int vertex, short z)
{
    int up = index - 24;
    int down = index + 24;
    data_020c32a0[index].vertex[vertex][2] = z;
    switch (vertex) {
    case 0:
        data_020c32a0[up].vertex[1][2] = z;
        data_020c32a0[up + 1].vertex[2][2] = z;
        data_020c32a0[index + 1].vertex[3][2] = z;
        break;
    case 1:
        data_020c32a0[down].vertex[0][2] = z;
        data_020c32a0[index + 1].vertex[2][2] = z;
        data_020c32a0[down + 1].vertex[3][2] = z;
        break;
    case 2:
        data_020c32a0[down - 1].vertex[0][2] = z;
        data_020c32a0[index - 1].vertex[1][2] = z;
        data_020c32a0[down].vertex[3][2] = z;
        break;
    case 3:
        data_020c32a0[index - 1].vertex[0][2] = z;
        data_020c32a0[up - 1].vertex[1][2] = z;
        data_020c32a0[up].vertex[2][2] = z;
        break;
    }
}
