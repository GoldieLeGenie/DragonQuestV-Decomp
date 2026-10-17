#include "ov005/fld/FieldCarrierDraw.hpp"

THUMB fld::FieldCarrirerDraw::FieldCarrirerDraw()
{
}

THUMB fld::FieldCarrirerDraw::~FieldCarrirerDraw()
{
}

THUMB void fld::FieldCarrirerDraw::setOffsetXY(int x, int y)
{
}

THUMB void fld::FieldCarrirerDraw::setHigh(int high)
{
}

THUMB void fld::FieldCarrirerDraw::setPosition(dss::Fix32Vector3& pos)
{
    position_ = pos;
}

THUMB dss::Fix32Vector3& fld::FieldCarrirerDraw::getPosition()
{
    return position_;
}

THUMB void fld::FieldCarrirerDraw::setHeight(int height)
{
}

THUMB void fld::FieldCarrirerDraw::setShadowAlpha(unsigned char alpha)
{
}
