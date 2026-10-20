#pragma ipa file
#include "main/window/ScreenEffectManager.hpp"
#include "main/cmn/CommonParticleEmitter.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/UnkMenuOverlay.hpp"
#include "main/object/DSSAObject.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov005/fld/FieldStage.hpp"
#include "ov020/ov020_entry.hpp"
#include "nitro/g3.hpp"
#include "nitro/fx/fx_trig.h"

inline bool window::UnkScreenEffect::isActive()
{
    return (flag_ & FLAG_ACTIVE) ? true : false;
}

inline bool window::UnkScreenEffect::isSetup()
{
    return (flag_ & FLAG_SETUP) ? true : false;
}

inline bool window::UnkScreenEffect::isReady()
{
    return (flag_ & FLAG_READY) ? true : false;
}

inline void fld::FieldData::pause(int flag)
{
    pause_ = flag;
}

inline void cmn::CommonParticleEmitter::pause(bool flag)
{
    stop_ = flag;
}

inline void fld::FieldStage::pause(int flag)
{
    fieldData.pause(flag);
    cmn::CommonParticleEmitter::getSingleton()->pause(flag);
}

static dss::Rectangle<dss::Vector3<dss::Fix16> > s_vertex;
static dss::Rectangle<dss::Vector2<dss::Fix32> > s_texCoord;
static dss::Vector3<dss::Fix16> s_leftBottom(-0.5f, -0.375f, -0.0f);
static dss::Vector3<dss::Fix16> s_rightBottom(0.5f, -0.375f, -0.0f);
static dss::Vector3<dss::Fix16> s_rightTop(0.5f, 0.375f, -0.0f);
static dss::Vector3<dss::Fix16> s_leftTop(-0.5f, 0.375f, -0.0f);
static dss::Vector2<dss::Fix32> s_texLeftTop(0L, 0L);
static dss::Vector2<dss::Fix32> s_texRightTop(0x100L, 0L);
static dss::Vector2<dss::Fix32> s_texRightBottom(0x100L, 0xc0L);
static dss::Vector2<dss::Fix32> s_texLeftBottom(0L, 0xc0L);
window::UnkScreenEffectPanel* data_020c32a0;
short unusedScreenEffectX;      // not linked: unreferenced, only takes part in the data layout
short unusedScreenEffectY;      // not linked: unreferenced, only takes part in the data layout

THUMB window::UnkScreenEffect::UnkScreenEffect()
{
    flag_ = 0;
    scale_.value = 0x8000;
    tilesX_ = 32;
    tilesY_ = 24;
    alpha_ = 30;
    setupWait_ = 0;
    frameCount_ = 0;
    data_020c32a0 = NULL;
}

THUMB window::UnkScreenEffect::~UnkScreenEffect()
{
}

THUMB void window::UnkScreenEffect::setup()
{
    UnkScreenEffectCamera::getSingleton()->initialize();
    dss::g_DISPLAYPLUGIN_DOUBLE3D.SetBlur(16, 0);
    flag_ = 0;
    s_vertex.v[0] = s_leftBottom;
    s_vertex.v[1] = s_rightBottom;
    s_vertex.v[2] = s_rightTop;
    s_vertex.v[3] = s_leftTop;
    s_texCoord.v[0] = s_texLeftBottom;
    s_texCoord.v[1] = s_texRightBottom;
    s_texCoord.v[2] = s_texRightTop;
    s_texCoord.v[3] = s_texLeftTop;
    frameCount_ = 0;
}

THUMB bool window::UnkScreenEffect::setupTiles()
{
    if (setupWait_ < 3) {
        setupWait_++;
        return false;
    }
    if (data_020c32a0 == NULL) {
        loadWindowOverlay(3);
        data_020c32a0 = (UnkScreenEffectPanel*)ov020_entry();
    }
    setupWait_ = 0;
    requestScreenCapture();
    for (int i = 0; i < tilesX_; i++) {
        for (int j = 0; j < tilesY_; j++) {
            int index = j + i * tilesY_;
            for (int k = 0; k < 4; k++) {
                data_020c32a0[index].vertex[k][0] = s_vertex.v[k].vx.value / tilesX_ + 1;
                data_020c32a0[index].vertex[k][1] = s_vertex.v[k].vy.value / tilesY_ + 1;
                data_020c32a0[index].vertex[k][2] = s_vertex.v[k].vz.value;
            }
            data_020c32a0[index].texCoord[3][0] = (i * 256 << 12) / tilesX_;
            data_020c32a0[index].texCoord[3][1] = (j * 192 << 12) / tilesY_;
            data_020c32a0[index].texCoord[2][0] = ((i + 1) * 256 << 12) / tilesX_ + 0x1000;
            data_020c32a0[index].texCoord[2][1] = (j * 192 << 12) / tilesY_;
            data_020c32a0[index].texCoord[1][0] = ((i + 1) * 256 << 12) / tilesX_ + 0x1000;
            data_020c32a0[index].texCoord[1][1] = ((j * 192 + 192) << 12) / tilesY_ + 0x1000;
            data_020c32a0[index].texCoord[0][0] = (i * 256 << 12) / tilesX_;
            data_020c32a0[index].texCoord[0][1] = ((j * 192 + 192) << 12) / tilesY_ + 0x1000;
            if (data_020c32a0[index].texCoord[2][0] >= 0x100000) {
                data_020c32a0[index].texCoord[2][0] = 0x100000;
                data_020c32a0[index].texCoord[1][0] = 0x100000;
            }
            if (data_020c32a0[index].texCoord[1][1] >= 0xc0000) {
                data_020c32a0[index].texCoord[1][1] = 0xc0000;
                data_020c32a0[index].texCoord[0][1] = 0xc0000;
            }
            data_020c32a0[index].x = i * 0x1000 / tilesX_ - 0x800 + 0x1000 / (tilesX_ * 2);
            data_020c32a0[index].y = 0x600 - j * 0xc00 / tilesY_ - 0xc00 / (tilesY_ * 2);
            data_020c32a0[index].z = 0;
        }
    }
    return true;
}

THUMB void window::UnkScreenEffect::terminate()
{
    data_020c32a0 = NULL;
    UnkScreenEffectCamera::getSingleton()->terminate();
}

THUMB void window::UnkScreenEffect::execute()
{
    if (isSetup() == false && isActive() == false) {
        if (setupTiles()) {
            flag_ |= FLAG_SETUP;
        } else {
            if (data_02101c88.isCurrentPart(4)) {
                twn::TownStageManager::getSingleton()->pause(1);
            } else if (data_02101c88.isCurrentPart(6)) {
                fld::FieldStage::getSingleton()->pause(1);
            }
            return;
        }
    }
    if (isScreenCaptureDone()) {
        if (isReady() == false) {
            if (frameCount_ >= 2) {
                flag_ |= FLAG_READY;
                frameCount_ = 0;
            } else {
                frameCount_++;
            }
        } else if (!(flag_ & FLAG_ACTIVE)) {
            flag_ |= FLAG_ACTIVE;
        }
    }
}

THUMB void window::UnkScreenEffect::setPolygonParams(int polygonId)
{
    if (getDisplayFrame() & 1) {
        G3_TexImageParam(GX_TEXFMT_DIRECT, GX_TEXGEN_TEXCOORD, GX_TEXSIZE_S256, GX_TEXSIZE_T256, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_USE, 0x20000);
    } else {
        G3_TexImageParam(GX_TEXFMT_DIRECT, GX_TEXGEN_TEXCOORD, GX_TEXSIZE_S256, GX_TEXSIZE_T256, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_USE, 0);
    }
    G3_PolygonAttr(0, 0, 0xc0, polygonId, alpha_, 0);
}

THUMB void window::UnkScreenEffect::draw()
{
    if (isActive() == false) {
        return;
    }
    UnkScreenEffectCamera::getSingleton()->draw();
    func_020802dc();
    func_02082604();
    for (int i = 0; i < tilesX_; i++) {
        for (int j = 0; j < tilesY_; j++) {
            G3_PushMtx();
            int index = j + i * tilesY_;
            G3_Scale(scale_.value, scale_.value, scale_.value);
            G3_Translate(data_020c32a0[index].x, data_020c32a0[index].y, data_020c32a0[index].z);
            setPolygonParams(24);
            G3_Begin(1);
            for (int k = 0; k < 4; k++) {
                G3_Color(0x7fff);
                G3_TexCoord(data_020c32a0[index].texCoord[k][0], data_020c32a0[index].texCoord[k][1]);
                G3_Vtx(data_020c32a0[index].vertex[k][0], data_020c32a0[index].vertex[k][1], data_020c32a0[index].vertex[k][2]);
            }
            G3_End();
            G3_PopMtx(1);
        }
    }
    frameCount_++;
}

ARM bool window::UnkScreenEffect::isEnd()
{
    return frameCount_ > 60;
}

#pragma thumb on                // the static initializer is Thumb
#include "main/dss/DssVectorDefault.hpp"
