#pragma ipa file
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkDssMath.hpp"
#include "main/dss/UnkMatrix43.hpp"
#include "main/global/Global.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/object/DSSAObject.hpp"
#include "main/status/StageInfo.hpp"

inline void dss::UnkDualCamera::setOffset(Fix32 offset)
{
    unk_0f0 = offset;
}

inline void dss::UnkDualCamera::setRotXYZ(Vector3<short> angle)
{
    unk_004.setAngle(angle);
}

inline void dss::UnkDualCamera::setDistance(Fix32 distance)
{
    unk_004.setDistance(distance);
    unk_074.setDistance(distance);
}

inline void dss::UnkDualCamera::setFOV2(int fovy)
{
    unk_004.setFOV2(fovy);
    unk_074.setFOV2(fovy);
}

inline void dss::UnkDualCamera::setScaleW(Fix32 scaleW)
{
    unk_004.setScaleW(scaleW);
    unk_074.setScaleW(scaleW);
}

inline VecFx32* twn::TownStageManager::GetCameraPosFX32(int no)
{
    return &stage_.m_fld.m_x32_camera_pos[no];
}

inline VecFx32* twn::TownStageManager::GetCameraCentFX32(int no)
{
    return &stage_.m_fld.m_x32_camera_tag[no];
}

inline VecFx32* twn::TownStageManager::GetCameraUpFX32(int no)
{
    return &stage_.m_fld.m_x32_camera_vec[no];
}

inline bool isEven()
{
    return (getDisplayFrame() & 1) == 0;
}

inline void BillboardCharacter::setChangeCameraAngle(bool flag)
{
    changeAngle_ = flag;
}

namespace dq5 {
    static const float TOWN_CAMERA_DISTANCE = 39.55f;
}

static const dss::Fix32Vector3 position(0, 0, 0);
static dss::Vector3<short> default_angle(-8556, 0, 0);
static dss::Fix32 distance(dq5::TOWN_CAMERA_DISTANCE);
static dss::Fix32 offset(2L);
static short dir_offset = 1456;
static short fov = 10;

THUMB TownCamera::TownCamera()
{
}

THUMB TownCamera::~TownCamera()
{
}

THUMB TownCamera* TownCamera::getSingleton()
{
    static TownCamera camera_;
    return &camera_;
}

THUMB void TownCamera::initialize()
{
    camera_.unk_004.setup();
    camera_.unk_074.setup();
    camera_.setTarget(position, 0);
    camera_.setDistance(distance);
    camera_.setRotXYZ(default_angle);
    camera_.setOffset(offset);
    camera_.unk_0f4 = dir_offset;
    camera_.unk_0e4 = 1;
    camera_.unk_0e8 = 0;
    camera_.unk_0ec = 0;
    camera_.setFOV2(fov);
    dss::Fix32 scaleW;
    scaleW.value = 0x100;
    camera_.setScaleW(scaleW);
    store();
    cameraLock_ = 0;
    remote_ = MOVE_NONE;
    saveFlag_ = 0;
    distance_ = distance;
    camera_.m_pursue = 1;
    povLock_ = 0;
    counter_ = 0;
    isPovMove_ = 0;
    endCameraReset_ = 0;
    effect_ = 0;
    changeDefaultAngleFlag_ = 0;
    changeDefaultAngle_ = default_angle;
    povOffset_.set(0, 0, 0);
    notEqualPreAngle_ = 1;
}

THUMB void TownCamera::terminate()
{
    if (changeDefaultAngleFlag_ == 1) {
        dss::Vector3<short> angle(default_angle.vx, default_angle.vy, default_angle.vz);
        angle.vy = camera_.unk_004.getAngle().vy;
        camera_.unk_004.setAngle(angle);
    }
    if (endCameraReset_ == 1 || g_Global.nextMapNameId == 999) {
        camera_.unk_004.setAngle(default_angle);
    }
    restore();
}

THUMB void TownCamera::execute()
{
    if (cameraLock_ == 0) {
        camera_.unk_004.setTarget(cmn::g_cmnPartyInfo.position_);
        saveFlag_ = 0;
    } else {
        gazeMove();
        angleRot();
        changeDistance();
        effectAction();
        viewMove();
        lockUpdate();
        notEqualPreAngle_ = 0;
    }
    if (preAngle_.vy != camera_.unk_004.getAngle().vy || preAngle_.vx != camera_.unk_004.getAngle().vx ||
        preAngle_.vz != camera_.unk_004.getAngle().vz) {
        notEqualPreAngle_ = 1;
    }
    if (notEqualPreAngle_ > 2) {
        BillboardCharacter::setChangeCameraAngle(false);
    } else {
        BillboardCharacter::setChangeCameraAngle(true);
    }
    dss::Vector3<short>& now = camera_.unk_004.getAngle();
    short y = now.vy;
    short z = now.vz;
    preAngle_.set(now.vx, y, z);
    notEqualPreAngle_++;
}

THUMB void TownCamera::gazeMove()
{
    switch (remote_) {
    case MOVE_NONE:
        break;
    case MOVE_TARGET_PLAYER:
        camera_.unk_004.setTarget(cmn::g_cmnPartyInfo.position_);
        break;
    case MOVE_TARGET_CHARA:
        camera_.unk_004.setTarget(TownCharacterManager::getSingleton()->getPosition(targetChara_));
        break;
    case MOVE_AREA:
        checkArea();
        camera_.unk_004.setTarget(target_);
        break;
    default:
        dss::Fix32Vector3 pos = camera_.unk_004.getTarget();
        cameraMove_.execMove(pos);
        camera_.unk_004.setTarget(pos);
        cameraMove_.moveUpdate();
        break;
    }
}

THUMB void TownCamera::angleRot()
{
    if (changeAngle_ == 1) {
        dss::Vector3<short>& now = camera_.unk_004.getAngle();
        dss::Vector3<short> angle(now.vx, now.vy, now.vz);
        cameraMove_.execRot(angle);
        camera_.unk_004.setAngle(angle);
        if (cameraMove_.rotUpdate() == 1) {
            changeAngle_ = 0;
        }
        notEqualPreAngle_ = 1;
    }
}

THUMB void TownCamera::changeDistance()
{
    if (changeDistance_ == 1) {
        if (counter_ > frame_) {
            changeDistance_ = 0;
        }
        if (counter_ < frame_) {
            distance_ = startDistance_ + addDistance_ * counter_ / frame_;
            camera_.unk_004.setDistance(distance_);
        } else {
            camera_.unk_004.setDistance(endDistance_);
        }
        counter_++;
    }
}

THUMB void TownCamera::effectAction()
{
    if (effect_ == 1) {
        if (cameraLock_ == 0 || remote_ == MOVE_TARGET_CHARA || remote_ == MOVE_TARGET_PLAYER) {
            effecter_.setMoveLock(true);
        } else {
            effecter_.setMoveLock(false);
        }
        dss::Fix32Vector3 effpos = camera_.unk_004.getTarget();
        effecter_.execMove(effpos);
        camera_.unk_004.setTarget(effpos);
        if (effecter_.moveUpdate()) {
            effect_ = 0;
        }
    }
}

THUMB void TownCamera::viewMove()
{
    if (povLock_ == 1) {
        dss::Fix32Vector3 povPos = camera_.unk_004.getPosition();
        switch (remote_) {
        case MOVE_TARGET_CHARA:
        case MOVE_TARGET_PLAYER:
            dss::Fix32Vector3 target = camera_.unk_004.getTarget();
            dss::Vector3<short>& now = camera_.unk_004.getAngle();
            dss::Vector3<short> angle(now.vx, now.vy, now.vz);
            unkfunc_021403a0(angle, povPos, target);
            povPos += povOffset_;
            break;
        }
        if (isPovMove_ == 1) {
            dss::Fix32Vector3 oldPovPos = povPos;
            povMove_.execMove(povPos);
            povOffset_ += povPos - oldPovPos;
            if (povMove_.moveUpdate() == 1) {
                isPovMove_ = 0;
            }
        }
        camera_.unk_004.setPosition(povPos);
        dss::Fix32Vector3& dirVec = camera_.unk_004.getDirection();
        dirVec = camera_.unk_004.getTarget() - camera_.unk_004.getPosition();
        camera_.unk_004.setDistance(dirVec.length());
        dirVec.normalize();
    }
}

THUMB void TownCamera::lockUpdate()
{
    if (remote_ != MOVE_NONE && cameraMove_.isEnd() == true) {
        switch (remote_) {
        case MOVE_VIBMOTION:
        case MOVE_RANDOM:
        case MOVE_RESET:
        case MOVE_TARGET_CHARA:
        case MOVE_TARGET_PLAYER:
        case MOVE_AREA:
            break;
        default:
            remote_ = MOVE_NONE;
            break;
        }
    }
}

THUMB void TownCamera::draw()
{
    int no0 = twn::TownStageManager::getSingleton()->stage_.m_fld.m_camera_no[0];
    int no1 = twn::TownStageManager::getSingleton()->stage_.m_fld.m_camera_no[1];
    if (no0 == 0 && no1 == 0) {
        camera_.applyCamera();
        if (getDisplayFrame() & 1) {
            ((getDisplayFrame() & 1) == 0 ? &camera_.unk_004 : &camera_.unk_074)->unkfunc_02046934();
        } else {
            ((getDisplayFrame() & 1) == 0 ? &camera_.unk_004 : &camera_.unk_074)->unkfunc_02046934();
        }
    } else {
        dss::Camera* cam = (getDisplayFrame() & 1) == 0 ? &camera_.unk_004 : &camera_.unk_074;
        int no = getDisplayFrame() & 1;
        cam->m_pos.vx.value = twn::TownStageManager::getSingleton()->GetCameraPosFX32(no)->x;
        cam->m_pos.vy.value = twn::TownStageManager::getSingleton()->GetCameraPosFX32(no)->y;
        cam->m_pos.vz.value = twn::TownStageManager::getSingleton()->GetCameraPosFX32(no)->z;
        cam->m_up.vx.value = twn::TownStageManager::getSingleton()->GetCameraUpFX32(no)->x;
        cam->m_up.vy.value = twn::TownStageManager::getSingleton()->GetCameraUpFX32(no)->y;
        cam->m_up.vz.value = twn::TownStageManager::getSingleton()->GetCameraUpFX32(no)->z;
        cam->m_target_pos.vx.value = twn::TownStageManager::getSingleton()->GetCameraCentFX32(no)->x;
        cam->m_target_pos.vy.value = twn::TownStageManager::getSingleton()->GetCameraCentFX32(no)->y;
        cam->m_target_pos.vz.value = twn::TownStageManager::getSingleton()->GetCameraCentFX32(no)->z;
        camera_.applyG3d();
        BillboardCharacter::setCamera(!isEven() ? &camera_.unk_004 : &camera_.unk_074);
    }
    DSSAObjectWithCamera::camera_ = !isEven() ? &camera_.unk_004 : &camera_.unk_074;
    flagRotateL = 0;
    flagRotateR = 0;
}

THUMB bool TownCamera::setAngleNorth(short& retAngle)
{
    bool ret = false;
    dss::Vector3<short>& now = camera_.unk_004.getAngle();
    dss::Vector3<short> target(now.vx, now.vy, now.vz);
    short dy = target.vy > 0 ? -0x200 : 0x200;
    if (target.vy < 0x200 && target.vy > -0x200) {
        dy = 0;
        target.vy = 0;
        camera_.setRotXYZ(target);
        ret = true;
    } else {
        target.vy += dy;
        camera_.setRotXYZ(target);
    }
    retAngle = dy;
    return ret;
}

THUMB bool TownCamera::rotateL()
{
    dss::Vector3<short>& now = camera_.unk_004.getAngle();
    dss::Vector3<short> angle(now.vx, now.vy, now.vz);
    int prev = angle.vy;
    angle.vy = prev + 0x100;
    if (limitL == dss::Fix32(-1L)) {
        if (cmn::g_cmnPartyInfo.cameraRot_ == 1) {
            angle.vy = 0;
        }
    } else if (limitL != dss::Fix32(0L)) {
        if (cmn::g_cmnPartyInfo.cameraRot_ == 1) {
            angle.vy = dss::clamp<int>(angle.vy, -degreeToAngle(limitR), degreeToAngle(limitL));
        }
    }
    int ry = angle.vy;
    if (ry == 0) {
        flagRotateL = 0;
    } else {
        flagRotateL = 1;
    }
    camera_.setRotXYZ(angle);
    if (prev == ry) {
        return false;
    }
    return true;
}

THUMB bool TownCamera::rotateR()
{
    dss::Vector3<short>& now = camera_.unk_004.getAngle();
    dss::Vector3<short> angle(now.vx, now.vy, now.vz);
    int prev = angle.vy;
    angle.vy = prev - 0x100;
    if (limitR == dss::Fix32(-1L)) {
        if (cmn::g_cmnPartyInfo.cameraRot_ == 1) {
            angle.vy = 0;
        }
    } else if (limitR != dss::Fix32(0L)) {
        if (cmn::g_cmnPartyInfo.cameraRot_ == 1) {
            angle.vy = dss::clamp<int>(angle.vy, -degreeToAngle(limitR), degreeToAngle(limitL));
        }
    }
    int ry = angle.vy;
    if (ry == 0) {
        flagRotateR = 0;
    } else {
        flagRotateR = 1;
    }
    camera_.setRotXYZ(angle);
    if (prev == ry) {
        return false;
    }
    return true;
}

THUMB void TownCamera::setLimitL(dss::Fix32 left)
{
    limitL = left;
    dss::Vector3<short>& now = camera_.unk_004.getAngle();
    dss::Vector3<short> angle(now.vx, now.vy, now.vz);
    if (limitL != dss::Fix32(0L)) {
        if (limitL == dss::Fix32(-1L)) {
            camera_.setRotXYZ(changeDefaultAngle_);
            return;
        }
        if (angle.vy > (short)degreeToAngle(limitL)) {
            angle.vy = degreeToAngle(limitL);
        }
        camera_.setRotXYZ(angle);
    }
}

THUMB void TownCamera::setLimitR(dss::Fix32 right)
{
    limitR = right;
    dss::Vector3<short>& now = camera_.unk_004.getAngle();
    dss::Vector3<short> angle(now.vx, now.vy, now.vz);
    if (limitR != dss::Fix32(0L)) {
        if (limitR == dss::Fix32(-1L)) {
            camera_.setRotXYZ(changeDefaultAngle_);
            return;
        }
        if (angle.vy < (short)-degreeToAngle(limitR)) {
            angle.vy = -degreeToAngle(limitR);
        }
        camera_.setRotXYZ(angle);
    }
}

THUMB void TownCamera::resetAngle()
{
    notEqualPreAngle_ = 1;
    dss::Vector3<short>& pre = camera_.unk_004.getAngle();
    short y = pre.vy;
    short z = pre.vz;
    preAngle_.set(pre.vx, y, z);
    dss::Vector3<short>& now = camera_.unk_004.getAngle();
    dss::Vector3<short> angle(now.vx, now.vy, now.vz);
    angle.vy = 0;
    camera_.setRotXYZ(angle);
}

THUMB void TownCamera::store()
{
    dss::Vector3<short>& now = camera_.unk_004.getAngle();
    short y = now.vy;
    short z = now.vz;
    preAngle_.set(now.vx, y, z);
    dss::Vector3<short>& pop = status::g_StageInfo.popCameraAngle();
    dss::Vector3<short> angle(pop.vx, pop.vy, pop.vz);
    if (angle.vx != 0 || angle.vy != 0 || angle.vz != 0) {
        camera_.setRotXYZ(angle);
    }
}

THUMB void TownCamera::restore()
{
    dss::Vector3<short>& now = camera_.unk_004.getAngle();
    dss::Vector3<short> angle(now.vx, now.vy, now.vz);
    status::g_StageInfo.pushCameraAngle(angle);
}

THUMB void TownCamera::setMoveTo(dss::Fix32Vector3& target, int frame, bool absFlag)
{
    dss::Fix32Vector3 pos = camera_.unk_004.getTarget();
    dss::Fix32Vector3 tTarget;
    tTarget = absFlag ? target : target + pos;
    cameraMove_.setActionMove(pos, tTarget);
    if (frame) {
        cameraMove_.setMoveFrame(frame);
    }
    if (saveFlag_ == 0) {
        savePos_ = pos;
        dss::Vector3<short>& now = camera_.unk_004.getAngle();
        saveAngle_.vx = now.vx;
        saveAngle_.vy = now.vy;
        saveAngle_.vz = now.vz;
    }
    remote_ = MOVE_SIMPLE;
    cameraLock_ = 1;
    saveFlag_ = 1;
}

THUMB void TownCamera::setRotTo(dss::Vector3<short>& angle, int frame, bool absFlag)
{
    if (frame == 0 && absFlag == true) {
        camera_.setRotXYZ(angle);
        return;
    }
    dss::Vector3<short>& now = camera_.unk_004.getAngle();
    dss::Vector3<short> angleNow(now.vx, now.vy, now.vz);
    if (!absFlag) {
        angle.vx += angleNow.vx;
        angle.vy += angleNow.vy;
        angle.vz += angleNow.vz;
    }
    cameraMove_.setActionRot(angleNow, angle);
    cameraMove_.setRotFrame(frame, 0);
    if (absFlag == true && angleNow.vx == angle.vx && angleNow.vz == angle.vz && frame != 0 &&
        dss::abs<short>(cameraMove_.getRotIdx().vy) < 100) {
        cameraMove_.setRotSpeedY(100);
    }
    if (saveFlag_ == 0) {
        savePos_ = camera_.unk_004.getTarget();
        saveAngle_.vx = angleNow.vx;
        saveAngle_.vy = angleNow.vy;
        saveAngle_.vz = angleNow.vz;
    }
    saveFlag_ = 1;
    changeAngle_ = 1;
}

THUMB void TownCamera::resetCameraMove(int frame)
{
    dss::Fix32Vector3 pos = camera_.unk_004.getTarget();
    dss::Fix32Vector3 target = twn::TownPlayerManager::getSingleton().getPosition();
    if (dss::abs<long>((pos - target).lengthsq().value) > 100) {
        cameraMove_.setActionMove(pos, target);
        cameraMove_.setMoveFrame(frame);
    } else {
        camera_.unk_004.setTarget(target);
    }
    dss::Vector3<short>& now = camera_.unk_004.getAngle();
    dss::Vector3<short> angleNow(now.vx, now.vy, now.vz);
    dss::Vector3<short> angle(0, 0, 0);
    if (changeDefaultAngleFlag_ == 0) {
        cameraMove_.setActionRot(angleNow, default_angle);
        cameraMove_.setRotFrame(frame, 0);
        if (angleNow.vx == default_angle.vx && angleNow.vz == default_angle.vz && frame != 0 &&
            dss::abs<short>(cameraMove_.getRotIdx().vy) < 100) {
            cameraMove_.setRotSpeedY(100);
        }
    } else {
        cameraMove_.setActionRot(angleNow, changeDefaultAngle_);
        cameraMove_.setRotFrame(frame, 0);
        if (angleNow.vx == changeDefaultAngle_.vx && angleNow.vz == changeDefaultAngle_.vz && frame != 0 &&
            dss::abs<short>(cameraMove_.getRotIdx().vy) < 100) {
            cameraMove_.setRotSpeedY(100);
        }
    }
    resetDistance(frame);
    remote_ = MOVE_RESET;
    cameraLock_ = 1;
    changeAngle_ = 1;
}

THUMB void TownCamera::setShake(int type, int count)
{
    dss::Fix32Vector3 targetPos = camera_.unk_004.getTarget();
    dss::Fix32Vector3 startPos = targetPos;
    int endframe = count << 3;
    dss::Fix32 len;
    len.value = 1000;
    switch (type) {
    case 0: {
        dss::Fix32Vector3 vec;
        twn::TownActionCalculate::getDirByIdx((short)(camera_.unk_004.getAngle().vy + 0x4000), vec);
        targetPos += vec * len;
        effecter_.setRandomShake(startPos, targetPos, count);
        break;
    }
    case 3:
        targetPos.vy.value += 500;
        effecter_.setVibMotion(startPos, targetPos, 15, endframe - 15, endframe);
        break;
    case 1:
        targetPos.vy.value += 1000;
        effecter_.setVibMotion(startPos, targetPos, 15, endframe - 15, endframe);
        break;
    case 2:
        targetPos.vy.value += 2000;
        effecter_.setVibMotion(startPos, targetPos, 15, endframe - 15, endframe);
        break;
    }
    effect_ = 1;
}

THUMB void TownCamera::setChangeDistance(int frame, dss::Fix32 end)
{
    if (frame == 0) {
        camera_.setDistance(end);
        return;
    }
    counter_ = 0;
    frame_ = frame;
    endDistance_ = end;
    changeDistance_ = 1;
    distance_ = (camera_.unk_004.getTarget() - camera_.unk_004.getPosition()).length();
    camera_.unk_004.setDistance(distance_);
    dss::Fix32Vector3& dirVec = camera_.unk_004.getDirection();
    dirVec = camera_.unk_004.getTarget() - camera_.unk_004.getPosition();
    dirVec.normalize();
    addDistance_ = endDistance_ - distance_;
    startDistance_ = distance_;
}

THUMB void TownCamera::resetDistance(int frame)
{
    if (frame == 0) {
        camera_.setDistance(distance);
        return;
    }
    counter_ = 0;
    endDistance_ = distance;
    distance_ = (camera_.unk_004.getTarget() - camera_.unk_004.getPosition()).lengthsq();
    if (dss::abs<long>((distance_ - distance * distance).value) <= 0x1000) {
        camera_.setDistance(distance);
        return;
    }
    distance_ = distance_.sqrt();
    frame_ = frame;
    changeDistance_ = 1;
    camera_.setDistance(distance_);
    dss::Fix32Vector3& dirVec = camera_.unk_004.getDirection();
    dirVec = camera_.unk_004.getTarget() - camera_.unk_004.getPosition();
    dirVec.normalize();
    addDistance_ = endDistance_ - distance_;
    startDistance_ = distance_;
}

THUMB bool TownCamera::isEndChangeDistance()
{
    return changeDistance_ == 0;
}

THUMB void TownCamera::setPovMove(dss::Fix32Vector3 target, int frame, int flag)
{
    dss::Fix32Vector3 start = camera_.unk_004.getPosition();
    if (flag) {
        target += start;
    }
    povMove_.setAddMove(start, target, frame);
    isPovMove_ = 1;
    povLock_ = 1;
}

THUMB void TownCamera::unkfunc_021403a0(dss::Vector3<short>& angle, dss::Fix32Vector3& pos, dss::Fix32Vector3& target)
{
    dss::UnkMatrix43 rotX;
    dss::UnkMatrix43 rotY;
    dss::Fix32Vector3& dirVec = camera_.unk_004.getDirection();
    rotX.setRotX(angle.vx);
    rotY.setRotY(angle.vy);
    dirVec.setFix32(0, 0, 1);
    dirVec *= camera_.unk_004.getDistance();
    dirVec = rotX * dirVec;
    dirVec = rotY * dirVec;
    pos = target + dirVec;
    dirVec *= -1;
}

THUMB void TownCamera::setTargetPlayer(int flag)
{
    if (flag == true) {
        remote_ = MOVE_TARGET_PLAYER;
        cameraLock_ = 1;
    } else {
        remote_ = MOVE_NONE;
    }
}

THUMB void TownCamera::setMoveTargetPlayer(int frame)
{
    dss::Fix32Vector3 target = twn::TownPlayerManager::getSingleton().getPosition();
    setMoveTo(target, frame, true);
}

THUMB void TownCamera::setMoveTragetChara(int index)
{
    cameraLock_ = 1;
    remote_ = MOVE_TARGET_CHARA;
    targetChara_ = index;
}

THUMB void TownCamera::setCameraLock(int flag)
{
    if (flag == false) {
        remote_ = MOVE_NONE;
    }
    cameraLock_ = flag;
}

THUMB void TownCamera::angleCalc()
{
    dss::Fix32 len = (camera_.unk_004.getPosition() - camera_.unk_004.getTarget()).length();
    camera_.unk_004.setDistance(len);
    dss::Vector3<short> angle;
    dss::Fix32Vector3 vec = camera_.unk_004.getTarget() - camera_.unk_004.getPosition();
    angle = camera_.unk_004.getAngle();
    dss::Fix32Vector3 tvec;
    tvec = vec * -1;
    if (tvec.vz > dss::Fix32(0L)) {
        twn::TownActionCalculate::getIdxByVec(angle.vy, tvec);
    } else if (tvec.vx < dss::Fix32(0L)) {
        tvec.vz *= -1;
        tvec.vx *= -1;
        twn::TownActionCalculate::getIdxByVec(angle.vy, tvec);
        angle.vy += 0x8000;
    } else {
        twn::TownActionCalculate::getIdxByVec(angle.vy, tvec);
    }
    tvec.vy = 0L;
    tvec.vz = tvec.length() * (vec.vz > dss::Fix32(0L) ? -1 : 1);
    tvec.vx = vec.vy * -1;
    if (tvec.vz >= dss::Fix32(0L)) {
        twn::TownActionCalculate::getIdxByVec(angle.vx, tvec);
        angle.vx *= -1;
    } else if (tvec.vx < dss::Fix32(0L)) {
        tvec.vz *= -1;
        twn::TownActionCalculate::getIdxByVec(angle.vx, tvec);
    } else {
        tvec.vz *= -1;
        twn::TownActionCalculate::getIdxByVec(angle.vx, tvec);
        angle.vx *= -1;
    }
    camera_.unk_004.setAngle(angle);
    dss::Fix32Vector3& dir = camera_.unk_004.getDirection();
    dir = vec;
}

THUMB void TownCamera::setLockPov(int flag)
{
    povLock_ = flag;
    camera_.m_pursue = !flag;
    povOffset_.set(0, 0, 0);
    if (!flag) {
        angleCalc();
    }
}

THUMB void TownCamera::setDefaultAngle(dss::Vector3<short>& angle)
{
    dss::Vector3<short> temp(angle.vx, angle.vy, angle.vz);
    if (temp.vy == 0) {
        temp.vy = camera_.unk_004.getAngle().vy;
    }
    camera_.unk_004.setAngle(temp);
    changeDefaultAngle_ = angle;
    changeDefaultAngleFlag_ = 1;
}

THUMB void TownCamera::checkArea()
{
    if (target_.vx > maxPos_.vx) {
        target_.vx = maxPos_.vx;
    } else if (target_.vx < minPos_.vx) {
        target_.vx = minPos_.vx;
    }
    if (target_.vz > maxPos_.vz) {
        target_.vz = maxPos_.vz;
    } else if (target_.vz < minPos_.vz) {
        target_.vz = minPos_.vz;
    }
}

THUMB void TownCamera::setArea(dss::Fix32Vector3& pos1, dss::Fix32Vector3& pos2)
{
    minPos_ = pos1;
    maxPos_ = pos2;
}

THUMB void TownCamera::setCameraAreaMove(bool flag)
{
    if (flag == true) {
        cameraLock_ = 1;
        remote_ = MOVE_AREA;
    } else {
        remote_ = MOVE_NONE;
        cameraLock_ = 0;
    }
}
