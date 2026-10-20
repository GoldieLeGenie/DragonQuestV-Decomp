#pragma ipa file
#include "main/dss/Camera.hpp"
#include "main/dss/UnkMatrix43.hpp"
#include <nitro/fx/fx_trig.h>

static UnkCamera s_camera;

static const dss::Fix32 s_unk0(0.0625f);
static const dss::Fix32 s_unk1(150L);
static const dss::Fix32 s_unk2(4L);
static const dss::Fix32 s_unk3(4L);
static const dss::Fix32 s_unk4(-4L);

THUMB UnkCamera::UnkCamera()
{
    m_pos.setFix32(0, 0, 10);
    m_up.setFix32(0, 1, 0);
    m_angle.set(0, 0, 0);
    setDistance(dss::Fix32(16L));
}

THUMB void UnkCamera::update()
{
}

THUMB void UnkCamera::calcPosition()
{
    dss::UnkMatrix43 rotX;
    dss::UnkMatrix43 rotY;
    dss::UnkMatrix43 rot;
    rotX.setRotX(m_angle.vx);
    rotY.setRotY(m_angle.vy);
    m_up.vx.value = -FX_SinIdx(m_angle.vz + 0x8000);
    m_up.vy.value = -FX_CosIdx(m_angle.vz + 0x8000);
    rot = rotX * rotY;
    m_direction.setFix32(0, 0, -10);
    m_direction = rot * m_direction;
    m_target_pos = m_direction * getDistance() + m_pos;
}

// not in the ROM (dead-stripped): stand-in for the unknown 2-byte zero literal at 0x0209a42e that follows the
// constructor's angle literals (a short const-ref argument of a removed function)
THUMB void unkfunc_unused_0209a42e(dss::Vector3<short>& angle, short x, short y)
{
    angle.set(x, y, 0);
}
