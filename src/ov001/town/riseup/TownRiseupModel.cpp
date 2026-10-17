#pragma ipa file
#include "ov001/town/riseup/TownRiseupModel.hpp"

inline int twn::TownRiseupModel::getType()
{
    return RISEUP_MODEL_ANIM;
}

inline int twn::TownRiseupModel::getResorceType()
{
    return 1;
}

#pragma thumb on

twn::TownRiseupModel::TownRiseupModel()
{
}

twn::TownRiseupModel::~TownRiseupModel()
{
}

void twn::TownRiseupModel::setup(int index)
{
    TownRiseupBase::setup(index);
    model_.setDisplayType(2);
    model_.setPosition(position_);
    model_.start();
}

void twn::TownRiseupModel::setResource(void* data)
{
    model_.setup((cmn::CommonEffectData*)data, 1);
}

void twn::TownRiseupModel::execute()
{
}

void twn::TownRiseupModel::draw()
{
    if (enable_) {
        model_.draw();
        if (model_.isEnd()) {
            enable_ = false;
        }
    }
}

void twn::TownRiseupModel::cleanup()
{
    TownRiseupBase::cleanup();
    model_.cleanup(1);
}

void twn::TownRiseupModel::setPosition(dss::Fix32Vector3 pos)
{
    position_ = pos;
    model_.setPosition(position_);
}

bool twn::TownRiseupModel::isFinish()
{
    if (model_.isEnd()) {
        return true;
    }
    return enable_ == false;
}
