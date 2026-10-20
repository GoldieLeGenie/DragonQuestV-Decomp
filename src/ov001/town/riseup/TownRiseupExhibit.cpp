#pragma ipa file
#include "ov001/town/riseup/TownRiseupExhibit.hpp"

inline int twn::TownRiseupExhibit::getType()
{
    return RISEUP_BILLBOARD_EXHIBIT;
}

inline int twn::TownRiseupExhibit::getResorceType()
{
    return RISEUP_BILLBOARD_ITEM;
}

#pragma thumb on

inline twn::UnkBillboardCorners::UnkBillboardCorners(const dss::Vector2<dss::Fix16>& v0, const dss::Vector2<dss::Fix16>& v1,
                                                   const dss::Vector2<dss::Fix16>& v2, const dss::Vector2<dss::Fix16>& v3)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
}

inline void UnkBillboardTexCoord::set(const dss::Vector2<dss::Fix32>& v0, const dss::Vector2<dss::Fix32>& v1,
                                      const dss::Vector2<dss::Fix32>& v2, const dss::Vector2<dss::Fix32>& v3)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
}

static dss::Vector2<dss::Fix16> xyLeftBottom(-0.48f, -0.0f);
static dss::Vector2<dss::Fix16> xyRightBottom(0.48f, -0.0f);
static dss::Vector2<dss::Fix16> xyRightTop(0.48f, 0.96f);
static dss::Vector2<dss::Fix16> xyLeftTop(-0.48f, 0.96f);
twn::UnkBillboardCorners twn::TownRiseupExhibit::xy_(xyLeftBottom, xyRightBottom, xyRightTop, xyLeftTop);

twn::TownRiseupExhibit::TownRiseupExhibit() : phase_(PHASE_NONE)
{
}

twn::TownRiseupExhibit::~TownRiseupExhibit()
{
}

void twn::TownRiseupExhibit::setup(int index)
{
    TownRiseupBase::setup(index);
}

void twn::TownRiseupExhibit::setResource(void* data)
{
    item_ = (BillboardItem*)data;
}

void twn::TownRiseupExhibit::setStartFrame(int frame)
{
    startFrame_ = frame;
    phase_ = PHASE_FADE_IN;
    frame_ = 0;
}

void twn::TownRiseupExhibit::setEndFrame(int frame)
{
    endFrame_ = frame;
    phase_ = PHASE_FADE_OUT;
    frame_ = 0;
}

void twn::TownRiseupExhibit::execute()
{
    if (enable_) {
        if (phase_ == PHASE_FADE_IN) {
            alpha_ = frame_ * 31 / startFrame_;
            if (frame_ == startFrame_) {
                phase_ = PHASE_NONE;
            } else {
                frame_++;
            }
        } else if (phase_ == PHASE_FADE_OUT) {
            alpha_ = 31 - frame_ * 31 / endFrame_;
            if (frame_ == endFrame_) {
                phase_ = PHASE_NONE;
                enable_ = false;
            } else {
                frame_++;
            }
        }
    }
}

void twn::TownRiseupExhibit::draw()
{
    if (enable_) {
        dss::Fix32Vector3 scale = *item_->getScale();
        dss::Fix32Vector3 pos = position_;
        dss::Fix32 size = scale.vx;
        {
            dss::Fix32Vector3 camPos = getCamera()->getPosition();
            dss::Fix32Vector3 nearPos = pos;
            dss::Fix32Vector3 camDir = camPos - nearPos;
            dss::Fix32 length = camDir.length();
            camDir.normalize();
            nearPos += camDir * 3 / 4;
            dss::Fix32 sub = length - dss::Fix32(1L);
            size = size * sub / length;
            pos = nearPos;
        }
        item_->setPosition(pos);
        item_->setScale(size);
        item_->setItemVertex(&xy_);
        item_->setItemTexCoord(&uv_);
        item_->setAlpha(alpha_);
        item_->draw();
        item_->setScale(scale);
    }
}

bool twn::TownRiseupExhibit::isFinish()
{
    return phase_ == PHASE_NONE;
}

// the original recomputes u + 32 and v + 32 for every corner
#pragma push
#pragma opt_common_subs off
void twn::TownRiseupExhibit::setExhibitIcon(int number)
{
    icon_ = number;
    number -= 0xd0;
    int u = (number % 8) * 32;
    int v = (number / 8) * 32;
    dss::Vector2<dss::Fix32> leftTop(u, v);
    dss::Vector2<dss::Fix32> rightTop(u + 32, v);
    dss::Vector2<dss::Fix32> rightBottom(u + 32, v + 32);
    dss::Vector2<dss::Fix32> leftBottom(u, v + 32);
    uv_.set(leftBottom, rightBottom, rightTop, leftTop);
}
#pragma pop

#include "main/dss/DssVectorDefault.hpp"
