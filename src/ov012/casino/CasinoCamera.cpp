#pragma ipa file
#include "ov012/casino/CasinoCamera.hpp"

static const dss::Fix32Vector3 position(0, 0, -4);
namespace casino {
    static dss::Vector3<short> default_angle(0xc9f5, 0, 0);
}
static const float CAMERA_DISTANCE = 45.0f;
static dss::Fix32 distance(CAMERA_DISTANCE);
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

THUMB casino::CasinoCamera::CasinoCamera()
{
}

THUMB casino::CasinoCamera::~CasinoCamera()
{
}

THUMB casino::CasinoCamera* casino::CasinoCamera::getSingleton()
{
    static CasinoCamera camera_;
    return &camera_;
}

THUMB void casino::CasinoCamera::initialize()
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
}

THUMB void casino::CasinoCamera::terminate()
{
}

THUMB void casino::CasinoCamera::draw()
{
    camera_.applyCamera();
}
