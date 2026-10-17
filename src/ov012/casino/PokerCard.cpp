#pragma ipa file
#include "ov012/casino/PokerCard.hpp"
#include "main/dss/DssVectorDefault.hpp"

THUMB casino::PokerCard::PokerCard()
{
    setup();
}

THUMB casino::PokerCard::~PokerCard()
{
}

THUMB void casino::PokerCard::setup()
{
    m_ctrl.clear();
    m_ctrl.set(1);
}

THUMB void casino::PokerCard::unkfunc_021282f0(dss::Fix32 scale)
{
    unk_000.setScale(scale);
    unk_088.setScale(scale);
    unk_110.setScale(scale);
    unk_198.setScale(scale);
}

THUMB void casino::PokerCard::unkfunc_02128350(const UnkPolygonVertex* vertex)
{
    unk_000.unkfunc_0204709c(vertex);
    unk_088.unkfunc_0204709c(vertex);
    unk_110.unkfunc_0204709c(vertex);
    unk_198.unkfunc_0204709c(vertex);
}

THUMB void casino::PokerCard::setPosition(dss::Fix32Vector3& pos)
{
    unk_000.setPosition(pos);
    unk_088.setPosition(pos);
    unk_198.setPosition(pos);
    pos.vz.value += 0x100;
    unk_110.setPosition(pos);
}

THUMB dss::Fix32Vector3 casino::PokerCard::getPosition()
{
    return *unk_000.getPosition();
}

THUMB void casino::PokerCard::setAngle(int angle)
{
    unk_000.angle_ = angle;
    unk_088.angle_ = angle + 0x8000;
}

THUMB void casino::PokerCard::unkfunc_02128400(const UnkBillboardTexCoord* texCoord)
{
    unk_000.unkfunc_02047138(texCoord);
}

THUMB void casino::PokerCard::unkfunc_02128408(const UnkBillboardTexCoord* texCoord)
{
    unk_088.unkfunc_02047138(texCoord);
}

THUMB void casino::PokerCard::unkfunc_02128414(const UnkBillboardTexCoord* texCoord)
{
    unk_110.unkfunc_02047138(texCoord);
    unk_110.setAlpha(12);
    unk_230.v[0].vx = texCoord->v[0].vx;
    unk_230.v[0].vy = texCoord->v[0].vy;
    unk_230.v[1].vx = texCoord->v[1].vx;
    unk_230.v[1].vy = texCoord->v[1].vy;
    unk_230.v[2].vx = texCoord->v[2].vx;
    unk_230.v[2].vy = texCoord->v[2].vy;
    unk_230.v[3].vx = texCoord->v[3].vx;
    unk_230.v[3].vy = texCoord->v[3].vy;
}

THUMB void casino::PokerCard::unkfunc_021284a0(const UnkBillboardTexCoord* texCoord)
{
    unk_198.unkfunc_02047138(texCoord);
}

THUMB void casino::PokerCard::unkfunc_021284b0(void* texture)
{
    unk_000.texture_ = texture;
}

THUMB void casino::PokerCard::unkfunc_021284b4(void* texture)
{
    unk_088.texture_ = texture;
}

THUMB void casino::PokerCard::unkfunc_021284bc(void* texture)
{
    unk_110.texture_ = texture;
}

THUMB void casino::PokerCard::unkfunc_021284c4(void* texture)
{
    unk_198.texture_ = texture;
    unk_198.setAlpha(1);
}

THUMB void casino::PokerCard::draw()
{
    if (!m_ctrl.check(1)) {
        return;
    }
    unk_000.draw();
    unk_088.draw();
    unk_198.draw();
    if (m_effect_enable) {
        UnkBillboardTexCoord texCoord;
        texCoord.v[0] = unk_230.v[0];
        texCoord.v[1] = unk_230.v[1];
        texCoord.v[2] = unk_230.v[2];
        texCoord.v[3] = unk_230.v[3];
        texCoord.v[0].vy.value = unk_230.v[0].vy.value + unk_228 * m_effect_frame;
        texCoord.v[1].vy.value = unk_230.v[1].vy.value + unk_228 * m_effect_frame;
        texCoord.v[2].vy.value = unk_230.v[2].vy.value + unk_228 * m_effect_frame;
        texCoord.v[3].vy.value = unk_230.v[3].vy.value + unk_228 * m_effect_frame;
        unk_110.unkfunc_02047138(&texCoord);
        unk_110.draw();
        m_effect_frame++;
    }
    if (m_effect_frame == MAX_FRAME) {
        m_effect_enable = 0;
    }
}

THUMB void casino::PokerCard::setEffect()
{
    m_effect_enable = 1;
    dss::Fix32Vector3 pos;
    m_effect_frame = 0;
    pos = *unk_088.getPosition();
    pos.vy.value += 0x100;
    unk_110.setPosition(pos);
    unk_198.setPosition(pos);
    unk_228 = 0x3333;
}

THUMB void casino::PokerCard::unkfunc_02128688(bool enable)
{
    if (enable) {
        m_ctrl.set(1);
    } else {
        m_ctrl.remove(1);
    }
}

THUMB void casino::PokerCard::setAlpha(unsigned char alpha)
{
    unk_000.setAlpha(alpha);
    unk_088.setAlpha(alpha);
}
