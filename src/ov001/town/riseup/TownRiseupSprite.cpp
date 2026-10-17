#include "ov001/town/riseup/TownRiseupSprite.hpp"
#include "ov001/town/TownFurniture.hpp"
#include "main/sound/SoundManager.hpp"

inline void cmn::CommonEffectFlat::setAlpha(dss::Fix32 alpha)
{
    dssaEffect_.setAlpha(alpha);
}

inline int twn::TownFurnitureManager::getTwinkleEffectID()
{
    return twinkleEffect;
}

THUMB twn::TownRiseupSprite::TownRiseupSprite()
{
}

THUMB twn::TownRiseupSprite::~TownRiseupSprite()
{
}

THUMB void twn::TownRiseupSprite::setup(int index)
{
    TownRiseupBase::setup(index);
    if (startCounter_ == 0) {
        if (index == TownFurnitureManager::getSingleton()->getTwinkleEffectID()) {
            SoundManager::playSe(0x23e, 0);
        }
        sprite_.start();
        phase_ = PHASE_ANIM;
    } else {
        phase_ = PHASE_WAIT;
    }
}

THUMB void twn::TownRiseupSprite::setupNear(int flag)
{
    if (flag == true) {
        sprite_.setDisplayType(3);
    } else {
        sprite_.setDisplayType(0);
    }
}

THUMB void twn::TownRiseupSprite::setupNear2(int type)
{
    sprite_.setDisplayType(type);
}

THUMB void twn::TownRiseupSprite::setResource(void* data)
{
    sprite_.setup((cmn::CommonEffectData*)data, 1);
}

THUMB void twn::TownRiseupSprite::execute()
{
    if (enable_) {
        switch (phase_) {
        case PHASE_MOVE:
            if (startCounter_ > 0) {
                break;
            }
            if (startCounter_ == 0) {
                SoundManager::playSe(0x275, 0);
            }
            if (counter_ < frame_) {
                position_ = start_ + move_ * counter_;
            } else {
                position_ = end_;
            }
            setPosition(position_);
            counter_++;
            if (counter_ >= frame_) {
                cleanup();
            }
            break;
        case PHASE_FADE_IN:
            alpha_.value = (counter_ << 12) / frame_;
            sprite_.setAlpha(alpha_);
            counter_++;
            if (counter_ >= frame_) {
                cleanup();
            }
            break;
        case PHASE_FADE_OUT:
            alpha_.value = ((frame_ - counter_) << 12) / frame_;
            sprite_.setAlpha(alpha_);
            counter_++;
            if (counter_ >= frame_) {
                cleanup();
            }
            break;
        }
    }
}

THUMB void twn::TownRiseupSprite::draw()
{
    DSSAObject::calcType_ = 1;
    if (enable_) {
        switch (phase_) {
        case PHASE_WAIT:
            startCounter_--;
            if (startCounter_ <= 0) {
                if (index_ == TownFurnitureManager::getSingleton()->getTwinkleEffectID()) {
                    SoundManager::playSe(0x23e, 0);
                }
                sprite_.start();
                phase_ = PHASE_ANIM;
            }
            break;
        case PHASE_ANIM:
            sprite_.draw();
            if (sprite_.isEnd()) {
                enable_ = false;
            }
            break;
        case PHASE_MOVE:
            startCounter_--;
            if (startCounter_ > 0) {
                break;
            }
        case PHASE_FADE_IN:
        case PHASE_FADE_OUT:
            sprite_.draw();
            if (sprite_.isEnd()) {
                if (index_ == TownFurnitureManager::getSingleton()->getTwinkleEffectID()) {
                    SoundManager::playSe(0x23e, 0);
                }
                sprite_.start();
            }
            break;
        }
    }
    DSSAObject::calcType_ = 0;
}

THUMB void twn::TownRiseupSprite::cleanup()
{
    TownRiseupBase::cleanup();
    sprite_.cleanup(1);
}

THUMB void twn::TownRiseupSprite::setPosition(dss::Fix32Vector3 pos)
{
    position_ = pos;
    sprite_.setPosition(position_);
}

THUMB bool twn::TownRiseupSprite::isFinish()
{
    if (sprite_.isEnd()) {
        return true;
    }
    if (!enable_) {
        return true;
    }
    return false;
}

THUMB void twn::TownRiseupSprite::setScriptData(dss::Fix32Vector3 start, dss::Fix32Vector3 end, int frame, int type)
{
    phase_ = PHASE_MOVE;
    start_ = start;
    end_ = end;
    move_ = (end - start) / frame;
    frame_ = frame;
    counter_ = 0;
    setPosition(start);
    startCounter_ = type;
}

THUMB void twn::TownRiseupSprite::setScriptFade(dss::Fix32Vector3 pos, int frame, int flag)
{
    if (flag == false) {
        phase_ = PHASE_FADE_IN;
        alpha_.value = 0;
    } else {
        phase_ = PHASE_FADE_OUT;
        alpha_.value = 0x1000;
    }
    start_ = pos;
    end_ = pos;
    frame_ = frame;
    counter_ = 0;
    sprite_.setAlpha(alpha_);
}

THUMB void twn::TownRiseupSprite::setStartFrame(int frame)
{
    startCounter_ = frame;
}

ARM int twn::TownRiseupSprite::getResorceType()
{
    return 1;
}

ARM int twn::TownRiseupSprite::getType()
{
    return RISEUP_SPRITE_ANIM;
}
