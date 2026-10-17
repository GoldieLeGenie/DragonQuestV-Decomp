#include "ov001/town/riseup/TownRiseupIcon.hpp"
#include "main/sound/SoundManager.hpp"

THUMB twn::TownRiseupIcon::TownRiseupIcon()
{
}

THUMB twn::TownRiseupIcon::~TownRiseupIcon()
{
}

THUMB void twn::TownRiseupIcon::setup(int index)
{
    TownRiseupBase::setup(index);
    if (index <= 0x107 || index == 1000) {
        param = &defaultParam[0];
    } else if (index == 1001) {
        param = &defaultParam[1];
    } else {
        param = &defaultParam[2];
    }
    endCounter_ = param->endWait_;
    startCounter_ = param->startWait_;
    phase_ = PHASE_START_WAIT;
    alpha_ = 1;
}

THUMB void twn::TownRiseupIcon::setType(int type)
{
    param = &defaultParam[type];
}

THUMB void twn::TownRiseupIcon::setResource(void* data)
{
    item_ = (BillboardItem*)data;
}

THUMB void twn::TownRiseupIcon::setPosition(dss::Fix32Vector3 pos)
{
    height_ = pos.vy.value;
    TownRiseupBase::setPosition(pos);
}

THUMB void twn::TownRiseupIcon::execute()
{
    if (enable_) {
        switch (phase_) {
        case PHASE_START_WAIT:
            if (--startCounter_ <= 0) {
                SoundManager::playSe(param->sound_, 0);
                phase_ = PHASE_RISE;
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
            if (alpha_ <= 0) {
                phase_ = PHASE_NONE;
                enable_ = false;
            }
            break;
        }
    }
}

THUMB void twn::TownRiseupIcon::draw()
{
    if (enable_ && startCounter_ == 0) {
        dss::Fix32Vector3 scale = *item_->getScale();
        dss::Fix32Vector3 pos = position_;
        dss::Fix32 size = scale.vx;
        calcNearPos(pos, size);
        item_->setPosition(pos);
        item_->setScale(size);
        item_->setAlpha((unsigned char)alpha_);
        item_->draw();
        item_->setScale(scale);
    }
}

THUMB bool twn::TownRiseupIcon::isFinish()
{
    if (phase_ == PHASE_FADE_OUT) {
        return true;
    }
    if (!enable_) {
        return true;
    }
    return false;
}

ARM void twn::TownRiseupIcon::setEndFrame(int frame)
{
    endCounter_ = frame;
}

ARM void twn::TownRiseupIcon::setStartFrame(int frame)
{
    startCounter_ = frame;
}

ARM int twn::TownRiseupIcon::getResorceType()
{
    return RISEUP_BILLBOARD_ITEM;
}

ARM int twn::TownRiseupIcon::getType()
{
    return RISEUP_BILLBOARD_ITEM;
}
