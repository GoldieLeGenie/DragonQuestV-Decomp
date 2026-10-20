#pragma ipa file
#include "ov004/ceremony/CeremonyCamera.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "ov004/ceremony/CeremonyStage.hpp"

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

inline int ceremony::CeremonyStage::getCameraNo(int idx)
{
    return stage_.m_fld.m_camera_no[idx];
}

inline VecFx32* ceremony::CeremonyStage::getCameraPosFX32(int idx)
{
    return &stage_.m_fld.m_x32_camera_pos[idx];
}

inline VecFx32* ceremony::CeremonyStage::getCameraCentFX32(int idx)
{
    return &stage_.m_fld.m_x32_camera_tag[idx];
}

inline VecFx32* ceremony::CeremonyStage::getCameraUpFX32(int idx)
{
    return &stage_.m_fld.m_x32_camera_vec[idx];
}

THUMB ceremony::CeremonyCamera::CeremonyCamera()
{
}

THUMB ceremony::CeremonyCamera::~CeremonyCamera()
{
}

THUMB ceremony::CeremonyCamera* ceremony::CeremonyCamera::getSingleton()
{
    static CeremonyCamera camera_;
    return &camera_;
}

THUMB void ceremony::CeremonyCamera::initialize()
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

THUMB void ceremony::CeremonyCamera::terminate()
{
}

THUMB void ceremony::CeremonyCamera::draw()
{
    int no[2];
    no[0] = CeremonyStage::getSingleton()->getCameraNo(0);
    no[1] = CeremonyStage::getSingleton()->getCameraNo(1);
    if (no[0] == 0 && no[1] == 0) {
        camera_.applyCamera();
        return;
    }
    dss::Camera* camera = (getDisplayFrame() & 1) == 0 ? &camera_.unk_004 : &camera_.unk_074;
    int screen = getDisplayFrame() & 1;
    camera->m_pos.vx.value = CeremonyStage::getSingleton()->getCameraPosFX32(screen)->x;
    camera->m_pos.vy.value = CeremonyStage::getSingleton()->getCameraPosFX32(screen)->y;
    camera->m_pos.vz.value = CeremonyStage::getSingleton()->getCameraPosFX32(screen)->z;
    camera->m_up.vx.value = CeremonyStage::getSingleton()->getCameraUpFX32(screen)->x;
    camera->m_up.vy.value = CeremonyStage::getSingleton()->getCameraUpFX32(screen)->y;
    camera->m_up.vz.value = CeremonyStage::getSingleton()->getCameraUpFX32(screen)->z;
    camera->m_target_pos.vx.value = CeremonyStage::getSingleton()->getCameraCentFX32(screen)->x;
    camera->m_target_pos.vy.value = CeremonyStage::getSingleton()->getCameraCentFX32(screen)->y;
    camera->m_target_pos.vz.value = CeremonyStage::getSingleton()->getCameraCentFX32(screen)->z;
    camera_.applyG3d();
    bool sub = !(getDisplayFrame() & 1);
    BillboardCharacter::setCamera(!sub ? &camera_.unk_004 : &camera_.unk_074);
}
