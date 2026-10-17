#include "ov005/fld/FieldEffect.hpp"

inline int fld::FieldEffectSprite::getType()
{
    return FIELD_SPRITE_ANIM;
}

THUMB fld::FieldEffectSprite::FieldEffectSprite()
{
}

THUMB fld::FieldEffectSprite::~FieldEffectSprite()
{
}

THUMB void fld::FieldEffectSprite::setup(int index)
{
    FieldEffectBase::setup(index);
    sprite_.start();
}

THUMB void fld::FieldEffectSprite::setResource(void* resource)
{
    sprite_.setup((cmn::CommonEffectData*)resource, 1);
}

THUMB void fld::FieldEffectSprite::execute()
{
}

THUMB void fld::FieldEffectSprite::draw()
{
    if (enable_ != 0) {
        sprite_.draw();
        if (sprite_.isEnd()) {
            enable_ = 0;
        }
    }
}

THUMB void fld::FieldEffectSprite::cleanup()
{
    FieldEffectBase::cleanup();
    sprite_.cleanup(1);
}

THUMB void fld::FieldEffectSprite::setPosition(dss::Fix32Vector3 pos)
{
    position_ = pos;
    sprite_.setPosition(position_);
}

THUMB bool fld::FieldEffectSprite::isFinish()
{
    if (sprite_.isEnd()) {
        return true;
    }
    return false;
}
