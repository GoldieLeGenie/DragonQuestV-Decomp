#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownStageManager.hpp"

#pragma thumb on

inline void fld::FLDObject::setMainCameraFlag(int flag)
{
    mainCameraFlag_ = flag;
}

inline void FldStage::setMainCameraFlag(int flag)
{
    m_fld.setMainCameraFlag(flag);
}

inline void twn::TownStageManager::setMainCameraFlag(bool flag)
{
    stage_.setMainCameraFlag(flag);
}

twn::TownSystemCamera::TownSystemCamera()
{
}

twn::TownSystemCamera::~TownSystemCamera()
{
}

void twn::TownSystemCamera::initialize()
{
}

void twn::TownSystemCamera::terminate()
{
    TownCamera::getSingleton()->terminate();
}

void twn::TownSystemCamera::execute()
{
    TownCamera::getSingleton()->execute();
}

void twn::TownSystemCamera::draw()
{
    TownCamera::getSingleton()->draw();
    bool flag = TownCamera::getSingleton()->camera_.m_cameraNo == 0;
    if (flag == true) {
        TownStageManager::getSingleton()->setMainCameraFlag(true);
    } else {
        TownStageManager::getSingleton()->setMainCameraFlag(false);
    }
}
