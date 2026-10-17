#include "ov001/town/TownFurnitureControl.hpp"
#include "ov001/town/TownStageManager.hpp"

inline void FldStage::setRotObjectUid(int uId, dss::Fix32Vector3& angle)
{
    m_fld.SetMapUidRotFX32(uId, (VecFx32*)&angle);
}

inline void twn::TownStageManager::setRotObjectUid(int uid, dss::Fix32Vector3& angle)
{
    stage_.setRotObjectUid(uid, angle);
}

THUMB twn::TownFurnitureControlRotate::TownFurnitureControlRotate()
{
}

THUMB twn::TownFurnitureControlRotate::~TownFurnitureControlRotate()
{
}

THUMB void twn::TownFurnitureControlRotate::setFurnitureRotate(int uid, int frame, dss::Fix32Vector3& start, dss::Fix32Vector3& goal)
{
    start_ = start;
    goal_ = goal;
    TownFurnitureControlBase::setup(uid, frame);
}

THUMB void twn::TownFurnitureControlRotate::execute()
{
    if (enable_) {
        counter_++;
        dss::Fix32Vector3 dir = goal_ - start_;
        dss::Fix32Vector3 dx = start_ + dir * counter_ / frame_;
        TownStageManager::getSingleton()->setRotObjectUid(uid_, dx);
        if (counter_ >= frame_) {
            enable_ = false;
        }
    }
}

THUMB void twn::TownFurnitureControlRotate::cleanup()
{
    TownFurnitureControlBase::cleanup();
}

ARM int twn::TownFurnitureControlRotate::getType()
{
    return 3;
}
