#pragma ipa file
#include "ov005/fld/FieldCarrierDraw.hpp"

THUMB fld::FieldDragonDraw::FieldDragonDraw()
{
}

THUMB fld::FieldDragonDraw::~FieldDragonDraw()
{
}

THUMB void fld::FieldDragonDraw::setOffsetXY(int x, int y)
{
    offsetx_ = x;
    offsety_ = y;
}

THUMB void fld::FieldDragonDraw::setHigh(int high)
{
    high_ = high;
}

THUMB void fld::FieldDragonDraw::setup()
{
    dragon_.setup("data/chr/h309.pack", 0x40, 0x40, 0);
    dragon_.depth_ = 6;
    dragon_.setShadowFlag(0);
    shadow_.setup("data/chr/h310.pack", 0x20, 0x20, 0);
    shadow_.depth_ = 6;
    shadow_.setShadowFlag(0);
    shadow_.setAlpha(0x10);
    shadow_.setPolygonID(0x1f);
    high_ = 0;
    offsetx_ = 0;
    offsety_ = 0;
}

THUMB void fld::FieldDragonDraw::setRotate(unsigned int rot)
{
    dragon_.setDirection(rot);
    shadow_.setDirection(rot);
}

THUMB void fld::FieldDragonDraw::draw(dss::Vector2<int>& pos)
{
    if (high_ != 0) {
        dragon_.setPosition(pos.vx + offsetx_, offsety_ + (pos.vy - high_ + 0xc));
        dragon_.draw();
        shadow_.setPosition(pos.vx + offsetx_, offsety_ + (pos.vy + 0xc));
        shadow_.draw();
    } else {
        dragon_.setPosition(pos.vx + offsetx_, offsety_ + (pos.vy + 0xc));
        dragon_.draw();
        shadow_.setPosition(pos.vx + offsetx_, offsety_ + (pos.vy + 0xc));
        shadow_.draw();
    }
}

THUMB void fld::FieldDragonDraw::cleanup()
{
    dragon_.cleanup();
    shadow_.cleanup();
}

THUMB void fld::FieldDragonDraw::setDrawPosition(int x, int y)
{
    dragon_.setPosition(x, y);
    shadow_.setPosition(x, y);
}

THUMB void fld::FieldDragonDraw::setDepth(int depth)
{
    dragon_.depth_ = depth + 1;
    shadow_.depth_ = depth;
}

THUMB void fld::FieldDragonDraw::setShadowWH(int w, int h)
{
    shadow_.shadow_.setSize(w, h);
}

THUMB void fld::FieldDragonDraw::setDisplayEnable(int flag)
{
    dragon_.setDisplayEnable(flag);
    shadow_.setDisplayEnable(flag);
}

THUMB int fld::FieldDragonDraw::isDisplayEnable()
{
    return dragon_.isDisplayEnable();
}

THUMB void fld::FieldDragonDraw::setShadowStay(int flag)
{
    dragon_.setShadowStay(flag);
}

THUMB void fld::FieldDragonDraw::setAnimFlag(int flag)
{
    dragon_.setAnimFlag(flag);
    shadow_.setAnimFlag(flag);
}

THUMB void fld::FieldDragonDraw::setShadowFlag(int flag)
{
    shadow_.setShadowFlag(flag);
}

THUMB void fld::FieldDragonDraw::setShadowDepth(int depth)
{
    dragon_.depth_ = depth + 1;
    shadow_.depth_ = depth;
}
