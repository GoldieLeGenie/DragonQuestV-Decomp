#pragma ipa file
#include "ov005/fld/FieldCarrierDraw.hpp"

namespace fld {
namespace {
    int shipOffset[7] = { 0, 1, 2, 2, 1, 0, -1 };
}
}

fld::SpriteShipCharacter fld::FieldShipDraw::nami_;

THUMB fld::FieldShipDraw::FieldShipDraw()
{
}

THUMB fld::FieldShipDraw::~FieldShipDraw()
{
}

THUMB void fld::FieldShipDraw::initialize()
{
    nami_.setup("data/chr/h303.pack");
    nami_.unk_28 = 4;
    nami_.setDirection(4);
    nami_.setShadowFlag(0);
}

THUMB void fld::FieldShipDraw::terminate()
{
    nami_.cleanup();
}

THUMB void fld::FieldShipDraw::setup()
{
    ship_.setup("data/chr/h302.pack", 0x28, 0x20, 0);
    ship_.unk_28 = 2;
    ship_.setDirection(4);
    ship_.setShadowFlag(0);
    ship_.setAnimFlag(0);
    ride_ = 0;
    offset_ = 0;
}

THUMB void fld::FieldShipDraw::draw(dss::Vector2<int>& pos)
{
    ship_.setPosition(pos.vx, pos.vy + 6 + shipOffset[offset_ / 12]);
    nami_.setPosition(pos.vx, pos.vy + 0xb);
    SpriteShadow& shadow = ship_.shadow_;
    shadow.setPosition(pos.vx, pos.vy);
    if (ride_ != 0) {
        nami_.setAnimFlag(2);
        nami_.draw();
        if (SpriteCharacter::unkfunc_020586dc()) {
            offset_++;
        }
    } else {
        ship_.setAnimFlag(0);
    }
    ship_.draw();
    if (offset_ == 0x54) {
        offset_ = 0;
    }
}

THUMB void fld::FieldShipDraw::setRotate(unsigned int dirIdx)
{
    nami_.setDirection(dirIdx);
    ship_.setDirection(dirIdx);
}

THUMB void fld::FieldShipDraw::cleanup()
{
    ship_.cleanup();
}

THUMB void fld::FieldShipDraw::setDrawPosition(int posX, int posY)
{
    ship_.setPosition(posX, posY);
}

THUMB void fld::FieldShipDraw::setDepth(int d)
{
    ship_.unk_28 = d;
}

THUMB void fld::FieldShipDraw::setShadowWH(int x, int y)
{
    ship_.shadow_.unkfunc_02047ec0(x, y);
}

THUMB void fld::FieldShipDraw::setDisplayEnable(int flag)
{
    ship_.setDisplayEnable(flag);
}

THUMB int fld::FieldShipDraw::isDisplayEnable()
{
    return ship_.isDisplayEnable();
}

THUMB void fld::FieldShipDraw::setShadowStay(int flag)
{
    ship_.setShadowStay(flag);
}

THUMB void fld::FieldShipDraw::setAnimFlag(int flag)
{
    ship_.setAnimFlag(flag);
}

THUMB void fld::FieldShipDraw::setShadowFlag(int flag)
{
    ship_.setShadowFlag(flag);
}

THUMB void fld::FieldShipDraw::setShadowDepth(int depth)
{
    ship_.shadow_.unk_28 = depth;
}
