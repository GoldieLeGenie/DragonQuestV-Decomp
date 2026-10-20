#include "main/window/ScreenEffectManager.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/object/DSSAObject.hpp"
#include "nitro/g3.hpp"
#include "nitro/fx/fx_trig.h"
#include "nnsys/g3d.hpp"

inline bool window::UnkScreenEffect::isActive()
{
    return (flag_ & FLAG_ACTIVE) ? true : false;
}

THUMB void window::ScreenEffectBattle::setup()
{
    UnkScreenEffect::setup();
    tilesX_ = 0x20;
    tilesY_ = 0x18;
    alpha_ = 0x1f;
    scale_ = dss::Fix32(0x8000);
    counter_ = 0;
    counter1_ = 0;
    angle0_ = 0xffff;
    angle1_ = 0xffff;
    unk_2c = 0xffff;
}

THUMB void window::ScreenEffectBattle::updatePanel(short x, short y, short index, short* sin, short* cos)
{
    const int unused[1] = {2};  // unreferenced, only its .rodata copy remains
    int rnd = UnkDssRand::rand(2);
    int count = rnd ? counter_ : counter1_;
    int angle = rnd ? angle0_ : angle1_;
    int x2 = x * 2;
    if (count > x2) {
        data_020c32a0[index].x -= 2;
        int diff = count - x2;
        data_020c32a0[index].y -= (diff + (0x20 - y)) * 2;
        angle += x2 * 0x78;
        *sin = FX_SinIdx(angle);
        *cos = FX_CosIdx(angle);
    }
}

THUMB void window::ScreenEffectBattle::draw()
{
    if (isActive() == false) {
        return;
    }
    dss::g_DISPLAYPLUGIN_DOUBLE3D.SetBlur(4, 12);
    UnkScreenEffectCamera::getSingleton()->draw();
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
    }
    func_02082604();
    short k = 0;
    for (short i = 0; i < 0x20; i++) {
        for (short j = 0; j < 0x18; j++) {
            short index = j + i * 0x18;
            short sc[2];
            G3_PushMtx();
            G3_Scale(0x8000, 0x8000, 0x8000);
            G3_Translate(data_020c32a0[index].x, data_020c32a0[index].y, data_020c32a0[index].z);
            sc[1] = FX_SinIdx(0);
            sc[0] = FX_CosIdx(0);
            updatePanel(j, i, index, &sc[1], &sc[0]);
            func_020761a0(sc[1], sc[0]);
            setPolygonParams(0x18);
            G3_Begin(1);
            for (int n = 0; n < 4; n++) {
                G3_Color(0x7fff);
                G3_TexCoord(data_020c32a0[index].texCoord[n][0], data_020c32a0[index].texCoord[n][1]);
                G3_Vtx(data_020c32a0[index].vertex[n][0], data_020c32a0[index].vertex[n][1], data_020c32a0[index].vertex[n][2]);
            }
            G3_PopMtx(1);
        }
        if (k > 2) {
            k = 0;
        } else {
            k++;
        }
    }
    counter_ += 2;
    if (counter_ > 0x14) {
        counter1_ += 2;
        if (angle1_ > 0xc000) {
            angle1_ -= 0xf0;
        } else {
            angle1_ = 0xc000;
        }
    }
    if (angle0_ > 0xc000) {
        angle0_ -= 0xf0;
    } else {
        angle0_ = 0xc000;
    }
    if (unk_2c < 0) {
        unk_2c += 0xffff;
    }
}

THUMB bool window::ScreenEffectBattle::isEnd()
{
    return counter_ > 0x4b;
}
