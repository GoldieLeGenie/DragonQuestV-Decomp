#include "ov001/town/TownFurnitureControl.hpp"

THUMB twn::TownFurnitureControlBase::TownFurnitureControlBase()
{
    enable_ = false;
}

THUMB twn::TownFurnitureControlBase::~TownFurnitureControlBase()
{
}

THUMB void twn::TownFurnitureControlBase::setup(int uid, int frame)
{
    enable_ = true;
    uid_ = uid;
    frame_ = frame;
    counter_ = 0;
    flag_.set(FLAG_GARBAGE_CORRECT);
}

THUMB void twn::TownFurnitureControlBase::cleanup()
{
    enable_ = false;
}

THUMB void twn::TownFurnitureControlBase::execute()
{
}

THUMB void twn::TownFurnitureControlBase::setFurnitureMove(int uid, int frame, dss::Fix32Vector3& start, dss::Fix32Vector3& goal)
{
}

THUMB void twn::TownFurnitureControlBase::setFurnitureFade(int uid, int frame, int fade, int priority)
{
}

THUMB void twn::TownFurnitureControlBase::setFurnitureRotate(int uid, int frame, dss::Fix32Vector3& start, dss::Fix32Vector3& goal)
{
}

THUMB void twn::TownFurnitureControlBase::setFurnitureGroupMove(int group, int frame, dss::Fix32Vector3& speed)
{
}

THUMB void twn::TownFurnitureControlBase::setFurnitureGroupRotate(int group, int frame, dss::Fix32Vector3& speed)
{
}

THUMB void twn::TownFurnitureControlBase::setGarbageCorrect(bool flag)
{
    if (flag) {
        flag_.set(FLAG_GARBAGE_CORRECT);
    } else {
        flag_.remove(FLAG_GARBAGE_CORRECT);
    }
}

THUMB bool twn::TownFurnitureControlBase::isGarbageCorrect()
{
    return flag_.check(FLAG_GARBAGE_CORRECT);
}
