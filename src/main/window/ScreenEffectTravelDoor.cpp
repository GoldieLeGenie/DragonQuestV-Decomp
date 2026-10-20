#include "main/window/ScreenEffectManager.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/global/Global.hpp"
#include "main/object/DSSAObject.hpp"
#include "nitro/g3.hpp"
#include "nitro/fx/fx_trig.h"
#include "nnsys/g3d.hpp"

inline bool window::UnkScreenEffect::isActive()
{
    return (flag_ & FLAG_ACTIVE) ? true : false;
}

THUMB void window::ScreenEffectTravelDoor::setup()
{
    unk_0c = 0x20;
    unk_10 = 0x18;
    alpha_ = 0x1f;
    unk_08 = dss::Fix32(0x8000);
    counter_ = 0;
    angle_ = 0xffff;
    speed_ = 100;
    travelBack_ = 0;
    UnkScreenEffect::setup();
}

THUMB void window::ScreenEffectTravelDoor::draw()
{
    if (isActive() == false) {
        return;
    }
    dss::g_DISPLAYPLUGIN_DOUBLE3D.SetBlur(4, 12);
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
    }
    func_02082604();
    int fade = counter_;
    if (travelBack_) {
        fade = 0x26 - fade;
        if (fade < 0) {
            int blur = 4 - fade;
            int blur2 = fade + 0xc;
            dss::clamp<int>(blur, 0, 16);
            dss::clamp<int>(blur2, 0, 16);
            dss::g_DISPLAYPLUGIN_DOUBLE3D.SetBlur(blur, blur2);
            fade = 0;
        }
    } else if (fade == 0) {
        g_Global.fadeOutBlack(0x32, true);
    }
    for (int i = 0; i < 0x20; i++) {
        for (int j = 0; j < 0x18; j++) {
            G3_PushMtx();
            G3_Scale(0x8000, 0x8000, 0x8000);
            func_020761dc(FX_SinIdx(angle_), FX_CosIdx(angle_));
            int index = j + i * 0x18;
            G3_Translate(data_020c32a0[index].x, data_020c32a0[index].y, data_020c32a0[index].z);
            unkfunc_020287e8(0x18);
            G3_Begin(1);
            for (int n = 0; n < 4; n++) {
                VecFx16 dir;
                VecFx16 pos;
                pos.x = data_020c32a0[index].x + data_020c32a0[index].vertex[n][0];
                pos.y = data_020c32a0[index].y + data_020c32a0[index].vertex[n][1];
                pos.z = data_020c32a0[index].z + data_020c32a0[index].vertex[n][2];
                func_0208a448(&pos, &dir);
                int dx = (dir.x >> 8) * fade;
                short vx = data_020c32a0[index].vertex[n][0] - dx;
                short vy = data_020c32a0[index].vertex[n][1] - (dir.y >> 8) * fade;
                short ox = dss::abs<short>(pos.x) - dss::abs<int>(dx);
                short oy = dss::abs<short>(pos.y) - dss::abs<int>((dir.y >> 8) * fade);
                if (ox < 0) {
                    vx = -pos.x;
                }
                if (oy < 0) {
                    vy = -pos.y;
                }
                G3_Color(0x7fff);
                G3_TexCoord(data_020c32a0[index].texCoord[n][0], data_020c32a0[index].texCoord[n][1]);
                G3_Vtx(vx, vy, data_020c32a0[index].vertex[n][2]);
            }
            G3_PopMtx(1);
        }
    }
    counter_++;
    if (travelBack_ == 0 || angle_ != 0) {
        angle_ += speed_;
        if (angle_ >= 0xffff) {
            angle_ -= 0xffff;
        }
        if (angle_ < 0) {
            angle_ += 0xffff;
        }
    }
}

THUMB bool window::ScreenEffectTravelDoor::isEnd()
{
    if (counter_ > 0x32 && !travelBack_) {
        dss::g_DISPLAYPLUGIN_DOUBLE3D.SetBlur(16, 0);
        return true;
    }
    if (counter_ > 0x32 && travelBack_) {
        travelBack_ = 0;
        dss::g_DISPLAYPLUGIN_DOUBLE3D.SetBlur(16, 0);
        return true;
    }
    return false;
}

THUMB void window::ScreenEffectTravelDoor::unkfunc_02029ba4(int travelBack)
{
    travelBack_ = travelBack;
    if (travelBack) {
        speed_ = 100;
        angle_ = 0xffff - speed_ * 0x26;
    } else {
        speed_ = -100;
        angle_ = 0xffff;
    }
}
