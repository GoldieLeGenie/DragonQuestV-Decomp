#pragma ipa file
#include "main/dss/Camera.hpp"
#include "main/dss/UnkMatrix43.hpp"
#include "main/dss/UnkDisplay.hpp"

static const dss::Fix32 s_unk0(0.0625f);
static const dss::Fix32 s_unk1(150L);
static const dss::Fix32 s_unk2(4L);
static const dss::Fix32 s_unk3(4L);
static const dss::Fix32 s_unk4(-4L);

THUMB dss::UnkDualCameraBase::UnkDualCameraBase()
{
    m_camera0.m_pos.setFix32(0, 0, 1);
    m_camera0.m_up.setFix32(0, 1, 0);
    m_camera0.m_angle.set(0x2000, 0, 0);
    m_camera0.m_distance = 8L;
    m_camera0.m_fov2 = 5;
    m_camera1.m_pos.setFix32(0, 0, 1);
    m_camera1.m_up.setFix32(0, 1, 0);
    m_camera1.m_angle.set(0x2000, 0, 0);
    m_camera1.m_distance = 8L;
    m_camera1.m_fov2 = 5;
    m_cameraNo = 1;
}

THUMB void dss::UnkDualCameraBase::updateCameraNo()
{
    if (getDisplayFrame() & 1) {
        m_cameraNo = 0;
    } else {
        m_cameraNo = 1;
    }
}

THUMB void dss::UnkDualCameraBase::update()
{
}

THUMB void dss::UnkDualCameraBase::calcPosition()
{
    updateCameraNo();
    m_camera0.calcPosition();
}

THUMB void dss::UnkDualCameraBase::applyCamera()
{
    update();
    calcPosition();
    applyG3d();
}

THUMB void dss::UnkDualCameraBase::applyG3d()
{
    updateCameraNo();
    Camera* camera;
    if (m_cameraNo != 0) {
        camera = &m_camera1;
    } else {
        camera = &m_camera0;
    }
    UnkCameraPerspective perspective = camera->m_perspective;
    Fix32Vector3 pos = camera->m_pos;
    Fix32Vector3 target = camera->m_target_pos;
    Fix32Vector3 up = camera->m_up;
    Fix32 scaleW = camera->m_scaleW;
    func_02089cf4(perspective.m_fovySin, perspective.m_fovyCos, perspective.m_aspect, perspective.m_near, perspective.m_far, scaleW.value, &data_02124bb4.projMtx);
    data_02124bb4.flag &= ~0x50;
    data_02124bb4.camPos.x = pos.vx.value;
    data_02124bb4.camPos.y = pos.vy.value;
    data_02124bb4.camPos.z = pos.vz.value;
    data_02124bb4.camUp.x = up.vx.value;
    data_02124bb4.camUp.y = up.vy.value;
    data_02124bb4.camUp.z = up.vz.value;
    data_02124bb4.camTarget.x = target.vx.value;
    data_02124bb4.camTarget.y = target.vy.value;
    data_02124bb4.camTarget.z = target.vz.value;
    func_02089528((VecFx32*)&pos, (VecFx32*)&up, (VecFx32*)&target, &data_02124bb4.cameraMtx);
    data_02124bb4.flag &= ~0xe8;
}

THUMB void dss::UnkDualCameraBase::setTarget(const Fix32Vector3& target, int screen)
{
    if (screen == 0) {
        m_camera0.setTarget(target);
    } else {
        m_camera1.setTarget(target);
    }
}

THUMB dss::UnkDualCamera::UnkDualCamera()
{
    setTarget(Fix32Vector3(0, 0, 0), 0);
    m_offset = 0.0f;
    m_cameraNo = 1;
    m_dirOffset = 0;
    m_pursue = 1;
}

THUMB void dss::UnkDualCamera::update()
{
}

THUMB void dss::UnkDualCamera::calcPosition()
{
    if (m_pursue == 1) {
        UnkDualCameraBase::calcPosition();
    } else {
        Fix32Vector3 direction = m_camera0.getTarget() - m_camera0.getPosition();
        direction.normalize();
        m_camera0.m_direction = direction;
    }
    UnkMatrix43 rotX;
    UnkMatrix43 rotY;
    rotX.setRotX(m_camera0.m_angle.vx);
    rotY.setRotY(m_camera0.m_angle.vy);
    Fix32Vector3 up(0, 1, 0);
    Fix32Vector3 offset;
    up = rotX * up;
    up = rotY * up;
    offset = up * m_offset;
    m_camera1.setPosition(m_camera0.getPosition() + offset);
    m_camera1.setTarget(m_camera0.getTarget() + offset);
    m_camera1.setDistance(m_camera0.getDistance());
    m_camera1.setAngle(m_camera0.getAngle());
    offset = m_camera1.m_target_pos - m_camera1.m_pos;
    rotX.setRotX(m_dirOffset);
    rotY.setRotY(-m_camera1.m_angle.vy);
    offset = rotY * offset;
    offset = rotX * offset;
    rotY.setRotY(m_camera1.m_angle.vy);
    offset = rotY * offset;
    m_camera1.m_target_pos = m_camera1.m_pos + offset;
}
