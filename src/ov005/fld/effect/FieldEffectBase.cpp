#include "ov005/fld/FieldEffect.hpp"

inline bool fld::FieldEffectBase::isFinish()
{
    return enable_ == 0;
}

THUMB fld::FieldEffectBase::FieldEffectBase()
{
    enable_ = 0;
}

THUMB fld::FieldEffectBase::~FieldEffectBase()
{
}

THUMB void fld::FieldEffectBase::setup(int index)
{
    enable_ = 1;
    index_ = index;
}

THUMB void fld::FieldEffectBase::cleanup()
{
    enable_ = 0;
}

THUMB void fld::FieldEffectBase::execute()
{
}

THUMB void fld::FieldEffectBase::setPosition(dss::Fix32Vector3 pos)
{
    position_ = pos;
}
