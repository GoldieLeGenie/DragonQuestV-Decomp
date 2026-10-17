#pragma ipa file
#include "ov001/town/TownFurnitureControl.hpp"
#include "ov001/town/TownStageManager.hpp"

inline bool twn::TownFurnitureControlBase::isEnd()
{
    return enable_ == false;
}

inline int twn::TownFurnitureGroupRotate::getType()
{
    return FURNITURE_GROUP_ROTATE;
}

#pragma thumb on

inline void twn::TownStageManager::addMapGroupRotFX32(int gid, dss::Fix32Vector3& newPos)
{
    stage_.addMapGroupRotFX32(gid, newPos);
}

twn::TownFurnitureGroupRotate::TownFurnitureGroupRotate()
{
}

twn::TownFurnitureGroupRotate::~TownFurnitureGroupRotate()
{
}

void twn::TownFurnitureGroupRotate::setFurnitureGroupRotate(int uid, int frame, dss::Fix32Vector3& diff)
{
    diff_ = diff;
    TownFurnitureControlBase::setup(uid, frame);
}

void twn::TownFurnitureGroupRotate::execute()
{
    if (enable_) {
        counter_++;
        TownStageManager::getSingleton()->addMapGroupRotFX32(uid_, diff_);
        if (counter_ >= frame_) {
            enable_ = false;
        }
    }
}

void twn::TownFurnitureGroupRotate::cleanup()
{
    TownFurnitureControlBase::cleanup();
}
