#include "ov005/fld/FieldEffect.hpp"

THUMB fld::FieldEffectStorage::FieldEffectStorage()
{
}

THUMB fld::FieldEffectStorage::~FieldEffectStorage()
{
}

THUMB void fld::FieldEffectStorage::initialize()
{
    spriteCounter_ = 0;
    for (unsigned int i = 0; i < EFFECT_SPRITE_MAX; i++) {
        sprite_[i].enable_ = 0;
    }
}

THUMB void fld::FieldEffectStorage::terminate()
{
}

THUMB fld::FieldEffectBase* fld::FieldEffectStorage::getContainer(int type)
{
    if (type == FieldEffectBase::FIELD_SPRITE_ANIM) {
        spriteCounter_++;
        for (unsigned int i = 0; i < EFFECT_SPRITE_MAX; i++) {
            if (sprite_[i].enable_ == 0) {
                return &sprite_[i];
            }
        }
    }
    return NULL;
}

THUMB void fld::FieldEffectStorage::restoreContainer(int type)
{
    if (type == FieldEffectBase::FIELD_SPRITE_ANIM) {
        spriteCounter_--;
    }
}
