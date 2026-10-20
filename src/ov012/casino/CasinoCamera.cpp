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
    m_camera0.setup();
    m_camera1.setup();
}

inline void dss::UnkDualCamera::setDistance(Fix32 distance)
{
    m_camera0.setDistance(distance);
    m_camera1.setDistance(distance);
}

inline void dss::UnkDualCamera::setAngle(Vector3<short> angle)
{
    m_camera0.setAngle(angle);
}

inline void dss::UnkDualCamera::setOffset(Fix32 offset)
{
    m_offset = offset;
}

inline void dss::UnkDualCamera::setFOV2(int fovy)
{
    m_camera0.setFOV2(fovy);
    m_camera1.setFOV2(fovy);
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
    camera_.m_dirOffset = dir_offset;
    camera_.m_cameraNo = 1;
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
