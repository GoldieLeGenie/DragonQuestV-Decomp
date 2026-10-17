#pragma ipa file
#include "ov005/fld/FieldCarrierDraw.hpp"

THUMB fld::FieldCarpetDraw::FieldCarpetDraw()
{
}

THUMB fld::FieldCarpetDraw::~FieldCarpetDraw()
{
}

THUMB void fld::FieldCarpetDraw::setHeight(int height)
{
    high_ = height;
}

THUMB void fld::FieldCarpetDraw::setup()
{
    carpet_.setup("data/chr/h304.pack", 0x20, 0x20, 0);
    carpet_.unk_28 = 4;
    carpet_.setDirection(4);
    carpet_.setShadowFlag(0);
    shadow_.setup("data/chr/h305.pack", 0x20, 0x20, 0);
    shadow_.unk_28 = 3;
    shadow_.setAlpha(0x10);
    shadow_.setDirection(4);
    shadow_.setShadowFlag(0);
    shadow_.setPolygonID(0x1f);
    ride_ = 0;
    high_ = 0;
}

THUMB void fld::FieldCarpetDraw::draw(dss::Vector2<int>& pos)
{
    carpet_.setPosition(pos.vx, pos.vy - high_);
    shadow_.setPosition(pos.vx, pos.vy);
    carpet_.draw();
    shadow_.draw();
}

THUMB void fld::FieldCarpetDraw::setRotate(unsigned int rot)
{
    shadow_.setDirection(rot);
    carpet_.setDirection(rot);
}

THUMB void fld::FieldCarpetDraw::cleanup()
{
    carpet_.cleanup();
    shadow_.cleanup();
}

THUMB void fld::FieldCarpetDraw::setDrawPosition(int x, int y)
{
    carpet_.setPosition(x, y);
    shadow_.setPosition(x, y);
}

THUMB void fld::FieldCarpetDraw::setDepth(int depth)
{
    carpet_.unk_28 = depth;
}

THUMB void fld::FieldCarpetDraw::setShadowWH(int w, int h)
{
}

THUMB void fld::FieldCarpetDraw::setDisplayEnable(int flag)
{
    carpet_.setDisplayEnable(flag);
    shadow_.setDisplayEnable(flag);
}

THUMB int fld::FieldCarpetDraw::isDisplayEnable()
{
    return carpet_.isDisplayEnable();
}

THUMB void fld::FieldCarpetDraw::setShadowStay(int flag)
{
}

THUMB void fld::FieldCarpetDraw::setAnimFlag(int flag)
{
    carpet_.setAnimFlag(flag);
    shadow_.setAnimFlag(flag);
}

THUMB void fld::FieldCarpetDraw::setShadowFlag(int flag)
{
    shadow_.setDisplayEnable(flag);
}

THUMB void fld::FieldCarpetDraw::setShadowDepth(int depth)
{
    shadow_.unk_28 = depth;
}
