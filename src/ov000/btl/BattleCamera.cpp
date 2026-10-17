#pragma ipa file
#include "ov000/btl/BattleCamera.hpp"
#include "ov000/btl/CameraControl.hpp"
#include "ov000/leveldata/CameraFile.hpp"

inline unsigned int ExcelBinaryData::getRecordCount() { return record_; }
inline unsigned int dq5::level::CameraFile::getArraySize() { return binary_.getRecordCount(); }
inline dq5::level::CameraFile* dq5::level::CameraFile::getRecord(int index) { return (CameraFile*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline char* dq5::level::CameraFile::getFile() { return file; }
inline dss::Fix32Vector3& btl::CameraControl::getInitPosition() { return iniPosition_; }
inline dss::Vector3<short>& btl::CameraControl::getInitAngle() { return iniAngle_; }

THUMB btl::BattleCamera::BattleCamera()
{
}

THUMB btl::BattleCamera::~BattleCamera()
{
}

namespace btl {
    namespace {
        CameraControl livecamera[16];
    }
}

THUMB btl::BattleCamera* btl::BattleCamera::getSingleton()
{
    static BattleCamera m_singleton;
    return &m_singleton;
}

THUMB void btl::BattleCamera::initialize()
{
    normalCamera_.setup();
    dss::Fix32Vector3 position(0.0f, 0.69f, 6.82f);
    normalCamera_.setPosition(position);
    normalCamera_.setFOV(0x6c3, 0xe80);
    normalCamera_.setFar(0x400000);
    normalCamera_.setFOV2(0x32);
    normalCamera_.unk_6c = 1;
    dss::Fix32 scaleW;
    scaleW.value = 0x1000;
    normalCamera_.setScaleW(scaleW);
    reset();
    normalCamera_.applyCamera();
    setCameraAnimation(0x9b, 0, 0);
    unk_070.setup();
    unk_070.setPosition(position);
    unk_070.setFOV(0x6c3, 0xe80);
    unk_070.setFar(0x400000);
    unk_070.setFOV2(0x32);
    unk_070.unk_6c = 1;
    unk_070.setScaleW(scaleW);
    dss::Vector3<short> angle;
    dss::Fix32Vector3 position2;
    livecamera[0].readCameraData("inicamera", false);
    livecamera[0].moveCamera(position2, angle);
    unk_070.setPosition(position2);
    unk_070.setAngle(angle);
    unk_070.applyCamera();
}

THUMB void btl::BattleCamera::terminate()
{
    for (int i = 0; i < 16; i++) {
        livecamera[i].terminate();
    }
}

THUMB void btl::BattleCamera::reset()
{
    dss::Vector3<short> angle;
    dss::Fix32Vector3 position;
    livecamera[0].readCameraData("inicamera", false);
    livecamera[0].moveCamera(position, angle);
    normalCamera_.setPosition(position);
    normalCamera_.setAngle(angle);
    initposition_ = position;
    enable_ = 0;
}

THUMB void btl::BattleCamera::executeForMap()
{
    dss::Vector3<short> rot;
    dss::Fix32Vector3 posSum;
    if (enable_) {
        for (int i = 0; i < 16; i++) {
            if (livecamera[i].isEnable()) {
                dss::Vector3<short> angle;
                dss::Fix32Vector3 position;
                livecamera[i].calc(position, angle);
                dss::Vector3<short>& iniAngle = livecamera[i].getInitAngle();
                angle.vx -= iniAngle.vx;
                angle.vy -= iniAngle.vy;
                angle.vz -= iniAngle.vz;
                position -= livecamera[i].getInitPosition();
                rot.vx += angle.vx;
                rot.vy += angle.vy;
                rot.vz += angle.vz;
                posSum += position;
            }
            else {
                livecamera[i].terminate();
            }
        }
    }
    normalCamera_.setAngle(rot);
    normalCamera_.setPosition(posSum + initposition_);
    normalCamera_.applyCamera();
    if (homing_.step_ != 0) {
        dss::Vector3<short>& current = normalCamera_.getAngle();
        rot.vx = current.vx;
        rot.vy = current.vy;
        rot.vz = current.vz;
        homing_.calculation(rot);
        normalCamera_.setAngle(rot);
    }
    normalCamera_.applyCamera();
}

THUMB void btl::BattleCamera::draw()
{
}

THUMB void btl::BattleCamera::initCamera(int wait)
{
    for (int i = 0; i < 16; i++) {
        if (!livecamera[i].isEnable()) {
            livecamera[i].readCameraData(file_, true);
            livecamera[i].initCameraControl(normalCamera_.getPosition(), normalCamera_.getAngle());
            livecamera[i].wait_ = 0;
            break;
        }
    }
    for (int i = 0; i < 16; i++) {
        if (!livecamera[i].isEnable()) {
            livecamera[i].readCameraData(file2_, true);
            livecamera[i].initCameraControl(normalCamera_.getPosition(), normalCamera_.getAngle());
            livecamera[i].wait_ = wait;
            break;
        }
    }
    enable_ = 1;
}

THUMB void btl::BattleCamera::setCameraAnimation(unsigned short camera1, unsigned short camera2, unsigned short wait)
{
    if (camera1 >= dq5::level::CameraFile::getArraySize()) {
        camera1 = 0xe;
    }
    if (camera2 >= dq5::level::CameraFile::getArraySize()) {
        camera2 = 0xe;
    }
    dss::strcpy(file_, dq5::level::CameraFile::getRecord(camera1)->getFile());
    dss::strcpy(file2_, dq5::level::CameraFile::getRecord(camera2)->getFile());
    initCamera(wait);
}

THUMB void btl::BattleCamera::setHomingTarget(int drawCtrlId)
{
    homing_.setup(initposition_, drawCtrlId);
}

THUMB dss::Camera* btl::BattleCamera::getCamera()
{
    return &normalCamera_;
}
