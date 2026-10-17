#pragma ipa file
#include "ov001/town/riseup/TownRiseupBase.hpp"

THUMB twn::TownRiseupBase::TownRiseupBase()
{
    enable_ = false;
}

THUMB twn::TownRiseupBase::~TownRiseupBase()
{
}

THUMB void twn::TownRiseupBase::setup(int index)
{
    enable_ = true;
    index_ = index;
}

THUMB void twn::TownRiseupBase::setType(int type)
{
}

THUMB void twn::TownRiseupBase::cleanup()
{
    enable_ = false;
}

THUMB void twn::TownRiseupBase::execute()
{
}

THUMB void twn::TownRiseupBase::setPosition(dss::Fix32Vector3 pos)
{
    position_ = pos;
}

THUMB void twn::TownRiseupBase::setCamera(dss::Camera* camera)
{
    camera_ = camera;
}

THUMB dss::Camera* twn::TownRiseupBase::getCamera()
{
    return camera_;
}

THUMB void twn::TownRiseupBase::calcNearPos(dss::Fix32Vector3& pos, dss::Fix32 scale)
{
    dss::Fix32Vector3 camPos = getCamera()->getPosition();
    dss::Fix32Vector3 nearPos = pos;
    dss::Fix32Vector3 dir = camPos - nearPos;
    dss::Fix32 length = dir.length();
    dir.normalize();
    nearPos += dir;
    dss::Fix32 sub = length - dss::Fix32(1L);
    scale = scale * sub / length;
    pos = nearPos;
}

THUMB void twn::TownRiseupBase::setScriptData(dss::Fix32Vector3 start, dss::Fix32Vector3 end, int frame, int type)
{
}

THUMB void twn::TownRiseupBase::setScriptFade(dss::Fix32Vector3 pos, int frame, int flag)
{
}

THUMB void twn::TownRiseupBase::setupNear(int flag)
{
}

THUMB void twn::TownRiseupBase::setupNear2(int type)
{
}

THUMB void twn::TownRiseupBase::setStartFrame(int frame)
{
}

THUMB void twn::TownRiseupBase::setEndFrame(int frame)
{
}

THUMB void twn::TownRiseupBase::setExhibitIcon(int icon)
{
}

dss::Camera* twn::TownRiseupBase::camera_;
dss::Fix32 twn::TownRiseupBase::near_scale = 2.0f;
twn::TownRiseupBase::RiseupParam twn::TownRiseupBase::defaultParam[4] = {
    {0x1a00, 0x200, 0x10, 0x20, 0x146, 0xc, 1},
    {0x1a00, 0x200, 0x10, 0x20, 0x144, 0xc, 1},
    {0x1a00, 0x200, 0x10, 0x20, 0x145, 0xc, 1},
    {0x1a00, 0x200, 0x10, 0xb4, 0x146, 0xc, 1},
};

ARM bool twn::TownRiseupBase::isFinish()
{
    return !enable_;
}

// the static initializer is thumb code
#pragma thumb on
