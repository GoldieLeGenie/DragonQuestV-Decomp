#pragma ipa file
#include "ov001/town/TownFurnitureControl.hpp"
#include "ov001/town/TownStageManager.hpp"

inline bool twn::TownFurnitureControlBase::isEnd()
{
    return enable_ == false;
}

inline int twn::TownFurnitureGroupMove::getType()
{
    return FURNITURE_GROUP_MOVE;
}

#pragma thumb on

inline void twn::TownStageManager::addMapGroupPosFX32(int gid, dss::Fix32Vector3& newPos)
{
    stage_.addMapGroupPosFX32(gid, newPos);
}

twn::TownFurnitureGroupMove::TownFurnitureGroupMove()
{
}

twn::TownFurnitureGroupMove::~TownFurnitureGroupMove()
{
}

void twn::TownFurnitureGroupMove::setFurnitureGroupMove(int uid, int frame, dss::Fix32Vector3& diff)
{
    diff_ = diff;
    TownFurnitureControlBase::setup(uid, frame);
}

void twn::TownFurnitureGroupMove::execute()
{
    if (enable_) {
        counter_++;
        TownStageManager::getSingleton()->addMapGroupPosFX32(uid_, diff_);
        if (counter_ >= frame_) {
            enable_ = false;
        }
    }
}

void twn::TownFurnitureGroupMove::cleanup()
{
    TownFurnitureControlBase::cleanup();
}
