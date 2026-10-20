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
    unk_004.m_pos.setFix32(0, 0, 1);
    unk_004.m_up.setFix32(0, 1, 0);
    unk_004.m_angle.set(0x2000, 0, 0);
    unk_004.m_distance = 8L;
    unk_004.m_fov2 = 5;
    unk_074.m_pos.setFix32(0, 0, 1);
    unk_074.m_up.setFix32(0, 1, 0);
    unk_074.m_angle.set(0x2000, 0, 0);
    unk_074.m_distance = 8L;
    unk_074.m_fov2 = 5;
    unk_0e4 = 1;
}

THUMB void dss::UnkDualCameraBase::unkfunc_02051c88()
{
    if (getDisplayFrame() & 1) {
        unk_0e4 = 0;
    } else {
        unk_0e4 = 1;
    }
}

THUMB void dss::UnkDualCameraBase::update()
{
}

THUMB void dss::UnkDualCameraBase::calcPosition()
{
    unkfunc_02051c88();
    unk_004.calcPosition();
}

THUMB void dss::UnkDualCameraBase::unkfunc_02051cbc()
{
    update();
    calcPosition();
    unkfunc_02051cd8();
}

THUMB void dss::UnkDualCameraBase::unkfunc_02051cd8()
{
    unkfunc_02051c88();
    Camera* camera;
    if (unk_0e4 != 0) {
        camera = &unk_074;
    } else {
        camera = &unk_004;
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

THUMB void dss::UnkDualCameraBase::unkfunc_02051ddc(const Fix32Vector3& target, int screen)
{
    if (screen == 0) {
        unk_004.setTarget(target);
    } else {
        unk_074.setTarget(target);
    }
}

THUMB dss::UnkDualCamera::UnkDualCamera()
{
    unkfunc_02051ddc(Fix32Vector3(0, 0, 0), 0);
    unk_0f0 = 0.0f;
    unk_0e4 = 1;
    unk_0f4 = 0;
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
        Fix32Vector3 direction = unk_004.getTarget() - unk_004.getPosition();
        direction.normalize();
        unk_004.m_direction = direction;
    }
    UnkMatrix43 rotX;
    UnkMatrix43 rotY;
    rotX.unkfunc_0204f4b4(unk_004.m_angle.vx);
    rotY.unkfunc_0204f4ec(unk_004.m_angle.vy);
    Fix32Vector3 up(0, 1, 0);
    Fix32Vector3 offset;
    up = rotX * up;
    up = rotY * up;
    offset = up * unk_0f0;
    unk_074.setPosition(unk_004.getPosition() + offset);
    unk_074.setTarget(unk_004.getTarget() + offset);
    unk_074.setDistance(unk_004.getDistance());
    unk_074.setAngle(unk_004.getAngle());
    offset = unk_074.m_target_pos - unk_074.m_pos;
    rotX.unkfunc_0204f4b4(unk_0f4);
    rotY.unkfunc_0204f4ec(-unk_074.m_angle.vy);
    offset = rotY * offset;
    offset = rotX * offset;
    rotY.unkfunc_0204f4ec(unk_074.m_angle.vy);
    offset = rotY * offset;
    unk_074.m_target_pos = unk_074.m_pos + offset;
}
