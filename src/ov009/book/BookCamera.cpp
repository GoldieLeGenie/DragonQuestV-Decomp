#pragma ipa file
#include "ov009/book/BookCamera.hpp"

static const float s_distanceF = 17.35f;

static const dss::Fix32Vector3 s_target(3.0f, 0.0f, 0.0f);
static dss::Vector3<short> s_angle(0xde94, 0, 0);
static dss::Fix32 s_distance(s_distanceF);
static dss::Fix32 s_offset(2L);
/* only used by setInitTarget: stripped from the ROM, but items of the data sort */
const short book::BookCamera::DIR_OFFSET = 0x5b0;
const short book::BookCamera::FOV = 50;

THUMB book::BookCamera::BookCamera()
{
}

THUMB book::BookCamera::~BookCamera()
{
}

THUMB book::BookCamera& book::BookCamera::getSingleton()
{
    static BookCamera m_singleton;
    return m_singleton;
}

THUMB void book::BookCamera::initialize()
{
    camera_.setup();
    camera_.setFOV(0x6c3, 0xe80);
    camera_.setFar(0x400000);
    camera_.setFOV2(0x32);
    camera_.unk_6c = 1;
    dss::Fix32 scaleW;
    scaleW.value = 0x1000;
    camera_.setScaleW(dss::Fix32(scaleW));
    dss::Fix32Vector3 pos;
    dss::Vector3<short> angle;
    pos.vx.value = 0x3800;
    pos.vy.value = 0x3200;
    pos.vz.value = 0xfc80;
    angle.vx = -0x80;
    camera_.setPosition(pos);
    camera_.setAngle(angle);
}

THUMB void book::BookCamera::terminate()
{
}

THUMB void book::BookCamera::draw()
{
    camera_.applyCamera();
}

/* not linked: no caller in the DS game, but its statics are items of the data sort */
THUMB void book::BookCamera::setInitTarget()
{
    dss::Vector3<short> angle = s_angle;
    angle.vy += DIR_OFFSET;
    camera_.setTarget(s_target);
    camera_.setDistance(s_distance);
    camera_.setAngle(angle);
    camera_.setFOV2(FOV);
}
