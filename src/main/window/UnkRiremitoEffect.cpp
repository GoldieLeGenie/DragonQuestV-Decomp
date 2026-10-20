#pragma ipa file
#include "main/window/ScreenEffectManager.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/object/DSSAObject.hpp"
#include "nitro/g3.hpp"
#include "nitro/fx/fx_trig.h"

inline bool window::UnkScreenEffect::isActive()
{
    return (flag_ & FLAG_ACTIVE) ? true : false;
}

THUMB void window::UnkRiremitoEffect::setup()
{
    unk_0c = 1;
    unk_10 = 1;
    alpha_ = 31;
    unk_08 = dss::Fix32(0x8000);
    unk_20 = 0xffff;
    unk_28 = 0x8000;
    for (int i = 0; i < 8; i++) {
        unk_30[i] = 0;
    }
    angle_ = 0;
    unk_2c = 0x8000;
    counter_ = 0;
    unk_5c = 0;
    UnkScreenEffect::setup();
}

THUMB void window::UnkRiremitoEffect::draw()
{
    drawPanels();
}

THUMB bool window::UnkRiremitoEffect::isEnd()
{
    if (counter_ > 60 || unk_30[0] > 60) {
        return true;
    }
    return false;
}

THUMB void window::UnkRiremitoEffect::drawPanels()
{
    if (isActive() == false) {
        return;
    }
    dss::g_DISPLAYPLUGIN_DOUBLE3D.SetBlur(4, 12);
    alpha_ = 31;
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
        func_02082604();
    }
    unk_2c = counter_ * 10 >> 1;
    counter_++;
    angle_ += 20;
    if (angle_ >= 0x10000) {
        angle_ -= 0x10000;
    }
    int polygonId = 0;
    int i;
    int j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            int distanceX;
            int distance = counter_ * (i * 10 + 10);
            distanceX = distance * 3;
            int dir;
            if (i == 1) {
                dir = j;
            } else {
                dir = 3 - j;
            }
            G3_PushMtx();
            switch (dir) {
            case 0:
                G3_Translate(distanceX + data_020c32a0->x, distance + data_020c32a0->y, data_020c32a0->z);
                break;
            case 1:
                G3_Translate(distanceX + data_020c32a0->x, data_020c32a0->y - distance, data_020c32a0->z);
                break;
            case 2:
                G3_Translate(data_020c32a0->x - distanceX, data_020c32a0->y - distance, data_020c32a0->z);
                break;
            case 3:
                G3_Translate(data_020c32a0->x - distanceX, distance + data_020c32a0->y, data_020c32a0->z);
                break;
            }
            func_020761dc(FX_SinIdx(angle_), FX_CosIdx(angle_));
            G3_Scale(0x8000, 0x8000, 0x8000);
            int alpha = 15 - j * 4 - (counter_ >> 3);
            if (alpha < 0) {
                alpha = 0;
            }
            alpha_ = alpha;
            setPolygonParams(polygonId);
            polygonId++;
            G3_Begin(1);
            int n = 0;
            G3_Color(0x7fff);
            G3_TexCoord(data_020c32a0->texCoord[n][0], data_020c32a0->texCoord[n][1]);
            G3_Vtx(data_020c32a0->vertex[n][0], data_020c32a0->vertex[n][1], data_020c32a0->vertex[n][2]);
            n++;
            G3_Color(0x7fff);
            G3_TexCoord(data_020c32a0->texCoord[n][0], data_020c32a0->texCoord[n][1]);
            G3_Vtx(data_020c32a0->vertex[n][0], data_020c32a0->vertex[n][1], data_020c32a0->vertex[n][2]);
            n++;
            G3_Color(0x7fff);
            G3_TexCoord(data_020c32a0->texCoord[n][0], data_020c32a0->texCoord[n][1]);
            G3_Vtx(data_020c32a0->vertex[n][0], data_020c32a0->vertex[n][1], data_020c32a0->vertex[n][2]);
            n++;
            G3_Color(0x7fff);
            G3_TexCoord(data_020c32a0->texCoord[n][0], data_020c32a0->texCoord[n][1]);
            G3_Vtx(data_020c32a0->vertex[n][0], data_020c32a0->vertex[n][1], data_020c32a0->vertex[n][2]);
            G3_PopMtx(1);
        }
    }
}

