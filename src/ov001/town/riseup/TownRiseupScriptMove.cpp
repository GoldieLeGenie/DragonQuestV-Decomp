#include "ov001/town/riseup/TownRiseupScriptMove.hpp"

THUMB twn::TownRiseupScriptMove::TownRiseupScriptMove()
{
}

THUMB twn::TownRiseupScriptMove::~TownRiseupScriptMove()
{
}

THUMB void twn::TownRiseupScriptMove::setup(int index)
{
    TownRiseupBase::setup(index);
}

THUMB void twn::TownRiseupScriptMove::setResource(void* data)
{
    item_ = (BillboardItem*)data;
}

THUMB void twn::TownRiseupScriptMove::execute()
{
    if (enable_) {
        dss::Fix32Vector3 move = end_ - start_;
        position_ = start_ + move * counter_ / frame_;
        if (++counter_ >= frame_) {
            cleanup();
        }
    }
}

THUMB void twn::TownRiseupScriptMove::draw()
{
    if (enable_) {
        dss::Fix32Vector3 scale = *item_->getScale();
        dss::Fix32Vector3 pos = position_;
        dss::Fix32 size = scale.vx;
        calcNearPos(pos, size);
        item_->setPosition(pos);
        item_->setScale(size);
        item_->draw();
        item_->setScale(scale);
    }
}

THUMB bool twn::TownRiseupScriptMove::isFinish()
{
    if (!enable_) {
        return true;
    }
    return false;
}

THUMB void twn::TownRiseupScriptMove::setScriptData(dss::Fix32Vector3 start, dss::Fix32Vector3 end, int frame, int type)
{
    start_ = start;
    end_ = end;
    frame_ = frame;
    counter_ = 0;
}

ARM int twn::TownRiseupScriptMove::getResorceType()
{
    return RISEUP_BILLBOARD_ITEM;
}

ARM int twn::TownRiseupScriptMove::getType()
{
    return RISEUP_BILLBOARD_SCRIPT;
}
