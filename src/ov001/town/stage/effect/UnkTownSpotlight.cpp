#include "ov001/town/stage/effect/UnkTownSpotlight.hpp"
#include "main/dss/RenderObject.hpp"

#pragma thumb on

twn::UnkTownSpotlightLight::UnkTownSpotlightLight() : enable_(false)
{
    x_ = 0;
    y_ = 0;
}

twn::UnkTownSpotlightLight::~UnkTownSpotlightLight()
{
}

void twn::UnkTownSpotlightLight::unkfunc_0212e6b0(int index, dss::Fix32Vector3* pos)
{
    index_ = index;
    enable_ = true;
    pos_ = pos;
    size_ = 0x40;
    alpha_ = 1;
}

void twn::UnkTownSpotlightLight::unkfunc_0212e6c0()
{
    enable_ = false;
    pos_ = 0;
}

void twn::UnkTownSpotlightLight::unkfunc_0212e6c8()
{
    sprite_[0].unkfunc_02051a50("data/mask/en02.tex", 0);
    sprite_[1].unkfunc_02051a50("data/mask/en01.tex", 0);
    for (int i = 0; i < 2; i++) {
        sprite_[i].unkfunc_02051b88();
        sprite_[i].unkfunc_02051ba0(0x3e);
        sprite_[i].unkfunc_02051bb0(0);
        sprite_[i].unkfunc_02051b14(0, 0);
        sprite_[i].unkfunc_02051b20(0, 0);
        sprite_[i].unkfunc_02051b90(1);
        sprite_[i].unkfunc_02051ba0(0x3c);
    }
}

void twn::UnkTownSpotlightLight::unkfunc_0212e73c()
{
    for (int i = 0; i < 2; i++) {
        sprite_[i].unkfunc_02051ac4();
    }
}

void twn::UnkTownSpotlightLight::unkfunc_0212e758(int screen)
{
    if (enable_ && x_ >= 0 && y_ >= 0) {
        sprite_[screen].unkfunc_02051b14(x_ / 2, y_ * 2 / 3);
        sprite_[screen].unkfunc_02051b20(size_ / 2, size_ * 2 / 3);
        sprite_[screen].unkfunc_02051b90(alpha_);
        sprite_[screen].unkfunc_02051bc8(color_);
        sprite_[screen].unkfunc_02051b68();
    }
}

void twn::UnkTownSpotlightLight::unkfunc_0212e7c0()
{
    if (enable_) {
        unkfunc_02052150(index_, *pos_);
        dss::Vector2<int>* point = unkfunc_02052164(index_);
        x_ = point->vx - size_ / 2;
        y_ = point->vy - size_ * 2 / 3;
    }
}

twn::UnkTownSpotlight::UnkTownSpotlight() : enable_(false)
{
}

twn::UnkTownSpotlight::~UnkTownSpotlight()
{
}

void twn::UnkTownSpotlight::unkfunc_0212e850()
{
    unkfunc_0212e8d4();
    blind_.screens_ = 3;
    blind_.setPolygonID(0x3e);
    blind_.depth_ = 0;
    blind_.setAlpha(0x1e);
    blind_.unkfunc_02047e88(0, 0);
    blind_.unkfunc_02047ec0(0x80, 0x80);
    blind_.setColor(0, 0, 0);
    blind_.setPolygonID(0x3c);
    UnkTownSpotlightLight::unkfunc_0212e6c8();
    setup_ = true;
}

void twn::UnkTownSpotlight::unkfunc_0212e8b4(int index, dss::Fix32Vector3* pos)
{
    light_[index].unkfunc_0212e6b0(index + 8, pos);
}

void twn::UnkTownSpotlight::unkfunc_0212e8c4(int index)
{
    light_[index].unkfunc_0212e6c0();
}

void twn::UnkTownSpotlight::unkfunc_0212e8d4()
{
    if (setup_) {
        UnkTownSpotlightLight::unkfunc_0212e73c();
        setup_ = false;
        unkfunc_0212e95c(false);
        for (int i = 0; i < LIGHT_MAX; i++) {
            unkfunc_0212e8c4(i);
        }
    }
}

void twn::UnkTownSpotlight::unkfunc_0212e900()
{
    if (enable_) {
        for (int i = 0; i < LIGHT_MAX; i++) {
            light_[i].unkfunc_0212e7c0();
        }
    }
}

void twn::UnkTownSpotlight::unkfunc_0212e920()
{
    if (enable_) {
        setupOrtho2DFine();
        for (int screen = 0; screen < 2; screen++) {
            for (int i = 0; i < LIGHT_MAX; i++) {
                light_[i].unkfunc_0212e758(screen);
            }
        }
        blind_.draw();
    }
}

void twn::UnkTownSpotlight::unkfunc_0212e95c(int enable)
{
    data_02101da4 = enable;
    enable_ = enable;
}

void twn::UnkTownSpotlight::setBlindAlpha(unsigned char alpha)
{
    blind_.setAlpha(alpha);
}

void twn::UnkTownSpotlight::unkfunc_0212e974(int r, int g, int b)
{
    blind_.setColor(r, g, b);
}

UnkMenuSprite twn::UnkTownSpotlightLight::sprite_[2];
