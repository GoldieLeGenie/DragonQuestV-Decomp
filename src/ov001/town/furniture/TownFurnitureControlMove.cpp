#include "ov001/town/TownFurnitureControl.hpp"
#include "ov001/town/TownStageManager.hpp"

THUMB twn::TownFurnitureControlMove::TownFurnitureControlMove()
{
}

THUMB twn::TownFurnitureControlMove::~TownFurnitureControlMove()
{
}

THUMB void twn::TownFurnitureControlMove::setFurnitureMove(int uid, int frame, dss::Fix32Vector3& start, dss::Fix32Vector3& goal)
{
    start_ = start;
    goal_ = goal;
    TownFurnitureControlBase::setup(uid, frame);
}

THUMB void twn::TownFurnitureControlMove::execute()
{
    if (enable_) {
        counter_++;
        dss::Fix32Vector3 dir = goal_ - start_;
        dss::Fix32Vector3 dx = start_ + dir * counter_ / frame_;
        TownStageManager::getSingleton()->setMapUidPosFX32(uid_, dx);
        if (counter_ >= frame_) {
            enable_ = false;
        }
    }
}

THUMB void twn::TownFurnitureControlMove::cleanup()
{
    TownFurnitureControlBase::cleanup();
}

ARM int twn::TownFurnitureControlMove::getType()
{
    return 0;
}
