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

THUMB void casino::PokerCard::setScale(dss::Fix32 scale)
{
    m_front_polygon.setScale(scale);
    m_back_polygon.setScale(scale);
    m_shine_polygon.setScale(scale);
    m_glow_polygon.setScale(scale);
}

THUMB void casino::PokerCard::setVertex(const UnkPolygonVertex* vertex)
{
    m_front_polygon.setVertex(vertex);
    m_back_polygon.setVertex(vertex);
    m_shine_polygon.setVertex(vertex);
    m_glow_polygon.setVertex(vertex);
}

THUMB void casino::PokerCard::setPosition(dss::Fix32Vector3& pos)
{
    m_front_polygon.setPosition(pos);
    m_back_polygon.setPosition(pos);
    m_glow_polygon.setPosition(pos);
    pos.vz.value += 0x100;
    m_shine_polygon.setPosition(pos);
}

THUMB dss::Fix32Vector3 casino::PokerCard::getPosition()
{
    return *m_front_polygon.getPosition();
}

THUMB void casino::PokerCard::setAngle(int angle)
{
    m_front_polygon.angle_ = angle;
    m_back_polygon.angle_ = angle + 0x8000;
}

THUMB void casino::PokerCard::setFrontTexCoord(const UnkBillboardTexCoord* texCoord)
{
    m_front_polygon.setTexCoord(texCoord);
}

THUMB void casino::PokerCard::setBackTexCoord(const UnkBillboardTexCoord* texCoord)
{
    m_back_polygon.setTexCoord(texCoord);
}

THUMB void casino::PokerCard::setShineTexCoord(const UnkBillboardTexCoord* texCoord)
{
    m_shine_polygon.setTexCoord(texCoord);
    m_shine_polygon.setAlpha(12);
    m_shine_tex_coord.v[0].vx = texCoord->v[0].vx;
    m_shine_tex_coord.v[0].vy = texCoord->v[0].vy;
    m_shine_tex_coord.v[1].vx = texCoord->v[1].vx;
    m_shine_tex_coord.v[1].vy = texCoord->v[1].vy;
    m_shine_tex_coord.v[2].vx = texCoord->v[2].vx;
    m_shine_tex_coord.v[2].vy = texCoord->v[2].vy;
    m_shine_tex_coord.v[3].vx = texCoord->v[3].vx;
    m_shine_tex_coord.v[3].vy = texCoord->v[3].vy;
}

THUMB void casino::PokerCard::setGlowTexCoord(const UnkBillboardTexCoord* texCoord)
{
    m_glow_polygon.setTexCoord(texCoord);
}

THUMB void casino::PokerCard::setFrontTexture(void* texture)
{
    m_front_polygon.texture_ = texture;
}

THUMB void casino::PokerCard::setBackTexture(void* texture)
{
    m_back_polygon.texture_ = texture;
}

THUMB void casino::PokerCard::setShineTexture(void* texture)
{
    m_shine_polygon.texture_ = texture;
}

THUMB void casino::PokerCard::setGlowTexture(void* texture)
{
    m_glow_polygon.texture_ = texture;
    m_glow_polygon.setAlpha(1);
}

THUMB void casino::PokerCard::draw()
{
    if (!m_ctrl.check(1)) {
        return;
    }
    m_front_polygon.draw();
    m_back_polygon.draw();
    m_glow_polygon.draw();
    if (m_effect_enable) {
        UnkBillboardTexCoord texCoord;
        texCoord.v[0] = m_shine_tex_coord.v[0];
        texCoord.v[1] = m_shine_tex_coord.v[1];
        texCoord.v[2] = m_shine_tex_coord.v[2];
        texCoord.v[3] = m_shine_tex_coord.v[3];
        texCoord.v[0].vy.value = m_shine_tex_coord.v[0].vy.value + m_shine_scroll_speed * m_effect_frame;
        texCoord.v[1].vy.value = m_shine_tex_coord.v[1].vy.value + m_shine_scroll_speed * m_effect_frame;
        texCoord.v[2].vy.value = m_shine_tex_coord.v[2].vy.value + m_shine_scroll_speed * m_effect_frame;
        texCoord.v[3].vy.value = m_shine_tex_coord.v[3].vy.value + m_shine_scroll_speed * m_effect_frame;
        m_shine_polygon.setTexCoord(&texCoord);
        m_shine_polygon.draw();
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
    pos = *m_back_polygon.getPosition();
    pos.vy.value += 0x100;
    m_shine_polygon.setPosition(pos);
    m_glow_polygon.setPosition(pos);
    m_shine_scroll_speed = 0x3333;
}

THUMB void casino::PokerCard::setVisible(bool enable)
{
    if (enable) {
        m_ctrl.set(1);
    } else {
        m_ctrl.remove(1);
    }
}

THUMB void casino::PokerCard::setAlpha(unsigned char alpha)
{
    m_front_polygon.setAlpha(alpha);
    m_back_polygon.setAlpha(alpha);
}
