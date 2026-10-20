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

void twn::UnkTownSpotlightLight::deactivate()
{
    enable_ = false;
    pos_ = 0;
}

void twn::UnkTownSpotlightLight::loadSprites()
{
    sprite_[0].loadFile("data/mask/en02.tex", 0);
    sprite_[1].loadFile("data/mask/en01.tex", 0);
    for (int i = 0; i < 2; i++) {
        sprite_[i].setBothScreens();
        sprite_[i].setPolygonID(0x3e);
        sprite_[i].setDepth(0);
        sprite_[i].setPosition(0, 0);
        sprite_[i].setSize(0, 0);
        sprite_[i].setAlpha(1);
        sprite_[i].setPolygonID(0x3c);
    }
}

void twn::UnkTownSpotlightLight::releaseSprites()
{
    for (int i = 0; i < 2; i++) {
        sprite_[i].unload();
    }
}

void twn::UnkTownSpotlightLight::draw(int screen)
{
    if (enable_ && x_ >= 0 && y_ >= 0) {
        sprite_[screen].setPosition(x_ / 2, y_ * 2 / 3);
        sprite_[screen].setSize(size_ / 2, size_ * 2 / 3);
        sprite_[screen].setAlpha(alpha_);
        sprite_[screen].setColor555(color_);
        sprite_[screen].draw();
    }
}

void twn::UnkTownSpotlightLight::update()
{
    if (enable_) {
        setProjectedPointPos(index_, *pos_);
        dss::Vector2<int>* point = getProjectedPointScreenPos(index_);
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

void twn::UnkTownSpotlight::setup()
{
    cleanup();
    blind_.screens_ = 3;
    blind_.setPolygonID(0x3e);
    blind_.depth_ = 0;
    blind_.setAlpha(0x1e);
    blind_.unkfunc_02047e88(0, 0);
    blind_.setSize(0x80, 0x80);
    blind_.setColor(0, 0, 0);
    blind_.setPolygonID(0x3c);
    UnkTownSpotlightLight::loadSprites();
    setup_ = true;
}

void twn::UnkTownSpotlight::setLight(int index, dss::Fix32Vector3* pos)
{
    light_[index].unkfunc_0212e6b0(index + 8, pos);
}

void twn::UnkTownSpotlight::clearLight(int index)
{
    light_[index].deactivate();
}

void twn::UnkTownSpotlight::cleanup()
{
    if (setup_) {
        UnkTownSpotlightLight::releaseSprites();
        setup_ = false;
        setEnable(false);
        for (int i = 0; i < LIGHT_MAX; i++) {
            clearLight(i);
        }
    }
}

void twn::UnkTownSpotlight::update()
{
    if (enable_) {
        for (int i = 0; i < LIGHT_MAX; i++) {
            light_[i].update();
        }
    }
}

void twn::UnkTownSpotlight::draw()
{
    if (enable_) {
        setupOrtho2DFine();
        for (int screen = 0; screen < 2; screen++) {
            for (int i = 0; i < LIGHT_MAX; i++) {
                light_[i].draw(screen);
            }
        }
        blind_.draw();
    }
}

void twn::UnkTownSpotlight::setEnable(int enable)
{
    data_02101da4 = enable;
    enable_ = enable;
}

void twn::UnkTownSpotlight::setBlindAlpha(unsigned char alpha)
{
    blind_.setAlpha(alpha);
}

void twn::UnkTownSpotlight::setBlindColor(int r, int g, int b)
{
    blind_.setColor(r, g, b);
}

UnkMenuSprite twn::UnkTownSpotlightLight::sprite_[2];
