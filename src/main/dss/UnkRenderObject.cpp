#pragma ipa file
#define RENDER_OBJECT_TU
#include "main/dss/RenderObjectLiterals.hpp"
#include "main/dss/UnkRenderObject.hpp"
#include "main/dss/UnkPolygonObject.hpp"
#include "main/dss/UnkBillboard.hpp"
#include "main/dss/UnkSprite2D.hpp"
#include "main/dss/UnkShadowPolygon.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/object/DSSAObject.hpp"
#include "nitro/g3.hpp"
#include "nitro/fx/fx_trig.h"

ARM inline void UnkRenderObject::draw()
{
}

ARM inline void Position::setScale(dss::Fix32 scale)
{
    scale_.vx = scale;
    scale_.vy = scale;
    scale_.vz = scale;
}

ARM inline void Position::setRotationIdx(const dss::Vector3<unsigned short>& rotation)
{
    unk_28 = rotation;
}

ARM inline void Position::setRotation(const dss::Fix32Vector3& rotation)
{
    rotation_ = rotation;
}

ARM inline void Position::setScale(const dss::Fix32Vector3& scale)
{
    scale_ = scale;
}

ARM inline void Position::setPosition(const dss::Fix32Vector3& position)
{
    position_ = position;
}


#pragma explicit_zero_data on
int renderLiteral_B1x = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B2z = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B9x = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B1y = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B9y = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B4x = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B8y = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B1z = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B4y = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B2x = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B5x = 0;
#pragma explicit_zero_data off
int data_020f3e94;
#pragma explicit_zero_data on
int renderLiteral_B5y = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B7z = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B3z = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B2y = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B4z = 0;
#pragma explicit_zero_data off
int data_020f3e8c;
#pragma explicit_zero_data on
int renderLiteral_B3x = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B8x = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B7y = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B9z = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B5z = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B8z = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B3y = 0;
#pragma explicit_zero_data off
int data_020f3e90;
#pragma explicit_zero_data on
int renderLiteral_B6x = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B6y = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B6z = 0;
#pragma explicit_zero_data off
#pragma explicit_zero_data on
int renderLiteral_B7x = 0;
#pragma explicit_zero_data off
dss::Vector3<int> data_020f3e98(renderLiteral_B1x, renderLiteral_B1y, renderLiteral_B1z);
extern const VecFx32 renderTemplate7 = { 0, FX32_ONE, 0 };
dss::Vector3<int> data_020f3eb0(renderLiteral_B2x, renderLiteral_B2y, renderLiteral_B2z);
dss::Vector3<int> data_020f3ebc(renderLiteral_B3x, renderLiteral_B3y, renderLiteral_B3z);
dss::Vector3<int> data_020f3ed4(renderLiteral_B4x, renderLiteral_B4y, renderLiteral_B4z);
dss::Vector3<int> data_020f3ee0(renderLiteral_B5x, renderLiteral_B5y, renderLiteral_B5z);
dss::Vector3<int> data_020f3eec(renderLiteral_B6x, renderLiteral_B6y, renderLiteral_B6z);
dss::Vector3<int> data_020f3ef8(renderLiteral_B7x, renderLiteral_B7y, renderLiteral_B7z);
extern const VecFx32 renderTemplate3 = { 0, FX32_ONE, 0 };
extern const VecFx32 renderTemplate4 = { 0, 0, 10 << FX32_SHIFT };
extern const VecFx32 renderTemplate5 = { 0, FX32_ONE, 0 };
extern const VecFx32 renderTemplate6 = { 0, 0, 10 << FX32_SHIFT };
extern const VecFx32 renderTemplate1 = { 10 << FX32_SHIFT, FX32_ONE, FX32_ONE };
extern const VecFx32 renderTemplate0 = { 10 << FX32_SHIFT, FX32_ONE, 10 << FX32_SHIFT };
dss::Vector3<int> data_020f3ea4(renderLiteral_B8x, renderLiteral_B8y, renderLiteral_B8z);
dss::Vector3<int> data_020f3ec8(renderLiteral_B9x, renderLiteral_B9y, renderLiteral_B9z);
extern const VecFx32 renderTemplate2 = { 0, 0, 10 << FX32_SHIFT };
unsigned int data_02099c00[15] = { 0x171012, 1, 2, FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0 };
unsigned int data_02099c3c[15] = { 0x171012, 1, 2, FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0 };

ARM Position::Position()
{
    scale_.vx.value = FX32_ONE;
    scale_.vy.value = FX32_ONE;
    scale_.vz.value = FX32_ONE;
}

ARM Position::~Position()
{
}

ARM dss::Fix32Vector3* Position::getPosition()
{
    return &position_;
}

ARM dss::Fix32Vector3* Position::getScale()
{
    return &scale_;
}

ARM UnkRenderObject::UnkRenderObject()
{
    polygonID_ = 0;
    alpha_ = 31;
    enable_ = 1;
}

ARM void UnkRenderObject::unkfunc_02046fe8()
{
    G3_PolygonAttr(0, 0, 0x80, polygonID_, alpha_, 0x8000);
}

ARM void UnkRenderObject::unkfunc_02047010()
{
    G3_PolygonAttr(1, 3, 0x40, 0, 12, 0);
}

ARM void UnkRenderObject::unkfunc_02047028()
{
    G3_PolygonAttr(1, 3, 0x80, 1, 12, 0);
}

ARM void UnkRenderObject::setPolygonID(int id)
{
    polygonID_ = id;
}

ARM void UnkRenderObject::setAlpha(int alpha)
{
    alpha_ = alpha;
}

ARM void UnkRenderObject::setRender(Render* render)
{
    render_ = render;
    render->unkfunc_02048b24(this);
}

ARM void UnkRenderObject::removeRender()
{
    if (render_ != NULL) {
        render_->unkfunc_02048b4c(this);
        render_ = NULL;
    }
}

ARM Render* UnkRenderObject::getRender()
{
    return render_;
}

ARM void UnkPolygonObject::unkfunc_0204709c(const UnkPolygonVertex* vertex)
{
    vertex_ = *vertex;
}

ARM void UnkPolygonObject::unkfunc_02047138(const UnkBillboardTexCoord* texCoord)
{
    texCoord_ = *texCoord;
}

ARM void UnkPolygonObject::draw()
{
    unkfunc_020471b0();
}

ARM void UnkPolygonObject::unkfunc_020471b0()
{
    if (!enable_ || alpha_ == 0) {
        return;
    }
    func_020802dc();
    func_02082604();
    G3_PushMtx();
    G3_Translate(position_.vx.value, position_.vy.value, position_.vz.value);
    func_020761a0(FX_SinIdx(unk_28.vy), FX_CosIdx(unk_28.vy));
    G3_Scale(scale_.vx.value, scale_.vy.value, scale_.vz.value);
    G3_MaterialColorDiffAmb(0x7fff, 0x4210, 1);
    G3_MaterialColorSpecEmi(0x4210, 0, 0);
    if (texture_) {
        ((UnkTextureObject*)texture_)->unkfunc_0204a1e4();
        ((UnkTextureObject*)texture_)->unkfunc_0204a264();
    } else {
        unkfunc_0204a250();
    }
    unkfunc_02046fe8();
    G3_Begin(1);
    for (int i = 0; i < 4; i++) {
        G3_Color(0x7fff);
        G3_TexCoord(texCoord_.v[i].vx.value, texCoord_.v[i].vy.value);
        G3_Vtx(vertex_.v[i].vx.value, vertex_.v[i].vy.value, vertex_.v[i].vz.value);
    }
    G3_End();
    G3_PopMtx(1);
}

ARM void UnkShadowPolygon::draw()
{
    if (!enable_) {
        return;
    }
    func_020802dc();
    func_02082604();
    G3_PushMtx();
    G3_Translate(position_.vx.value, position_.vy.value, position_.vz.value);
    func_020761a0(FX_SinIdx(unk_28.vy), FX_CosIdx(unk_28.vy));
    G3_Scale(scale_.vx.value, scale_.vy.value, scale_.vz.value);
    unkfunc_0204a250();
    if (data_020f3e8c == 0) {
        G3_MaterialColorDiffAmb(0, 0, 0);
        G3_MaterialColorSpecEmi(0, 0, 0);
        unkfunc_02047010();
    } else {
        G3_MaterialColorDiffAmb(0, 0, 1);
        G3_MaterialColorSpecEmi(0, 0, 0);
        unkfunc_02047028();
    }
    G3_Begin(1);
    G3_Color(unk_80.vx | (unk_80.vy << 5) | (unk_80.vz << 10));
    for (int i = 0; i < 4; i++) {
        G3_Vtx(vertex_.v[i].vx.value, vertex_.v[i].vy.value, vertex_.v[i].vz.value);
    }
    G3_End();
    G3_PopMtx(1);
}

ARM void UnkShadowPolygon::unkfunc_0204748c()
{
    if (!enable_) {
        return;
    }
    func_020802dc();
    func_02082604();
    G3_PushMtx();
    G3_Translate(position_.vx.value, position_.vy.value, position_.vz.value);
    func_020761a0(FX_SinIdx(unk_28.vy), FX_CosIdx(unk_28.vy));
    G3_Scale(scale_.vx.value, scale_.vy.value, scale_.vz.value);
    unkfunc_0204a250();
    G3_MaterialColorDiffAmb(0, 0, 0);
    G3_MaterialColorSpecEmi(0, 0, 0);
    unkfunc_02047010();
    G3_Begin(1);
    G3_Color(unk_80.vx | (unk_80.vy << 5) | (unk_80.vz << 10));
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 4; i++) {
            G3_Vtx(unk_84[j].v[i].vx.value, unk_84[j].v[i].vy.value, unk_84[j].v[i].vz.value);
        }
    }
    G3_End();
    G3_MaterialColorDiffAmb(0, 0, 1);
    G3_MaterialColorSpecEmi(0, 0, 0);
    unkfunc_02047028();
    G3_Begin(1);
    G3_Color(unk_80.vx | (unk_80.vy << 5) | (unk_80.vz << 10));
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 4; i++) {
            G3_Vtx(unk_84[j].v[i].vx.value, unk_84[j].v[i].vy.value, unk_84[j].v[i].vz.value);
        }
    }
    G3_End();
    G3_PopMtx(1);
}

ARM void UnkShadowPolygon::unkfunc_02047670(int index, const UnkPolygonVertex* vertex)
{
    unk_84[index] = *vertex;
}

ARM UnkBillboard::UnkBillboard()
{
    setScale(dss::Fix32(1L));
    color_ = 0x7fff;
}

ARM void UnkBillboard::unkfunc_02047a20(const UnkBillboardVertex* vertex)
{
    vertex_ = *vertex;
}

ARM UnkBillboardVertex* UnkBillboard::unkfunc_02047a8c()
{
    return &vertex_;
}

ARM void UnkBillboard::unkfunc_02047a94(const UnkBillboardTexCoord* texCoord)
{
    texCoord_ = *texCoord;
}

ARM UnkBillboardTexCoord* UnkBillboard::unkfunc_02047b00()
{
    return &texCoord_;
}

ARM void UnkBillboard::unkfunc_02047b08(const dss::Vector2<dss::Fix32>* offset)
{
    unk_a8 = *offset;
}

ARM void UnkBillboard::unkfunc_02047b2c()
{
    drawVertex_ = vertex_;
    for (int i = 0; i < 4; i++) {
        drawTexCoord_.v[i].vx = texCoord_.v[i].vx + unk_a8.vx;
        drawTexCoord_.v[i].vy = texCoord_.v[i].vy + unk_a8.vy;
    }
}

ARM void UnkBillboard::unkfunc_02047c10(int color)
{
    color_ = color;
}

ARM void UnkBillboard::draw()
{
    if (alpha_ == 0) {
        return;
    }
    G3_PushMtx();
    G3_Translate(position_.vx.value, position_.vy.value, position_.vz.value);
    unkfunc_02047d38();
    G3_Scale(scale_.vx.value, scale_.vx.value, scale_.vx.value);
    if (texture_) {
        ((UnkTextureObject*)texture_)->unkfunc_0204a1e4();
        ((UnkTextureObject*)texture_)->unkfunc_0204a264();
    } else {
        unkfunc_0204a250();
    }
    unkfunc_02046fe8();
    unkfunc_02047b2c();
    G3_Begin(1);
    G3_Color(color_);
    for (int i = 0; i < 4; i++) {
        G3_TexCoord(drawTexCoord_.v[i].vx.value, drawTexCoord_.v[i].vy.value);
        G3_Vtx(drawVertex_.v[i].vx.value, drawVertex_.v[i].vy.value, 0);
    }
    G3_End();
    G3_PopMtx(1);
}

ARM void unkfunc_02047d38()
{
    unsigned int* trans = &data_02099c00[12];
    MtxFx44 clip;
    func_02082604();
    REG_GFX_FIFO = 0x151110;
    REG_GFX_FIFO = 0;
    while (func_02075e58(&clip) != 0) {
    }
    trans[0] = clip.m[3][0];
    trans[1] = clip.m[3][1];
    trans[2] = clip.m[3][2];
    MI_CpuFillFromSrc(data_02099c00, &REG_GFX_FIFO, sizeof(data_02099c00));
}

ARM UnkSprite2D::UnkSprite2D()
{
    unk_1c = 0;
    unk_1e = 0;
    unk_20 = 0;
    unk_22 = 0;
    unk_24 = 0;
    unk_26 = 0;
    unk_28 = 0;
    unk_30 = 0;
    unk_32 = 0;
    unk_34 = 0x7fff;
}

ARM void UnkSprite2D::unkfunc_02047e88(int x, int y)
{
    unk_14.vx.value = x << FX32_SHIFT;
    unk_14.vy.value = y << FX32_SHIFT;
}

ARM void UnkSprite2D::unkfunc_02047e9c(dss::Fix32 x, dss::Fix32 y)
{
    unk_14.vx = x;
    unk_14.vy = y;
}

ARM void UnkSprite2D::unkfunc_02047ec0(int w, int h)
{
    unk_1c = w;
    unk_1e = h;
}

ARM void UnkSprite2D::unkfunc_02047ecc(int u0, int v0, int u1, int v1)
{
    unk_20 = u0;
    unk_22 = v0;
    unk_24 = u1;
    unk_26 = v1;
}

ARM void UnkSprite2D::draw()
{
    if (!enable_ || !alpha_) {
        return;
    }
    if (unkfunc_0204ccd0() & 1) {
        if (!(unk_2c & 1)) {
            return;
        }
    } else if (!(unk_2c & 2)) {
        return;
    }
    G3_PushMtx();
    if (texture_) {
        if (unk_32 == 0) {
            ((UnkTextureObject*)texture_)->unkfunc_0204a1e4();
            ((UnkTextureObject*)texture_)->unkfunc_0204a264();
        } else {
            ((UnkTextureObject*)texture_)->unkfunc_0204a21c();
            ((UnkTextureObject*)texture_)->unkfunc_0204a264();
        }
    } else {
        unkfunc_0204a250();
    }
    G3_PolygonAttr(0, 0, 0xc0, polygonID_, alpha_, 0x8000);
    G3_Identity();
    G3_Color(unk_34);
    G3_Translate(unk_14.vx.value, unk_14.vy.value, (unk_28 - 0x400) << FX32_SHIFT);
    G3_Translate(unk_1c * FX32_ONE / 2, unk_1e * FX32_ONE / 2, 0);
    func_020761dc(FX_SinIdx(unk_30), FX_CosIdx(unk_30));
    G3_Translate(unk_1c * -FX32_ONE / 2, unk_1e * -FX32_ONE / 2, 0);
    G3_Scale(unk_1c << FX32_SHIFT, unk_1e << FX32_SHIFT, FX32_ONE);
    fx32 u0 = unk_20 << FX32_SHIFT;
    fx32 u1 = unk_24 << FX32_SHIFT;
    fx32 v0 = unk_22 << FX32_SHIFT;
    fx32 v1 = unk_26 << FX32_SHIFT;
    G3_Begin(1);
    G3_TexCoord(u0, v1);
    G3_Vtx(0, FX32_ONE, 0);
    G3_TexCoord(u1, v1);
    G3_Vtx(FX32_ONE, FX32_ONE, 0);
    G3_TexCoord(u1, v0);
    G3_Vtx(FX32_ONE, 0, 0);
    G3_TexCoord(u0, v0);
    G3_Vtx(0, 0, 0);
    G3_End();
    G3_PopMtx(1);
}

// Never called
ARM void unkfunc_unused_29()
{
    VecFx32 camPos = renderTemplate0;
    VecFx32 camUp = renderTemplate1;
    VecFx32 target = { 0, 0, 0 };
    func_02076118(&camPos, &camUp, &target, 1, NULL);
    MI_CpuFillFromSrc(data_02099c3c, &REG_GFX_FIFO, sizeof(data_02099c3c));
}

ARM void unkfunc_0204813c()
{
    func_02082604();
    G3_Viewport(0, 0, 255, 191);
    func_020760b4(0, 192 << FX32_SHIFT, 0, 256 << FX32_SHIFT, -1024 << FX32_SHIFT, 1024 << FX32_SHIFT, FX32_ONE, 1, NULL);
    G3_StoreMtx(0);
    G3_MtxMode(1);
    VecFx32 camPos = renderTemplate2;
    VecFx32 camUp = renderTemplate3;
    VecFx32 target = { 0, 0, 0 };
    func_02076118(&camPos, &camUp, &target, 1, NULL);
}

ARM void unkfunc_020481fc()
{
    G3_Viewport(0, 0, 255, 191);
    func_020760b4(0, 192 << FX32_SHIFT, 0, 256 << FX32_SHIFT, -1024 << FX32_SHIFT, 1024 << FX32_SHIFT, 0x40, 1, NULL);
    G3_StoreMtx(0);
    G3_MtxMode(1);
    VecFx32 camPos = renderTemplate4;
    VecFx32 camUp = renderTemplate5;
    VecFx32 target = { 0, 0, 0 };
    func_02076118(&camPos, &camUp, &target, 1, NULL);
}

ARM void unkfunc_020482b8()
{
    G3_Viewport(0, 0, 255, 191);
    func_020760b4(0, 192 << FX32_SHIFT, 0, 256 << FX32_SHIFT, -1024 << FX32_SHIFT, 1024 << FX32_SHIFT, 1024 << FX32_SHIFT, 1, NULL);
    G3_StoreMtx(0);
    G3_MtxMode(1);
    VecFx32 camPos = renderTemplate6;
    VecFx32 camUp = renderTemplate7;
    VecFx32 target = { 0, 0, 0 };
    func_02076118(&camPos, &camUp, &target, 1, NULL);
}

ARM void unkfunc_02048370()
{
    if (data_020f3e94 == 0) {
        return;
    }
    G3_PushMtx();
    G3_PolygonAttr(0, 0, 0xc0, 0, 31, 0);
    G3_Identity();
    G3_Color(data_020f3e98.vx | (data_020f3e98.vy << 5) | (data_020f3e98.vz << 10));
    G3_Translate(0, 0, 1024 << FX32_SHIFT);
    G3_Scale(256 << FX32_SHIFT, 192 << FX32_SHIFT, FX32_ONE);
    if (unkfunc_0204ccd0() & 1) {
        G3_Begin(1);
        G3_Color(data_020f3ed4.vx | (data_020f3ed4.vy << 5) | (data_020f3ed4.vz << 10));
        G3_TexCoord(0, 0);
        G3_Vtx(0, FX32_ONE, 0);
        G3_Color(data_020f3ee0.vx | (data_020f3ee0.vy << 5) | (data_020f3ee0.vz << 10));
        G3_TexCoord(0, 0);
        G3_Vtx(FX32_ONE, FX32_ONE, 0);
        G3_Color(data_020f3ebc.vx | (data_020f3ebc.vy << 5) | (data_020f3ebc.vz << 10));
        G3_TexCoord(0, 0);
        G3_Vtx(FX32_ONE, 0, 0);
        G3_Color(data_020f3eb0.vx | (data_020f3eb0.vy << 5) | (data_020f3eb0.vz << 10));
        G3_TexCoord(0, 0);
        G3_Vtx(0, 0, 0);
        G3_End();
    } else {
        G3_Begin(1);
        G3_Color(data_020f3ea4.vx | (data_020f3ea4.vy << 5) | (data_020f3ea4.vz << 10));
        G3_TexCoord(0, 0);
        G3_Vtx(0, FX32_ONE, 0);
        G3_Color(data_020f3ec8.vx | (data_020f3ec8.vy << 5) | (data_020f3ec8.vz << 10));
        G3_TexCoord(0, 0);
        G3_Vtx(FX32_ONE, FX32_ONE, 0);
        G3_Color(data_020f3ef8.vx | (data_020f3ef8.vy << 5) | (data_020f3ef8.vz << 10));
        G3_TexCoord(0, 0);
        G3_Vtx(FX32_ONE, 0, 0);
        G3_Color(data_020f3eec.vx | (data_020f3eec.vy << 5) | (data_020f3eec.vz << 10));
        G3_TexCoord(0, 0);
        G3_Vtx(0, 0, 0);
        G3_End();
    }
    G3_PopMtx(1);
}

ARM void unkfunc_020485cc(int r, int g, int b)
{
    data_020f3eb0.vx = r;
    data_020f3eb0.vy = g;
    data_020f3eb0.vz = b;
    data_020f3ebc.vx = r;
    data_020f3ebc.vy = g;
    data_020f3ebc.vz = b;
    data_020f3ed4.vx = r;
    data_020f3ed4.vy = g;
    data_020f3ed4.vz = b;
    data_020f3ee0.vx = r;
    data_020f3ee0.vy = g;
    data_020f3ee0.vz = b;
    data_020f3eec.vx = r;
    data_020f3eec.vy = g;
    data_020f3eec.vz = b;
    data_020f3ef8.vx = r;
    data_020f3ef8.vy = g;
    data_020f3ef8.vz = b;
    data_020f3ea4.vx = r;
    data_020f3ea4.vy = g;
    data_020f3ea4.vz = b;
    data_020f3ec8.vx = r;
    data_020f3ec8.vy = g;
    data_020f3ec8.vz = b;
    data_020f3e94 = 1;
}

ARM void unkfunc_02048640(unsigned char* bottomUpLeft, unsigned char* bottomUpRight, unsigned char* bottomDownLeft, unsigned char* bottomDownRight,
                          unsigned char* topUpLeft, unsigned char* topUpRight, unsigned char* topDownLeft, unsigned char* topDownRight)
{
    data_020f3eec.vx = topUpLeft[0];
    data_020f3eec.vy = topUpLeft[1];
    data_020f3eec.vz = topUpLeft[2];
    data_020f3ef8.vx = topUpRight[0];
    data_020f3ef8.vy = topUpRight[1];
    data_020f3ef8.vz = topUpRight[2];
    data_020f3ea4.vx = topDownLeft[0];
    data_020f3ea4.vy = topDownLeft[1];
    data_020f3ea4.vz = topDownLeft[2];
    data_020f3ec8.vx = topDownRight[0];
    data_020f3ec8.vy = topDownRight[1];
    data_020f3ec8.vz = topDownRight[2];
    data_020f3eb0.vx = bottomUpLeft[0];
    data_020f3eb0.vy = bottomUpLeft[1];
    data_020f3eb0.vz = bottomUpLeft[2];
    data_020f3ebc.vx = bottomUpRight[0];
    data_020f3ebc.vy = bottomUpRight[1];
    data_020f3ebc.vz = bottomUpRight[2];
    data_020f3ed4.vx = bottomDownLeft[0];
    data_020f3ed4.vy = bottomDownLeft[1];
    data_020f3ed4.vz = bottomDownLeft[2];
    data_020f3ee0.vx = bottomDownRight[0];
    data_020f3ee0.vy = bottomDownRight[1];
    data_020f3ee0.vz = bottomDownRight[2];
    data_020f3e94 = 1;
}

ARM void unkfunc_02048728(int enable)
{
    data_020f3e94 = enable;
}

ARM void unkfunc_02048738()
{
    if (data_020f3e90 == 0) {
        return;
    }
    if (unkfunc_0204ccd0() & 1) {
        return;
    }
    unkfunc_0204813c();
    G3_PushMtx();
    G3_TexImageParam(GX_TEXFMT_NONE, GX_TEXGEN_TEXCOORD, GX_TEXSIZE_S8, GX_TEXSIZE_T8, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_TRNS, 0);
    G3_PolygonAttr(0, 0, 0xc0, 0, 15, 0);
    G3_Identity();
    G3_Color(0);
    func_0207eca8(0, 0, 0x3ff, 256, 192, 0, 0, 255, 191);
    G3_PopMtx(1);
}

ARM void UnkSprite2D::setColor(int r, int g, int b)
{
    unk_34 = r | (g << 5) | (b << 10);
}

ARM void UnkSprite2D::setColor(int color)
{
    unk_34 = color;
}



#include "main/dss/DssVectorDefault.hpp"
