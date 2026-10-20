#pragma ipa file
#include "ov012/casino/CasinoPokerDraw.hpp"
#include "nitro/g3.hpp"
#include "nitro/fx/fx_trig.h"
#include "main/object/DSSAObject.hpp"

static UnkPolygonVertex s_vertex;
static UnkBillboardTexCoord s_texCoord;
static dss::Vector3<dss::Fix16> s_vertexLeftTop(-0.21f, -0.0f, 0.0f);
static dss::Vector3<dss::Fix16> s_vertexRightTop(0.21f, -0.0f, 0.0f);
static dss::Vector3<dss::Fix16> s_vertexRightBottom(0.21f, -0.0f, -0.64f);
static dss::Vector3<dss::Fix16> s_vertexLeftBottom(-0.21f, -0.0f, -0.64f);
static dss::Vector2<dss::Fix32> s_texCoordLeftTop(0, 0);
static dss::Vector2<dss::Fix32> s_texCoordRightTop(42, 0);
static dss::Vector2<dss::Fix32> s_texCoordRightBottom(42, 64);
static dss::Vector2<dss::Fix32> s_texCoordLeftBottom(0, 64);

THUMB casino::CasinoPokerDraw::CasinoPokerDraw()
{
}

THUMB casino::CasinoPokerDraw::~CasinoPokerDraw()
{
}

THUMB casino::CasinoPokerDraw* casino::CasinoPokerDraw::getSingleton()
{
    static CasinoPokerDraw m_singleton;
    return &m_singleton;
}

THUMB void casino::CasinoPokerDraw::initialize()
{
    cardObject[0].setup("data/minigame/poker/slime1.tex", 0, 0);
    cardObject[1].setup("data/minigame/poker/crown1.tex", 0, 0);
    cardObject[2].setup("data/minigame/poker/tate1.tex", 0, 0);
    cardObject[3].setup("data/minigame/poker/ken1.tex", 0, 0);
    cardObject[4].setup("data/minigame/poker/joker_omote.tex", 0, 0);
    cardObject[5].setup("data/minigame/poker/hikari.tex", 0, 0);
    for (int i = 0; i < MAX_CARD_TYPE; i++) {
        cardTexture_[i] = (TextureObject*)cardObject[i].getAddr();
        cardTexture_[i]->loadToVram(1);
    }
    s_vertex.v[0] = s_vertexLeftTop;
    s_vertex.v[1] = s_vertexRightTop;
    s_vertex.v[2] = s_vertexRightBottom;
    s_vertex.v[3] = s_vertexLeftBottom;
    s_texCoord.v[0] = s_texCoordLeftBottom;
    s_texCoord.v[1] = s_texCoordRightBottom;
    s_texCoord.v[2] = s_texCoordRightTop;
    s_texCoord.v[3] = s_texCoordLeftTop;
    cardDistance_.value = 0x3744;
    cardSpace_.value = 0xe64;
    cardScale_.value = 0x4000;
    cardDepth_.value = -0x2640;
    setPoolPosition();
    setBackCardTexture();
    setEffectCardTexture();
    for (int i = 0; i < MAX_CARD_INSTANCE; i++) {
        card[i].setAngle(0x8000);
    }
    alpha_ = 0x1f;
}

THUMB void casino::CasinoPokerDraw::setPoolPosition()
{
    for (int i = 0; i < MAX_CARD_INSTANCE; i++) {
        dss::Fix32Vector3 pos;
        pos.vy = cardDistance_;
        pos.vx.value = cardSpace_.value * (i * 2 - 4);
        pos.vz.value = cardDepth_.value;
        defaultPos[i] = pos;
        card[i].setScale(cardScale_.value);
        card[i].setVertex(&s_vertex);
        card[i].setPosition(pos);
        setDisplay(i, true);
        setCardReverse(i);
    }
}

THUMB void casino::CasinoPokerDraw::setHighLowPosition()
{
    for (int i = 0; i < MAX_CARD_INSTANCE; i++) {
        setDisplay(i, false);
    }
    for (int i = 0; i < 2; i++) {
        dss::Fix32Vector3 pos;
        pos.vy = cardDistance_;
        if (i == 0) {
            pos.vx.value = cardSpace_.value + cardSpace_.value / 2;
        } else {
            pos.vx.value = -cardSpace_.value / 2 - cardSpace_.value;
        }
        pos.vz.value = cardDepth_.value;
        defaultPos[i] = pos;
        card[i].setScale(cardScale_.value);
        card[i].setVertex(&s_vertex);
        card[i].setPosition(pos);
        setDisplay(i, true);
        setCardReverse(i);
    }
}

THUMB void casino::CasinoPokerDraw::terminate()
{
    for (int i = 0; i < MAX_CARD_TYPE; i++) {
        cardTexture_[i]->freeVram();
        cardObject[i].cleanup();
    }
}

THUMB void casino::CasinoPokerDraw::draw()
{
    for (int i = 0; i < MAX_CARD_INSTANCE; i++) {
        card[i].draw();
    }
}

THUMB void casino::CasinoPokerDraw::setCardReverse(int cardIndex)
{
    setCardTexture(cardIndex, 4, 1);
}

THUMB void casino::CasinoPokerDraw::setCardTexture(int cardIndex, int type, int number)
{
    int x = number % 6;
    int y = number / 6;
    dss::Vector2<dss::Fix32> leftTop(x * 42, y * 64);
    dss::Vector2<dss::Fix32> rightTop((x + 1) * 42, y * 64);
    dss::Vector2<dss::Fix32> rightBottom((x + 1) * 42, (y + 1) * 64);
    dss::Vector2<dss::Fix32> leftBottom(x * 42, (y + 1) * 64);
    card[cardIndex].setFrontTexture(cardObject[type].getAddr());
    s_texCoord.v[0] = leftBottom;
    s_texCoord.v[1] = rightBottom;
    s_texCoord.v[2] = rightTop;
    s_texCoord.v[3] = leftTop;
    card[cardIndex].setFrontTexCoord(&s_texCoord);
}

THUMB void casino::CasinoPokerDraw::setBackCardTexture()
{
    for (int i = 0; i < MAX_CARD_INSTANCE; i++) {
        dss::Vector2<dss::Fix32> leftTop(42, 0);
        dss::Vector2<dss::Fix32> rightTop(84, 0);
        dss::Vector2<dss::Fix32> rightBottom(84, 64);
        dss::Vector2<dss::Fix32> leftBottom(42, 64);
        card[i].setBackTexture(cardObject[4].getAddr());
        s_texCoord.v[0] = leftBottom;
        s_texCoord.v[1] = rightBottom;
        s_texCoord.v[2] = rightTop;
        s_texCoord.v[3] = leftTop;
        card[i].setBackTexCoord(&s_texCoord);
    }
}

THUMB void casino::CasinoPokerDraw::setEffectCardTexture()
{
    for (int i = 0; i < MAX_CARD_INSTANCE; i++) {
        dss::Vector2<dss::Fix32> leftTop(0, 0);
        dss::Vector2<dss::Fix32> rightTop(42, 0);
        dss::Vector2<dss::Fix32> rightBottom(42, 64);
        dss::Vector2<dss::Fix32> leftBottom(0, 64);
        card[i].setShineTexture(cardObject[5].getAddr());
        s_texCoord.v[0] = leftBottom;
        s_texCoord.v[1] = rightBottom;
        s_texCoord.v[2] = rightTop;
        s_texCoord.v[3] = leftTop;
        card[i].setShineTexCoord(&s_texCoord);
    }
    for (int i = 0; i < MAX_CARD_INSTANCE; i++) {
        dss::Vector2<dss::Fix32> leftTop(42, 0);
        dss::Vector2<dss::Fix32> rightTop(84, 0);
        dss::Vector2<dss::Fix32> rightBottom(84, 64);
        dss::Vector2<dss::Fix32> leftBottom(42, 64);
        card[i].setGlowTexture(cardObject[5].getAddr());
        s_texCoord.v[0] = leftBottom;
        s_texCoord.v[1] = rightBottom;
        s_texCoord.v[2] = rightTop;
        s_texCoord.v[3] = leftTop;
        card[i].setGlowTexCoord(&s_texCoord);
    }
}

THUMB void casino::CasinoPokerDraw::setCardPosition(int cardIndex, dss::Fix32Vector3 pos)
{
    card[cardIndex].setPosition(pos);
}

THUMB dss::Fix32 casino::CasinoPokerDraw::getDistance()
{
    return cardDistance_;
}

THUMB dss::Fix32 casino::CasinoPokerDraw::getSpace()
{
    return cardSpace_;
}

THUMB void casino::CasinoPokerDraw::setCardAngle(int cardIndex, unsigned short angle)
{
    card[cardIndex].setAngle(angle);
}

THUMB void casino::CasinoPokerDraw::setEffect(int cardIndex)
{
    card[cardIndex].setEffect();
}

THUMB void casino::CasinoPokerDraw::setDisplay(int cardIndex, bool flag)
{
    card[cardIndex].setVisible(flag);
}

THUMB void casino::CasinoPokerDraw::setAlpha(int cardIndex, unsigned char alpha)
{
    card[cardIndex].setAlpha(alpha);
    if (cardIndex == 0) {
        alpha_ = alpha;
    }
}

THUMB unsigned char casino::CasinoPokerDraw::getAlpha()
{
    return alpha_;
}

THUMB casino::PokerCardPolygon::PokerCardPolygon()
{
    angle_ = 0;
}

THUMB casino::PokerCardPolygon::~PokerCardPolygon()
{
}

THUMB void casino::PokerCardPolygon::draw()
{
    if (alpha_ == 0 || !enable_) {
        return;
    }
    func_020802dc();
    func_02082604();
    G3_PushMtx();
    G3_Translate(position_.vx.value, position_.vy.value, position_.vz.value);
    func_020761dc(FX_SinIdx(angle_), FX_CosIdx(angle_));
    G3_Scale(scale_.vx.value, scale_.vy.value, scale_.vz.value);
    G3_MaterialColorDiffAmb(0x7fff, 0x4210, 1);
    G3_MaterialColorSpecEmi(0x4210, 0, 0);
    if (texture_) {
        ((TextureObject*)texture_)->applyTexImageParam();
        ((TextureObject*)texture_)->applyPlttBase();
    } else {
        disableTexture();
    }
    applyPolygonAttr();
    G3_Begin(1);
    for (int i = 0; i < 4; i++) {
        G3_Color(0x7fff);
        G3_TexCoord(texCoord_.v[i].vx.value, texCoord_.v[i].vy.value);
        G3_Vtx(vertex_.v[i].vx.value, vertex_.v[i].vy.value, vertex_.v[i].vz.value);
    }
    G3_End();
    G3_PopMtx(1);
}

// The original TU also emitted UnkRenderObject3D's weak vtable (merged with main's by the linker).
// Our headers keep it external, so this dead-stripped stand-in recreates that 0x3C vtable for the data layout.
struct CasinoPokerDrawWeakVtable : RenderObject, Position {
};

void CasinoPokerDraw_weakVtable()
{
    CasinoPokerDrawWeakVtable unused;
}

#include "main/dss/DssVectorDefault.hpp"
