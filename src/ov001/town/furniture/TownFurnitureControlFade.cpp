#include "ov001/town/TownFurnitureControl.hpp"
#include "ov001/town/TownStageManager.hpp"

inline void twn::TownStageManager::setMapUidAlpha(int uid, int alpha, int flag)
{
    stage_.m_fld.SetMapUidAlpha(uid, alpha, flag);
}

THUMB twn::TownFurnitureControlFade::TownFurnitureControlFade()
{
}

THUMB twn::TownFurnitureControlFade::~TownFurnitureControlFade()
{
}

THUMB void twn::TownFurnitureControlFade::execute()
{
    if (enable_) {
        counter_++;
        int alpha;
        if (fade_) {
            alpha = 0x1f - counter_ * 0x1f / frame_;
        } else {
            alpha = counter_ * 0x1f / frame_;
        }
        TownStageManager::getSingleton()->setMapUidAlpha(uid_, alpha, priority_);
        if (counter_ >= frame_) {
            enable_ = false;
        }
    }
}

THUMB void twn::TownFurnitureControlFade::cleanup()
{
    TownFurnitureControlBase::cleanup();
}

THUMB void twn::TownFurnitureControlFade::setFurnitureFade(int uid, int frame, int fade, int priority)
{
    fade_ = fade;
    priority_ = priority;
    TownFurnitureControlBase::setup(uid, frame);
}

ARM int twn::TownFurnitureControlFade::getType()
{
    return 2;
}
