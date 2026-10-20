#pragma ipa file
#include "ov005/fld/FieldCamera.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

namespace dq5 {
    const float TOWN_CAMERA_DISTANCE = 39.55f;
}

static const dss::Fix32Vector3 position(0, 0, 0);
static dss::Vector3<short> default_angle(0xde94, 0, 0);
static dss::Fix32 distance(dq5::TOWN_CAMERA_DISTANCE);
static dss::Fix32 offset(2L);
static short dir_offset = 0x5b0;
static short fov = 10;

inline void dss::UnkDualCamera::setup()
{
    unk_004.setup();
    unk_074.setup();
}

inline void dss::UnkDualCamera::setDistance(Fix32 distance)
{
    unk_004.setDistance(distance);
    unk_074.setDistance(distance);
}

inline void dss::UnkDualCamera::setAngle(Vector3<short> angle)
{
    unk_004.setAngle(angle);
}

inline void dss::UnkDualCamera::setOffset(Fix32 offset)
{
    unk_0f0 = offset;
}

inline void dss::UnkDualCamera::setFOV2(int fovy)
{
    unk_004.setFOV2(fovy);
    unk_074.setFOV2(fovy);
}

inline void dss::UnkDualCamera::setScaleW(Fix32 scaleW)
{
    unk_004.setScaleW(Fix32(scaleW));
    unk_074.setScaleW(Fix32(scaleW));
}

THUMB fld::FieldCamera::FieldCamera()
{
}

THUMB fld::FieldCamera::~FieldCamera()
{
}

THUMB fld::FieldCamera& fld::FieldCamera::getSingleton()
{
    static FieldCamera camera_;
    return camera_;
}

THUMB void fld::FieldCamera::initialize()
{
    camera_.setup();
    camera_.setTarget(position, 0);
    camera_.setDistance(distance);
    camera_.setAngle(default_angle);
    camera_.setOffset(offset);
    camera_.unk_0f4 = dir_offset;
    camera_.unk_0e4 = 1;
    camera_.unk_0e8 = 0;
    camera_.unk_0ec = 0;
    camera_.setFOV2(fov);
    dss::Fix32 scalew;
    scalew.value = 0x100;
    camera_.setScaleW(scalew);
}

THUMB void fld::FieldCamera::terminate()
{
}

THUMB void fld::FieldCamera::execute()
{
}

THUMB void fld::FieldCamera::draw()
{
    dss::Fix32Vector3 target;
    target = FieldPlayerManager::getSingleton().getPosition();
    target.vx.value = target.vx.value / 32;
    target.vz.value = target.vy.value / 32;
    target.vy.value = 0;
    camera_.unk_004.setTarget(target);
    camera_.applyCamera();
    camera_.unk_074.calcLookDirection();
}
