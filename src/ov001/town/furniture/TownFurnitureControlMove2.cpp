#include "ov001/town/TownFurnitureControl.hpp"
#include "ov001/town/TownStageManager.hpp"

THUMB twn::TownFurnitureControlMove2::TownFurnitureControlMove2()
{
}

THUMB twn::TownFurnitureControlMove2::~TownFurnitureControlMove2()
{
}

THUMB void twn::TownFurnitureControlMove2::execute()
{
    if (enable_) {
        dss::Fix32Vector3 dir = (goal_ - start_) / frame_;
        dss::Fix32Vector3 dx = start_ + dir * counter_;
        if (counter_ >= frame_) {
            enable_ = false;
            dx = goal_;
        }
        TownStageManager::getSingleton()->setMapUidPosFX32(uid_, dx);
        counter_++;
    }
}

THUMB void twn::TownFurnitureControlMove2::cleanup()
{
    TownFurnitureControlBase::cleanup();
}

ARM int twn::TownFurnitureControlMove2::getType()
{
    return 0;
}
