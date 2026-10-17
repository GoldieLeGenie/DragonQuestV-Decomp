#include "ov001/town/riseup/TownRiseupMedal.hpp"
#include "main/sound/SoundManager.hpp"

THUMB twn::TownRiseupMedal::TownRiseupMedal()
{
}

THUMB twn::TownRiseupMedal::~TownRiseupMedal()
{
}

THUMB void twn::TownRiseupMedal::setup(int index)
{
    TownRiseupBase::setup(index);
    param = &defaultParam[3];
    endCounter_ = param->endWait_;
    startCounter_ = param->startWait_;
    phase_ = PHASE_START_WAIT;
    alpha_ = 1;
    sprite_.setDisplayType(2);
}

THUMB void twn::TownRiseupMedal::setType(int type)
{
    param = &defaultParam[type];
}

THUMB void twn::TownRiseupMedal::setResource(void* data)
{
    sprite_.setup((cmn::CommonEffectData*)data, 1);
}

THUMB void twn::TownRiseupMedal::setPosition(dss::Fix32Vector3 pos)
{
    height_ = pos.vy.value;
    TownRiseupBase::setPosition(pos);
    sprite_.setPosition(position_);
}

THUMB void twn::TownRiseupMedal::execute()
{
    if (enable_) {
        switch (phase_) {
        case PHASE_START_WAIT:
            if (--startCounter_ <= 0) {
                SoundManager::playRestart(0x2b, 5);
                phase_ = PHASE_RISE;
                sprite_.start();
            }
            break;
        case PHASE_RISE:
            if (position_.vy.value >= param->maxHigh_ + height_) {
                phase_ = PHASE_END_WAIT;
                break;
            }
            alpha_ += param->fadein_;
            if (alpha_ > 31) {
                alpha_ = 31;
            }
            position_.vy.value += param->velocity_;
            if (position_.vy.value > param->maxHigh_ + height_) {
                position_.vy.value = param->maxHigh_ + height_;
            }
            break;
        case PHASE_END_WAIT:
            if (--endCounter_ <= 0) {
                phase_ = PHASE_FADE_OUT;
            }
            break;
        case PHASE_FADE_OUT:
            alpha_ -= param->fadeout_;
            if (alpha_ == 0) {
                phase_ = PHASE_NONE;
                enable_ = false;
            }
            break;
        }
    }
}

THUMB void twn::TownRiseupMedal::draw()
{
    if (enable_ && startCounter_ == 0) {
        dss::Fix32 rate = sprite_.rate_;
        dss::Fix32Vector3 pos = position_;
        dss::Fix32 scale = rate;
        calcNearPos(pos, scale);
        sprite_.setPosition(pos);
        sprite_.setScale(scale);
        sprite_.draw();
        sprite_.setScale(rate);
        if (sprite_.isEnd()) {
            enable_ = false;
        }
    }
}

THUMB void twn::TownRiseupMedal::cleanup()
{
    TownRiseupBase::cleanup();
    sprite_.cleanup(1);
}

THUMB bool twn::TownRiseupMedal::isFinish()
{
    if (phase_ == PHASE_FADE_OUT) {
        return true;
    }
    if (!enable_) {
        return true;
    }
    return false;
}

ARM void twn::TownRiseupMedal::setEndFrame(int frame)
{
    endCounter_ = frame;
}

ARM void twn::TownRiseupMedal::setStartFrame(int frame)
{
    startCounter_ = frame;
}

ARM int twn::TownRiseupMedal::getResorceType()
{
    return 1;
}

ARM int twn::TownRiseupMedal::getType()
{
    return RISEUP_SPRITE_MEDAL;
}
