#include "ov005/fld/FieldEffect.hpp"
#include "main/dss/UnkDisplay.hpp"

int fld::FieldEffectManager::riseupCounter_;

THUMB fld::FieldEffectManager::FieldEffectManager()
{
}

THUMB fld::FieldEffectManager::~FieldEffectManager()
{
}

THUMB fld::FieldEffectManager& fld::FieldEffectManager::getSingleton()
{
    static FieldEffectManager fieldEffectManager;
    return fieldEffectManager;
}

THUMB void fld::FieldEffectManager::initialize()
{
    effectStorage_.initialize();
    effectResourece_.initialize();
    riseupCounter_ = 0;
}

THUMB void fld::FieldEffectManager::terminate()
{
    for (int i = 0; i < EFFECT_MAX; i++) {
        if (riseup_[i] != NULL) {
            cleanup(i);
        }
    }
    effectStorage_.terminate();
    effectResourece_.terminate();
}

THUMB int fld::FieldEffectManager::setup(int type, dss::Fix32Vector3 pos)
{
    for (int i = 0; i < EFFECT_MAX; i++) {
        if (riseup_[i] == NULL) {
            riseup_[i] = effectStorage_.getContainer(FieldEffectBase::FIELD_SPRITE_ANIM);
            riseup_[i]->setResource(effectResourece_.getResource(type));
            riseup_[i]->setup(type);
            riseup_[i]->setPosition(pos);
            riseupCounter_++;
            return i;
        }
    }
    return 0;
}

THUMB void fld::FieldEffectManager::cleanup(int index)
{
    effectStorage_.restoreContainer(riseup_[index]->getType());
    effectResourece_.restoreResource(riseup_[index]->index_);
    riseup_[index]->cleanup();
    riseup_[index] = NULL;
    riseupCounter_--;
}

THUMB void fld::FieldEffectManager::draw()
{
    if (riseupCounter_ != 0) {
        for (int i = 0; i < EFFECT_MAX; i++) {
            if (riseup_[i] != NULL) {
                if (unkfunc_0204ccd0() & 1) {
                    riseup_[i]->draw();
                }
                if (riseup_[i]->enable_ == 0) {
                    cleanup(i);
                }
            }
        }
    }
}

THUMB void fld::FieldEffectManager::execute()
{
    if (riseupCounter_ != 0) {
        for (int i = 0; i < EFFECT_MAX; i++) {
            if (riseup_[i] != NULL) {
                riseup_[i]->execute();
                if (riseup_[i]->enable_ == 0) {
                    cleanup(i);
                }
            }
        }
    }
}
